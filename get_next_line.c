/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:38:18 by victorgiord       #+#    #+#             */
/*   Updated: 2022/11/15 12:36:32 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffertest;
	char	*new_line;
	char 	**result;

	buffertest = NULL;
	result = NULL;
	if (fd < 0 || read(fd, buffertest, 0) < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = ft_strdup("");

	new_line = line_constructor(line, fd, result);
	//free(result[0]);
	free(result);
	//free(line);
	if (new_line == NULL || new_line[0] == '\0')
	{
		//free(line);
		free(new_line);
		return (NULL);
	}
	/*if (result[1])
		free(result[1]);*/
	return (new_line);
}

char	*get_buffer(int fd)
{
	int	bytes_read;
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
	//printf("REMAINS %s\n", remains);
	if (remains && isCharInString(remains, '\n') != -1)
	{
		result = split_first_char(remains, '\n');
		free(remains);
		remains = NULL;
		//remains = result[1];
		
		remains = malloc(ft_strlen(result[1]) + 1);
		ft_memmove(remains, result[1], ft_strlen(result[1]) + 1);
		free(result[1]);
		result[1] = NULL;
		/*printf("%p %s\n", remains, remains);
		printf("%p %s\n", result[1], result[1]);*/
		return (result[0]);
	}
	if (remains)
	{
		temp = line;
		free(line);
		line = NULL;
		line = ft_strjoin(temp, remains);
		free(temp);
		free(remains);
		remains = NULL;
	}
	buffer = get_buffer(fd);
	index = isCharInString(buffer, '\n');
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
		index = isCharInString(buffer, '\n');
	}
	temp = line;
	line = ft_strnjoin(temp, buffer, index + 1);
	free(temp);
	remains = get_left_str(buffer, '\n');
	free(buffer);
	return (line);
}

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *result;
	int i = 0;

	/*result = get_next_line(fd);
	printf("Result %d : %s", i++, result);
	free(result);
	result = get_next_line(fd);
	printf("Result %d : %s", i++, result);
	free(result);
	result = get_next_line(fd);
	printf("Result %d : %s", i++, result);
	free(result);*/
	while ((result = get_next_line(fd)))
	{
		if (result == NULL)
		{
			return (0);
		}
		printf("Result %d : %s", i++, result);
		free(result);
	}
	return 0;
}