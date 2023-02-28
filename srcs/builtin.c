/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:35:23 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:35:25 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	sort_env(char **envp, int len)
{
	int		ordered;
	int		i;
	int		env_len;
	char	*tmp;

	env_len = len;
	ordered = 0;
	while (envp && ordered == 0)
	{
		ordered = 1;
		i = 0;
		while (i < env_len - 1)
		{
			if (ft_strcmp(envp[i], envp[i + 1]) > 0)
			{
				tmp = envp[i];
				envp[i] = envp[i + 1];
				envp[i + 1] = tmp;
				ordered = 0;
			}
			i++;
		}
		env_len--;
	}
}

void	aff_env(char **envp)
{
	int	i;

	i = 0;
	while (envp[i])
	{
		printf("%s\n", envp[i]);
		i++;
	}
}

static void	fork_builtin2(t_obj *obj, t_cmd *cmd, int mode)
{
	changefdrd(cmd);
	if (mode == 0)
		aff_env(obj->myenv);
	else if (mode == 1)
		my_echo(cmd->cmdargs);
	else if (mode == 2)
		my_pwd();
	else if (mode == 3)
		affenv_export(obj->myenv, obj->len_myenv);
	if (obj->tabfd)
	{
		free(obj->tabfd);
		obj->tabfd = NULL;
	}
	free_env(obj->myenv);
	freecmd(obj->cmd);
	freelist(obj->list);
	close(0);
	close(1);
	close(2);
	exit(EXIT_SUCCESS);
}

void	fork_builtin(t_obj *obj, t_cmd *cmd, int mode)
{
	pid_t	pid;
	int		status;

	status = 0;
	pid = fork();
	if (pid == 0)
		fork_builtin2(obj, cmd, mode);
	else if (pid < 0)
	{
		write(2, "minishell: Fork failed to create a new process.\n", 48);
		return ;
	}
	else
		waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		obj->status = WEXITSTATUS(status);
}
