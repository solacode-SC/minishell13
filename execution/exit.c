/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:21:33 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/14 15:58:41 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_var;

void	ft_exit(t_data *data, t_env *envp)
{
	int	exit_s;

	if (data->cmd[1] == NULL)
		exit_s = envp->exit;
	else if (data->cmd[2] != NULL)
	{
		print_error1("minishell", ":exit: too ", "many arguments\n");
		return ;
	}
	else
		exit_s = ft_atoi(data->cmd[1]);
	if (g_var.flg != 1)
		printf("exit\n");
	free_data(data);
	free_envp(envp);
	free_var(g_var.var);
	exit(exit_s);
}

void	free_envp(t_env *envp)
{
	t_env	*tmp;

	double_free(envp->env);
	while (envp)
	{
		tmp = envp;
		envp = envp->next;
		free(tmp->var);
		if (tmp->value)
			free(tmp->value);
		if (tmp->pwd)
			free(tmp->pwd);
		free(tmp);
	}
}

void	free_data(t_data *data)
{
	t_data	*tmp;

	while (data)
	{
		tmp = data->next;
		ft_free1(data->cmd);
		free_file(data->file);
		free(data);
		data = tmp;
	}
	free(data);
}

void	free_herdoc(int exit_s, char *str)
{
	if (str)
		printf("%s\n", str);
	free_data(g_var.data);
	free_envp(g_var.env);
	clear_history();
	exit(exit_s);
}
