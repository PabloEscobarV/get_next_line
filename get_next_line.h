/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:53:36 by polenyc           #+#    #+#             */
/*   Updated: 2024/01/09 12:19:19 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define NEXT_LINE	'\n'

typedef struct s_data
{
	int				fd;
	char			*str;
	struct s_data	*next;
}					t_datafd;

char	*get_next_line(int fd);
char	*ft_strchr(const char *s, int ch);
char	*ft_strdup(const char *src, char end);
char	*strjoinfree(char *s1, char *s2, int pos);

#endif