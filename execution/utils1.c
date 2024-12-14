/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils1.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:25:49 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/14 15:40:43 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin(char *s1, char *s2)
{
	int		i;
	int		j;
	char	*join;

	if (!s1 && !s2)
		return (NULL);
	if (!s1)
	{
		join = ft_strdup(s2);
		return (join);
	}
	if (!s2)
		return (ft_strdup(s1));
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	join = ((char *)malloc(i + j + 1));
	if (!join)
		return (NULL);
	ft_memcpy(join, s1, i);
	ft_memcpy(join + i, s2, j);
	join[i + j] = '\0';
	return (join);
}

int	print_error1(char *s1, char *s2, char *s3)
{
	ft_putstr(s1);
	ft_putstr(s2);
	ft_putstr(s3);
	return (1);
}

int	print_error2(char *s1, char s2, char *s3)
{
	ft_putstr(s1);
	write(2, &s2, 1);
	ft_putstr(s3);
	return (2);
}

void	*ft_memset(void *ptr, int c, size_t s)
{
	size_t			n;
	unsigned char	*str;

	str = (unsigned char *)ptr;
	n = 0;
	while (n < s)
	{
		str[n] = (unsigned char)c;
		n++;
	}
	return (ptr);
}

char	*join_wih_path(char *s1, char *s2)
{
	char	*s;
	size_t	i;
	size_t	j;

	if (s1 == NULL && s2 == NULL)
		return (0);
	if (!s1)
		return ((char *)s2);
	i = ft_strlen(s1);
	j = ft_strlen(s2);
	s = malloc(sizeof(char) * (i + j + 2));
	if (s == NULL)
		return (0);
	ft_memcpy(s, s1, i);
	s[i++] = '/';
	ft_memcpy(s + i, s2, j);
	s[j + i] = '\0';
	return (s);
}
