/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:43:28 by polenyc           #+#    #+#             */
/*   Updated: 2023/12/14 14:50:23 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char	*readdata(int fd)
{
	char	*buffer;
	char	*str;
	int		count;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	count = read(fd, buffer, BUFFER_SIZE);
	if (count < 1)
	{
		free(buffer);
		return (NULL);
	}
	buffer[count] = '\0';
	str = ft_strdup("", '\0');
	while (count && !ft_strchr(buffer, NEXT_LINE))
	{
		str = strjoinfree(str, buffer, 0);
		if (!str)
		{
			free(buffer);
			return (str);
		}
		count = read(fd, buffer, BUFFER_SIZE);
		buffer[count] = '\0';
	}
	return (strjoinfree(str, buffer, 2));
}

char	*splitdata(char **data, char *str)
{
	char	*chnext;
	char	*tmp;

	chnext = ft_strchr(*data, NEXT_LINE);
	if (chnext)
	{
		tmp = ft_strdup(*data, *chnext);
		chnext = ft_strdup(chnext + 1, '\0');
		free(*data);
		*data = strjoinfree(chnext, str, 2);
		return (tmp);
	}
	chnext = ft_strchr(str, NEXT_LINE);
	if (!chnext)
		return (strjoinfree(*data, str, 1));
	tmp = strjoinfree(*data, ft_strdup(str, *chnext), 2);
	*data = ft_strdup(chnext + 1, '\0');
	free(str);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*data = NULL;
	char		*str;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!data)
		data = ft_strdup("", '\0');
	if (!data)
		return (NULL);
	str = readdata(fd);
	if (!str)
		return (NULL);
	return (splitdata(&data, str));
}

// int main(void)
// {
// 	char	*str;
// 	char	*str1;
// 	int		file;

// 	file = open("file.txt", O_RDONLY);
// 	str = get_next_line(file);
// 	while (str)
// 	{
// 		printf("%s", str);
// 		str = get_next_line(file);
// 	}
// 	close(file);
// 	return (0);
// }
