/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:47:05 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/23 14:07:44 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static void	count_apost(char *s, int *i, int *count)
{
	int	j;

	j = *i;
	while (s[++j])
	{
		if (s[j] == '\'')
		{
			*i = j + 1;
			*count += 1;
			break ;
		}
	}
}

static unsigned int	count_args(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
			count_apost(s, &i, &count);
		if (s[i] == '\0')
			break ;
		if (s[i] != ' ' && (i == 0 || s[i - 1] == ' '))
			count++;
		i++;
	}
	return (count);
}

static void	arg_len(char *s, int *i, int *len)
{
	if (s[*i] == '\'')
	{
		*i += 1;
		while (s[*i] && s[*i] != '\'')
		{
			*i += 1;
			*len += 1;
		}
		if (s[*i] == '\'')
			*i += 1;
	}
	else
	{
		while (s[*i] != ' ' && s[*i])
		{
			*i += 1;
			*len += 1;
		}
	}
}

static int	ft_cpy_alloc(char **arr, char *s)
{
	int	i;
	int	j;
	int	len;
	int	start;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		len = 0;
		while (s[i] == ' ' && s[i])
			i++;
		start = i;
		arg_len(s, &i, &len);
		if (len == 0 && s[start] != '\'')
			break ;
		if (s[start] == '\'')
			start++;
		arr[j] = (char *)malloc((len + 1) * sizeof(char));
		if (arr[j] == NULL)
			return (free_arr(arr), -1);
		ft_strlcpy(arr[j], s + start, len + 1);
		j++;
	}
	return (j);
}

char	**arg_split(char *s)
{
	char	**arr;
	int		i;

	if (s == NULL)
		return (NULL);
	arr = (char **)malloc(((count_args(s) + 1) * sizeof(char *)));
	if (arr == NULL)
		return (NULL);
	i = ft_cpy_alloc(arr, s);
	if (i == -1)
		return (NULL);
	arr[i] = NULL;
	return (arr);
}

/* int main(int argc, char **argv)
{
	(void)argc;
	char **arr = arg_split(argv[1]);
	int i = 0;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
	free_arr(arr);
} */