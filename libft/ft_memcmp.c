/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 16:25:47 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/21 17:42:36 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	size_t			i;
	unsigned char	*s1_cpy;
	unsigned char	*s2_cpy;

	s1_cpy = (unsigned char *)s1;
	s2_cpy = (unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (s1_cpy[i] != s2_cpy[i])
			return (s1_cpy[i] - s2_cpy[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (s1_cpy[i] - s2_cpy[i]);
}

/* #include <stdio.h>
#include <string.h>

// Your function prototype
int ft_memcmp(const void *s1, const void *s2, size_t n);

void run_test(const char *test_name, const void *s1, const void *s2, size_t n) {
    int expected = memcmp(s1, s2, n);
    int result = ft_memcmp(s1, s2, n);

    int passed = ((expected == 0 && result == 0) || 
                  (expected < 0 && result < 0) || 
                  (expected > 0 && result > 0));

    if (passed) {
        printf("✅ %s passed\n", test_name);
    } else {
        printf("❌ %s failed | Expected: %d, Got: 
		%d\n", test_name, expected, result);
    }
}

int main() {
    // Same content
    run_test("Equal strings", "abcde", "abcde", 5);

    // Difference at beginning
    run_test("Diff at start", "zbcde", "abcde", 5);

    // Difference at end
    run_test("Diff at end", "abcdz", "abcde", 5);

    // Shorter length
    run_test("Short compare equal", "abcde", "abcde", 3);
    run_test("Short compare diff", "abcde", "abfde", 3);

    // With null characters in the middle
    char buf1[] = {'a', 'b', '\0', 'd', 'e'};
    char buf2[] = {'a', 'b', '\0', 'd', 'e'};
    char buf3[] = {'a', 'b', '\0', 'x', 'y'};
    run_test("Binary match with NUL", buf1, buf2, 5);
    run_test("Binary mismatch with NUL", buf1, buf3, 5);

    // Zero-length comparison
	char s[] = {-128, 0, 127, 0};
	char sCpy[] = {-128, 0, 127, 0};
    run_test("Libfttester", s, sCpy, 4);

    return 0;
} */