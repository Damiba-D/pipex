/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/22 20:47:05 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/24 01:49:29 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

/* static void	count_apost(char *s, int *i, int *count)
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
} */

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
		{
			while (s[i] != '\'')
				i++;
			count++;
			i++;
		}
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

static int	has_unmatched_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] == '\0')
				return (1);
		}
		if (s[i])
			i++;
	}
	return (0);
}

char	**arg_split(char *s, int *inv_arg)
{
	char	**arr;
	int		i;

	*inv_arg = 1;
	if (s == NULL)
		return (NULL);
	if (has_unmatched_quote(s))
	{
		*inv_arg = 2;
		return (NULL);
	}
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
	int flag;
	char **arr = arg_split(argv[1], &flag);
	printf("flag: %d\n", flag);
	if (arr == NULL)
		exit(1);
	int i = 0;
	while (arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		i++;
	}
	free_arr(arr);
} */

/* int	main(void)
{
	const char	*tests[] = {
		"echo hello world",        // basic split
		"echo    spaced   words",  // multiple spaces
		"echo '' empty",           // empty arg in quotes
		"echo 'it'\\''s fine'",     // tricky escaped quote style
		"echo 'unterminated",      // unmatched quote -> should set flag
		"echo a''b",               // empty quote in middle
		"echo '  spaces  '",       // quotes preserving spaces
		"echo mix'and'match",      // concatenated quoted + unquoted
		"'",
		NULL
	};
	int			t;
	char		**arr;
	int			flag;
	int			i;

	t = 0;
	while (tests[t])
	{
		printf("==== Test %d: [%s] ====\n", t + 1, tests[t]);
		arr = arg_split((char *)tests[t], &flag);
		printf("flag: %d\n", flag);
		if (arr)
		{
			i = 0;
			while (arr[i])
			{
				printf("arg[%d]: [%s]\n", i, arr[i]);
				i++;
			}
			free_arr(arr);
		}
		else
			printf("Parsing failed (NULL)\n");
		printf("\n");
		t++;
	}
	return (0);
} */
