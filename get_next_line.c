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

char	*create_line(char *line, int fd)
{
	static char	*remains;
	char		*buffer;
	char		*line_remains;
	char		*new_line;
	int			i;
	int			j;

	i = 0;
	j = 0;
	buffer = NULL;
	line_remains = ft_strdup(line);
	if (!line_remains)
		return (NULL);
	if (remains)
	{
		if ((ft_strchr(remains, '\n')))
		{
			//free(remains);
			//free(line_remains);
			//return (ft_strchr(remains, '\n'));
			printf("-----------------\n");
			printf("remainsString : %s\n", remains);
			printf("-----------------\n");
		}
		buffer = get_buffer(fd, buffer);
		free(line_remains);
		line_remains = ft_strjoin(line, remains);
		free(remains);
		remains = NULL;
		/*memcpy(line, remains, strlen(remains));
		printf("memcpyOK\n");
		printf("line : %s, remains : %lu\n", line, strlen(remains));*/
	}
	else
		buffer = get_buffer(fd, buffer);
	free(line);
	if (!buffer)
		return (NULL);
		
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] == '\0')
	{
		new_line = ft_strjoin(line_remains, buffer);
		free(line_remains);
		free(buffer);
		buffer = NULL;
		if (i != BUFFER_SIZE)	
			return (new_line);
		else
			return (create_line(new_line, fd));
	}
	else //(buffer[i] == '\n')
	{
		new_line = ft_strnjoin(line_remains, buffer, i + 1);
		free(line_remains);
		//printf("Line%p\n", line);
		remains = malloc(BUFFER_SIZE - i);
		i++;
		while (buffer[i])
		{
			remains[j++] = buffer[i];
			i++;
		}
		//printf("BUFFER %s\n", buffer);
		//printf("new_line : %p\n", new_line);
		//printf("Remains : %p || PLACE %d || ", remains, place);
		//printf("J %d\n", j);
		remains[j] = '\0';
		free(buffer);
		buffer = NULL;
		return (new_line);
	}
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffertest;
	char	*result;

	buffertest = NULL;
	if (fd < 0 || read(fd, buffertest, 0) < 0 || BUFFER_SIZE < 1)
		return (NULL);
	line = ft_strdup("");
	if (!line)
		return (NULL);
	result = create_line(line, fd);
	//free(line);
	if (result == NULL || result[0] == '\0')
	{
		free(result);
		return (NULL);
	}
	return (result);
}

int main(void)
{
	int fd = open("test.txt", O_RDONLY);
	char *result;
	int i = 0;
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
