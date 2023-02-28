/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bin2.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:34:55 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:34:59 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	status_sigint(t_obj *obj)
{
	write(1, "\n", 1);
	obj->status = 130;
}

void	fork_father_exec_bin(t_obj *obj, pid_t pid, int *status)
{
	obj->act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &obj->act, NULL);
	waitpid(pid, status, 0);
	obj->act.sa_handler = &myctrlsignal;
	sigaction(SIGINT, &obj->act, NULL);
}

void	fork_child_exec_bin(t_obj *obj, t_cmd *cmd, char *bin, char **envp)
{
	obj->act.sa_handler = SIG_DFL;
	sigaction(SIGINT, &obj->act, NULL);
	changefdrd(cmd);
	if (execve(bin, cmd->cmdargs, envp) == -1)
		print_error(NULL, bin, "execve error");
	freecmd(cmd);
	free_env(obj->myenv);
	exit(EXIT_FAILURE);
}
