/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:27:36 by toueis            #+#    #+#             */
/*   Updated: 2019/11/08 15:27:37 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	char	*strstr;
	int		i;
	int		j;

	if (to_find[0] == '\0')
		return (strstr = (char *)str);
	while (*str && len > 0 && len >= ft_strlen(to_find))
	{
		i = 0;
		j = 0;
		while (str[j] == to_find[i])
		{
			j++;
			i++;
			if (to_find[i] == '\0')
				return (strstr = (char *)str);
		}
		str++;
		len--;
	}
	return (NULL);
}
