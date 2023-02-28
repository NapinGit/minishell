/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:37:46 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:37:47 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	newcmd(t_cmd **cmd)
{
	(*cmd)->next = (t_cmd *)malloc(sizeof(t_cmd));
	if (!(*cmd)->next)
	{
		perror("Minishell :");
		exit(EXIT_FAILURE);
	}
	(*cmd) = (*cmd)->next;
	(*cmd)->token = 0;
	(*cmd)->fdstdin = 0;
	(*cmd)->fdstdout = 1;
	(*cmd)->rin = NULL;
}

void	redirectsimple(t_list **tmp, t_cmd **cmd)
{
	if (ft_strcmp((*tmp)->content, "<") == 0 && \
		ft_strcmp((*tmp)->next->content, ">") == 0)
	{
		redirectinspe((*tmp)->next->content, (*cmd));
		(*tmp) = (*tmp)->next;
	}
	else if (ft_strcmp((*tmp)->content, "<") == 0)
		redirectin((*tmp)->next->content, (*cmd));
	else
		redirectout((*tmp)->next->content, (*cmd));
	(*tmp) = (*tmp)->next;
	(*tmp) = (*tmp)->next;
}
