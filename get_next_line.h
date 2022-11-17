/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/05 13:19:30 by victorgiord       #+#    #+#             */
/*   Updated: 2022/11/15 12:08:38 by vgiordan         ###   ########.fr       */
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
char    **split_first_char(char *str, char c);
int	    isCharInString(const char *str, int c);
char	*ft_strnjoin(char *s1, char *s2, int n);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_strchr(const char *str, int c);
char	*ft_custom_join(char *s1, char *s2);
char	*ft_strdup(char *src);
char	*get_left_str(char *str, char c);
void	*ft_memmove(void *dst, const void *src, size_t n);
size_t	ft_strlen(const char *str);

#endif