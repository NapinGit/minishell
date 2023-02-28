/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin_local.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <toueis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:44:40 by toueis            #+#    #+#             */
/*   Updated: 2021/11/12 10:46:59 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	fork_child_local(t_cmd *cmd, t_obj *obj, char **newenv)
{
	obj->act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &obj->act, NULL);
	changefdrd(cmd);
	if (execve(cmd->cmdargs[0], cmd->cmdargs, newenv) == -1)
		print_error(NULL, cmd->cmdargs[0], "No such file or directory");
	free_env(obj->myenv);
	free_env(newenv);
	freecmd(obj->cmd);
	freelist(obj->list);
	close(0);
	close(1);
	close(2);
	exit(EXIT_FAILURE);
}

char	**create_newenv(char **envp, char *path)
{
	int		i;
	char	**new_env;
	char	**out;

	i = 0;
	new_env = NULL;
	out = NULL;
	while (envp[i])
		i++;
	new_env = malloc(sizeof(char *) * (i + 1));
	if (new_env == NULL)
	{
		write(2, "minishell: l'allocation de mémoire de", 37);
		write(2, " l'environnement a échoué\n", 26);
		return (NULL);
	}
	i = 0;
	while (envp[i])
	{
		new_env[i] = ft_strdup(envp[i]);
		i++;
	}
	new_env[i] = NULL;
	out = add_executable(new_env, path);
	return (out);
}

static int	exec_bin_local_2(t_cmd *cmd)
{
	if (access(cmd->cmdargs[0], 0) == -1)
	{
		print_error(NULL, cmd->cmdargs[0], "No such file or directory");
		return (0);
	}
	return (1);
}

void	fork_father(t_obj *obj, pid_t pid, int *status)
{
	obj->act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &obj->act, NULL);
	waitpid(pid, status, 0);
	obj->act.sa_handler = &myctrlsignal;
	sigaction(SIGINT, &obj->act, NULL);
}

void	exec_bin_local(t_cmd *cmd, t_obj *obj)
{
	pid_t	pid;
	int		status;
	char	**newenv;

	if (exec_bin_local_2(cmd) == 0)
		return ;
	status = 0;
	newenv = create_newenv(obj->myenv, cmd->cmdargs[0]);
	pid = fork();
	if (pid == 0)
		fork_child_local(cmd, obj, newenv);
	else if (pid < 0)
	{
		write(2, "minishell: Fork failed to create a new process.\n", 48);
		return ;
	}
	else
		fork_father(obj, pid, &status);
	if (WIFEXITED(status))
		obj->status = WEXITSTATUS(status);
	free_env(newenv);
}
