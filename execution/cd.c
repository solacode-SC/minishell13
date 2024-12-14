/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:14:12 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/11 19:14:18 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_no_argument(t_env *env, char *tmp)
{
	char	*newpwd;
	char	*oldpwd;
	char	*home;

	home = get_val(env, "HOME");
	if (home != NULL)
	{
		if (chdir(home) != 0)
		{
			write(2, "minshell: cd: ", 10);
			perror(NULL);
			return ;
		}
		newpwd = ft_strjoin("PWD=", home);
		oldpwd = ft_strjoin("OLDPWD=", tmp);
		ft_add_env_var(oldpwd, &env);
		ft_add_env_var(newpwd, &env);
		free(newpwd);
		free(oldpwd);
		if (env->pwd)
			free(env->pwd);
		env->pwd = ft_strdup(home);
	}
	else
		write(2, "minishell: cd: HOME not set\n", 23);
}

void	change_and_free(char *oldpwd, char *newpwd, char *str, t_env *env)
{
	ft_add_env_var(oldpwd, &env);
	ft_add_env_var(newpwd, &env);
	free(newpwd);
	free(oldpwd);
	if (env->pwd)
		free(env->pwd);
	env->pwd = str;
}

int	handle_change_directory(t_data *data, t_env *env, char *tmp)
{
	char	*newpwd;
	char	*oldpwd;
	char	*str;

	if (data->cmd[1][0] == '\0')
		return (0);
	if (chdir(data->cmd[1]) != 0)
	{
		perror(data->cmd[1]);
		return (1);
	}
	else
	{
		str = getcwd(NULL, 0);
		if (!str)
		{
			perror("getcwd : ");
			return (0);
		}
		newpwd = ft_strjoin("PWD=", str);
		oldpwd = ft_strjoin("OLDPWD=", tmp);
		change_and_free(oldpwd, newpwd, str, env);
	}
	return (0);
}

int	cd(t_data *data, t_env *env)
{
	char	*tmp;

	tmp = get_val(env, "PWD");
	if (data->cmd[1] == NULL)
	{
		handle_no_argument(env, tmp);
		return (1);
	}
	if (data->cmd[2] != NULL)
	{
		write(2, "minishell: cd: too many arguments\n",
			ft_strlen("minishell: cd: too many arguments\n"));
		return (1);
	}
	if (handle_change_directory(data, env, tmp))
		return (1);
	return (0);
}
