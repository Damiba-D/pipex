/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:27:51 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/26 17:45:41 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s) + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s) + i);
	return (NULL);
}

/* #include <stdio.h>
#include <string.h>

// Color codes
#define GREEN   "\033[0;32m"
#define RED     "\033[0;31m"
#define YELLOW  "\033[1;33m"
#define RESET   "\033[0m"

// Prototype of your custom function
char *ft_strchr(const char *s, int c);

void test_strchr(const char *s, int c) {
    char *expected = strchr(s, c);
    char *actual = ft_strchr(s, c);

    if (expected != actual) {
        printf(RED "[ft_strchr] FAILED: strchr(\"%s\", '%c')\n" RESET, s, c);
        printf(YELLOW "    Expected: %s\n" RESET, expected ? expected : "NULL");
        printf(YELLOW "    Got     : %s\n\n" RESET, actual ? actual : "NULL");
    } else {
        printf(GREEN "[ft_strchr] OK: strchr(\"%s\", '%c') → \"%s\"\n" RESET,
               s, c, expected ? expected : "NULL");
    }
}

int main(void) {
    const char *tests[] = {
        "hello world",
        "42 Network",
        "abcabcabc",
        "",
        "a",
        "a\0b\0c"
    };
    int chars[] = {
        'a', 'z', ' ', '\0', 'o', 'N'
    };

    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    size_t num_chars = sizeof(chars) / sizeof(chars[0]);

    for (size_t i = 0; i < num_tests; ++i) {
        for (size_t j = 0; j < num_chars; ++j) {
            test_strchr(tests[i], chars[j]);
        }
    }

    return 0;
} */
