/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vgiordan <vgiordan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:46:08 by victorgiord       #+#    #+#             */
/*   Updated: 2022/11/14 14:16:53 by vgiordan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	i;

	i = 0;
	while (str[i] != '\0')
		i++;
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	int		s_s1;
	int		s_s2;
	int		i;
	char	*result;

	i = 0;
	s_s1 = ft_strlen(s1);
	s_s2 = ft_strlen(s2);
	result = malloc((s_s1 + s_s2 + 1) * sizeof(char));
	if (!result || !s1 || !s2)
		return (NULL);
	while (*s1)
		result[i++] = *s1++;
	while (*s2)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

char	*ft_custom_join(char *s1, char *s2)
{
	char *result;
	int		s_s1;
	int		s_s2;
	int		i;
	int		j;

	i = 0;
	j = 0;
	s_s1 = ft_strlen(s1);
	s_s2 = ft_strlen(s2);
	result = malloc((s_s1 + s_s2 + 1) * sizeof(char));
	if (!result || !s1 || !s2)
		return (NULL);
	while (s1[i])
		result[j++] = s1[i++];
	i = 0;
	while (s2[i])
		result[j++] = s2[i++];
	result[j] = '\0';
	free(s1);
	return (result);
}


char	*ft_strnjoin(char const *s1, char const *s2, int n)
{
	int		s_s1;
	int		s_s2;
	int		i;
	char	*result;

	i = 0;
	s_s1 = ft_strlen(s1);
	s_s2 = ft_strlen(s2);
	result = malloc((s_s1 + s_s2 + 1) * sizeof(char));
	if (!result || !s1 || !s2)
		return (NULL);
	while (*s1)
		result[i++] = *s1++;
	while (*s2 && n-- > 0)
		result[i++] = *s2++;
	result[i] = '\0';
	return (result);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str)
	{
		if (*str == (char)c)
			return ((char *) str);
		str++;
	}
	if ((char)c == *str)
		return ((char *)str);
	return (NULL);
}
