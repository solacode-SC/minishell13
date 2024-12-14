/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_val.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:17:59 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/14 15:40:15 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_val(t_env *env, char *str)
{
	char	*s;

	s = NULL;
	if (!str)
		return (NULL);
	while (env)
	{
		if (!ft_strcmp(env->var, str))
			s = env->value;
		env = env->next;
	}
	if (s == NULL)
		return (NULL);
	s = &s[1];
	if (*s == '\0')
		return (NULL);
	return (s);
}

void	free_node(t_data *tmp)
{
	free_file(tmp->file);
	ft_free1(tmp->cmd);
	free(tmp);
}
