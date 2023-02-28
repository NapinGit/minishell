/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:36:17 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:36:18 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	exec_buitin(t_obj *obj, t_cmd *cmd)
{
	if (cmd == NULL || cmd->cmdargs == NULL || cmd->cmdargs[0] == NULL)
		return ;
	else if (ft_strcmp("exit", cmd->cmdargs[0]) == 0)
		parse_exit(obj, cmd);
	else if (ft_strcmp("env", cmd->cmdargs[0]) == 0)
		fork_builtin(obj, cmd, 0);
	else if (ft_strcmp("export", cmd->cmdargs[0]) == 0)
		export_myenv_start(obj, cmd->cmdargs);
	else if (ft_strcmp("unset", cmd->cmdargs[0]) == 0)
		unset_myenv_start(obj, cmd->cmdargs);
	else if (ft_strcmp("cd", cmd->cmdargs[0]) == 0)
		check_number_arg_cd(obj, cmd);
	else if (ft_strcmp("echo", cmd->cmdargs[0]) == 0)
		fork_builtin(obj, cmd, 1);
	else if (ft_strcmp("pwd", cmd->cmdargs[0]) == 0)
		fork_builtin(obj, cmd, 2);
	else if (ft_strncmp("./", cmd->cmdargs[0], 2) == 0)
		exec_bin_local(cmd, obj);
	else if (ft_strncmp("/", cmd->cmdargs[0], 1) == 0)
		exec_bin_unique(cmd, obj->myenv, obj);
	else
		get_path(cmd, obj->myenv, obj);
}
