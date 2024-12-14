/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:17:12 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/14 16:01:47 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g_var;

void	handle_ctrl_c(int sig)
{
	(void)sig;
	printf("\n");
	g_var.exit_s = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}

void	f(int sig)
{
	(void)sig;
	free_data(g_var.data);
	free_envp(g_var.env);
	clear_history();
	exit(130);
}

void	child_handler(int signum)
{
	(void)signum;
	exit(130);
}

void	child_handler1(int signum)
{
	(void)signum;
	exit(131);
}
