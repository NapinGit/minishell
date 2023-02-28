/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exitfree.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:36:27 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:36:28 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	myexit(t_obj *obj, int val)
{
	free_env(obj->myenv);
	freelist(obj->list);
	freecmd(obj->cmd);
	unlink("/tmp/tmpfile");
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	exit(val);
}

void	parse_exit_2(t_obj *obj, t_cmd *cmd)
{
	int	i;

	i = 0;
	while (cmd->cmdargs[1][i])
	{
		if (cmd->cmdargs[1][i] >= '0' && cmd->cmdargs[1][i] <= '9')
			i++;
		else
		{
			print_error("exit: ", cmd->cmdargs[1], "numeric argument required");
			myexit(obj, 2);
		}
	}
}

void	parse_exit(t_obj *obj, t_cmd *cmd)
{
	int	i;

	i = 0;
	if (cmd->cmdargs[1])
	{
		parse_exit_2(obj, cmd);
		while (cmd->cmdargs[i])
			i++;
		if (i > 2)
		{
			print_error("exit", NULL, "too many arguments");
			return ;
		}
		i = ft_atoi(cmd->cmdargs[1]);
	}
	myexit(obj, i);
	return ;
}

void	freelist(t_list *list)
{
	t_list	*tmp;

	tmp = list;
	while (tmp)
	{
		if (tmp && tmp->content)
			free(tmp->content);
		tmp = tmp->next;
	}
	tmp = list;
	while (list)
	{
		list = list->next;
		free(tmp);
		tmp = list;
	}
}

void	freecmd(t_cmd *cmd)
{
	t_cmd	*tmp;

	tmp = cmd;
	while (tmp)
	{
		if (tmp->fdstdin != 0)
			close(tmp->fdstdin);
		if (tmp->fdstdout != 1)
			close(tmp->fdstdout);
		if (tmp->rin != NULL)
			free(tmp->rin);
		if (tmp->cmdargs != NULL)
			free(tmp->cmdargs);
		tmp = tmp->next;
	}
	tmp = cmd;
	while (cmd)
	{
		cmd = cmd->next;
		free(tmp);
		tmp = cmd;
	}
}
