/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:36:09 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:36:11 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	my_echo(char **arg)
{
	int	i;
	int	optionn;

	i = 1;
	optionn = 0;
	if (arg[i] == NULL)
	{
		printf("\n");
		return ;
	}
	if (ft_strcmp("-n", arg[i]) == 0)
	{	
		optionn = 1;
		i++;
	}
	while (arg[i])
	{
		if ((i != 1 && optionn == 0) || (i != 2 && optionn == 1))
			write(1, " ", 1);
		write(1, arg[i], ft_strlen(arg[i]));
		i++;
	}
	if (optionn == 0)
		write(1, "\n", 1);
}
