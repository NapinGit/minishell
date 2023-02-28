/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:18:10 by toueis            #+#    #+#             */
/*   Updated: 2019/11/08 15:18:10 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_len(int n)
{
	int	count;

	count = 0;
	if (n < 0)
	{
		count++;
		n = -n;
	}
	while (n)
	{
		n = n / 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char	*s;
	int		len;

	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	if (n == 0)
		return (ft_strdup("0"));
	len = ft_len(n);
	s = (char *)malloc(sizeof(char) * (len + 1));
	if (s == NULL )
		return (NULL);
	s[len] = '\0';
	len--;
	if (n < 0)
	{
		s[0] = '-';
		n = -n;
	}
	while (len >= 0 && n)
	{
		s[len] = (n % 10) + '0';
		n = n / 10;
		len--;
	}
	return (s);
}
