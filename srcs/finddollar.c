/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finddollar.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:36:44 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:36:45 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	replacedollar_finded(char *finded, t_obj *obj, int *j, char *tofind)
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
	return (i - 1);
}

static int	replacedollar_nfinded(char *tofind)
{
	int	i;

	i = ft_strlen(tofind);
	free(tofind);
	return (i - 1);
}

int	replacedollar(char *line, int *j, t_obj *obj)
{
	char	*tofind;
	char	*finded;

	tofind = malloc(sizeof(char) * ft_strlen(line) + 10);
	if (!tofind)
	{
		perror("Minishell :");
		exit(EXIT_FAILURE);
	}
	replacedollar_tools1(line, tofind);
	if (tofind[0] == '$' && tofind[1] == '\0')
		return (replacedollar_tools2(tofind, obj->buff, j));
	else if (tofind[0] == '$' && tofind[1] == '?')
		return (replacedollar_tools3(obj, tofind, obj->buff, j));
	else if (tofind[0] == '$' && tofind[1] == '0')
		return (replacedollar_tools4(tofind, obj->buff, j));
	finded = finddollar(tofind, obj->myenv);
	if (finded != NULL)
		return (replacedollar_finded(finded, obj, j, tofind));
	else
		return (replacedollar_nfinded(tofind));
}
