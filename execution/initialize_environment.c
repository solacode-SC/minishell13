/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   initialize_environment.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: iait-bou <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/11 19:14:46 by iait-bou          #+#    #+#             */
/*   Updated: 2024/12/11 19:14:50 by iait-bou         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_shell_level(t_env *envp)
{
	char	*level_value;
	int		shell_level;

	while (envp)
	{
		if (!ft_strcmp(envp->var, "SHLVL"))
		{
			shell_level = ft_atoi(&envp->value[1]) + 1;
			if (shell_level >= 1000)
			{
				printf("warning: shell level (%d) too high\n", shell_level);
				shell_level = 1;
			}
			free(envp->value);
			level_value = ft_itoa(shell_level);
			envp->value = ft_strjoin("=", level_value);
			free(level_value);
			return ;
		}
		envp = envp->next;
	}
	ft_add_env_var("SHLVL=1", &envp);
}

void	add_default_path(t_env **envp)
{
	t_env	*new_node;

	new_node = ft_calloc(sizeof(t_env), 1);
	if (new_node == NULL)
		return ;
	new_node->var = ft_strdup("PATH");
	new_node->value = ft_strdup("/usr/local/sbin:/usr/local/bin:/usr/sbin:/usr/bin:/sbin:/bin");
	new_node->egnor = 1;
	ft_add_node_to_env_list(envp, new_node);
}

void	initialize_environment(char **env, t_env **envp)
{
	int		i;
	char	*cwd;
	char	*env_var;

	i = -1;
	*envp = ft_calloc(sizeof(t_env), 1);
	if (*envp == NULL)
		return ;
	if (*env == NULL)
	{
		cwd = getcwd(NULL, 0);
		add_default_path(envp);
		env_var = ft_strjoin("PWD=", cwd);
		ft_add_env_var(env_var, envp);
		free(env_var);
		free(cwd);
		ft_add_env_var("SHLVL=1", envp);
		ft_add_env_var("OLDPWD", envp);
		ft_add_env_var("_=/usr/bin/env", envp);
		return ;
	}
	while (env[++i])
		ft_add_env_var(env[i], envp);
	update_shell_level(*envp);
}

void	ft_add_node_to_env_list(t_env **env, t_env *new_node)
{
	t_env	*tmp;

	if (!env || !new_node)
		return ;
	if (*env)
	{
		tmp = *env;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new_node;
	}
	else
		*env = new_node;
}

char	*ft_extract_variable_name(char *str)
{
	int		i;
	char	*var_name;
	int		len;

	i = 0;
	len = 0;
	while (str[len] && str[len] != '=' && str[len] != '+')
		len++;
	var_name = ft_calloc(sizeof(char), len + 1);
	if (var_name == NULL)
		return (NULL);
	len = 0;
	while (str[i] && str[i] != '=')
	{
		if (str[i] != '+')
			var_name[len++] = str[i];
		i++;
	}
	var_name[len] = '\0';
	return (var_name);
}

int	update_existing_variable(char *var, char *value, t_env *envp)
{
	while (envp)
	{
		if (!ft_strcmp(envp->var, var))
		{
			if (ft_strchr(value, '='))
			{
				if (envp->value)
					free(envp->value);
				envp->value = value;
				envp->egnor = 0;
			}
			free(var);
			return (1);
		}
		envp = envp->next;
	}
	return (0);
}

void	ft_add_env_var(char *env_var, t_env **envp)
{
	char	*value;
	char	*var_name;
	t_env	*new_env;

	var_name = ft_extract_variable_name(env_var);
	value = ft_strsrch(env_var, '=');
	if (value)
		value = ft_strdup(value);
	if (update_existing_variable(var_name, value, *envp))
		return ;
	else
	{
		new_env = ft_calloc(sizeof(t_env), 1);
		if (!new_env)
			return ;
		new_env->value = value;
		new_env->var = var_name;
		ft_add_node_to_env_list(envp, new_env);
	}
}
