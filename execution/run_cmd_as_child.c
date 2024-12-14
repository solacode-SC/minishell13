/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd_as_child.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:16:49 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/14 15:38:45 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	run_first_cmd(t_data *data, t_us_var var, char **env, t_env **envp)

{
	var.envp = *envp;
	input_output_free(data, &var);
	run_builtin_in_pipe(data, envp, var);
	var.path_cmd = get_val(*envp, "PATH");
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
	else
		dup2(var.pipe[var.i][1], 1);
	close(var.pipe[var.i][0]);
	close(var.pipe[var.i][1]);
	ft_execve(data, var, *envp, env);
}

void	run_second_cmd(t_data *data, t_us_var var, char **env, t_env **envp)
{
	var.envp = *envp;
	input_output_free(data, &var);
	run_builtin_in_pipe(data, envp, var);
	var.path_cmd = get_val(*envp, "PATH");
	var.path_spt = ft_split(var.path_cmd, ':');
	var.path_cmd = get_path_cmd(var, data);
	if (var.inpfd != -13)
	{
		dup2(var.inpfd, 0);
		close(var.inpfd);
	}
	else
		dup2(var.pipe[var.i - 1][0], 0);
	if (var.outfd != -13)
	{
		dup2(var.outfd, 1);
		close(var.outfd);
	}
	else
		dup2(var.pipe[var.i][1], 1);
	close(var.pipe[var.i - 1][0]);
	close(var.pipe[var.i][0]);
	close(var.pipe[var.i][1]);
	ft_execve(data, var, *envp, env);
}

void	run_last_cmd(t_data *data, t_us_var var, char **env, t_env **envp)
{
	var.envp = *envp;
	input_output_free(data, &var);
	run_builtin_in_pipe(data, envp, var);
	var.path_cmd = get_val(*envp, "PATH");
	var.path_spt = ft_split(var.path_cmd, ':');
	var.path_cmd = get_path_cmd(var, data);
	if (var.inpfd != -13)
	{
		dup2(var.inpfd, 0);
		close(var.inpfd);
	}
	else
		dup2(var.pipe[var.i - 1][0], 0);
	if (var.outfd != -13)
	{
		dup2(var.outfd, 1);
		close(var.outfd);
	}
	close(var.pipe[var.i - 1][0]);
	ft_execve(data, var, *envp, env);
}

void	run_cmd_as_child(t_data *data, t_us_var var, char **env, t_env **envp)
{
	signal(SIGINT, handle_ctrl_c);
	signal(SIGQUIT, SIG_IGN);
	if (var.i == 0)
		run_first_cmd(data, var, env, envp);
	if (var.i < var.count_cmd - 1)
		run_second_cmd(data, var, env, envp);
	else
		run_last_cmd(data, var, env, envp);
}
