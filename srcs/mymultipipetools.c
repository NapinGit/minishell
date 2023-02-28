/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mymultipipetools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 16:42:14 by toueis            #+#    #+#             */
/*   Updated: 2021/11/18 16:42:16 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	closefd(int tabfd[], int nbpipe)
{
	int	i;

	i = 0;
	while (i < nbpipe * 2)
	{
		close(tabfd[i]);
		i++;
	}
}

static void	fork_child_first(t_obj *obj, t_cmd *cmd, int *tabfd)
{
	dup2(tabfd[1], 1);
	closefd(tabfd, obj->nbpipe);
	exec_buitin(obj, cmd);
	free(obj->tabfd);
	obj->tabfd = NULL;
	freecmd(obj->cmd);
	freelist(obj->list);
	free_env(obj->myenv);
	close(0);
	close(1);
	close(2);
	exit(obj->status);
}

static void	fork_child_last(t_obj *obj, t_cmd *cmd, int *tabfd, int i)
{
	dup2(tabfd[(i - 1) * 2], 0);
	closefd(tabfd, obj->nbpipe);
	exec_buitin(obj, cmd);
	free(obj->tabfd);
	obj->tabfd = NULL;
	freecmd(obj->cmd);
	freelist(obj->list);
	free_env(obj->myenv);
	close(0);
	close(1);
	close(2);
	exit(obj->status);
}

void	pipemulti_error(void)
{
	write(2, "minishell: fork error\n", 22);
	exit(EXIT_FAILURE);
}

void	fork_child(t_obj *obj, t_cmd *cmd, int *tabfd, int i)
{
	if (i == 0)
		fork_child_first(obj, cmd, tabfd);
	else if (cmd->next == NULL)
		fork_child_last(obj, cmd, tabfd, i);
	else
	{
		dup2(tabfd[(i - 1) * 2], 0);
		dup2(tabfd[i * 2 + 1], 1);
		closefd(tabfd, obj->nbpipe);
		exec_buitin(obj, cmd);
		free(obj->tabfd);
		obj->tabfd = NULL;
		freecmd(obj->cmd);
		freelist(obj->list);
		free_env(obj->myenv);
		close(0);
		close(1);
		close(2);
		exit(obj->status);
	}
}
