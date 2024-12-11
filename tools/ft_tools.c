/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tools.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:53:58 by soel-mou          #+#    #+#             */
/*   Updated: 2024/12/11 21:00:45 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_copy(char **cmd, char **str)
{
	int	i;

	i = 0;
	while (str && str[i])
	{
		cmd[i] = ft_strdup(str[i]);
		i++;
	}
	return (i);
}

int	count_list(t_data *data)
{
	int	cont;

	cont = 0;
	while (data)
	{
		cont++;
		data = data->next;
	}
	return (cont);
}

char	**ft_addstring(char **str, t_lexer *lexer, t_env *envp)
{
	int		cont;
	t_var	var;

	var.j = 0;
	var.i = 0;
	if (str && !ft_strcmp(str[0], "export"))
		var.newstr = ft_expending_word(lexer->data, envp, 0);
	else
		var.newstr = ft_expending_word(lexer->data, envp, 1);
	cont = count_str(str) + count_str(var.newstr);
	var.cmd = ft_calloc(sizeof(char *), cont + 1);
	if (var.cmd == NULL)
		return (NULL);
	var.i = ft_copy(var.cmd, str);
	ft_copy(&var.cmd[var.i], var.newstr);
	ft_free1(str);
	ft_free1(var.newstr);
	return (var.cmd);
}

static int	cont_w(const char *str, char c)
{
	int	i;
	int	count;

	i = 0;
	if (!str)
		return (0);
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] != c && str[i] != '\t')
		{
			count++;
			while (str[i] != '\0' && str[i] != c && str[i] != '\t')
				i++;
		}
		else if (str[i] == c || str[i] == '\t')
			i++;
	}
	return (count);
}

char	**ft_split(char *s, char c)
{
	char	**p;
	int		i;
	int		j;
	int		n;

	n = 0;
	i = 0;
	p = (char **)malloc((cont_w(s, c) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	while (s != NULL && s[i] != '\0')
	{
		while (s[i] == c || s[i] == '\t')
			i++;
		if (s[i] == '\0')
			break ;
		j = 0;
		while (s[i] != c && s[i] != '\t' && s[i] != '\0' && j++ >= 0)
			i++;
		p[n++] = ft_substr(s, i - j, j);
	}
	p[n] = NULL;
	return (p);
}
