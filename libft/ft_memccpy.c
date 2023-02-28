/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:25:19 by toueis            #+#    #+#             */
/*   Updated: 2019/11/08 15:25:20 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t					i;
	unsigned char			*ptr_dst;
	const unsigned char		*ptr_src;

	i = 0;
	ptr_dst = dst;
	ptr_src = src;
	while (i < n)
	{
		ptr_dst[i] = ptr_src[i];
		if (ptr_src[i] == (unsigned char)c)
			return (dst = &ptr_dst[i + 1]);
		i++;
	}
	return (dst = NULL);
}
