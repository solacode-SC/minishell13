/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_helper.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:53:48 by soel-mou          #+#    #+#             */
/*   Updated: 2024/12/11 21:01:24 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*apend_char_str(char *str, char c)
{
	int		i;
	char	*new;

	i = ft_strlen(str);
	new = malloc(i + 2);
	if (!new)
		return (NULL);
	i = 0;
	while (str && str[i])
	{
		new[i] = str[i];
		i++;
	}
	new[i++] = c;
	new[i] = '\0';
	if (str)
		free(str);
	return (new);
}

static int	cont_w1(const char *str)
{
	int	i;
	int	count;

	i = 0;
	if (!str)
		return (0);
	count = 0;
	while (str[i] != '\0')
	{
		if (!is_whitespace(str[i]))
		{
			count++;
			while (str[i] != '\0' && !is_whitespace(str[i]))
				i++;
		}
		else if (is_whitespace(str[i]))
			i++;
	}
	return (count);
}

int	ft_len(long nb)
{
	int	i;

	i = 0;
	if (nb < 0)
	{
		nb *= -1;
		i++;
	}
	else if (nb == 0)
		i++;
	while (nb >= 1)
	{
		nb = nb / 10;
		i++;
	}
	return (i);
}

char	**ft_split_it(char *str)
{
	char	**p;
	int		i;
	int		j;
	int		n;

	n = 0;
	i = 0;
	p = (char **)malloc((cont_w1(str) + 1) * sizeof(char *));
	if (!p)
		return (NULL);
	while (str != NULL && str[i] != '\0')
	{
		while (is_whitespace(str[i]))
			i++;
		if (str[i] == '\0')
			break ;
		j = 0;
		while (!is_whitespace(str[i]) && str[i] != '\0' && j++ >= 0)
			i++;
		p[n++] = ft_substr(str, i - j, j);
	}
	p[n] = NULL;
	return (p);
}
