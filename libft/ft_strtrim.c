/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 18:09:54 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/26 17:23:02 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isset(char const *set, char c)
{
	unsigned int	i;

	i = 0;
	while (set[i] != '\0')
	{
		if (set[i] == c)
			return (1);
		i++;
	}
	return (0);
}

char	*ft_strtrim(char const *s1, char const *set)
{
	unsigned int	start;
	unsigned int	end;
	unsigned int	final_len;
	char			*trimmed_s;

	if (*s1 == 0)
		return (ft_strdup(""));
	if (*set == 0)
		return (ft_strdup(s1));
	if (s1 == NULL || set == NULL)
		return (NULL);
	start = 0;
	end = ft_strlen(s1) - 1;
	while (ft_isset(set, s1[start]))
		start++;
	if (start == ft_strlen(s1))
		return (ft_strdup(""));
	while (ft_isset(set, s1[end]))
		end--;
	final_len = (end + 1) - start + 1;
	trimmed_s = (char *)malloc(final_len * sizeof(char));
	if (trimmed_s == NULL)
		return (NULL);
	ft_strlcpy(trimmed_s, s1 + start, final_len);
	return (trimmed_s);
}

/* int main()
{
	char *trimmed = ft_strtrim("  \t \t \n   \n\n\n\t", " \n\t");
	if (trimmed != NULL)
	{
		printf("%s\n", trimmed);
		free(trimmed);
	}
	return 0;
} */ 