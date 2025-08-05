/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_tolower.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:51:08 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/18 19:51:17 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_tolower(int c)
{
	if (c >= 'A' && c <= 'Z')
	{
		c += 32;
	}
	return (c);
}

/* int main(void)
{
	char a = 'H';
	char b = 'h';
	char c = '5';
	char d = '[';
	
	printf("%c\n", tolower(a));
	printf("%c\n", tolower(b));
	printf("%c\n", tolower(c));
	printf("%c\n", tolower(d));
} */