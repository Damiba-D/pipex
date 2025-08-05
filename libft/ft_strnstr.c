/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/01 14:25:26 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/21 17:29:13 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *str, const char *to_find, size_t len)
{
	unsigned int	i;
	unsigned int	j;

	i = 0;
	j = 0;
	if (to_find[j] == '\0')
		return ((char *)str);
	while (str[i] != '\0' && i < len)
	{
		j = 0;
		if (str[i] == to_find[j])
		{
			while (to_find[j] != '\0'
				&& (to_find[j] == str[i + j]) && (i + j < len))
				j++;
			if (to_find[j] == '\0')
				return ((char *)(str) + i);
		}
		i++;
	}
	return (NULL);
}
/* int main(void)
{
	char str1[200] = "aaabcabcd";
	char str2[10] = "aabc";
	printf("%s\n", ft_strnstr(str1, str2, -1));
} */