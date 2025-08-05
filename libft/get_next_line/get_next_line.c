/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddamiba <ddamiba@student.42lisboa.com>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/06 17:16:17 by ddamiba           #+#    #+#             */
/*   Updated: 2025/05/30 16:15:58 by ddamiba          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char		*line;
	static char	buffer[FOPEN_MAX][BUFFER_SIZE + 1];

	if (fd < 0 || BUFFER_SIZE <= 0 || fd > FOPEN_MAX)
		return (NULL);
	line = NULL;
	return (ret(line, buffer[fd], fd));
}

/* int main()
{
	int fd1 = open("bonus1.txt", O_RDONLY);
	int fd2 = open("bonus2.txt", O_RDONLY);
	int fd3 = open("bonus3.txt", O_RDONLY);
	char *str1;
	char *str2;
	char *str3;
	int NULL_CHECK = 0;
	str1 = get_next_line(fd1);
	str2 = get_next_line(fd2);
	str3 = get_next_line(fd3);
	while (!NULL_CHECK)
	{
		printf("%s", str1);
		free(str1);
		printf("%s", str2);
		free(str2);
		printf("%s", str3);
		free(str3);
		str1 = get_next_line(fd1);
		str2 = get_next_line(fd2);
		str3 = get_next_line(fd3);
		if (str1 == NULL || str2 == NULL || str3 == NULL)
			NULL_CHECK = 1;
	}
	close(fd1);
	close(fd2);
	close(fd3);
	return 0;
} */