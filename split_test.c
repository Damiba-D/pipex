#include "pipex.h"

static void	free_arr(char **arr)
{
	int	i;

	i = 0;
	while (arr[i] != NULL)
	{
		free(arr[i]);
		i++;
	}
	free(arr);
}

static unsigned int	count_args(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i] == ' ')
		i++;
	while (s[i] != '\0')
	{
		if (s[i] == '\'')
		{
			while (s[i] != '\'')
				i++;
			count++;
			i++;
		}
		if (s[i] == '\0')
			break ;
		if (s[i] != ' ' && (i == 0 || s[i - 1] == ' '))
			count++;
		i++;
	}
	return (count);
}

static void	arg_len(char *s, int *i, int *len)
{
	if (s[*i] == '\'')
	{
		*i += 1;
		while (s[*i] && s[*i] != '\'')
		{
			*i += 1;
			*len += 1;
		}
		if (s[*i] == '\'')
			*i += 1;
	}
	else
	{
		while (s[*i] != ' ' && s[*i])
		{
			*i += 1;
			*len += 1;
		}
	}
}

size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
		i++;
	return (i);
}

size_t	ft_strlcpy(char *dest, const char *src, size_t size)
{
	unsigned int	i;

	i = 0;
	if (size == 0)
		return (ft_strlen(src));
	while (i < size - 1 && src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (ft_strlen(src));
}

static int	ft_cpy_alloc(char **arr, char *s)
{
	int	i;
	int	j;
	int	len;
	int	start;

	i = 0;
	j = 0;
	while (s[i] != '\0')
	{
		len = 0;
		while (s[i] == ' ' && s[i])
			i++;
		start = i;
		arg_len(s, &i, &len);
		if (len == 0 && s[start] != '\'')
			break ;
		if (s[start] == '\'')
			start++;
		arr[j] = (char *)malloc((len + 1) * sizeof(char));
		if (arr[j] == NULL)
			return (free_arr(arr), -1);
		ft_strlcpy(arr[j], s + start, len + 1);
		j++;
	}
	return (j);
}

static int	has_unmatched_quote(char *s)
{
	int	i;

	i = 0;
	while (s[i])
	{
		if (s[i] == '\'')
		{
			i++;
			while (s[i] && s[i] != '\'')
				i++;
			if (s[i] == '\0')
				return (1);
		}
		if (s[i])
			i++;
	}
	return (0);
}

char	**arg_split(char *s, int *inv_arg)
{
	char	**arr;
	int		i;

	*inv_arg = 1;
	if (s == NULL)
		return (NULL);
	if (has_unmatched_quote(s))
	{
		*inv_arg = 2;
		return (NULL);
	}
	arr = (char **)malloc(((count_args(s) + 1) * sizeof(char *)));
	if (arr == NULL)
		return (NULL);
	i = ft_cpy_alloc(arr, s);
	if (i == -1)
		return (NULL);
	arr[i] = NULL;
	return (arr);
}

