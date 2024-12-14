/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_export.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/12 15:36:32 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/12 15:36:35 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_listenv(t_env *env)
{
	int	i;

	i = 0;
	while (env)
	{
		i++;
		env = env->next;
	}
	return (i);
}

void	ft_print(t_env *s1)
{
	if (s1->var && !s1->egnor && ft_strcmp(s1->var, "_"))
	{
		printf("declare -x ");
		printf("%s", s1->var);
		if (s1->value)
		{
			printf("%c", s1->value[0]);
			printf("\"%s\"\n", &s1->value[1]);
		}
		else
			printf("\n");
	}
}

void	sort_print(t_env *env)
{
	int		n;
	t_env	*tmp;
	char	*str;
	t_env	*s1;

	str = NULL;
	n = count_listenv(env);
	while (n > 0)
	{
		tmp = env;
		s1 = tmp;
		while (tmp)
		{
			if (ft_strcmp(s1->var, str) <= 0)
				s1 = tmp;
			else if (ft_strcmp(s1->var, tmp->var) > 0 && ft_strcmp(tmp->var,
					str) > 0)
				s1 = tmp;
			tmp = tmp->next;
		}
		str = s1->var;
		ft_print(s1);
		n--;
	}
}
