/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:53:36 by polenyc           #+#    #+#             */
/*   Updated: 2024/02/07 14:32:26 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif
# define NEXT_LINE	'\n'

typedef struct s_data
{
	int				fd;
	char			*str;
	struct s_data	*next;
	struct s_data	*previos;
}					t_datafd;

char	*get_next_line(int fd);
char	*ft_strchr_gnl(const char *s, int ch);
char	*ft_strdup_gnl(const char *src, char end);
char	*strjoinfree(char *s1, char *s2, int pos);

#endif
