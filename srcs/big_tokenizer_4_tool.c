/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   big_tokenizer_4_tool.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 14:45:15 by omoudni           #+#    #+#             */
/*   Updated: 2022/06/28 19:29:39 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	rd_inout_type(char *str, int *type_red)
{
	if (ft_strlen(str) == 1 && !ft_strncmp(str, "<", 1))
		(*type_red) = 1;
	if (ft_strlen(str) == 2 && !ft_strncmp(str, "<<", 2))
		(*type_red) = 2;
	if (ft_strlen(str) == 1 && !ft_strncmp(str, ">", 1))
		(*type_red) = 3;
	if (ft_strlen(str) == 2 && !ft_strncmp(str, ">>", 2))
		(*type_red) = 4;
}

int	check_if_piped(t_big_token **tmp_b, int ind, t_info *info, int len)
{
	t_token	*tmp;
	int		i;

	(void) tmp_b;
	tmp = info->tokens;
	i = 0;
	move_tok_2_ind(&tmp, ind);
	while (tmp && i < len)
	{
		if (tmp->token == TOK_OPERATOR && ft_strlen(tmp->value) == 1
			&& !ft_strncmp("|", tmp->value, 1))
			return (1);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
