/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nflan <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/05/20 12:32:37 by nflan             #+#    #+#             */
/*   Updated: 2022/06/27 20:46:21 by nflan            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

int	ft_do_export(char *line)
{
	if (!line)
		return (0);
	while (*line++)
		if (*line == '=')
			return (1);
	return (0);
}

void	ft_export_new(t_env *env, t_env *tmp, char *line)
{
	tmp = ft_envnew(line);
	if (!tmp)
		return ;
	ft_envadd_back(&env, tmp);
}

void	ft_export_replace(t_env *env, char *line, int i, int j)
{
	free(env->value);
	env->value = NULL;
	if (j > i + 1)
		env->value = ft_substr(line, i + 1, j);
	if (!env->value)
		env->value = ft_strdup("");
}

void	ft_not_valid_id(char **args)
{
	int	i;
	int	j;

	i = 2;
	j = 0;
	if (args)
	{
		while (args[i])
		{
			j = 0;
			while (args[i][j])
			{
				if (!ft_isdigit(args[i][j]) && !ft_isalpha(args[i][j]))
				{
					ft_putstr_fd_3("minishell: export: `", args[i],
						"': not a valid identifier\n", 2);
					break ;
				}
				j++;
			}
			i++;
		}
	}
}

int	ft_export(t_info *info, t_big_token *b_tokens)
{
	t_env	*tmp;
	int		i;
	int		j;

	tmp = info->env;
	i = 0;
	if (!tmp || !b_tokens->cmd_args[0])
		return (1);
	if (ft_do_export(b_tokens->cmd_args[1]))
	{
		while (b_tokens->cmd_args[1][1] && b_tokens->cmd_args[1][i] != '=')
			i++;
		j = i + 1;
		while (b_tokens->cmd_args[1][j])
			j++;
		while (tmp && ft_strncmp(tmp->name, b_tokens->cmd_args[1], i + 1)
			!= -61)
			tmp = tmp->next;
		if (!tmp)
			ft_export_new(info->env, tmp, b_tokens->cmd_args[1]);
		else
			ft_export_replace(tmp, b_tokens->cmd_args[1], i, j);
	}
	ft_not_valid_id(b_tokens->cmd_args);
	return (0);
}
