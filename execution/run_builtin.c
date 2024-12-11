/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_builtin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:25:29 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/11 19:25:32 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	other_builtin(t_data *data, t_env **envp)
{
	if (ft_strcmp(data->cmd[0], "env") == 0)
	{
		(*envp)->exit = env(data, *envp);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "exit") == 0)
		ft_exit(data, *envp);
	if (ft_strcmp(data->cmd[0], "unset") == 0)
	{
		(*envp)->exit = unset(data, envp);
		return (1);
	}
	return (0);
}

int	run_builtin(t_data *data, t_env **envp)
{
	if (ft_strcmp(data->cmd[0], "echo") == 0)
	{
		(*envp)->exit = echo(data);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "cd") == 0)
	{
		(*envp)->exit = cd(data, *envp);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "pwd") == 0)
	{
		(*envp)->exit = pwd(data, *envp);
		return (1);
	}
	if (ft_strcmp(data->cmd[0], "export") == 0)
	{
		(*envp)->exit = export(data, envp);
		return (1);
	}
	if (other_builtin(data, envp))
		return (1);
	return (0);
}
