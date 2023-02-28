/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:38:28 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:38:30 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

size_t	ft_lenworld(char *s, char c)
{
	size_t	len;

	len = 0;
	while (s[len] && s[len] != c)
		len++;
	return (len);
}

static int	construct_env(t_obj *obj, char **av)
{
	char	*pwd;
	char	*tmp;
	char	*tmp2;
	char	**new_env;

	new_env = malloc(sizeof(char *) * (4));
	if (new_env == NULL)
	{
		write(2, "minishell: l'allocation de mémoire de", 37);
		write(2, " l'environnement a échoué\n", 26);
		return (0);
	}
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	tmp = ft_strjoin("PWD=", pwd);
	new_env[0] = tmp;
	new_env[1] = ft_strdup("SHLVL=1");
	tmp = NULL;
	tmp = ft_strjoin("_=", pwd);
	tmp2 = ft_strjoin(tmp, av[0]);
	new_env[2] = tmp2;
	free(tmp);
	new_env[3] = 0;
	obj->myenv = new_env;
	return (1);
}

void	cp_env(char **envp, t_obj *obj)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		obj->myenv[i] = ft_strdup(envp[i]);
		i++;
		obj->len_myenv++;
	}
	obj->myenv[i] = NULL;
}

int	init_env(char **envp, t_obj *obj, char **av)
{
	int	i;

	i = 0;
	if (envp[i] == NULL)
	{
		if (construct_env(obj, av) == 0)
			return (0);
		return (1);
	}
	while (envp[i])
		i++;
	obj->myenv = malloc(sizeof(char *) * (i + 1));
	if (obj->myenv == NULL)
	{
		write(2, "minishell: l'allocation de mémoire de", 37);
		write(2, " l'environnement a échoué\n", 26);
		return (0);
	}
	cp_env(envp, obj);
	return (1);
}

char	*dollard(char *tofind, char **envp)
{
	char	*out;
	int		i;

	i = 0;
	out = NULL;
	while (envp[i])
	{
		if (ft_strncmp(tofind, envp[i], ft_strlen(tofind)) == 0)
		{
			if (envp[i][ft_strlen(tofind)] == '=')
			{
				out = envp[i] + ft_strlen(tofind) + 1;
				break ;
			}
		}
		i++;
	}
	return (out);
}
