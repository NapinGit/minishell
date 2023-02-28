/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aloiseau <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/25 15:35:53 by aloiseau          #+#    #+#             */
/*   Updated: 2021/10/25 15:35:55 by aloiseau         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

static int	my_cd_2(t_obj *obj, char *path)
{
	char	*tmp;

	if (path && access(path, F_OK) == -1 && path[0] != '~'
		&& path[0] != '-' && path[0] != '/')
	{
		print_error("cd: ", path, "No such file or directory");
		return (0);
	}
	if (path == NULL)
	{
		tmp = dollard("HOME", obj->myenv);
		if (tmp == NULL)
			print_error("cd", NULL, "HOME not set");
		env_pwd(obj, "OLDPWD");
		chdir(tmp);
		env_pwd(obj, "PWD");
		return (0);
	}
	return (1);
}

static void	my_cd_3(t_obj *obj, char *path, char *pwd)
{
	char	*newpath;
	char	*tmp;

	env_pwd(obj, "OLDPWD");
	tmp = ft_strjoin(pwd, "/");
	newpath = ft_strjoin(tmp, path);
	chdir(newpath);
	free (tmp);
	free(newpath);
	free(pwd);
	env_pwd(obj, "PWD");
}

void	cd_less(t_obj *obj)
{
	char	*oldpwd;
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(pwd, 0);
	oldpwd = ft_strdup(dollard("OLDPWD", obj->myenv));
	if (pwd == NULL)
		return ;
	else if (oldpwd == NULL)
		print_error("cd", NULL, "OLDPWD not set");
	else
	{
		env_pwd(obj, "OLDPWD");
		chdir(oldpwd);
		printf("%s\n", oldpwd);
		env_pwd(obj, "PWD");
		free(oldpwd);
		free(pwd);
	}
}

void	cd_slash(t_obj *obj, char *path)
{
	if (access(path, F_OK) == -1)
	{
		print_error("cd: ", path, "No such file or directory");
		return ;
	}
	env_pwd(obj, "OLDPWD");
	chdir(path);
	env_pwd(obj, "PWD");
}

void	my_cd(t_obj *obj, char *path)
{
	char	*pwd;

	pwd = NULL;
	if (my_cd_2(obj, path) == 0)
		return ;
	if (path[0] == '~')
	{
		path = path + 1;
		pwd = ft_strdup(dollard("HOME", obj->myenv));
		if (pwd == NULL)
		{
			print_error("cd", NULL, "HOME not set");
			return ;
		}
	}
	else if (path[0] == '-')
		cd_less(obj);
	else if (path[0] == '/')
		cd_slash(obj, path);
	else
		pwd = getcwd(pwd, 0);
	if (pwd == NULL)
		return ;
	my_cd_3(obj, path, pwd);
}
