/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_bzero.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:11:38 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/26 16:25:31 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_bzero(void *s, size_t n)
{
	unsigned char	*cpy;

	cpy = s;
	while (n > 0)
	{
		*cpy = 0;
		cpy++;
		n--;
	}
}

/* void print_memory(const void *mem, size_t n) {
    const unsigned char *bytes = (const unsigned char *)mem;
    for (size_t i = 0; i < n; ++i)
        printf("%02x ", bytes[i]);
    printf("\n");
}

void run_test(const char *test_name, const void *input
, size_t size, size_t bzero_len) {
    void *real_buf = malloc(size);
    void *test_buf = malloc(size);
    memcpy(real_buf, input, size);
    memcpy(test_buf, input, size);

    bzero(real_buf, bzero_len);
    ft_bzero(test_buf, bzero_len);

    if (memcmp(real_buf, test_buf, size) == 0) {
        printf("✅ %s passed\n", test_name);
    } else {
        printf("❌ %s failed\n", test_name);
        printf("Expected: ");
        print_memory(real_buf, size);
        printf("Got     : ");
        print_memory(test_buf, size);
    }

    free(real_buf);
    free(test_buf);
}

int main() {
    char data1[] = "Hello, World!";
    char data2[] = "1234567890";
    char data3[] = "";
    char data4[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    char data5[] = "AlreadyZeroed";

    run_test("Full string zero", data1, sizeof(data1), sizeof(data1));
    run_test("Partial string zero", data2, sizeof(data2), 5);
    run_test("Zero length", data3, sizeof(data3), 0);
    run_test("Exact buffer size", data4, sizeof(data4), 10);
    run_test("Zero part of zeroed", data5, sizeof(data5), 0);

    return 0;
} */