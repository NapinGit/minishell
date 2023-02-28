/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tools2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 17:02:42 by toueis            #+#    #+#             */
/*   Updated: 2021/11/18 17:02:43 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	fnone_tools_exit(void)
{
	perror("Minishell :");
	exit(EXIT_FAILURE);
}

static int	fnone_tools2(t_list **tmp)
{
	(*tmp)->next = (t_list *)malloc(sizeof(t_list));
	if (!(*tmp)->next)
		return (1);
	(*tmp) = (*tmp)->next;
	(*tmp)->ign = 0;
	(*tmp)->next = NULL;
	return (0);
}

static void	fnone_tools(t_obj *obj, t_list *tmp)
{
	int	i;

	i = 0;
	obj->tmp = tmp;
	while (obj->line[i] && i < (int)ft_strlen(obj->line))
	{
		while (obj->line[i] == ' ')
			i += 1;
		if (obj->line[i] == '|')
			i = i + copyc(obj->line + i, &(tmp->content));
		else if (obj->line[i] == '<' || obj->line[i] == '>')
			i = i + copyoblique(obj->line + i, &(tmp->content));
		else
			i = i + copystring(obj->line + i, &tmp, obj);
		while (obj->line[i] == ' ')
			i += 1;
		if (i < (int)ft_strlen(obj->line))
		{
			if (fnone_tools2(&tmp))
				fnone_tools_exit();
		}
	}
}

t_list	*first_cut(t_obj *obj)
{
	t_list	*list;
	t_list	*tmp;

	tmp = (t_list *)malloc(sizeof(t_list));
	if (!tmp)
	{
		perror("Minishell :");
		exit(EXIT_FAILURE);
	}
	tmp->next = NULL;
	tmp->ign = 0;
	list = tmp;
	fnone_tools(obj, list);
	return (tmp);
}
