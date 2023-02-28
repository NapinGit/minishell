/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:34:55 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:34:59 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	*join_path(t_cmd *cmd, char *path)
{
	char	*bin;
	char	*tmp;

	bin = NULL;
	tmp = NULL;
	tmp = ft_strjoin(path, "/");
	if (tmp == NULL)
		return (NULL);
	bin = ft_strjoin(tmp, cmd->cmdargs[0]);
	if (bin == NULL)
		return (NULL);
	free(tmp);
	return (bin);
}

static void	exec_bin(t_cmd *cmd, char **envp, char *path, t_obj *obj)
{
	pid_t	pid;
	int		status;
	char	*bin;

	bin = join_path(cmd, path);
	pid = fork();
	status = 0;
	if (pid == 0)
		fork_child_exec_bin(obj, cmd, bin, envp);
	else if (pid < 0)
	{
		write(2, "minishell: Fork failed to create a new process.\n", 48);
		return ;
	}
	else
		fork_father_exec_bin(obj, pid, &status);
	if (WIFEXITED(status))
		obj->status = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
		if (WTERMSIG(status) == SIGINT)
			obj->status = 130;
	free(bin);
}

int	get_bin(t_cmd *cmd, char **envp, char *path, t_obj *obj)
{
	DIR				*dir;
	struct dirent	*sd;

	dir = opendir(path);
	if (dir == NULL)
		return (0);
	while (1)
	{
		sd = readdir(dir);
		if (sd == NULL)
			break ;
		if (ft_strcmp(cmd->cmdargs[0], sd->d_name) == 0)
		{
			exec_bin(cmd, envp, path, obj);
			closedir(dir);
			return (1);
		}
	}
	closedir(dir);
	return (0);
}

static int	get_path_2(t_cmd *cmd, t_obj *obj, char *stock)
{
	if (stock == NULL)
	{
		if (access(cmd->cmdargs[0], F_OK) != -1)
		{
			exec_bin_unique(cmd, obj->myenv, obj);
			return (0);
		}
		print_error(NULL, cmd->cmdargs[0], "command not found");
		obj->status = 127;
		return (0);
	}
	return (1);
}

void	get_path(t_cmd *cmd, char **envp, t_obj *obj)
{
	char	*stock;
	char	*path;
	int		len_stock;
	int		len;

	len_stock = 0;
	stock = dollard("PATH", envp);
	if (get_path_2(cmd, obj, stock) == 0)
		return ;
	len = ft_strlen(stock);
	while (len_stock < len)
	{
		len_stock = len_stock + ft_strlen_char(stock, ':') + 1;
		path = ft_strndup(stock, ft_strlen_char(stock, ':'));
		if (get_bin(cmd, envp, path, obj) == 1)
		{
			free(path);
			return ;
		}
		stock = stock + ft_strlen_char(stock, ':') + 1;
		free(path);
	}
	print_error (NULL, cmd->cmdargs[0], "command not found");
	obj->status = 127;
}
