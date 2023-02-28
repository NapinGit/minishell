/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   myprompt.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <toueis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/20 20:41:28 by toueis            #+#    #+#             */
/*   Updated: 2021/11/20 20:41:30 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	myprompt2tools(t_obj *obj, char *line, t_list **list, t_cmd **cmd)
{
	add_history(line);
	obj->line = line;
	*list = first_cut(obj);
	if (!*list)
		return (1);
	obj->list = *list;
	obj->status = parse_error(*list);
	if (obj->status != 0)
	{
		free(line);
		freelist(*list);
		return (1);
	}
	*cmd = second_cut(*list);
	obj->cmd = *cmd;
	return (0);
}

static void	myprompt2_tools2(t_obj *obj, t_cmd *cmd, t_cmd *tmp)
{
	obj->nbpipe = 0;
	tmp = cmd;
	while (tmp->token == '|')
	{
		obj->nbpipe++;
		tmp = tmp->next;
	}
	pipemulti(cmd, obj);
}

static void	myprompt2_tools(t_obj *obj, t_cmd *cmd)
{
	cmd = (t_cmd *)malloc(sizeof(t_cmd));
	if (!cmd)
	{
		perror("Minishell ");
		exit(EXIT_FAILURE);
	}
	cmd->cmdargs = NULL;
	cmd->rin = NULL;
	cmd->token = 0;
	cmd->fdstdin = 0;
	cmd->fdstdout = 1;
	cmd->next = NULL;
	obj->cmd = cmd;
}

int	myprompt2(t_obj *obj, char *line, t_list *list)
{
	t_cmd	*cmd;
	t_cmd	*tmp;

	cmd = NULL;
	tmp = NULL;
	line = readline("$ ");
	if (!line)
		myexitd(obj);
	if (ft_strlen(line) > 0)
	{
		if (myprompt2tools(obj, line, &list, &cmd) == 1)
			return (1);
	}
	else
		myprompt2_tools(obj, cmd);
	if (cmd && cmd->cmdargs && cmd->token == '|')
		myprompt2_tools2(obj, cmd, tmp);
	else if (cmd && cmd->cmdargs)
		exec_buitin(obj, cmd);
	freelist(list);
	freecmd(obj->cmd);
	free(line);
	return (0);
}
