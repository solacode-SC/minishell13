/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_with_pipe.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:20:45 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/14 16:01:16 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_var;

void	close_pipes(t_us_var var)
{
	if (var.i > 0)
		close(var.pipe[var.i - 1][0]);
	if (var.i < var.count_cmd - 1)
		close(var.pipe[var.i][1]);
}

void	check_status(int status, t_env *envp)
{
	if (WIFSIGNALED(status))
	{
		envp->exit = 128 + WTERMSIG(status);
		if (envp->exit == 131)
			write(2, "Quit (core dumped)\n", 20);
		else if (envp->exit == 130)
			write(1, "\n", 1);
	}
	else
		envp->exit = WEXITSTATUS(status);
}

void	wait_for_children(t_us_var var, t_env *envp)
{
	int	status;

	var.i = 0;
	while (var.i < var.count_cmd)
	{
		waitpid(var.id[var.i], &status, 0);
		var.i++;
	}
	check_status(status, envp);
	free_var(&var);
}

void	init_pipe(t_us_var *var, t_data *data)
{
	g_var.flg = 1;
	var->i = 0;
	var->count_cmd = count_cmd(data);
	var->id = ft_calloc(sizeof(int), var->count_cmd + 1);
	var->pipe = ft_calloc(sizeof(int *), var->count_cmd + 1);
	if (var->id == NULL || !var->pipe)
		return ;
	g_var.var = var;
}

void	run_cmd_with_pipe(t_data **data, char **env, t_env **envp)
{
	t_us_var	var;
	t_data		*tmp;

	init_pipe(&var, *data);
	while (var.i < var.count_cmd)
	{
		var.pipe[var.i] = malloc(sizeof(int *) * 2);
		if (var.i < var.count_cmd - 1)
			var.d = pipe(var.pipe[var.i]);
		var.id[var.i] = fork();
		if (var.id[var.i] == -1 || var.d == -1)
		{
			perror(NULL);
			return ;
		}
		if (var.id[var.i] == 0)
			run_cmd_as_child(*data, var, env, envp);
		close_pipes(var);
		var.i++;
		tmp = (*data)->next;
		free_node(*data);
		*data = tmp;
	}
	wait_for_children(var, *envp);
}
