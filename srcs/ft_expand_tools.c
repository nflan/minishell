/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_expand_tools.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/07/01 13:12:19 by omoudni           #+#    #+#             */
/*   Updated: 2022/07/01 13:12:29 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	ft_count_q(char *str, char c, size_t *i, size_t *q)
{
	if (!str)
		return ;
	(*i)++;
	(*q)++;
	while (str[*i] && str[*i] != c)
		(*i)++;
}

size_t	ft_strlen_nq(char *str)
{
	size_t	i;
	size_t	q;

	i = 0;
	q = 0;
	if (!str)
		return (0);
	while (str[i])
	{
		if (str[i] == '\'' || str[i] == '\"')
			ft_count_q(str, str[i], &i, &q);
		else
			i++;
	}
	return (i - q);
}

void	ft_type(char c, int *t)
{
	if (c == '\'' && !*t)
		*t = 2;
	else if (c == '\'' && *t == 2)
		*t = 0;
	else if (c == '\"' && !*t)
		*t = 1;
	else if (c == '\"' && *t == 1)
		*t = 0;
}

char	*ft_strndup(char *str, int len)
{
	char	*ret;
	int		i;

	i = 0;
	if (!str)
		return (NULL);
	ret = ft_calloc(sizeof(char), len + 1);
	if (!ret)
		return (NULL);
	while (i < len && str[i])
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

char	*strjoin_4(char *str1, char *str2)
{
	char	*ret;

	ret = ft_strjoin(str1, str2);
	free(str1);
	return (ret);
}
