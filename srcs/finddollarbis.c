/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   finddollarbis.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <toueis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:08:13 by toueis            #+#    #+#             */
/*   Updated: 2021/11/20 20:08:18 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	mystrcmp(char *envp, char *var)
{
	int	i;

	i = 0;
	while (envp[i] != '=')
	{
		if (var[i] != 0 && var[i] != envp[i])
			return (1);
		if (var[i] == 0 && envp[i] != '=')
			return (1);
		i++;
	}
	if (var[i] == 0 && envp[i] == '=')
		return (0);
	return (1);
}

char	*finddollar(char *tofind, char **envp)
{
	char	*find;
	int		i;
	int		j;

	i = 0;
	while (envp[i])
	{
		if (mystrcmp(envp[i], tofind + 1) == 0)
		{
			j = 0;
			while (envp[i][j] != '=')
				j++;
			find = envp[i] + j + 1;
			return (find);
		}
		else
			i++;
	}
	return (NULL);
}

int	replacedollarbistools4(t_obj *obj, char *tofind, int *j)
{
	int		i;
	char	*str;

	str = ft_strdup("minishell");
	i = 0;
	while (str[i])
	{
		obj->buff[*j] = str[i];
		*j = *j + 1;
		i++;
	}
	obj->buff[*j] = 0;
	i = (int)ft_strlen(tofind);
	free(tofind);
	free(str);
	return (i);
}

int	replacedollarbistools3(t_obj *obj, char *tofind, int *j)
{
	char	*str;
	int		i;

	str = ft_itoa(obj->status);
	i = 0;
	while (str[i])
	{
		obj->buff[*j] = str[i];
		*j = *j + 1;
		i++;
	}
	obj->buff[*j] = 0;
	i = (int)ft_strlen(tofind);
	free(tofind);
	free(str);
	return (i);
}

int	replacedollarbistools2(t_obj *obj, char *tofind, int *j)
{
	obj->buff[*j] = tofind[0];
	*j = *j + 1;
	obj->buff[*j] = 0;
	free(tofind);
	return (1);
}
