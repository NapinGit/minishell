/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <toueis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/28 16:54:13 by toueis            #+#    #+#             */
/*   Updated: 2021/11/28 16:54:14 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*tmp;
	int		*cast;
	int		*cast2;
	size_t	i;

	i = 0;
	tmp = (void *)malloc(size);
	if (!tmp)
		return (NULL);
	cast = (int *)tmp;
	cast2 = (int *)ptr;
	while (cast2[i] != 0)
	{
		cast[i] = cast2[i];
		i++;
	}
	while (i < size)
		cast[i++] = 0;
	free(ptr);
	return (tmp);
}
