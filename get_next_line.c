/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:16:00 by mnajem            #+#    #+#             */
/*   Updated: 2025/10/04 17:21:47 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strchr(const char *s, int c)
{
	while (*s)
	{
		if (*s == (char)c)
			return ((char *)s);
		s++;
	}
	if ((char)c == '\0')
		return ((char *)s);
	return (NULL);
}

char	*ft_rest_of_read(char *rest_of_read)
{
	int		line_length;
	char	*newline_ptr;
	char	*new_rest_of_read;

	if (!rest_of_read)
		return (NULL);
	newline_ptr = ft_strchr(rest_of_read, '\n');
	if (newline_ptr)
		line_length = (newline_ptr - rest_of_read) + 1;
	else
		line_length = ft_strlen(rest_of_read);
	new_rest_of_read = ft_substr(rest_of_read,
			line_length, ft_strlen(rest_of_read) - line_length);
	if (!new_rest_of_read)
	{
		free(rest_of_read);
		return (NULL);
	}
	free(rest_of_read);
	return (new_rest_of_read);
}

char	*ft_get_my_line(char *rest_of_read)
{
	int		line_length;
	char	*newline_ptr;
	char	*line;

	if (!rest_of_read)
	{
		return (NULL);
	}
	newline_ptr = ft_strchr(rest_of_read, '\n');
	if (newline_ptr)
	{
		line_length = (newline_ptr - rest_of_read) + 1;
	}
	else
	{
		line_length = ft_strlen(rest_of_read);
	}
	line = ft_substr(rest_of_read, 0, line_length);
	if (!line)
	{
		free(rest_of_read);
		return (NULL);
	}
	return (line);
}

char	*ft_read_file(int fd, char *rest_of_read)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
	{
		return (NULL);
	}
	bytes_read = 1;
	while ((!rest_of_read || !ft_strchr(rest_of_read, '\n')) && bytes_read > 0)
	{
		bytes_read = read(fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			free(rest_of_read);
			return (NULL);
		}
		buffer[bytes_read] = '\0';
		rest_of_read = ft_strjoin(rest_of_read, buffer);
	}
	free(buffer);
	return (rest_of_read);
}

char	*get_next_line(int fd)
{
	static char	*rest_of_read;
	char		*line;
	char		*temp;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	rest_of_read = ft_read_file(fd, rest_of_read);
	if (rest_of_read && *rest_of_read)
	{
		line = ft_get_my_line(rest_of_read);
		if (line == NULL)
		{
			free(rest_of_read);
			return (NULL);
		}
		temp = ft_rest_of_read(rest_of_read);
		if (temp == NULL)
			free(rest_of_read);
		rest_of_read = temp;
		return (line);
	}
	free(rest_of_read);
	rest_of_read = NULL;
	return (NULL);
}

// int	main(void)
// {
// 	int fd = open("t.txt", O_RDONLY);
// 	char *s;

// 	while ((s = get_next_line(fd)))
// 	{
// 		printf("%s", s);
// 		free(s);
// 	}

// 	close(fd);
// 	return (0);
// }