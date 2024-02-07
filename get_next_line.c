/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:43:28 by polenyc           #+#    #+#             */
/*   Updated: 2024/02/07 14:33:32 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

char	*readdata(char *data, int fd)
{
	char	*buffer;
	int		count;

	if (data && ft_strchr_gnl(data, NEXT_LINE))
		return (data);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	count = read(fd, buffer, BUFFER_SIZE);
	while (count > 0)
	{
		buffer[count] = '\0';
		data = strjoinfree(data, buffer, 0);
		if (ft_strchr_gnl(buffer, NEXT_LINE))
			break ;
		count = read(fd, buffer, BUFFER_SIZE);
	}
	free(buffer);
	return (data);
}

char	*splitdata(char **data)
{
	char	*chnext;
	char	*tmp;

	chnext = ft_strchr_gnl(*data, NEXT_LINE);
	if (!chnext)
	{
		chnext = ft_strdup_gnl(*data, '\0');
		free(*data);
		*data = NULL;
		return (chnext);
	}
	tmp = ft_strdup_gnl(*data, *chnext);
	chnext = ft_strdup_gnl(chnext + 1, '\0');
	if (!(*chnext))
	{
		free(chnext);
		chnext = NULL;
	}
	free(*data);
	*data = chnext;
	return (tmp);
}

char	*get_next_line(int fd)
{
	static char	*data = NULL;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	data = readdata(data, fd);
	if (!data)
		return (NULL);
	return (splitdata(&data));
}
