/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_out_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:16:24 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/11 19:16:27 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ambiguous(t_file *file)
{
	if (file->ambiguous == 1)
	{
		printf("minishell :%s: ambiguous redirect\n", file->name);
		return (1);
	}
	return (0);
}

int	input_file(t_file *file, t_us_var *var)
{
	if (file->infile == 1)
	{
		if (var->inpfd != -13)
			close(var->inpfd);
		var->inpfd = open(file->name, O_RDONLY);
	}
	else if (file->heredoc == 1)
	{
		if (var->inpfd != -13)
			close(var->inpfd);
		var->inpfd = file->fd[0];
	}
	if (var->inpfd == -1)
		return (1);
	return (0);
}

int	output_file(t_file *file, t_us_var *var)
{
	if (file->outfile == 1)
	{
		if (var->outfd != -13)
			close(var->outfd);
		var->outfd = open(file->name, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	}
	else if (file->apend == 1)
	{
		if (var->outfd != -13)
			close(var->outfd);
		var->outfd = open(file->name, O_WRONLY | O_APPEND | O_CREAT, 0664);
	}
	if (var->outfd == -1)
		return (1);
	return (0);
}

int	int_out_file(t_data *data, t_us_var *var)
{
	t_file	*file;

	file = data->file;
	var->inpfd = -13;
	var->outfd = -13;
	while (file)
	{
		if (input_file(file, var) || output_file(file, var))
		{
			perror(file->name);
			return (1);
		}
		if (ambiguous(file))
		{
			return (1);
		}
		file = file->next;
	}
	return (0);
}

void	input_output_free(t_data *data, t_us_var *var)
{
	if (int_out_file(data, var))
	{
		free_data(data);
		free_envp(var->envp);
		free_var(var);
		rl_clear_history();
		exit(1);
	}
}
