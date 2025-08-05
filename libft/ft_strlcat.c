/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 18:26:52 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/18 19:47:49 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dest, const char *src, size_t size)
{
	unsigned int	i;
	unsigned int	dest_len;
	unsigned int	src_len;

	i = 0;
	dest_len = 0;
	while (dest[dest_len] != '\0' && dest_len < size)
		dest_len++;
	src_len = ft_strlen(src);
	if (size == 0)
		return (ft_strlen(src));
	while (src[i] != '\0' && dest_len + i + 1 < size)
	{
		dest[dest_len + i] = src[i];
		i++;
	}
	if (dest_len + i < size)
		dest[dest_len + i] = '\0';
	return (dest_len + src_len);
}

/* #define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

typedef struct {
    char dest[100];
    char src[100];
    size_t size;
} t_test_case;

int main(void)
{
    t_test_case tests[] = {
        {"Hello", " World", 20},
        {"Hello", " World", 11},
        {"Hello", " World", 10},
        {"Hello", " World", 5},
        {"", "abc", 4},
        {"abc", "", 10},
        {"", "", 1},
        {"abc", "def", 0},
        {"abc", "def", 3},
        {"abc", "def", 6},
        {"abc", "def", 7},
        {"abc", "def", 100},
        {"a", "bcdefghijklmnopqrstuvwxyz", 30},
        {"Short", "ThisIsAVeryLongString", 10},
        {"", "VeryLongSourceThatDoesntFit", 5},
        {"", "VeryLongSourceThatDoesntFit", 1},
    };

    size_t num_tests = sizeof(tests) / sizeof(tests[0]);
    unsigned int passed = 0;

    printf("Testing ft_strlcat vs strlcat:\n\n");

    for (size_t i = 0; i < num_tests; i++) {
        char dest1[100], dest2[100];
        strcpy(dest1, tests[i].dest);
        strcpy(dest2, tests[i].dest);

        size_t real = strlcat(dest1, tests[i].src, tests[i].size);
        size_t custom = ft_strlcat(dest2, tests[i].src, tests[i].size);

        int same_result = real == custom;
        int same_string = strcmp(dest1, dest2) == 0;

        if (same_result && same_string) {
            printf(GREEN "[OK]" RESET "    
			Test %2zu | size: %2zu | \"%s\" + \"%s\"\n",
                   i + 1, tests[i].size, tests[i].dest, tests[i].src);
            passed++;
        } else {
            printf(RED "[FAIL]" RESET "  
			Test %2zu | size: %2zu | \"%s\" + \"%s\"\n",
                   i + 1, tests[i].size, tests[i].dest, tests[i].src);
            printf("         Return: expected %zu, got %zu\n", real, custom);
            printf("         Result: expected 
			\"%s\", got \"%s\"\n\n", dest1, dest2);
        }
    }

    printf("\nSummary: %u/%zu tests passed\n", passed, num_tests);
    return (passed == num_tests) ? 0 : 1;
} */
