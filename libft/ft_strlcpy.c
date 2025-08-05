/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 16:59:16 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/21 17:58:19 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

/* #define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

typedef struct {
    char src[100];
    size_t size;
} t_test_case;

int main(void)
{
    t_test_case tests[] = {
        {"Hello", 10},
        {"Hello", 6},
        {"Hello", 5},
        {"Hello", 4},
        {"Hello", 1},
        {"Hello", 0},
        {"", 10},
        {"", 0},
        {"Longer source string", 20},
        {"Longer source string", 5},
        {"a", 2},
        {"a", 1},
        {"a", 0},
        {"This is a very very long string that won't fit", 10},
    };

    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    unsigned int passed = 0;

    printf("Testing ft_strlcpy vs strlcpy:\n\n");

    for (size_t i = 0; i < num_tests; i++) {
        char dest1[100] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";
        char dest2[100] = "XXXXXXXXXXXXXXXXXXXXXXXXXXXXXXXX";

        size_t real = strlcpy(dest1, tests[i].src, tests[i].size);
        size_t custom = ft_strlcpy(dest2, tests[i].src, tests[i].size);

        int same_result = real == custom;
        int same_string = strcmp(dest1, dest2) == 0;

        if (same_result && same_string) {
            printf(GREEN "[OK]" RESET "    Test %2zu | 
			size: %2zu | src: \"%s\"\n",
                   i + 1, tests[i].size, tests[i].src);
            passed++;
        } else {
            printf(RED "[FAIL]" RESET "  Test %2zu | size: %2zu | src: \"%s\"\n",
                   i + 1, tests[i].size, tests[i].src);
            printf("         Return: expected %zu, got 
			%zu\n", real, custom);
            printf("         Result: expected \"%s\", got 
			\"%s\"\n\n", dest1, dest2);
        }
    }

    printf("\nSummary: %u/%zu tests passed\n", passed, num_tests);
    return (passed == num_tests) ? 0 : 1;
} */