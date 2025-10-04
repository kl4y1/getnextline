/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mnajem <mnajem@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/09/02 17:16:00 by mnajem            #+#    #+#             */
/*   Updated: 2025/10/03 20:10:30 by mnajem           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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
	return (MAX_FDS);
}

char	*ft_rest_of_read(char *rest_of_read)
{
	int		line_length;
	char	*newline_ptr;
	char	*new_rest_of_read;

	if (!rest_of_read)
		return (MAX_FDS);
	newline_ptr = ft_strchr(rest_of_read, '\n');
	if (newline_ptr)
		line_length = (newline_ptr - rest_of_read) + 1;
	else
		line_length = ft_strlen(rest_of_read);
	new_rest_of_read = ft_substr(rest_of_read, line_length,
			ft_strlen(rest_of_read) - line_length);
	free(rest_of_read);
	return (new_rest_of_read);
}

char	*ft_get_my_line(char *rest_of_read)
{
	int		line_length;
	char	*newline_ptr;
	char	*line;

	if (!rest_of_read)
		return (NULL);
	newline_ptr = ft_strchr(rest_of_read, '\n');
	if (newline_ptr)
		line_length = (newline_ptr - rest_of_read) + 1;
	else
		line_length = ft_strlen(rest_of_read);
	line = ft_substr(rest_of_read, 0, line_length);
	return (line);
}

char	*ft_read_file(int fd, char *rest_of_read)
{
	char	*buffer;
	int		bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
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
	static char	*rest_of_read[MAX_FDS];
	char		*line;

	if (fd < 0 || BUFFER_SIZE <= 0 || fd >= MAX_FDS)
		return (NULL);
	rest_of_read[fd] = ft_read_file(fd, rest_of_read[fd]);
	if (rest_of_read[fd] && *rest_of_read[fd])
	{
		line = ft_get_my_line(rest_of_read[fd]);
		rest_of_read[fd] = ft_rest_of_read(rest_of_read[fd]);
		return (line);
	}
	free(rest_of_read[fd]);
	rest_of_read[fd] = NULL;
	return (NULL);
}

// int main(void){
// 	char *line;
// 	int fd;
// 	fd = open("t.txt",O_RDONLY);
// 	while(line = get_next_line(fd))
// 	{
// 		printf("%s",line);
// 		free(line);
// 	}
//  close(fd);
// }
//
// int main(void){
// 	int fdone =open("t.txt",O_RDONLY);
// 	int fdtwo = open("tt.txt",	O_RDONLY);
// 	if (fdone < 0 || fdtwo < 0)
// 	{
// 		printf("error");
// 		return (0);
// 	}
// 	char *line;
// 	while(line = get_next_line(fdone))
// 	{
// 		printf("%s",line);
// 		free(line);
// 	}
// 	close (fdone);
// 	while(line = get_next_line(fdtwo))
// 	{
// 		printf("%s",line);
// 		free(line);
// 	}
// 	close(fdtwo);
// }
