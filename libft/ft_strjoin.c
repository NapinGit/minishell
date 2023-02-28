/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/08 15:26:58 by toueis            #+#    #+#             */
/*   Updated: 2019/11/08 15:26:59 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(const char *s1, const char *s2)
{
	char	*strjoin;
	int		len;

	if (s1 && s2)
	{
		len = (int)(ft_strlen(s1) + ft_strlen(s2));
		strjoin = (char *)malloc(sizeof(char) * (len + 1));
		if (strjoin == NULL)
			return (NULL);
		strjoin[0] = '\0';
		ft_strcat(strjoin, s1);
		ft_strcat(strjoin, s2);
		return (strjoin);
	}
	else
		return (NULL);
}
