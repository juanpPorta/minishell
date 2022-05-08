/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils2.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/15 13:28:24 by jsanfeli          #+#    #+#             */
/*   Updated: 2022/05/05 18:52:37 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	*fuckeveryting(t_list *list)
{
	void *kk;

	kk = list->next;
	list->next = NULL;
	free(list->content);
	free(list);
	return(kk);
}

int getgoodpositionexp(t_list *list, char *add)
{
	int i;
	int j;
	char *aux;
	char *tmp;

	j = 0;
	i = ft_lstsize(list);
	aux = getnamevariable(add);
	while(j < i)
	{
		tmp = getnamevariable(list->content);
		if(strcmp(aux, tmp) < 0)
		{
			free(aux);
			free(tmp);
			return(j);
		}
		free(tmp);
		list = list->next;
		j++;
	}
	free(aux);
	return(j);
}

char	*getnamevariable(char *add)
{
	int i;
	char *kk;

	i = 0;
	while(add[i] && add[i] != '=')
		i++;
	kk = ft_substr(add, 0, i);
	return(kk);
}

int		itsinenv(char *add, t_list *list)
{
	int i;
	int j;
	char *str;
	char *tmp;
	void *kk;

	j = 0;
	kk = list;
	i = ft_lstsize(list);
	tmp = getnamevariable(add);
	while(j < i)
	{
		str = getnamevariable(list->content);
		if(!strcmp(str, tmp))
		{
			free(tmp);
			free(str);
			list = kk;
			return(-1);
		}
		free(str);
		list = list->next;
		j++;
	}
	free(tmp);
	list = kk;
	return(1);
}

void	freecmds(t_minib *minilst)
{
	int i;

	i = 0;
	if(minilst->cmdnum != 0)
	{
		while(i < minilst->cmdnum)
		{
			if(minilst->cmds[i].cmd)
				free(minilst->cmds[i].cmd);
			if(minilst->cmds[i].args)
				free(minilst->cmds[i].args);
			if(minilst->cmds[i].filein != STDIN_FILENO)
				close(minilst->cmds[i].filein);
			if(minilst->cmds[i].fileout != STDOUT_FILENO)
				close(minilst->cmds[i].fileout);
			i++;
		}
		free(minilst->cmds);
		unlink(".hide");
		minilst->cmdnum = 0;
	}
}

void	freeeverything(t_minib *minilst)
{
	
	ft_lstclear(minilst->envp, free);
	ft_lstclear(minilst->exp, free);
	freecmds(minilst);
	free(minilst->pwd);
}
