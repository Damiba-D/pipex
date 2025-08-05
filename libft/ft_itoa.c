/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 14:37:30 by ddamiba           #+#    #+#             */
/*   Updated: 2025/07/03 21:18:59 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_countdigit(long nb)
{
	int	count;

	if (nb < 0)
		nb *= -1;
	count = 1;
	while (nb > 9)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*ft_itoa(int n)
{
	char			*str;
	int				count;
	long			nb;

	nb = (long)n;
	count = ft_countdigit(nb);
	if (nb < 0)
		count++;
	str = (char *)malloc((count * sizeof(char)) + sizeof(char));
	if (str == NULL)
		return (NULL);
	if (nb < 0)
	{
		str[0] = '-';
		nb *= -1;
	}
	str[count--] = '\0';
	while (nb > 9 || count > 1)
	{
		str[count--] = (nb % 10) + '0';
		nb /= 10;
	}
	str[count] = (nb % 10) + '0';
	return (str);
}

/* void test_itoa(int input, const char *expected) {
    char *result = ft_itoa(input);

    if (!result) {
        if (!expected) {
            printf("PASS: ft_itoa(%d) == NULL (expected)\n", input);
        } else {
            printf("FAIL: ft_itoa(%d) == NULL (unexpected)\n", input);
        }
        return;
    }

    if (strcmp(result, expected) == 0) {
        printf("PASS: ft_itoa(%d) == \"%s\"\n", input, result);
    } else {
        printf("FAIL: ft_itoa(%d) == \"%s\",
		expected \"%s\"\n", input, result, expected);
    }

    free(result);
}

int main(void) {
    // Basic tests
    test_itoa(0, "0");
    test_itoa(1, "1");
    test_itoa(-1, "-1");
    test_itoa(42, "42");
    test_itoa(-42, "-42");
    test_itoa(123456, "123456");
    test_itoa(-987654, "-987654");

    // Edge cases
    test_itoa(INT_MAX, "2147483647");
    test_itoa(INT_MIN, "-2147483648"); // tricky case due to two's complement

    // Large near-limits
    test_itoa(1000000000, "1000000000");
    test_itoa(-1000000000, "-1000000000");

    // Leading zeros not expected — we test format correctness
    // If your ft_itoa is returning padded numbers, it would fail these

    return 0;
} */