/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strs.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:53:35 by soel-mou          #+#    #+#             */
/*   Updated: 2024/12/11 21:00:56 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*ft_sub(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	int		i;
	int		j;

	i = start;
	j = 0;
	ptr = malloc((len + 1) * sizeof(char));
	if (!ptr)
		return (NULL);
	while (s[i] != '\0' && len > 0)
	{
		ptr[j] = s[i];
		i++;
		j++;
		len--;
	}
	ptr[j] = '\0';
	return (ptr);
}

char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*ptr;
	size_t	j;
	size_t	lens;

	j = 0;
	lens = 0;
	if (!s)
		return (NULL);
	while (s[lens])
		lens++;
	if (len > lens - start)
		len = lens - start;
	if (lens <= start)
	{
		ptr = malloc(1 * sizeof(char));
		if (!ptr)
			return (NULL);
		ptr[j] = '\0';
		return (ptr);
	}
	ptr = ft_sub(s, start, len);
	return (ptr);
}

int	ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s && s[i])
	{
		if (s[i] == (unsigned char)c)
			return (1);
		i++;
	}
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	if (!s1 || !s2)
		return (1);
	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}

char	*ft_itoa(int nb)
{
	int		i;
	char	*p;
	long	b;

	b = nb;
	i = ft_len(b);
	p = malloc(i + 1);
	if (p == NULL)
		return (0);
	p[i] = '\0';
	if (b < 0)
	{
		p[0] = '-';
		b *= (-1);
	}
	if (b == 0)
		p[i - 1] = 48;
	while (b > 0)
	{
		p[i - 1] = (b % 10) + '0';
		i--;
		b /= 10;
	}
	return (p);
}
