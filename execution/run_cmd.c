/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   run_cmd.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:18:21 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/14 16:00:32 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_var;

int	count_cmd(t_data *data)
{
	int	c;

	c = 0;
	while (data)
	{
		c++;
		data = data->next;
	}
	return (c);
}

void	run_cmd(t_data **data, char **env, t_env **envp)
{
	int	nb_cmd;

	if (!*data)
		return ;
	g_var.data = *data;
	g_var.env = *envp;
	g_var.var = NULL;
	g_var.flg = 0;
	nb_cmd = count_cmd(*data);
	signal(SIGINT, SIG_IGN);
	if (heredoc(*data, *envp))
	{
		close_herdoc(*data);
		(*envp)->exit = 130;
		return ;
	}
	if (data)
	{
		if (nb_cmd == 1)
			run_one_cmd(*data, env, envp);
		else
			run_cmd_with_pipe(data, env, envp);
		signal(SIGINT, handle_ctrl_c);
		close_herdoc(*data);
	}
}
