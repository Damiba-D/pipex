/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copying.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:03:20 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/24 16:55:26 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_split.h"

/* Copy token into arr[j], removing quotes/escapes */
static void	copy_token(char *dst, char *s, int *i)
{
	int	in_quote;
	int	k;

	in_quote = 0;
	k = 0;
	while (s[*i] && (in_quote || s[*i] != ' '))
	{
		if (s[*i] == '\'' && (in_quote || s[*i + 1] != '\0'))
		{
			in_quote = !in_quote;
			*i += 1;
		}
		else if (!in_quote && s[*i] == '\\' && s[*i + 1])
		{
			dst[k++] = s[*i + 1];
			*i += 2;
		}
		else
		{
			dst[k++] = s[*i];
			*i += 1;
		}
	}
	dst[k] = '\0';
}

int	ft_cpy_alloc(char **arr, char *s)
{
	int	i;
	int	j;
	int	len;
	int	save;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == ' ')
			i++;
		if (!s[i])
			break ;
		save = i;
		len = 0;
		arg_len(s, &i, &len);
		arr[j] = malloc(len + 1 * sizeof(char));
		if (!arr[j])
			return (free_arr(arr), -1);
		i = save;
		copy_token(arr[j], s, &i);
		j++;
	}
	return (j);
}
