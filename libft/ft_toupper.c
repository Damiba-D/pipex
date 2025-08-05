/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_toupper.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/30 09:51:08 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/18 19:51:08 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_toupper(int c)
{
	if (c >= 'a' && c <= 'z')
	{
		c -= 32;
	}
	return (c);
}

/* int main(void)
{
	char a = 'H';
	char b = 'h';
	char c = '5';
	char d = '[';
	
	printf("%c\n", toupper(a));
	printf("%c\n", toupper(b));
	printf("%c\n", toupper(c));
	printf("%c\n", toupper(d));
} */