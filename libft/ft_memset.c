/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memset.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:26:00 by toueis            #+#    #+#             */
/*   Updated: 2019/11/08 15:26:01 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memset(void *b, int c, size_t len)
{
	unsigned char	letter;
	unsigned char	*ptr;
	size_t			i;

	i = 0;
	ptr = (unsigned char *)b;
	letter = c;
	while (i < len)
	{
		ptr[i] = letter;
		i++;
	}
	return (b);
}
