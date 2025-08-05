/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 15:19:36 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/25 11:56:39 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	unsigned char	*cpy;
	unsigned char	*clone;

	if ((dest == NULL || src == NULL) && n == 0)
		return (dest);
	cpy = (unsigned char *)dest;
	clone = (unsigned char *)src;
	while (n > 0)
	{
		*cpy = *clone;
		cpy++;
		clone++;
		n--;
	}
	return (dest);
}

/* int memcmp_safe(const void *a, const void *b, size_t n) {
    if (!a || !b) return a == b;
    return memcmp(a, b, n);
}

void print_bytes(const void *ptr, size_t n) {
    const unsigned char *bytes = (const unsigned char *)ptr;
    for (size_t i = 0; i < n; i++)
        printf("%02X ", bytes[i]);
    printf("\n");
}

void run_test(const void *src_data, size_t len, size_t n) {
    unsigned char *dst_std = malloc(len);
    unsigned char *dst_ft = malloc(len);
    if (!dst_std || !dst_ft) {
        printf("Memory allocation failed.\n");
        return;
    }

    // Initialize both destinations with something (so we can detect changes)
    memset(dst_std, 0xAA, len);
    memset(dst_ft, 0xAA, len);

    // Call memcpy only if src_data is not NULL or n == 0
    void *ret_std = NULL;
    if (src_data || n == 0)
        ret_std = memcpy(dst_std, src_data, n);

    void *ret_ft = ft_memcpy(dst_ft, src_data, n);

    int passed = memcmp_safe(dst_std, dst_ft, len) == 0 &&
             (ret_ft == dst_ft) &&
             (ret_std == dst_std);

    if (!passed) {
        printf("FAIL: memcpy(%zu bytes)\n", n);
        printf("  Expected: ");
        print_bytes(dst_std, len);
        printf("  Actual  : ");
        print_bytes(dst_ft, len);
        if (ret_ft != dst_ft)
            printf("  ❗ Return value is incorrect (should return dst)\n");
    } else {
        printf("PASS: memcpy(%zu bytes)\n", n);
    }

    free(dst_std);
    free(dst_ft);
}

int main(void) {
    char src1[] = "Hello, world!";
    char src2[] = "";
    char src3[] = "1234567890";

    run_test(src1, sizeof(src1), strlen(src1));
    run_test(src1, sizeof(src1), 5);
    run_test(src2, sizeof(src2), 0);              // Copy 0 bytes
    run_test(src2, sizeof(src2), strlen(src2));   // Copy empty string
    run_test(src3, sizeof(src3), 10);

    // Copy from NULL (undefined, but testing defensive behavior)
    run_test(NULL, 10, 0); // should not crash (0 bytes)
    run_test(NULL, NULL, 5); // uncommenting this will likely crash

    return 0;
} */