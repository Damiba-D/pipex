/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isascii.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 13:06:17 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/18 16:08:03 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isascii(int c)
{
	if (!(c >= '\0' && c <= 127))
		return (0);
	return (1);
}

/* void run_test(const char *test_name, int input) {
    int expected = isascii(input);
    int result = ft_isascii(input);

    if ((expected && result) || (!expected && !result)) {
        printf("✅ %s (%d) passed\n", test_name, input);
    } else {
        printf("❌ %s (%d) failed | Expected: %d, Got: %d\n",
               test_name, input, expected, result);
    }
}

int main() {
    // Standard ASCII range
    for (int c = 0; c <= 127; c++) {
        char label[25];
        sprintf(label, "ASCII %d", c);
        run_test(label, c);
    }

    // Out-of-range values
    run_test("ASCII 128", 128);
    run_test("ASCII 255", 255);
    run_test("Negative -1", -1);
    run_test("Negative -42", -42);

    return 0;
} */