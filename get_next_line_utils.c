/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/13 17:17:10 by polenyc           #+#    #+#             */
/*   Updated: 2024/02/07 14:33:07 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

char	*ft_strchr_gnl(const char *s, int ch)
{
	unsigned char	c;

	c = (unsigned char)ch;
	while (*s != c && *s != '\0')
		++s;
	if (*s == c)
		return ((char *)s);
	return (NULL);
}

size_t	ft_strlen_gnl(const char *str)
{
	size_t	count;

	count = 0;
	if (!str)
		return (count);
	while (str[count] != '\0')
		++count;
	return (count);
}

char	*ft_strdup_gnl(const char *src, char end)
{
	char	*tmp;
	int		size;

	size = 0;
	if (!src)
		return (NULL);
	while (src[size] != end && src[size])
		++size;
	if (end != '\0')
		++size;
	tmp = (char *)malloc((size + 1) * sizeof(char));
	if (!tmp)
		return (NULL);
	tmp[size] = '\0';
	while (--size >= 0)
		tmp[size] = src[size];
	return (tmp);
}

char	*ft_strcpy_gnl(char *dest, char const *src)
{
	if (!dest || !src)
		return (dest);
	while (*src != 0)
	{
		*dest = *src;
		++dest;
		++src;
	}
	*dest = '\0';
	return (dest);
}

char	*strjoinfree(char *s1, char *s2, int pos)
{
	char	*arr;
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen_gnl(s1);
	size2 = ft_strlen_gnl(s2);
	arr = malloc((size1 + size2 + 1) * sizeof(char));
	if (!arr)
		return (NULL);
	ft_strcpy_gnl(ft_strcpy_gnl(arr, s1), s2);
	if (pos < 0)
		return (arr);
	if (pos == 0)
	{
		free((char *)s1);
		return (arr);
	}
	if (pos == 1)
	{
		free((char *)s2);
		return (arr);
	}
	free((char *)s1);
	free((char *)s2);
	return (arr);
}
