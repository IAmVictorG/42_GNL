/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:38:18 by victorgiord       #+#    #+#             */
/*   Updated: 2022/11/17 23:40:38 by victorgiord      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffertest;
	char	*temp;
	char	**result;

	buffertest = NULL;
	result = NULL;
	if (fd < 0 || read(fd, buffertest, 0) < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = ft_strdup("");
	temp = line;
	line = line_constructor(temp, fd, result);
	if (line == NULL || line[0] == '\0')
	{
		free(line);
		return (NULL);
	}
	return (line);
}

char	*get_buffer(int fd)
{
	int		bytes_read;
	char	*buffer;

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

char	*line_constructor(char *line, int fd, char **result)
{
	static char	*remains;
	char		*buffer;
	char		*temp;
	int			index;

	if (remains && is_char_in_string(remains, '\n') != -1)
	{
		result = split_at_first_char(remains, '\n');
		free(remains);
		remains = NULL;
		remains = result[1];
		remains = malloc(ft_strlen(result[1]) + 1);
		memcpy(remains, result[1], strlen(result[1]) + 1);
		free(result[1]);
		result[1] = NULL;
		temp = line;
		line = ft_strjoin(line, result[0]);
		free(temp);
		free(result[0]);
		result[0] = NULL;
		free(result);
		result = NULL;
		return (line);
	}
	if (remains)
	{
		temp = line;
		line = ft_strjoin(temp, remains);
		free(temp);
		free(remains);
		remains = NULL;
	}
	buffer = get_buffer(fd);
	index = is_char_in_string(buffer, '\n');
	while (index == -1)
	{
		temp = line;
		line = ft_strjoin(temp, buffer);
		free(temp);
		if (ft_strlen(buffer) != BUFFER_SIZE)
		{
			free(buffer);
			return (line);
		}
		free(buffer);
		buffer = get_buffer(fd);
		index = is_char_in_string(buffer, '\n');
	}
	temp = line;
	line = ft_strnjoin(temp, buffer, index + 1);
	free(temp);
	remains = get_left_str(buffer, '\n');
	free(buffer);
	return (line);
}

/*int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *result;
	int i = 0;

	result = get_next_line(fd);
	printf("Result %d : %s", i++, result);
	free(result);
	result = get_next_line(fd);
	printf("Result %d : %s", i++, result);
	free(result);
	result = get_next_line(fd);
	printf("Result %d : %s", i++, result);
	free(result);
	while ((result = get_next_line(fd)))
	{
		if (result == NULL)
		{
			free(result);
			return (0);
		}
		printf("Result %d : %s", i++, result);
		free(result);
	}
	return 0;
}*/