/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:37:53 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:37:54 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

char	*unset_myenv_2(t_obj *obj, char *to_remove)
{
	int		i;
	int		len_to_remove;
	char	*delete;

	i = 0;
	delete = NULL;
	len_to_remove = ft_strlen(to_remove);
	while (obj->myenv[i])
	{
		if (ft_strncmp(to_remove, obj->myenv[i], len_to_remove) == 0
			&& obj->myenv[i][len_to_remove] == '=')
		{
			delete = ft_strdup(obj->myenv[i]);
			free(obj->myenv[i]);
			obj->myenv[i] = delete;
		}
		i++;
	}
	return (delete);
}

static char	**unset_myenv_3(t_obj *obj, char *to_remove, char **new_env)
{
	int	i;
	int	k;

	i = 0;
	k = 0;
	while (obj->myenv[i])
	{
		if (ft_strncmp(to_remove, obj->myenv[i], ft_strlen(to_remove)) != 0)
		{
			new_env[k] = obj->myenv[i];
			k++;
		}
		i++;
	}
	new_env[k] = NULL;
	return (new_env);
}

static int	parse_unset_myenv(char *to_add)
{
	int		i;

	i = 0;
	while (to_add[i])
	{
		if ((to_add[i] >= 0 && to_add[i] <= '/') || (to_add[i] >= ':'
				&& to_add[i] <= '@') || to_add[i] >= '{'
			|| (to_add[i] >= '[' && to_add[i] <= '^'))
		{
			print_error("unset :", to_add, "not a valid identifiers");
			return (0);
		}
		i++;
	}
	i = 0;
	if ((to_add[i] >= '0' && to_add[i] <= '@') || (to_add[i] >= '['
			&& to_add[i] <= '^') || to_add[i] >= '{' || to_add[i] <= 47)
	{
		print_error("unset :", to_add, "not a valid identifier");
		return (0);
	}
	return (1);
}

void	unset_myenv(t_obj *obj, char *to_remove)
{
	char	*delete;
	char	**new_env;

	if (parse_unset_myenv(to_remove) == 0)
		return ;
	delete = unset_myenv_2(obj, to_remove);
	if (delete == NULL)
		return ;
	new_env = malloc(sizeof(char *) * (obj->len_myenv));
	if (new_env == NULL)
	{
		write(2, "minishell: l'allocation de mémoire de", 37);
		write(2, " l'environnement a échoué\n", 26);
		free_env(obj->myenv);
		exit(EXIT_FAILURE);
	}
	obj->len_myenv--;
	new_env = unset_myenv_3(obj, to_remove, new_env);
	free(delete);
	free(obj->myenv);
	obj->myenv = new_env;
}

void	unset_myenv_start(t_obj *obj, char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		unset_myenv(obj, arg[i]);
		i++;
	}
}
