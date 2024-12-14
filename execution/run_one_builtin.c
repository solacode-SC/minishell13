/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_one_builtin.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 20:36:39 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 20:36:52 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	dup_and_run(t_data *data, t_us_var var, t_env **envp, int flag)
{
	var.fd = dup(1);
	if (var.outfd != -13)
	{
		dup2(var.outfd, 1);
		close(var.outfd);
	}
	if (var.inpfd != -13)
		close(var.inpfd);
	if (flag == 1)
		run_builtin(data, envp);
	dup2(var.fd, 1);
	close(var.fd);
}

int	is_builtin_command(char *cmd)
{
	if (!ft_strcmp(cmd, "pwd") || !ft_strcmp(cmd, "cd") || !ft_strcmp(cmd,
			"env"))
		return (0);
	if (!ft_strcmp(cmd, "exit") || !ft_strcmp(cmd, "echo"))
		return (0);
	if (!ft_strcmp(cmd, "export") || !ft_strcmp(cmd, "unset"))
		return (0);
	return (1);
}

int	run_one_builtin(t_data *data, t_env **envp)
{
	int			flag;
	t_us_var	var;

	flag = 0;
	if (!data->cmd || !data->cmd[0])
		flag = 2;
	else if (!is_builtin_command(data->cmd[0]))
		flag = 1;
	if (flag != 0)
	{
		if (int_out_file(data, &var))
		{
			(*envp)->exit = 1;
			return (1);
		}
		dup_and_run(data, var, envp, flag);
		return (1);
	}
	return (0);
}
