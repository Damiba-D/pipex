/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_striteri.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 19:05:29 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/25 16:48:53 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_striteri(char *s, void (*f)(unsigned int, char*))
{
	unsigned int	i;

	i = 0;
	if (s == NULL || f == NULL)
		return ;
	while (s[i] != '\0')
	{
		f(i, s + i);
		i++;
	}
}

/* void	iteri_toupper(unsigned int i, char *c)
{
	if (*c >= 'a' && *c <= 'z' && i > 0)
	{
		*c -= 32;
	}
}

int main()
{
	char string[] = "Hello World!";
	ft_striteri(string, iteri_toupper);

	printf("%s\n", string);
	return 0;
}  */