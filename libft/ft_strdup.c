/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/08 14:58:45 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/26 17:22:25 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s1)
{
	char		*ptr;
	size_t		len;

	len = ft_strlen((char *)s1) + 1;
	ptr = (char *)malloc(len * sizeof(char));
	if (ptr == NULL)
		return (NULL);
	ft_strlcpy(ptr, (char *)s1, len);
	return (ptr);
}

/* void run_test(const char *input) {
    char *expected = strdup(input);
    char *actual = ft_strdup(input);
    int passed = 1;

    if (!expected || !actual) {
        if (expected != actual) {
            passed = 0;
        }
    } else if (strcmp(expected, actual) != 0 || expected == actual) {
        passed = 0;
    }

    if (!passed) {
        printf("FAIL: input = \"%s\"\n", input);
        printf("  Expected (strdup): \"%s\"\n", expected ? expected : "NULL");
        printf("  Actual (ft_strdup): \"%s\"\n", actual ? actual : "NULL");
        if (expected == actual) {
            printf("  ❗ Returned pointer is the same as input 
			— should be a new allocation\n");
        }
    } else {
        printf("PASS: input = \"%s\"\n", input);
    }

    free(expected);
    free(actual);
}

int main(void) {
    run_test("hello world");
    run_test("");
    run_test("   ");                     // spaces only
    run_test("1234567890");
    run_test("!@#$%^&*()_+");
    run_test("A\nB\tC");       // with escape characters
    run_test("こんにちは"); // UTF-8 (assuming your function handles it as bytes)
    run_test("💡🔥🚀");        // emojis
    run_test(NULL); // undefined behavior, just to see what happens (comment out

    return 0;
}
 */
