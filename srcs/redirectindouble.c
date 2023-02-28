/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirectindouble.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:37:32 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:37:33 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static void	redirect_exit(void)
{
	perror("Minishell ");
	exit(EXIT_FAILURE);
}

static int	redirect_exit2(char *rin, char *stop, int i)
{
	free(rin);
	printf("minishell: warning: here-document at line %d", i);
	printf(" delimited by end-of-file (wanted `%s')\n", stop);
	return (-1);
}

void	changefdrd(t_cmd *cmd)
{
	int	fd;

	if (cmd->rin != NULL)
	{
		fd = open("/tmp/tmpfile", O_RDWR | O_TRUNC | O_CREAT, 0666);
		if (fd < 0)
			redirect_exit();
		write(fd, cmd->rin, (int)ft_strlen(cmd->rin));
		if ((int)ft_strlen(cmd->rin) > 0)
			write(fd, "\n", 1);
		close(fd);
		fd = open("/tmp/tmpfile", O_RDWR | O_CREAT, 0666);
		dup2(fd, 0);
	}
	if (cmd->fdstdin != 0)
	{
		dup2(cmd->fdstdin, 0);
		close(cmd->fdstdin);
	}
	if (cmd->fdstdout != 1)
	{
		dup2(cmd->fdstdout, 1);
		close(cmd->fdstdout);
	}
}

char	*straddback(char **src, char *add)
{
	char	*tmp;
	char	*tmp2;

	if (!(*src) || (*src)[0] == '\0')
	{
		free((*src));
		tmp = ft_strdup(add);
		return (tmp);
	}
	tmp = ft_strjoin((*src), "\n");
	tmp2 = ft_strjoin(tmp, add);
	free((*src));
	free(tmp);
	return (tmp2);
}

int	redirectindouble(char *stop, t_cmd *cmd)
{
	char	*rin;
	char	*line;
	int		i;

	rin = (char *)malloc(sizeof(char) * 1);
	if (!rin)
		redirect_exit();
	i = 1;
	rin[0] = '\0';
	while (1)
	{
		line = readline("> ");
		if (!line)
			return (redirect_exit2(rin, stop, i));
		if (line && ft_strcmp(line, stop) == 0)
		{
			cmd->rin = rin;
			free(line);
			return (0);
		}
		rin = straddback(&rin, line);
		free(line);
		i++;
	}
	return (-1);
}
