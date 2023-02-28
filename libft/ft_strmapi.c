/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strmapi.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:27:22 by toueis            #+#    #+#             */
/*   Updated: 2019/11/08 15:27:23 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strmapi(const char *s, char (*f)(unsigned int, char))
{
	char	*strmapi;
	int		i;

	if (s)
	{
		i = -1;
		strmapi = (char *)ft_calloc(sizeof(char), (ft_strlen(s) + 1));
		if (strmapi == NULL)
			return (NULL);
		while (s[++i])
			strmapi[i] = f(i, s[i]);
		strmapi[i] = '\0';
		return (strmapi);
	}
	else
		return (strmapi = NULL);
}
