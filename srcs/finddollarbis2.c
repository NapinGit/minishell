/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finddollarbis2.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <toueis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/23 21:39:10 by toueis            #+#    #+#             */
/*   Updated: 2021/11/23 21:39:12 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replacedollarbistools1(char *line, char *tofind, int *i)
{
	tofind[*i] = line[*i];
	*i = *i + 1;
	while (line[*i] && line[*i] != ' ' && line[*i] != '|' && \
		line[*i] != '\'' && line[*i] != '\"' && line[*i] != '$' && \
		line[*i] != '/')
	{
		if (*i == 1 && ft_isdigit(line[*i]) == 1)
		{
			tofind[*i] = line[*i];
			*i += 1;
			break ;
		}
		if (line[*i] == '?')
		{
			tofind[*i] = line[*i];
			*i += 1;
			break ;
		}	
		tofind[*i] = line[*i];
		*i += 1;
	}
	tofind[*i] = '\0';
}

static int	replacedollarbis_nfinded(char *tofind)
{
	int	i;

	i = ft_strlen(tofind);
	free(tofind);
	return (i);
}

void	reallocbuff(t_obj *obj, int len, int index)
{
	char	*tmp;
	int		i;

	i = 0;
	obj->buff[index] = 0;
	tmp = malloc(sizeof(char) * ((int)ft_strlen(obj->buff) + \
		(int)ft_strlen(obj->line) + len + 1));
	if (!tmp)
	{
		perror("Minishel ");
		exit (EXIT_FAILURE);
	}
	while (obj->buff[i])
	{
		tmp[i] = obj->buff[i];
		i++;
	}
	tmp[i] = 0;
	free(obj->buff);
	obj->buff = tmp;
}

static int	replacedollarbis_finded(char *tofind, char *finded, \
	int *j, t_obj *obj)
{
	int	i;

	i = ft_strlen(tofind);
	reallocbuff(obj, (int)ft_strlen(finded), *j);
	while (finded && finded[0] != 0)
	{
		obj->buff[*j] = finded[0];
		finded = finded + 1;
		*j = *j + 1;
	}
	obj->buff[*j] = 0;
	free(tofind);
	return (i);
}

int	replacedollarbis(char *line, int *j, t_obj *obj)
{
	char	*tofind;
	char	*finded;
	int		i;

	i = 0;
	tofind = malloc(sizeof(char) * ((int)ft_strlen(line) + 1));
	if (!tofind)
	{
		perror("Minishell :");
		exit(EXIT_FAILURE);
	}
	replacedollarbistools1(line, tofind, &i);
	if (tofind[0] == '$' && tofind[1] == '\0')
		return (replacedollarbistools2(obj, tofind, j));
	else if (tofind[0] == '$' && tofind[1] == '?')
		return (replacedollarbistools3(obj, tofind, j));
	else if (tofind[0] == '$' && tofind[1] == '0')
		return (replacedollarbistools4(obj, tofind, j));
	finded = finddollar(tofind, obj->myenv);
	if (finded != NULL)
		return (replacedollarbis_finded(tofind, finded, j, obj));
	else
		return (replacedollarbis_nfinded(tofind));
}
