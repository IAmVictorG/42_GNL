/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:38:18 by victorgiord       #+#    #+#             */
/*   Updated: 2022/11/14 14:26:37 by vgiordan         ###   ########.fr       */
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

char	*add_buffer_to_line(char *line, int fd)
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
	if (remains)
	{
		line_remains = ft_strjoin(line, remains);
		free(remains);
		remains = NULL;
	}
	//printf("Buffer : %p\n", buffer);
	buffer = get_buffer(fd, buffer);
	//printf("Buffer : %p\n", buffer);
	if (!buffer)
		return (NULL);
	while (buffer[i] != '\0' && buffer[i] != '\n')
		i++;
	if (buffer[i] != '\n' && i != 0)//i != 0 pareil que buffer[0] != '\0' 
	{
		//printf("OUI\nline%p\n", line);
		//printf("new_line %p\n", new_line);
		if (line_remains)
			new_line = ft_strjoin(line_remains, buffer);
		else
			new_line = ft_strjoin(line, buffer);
		//free(line);
		//printf("line %p\n", line);
		//printf("new_line %p\n", new_line);
		free(buffer);
		buffer = NULL;
		//printf("buffer %p\n", buffer);
		//printf("linelast %p\n", line);
		line = NULL;
		//printf("linelast %p\n", line);
		return (add_buffer_to_line(new_line, fd));
	}
	if (buffer[i] == '\0' && i != BUFFER_SIZE)
		return (buffer);
	//printf("NON\n");
	if (line_remains)
		new_line = ft_strnjoin(line_remains, buffer, i + 1);
	else
		new_line = ft_strnjoin(line, buffer, i + 1);
	remains = malloc(BUFFER_SIZE - i);
	while (buffer[i + 1])
	{
		remains[j++] = buffer[i++ + 1];
	}
	remains[j] = '\0';
	free(buffer);
	if (new_line[0] == '\0')
	{
		free(new_line);
		free(remains);
		return (NULL);
	}
	return (new_line);
}

char	*get_next_line(int fd)
{
	char	*line;
	char	*buffertest;
	char	*result;

	buffertest = NULL;
	line = "";
	if (fd < 0 || read(fd, buffertest, 0) < 0 || BUFFER_SIZE < 1)
		return (NULL);
	result = add_buffer_to_line(line, fd);
	if (result == NULL)
	{
		free(result);
		return (NULL);
	}
	return (result);
}

int main(int argc, char const *argv[])
{
	int fd = open("test.txt", O_RDONLY);
	char *result;

	while ((result = get_next_line(fd)))
	{	
		if (result == NULL)
			return (0);
		printf("%s", result);
		free(result);
	}
	return 0;
}
