/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printer.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omoudni <omoudni@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/08 10:33:29 by omoudni           #+#    #+#             */
/*   Updated: 2022/06/09 22:23:03 by omoudni          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include "libft/libft.h"

void	print_all_everything(t_big_token **b_tokens, t_token **tokens)
{
	t_big_token	*tmp_b;
	int			i;
	int			j;

	tmp_b = *b_tokens;
	j = 1;
	i = 1;
	while (tmp_b)
	{
		printf("\nWelcome in the parent: %d\n", i);
		printf("\n");
		print_s_tokens(tokens, tmp_b->ind_tok_start, tmp_b->length);
		printf("\n");
		if (tmp_b->child)
			print_all_child(&(tmp_b->child), tokens, i, j);
		else
			printf("\nje n'ai pas de child moi!!\n");
		tmp_b = tmp_b->sibling;
		i++;
		printf("---------------");
	}
}

void	print_all_child(t_big_token **b_tokens, t_token **tokens, int i, int j)
{
	t_big_token	*tmp_b;

	tmp_b = *b_tokens;
	while (tmp_b)
	{
			printf("\nWelcome to the bunch of childs of order: %d of the parent: %d\n", j, i);
		print_b_tokens(&tmp_b, tokens, i, j);
		printf("\n");
		tmp_b = tmp_b->child;
		j++;
	}
}

void	print_b_tokens(t_big_token **b_tokens, t_token **tokens, int i, int j)
{
	t_big_token	*tmp_b;
	t_token		*tmp_s;

	tmp_b = *b_tokens;
	tmp_s = *tokens;
	int	k;
	k =0;
	while (tmp_b)
	{
		printf("   --->>    ");
		print_s_tokens(&tmp_s, tmp_b->ind_tok_start, tmp_b->length);
		printf("\n");
		printf("It's type is: %d\n", tmp_b->type);
		printf("It's start is: %d\n", tmp_b->ind_tok_start);
		printf("It's length is: %d\n", tmp_b->length);
		printf("It's par_pam is: %d\n", tmp_b->par);
		printf("It's rank is: %d\n", k);
		printf("It's fd_in is: %d\n", tmp_b->fdin);
		printf("It's fd_out %d\n", tmp_b->fdout);
		if (tmp_b->parent)
		printf("It's got a PARENT!!\n");
		else if (!(tmp_b->parent))
		printf("It's an ORPHAN!!\n");
		if (k && tmp_b->child)
			print_all_child(&tmp_b->child, tokens, i, j + 1);
		tmp_b = tmp_b->sibling;
		k++;
	}
}

void	print_s_tokens(t_token **tokens, int start, int length)
{
	int			i;
	t_big_token	*tmp_b;
	t_token		*tmp_s;

	tmp_s = *tokens;
	i = 0;
	move_tok_2_ind(&tmp_s, start);
	while (i < length && tmp_s)
	{
		printf("%s", tmp_s->value);
		// printf("%d\n", tmp_s->token);
		tmp_s = tmp_s->next;
		i++;
	}
	// printf("\n");
}