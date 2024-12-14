/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:16:03 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 14:21:00 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	double_free(char **str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		free(str[i]);
		i++;
	}
	free(str);
}

void	free_file(t_file *file)
{
	t_file	*tmp;

	while (file)
	{
		tmp = file->next;
		free(file->name);
		free(file);
		file = tmp;
	}
}

void	free_exit(char *str, t_us_var var, int n, t_data *data)
{
	ft_free1(var.path_spt);
	if (str != NULL)
		printf("%s", str);
	free_data(data);
	free_envp(var.envp);
	free_var(&var);
	rl_clear_history();
	exit(n);
}

void	free_var(t_us_var *var)
{
	int	i;

	i = 0;
	if (!var)
		return ;
	if (var->pipe)
	{
		while (var->pipe[i])
		{
			free(var->pipe[i]);
			i++;
		}
		free(var->pipe);
	}
	if (var->id)
		free(var->id);
}

void	free_and_exit(t_data *data, t_us_var var, t_env *envp, int exit_s)
{
	free_data(data);
	free_envp(envp);
	free_var(&var);
	rl_clear_history();
	exit(exit_s);
}
