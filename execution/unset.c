/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:21:19 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/11 19:21:23 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	remove_env_var(t_env **envp, char *var_name)
{
	t_env	*new;
	t_env	*tmp;

	new = *envp;
	tmp = NULL;
	while (new)
	{
		if (!ft_strcmp(var_name, new->var))
		{
			if (tmp)
				tmp->next = new->next;
			free(new->var);
			if (new->value)
				free(new->value);
			if (!tmp)
				*envp = (*envp)->next;
			free(new);
			return ;
		}
		tmp = new;
		new = new->next;
	}
}

int	unset(t_data *data, t_env **envp)
{
	int	i;

	i = 1;
	while (data->cmd[i])
	{
		if (data->cmd[1][0] == '-')
		{
			print_error2(" unset: -", data->cmd[i][1], ": invalid option\n");
			return (2);
		}
		remove_env_var(envp, data->cmd[i]);
		i++;
	}
	return (0);
}
