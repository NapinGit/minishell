/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:36:36 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:36:37 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	affenv_export(char **env, int env_len)
{
	int	i;

	i = 0;
	sort_env(env, env_len);
	while (env[i])
	{
		printf("declare -x %s\n", env[i]);
		i++;
	}
}

static void	export_myenv_2(t_obj *obj, char *to_add)
{
	int		i;
	char	**new_env;

	i = 0;
	obj->len_myenv++;
	new_env = malloc(sizeof(char *) * (obj->len_myenv + 1));
	if (obj->myenv == NULL)
	{
		write(2, "minishell: l'allocation de mémoire de", 37);
		write(2, " l'environnement a échoué\n", 26);
		free_env(obj->myenv);
		exit(EXIT_FAILURE);
	}
	while (i < obj->len_myenv - 1)
	{
		new_env[i] = obj->myenv[i];
		i++;
	}
	new_env[i] = ft_strdup(to_add);
	new_env[i + 1] = NULL;
	free(obj->myenv);
	obj->myenv = new_env;
}

static int	parse_export_myenv(char *to_add)
{
	int		i;

	i = 0;
	while (to_add[i] != '=')
	{
		if (!(to_add[i]))
			return (0);
		if ((to_add[i] >= 0 && to_add[i] <= '/') || (to_add[i] >= ':'
				&& to_add[i] <= '@') || to_add[i] >= '{'
			|| (to_add[i] >= '[' && to_add[i] <= '^'))
		{
			print_error("export: ", to_add, "not a valid identifier");
			return (0);
		}
		i++;
	}
	i = 0;
	if ((to_add[i] >= '0' && to_add[i] <= '@') || (to_add[i] >= '['
			&& to_add[i] <= '^') || to_add[i] >= '{' || to_add[i] <= 47)
	{
		print_error("export: ", to_add, "not a valid identifier");
		return (0);
	}
	return (1);
}

void	export_myenv(t_obj *obj, char *to_add)
{
	char	*tmp;
	int		i;

	i = 0;
	if (parse_export_myenv(to_add) == 0)
		return ;
	while (obj->myenv[i])
	{
		if (ft_strncmp(to_add, obj->myenv[i], \
			ft_lenworld(to_add, '=') + 1) == 0)
		{
			tmp = ft_strndup(obj->myenv[i], ft_lenworld(to_add, '='));
			unset_myenv(obj, tmp);
			free(tmp);
			break ;
		}
		i++;
	}
	export_myenv_2(obj, to_add);
}

void	export_myenv_start(t_obj *obj, char **arg)
{
	int	i;

	i = 1;
	while (arg[i])
	{
		export_myenv(obj, arg[i]);
		i++;
	}
	if (i == 1)
	{
		fork_builtin(obj, obj->cmd, 3);
	}
}
