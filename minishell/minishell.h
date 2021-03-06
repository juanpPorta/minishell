/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 17:55:21 by jporta            #+#    #+#             */
/*   Updated: 2022/06/01 22:40:13 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//Header files
# include <stdlib.h>
# include <stdio.h>
# include <fcntl.h>
# include <unistd.h>
# include "libft/libft.h"
# include <readline/readline.h>
# include <readline/history.h>

# define ALIEN  "👽"
# define SKULL	"🦠"
# define FLAME	"🔥"
# define PATH_TO_TMP	"/tmp/"
# define BLUE_BOLD "\e[1;34m"
# define GREEN_BOLD "\e[1;32m"
# define MAG_BOLD "\e[1;35m"
# define RED_BOLD "\e[1;31m"
# define UNSET "\033[0m"
# define CYAN "\e[0;36m"

int	g_cmd_status;

typedef struct s_cmds
{
	char	*cmd;
	char	*args;
	int		filein;
	int		fileout;
	int		pid;
	int		fd[2];
}	t_cmds;

typedef struct s_minib
{
	t_cmds	*cmds;
	t_list	*envp;
	t_list	*exp;
	int		envindex;
	int		expindex;
	int		cmdnum;
	int		shlvl;
	char	*lastcmd;
	char	*pwd;
	char	*promt;
	char	**pths2;
}	t_minib;

//MINISHELLSTRUCTURE

char	**getdonexp(char **envp, int i);
void	prepbasics(t_minib *minilst, char **envp);
int		prepline(char *line, t_minib *minilst);
void	checkeverything(char *line, t_minib *minilst);

//BUILTINS

int		checkforexit(char *cmd, char *arg, t_minib *minilst);
int		checkforenv(char *cmd, t_list *envp, int fileout);
int		checkforexport(char *cmd, char *arg, t_minib *minilst, int fileout);
int		checkforcd(char *cmd, char *arg, t_minib *minilst, int fileout);
int		checkforunset(char *cmd, char *arg, t_minib *minilst);
int		checkforecho(char *cmd, char *arg, int fileout);
int		checkadd(char *add);
int		checkarg(char *arg);
char	**exportarg(char *cmd);
char	*do_real_arg(char *add);
int		checkarg(char *arg);
char	*strchecker(char *s1, char *s2);

//LEXER

int		ft_getlenname(char *line, int start);
char	*expanddollar(char *name, t_minib *minilst);
int		get_len(char *line, int a);
char	*checkredirect(char *line, int *filein, int *fileout);
int		morfeo(t_cmds *com, char **line);
char	*expander(char *line, t_minib *minilst, int i, int a);
char	**lexer(char *expanded);
int		countdollars(char *line);
char	*fillline(char *line, int *i);
int		openfilesredirect(char *line, int i, int *fileout);
int		openfilesappend(char *line, int i, int *fileout);
int		openfilesindirect(char *line, int i, int *filein);
int		openfilesheredoc(char *line, int i, int *filein);
int		ft_getlen(int i, char *line, int *filein);
char	*gettmp(int i, char *line);
int		ft_comprobapipe(char *expanded);
int		pipesin(char *expanded);

//SIGNALS

void	inputsignal(void);
void	rl_replace_line(const char *text, int clear_undo);

//UTILS

int		getgoodpositionexp(t_list *list, char *add);
void	freeeverything(t_minib *minilst);
char	**createlstarray(t_list *lst, int index);
void	freemat(char **mat);
void	putinpos(t_list **list, int pos, void *newcontent);
void	delpos(t_list **list, int pos);
int		isinexp(t_list *list, char *line);
char	*getlineinenv(t_list *list, int i);
t_list	*createarraylst(char **array);
void	*fuckeveryting(t_list *list);
int		getvariable(char *add, t_list *list);
int		itsinenv(char *add, t_list *list);
int		getposinlst(t_list *list, char *line);
char	*getnamevariable(char *add);
int		checkadd(char *add);
int		num_matrix(char **matrix);
int		count_c(char *str, char c); //cuenta pipes validos
void	freecmds(t_minib *minilst);
char	*getaddedexp(char *add);
char	*freezerjoin(char *s1, char *s2);
char	*dopromt(t_minib *minilst);
char	*argsdone(char *arg);
char	*comparse(char *add);
void	getaddexp(char *add, t_minib *minilst);
int		checkforspaces(char *line);
int		checkinout(t_minib *minilst);
int		count_c(char *str, char c);
int		helpecho(char *line, int i);

//DEBUGGIN TOOLS

void	printlist(t_list *list, int fileout);
void	printlistexp(t_list *list, int fileout);
void	errorprintf(char *str);

//EXECUTER

void	executer(t_minib *minilst, int i, int num);
char	*path(char *cmd, char **envp);
void	ft_errorpipex(int index);
void	simba(t_minib *minilst, int i );
void	ejecucion(t_minib *minilst, int i, int num, int flag);
void	first_child(t_minib *minilst, int i);
void	statuschecker(int tmp);

#endif
