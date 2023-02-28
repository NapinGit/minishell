/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:36:53 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:36:54 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	myctrlsignal(int sig)
{
	if (sig == SIGINT)
	{
		write(1, "\n", 1);
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	myexitd(t_obj *obj)
{
	printf("exit\n");
	free_env(obj->myenv);
	unlink("/tmp/tmpfile");
	rl_clear_history();
	close(0);
	close(1);
	close(2);
	exit(0);
}

static int	myprompt(t_obj *obj)
{
	char	*line;
	t_list	*list;

	line = NULL;
	list = NULL;
	obj->act.sa_handler = &myctrlsignal;
	sigaction(SIGINT, &obj->act, NULL);
	sigaction(SIGQUIT, &obj->act, NULL);
	while (1)
		myprompt2(obj, line, list);
	free(line);
	return (0);
}

int	main(int ac, char **av, char **envp)
{
	t_obj				obj;

	(void)ac;
	(void)av;
	ft_bzero(&obj, sizeof(t_obj));
	if (init_env(envp, &obj, av) == 0)
		return (0);
	if (myprompt(&obj) == 0)
	{
		close(0);
		close(1);
		close(2);
		return (0);
	}
	return (-1);
}
