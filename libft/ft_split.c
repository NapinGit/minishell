/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/26 17:23:39 by toueis            #+#    #+#             */
/*   Updated: 2019/11/26 17:23:42 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static char	**ft_freesplit(char **str)
{
	while (*str)
	{
		free(str);
		(*str)++;
	}
	free(str);
	return (NULL);
}

static size_t	ft_lenworld(const char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static char	*ft_malcopy(const char *str, size_t size)
{
	unsigned int	i;
	char			*dest;

	i = 0;
	dest = (char *)malloc(sizeof(char) * (size + 1));
	if (dest == NULL)
		return (NULL);
	while (i < size && str[i])
	{
		dest[i] = str[i];
		i++;
	}
	dest[i++] = '\0';
	return (dest);
}

static char	**ft_splittt(char **str, char const *s1, char s2)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	while (*(s1 + i))
	{
		while (*(s1 + i) && *(s1 + i) == s2)
			i++;
		if (*(s1 + i))
		{
			str[j] = ft_malcopy(s1 + i, ft_lenworld(s1 + i, s2));
			if (str[j] == NULL)
				return (NULL);
		}
		else
			break ;
		while (*(s1 + i) && *(s1 + i) != s2)
			i++;
		j++;
	}
	*(str + j) = 0;
	return (str);
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		count;
	char	**tab;

	i = 0;
	count = 0;
	if (!s)
		return (NULL);
	while (*(s + i))
	{
		while (*(s + i) && *(s + i) == c)
			i++;
		while (*(s + i) && *(s + i) != c)
			i++;
		if (*(s + i - 1) != c)
			count++;
	}
	tab = malloc(sizeof(char *) * (count + 1));
	if (tab == NULL)
		return (NULL);
	if (ft_splittt(tab, s, c) == NULL)
		return (ft_freesplit(tab));
	return (tab);
}
