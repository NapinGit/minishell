/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:25:25 by toueis            #+#    #+#             */
/*   Updated: 2019/11/08 15:25:25 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <string.h>

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned char	*ptr_str;
	void			*ptr;
	size_t			i;

	i = -1;
	ptr_str = (unsigned char *)s;
	while (++i < n)
		if (ptr_str[i] == (unsigned char)c)
			return (ptr = ptr_str + i);
	return (NULL);
}
