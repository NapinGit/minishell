/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirecttools.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:37:38 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:37:39 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	redirectin(char *path, t_cmd *cmd)
{
	int	fd;

	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		print_error(NULL, path, "No such file or directory");
		return (-1);
	}
	cmd->fdstdin = fd;
	return (0);
}

int	redirectinspe(char *path, t_cmd *cmd)
{
	int	fd;

	fd = open(path, O_RDONLY | O_CREAT, 0666);
	if (fd == -1)
	{
		print_error(NULL, path, "No such file or directory");
		return (-1);
	}
	cmd->fdstdin = fd;
	return (0);
}

int	redirectout(char *file, t_cmd *cmd)
{
	int	fd;

	fd = open(file, O_WRONLY | O_TRUNC | O_CREAT, 0666);
	if (fd == -1)
	{
		print_error(NULL, file, "No such file or directory");
		return (-1);
	}
	cmd->fdstdout = fd;
	return (0);
}

int	redirectoutdouble(char *file, t_cmd *cmd)
{
	int	fd;

	fd = open(file, O_WRONLY | O_APPEND | O_CREAT, 0666);
	if (fd == -1)
	{
		print_error(NULL, file, "No such file or directory");
		return (-1);
	}
	cmd->fdstdout = fd;
	return (0);
}
