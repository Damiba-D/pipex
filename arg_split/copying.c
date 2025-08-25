/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copying.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:03:20 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/25 12:03:51 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_split.h"

static void	cpy_in_quote(char *dst, char *s, int *i, int *k)
{
	*i += 1;
	while (s[*i] && s[*i] != '\'')
	{
		dst[*k] = s[*i];
		*i += 1;
		*k += 1;
	}
	*i += 1;
}

/* Copy token into arr[j], removing quotes/escapes */
static void	copy_token(char *dst, char *s, int *i)
{
	int	k;

	k = 0;
	while (s[*i] && s[*i] != ' ')
	{
		if (s[*i] == '\'')
			cpy_in_quote(dst, s, i, &k);
		else if (s[*i] == '\\' && s[*i + 1])
		{
			dst[k++] = s[*i + 1];
			*i += 2;
		}
		else
		{
			if (s[*i] == '\\' && !s[*i + 1])
				dst[k++] = ' ';
			else
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
