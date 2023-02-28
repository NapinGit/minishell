/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: toueis <toueis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/12 10:43:54 by toueis            #+#    #+#             */
/*   Updated: 2021/11/12 10:43:55 by toueis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/libft.h"
# include <signal.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <dirent.h>

typedef struct s_list
{
	char			*content;
	int				ign;
	struct s_list	*next;
}					t_list;

typedef struct s_cmd
{
	char			**cmdargs;
	int				token;
	int				fdstdin;
	int				fdstdout;
	char			*rin;
	struct s_cmd	*next;
}					t_cmd;

typedef struct s_obj
{
	t_list				*list;
	t_list				*tmp;
	t_cmd				*cmd;
	char				**myenv;
	int					len_myenv;
	int					status;
	int					nbpipe;
	pid_t				lastpid;
	char				*line;
	char				*buff;
	int					*tabfd;
	struct sigaction	act;
}					t_obj;

t_list			*first_cut(t_obj *obj);
char			*finddollar(char *tofind, char **envp);
int				replacedollar(char *line, int *j, t_obj *obj);
int				replacedollarbis(char *line, int *j, t_obj *obj);
t_cmd			*second_cut(t_list *list);
void			get_path(t_cmd *cmd, char **envp, t_obj *obj);
char			*dollard(char	*tofind, char	**envp);
void			exec_buitin(t_obj *obj, t_cmd *cmd);
int				init_env(char **envp, t_obj *obj, char **av);
void			myexit(t_obj *obj, int val);
void			export_myenv_start(t_obj	*obj, char	**arg);
void			unset_myenv_start(t_obj	*obj, char	**arg);
void			unset_myenv(t_obj	*obj, char	*to_remove);
void			export_myenv(t_obj	*obj, char	*to_add);
void			my_cd(t_obj	*obj, char	*path);
void			my_echo(char	**arg);
void			my_pwd(void);
void			exec_bin_local(t_cmd	*cmd, t_obj	*obj);
void			pipemulti(t_cmd	*cmd, t_obj	*obj);
size_t			ft_lenworld(char *s, char c);
char			**create_newenv(char	**envp, char	*path);
void			aff_env(char	**envp);
void			free_env(char	**envp);
void			fork_builtin(t_obj *obj, t_cmd	*cmd, int mode);
void			affenv_export(char	**env, int env_len);
int				redirectindouble(char	*path, t_cmd	*cmd);
void			changefdrd(t_cmd	*cmd);
int				parse_error(t_list	*list);
void			freelist(t_list	*list);
void			freecmd(t_cmd	*cmd);
int				redirectinspe(char *path, t_cmd *cmd);
int				redirectin(char *path, t_cmd *cmd);
int				redirectout(char *file, t_cmd *cmd);
int				redirectoutdouble(char *file, t_cmd *cmd);
int				copysimplequote(char *line, t_obj *obj, int *i, int *j);
int				copydoublequote(char *line, int *i, int *j, t_obj *obj);
int				copystring(char *line, t_list **tmp, t_obj *obj);
int				copyc(char *line, char **content);
int				copyoblique(char *line, char **content);
char			**add_executable(char **envp, char *path);
unsigned long	ft_strlen_char(const char *str, char c);
void			exec_bin_unique(t_cmd *cmd, char **envp, t_obj *obj);
void			fork_child(t_obj *obj, t_cmd *cmd, int *tabfd, int i);
void			closefd(int tabfd[], int nbpipe);
void			redirectsimple(t_list **tmp, t_cmd **cmd);
void			newcmd(t_cmd **cmd);
void			replacedollar_tools1(char *line, char *tofind);
int				replacedollar_tools2(char *tofind, char *buff, int *j);
int				replacedollar_tools3(t_obj *obj, char *tofind, char \
	*buff, int *j);
int				replacedollar_tools4(char *tofind, char *buff, int *j);
int				myprompt2(t_obj *obj, char *line, t_list *list);
void			myexitd(t_obj *obj);
void			reallocbuff(t_obj *obj, int len, int index);
void			replacedollarbistools1(char *line, char *tofind, int *i);
int				replacedollarbistools2(t_obj *obj, char *tofind, int *j);
int				replacedollarbistools3(t_obj *obj, char *tofind, int *j);
int				replacedollarbistools4(t_obj *obj, char *tofind, int *j);
void			pipemulti_error(void);
void			parse_exit(t_obj *obj, t_cmd *cmd);
void			sort_env(char **envp, int env_len);
void			check_number_arg_cd(t_obj *obj, t_cmd *cmd);
void			env_pwd(t_obj *obj, char *name);
void			print_error(char *builtin, char *cmd, char *msg_error);
void			myctrlsignal(int sig);
void			fork_child_exec_bin(t_obj *obj, t_cmd *cmd,
					char *bin, char **envp);
void			fork_father_exec_bin(t_obj *obj, pid_t pid, int *status);
void			status_sigint(t_obj *obj);

#endif
