/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 15:29:50 by ddamiba           #+#    #+#             */
/*   Updated: 2025/04/26 17:19:06 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static unsigned int	ft_count_words(char const *s, char c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == c)
		i++;
	while (s[i] != '\0')
	{
		if (s[i] != c && (i == 0 || s[i - 1] == c))
			count++;
		i++;
	}
	return (count);
}

static void	ft_free_arr(char **arr, int i)
{
	while (i >= 0)
	{
		free(arr[i]);
		i--;
	}
	free(arr);
}

static int	ft_cpy_alloc(char **arr, const char *s, char c)
{
	int	i;
	int	j;
	int	len;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		len = 0;
		while (s[i] == c && s[i])
			i++;
		while (s[i] != c && s[i])
		{
			i++;
			len++;
		}
		if (len == 0)
			break ;
		arr[j] = (char *)malloc((len + 1) * sizeof(char));
		if (arr[j] == NULL)
			return (ft_free_arr(arr, j), -1);
		ft_strlcpy(arr[j], s + (i - len), len + 1);
		j++;
	}
	return (j);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		i;

	if (s == NULL)
		return (NULL);
	arr = (char **)malloc(((ft_count_words(s, c) + 1) * sizeof(char *)));
	if (arr == NULL)
		return (NULL);
	i = ft_cpy_alloc(arr, s, c);
	if (i == -1)
		return (NULL);
	arr[i] = NULL;
	return (arr);
}

/* int main()
{
	char **arr = ft_split("Hello   World", 'a');
	unsigned int i = 0;
	while(arr[i] != NULL)
	{
		printf("%s\n", arr[i]);
		free(arr[i]);
		i++;
	}
	free(arr);
	return 0;
} */