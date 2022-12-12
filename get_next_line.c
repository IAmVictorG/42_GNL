/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:38:18 by victorgiord       #+#    #+#             */
/*   Updated: 2022/12/12 18:37:24 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffertest;
	int		r;

	buffertest = NULL;
	if (fd < 0 || BUFFER_SIZE < 1)
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
		if (get_buffer(fd, &buffer) < 0)
		{
			free(*remains);
			*remains = NULL;
			return (NULL);
		}
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
	static char	*remains[2048];
	char		*buffer;

	if (remains[fd] && is_char_in_string(remains[fd], '\n') != -1)
	{
		line_is_in_remains(line, &remains[fd]);
		return (ft_strlen(*line));
	}
	if (remains[fd])
	{
		ft_strnjoin(line, &remains[fd], ft_strlen(remains[fd]));
		free(remains[fd]);
		remains[fd] = NULL;
	}
	if (get_buffer(fd, &buffer) < 0)
	{
		free(remains[fd]);
		remains[fd] = NULL;
		return (-1);
	}
	c_line_with_buffer(line, &remains[fd], buffer, fd);
	return (ft_strlen(*line));
}

int main(void)
{
	int fd1 = open("test.txt", O_RDONLY);
	int fd2 = open("test2.txt", O_RDONLY);
	char *result;
	int i = 0;

	printf("Result %d : %s", i++, get_next_line(fd1));
	printf("Result %d : %s", i++, get_next_line(fd1));
	printf("Result %d : %s", i++, get_next_line(fd2));
	printf("Result %d : %s", i++, get_next_line(fd1));
	printf("Result %d : %s", i++, get_next_line(fd2));
	/*while ((result = get_next_line(fd)))
	{
		printf("Result %d : %s", i++, result);
		free(result);
	}*/
	return 0;
}