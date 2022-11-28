/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:38:18 by victorgiord       #+#    #+#             */
/*   Updated: 2022/11/28 21:34:23 by victorgiord      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffertest;
	int		r;

	buffertest = NULL;
	if (fd < 0 || read(fd, buffertest, 0) < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = malloc(sizeof(char));
	if (!line)
		return (NULL);
	line[0] = '\0';
	r = line_constructor(&line, fd);
	if (line == NULL || line[0] == '\0' || r == -1)
	{
		if (line)
			free(line);
		return (NULL);
	}
	return (line);
}

int	get_buffer(int fd, char **buffer)
{
	int		bytes_read;

	*buffer = malloc(BUFFER_SIZE + 1);
	if (!(*buffer))
		return (-1);
	bytes_read = read(fd, *buffer, BUFFER_SIZE);
	if (bytes_read < 0)
	{
		free(*buffer);
		*buffer = NULL;
		return (-1);
	}
	(*buffer)[bytes_read] = '\0';
	return (bytes_read);
}

char	*line_is_in_remains(char **line, char **remains)
{
	char	**result;

	result = split_at_first_char(*remains, '\n');
	free(*remains);
	*remains = NULL;
	*remains = malloc(ft_strlen(result[1]) + 1);
	strcpy(*remains, result[1]);
	free(result[1]);
	result[1] = NULL;
	ft_strnjoin(line, &result[0], ft_strlen(result[0]));
	free(result[0]);
	result[0] = NULL;
	free(result);
	result = NULL;
	return (*line);
}

char	*c_line_with_buffer(char **line, char **remains, char *buffer, int fd)
{
	int		index;

	index = is_char_in_string(buffer, '\n');
	while (index == -1)
	{
		ft_strnjoin(line, &buffer, ft_strlen(buffer));
		if (ft_strlen(buffer) != BUFFER_SIZE)
		{
			free(buffer);
			return (*line);
		}
		free(buffer);
		get_buffer(fd, &buffer);
		index = is_char_in_string(buffer, '\n');
	}
	ft_strnjoin(line, &buffer, index + 1);
	*remains = get_right_str(buffer, '\n');
	free(buffer);
	buffer = NULL;
	return (*line);
}

int	line_constructor(char **line, int fd)
{
	static char	*remains;
	char		*buffer;

	if (remains && is_char_in_string(remains, '\n') != -1)
	{
		line_is_in_remains(line, &remains);
		return (ft_strlen(*line));
	}
	if (remains)
	{
		ft_strnjoin(line, &remains, ft_strlen(remains));
		free(remains);
		remains = NULL;
	}
	if (get_buffer(fd, &buffer) == -1)
		return (-1);
	if (buffer == NULL || buffer[0] == '\0')
	{
		if (buffer)
			free(buffer);
		free(remains);
		return (ft_strlen(*line));
	}
	c_line_with_buffer(line, &remains, buffer, fd);
	return (ft_strlen(*line));
}

/*int main(void)
{
	char *str1 = strdup("HELLO ");
	char *str2 = strdup("WORLD");
	printf("%s\n", str1);
	printf("%s\n", str2);
	ft_strnjoin(&str1, &str2, ft_strlen(str2));
	printf("%s\n", str1);
	printf("%s\n", str2);
	free(str1);
	free(str2);
	int fd = open("test.txt", O_RDONLY);
	char *result;
	int i = 0;

	while ((result = get_next_line(fd)))
	{
		printf("Result %d : %s", i++, result);
		free(result);
	}
	return 0;
}*/