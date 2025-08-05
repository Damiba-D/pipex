/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:43:03 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/21 15:47:23 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	unsigned int	i;
	unsigned char	*cpy;

	cpy = (unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (cpy[i] == (unsigned char)c)
			return ((void *)s + i);
		i++;
	}
	return (NULL);
}

/* void print_result(const char *label, 
void *expected, void *got, const char *base) {
    if (expected == got) {
        printf("✅ %s passed\n", label);
    } else {
        printf("❌ %s failed\n", label);
        printf("Expected: %p (offset %ld)\n", expected, (char *)expected - base);
        printf("Got     : %p (offset %ld)\n", got, (char *)got - base);
    }
}

void run_test(const char *test_name, const void *haystack, int c, size_t n) {
    void *real_result = memchr(haystack, c, n);
    void *test_result = ft_memchr(haystack, c, n);

    print_result(test_name, real_result, test_result, (const char *)haystack);
}

int main() {
    char buffer1[] = "Hello, World!";
    char buffer2[] = "abc\0def";
    char buffer3[] = {0, 1, 2, 3, 4, 5};

    run_test("Find 'o' in buffer1", buffer1, 'o', sizeof(buffer1));
    run_test("Find 'W' in buffer1", buffer1, 'W', 5); // 'W' after 5th byte
    run_test("Find null terminator in buffer1", buffer1, '\0', sizeof(buffer1));
    run_void print_result(const char *label, 
void *expected, void *got, const char *base) {
    if (expected == got) {
        printf("✅ %s passed\n", label);
    } else {
        printf("❌ %s failed\n", label);
        printf("Expected: %p (offset %ld)\n", expected, (char *)expected - base);
        printf("Got     : %p (offset %ld)\n", got, (char *)got - base);
    }
}

void run_test(const char *test_name, const void *haystack, int c, size_t n) {
    void *real_result = memchr(haystack, c, n);
    void *test_result = ft_memchr(haystack, c, n);

    print_result(test_name, real_result, test_result, (const char *)haystack);
}

int main() {
    char buffer1[] = "Hello, World!";
    char buffer2[] = "abc\0def";
    char buffer3[] = {0, 1, 2, 3, 4, 5};

    run_test("Find 'o' in buffer1", buffer1, 'o', sizeof(buffer1));
    run_test("Find 'W' in buffer1", buffer1, 'W', 5); // 'W' after 5th byte
    run_test("Find null terminator in buffer1", buffer1, '\0', sizeof(buffer1));
    run_test("Find '\\0' in buffer2", buffer2, '\0', sizeof(buffer2));
    run_test("Find 'd' in buffer2", buffer2, 'd', sizeof(buffer2));
    run_test("Find byte 3 in buffer3", buffer3, 3, 6);
    run_test("Find byte 99 in buffer3", buffer3, 99, 6); // doesn't exist
    run_test("Zero-length search", buffer1, 'o', 0);

    return 0;
}test("Find '\\0' in buffer2", buffer2, '\0', sizeof(buffer2));
    run_test("Find 'd' in buffer2", buffer2, 'd', sizeof(buffer2));
    run_test("Find byte 3 in buffer3", buffer3, 3, 6);
    run_test("Find byte 99 in buffer3", buffer3, 99, 6); // doesn't exist
    run_test("Zero-length search", buffer1, 'o', 0);

    return 0;
} */