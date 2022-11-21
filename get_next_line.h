/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:19:30 by victorgiord       #+#    #+#             */
/*   Updated: 2022/11/17 23:38:20 by victorgiord      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <strings.h>
# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

# ifndef BUFFER_SIZE
#  define  BUFFER_SIZE 5
# endif

char	*get_next_line(int fd);
char	*line_constructor(char *line, int fd, char **result);
char	*get_buffer(int fd);
char	**split_at_first_char(char *str, char c);
int		is_char_in_string(const char *str, int c);
char	*ft_strnjoin(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strdup(char *src);
char	*get_left_str(char *str, char c);
size_t	ft_strlen(const char *str);

#endif