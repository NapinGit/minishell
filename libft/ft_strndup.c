/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <toueis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/27 13:15:54 by toueis            #+#    #+#             */
/*   Updated: 2021/10/27 13:15:54 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strndup(const char *s1, size_t size)
{
	size_t	i;
	char	*dest;

	i = 0;
	if (s1 == NULL || size == 0)
		return (NULL);
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (dest == NULL )
		return (NULL);
	while (s1[i] && i < size)
	{
		dest[i] = s1[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}
