/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:16:22 by toueis            #+#    #+#             */
/*   Updated: 2019/11/21 15:43:10 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static void	signtools_atoi(const char *str, int *i, int *my_bool)
{
	if (str[*i] == '+' || str[*i] == '-')
	{
		if (str[*i] == '-')
			*my_bool = 1;
		*i = *i + 1;
	}
}

int	ft_atoi(const char *str)
{
	int		i;
	int		my_bool;
	long	my_nb;

	my_nb = 0;
	my_bool = 0;
	i = 0;
	while ((str[i] >= 9 && str[i] <= 13) || str[i] == ' ')
		i++;
	signtools_atoi(str, &i, &my_bool);
	while (ft_isdigit(str[i]) == 1)
	{
		my_nb = my_nb * 10 + str[i] - '0';
		i++;
		if (my_nb > 2147483647 && my_bool == 0)
			return (-1);
		if (my_nb > 2147483648 && my_bool == 1)
			return (0);
	}
	if (my_bool == 1)
		return (-my_nb);
	return (my_nb);
}
