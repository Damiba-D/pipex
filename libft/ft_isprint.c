/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isprint.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/29 17:43:05 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/18 15:47:43 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isprint(int c)
{
	if (!(c >= ' ' && c <= '~'))
	{
		return (0);
	}
	return (1);
}

/* void run_test(const char *test_name, int input) {
    int expected = isprint(input);
    int result = ft_isprint(input);

    if ((expected && result) || (!expected && !result)) {
        printf("✅ %s (%d) passed\n", test_name, input);
    } else {
        printf("❌ %s (%d) failed | Expected: %d, Got: %d\n",
               test_name, input, expected, result);
    }
}

int main() {
    // Printable ASCII range: 32 (space) to 126 (~)
    for (int c = 32; c <= 126; c++) {
        char label[25];
        sprintf(label, "Printable '%c'", c);
        run_test(label, c);
    }

    // Non-printable: 0–31 and 127
    for (int c = 0; c < 32; c++) {
        char label[25];
        sprintf(label, "Non-printable %d", c);
        run_test(label, c);
    }
    run_test("Non-printable 127", 127);

    // Out-of-range
    run_test("Extended ASCII 128", 128);
    run_test("Extended ASCII 255", 255);
    run_test("Negative -1", -1);
    run_test("Negative -50", -50);

    return 0;
} */