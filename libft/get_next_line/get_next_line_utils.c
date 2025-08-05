/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:16:34 by ddamiba           #+#    #+#             */
/*   Updated: 2025/05/30 16:16:08 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_linelen(const char *s)
{
	int	i;

	i = 0;
	if (s == NULL)
		return (i);
	while (s[i] != '\0' && s[i] != '\n')
		i++;
	if (s[i] == '\n')
		i++;
	return (i);
}

char	*ft_makeline(const char *s1, const char *s2)
{
	size_t	totallen;
	char	*final_s;
	int		i;
	int		j;

	totallen = ft_linelen(s1) + ft_linelen(s2) + 1;
	final_s = (char *)malloc(sizeof(char) * totallen);
	if (final_s == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (s1 != NULL && s1[i] != '\0')
		final_s[j++] = s1[i++];
	i = 0;
	while (s2 != NULL && s2[i] != '\0')
	{
		final_s[j++] = s2[i];
		if (s2[i++] == '\n')
			break ;
	}
	final_s[j] = '\0';
	free((char *)s1);
	return (final_s);
}

int	prepare_next_line(char *line)
{
	int	i;
	int	j;
	int	check;

	i = 0;
	j = 0;
	check = 0;
	while (line[i])
	{
		if (check == 1)
			line[j++] = line[i];
		if (line[i] == '\n')
			check = 1;
		line[i] = 0;
		i++;
	}
	return (check);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == (char)c)
			return ((char *)(s) + i);
		i++;
	}
	if (s[i] == (char)c)
		return ((char *)(s) + i);
	return (NULL);
}

char	*ret(char *line, char *buffer, int fd)
{
	int	line_read;

	while (1)
	{
		if (buffer[0])
		{
			line = ft_makeline(line, buffer);
			prepare_next_line(buffer);
			if (ft_strchr(line, '\n'))
				return (line);
		}
		line_read = read(fd, buffer, BUFFER_SIZE);
		buffer[line_read] = '\0';
		if (line_read < 0)
			return (free(line), NULL);
		else if (line_read == 0)
			return (prepare_next_line(buffer), line);
		line = ft_makeline(line, buffer);
		if (prepare_next_line(buffer))
			break ;
	}
	return (line);
}
