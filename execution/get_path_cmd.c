

#include "minishell.h"

int	ft_access(t_us_var *var, t_data *data)
{
	if (access(data->cmd[0], F_OK) != -1)
	{
		var->fd = open(data->cmd[0], O_CREAT);
		if (var->fd == -1)
		{
			printf("heree1\n");
			perror(data->cmd[0]);
			free_exit(NULL, *var, 126, data);
		}
		close(var->fd);
		if (access(data->cmd[0], X_OK) == -1)
		{
			print_error1("minishell:", data->cmd[0], "permission denied\n");
			free_exit(NULL, *var, 126, data);
		}
	}
	else
	{
		print_error1("minishell:", data->cmd[0],
			":No such file or directory\n");
		free_exit(NULL, *var, 127, data);
	}
	return (1);
}

char	*get_path_cmd(t_us_var var, t_data *data)
{
	int	i;

	i = 0;
	if (data->cmd[0][0] == '\0')
		free_exit(" :command not found\n", var, 127, data);
	if (data->cmd[0][0] == '.' && data->cmd[0][1] == '\0')
		free_exit(".: filename argument required\n", var, 2, data);
	if (ft_strsrch(data->cmd[0], '/') != 0 || var.path_spt[0] == NULL)
	{
		if (ft_access(&var, data) == 1)
			return (data->cmd[0]);
	}
	while (var.path_spt[i])
	{
		var.path_cmd = join_wih_path(var.path_spt[i++], data->cmd[0]);
		if (access(var.path_cmd, X_OK) == 0)
			return (var.path_cmd);
		free(var.path_cmd);
	}
	if (var.path_spt[i] == NULL)
	{
		write(2, data->cmd[0], ft_strlen(data->cmd[0]));
		write(2, ":command not found\n", ft_strlen(":command not found\n"));
		free_exit(NULL, var, 127, data);
	}
	return (NULL);
}
