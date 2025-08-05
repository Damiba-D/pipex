/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strncmp.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:03:17 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/21 18:05:27 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_strncmp(const char *s1, const char *s2, size_t n)
{
	size_t			i;
	unsigned char	*temp1;
	unsigned char	*temp2;

	temp1 = (unsigned char *)s1;
	temp2 = (unsigned char *)s2;
	i = 0;
	while ((temp1[i] != '\0' && temp2[i] != '\0') && i < n)
	{
		if (temp1[i] != temp2[i])
			return (temp1[i] - temp2[i]);
		i++;
	}
	if (i == n)
		return (0);
	return (temp1[i] - temp2[i]);
}

/* #include <stdio.h>

int main(void)
{
	char str1[] = "Hello Frens";
	char str2[] = "Hello Big Old Frens";
	printf("%d\n", ft_strncmp(str1, str2, 13));
} */