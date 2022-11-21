/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:19:30 by victorgiord       #+#    #+#             */
/*   Updated: 2022/11/21 10:37:02 by vgiordan         ###   ########.fr       */
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
char	*line_constructor(char *line, int fd);
char	*get_buffer(int fd, char *remains);
char	**split_at_first_char(char *str, char c);
int		is_char_in_string(const char *str, int c);
char	*ft_strnjoin(char *s1, char *s2, int n);
char	*get_left_str(char *str, char c);
size_t	ft_strlen(const char *str);

#endif