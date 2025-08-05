/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:19:27 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/22 15:46:52 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	totallen;
	char	*final_s;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	totallen = ft_strlen(s1) + ft_strlen(s2) + sizeof(char);
	final_s = (char *)malloc(sizeof(char) * totallen);
	if (final_s == NULL)
		return (NULL);
	ft_strlcpy(final_s, s1, totallen);
	ft_strlcat(final_s, s2, totallen);
	return (final_s);
}

/* int main()
{
	printf("%s\n", ft_strjoin("hello", " world"));
} */