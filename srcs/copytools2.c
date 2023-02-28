/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copytools2.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <toueis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 21:48:32 by toueis            #+#    #+#             */
/*   Updated: 2021/11/18 21:48:34 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	copystring_tools1(char *l, t_obj *obj, int *i, int *j)
{
	obj->buff[*j] = l[*i];
	*i += 1;
	*j += 1;
}

static int	copystring_tools(char *l, t_obj *obj, int *i, t_list **tmp)
{
	int	j;

	j = 0;
	while (l[*i] && l[*i] != ' ' && l[*i] != '|' && l[*i] != '>' && \
		l[*i] != '<')
	{
		if (l[*i] == '\'')
		{
			if (copysimplequote(l, obj, i, &j))
				return (1);
			(*tmp)->ign = 1;
		}
		else if (l[*i] == '\"')
		{
			if (copydoublequote(l, i, &j, obj))
				return (1);
			(*tmp)->ign = 1;
		}
		else if (l[*i] == '$')
			*i = *i + replacedollarbis(l + *i, &j, obj);
		else
			copystring_tools1(l, obj, i, &j);
	}
	obj->buff[j] = '\0';
	return (0);
}

int	copystring(char *line, t_list **tmp, t_obj *obj)
{
	int		i;

	i = 0;
	obj->buff = (char *)malloc(sizeof(char) * ((int)ft_strlen(line) + 10));
	if (!obj->buff)
	{
		perror("Minishell ");
		exit(EXIT_FAILURE);
	}
	ft_bzero(obj->buff, (int)ft_strlen(line) + 1);
	if (copystring_tools(line, obj, &i, tmp))
		return (-1);
	(*tmp)->content = obj->buff;
	return (i);
}
