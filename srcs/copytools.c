/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copytools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:36:00 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:36:02 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	copydoublequote_exit(t_obj *obj)
{
	t_list	*lstexp;

	write(2, "minishell: Multiline not supported !\n", 37);
	lstexp = obj->tmp;
	while (lstexp->next)
		lstexp = lstexp->next;
	lstexp->content = obj->buff;
	freelist(obj->tmp);
	free_env(obj->myenv);
	close(0);
	close(1);
	close(2);
	exit (0);
}

int	copysimplequote(char *line, t_obj *obj, int *i, int *j)
{
	*i += 1;
	while (line[*i] && line[*i] != '\'')
	{
		obj->buff[*j] = line[*i];
		*i += 1;
		*j += 1;
	}
	if (line[*i] == '\'')
		*i += 1;
	else
		copydoublequote_exit(obj);
	return (0);
}

int	copydoublequote(char *line, int *i, int *j, t_obj *obj)
{
	*i += 1;
	while (line[*i] && line[*i] != '\"')
	{
		if (line[*i] == '$' && line[*i + 1] && line[*i + 1] != '"')
			*i = *i + replacedollar(line + *i, j, obj) + 1;
		else
		{
			obj->buff[*j] = line[*i];
			*i += 1;
			*j += 1;
		}
	}
	if (line[*i] != '\"')
		copydoublequote_exit(obj);
	*i += 1;
	return (0);
}

int	copyc(char *line, char **content)
{
	char	buff[2];

	buff[0] = line[0];
	buff[1] = '\0';
	*content = ft_strdup(buff);
	return (1);
}

int	copyoblique(char *line, char **content)
{
	char	buff[3];

	buff[0] = line[0];
	if (line[1] == buff[0])
	{
		buff[1] = line[1];
		buff[2] = '\0';
		*content = ft_strdup(buff);
		return (2);
	}
	buff[1] = '\0';
	*content = ft_strdup(buff);
	return (1);
}
