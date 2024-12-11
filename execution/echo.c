/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:15:41 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/11 19:15:45 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_newline(t_data *data, int *i)
{
	int	j;
	int	found_flag;

	found_flag = 0;
	while (data->cmd[*i] && data->cmd[*i][0] == '-' && data->cmd[*i][1] == 'n')
	{
		j = 1;
		while (data->cmd[*i][j] == 'n')
			j++;
		if (data->cmd[*i][j] == '\0')
		{
			found_flag = 1;
			(*i)++;
		}
		else
			break ;
	}
	if (found_flag)
		return (0);
	else
		return (1);
}

int	echo(t_data *data)
{
	int	i;
	int	newline;

	i = 1;
	newline = check_newline(data, &i);
	while (data->cmd[i])
	{
		write(1, data->cmd[i], ft_strlen(data->cmd[i]));
		if (data->cmd[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (newline)
		printf("\n");
	return (0);
}
