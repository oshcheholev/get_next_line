/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/27 14:53:09 by oshcheho          #+#    #+#             */
/*   Updated: 2024/05/11 15:24:23 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(char const *s)
{
	size_t	i;

	i = 0;
	if (!s)
		return (0);
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}

char	*ft_strchr(const char *s, int c)
{
	int	i;

	i = 0;
	if (!s)
		return (NULL);
	while (s[i] != '\0')
	{
		if ((unsigned char)s[i] == (unsigned char)c)
			return ((char *)&s[i]);
		i++;
	}
	if ((unsigned char)c == '\0')
		return ((char *)&s[i]);
	return (NULL);
}



char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	size_t	i;
	char	*res;

	if (!s)
		return (NULL);
	i = 0;
	if (start >= ft_strlen(s))
		len = 0;
	else if (len > ft_strlen(s))
		len = ft_strlen(s) - start;
	else if (len + start > ft_strlen(s))
		len = ft_strlen(s) - start;
	res = malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	while (i < len && s[i + start] != '\0')
	{
		res[i] = s[i + start];
		i++;
	}
	res[i] = '\0';
	return (res);
}
char	*extract_right(char *str, int n)
{
	char	*res;
	int i;

	i = 0;
//	printf("extract   %lu\n", ft_strlen(str) - n + 1);
	res = (char *)malloc((ft_strlen(str) - n) + 1 * sizeof(char));
	if (!res)
		return (NULL);
	while (str[n] != '\0')
	{
		res[i] = str[n];
		i++;
		n++;
	}
	res[i + 1] = '\0';
	return (res);
}

char	*init_str(void)
{
	char	*res;

	res = malloc(1);
	res[0] = '\0';
	return (res);

}