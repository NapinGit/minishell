/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   new_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:37:08 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:37:09 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static char	**unset_newenv_2(char **envp, char *to_remove, int len)
{
	int		k;
	int		i;
	char	**new_env;

	i = 0;
	k = 0;
	new_env = malloc(sizeof(char *) * (len));
	if (new_env == NULL)
	{
		write(2, "minishell: l'allocation de mémoire de", 37);
		write(2, " l'environnement a échoué\n", 26);
		return (NULL);
	}
	while (envp[i])
	{
		if (ft_strncmp(to_remove, envp[i], ft_strlen(to_remove)) != 0)
		{
			new_env[k] = envp[i];
			k++;
		}
		i++;
	}
	new_env[k] = NULL;
	free(envp);
	return (new_env);
}

char	**unset_newenv(char **envp, char *to_remove)
{
	int		i;
	char	*delete;
	char	**new_env;

	i = 0;
	delete = NULL;
	while (envp[i])
	{
		if (ft_strncmp(to_remove, envp[i], ft_strlen(to_remove)) == 0
			&& envp[i][ft_strlen(to_remove)] == '=')
		{
			delete = ft_strdup(envp[i]);
			free(envp[i]);
			envp[i] = delete;
		}
		i++;
	}
	if (delete == NULL)
		return (NULL);
	i = 0;
	while (envp[i])
		i++;
	new_env = unset_newenv_2(envp, to_remove, i);
	free(delete);
	return (new_env);
}

static char	**export_newenv_2(char **envp, char *to_add)
{
	int		len;
	int		i;
	char	**new_env;

	i = 0;
	len = 0;
	while (envp[len])
		len++;
	new_env = malloc(sizeof(char *) * (len + 2));
	if (new_env == NULL)
	{
		write(2, "minishell: l'allocation de mémoire de", 37);
		write(2, " l'environnement a échoué\n", 26);
		exit(EXIT_FAILURE);
	}
	while (i < len)
	{
		new_env[i] = envp[i];
		i++;
	}
	new_env[i] = ft_strdup(to_add);
	new_env[i + 1] = NULL;
	free (envp);
	return (new_env);
}

char	**export_newenv(char **envp, char *to_add)
{
	char	**new_env;
	char	*tmp;
	int		i;

	i = 0;
	while (envp[i])
	{
		if (ft_strncmp(to_add, envp[i], ft_lenworld(to_add, '=') + 1) == 0)
		{
			tmp = ft_strndup(envp[i], ft_lenworld(to_add, '='));
			envp = unset_newenv(envp, tmp);
			free(tmp);
			break ;
		}
		i++;
	}
	new_env = export_newenv_2(envp, to_add);
	return (new_env);
}

char	**add_executable(char **envp, char *path)
{
	char	*tmp;
	char	*switc;
	char	**newenv;

	tmp = NULL;
	switc = NULL;
	tmp = getcwd(tmp, 0);
	switc = ft_strjoin("_=", tmp);
	free(tmp);
	tmp = ft_strjoin(switc, path);
	free(switc);
	newenv = export_newenv(envp, tmp);
	free(tmp);
	return (newenv);
}
