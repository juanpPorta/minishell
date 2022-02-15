/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins0.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jsanfeli <jsanfeli@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/08 22:20:03 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/02/15 19:35:31 by jsanfeli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	checkforenv(char **line, t_list *envp)
{
	int i;

	i = -1;
	if (ft_strncmp(line[0], "env", ft_strlen(line[0])) == 0)
	{
		if(line[1])
		{
			printf("env: %s: No such file or directory\n", line[1]);
			return ;
		}
		printlist(envp);
	}
}

void	cd_update_env(int i[2], t_minib *minilst)
{
	char *tmp;

	delpos(minilst->envp, i[1]);
	putinpos(minilst->envp, i[1], ft_strjoin("OLDPWD=", getlineinenv(minilst->envp, i[0]) + 4));
	tmp = getcwd(NULL, 0);
	delpos(minilst->envp, i[0]);
	putinpos(minilst->envp, i[0], ft_strjoin("PWD=", tmp));
	free(tmp);
}

char	*check_pwd(char *str, int home, int opwd, t_minib *minilst)
{
	char	*s;

	s = NULL;
	if (!str)
	{
		if (home != -1)
			s = ft_strdup(getlineinenv(minilst->envp, home) + 5);
		else
			printf("minishell: cd: HOME not set\n");
	}
	else if(!ft_strncmp(str, "-", ft_strlen(str)))
	{
		if(opwd != -1)
		{
			s = ft_strdup(getlineinenv(minilst->envp, opwd) + 7);
			printf("%s\n", s);
		}
		else
			printf("minishell: cd: OLDPWD not set\n");
	}
	else
		s = ft_strdup(str);
	return (s);
}


void	checkforcd(char **line, t_minib *minilst)
{
	char	*str;
	int		i[2];

	if (ft_strncmp(line[0], "cd", ft_strlen(line[0])) != 0)
		return	;
	if (getposinlst(minilst->envp, "PWD") == -1)
	{
		minilst->pwd = getcwd(NULL, 0);
		putinpos(minilst->envp, 16, minilst->pwd);
	}
	i[0] = getposinlst(minilst->envp, "PWD");
	i[1] = getposinlst(minilst->envp, "OLDPWD");
	str = check_pwd(line[1], getposinlst(minilst->envp, "HOME"), getposinlst(minilst->envp, "OLDPWD"), minilst);
	if(chdir(str) == -1)
	{
		minilst->pwd = getcwd(NULL, 0);
		if(str)
			printf("minishell: cd: %s: No such file or directory\n", str);
	}
	else
		cd_update_env(i, minilst);
	free(str);
}

void checkforexit(char **line, t_minib *minilst)
{
	int		i;

	i = 0;
	if (ft_strncmp(line[0], "exit", ft_strlen(line[0])) == 0)
	{
		printf("exit\n");
		if (!line[1])
		{
			freeeverything(minilst);
			system("leaks minishell");
			exit(0);
		}
		if(line[2]) //SALIDA EN CASO DE MAS DE DOS ARGS
		{
			printf("minishell: exit: too many arguments\n");
			return ;
		}
		i = -1;
		while(line[1][++i])
		{
			if(ft_isdigit(line[1][i]) != 1)
			{
				printf("minishell: exit: %s: numeric argument required\n", line[1]);
				break ;
			}
		}
		freeeverything(minilst);
		exit(ft_atoi(line[1]));
	}
}