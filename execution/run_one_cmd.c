/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_one_cmd.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:15:28 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/11 19:15:31 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_execve(t_data *data, t_us_var var, t_env *envp, char **env)
{
	if (execve(var.path_cmd, data->cmd, env) == -1)
	{
		free_data(data);
		free_envp(envp);
		ft_free1(var.path_spt);
		free_var(&var);
		exit(1);
	}
}

void	run_exuc(t_data *data, char **env, t_env *envp)
{
	t_us_var	var;

	var.envp = envp;
	var.pipe = NULL;
	var.id = NULL;
	var.path_cmd = get_val(envp, "PATH");
	input_output_free(data, &var);
	var.path_spt = ft_split(var.path_cmd, ':');
	var.path_cmd = get_path_cmd(var, data);
	if (var.inpfd != -13)
	{
		dup2(var.inpfd, 0);
		close(var.inpfd);
	}
	if (var.outfd != -13)
	{
		dup2(var.outfd, 1);
		close(var.outfd);
	}
	ft_execve(data, var, envp, env);
}

void	run_one_cmd(t_data *data, char **env, t_env **envp)
{
	int	pid;
	int	status;

	status = 0;
	if (run_one_builtin(data, envp))
		return ;
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return ;
	}
	if (pid == 0)
	{
		signal(SIGINT, child_handler);
		signal(SIGQUIT, child_handler1);
		run_exuc(data, env, *envp);
	}
	signal(SIGINT, SIG_IGN);
	waitpid(pid, &status, 0);
	check_status(status, *envp);
}
