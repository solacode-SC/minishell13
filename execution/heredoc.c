/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   heredoc.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:25:08 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/11 19:25:14 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g;
void	free_herdoc(int exit_s, char *str)
{
	if (str)
		printf("%s\n", str);
	free_data(g.data);
	free_envp(g.env);
	clear_history();
	exit(exit_s);
}
int	count_heredoc(t_data *data)
{
	t_file	*file;
	int		c;

	c = 0;
	while (data)
	{
		file = data->file;
		while (file)
		{
			if (file->heredoc)
				c++;
			file = file->next;
		}
		data = data->next;
	}
	return (c);
}

void	read_from_heredoc(t_file *file, t_env *env)
{
	char	*line;

	signal(SIGINT, f);
	while (1)
	{
		line = readline(">");
		if (line == NULL)
			break ;
		if (ft_strcmp(line, file->name) == 0)
		{
			free(line);
			free_herdoc(0, NULL);
		}
		line = apend_char_str(line, '\n');
		if (!file->expand)
			line = expending_herd(line, env);
		write(file->fd[1], line, ft_strlen(line));
		free(line);
	}
	if (line == NULL)
	{
		printf("here-document delimited by end-of-file(wanted`%s')\n",
			file->name);
		free_herdoc(0, NULL);
	}
}

int	wait_children(int pid, t_file *newfile)
{
	int	status;

	waitpid(pid, &status, 0);
	if ((status >> 8) == 130)
	{
		write(1, "\n", 1);
		close(newfile->fd[1]);
		return (1);
	}
	close(newfile->fd[1]);
	return (0);
}
int	heredoc(t_data *data, t_env *env)
{
	t_file	*file;
	int		pid;

	if (count_heredoc(data) > 16)
	{
		// ft_putstr("minishell: maximum here-document count exceeded") ;
		free_herdoc(2, "maximum here-document count exceeded");
		/// freee to do please do no forget .........
		exit(2);
	}
	while (data)
	{
		file = data->file;
		while (file)
		{
			if (file->heredoc == 1)
			{
				pipe(file->fd);
				pid = fork();
				if (pid == 0)
				{
					// printf("hii\n") ;
					// signal don't forgr  again please ..
					read_from_heredoc(file, env);
				}
				if (wait_children(pid, file))
					return (1);
			}
			file = file->next;
		}
		data = data->next;
	}
	return (0);
}

void	close_herdoc(t_data *data)
{
	t_file	*file;

	while (data)
	{
		file = data->file;
		while (file)
		{
			if (file->heredoc == 1 && file->fd[0])
				close(file->fd[0]);
			file = file->next;
		}
		data = data->next;
	}
}
