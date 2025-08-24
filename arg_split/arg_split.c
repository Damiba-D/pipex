/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   arg_split.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/08/24 15:11:23 by ddamiba           #+#    #+#             */
/*   Updated: 2025/08/24 17:04:42 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "arg_split.h"

/* Check if quotes are balanced (bash rejects unmatched single quotes) */
static int	has_unmatched_quote(char *s)
{
	int	i;
	int	in_quote;

	i = 0;
	in_quote = 0;
	while (s[i])
	{
		if (s[i] == '\\')
		{
			if (!s[i + 1])
				return (1);
			i += 2;
			continue ;
		}
		if (s[i] == '\'')
			in_quote = !in_quote;
		i++;
	}
	return (in_quote);
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
	if (!arr)
		return (NULL);
	i = ft_cpy_alloc(arr, s);
	if (i == -1)
		return (NULL);
	arr[i] = NULL;
	return (arr);
}

/* int	main(void)
{
	const char	*tests[] = {
	"echo hello world",        // basic split
	"echo    spaced   words",  // multiple spaces
	"echo '' empty",           // empty arg in quotes
	"echo 'it'\\''s fine'",    // tricky escaped quote style (C style literal)
	"echo 'unterminated",      // unmatched quote -> should set flag
	"echo a''b",               // empty quote in middle
	"echo '  spaces  '",       // quotes preserving spaces
	"echo mix'and'match",      // concatenated quoted + unquoted
	"'",                       // single lonely quote
	"echo a\\ b c",            // backslash escaping space
	"echo a\\\\b",             // escaped backslash (-> "a\\b")
	"echo 'a\\b'",             // backslash inside single quotes (literal)
	"echo \\'quoted\\'",       // escaped single quotes outside
	"echo abc\\",              // backslash at end of input
	"echo \"double quotes?\"", 
	// if you extend later (currently treated literally)
	"echo one\\ two\\ three",  // multiple escaped spaces
	"echo ''",                 // just an empty quoted string
	"   echo   leading",       // leading spaces before command
	"echo trailing   ",        // trailing spaces after arg
	"echo 'multi word arg' x", // quoted arg + unquoted arg
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