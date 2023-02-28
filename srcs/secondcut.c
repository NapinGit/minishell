/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   secondcut.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:03:51 by toueis            #+#    #+#             */
/*   Updated: 2021/11/18 17:03:52 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	exit_cut(void)
{
	perror("Minishell :");
	exit(EXIT_FAILURE);
}

static void	fntwotools3(t_list **tmp, t_cmd **cmd, int *i)
{
	(*cmd)->cmdargs[*i] = (*tmp)->content;
	(*tmp) = (*tmp)->next;
	*i += 1;
}

static void	fntwotools2(t_list **tmp, t_cmd **cmd, int *i)
{
	while (((*tmp) && ft_strcmp((*tmp)->content, "|") != 0) || \
		((*tmp) && (ft_strcmp((*tmp)->content, "|") == 0 && (*tmp)->ign)))
	{
		if ((*tmp)->ign == 0 && (ft_strcmp((*tmp)->content, "<") == 0 || \
			ft_strcmp((*tmp)->content, ">") == 0))
			redirectsimple(tmp, cmd);
		else if ((*tmp)->ign == 0 && (ft_strcmp((*tmp)->content, "<<") == 0 || \
			ft_strcmp((*tmp)->content, ">>") == 0))
		{
			if (ft_strcmp((*tmp)->content, "<<") == 0)
			{
				if (redirectindouble((*tmp)->next->content, (*cmd)) == -1)
					(*tmp) = (*tmp)->next;
			}
			else
				redirectoutdouble((*tmp)->next->content, (*cmd));
			(*tmp) = (*tmp)->next;
			(*tmp) = (*tmp)->next;
		}
		else
			fntwotools3(tmp, cmd, i);
	}
}

static void	fntwotools(t_list **tmp, t_cmd **cmd, int nb)
{
	int	i;

	i = 0;
	(*cmd)->cmdargs = (char **)malloc(sizeof(char *) * (nb + 1));
	if (!(*cmd)->cmdargs)
		exit_cut();
	fntwotools2(tmp, cmd, &i);
	(*cmd)->cmdargs[i] = NULL;
	if ((*tmp) && ft_strcmp((*tmp)->content, "|") == 0 && (*tmp)->ign == 0)
	{
		(*cmd)->token = (*tmp)->content[0];
		(*tmp) = (*tmp)->next;
	}
	if ((*tmp))
		newcmd(cmd);
	else
		(*cmd)->next = NULL;
}

t_cmd	*second_cut(t_list *list)
{
	t_cmd	*cmd;
	t_cmd	*cmdtmp;
	t_list	*tmp;
	int		nb;

	tmp = list;
	nb = 0;
	while (tmp)
	{
		nb++;
		tmp = tmp->next;
	}
	tmp = list;
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
		exit_cut();
	cmd->token = 0;
	cmd->fdstdin = 0;
	cmd->fdstdout = 1;
	cmd->rin = NULL;
	cmdtmp = cmd;
	while (tmp)
		fntwotools(&tmp, &cmd, nb);
	return (cmdtmp);
}
