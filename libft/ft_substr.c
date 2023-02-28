/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsub.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:27:53 by toueis            #+#    #+#             */
/*   Updated: 2019/11/26 14:45:39 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_substr(const char *s, unsigned int start, size_t len)
{
	char	*strsub;
	size_t	i;

	if (s)
	{
		if (start > ft_strlen(s))
		{
			strsub = (char *)malloc(sizeof(char) * 1);
			if (strsub == NULL)
				return (NULL);
			strsub[0] = '\0';
			return (strsub);
		}
		i = -1;
		strsub = ft_calloc(len + 1, 1);
		if (strsub == NULL)
			return (NULL);
		while (++i < len)
			strsub[i] = s[start + i];
		return (strsub);
	}
	else
		return (strsub = NULL);
}
