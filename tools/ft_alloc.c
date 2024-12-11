/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_alloc.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:53:43 by soel-mou          #+#    #+#             */
/*   Updated: 2024/12/11 20:58:57 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*p;

	if (count != 0 && size > SIZE_MAX / count)
		return (0);
	p = malloc(count * size);
	if (p == NULL)
		return (NULL);
	ft_memset(p, 0, count * size);
	return (p);
}

char	*ft_strdup(char *str)
{
	int		i;
	char	*cp;

	i = 0;
	if (str == NULL)
		return (NULL);
	cp = malloc(ft_strlen(str) + 1);
	if (cp == NULL)
		return (NULL);
	while (str[i])
	{
		cp[i] = str[i];
		i++;
	}
	cp[i] = '\0';
	return (cp);
}

char	*skip_char(char *s, char c)
{
	int		n;
	char	*str;

	n = 0;
	while (s[n] && s[n] != c)
		n++;
	str = ft_calloc(sizeof(char), n + 1);
	if (!str)
		return (NULL);
	ft_strncpy(str, s, n);
	return (str);
}

char	*ft_strjoinn(char *s1, char *ss2)
{
	int		i;
	int		j;
	char	*result;

	if (!s1 && !ss2)
		return (NULL);
	if (!s1)
	{
		result = ft_strdup(ss2);
		return (result);
	}
	if (!ss2)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(ss2);
	result = ((char *)malloc(i + j + 1));
	if (!result)
		return (NULL);
	ft_memcpy(result, s1, i);
	ft_memcpy(result + i, ss2, j);
	result[i + j] = '\0';
	return (result);
}

void	*ft_memcpy(void *dest, const void *src, size_t size)
{
	size_t				i;
	unsigned char		*d;
	const unsigned char	*s;

	if (dest == NULL && src == NULL)
		return (0);
	if (dest == src)
		return (dest);
	i = 0;
	d = (unsigned char *)dest;
	s = (unsigned char *)src;
	while (i < size)
	{
		d[i] = s[i];
		i++;
	}
	return (dest);
}
