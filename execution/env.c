/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:17:35 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/11 19:17:38 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print(t_env *envp)
{
	while (envp)
	{
		if (envp->value && envp->egnor != 1)
		{
			printf("%s", envp->var);
			printf("%s\n", envp->value);
		}
		envp = envp->next;
	}
}

int	env(t_data *data, t_env *evnp)
{
	if (data->cmd[1] == NULL)
		print(evnp);
	else if (data->cmd[1][0] == '-')
	{
		print_error1("env: invalid option -- '", data->cmd[1], "\n");
		return (125);
	}
	else
	{
		print_error1("env: ", data->cmd[1], ": No such file or directory\n");
		return (127);
	}
	return (0);
}
