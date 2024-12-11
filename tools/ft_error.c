/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:53:18 by soel-mou          #+#    #+#             */
/*   Updated: 2024/12/11 19:55:59 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern t_global	g;

int	syntax_error1(t_lexer *lexer)
{
	while (lexer->next)
	{
		if (lexer->type == PI_PE && (lexer->prev == NULL
				|| ft_strlen(lexer->data) > 1))
			return (1);
		else if (lexer->type != WO_RD && ft_strlen(lexer->data) > 2)
			return (1);
		lexer = lexer->next;
		if (lexer->type != WO_RD && lexer->prev->type != WO_RD
			&& lexer->prev->type != PI_PE)
			return (1);
		if (lexer->type == PI_PE && lexer->prev->type != WO_RD)
			return (1);
	}
	if (lexer->type != WO_RD && ft_strlen(lexer->data) >= 2)
		return (1);
	else if (lexer->type != WO_RD)
		return (1);
	return (0);
}

int	syntax_error(t_lexer **lexer)
{
	int	n;

	if (*lexer == NULL)
		return (0);
	n = syntax_error1(*lexer);
	if (n != 0)
	{
		free_lexer(*lexer);
		*lexer = NULL;
		printf("syntax error\n");
		return (1);
	}
	return (0);
}
