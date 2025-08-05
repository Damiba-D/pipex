/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 12:02:47 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/26 16:27:50 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	void	*ptr;

	if (nmemb == 0 || size == 0)
	{
		ptr = malloc(0);
		return (ptr);
	}
	if (nmemb > (INT_MAX / size))
		return (NULL);
	ptr = malloc(nmemb * size);
	if (ptr == NULL)
		return (NULL);
	ft_bzero(ptr, nmemb * size);
	return (ptr);
}

/* void print_memory(const void *mem, size_t n) {
    const unsigned char *bytes = (const unsigned char *)mem;
    for (size_t i = 0; i < n; ++i)
        printf("%02x ", bytes[i]);
    printf("\n");
}

void run_test(const char *test_name, size_t count, size_t size) {
    void *real_ptr = calloc(count, size);
    void *test_ptr = ft_calloc(count, size);

    size_t total_size = count * size;
    int passed = 1;

    if (count == 0 || size == 0) {
        // Rule: both must return non-NULL and be freeable
        if (!real_ptr || !test_ptr) {
            passed = 0;
        }
    } else {
        if ((real_ptr == NULL && test_ptr != NULL) 
		|| (real_ptr != NULL && test_ptr == NULL)) {
            passed = 0;
        } else if (real_ptr && test_ptr) {
            if (memcmp(real_ptr, test_ptr, total_size) != 0) {
                passed = 0;
            }
        }
    }

    if (passed) {
        printf("✅ %s passed\n", test_name);
    } else {
        printf("❌ %s failed\n", test_name);
        printf("Expected: ");
        if (real_ptr && total_size > 0) print_memory(real_ptr, total_size);
        else printf("Non-NULL or NULL pointer: %p\n", real_ptr);

        printf("Got     : ");
        if (test_ptr && total_size > 0) print_memory(test_ptr, total_size);
        else printf("Non-NULL or NULL pointer: %p\n", test_ptr);
    }

    free(real_ptr);
    free(test_ptr);
}

int main() {
    run_test("Normal allocation", 10, sizeof(int));
    run_test("Zero count", 0, sizeof(int));
    run_test("Zero size", 10, 0);
    run_test("Zero count and size", 0, 0);
    run_test("Large allocation", 1024, 1024);  // 1MB
    run_test("Char allocation", 15, sizeof(char));
    run_test("Struct size", 5, sizeof(struct { int a; char b; }));

    return 0;
} */