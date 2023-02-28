/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:16:47 by toueis            #+#    #+#             */
/*   Updated: 2019/11/12 16:05:10 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*calloc;

	calloc = NULL;
	calloc = (void *)malloc(size * count);
	if (calloc == NULL)
		return (NULL);
	ft_bzero(calloc, count * size);
	return (calloc);
}
