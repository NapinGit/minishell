/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parseerror.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:37:17 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:37:18 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	parse_return(char *content, int mode)
{
	if (mode == 0)
		print_error(NULL, content, "syntax error near unexpected token");
	else
		print_error(NULL, content, \
			"syntax error near unexpected token `newline");
	return (2);
}

int	parse_error(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	if (tmp && tmp->content[0] == '|')
		return (parse_return(tmp->content, 0));
	while (tmp)
	{
		if (tmp->ign == 1)
			NULL;
		else if ((tmp->content[0] == '|' && tmp->next == NULL) \
				|| ((tmp->content[0] == '<' || tmp->content[0] == '>') \
				&& tmp->next == NULL))
			return (parse_return(tmp->content, 1));
		else if (tmp->content[0] == '<' && tmp->next->content[0] == '>')
			NULL;
		else if ((tmp->content[0] == '<' || tmp->content[0] == '>') && \
			(tmp->next->content[0] == '<' || tmp->next->content[0] == '>' || \
				tmp->next->content[0] == '|'))
			return (parse_return(tmp->next->content, 0));
		else if (tmp->content[0] == '|' && tmp->next->content[0] == '|')
			return (parse_return(tmp->content, 0));
		tmp = tmp->next;
	}
	return (0);
}
