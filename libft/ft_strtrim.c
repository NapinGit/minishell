/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:27:59 by toueis            #+#    #+#             */
/*   Updated: 2019/11/26 17:38:54 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_counttrim(const char *s1, const char *set)
{
	int	len;
	int	i;

	len = ft_strlen(s1);
	i = 0;
	while (len > 0 && set[i])
	{
		if (s1[len - 1] == set[i])
		{
			len--;
			i = 0;
		}
		else
			i++;
	}
	return (len);
}

static char	*ft_stricpy(char *dst, const char *src, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	int		len;
	char	*str;

	if (!s1)
		return (NULL);
	if (!set)
		return (ft_strdup(s1));
	i = 0;
	while (*s1 && set[i])
	{
		if (*s1 == set[i])
		{
			s1++;
			i = 0;
		}
		else
			i++;
	}
	len = ft_counttrim(s1, set);
	str = (char *)malloc(sizeof(char) * (len + 1));
	if (str == NULL )
		return (NULL);
	str = ft_stricpy(str, s1, len);
	return (str);
}
