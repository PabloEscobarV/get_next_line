/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:53:36 by polenyc           #+#    #+#             */
/*   Updated: 2023/12/14 00:08:00 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUFFER_SIZE
#define BUFFER_SIZE 10
#endif
#pragma once
#define NEXT_LINE	'\n'
typedef	struct	s_data
{
	int		fd;
	char	*str;
	struct s_data	*next;
}			t_datafd;

char	*ft_strchr(const char *s, int ch);
char	*ft_strdup(const char *src, char end);
char	*strjoinfree(char *s1, char *s2, int pos);
