/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finddollar2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <toueis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/18 22:00:19 by toueis            #+#    #+#             */
/*   Updated: 2021/11/18 22:00:21 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	replacedollar_tools1(char *line, char *tofind)
{
	int	i;

	i = 0;
	tofind[i] = line[i];
	i++;
	while (line[i] && line[i] != ' ' && line[i] != '|' \
		&& line[i] != '\'' && line[i] != '\"' && line[i] != '$' \
		&& line[i] != '/')
	{
		if (i == 1 && ft_isdigit(line[i]) == 1)
		{
			tofind[i] = line[i];
			i++;
			break ;
		}
		if (line[i] == '?')
		{
			tofind[i] = line[i];
			i++;
			break ;
		}	
		tofind[i] = line[i];
		i++;
	}
	tofind[i] = '\0';
}

int	replacedollar_tools2(char *tofind, char *buff, int *j)
{
	buff[*j] = tofind[0];
	*j = *j + 1;
	buff[*j] = 0;
	free(tofind);
	return (1);
}

int	replacedollar_tools3(t_obj *obj, char *tofind, char *buff, int *j)
{
	int		i;
	char	*str;

	str = ft_itoa(obj->status);
	i = 0;
	while (str[i])
	{
		buff[*j] = str[i];
		*j = *j + 1;
		i++;
	}
	buff[*j] = 0;
	i = (int)ft_strlen(tofind);
	free(tofind);
	free(str);
	return (i - 1);
}

int	replacedollar_tools4(char *tofind, char *buff, int *j)
{
	char	*str2;
	int		i;

	str2 = ft_strdup("minishell");
	i = 0;
	while (str2[i])
	{
		buff[*j] = str2[i];
		*j = *j + 1;
		i++;
	}
	buff[*j] = 0;
	i = (int)ft_strlen(tofind);
	free(tofind);
	free(str2);
	return (i - 1);
}
