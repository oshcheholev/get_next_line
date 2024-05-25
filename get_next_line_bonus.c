/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:32:58 by oshcheho          #+#    #+#             */
/*   Updated: 2024/05/22 13:07:33 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	free_and_null(char **str)
{
	if (*str)
		free(*str);
	*str = NULL;
}

char	*ft_strjoin(char *s1, char *s2)
{
	size_t	i;
	size_t	j;
	char	*res;

	if (!s1 && !s2)
		return (NULL);
	res = (char *)ft_calloc(ft_strlen(s1) + ft_strlen(s2) + 1, sizeof(char));
	if (!res)
		return (free_and_null(&s1), NULL);
	i = 0;
	j = 0;
	while (s1 && s1[i] != '\0')
	{
		res[i] = s1[i];
		i++;
	}
	while (s2 && s2[j] != '\0')
	{
		res[i] = s2[j];
		i++;
		j++;
	}
	return (free_and_null(&s1), res);
}

char	*get_left(char **buf)
{
	char	*left;
	char	*prev;
	size_t	i;

	i = 0;
	while ((*buf)[i] && (*buf)[i] != '\n')
		i++;
	if ((*buf)[i])
		i++;
	if (i == 0)
		return (NULL);
	left = ft_substr(*buf, 0, i);
	if (!left)
		return (free_and_null(buf), NULL);
	if (i == ft_strlen(*buf))
		return (free_and_null(buf), left);
	prev = *buf;
	*buf = ft_substr(*buf, i, ft_strlen(*buf) - i);
	free (prev);
	return (left);
}

char	*read_line(int fd, char *buf)
{
	int		chars_read;
	char	*tmp;

	tmp = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!tmp)
		return (free_and_null(&buf), NULL);
	chars_read = 1;
	while (!ft_strchr(buf, '\n') && chars_read != 0)
	{
		chars_read = read(fd, tmp, BUFFER_SIZE);
		if (chars_read < 0)
			return (free_and_null(&buf), free_and_null(&tmp), NULL);
		if (chars_read == 0)
			break ;
		tmp[chars_read] = '\0';
		buf = ft_strjoin(buf, tmp);
		if (!buf)
			return (free_and_null(&tmp), NULL);
	}
	return (free_and_null(&tmp), buf);
}

char	*get_next_line(int fd)
{
	static char		*static_buf[MAX_FD];

	if (fd < 0 || fd > MAX_FD || BUFFER_SIZE <= 0)
		return (NULL);
	static_buf[fd] = read_line(fd, static_buf[fd]);
	if (!static_buf[fd])
		return (NULL);
	return (get_left(&static_buf[fd]));
}
