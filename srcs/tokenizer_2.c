/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_2.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/30 13:47:48 by omoudni           #+#    #+#             */
/*   Updated: 2022/06/27 15:32:41 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int add_tok_last(t_token **tok_list, t_tok_type tok_type, int length, int i)
{
	t_token *tmp;
	t_token *bef_last;
	//	int		rank_in_list;

	if (!*tok_list)
	{
		*tok_list = ft_create_token(tok_type, length, i);
		if (!*tok_list)
			return (ft_putstr_error("Error in create_token in add_tok_last in "));
		(*tok_list)->prev = NULL;
		//		rank_in_list = 0;
	}
	else
	{
		tmp = *tok_list;
		while (tmp->next)
			tmp = tmp->next;
		bef_last = tmp;
		bef_last->next = ft_create_token(tok_type, length, i);
		if (!*tok_list)
			return (ft_putstr_error("Error in create_token in add_tok_last in "));
		bef_last = bef_last->next;
		bef_last->prev = tmp;
		//		rank_in_list = 1;
	}
	//	init_tok_struct(tok_list, rank_in_list);
	return (0);
}

void add_tok_last_bis(t_token **tok_list, t_tok_type tok_type, int quoted, char *value)
{
	t_token *tmp;
	t_token *bef_last;

	if (!*tok_list)
	{
		*tok_list = create_tok_bis(tok_type, quoted, value);
		//	(*tok_list)->prev = NULL;
	}
	else
	{
		tmp = *tok_list;
		while (tmp->next)
			tmp = tmp->next;
		bef_last = tmp;
		bef_last->next = create_tok_bis(tok_type, quoted, value);
		bef_last = bef_last->next;
		bef_last->prev = tmp;
	}
	// init_tok_struct(tok_list, rank_in_list);
}

int	check_tok_type(t_tok_type tok_type)
{
if (tok_type != TOK_EXPANDER_OP && tok_type != TOK_EXPANDER_CL && tok_type != TOK_S_QUOTER && tok_type != TOK_D_QUOTER)
	return (1);
return (0);
}

int detect_tokens(t_token **tok_list, char *str)
{
	int i;
	unsigned int tok_type;
	int length;
	int start;

	i = 0;
	if (!str)
		return (ft_putstr_error("Command error in detect_tokens "));
	while (str[i])
	{
		length = 1;
		start = i;
		tok_type = get_real_tok_type(str[i], tok_list);
		i++;
		while (str[i] && check_tok_type(tok_type) && (get_real_tok_type(str[i], tok_list) == tok_type))
		{
			length++;
			i++;
		}
		if (tok_type == TOK_WORD_NULL_S || tok_type == TOK_WORD_NULL_D)
		{
			if (tok_type == TOK_WORD_NULL_S)
			{
			if (add_tok_last(tok_list, TOK_WORD_S_QUOTED, 0, start))
				return (ft_putstr_error("detect_tokens "));
				if (add_tok_last(tok_list, TOK_S_QUOTER, length, start))
					return (ft_putstr_error("detect_tokens "));
			}
			else
			{
			if (add_tok_last(tok_list, TOK_WORD_D_QUOTED, 0, start))
				return (ft_putstr_error("detect_tokens "));
				if (add_tok_last(tok_list, TOK_D_QUOTER, length, start))
					return (ft_putstr_error("detect_tokens "));
			}
		}
		else
		{
		if (add_tok_last(tok_list, tok_type, length, start))
			return (ft_putstr_error("detect_tokens "));
		}
	}
	return (0);
}

int fill_tok_value(t_token **tok, char *str)
{
	t_token *tmp;

	//	printf("(*tok) %p && str = %s\n", (*tok), str);
	if (!*tok || !str)
		return (1);
	tmp = *tok;
	while (tmp)
	{
		tmp->value = ft_strncpy(&(str[tmp->start]), tmp->length);
		if (!tmp->value)
			return (ft_putstr_error("Error in ft_strncpy in fill_tok_value"));
		tmp = tmp->next;
	}
	return (0);
}

char *ft_strncpy(char *str, int n)
{
	int i;
	char *ret;

	i = 0;
	if (!str)
		return (NULL);
	ret = ft_calloc(sizeof(char), n + 1);
	if (!ret)
		return (NULL);
	while (i < n)
	{
		ret[i] = str[i];
		i++;
	}
	return (ret);
}

void index_toks(t_token **tokens)
{
	int i;
	t_token *tmp;

	tmp = *tokens;
	i = 0;
	while (*tokens)
	{
		(*tokens)->index = i;
		(*tokens) = (*tokens)->next;
		i++;
	}
	*tokens = tmp;
}
