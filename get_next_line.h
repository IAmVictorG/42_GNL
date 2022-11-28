/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:19:30 by victorgiord       #+#    #+#             */
/*   Updated: 2022/11/28 21:14:34 by victorgiord      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdio.h>
# include <string.h>
# include <stdlib.h>
# include <fcntl.h>

# ifndef BUFFER_SIZE
#  define  BUFFER_SIZE 500
# endif

char	*get_next_line(int fd);
int		line_constructor(char **line, int fd);
int		get_buffer(int fd, char **buffer);
char	**split_at_first_char(char *str, char c);
int		is_char_in_string(char *str, int c);
void	ft_strnjoin(char **s1, char **s2, int n);
char	*get_right_str(char *str, char c);
size_t	ft_strlen(char *str);

#endif