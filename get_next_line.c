/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:53:09 by oshcheho          #+#    #+#             */
/*   Updated: 2024/05/13 14:29:58 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_strdup(char *s)
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

void free_and_null(char **str)
{
//	if (*str)
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
	res = (char *)malloc((ft_strlen(s1) + ft_strlen(s2) + 1)
			* sizeof(char));
	if (!res)
		return (NULL);
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
	res[i] = '\0';
	return (res);
}

char	*fill_str(int fd, char *line, char *tmp_buf)
{
	char	*tmp;
	int		chars_read;

	chars_read = 1;
	while (chars_read > 0)
	{
		chars_read = read(fd, tmp_buf, BUFFER_SIZE);
		if (chars_read < 0)
			return (free_and_null(&line), NULL);
		else if (chars_read == 0)
			break ;
		if (!tmp_buf)
			return (free_and_null(&line), NULL);
		tmp_buf[chars_read] = '\0';
		if (!line)
			line = ft_strdup("");
		tmp = line;
		line = ft_strjoin(tmp, tmp_buf);
		free_and_null(&tmp);
		if (ft_strchr(tmp_buf, '\n'))
			break ;
	}
	return (line);
}

char	*get_right(char *str)
{
	char	*right;
	int		n_pos;
	int		j;
	int		i;
//	static int count = 0;

	if (str == NULL)
		return (NULL);
	n_pos = 0;
	j = 0;
	while (str[n_pos] != '\n' && str[n_pos] != '\0')
		n_pos++;
	if (str[n_pos] == '\0')
		return (NULL);
	i = n_pos + 1;
	right = (char *)malloc((ft_strlen(str) - n_pos + 1) * sizeof(char));
	// count++;
	// if (count == 5)
	// 	return (free_and_null(&right), NULL);
//	printf ("len - npos  %lu         len %lu\n", ft_strlen(str) - n_pos, ft_strlen(str));
	if (!right)
		return (free_and_null(&right), NULL);
	while (str[i] != '\0')
		right[j++] = str[i++];
	right[j] = '\0';
	str[n_pos + 1] = '\0';
	if (*right == '\0')
		return (free_and_null(&right), NULL);
//printf("len   %lu    j  %d   right[j-1]   %c", ft_strlen(right), j, right[j - 1]);
	return (right);
}

// check if fd is correct and BUFFER_SIZE
// check if static_buf contains newLine, if it is => extract until newLine form static buf and return
// 

	// {
	// free(static_buf);
	// static_buf = NULL;
	// free(tmp_buf);
	// tmp_buf = NULL;
	// }

	// begin infinite while loop
	// check if static_buf contains newLine, if it is => extract until newLine from static buf and return
	// call read and append read chars to the buffer. If read returns 0 => return a copy of buffer and free it.

char	*get_next_line(int fd)
{
	static char	*static_buf;
	char		*line;
	char		*tmp_buf;
	// char		*temp;

	tmp_buf = (char *)malloc(BUFFER_SIZE + 1);
	if (!tmp_buf)
		return (free_and_null(&static_buf), free_and_null(&tmp_buf), NULL);
	if (fd < 0 || BUFFER_SIZE <= 0)
		return (free_and_null(&static_buf), free_and_null(&tmp_buf), NULL);
	line = fill_str(fd, static_buf, tmp_buf);
	free_and_null(&tmp_buf);
	if (!line)
	{
		static_buf = NULL;
		return (free_and_null(&line), NULL);
	}
	static_buf = get_right(line);
	if (!static_buf)
		return (free_and_null(&static_buf), line);
	// temp = get_right(line);
	// if (temp)
	// 	static_buf = temp;
	// else
	// 	return (free_and_null(&temp), free_and_null(&static_buf) , NULL);
	return (line);
}

// int main() {
//     // Open a file for reading
//     int fd = open("test_nl.txt", O_RDONLY);
//     if (fd < 0) {
//         perror("Failed to open file");
//         return 1; // Return an error code if the file can't be opened
//     }
// 	char *line;
	
// 	int i = 0;
// 	while (i < 2)
// 	{
// 		i++;
// 		line = get_next_line(fd);
// 		if (!line)
// 			break;
//     	printf("{%s}", line); // Print the line
// 		free(line);
// 	}
//     close(fd);
// 	return 0; // Successful completion
// }