/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:25:53 by toueis            #+#    #+#             */
/*   Updated: 2019/11/21 14:02:13 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dst, const void *src, size_t len)
{
	char	*new_dest;
	char	*new_src;
	char	*dest_over;
	char	*src_over;

	if (dst == NULL && src == NULL)
		return (NULL);
	new_dest = dst;
	new_src = (char *)src;
	if (new_dest < new_src)
		ft_memcpy(dst, src, len);
	else
	{
		src_over = new_src + (len - 1);
		dest_over = new_dest + (len - 1);
		while (len--)
			*dest_over-- = *src_over--;
	}
	return (dst);
}
