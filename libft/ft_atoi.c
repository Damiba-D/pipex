/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/03 17:14:33 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/26 16:20:20 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_atoi(const char *str)
{
	int		i;
	int		res;
	int		sign;
	char	*cpy;

	i = 0;
	res = 0;
	sign = 1;
	cpy = (char *)str;
	while (cpy[i] != '\0' && ((cpy[i] >= '\t' && cpy[i] <= '\r')
			|| cpy[i] == ' '))
		i++;
	if (cpy[i] == '-')
	{
		sign *= -1;
		i++;
	}
	else if (cpy[i] == '+')
		i++;
	while ((cpy[i] != '\0' && (cpy[i] >= '0' && cpy[i] <= '9')))
	{
		res = (res * 10) + (cpy[i] - '0');
		i++;
	}
	return (res * sign);
}

/* int main(void)
{
    const char *tests[] = {
        "42",
        "   -42",
        "+42",
        "0042",
        "-0",
        "  \t\n\v\f\r123",
        "123abc",
        "abc123",
        "",
        "+-42",
        "--42",
        "-+42",
        "99999999999999999999999999",  // overflow case
        "-2147483648",
        "2147483647"
    };

    size_t n = sizeof(tests) / sizeof(tests[0]);
    unsigned int passed = 0;

    printf("Testing ft_atoi:\n");
    for (size_t i = 0; i < n; i++) {
        int std = atoi(tests[i]);
        int custom = ft_atoi(tests[i]);
        if (std == custom) {
            printf("[OK]    ft_atoi(\"%s\") == %d\n", tests[i], custom);
            passed++;
        } else {
            printf("[FAIL]  ft_atoi(\"%s\") == %d (expected %d)\n"
			, tests[i], custom, std);
        }
    }

    printf("\nResult: %d/%zu passed\n", passed, n);
    return (passed == n) ? 0 : 1;
} */
