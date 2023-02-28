/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:26:52 by toueis            #+#    #+#             */
/*   Updated: 2019/11/12 17:14:17 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char	*dup;

	if (s1)
	{
		dup = (char *)malloc(sizeof(*dup) * ft_strlen(s1) + 1);
		if (dup == NULL)
			return (NULL);
		dup = ft_strcpy(dup, s1);
	}
	else
		dup = NULL;
	return (dup);
}
