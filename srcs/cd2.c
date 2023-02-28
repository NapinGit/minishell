/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd2.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:35:53 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:35:55 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	check_number_arg_cd(t_obj *obj, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd && cmd->cmdargs[i])
	{
		i++;
	}
	if (i > 2)
	{
		print_error("cd", NULL, "too many arguments");
		return ;
	}
	else
		my_cd(obj, cmd->cmdargs[1]);
}

void	env_pwd(t_obj *obj, char *name)
{
	char	*tmp;
	char	*sw;
	char	*pwd;

	pwd = NULL;
	tmp = NULL;
	sw = NULL;
	pwd = getcwd(pwd, 0);
	if (pwd == NULL)
		return ;
	unset_myenv(obj, name);
	sw = ft_strjoin(name, "=");
	tmp = ft_strjoin(sw, pwd);
	export_myenv(obj, tmp);
	free(sw);
	free(tmp);
	free(pwd);
}
