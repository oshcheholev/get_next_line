/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: oshcheho <oshcheho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/04/26 11:44:11 by oshcheho          #+#    #+#             */
/*   Updated: 2024/04/30 14:59:30 by oshcheho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <stdlib.h>
# include <fcntl.h>
# include <string.h>

# include <unistd.h>
# include <stddef.h>

# include <stdio.h>

size_t	ft_strlen(char const *s);
char	*ft_strjoin(char const *s1, char const *s2);
char	*ft_strchr(const char *s, int c);
char	*ft_substr(char const *s, unsigned int start, size_t len);
char	*init_str(void);
char	*ft_strdup(const char *s);
char	*fill_str(char *str, char *buf, int fd);
char	*process_str(char *str);
char	*get_next_line(int fd);

typedef struct s_list
{
	char			*content;
	struct s_list	*next;
}	t_list;

#endif