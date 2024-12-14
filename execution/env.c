/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:17:35 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 20:35:53 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_extract_variable_name(char *str)
{
	int		i;
	char	*var_name;
	int		len;

	i = 0;
	len = 0;
	while (str[len] && str[len] != '=' && str[len] != '+')
		len++;
	var_name = ft_calloc(sizeof(char), len + 1);
	if (var_name == NULL)
		return (NULL);
	len = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '+')
			var_name[len++] = str[i];
		i++;
	}
	var_name[len] = '\0';
	return (var_name);
}

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
