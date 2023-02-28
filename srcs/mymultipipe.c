/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymultipipe.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:36:59 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:37:00 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static	int	startfreenclose(t_obj *obj, int tabfd[])
{
	write(2, "minishell: Pipe Error: Too many FD opened\n", 42);
	free(tabfd);
	freelist(obj->list);
	freecmd(obj->cmd);
	free_env(obj->myenv);
	close(0);
	close(1);
	close(2);
	exit(EXIT_FAILURE);
}

static	int	start(t_obj *obj, int tabfd[])
{
	int	i;

	i = 0;
	if (obj->nbpipe > 510)
		startfreenclose(obj, tabfd);
	while (i < obj->nbpipe)
	{
		if (pipe(tabfd + i * 2) != 0)
		{
			write(2, "minishell: Pipe Error\n", 22);
			exit(EXIT_FAILURE);
		}
		i++;
	}
	return (0);
}

static void	pipemulti_exit(t_obj *obj, pid_t pid, int status, int i)
{
	int	j;

	j = 0;
	obj->act.sa_handler = SIG_IGN;
	sigaction(SIGINT, &obj->act, NULL);
	while (j < i)
	{
		if (waitpid(pid, &status, 0) == obj->lastpid)
		{
			if (WIFEXITED(status))
				obj->status = WEXITSTATUS(status);
			else if (WTERMSIG(status) == SIGPIPE)
				write(1, "\n", 1);
		}
		else
			wait(&status);
		if (WIFSIGNALED(status))
		{
			if (WTERMSIG(status) == SIGINT)
				status_sigint(obj);
		}
		j++;
	}
	obj->act.sa_handler = &myctrlsignal;
	sigaction(SIGINT, &obj->act, NULL);
}

static int	pipemulti2(pid_t *pid, t_cmd *cmd, t_obj *obj)
{
	int	i;

	i = 0;
	while (cmd)
	{
		*pid = fork();
		if (*pid < 0)
			pipemulti_error();
		if (cmd->next == NULL && *pid != 0)
			obj->lastpid = *pid;
		if (*pid == 0)
			fork_child(obj, cmd, obj->tabfd, i);
		else
		{
			cmd = cmd->next;
			i++;
		}
	}
	return (i);
}

void	pipemulti(t_cmd *cmd, t_obj *obj)
{
	int		i;
	pid_t	pid;
	int		status;

	i = 0;
	status = 0;
	obj->tabfd = (int *)malloc(sizeof(int) * obj->nbpipe * 2);
	if (!obj->tabfd || start(obj, obj->tabfd) == -1)
		return ;
	i = pipemulti2(&pid, cmd, obj);
	closefd(obj->tabfd, obj->nbpipe);
	free(obj->tabfd);
	obj->tabfd = NULL;
	pipemulti_exit(obj, pid, status, i);
}
