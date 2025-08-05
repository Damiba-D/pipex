/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/11 18:15:20 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/18 16:07:06 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	return (ft_isalpha(c) || ft_isdigit(c));
}

/* void run_test(const char *test_name, int input) {
    int expected = isalnum(input);
    int result = ft_isalnum(input);

    if ((expected && result) || (!expected && !result)) {
        printf("✅ %s (%d) passed\n", test_name, input);
    } else {
        printf("❌ %s (%d) failed | Expected: %d, Got: %d\n",
               test_name, input, expected, result);
    }
}

int main() {
    // Digits
    for (int c = '0'; c <= '9'; c++) {
        char label[20];
        sprintf(label, "Digit '%c'", c);
        run_test(label, c);
    }

    // Uppercase
    for (int c = 'A'; c <= 'Z'; c++) {
        char label[20];
        sprintf(label, "Upper '%c'", c);
        run_test(label, c);
    }

    // Lowercase
    for (int c = 'a'; c <= 'z'; c++) {
        char label[20];
        sprintf(label, "Lower '%c'", c);
        run_test(label, c);
    }

    // Symbols
    run_test("Symbol '!'", '!');
    run_test("Symbol '@'", '@');
    run_test("Space", ' ');
    run_test("Newline", '\n');

    // Extended ASCII
    run_test("Extended ASCII 128", 128);
    run_test("Extended ASCII 255", 255);

    // Negative input
    run_test("Negative -1", -1);
    run_test("Negative -42", -42);

    return 0;
} */
