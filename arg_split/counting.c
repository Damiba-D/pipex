/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   counting.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:00:37 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/24 16:37:02 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_split.h"

/* handle quotes: toggle in_quote and mark word started */
static void	handle_quote(char *s, int i, int *in_quote, int *in_word)
{
	if (s[i] == '\'' && (i == 0 || s[i - 1] != '\\'))
	{
		if (!*in_quote)
			*in_word = 1;
		*in_quote = !*in_quote;
	}
}

/* handle space outside quotes: maybe end a word */
static void	handle_space(char c, int in_quote, int *in_word, int *count)
{
	if (!in_quote && c == ' ')
	{
		if (*in_word)
		{
			(*count)++;
			*in_word = 0;
		}
	}
}

unsigned int	count_args(char *s)
{
	int	i;
	int	count;
	int	in_word;
	int	in_quote;

	i = 0;
	count = 0;
	in_word = 0;
	in_quote = 0;
	while (s[i])
	{
		handle_quote(s, i, &in_quote, &in_word);
		handle_space(s[i], in_quote, &in_word, &count);
		if (!in_quote && s[i] != ' ' && s[i] != '\'')
			in_word = 1;
		i++;
	}
	if (in_word)
		count++;
	return (count);
}

/* Compute arg length following quoting rules */
void	arg_len(char *s, int *i, int *len)
{
	int	in_quote;

	in_quote = 0;
	while (s[*i] && (in_quote || (s[*i] != ' ')))
	{
		if (s[*i] == '\'' && (in_quote || s[*i + 1] != '\0'))
		{
			in_quote = !in_quote;
			*i += 1;
			continue ;
		}
		if (!in_quote && s[*i] == '\\' && s[*i + 1])
		{
			*len += 1;
			*i += 2;
		}
		else
		{
			*len += 1;
			*i += 1;
		}
	}
}
