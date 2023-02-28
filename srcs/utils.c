/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <toueis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:47:49 by toueis            #+#    #+#             */
/*   Updated: 2021/11/12 10:47:50 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

unsigned long	ft_strlen_char(const char *str, char c)
{
	unsigned long	i;

	i = 0;
	while (str[i] && str[i] != c)
		i++;
	return (i);
}

void	exec_bin_unique(t_cmd *cmd, char **envp, t_obj *obj)
{
	pid_t	pid;
	int		status;

	if (access(cmd->cmdargs[0], F_OK) == -1)
	{
		print_error(NULL, cmd->cmdargs[0], "No such file or directory");
		return ;
	}
	pid = fork();
	if (pid == 0)
	{
		changefdrd(cmd);
		if (execve(cmd->cmdargs[0], cmd->cmdargs, envp) == -1)
			print_error(NULL, cmd->cmdargs[0], "Is a directory");
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		printf("Fork failed to create a new process.\n");
		return ;
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		obj->status = WEXITSTATUS(status);
}

void	free_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		free(envp[i]);
		i++;
	}
	free(envp[i]);
	free(envp);
}

void	print_error(char *builtin, char *cmd, char *msg_error)
{
	write(2, "minishell: ", 11);
	write(2, builtin, ft_strlen(builtin));
	write(2, cmd, ft_strlen(cmd));
	write(2, ": ", 2);
	write(2, msg_error, ft_strlen(msg_error));
	write(2, "\n", 1);
}
