/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:53:53 by soel-mou          #+#    #+#             */
/*   Updated: 2024/12/11 21:11:23 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g;

void	handle_signal1(int sig)
{
	(void)sig;
	write(1, "\n", 1);
	g.exit_s = 130;
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	return ;
}
