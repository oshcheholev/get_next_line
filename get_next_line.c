/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:53:09 by oshcheho          #+#    #+#             */
/*   Updated: 2024/04/30 16:21:05 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(const char *s)
{
	char	*res;
	int		i;

	i = 0;
	while (s[i] != '\0')
		i++;
	res = malloc((i + 1) * sizeof(char));
	if (!res)
		return (NULL);
	i = 0;
	while (s[i] != '\0')
	{
		res[i] = s[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*fill_str(char *str, char *buf, int fd)
{
	char	*res;
	char	tmp[BUFFER_SIZE + 1];
	char	*n_found;
	int		chars_read;

	n_found = NULL;
//printf ("fill str >  %s\n", str);
	if (!str)
		res = init_str();
	else
		res = ft_strdup(str);
	if (!BUFFER_SIZE || BUFFER_SIZE <= 0 || read(fd, 0, 0) < 0)
		return (NULL);
	while (res)
	{
		chars_read = read(fd, tmp, BUFFER_SIZE);
		if (chars_read < 0)
			return (free(res), NULL);
		else if (chars_read == 0)
			break ;
		tmp[chars_read] = '\0';
		res = ft_strjoin(res, tmp);
		n_found = ft_strchr(tmp, '\n');
		if (n_found)
			break ;
	}
	return (res);
}

char	*process_str(char *str)
{
	char	*right;
	char	*left;
	int		n_pos;

	n_pos = 0;
	while (str[n_pos] != '\0' && str[n_pos] != '\n')
		n_pos++;
	left = ft_substr(str, 0, n_pos);
	right = ft_substr(str, n_pos + 1, ft_strlen(str) - n_pos);
printf ("string > %s left >  %s right > %s \n", str, left, right);	
	free(str);
	str = ft_strdup(right);
	return (left);
}

char	*get_next_line(int fd)
{
	static char	*buf = NULL;
	char		*line;
	char		*tmp_buf;


	line = NULL;
	if (buf == NULL)
		buf = ft_strdup("");
	tmp_buf = ft_strjoin(buf, fill_str(buf, line, fd));
	buf = tmp_buf;
	line = process_str(buf);
printf ("line, buf in the end > %s  buf    %s   \n", line,  buf);	
	if (line == NULL && ft_strlen(buf) == 0)
	{
		free(buf);
		return (NULL);
	}

	return (line);
}

int main (void)
{
	int fd;
	char 	*str;

	fd = open("test.txt", O_RDONLY);
	str = get_next_line(fd);
	printf("m1 %s\n", str);
	str = get_next_line(fd);
	printf("m2 %s\n", str);
	str = get_next_line(fd);
	printf("m3 %s\n", str);
	str = get_next_line(fd);
	printf("m4 %s\n", str);
	str = get_next_line(fd);
	printf("m5 %s\n", str);


}