/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: soel-mou <soel-mou@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:54:02 by soel-mou          #+#    #+#             */
/*   Updated: 2024/12/11 20:43:49 by soel-mou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_global	g;

int	check_quote(char *str)
{
	int	i;
	int	sinqot;
	int	dbqot;

	i = 0;
	sinqot = 1;
	dbqot = 1;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && sinqot == 1)
			dbqot *= (-1);
		if (str[i] == '\'' && dbqot == 1)
			sinqot *= (-1);
		i++;
	}
	if (dbqot == -1 || sinqot == -1)
		return (0);
	return (1);
}

int	ft_token(char c, int *singl, int *doubl)
{
	if (c == '\'' && *doubl != -1)
		*singl *= -1;
	if (c == '\"' && *singl != -1)
		*doubl *= -1;
	if (ft_strsrch("\t\v\n ", c) && (*singl != -1 && *doubl != -1))
		return (0);
	else
		return (1);
}

void	chang_status(t_env *envp)
{
	if (g.exit_s != 0)
	{
		envp->exit = g.exit_s;
		g.exit_s = 0;
	}
}

int	ft_minishell(t_data *data, t_env **envp, char *len)
{
	t_lexer	*lexer;

	if (len == NULL)
		return (1);
	chang_status(*envp);
	(*envp)->env = get_envp(*envp, (*envp)->env);
	add_history(len);
	if (!check_quote(len))
	{
		write(2, "syntax error\n", ft_strlen("syntax error\n"));
		free(len);
	}
	else
	{
		lexer = NULL;
		ft_lexer(len, &lexer);
		data = ft_parsing(lexer, *envp);
		free(len);
		run_cmd(&data, (*envp)->env, envp);
		free_data(data);
	}
	return (0);
}

int	main(int ac, char **av, char **env)
{
	t_data	*data;
	char	*len;
	t_env	*envp;

	envp = NULL;
	data = NULL;
	if (ac > 1 || !av)
	{
		print_error1("minishell: ", av[1], ": No such file or directory");
		exit(127);
	}
	initialize_environment(env, &envp);
	signal(SIGINT, handle_CTRL_C);
	signal(SIGQUIT, SIG_IGN);
	while (1)
	{
		len = readline("minishell $ ");
		if (ft_minishell(data, &envp, len))
			break ;
	}
	g.exit_s = envp->exit;
	free_envp(envp);
	rl_clear_history();
	printf("exit\n");
	exit(g.exit_s);
}
