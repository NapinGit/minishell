/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:26:41 by toueis            #+#    #+#             */
/*   Updated: 2019/11/08 15:26:41 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	char			*dst;
	unsigned long	i;

	i = -1;
	dst = NULL;
	while (++i <= ft_strlen(s))
	{
		if (s[i] == c)
		{
			dst = (char *)s + i;
			break ;
		}
	}
	return (dst);
}
