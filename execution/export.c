/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:14:32 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/11 19:14:35 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_isalnumm(int c)
{
	if ((c >= 48 && c <= 57) || (c >= 65 && c <= 90) || (c >= 97 && c <= 122)
		|| c == '=' || c == '_')
		return (1);
	return (0);
}

int	ft_check_str(char *str)
{
	int	i;

	i = 0;
	while (str[i] && str[i] != '=')
	{
		if (!ft_isalnumm(str[i]))
			return (0);
		i++;
	}
	return (1);
}

int	add__env_val(char *env, t_env **envp)
{
	t_env	*new;
	char	*str;
	char	*var;

	var = skip_char(env, '+');
	new = *envp;
	while (new)
	{
		if (!ft_strcmp(var, new->var))
		{
			str = ft_strsrch(env, '=');
			if (ft_strsrch(new->value, '='))
				str = ft_strjoin(new->value, &str[1]);
			else
				str = ft_strjoin(new->value, &str[0]);
			free(new->value);
			new->value = str;
			free(var);
			return (1);
		}
		new = new->next;
	}
	ft_add_env_var(env, envp);
	free(var);
	return (1);
}

int	export(t_data *data, t_env **env)
{
	int		i;
	char	*str;
	int		exit_s;

	i = 1;
	exit_s = 0;
	if (data->cmd[1] == NULL)
		sort_print(*env);
	while (data->cmd[i])
	{
		str = ft_strsrch(data->cmd[i], '+');
		if (!ft_isalpha(data->cmd[i][0]) && data->cmd[i][0] != '_')
			exit_s = print_error1("minishell: export:`", data->cmd[i],
					"': not a valid identifier\n");
		else if (str && str[1] == '=')
			add__env_val(data->cmd[i], env);
		else if (ft_check_str(data->cmd[i]) == 0)
			exit_s = print_error1("minishell: export:`", data->cmd[i],
					"': nont a valid identifier\n");
		else
			ft_add_env_var(data->cmd[i], env);
		i++;
	}
	return (exit_s);
}
