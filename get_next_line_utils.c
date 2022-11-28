/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: victorgiordani01 <victorgiordani01@stud    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/12 22:46:08 by victorgiord       #+#    #+#             */
/*   Updated: 2022/11/28 21:36:57 by victorgiord      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '\0')
		i++;
	return (i);
}

void	ft_strnjoin(char **s1, char **s2, int n)
{
	int		i;
	int		j;
	int		k;
	char	*result;

	i = 0;
	j = 0;
	k = 0;
	if (!(*s1) || !(*s1))
		return ;
	result = malloc((ft_strlen(*s1) + ft_strlen(*s2) + 1) * sizeof(char));
	if (!result)
		return ;
	while ((*s1)[i])
		result[k++] = (*s1)[i++];
	while ((*s2)[j] && n-- > 0)
		result[k++] = (*s2)[j++];
	result[k] = '\0';
	free(*s1);
	*s1 = result;
}

int	is_char_in_string(char *str, int c)
{
	int	i;

	i = 0;
	if (!str)
		return (-1);
	while (str[i])
	{
		if (str[i] == (char)c)
			return (i);
		i++;
	}
	if ((char)c == str[i])
		return (i);
	return (-1);
}

char	*get_right_str(char *str, char c)
{
	char	*result;
	int		i;
	int		j;

	j = 0;
	i = 0;
	if (!str)
		return (NULL);
	while (str[i] != c && str[i])
		i++;
	i++;
	result = (char *)malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!result)
		return (NULL);
	while (str[i])
		result[j++] = str[i++];
	result[j] = '\0';
	return (result);
}

char	**split_at_first_char(char *str, char c)
{
	char	**result;
	int		i;
	int		j;

	i = 0;
	j = 0;
	result = (char **)malloc((2) * sizeof(char *));
	if (!result)
		return (NULL);
	while (str[i] != c)
		i++;
	result[0] = (char *)malloc((i + 1 + 1) * sizeof(char));
	result[1] = (char *)malloc((ft_strlen(str) - i + 1) * sizeof(char));
	if (!result[0] || !result[1])
		return (NULL);
	i = -1;
	while (str[++i] != c)
		result[0][i] = str[i];
	result[0][i] = c;
	result[0][i++ + 1] = '\0';
	while (str[i])
		result[1][j++] = str[i++];
	result[1][j] = '\0';
	return (result);
}
