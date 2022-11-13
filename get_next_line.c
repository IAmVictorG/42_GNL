/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:38:18 by victorgiord       #+#    #+#             */
/*   Updated: 2022/11/13 01:32:25 by victorgiord      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_buffer(int fd, char *buffer)
{
	int	bytes_read;

	buffer = malloc(BUFFER_SIZE + 1);
	if (!buffer)
		return (NULL);
	bytes_read = read(fd, buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(buffer);
		return (NULL);
	}
	buffer[bytes_read] = '\0';
	return (buffer);
}

char	*add_buffer_to_line(char *line, char *buffer)
{
	static char	*remains;

	if(remains)
	{
		line = ft_strjoin(line, remains);
		free(remains);
		remains = NULL;
	}
	line = ft_strjoin(line, buffer);
	if (line[0] == '\0')
	{
		free(line);
		free(remains);
		return (NULL);
	}
	return (line);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffer;

	buffer = NULL;
	line = "";
	if (fd < 0 || read(fd, buffer, 0) < 0 || BUFFER_SIZE < 1)
		return (NULL);
	//printf("%d", read(fd, buffer, 0));
	buffer = get_buffer(fd, buffer);
	if (!buffer)
		return (NULL);
	line = add_buffer_to_line(line, buffer);
	free(buffer);
	return (line);
}

int main(int argc, char const *argv[])
{
	int fd = open("test.txt", O_RDONLY);
	char *result;
	while (result = get_next_line(fd))
	{	
		if (result == NULL)
			return (0);
		printf("%s\n", result);
		free(result);
	}
	return 0;
}
