/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils5.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jporta <jporta@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/27 16:51:56 by jporta            #+#    #+#             */
/*   Updated: 2022/06/01 22:39:59 by jporta           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	statuschecker(int tmp)
{
	int	aux;

	aux = 0;
	if (tmp == 32512)
		aux = 127;
	if (WIFSIGNALED(tmp))
		aux = 128 + tmp;
	if (tmp == 256)
		aux = 1;
	if (aux != 0 && g_cmd_status != 127)
		g_cmd_status = aux;
}

void	freemat(char **mat)
{
	int	i;

	i = -1;
	while (mat[++i])
		free(mat[i]);
	free(mat);
}

char	*getlineinenv(t_list *list, int i)
{
	int	j;

	j = 0;
	while (++j < i)
		list = list->next;
	return (list->content);
}

void	freeeverything(t_minib *minilst)
{
	ft_lstclear(minilst->envp, free);
	ft_lstclear(minilst->exp, free);
	freecmds(minilst);
	free(minilst->pwd);
}

char	*strchecker(char *s1, char *s2)
{
	char	*str;

	if (!s1)
	{
		str = ft_strdup(s2);
		free(s2);
		return (str);
	}
	if (!s2)
	{
		str = ft_strdup(s1);
		free(s1);
		return (str);
	}
	return (NULL);
}
