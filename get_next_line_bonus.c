/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:43:28 by polenyc           #+#    #+#             */
/*   Updated: 2024/02/07 14:32:11 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

t_datafd	*delnode(t_datafd **data)
{
	t_datafd	*tmp;

	if (!(*data))
		return (NULL);
	if (!(*data)->previos)
	{
		tmp = (*data)->next;
		if (tmp)
			tmp->previos = NULL;
		free((*data)->str);
		free(*data);
		return (tmp);
	}
	if ((*data)->next)
		tmp = (*data)->next;
	else
		tmp = (*data)->previos;
	(*data)->previos->next = (*data)->next;
	if ((*data)->next)
		(*data)->next->previos = (*data)->previos;
	free((*data)->str);
	free(*data);
	return (tmp);
}

t_datafd	*crtdata(t_datafd *data, t_datafd *prev, int fd)
{
	t_datafd	*tmp;

	if (!data)
	{
		data = malloc(sizeof(t_datafd));
		if (!data)
			return (NULL);
		data->fd = fd;
		data->str = NULL;
		data->next = NULL;
		data->previos = prev;
		return (data);
	}
	tmp = data;
	while (data && data->fd != fd)
		data = data->previos;
	if (data)
		return (data);
	while (tmp->next && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp);
	tmp->next = crtdata(NULL, tmp, fd);
	return (tmp->next);
}

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

char	*gnl(t_datafd *data, int fd)
{
	char	*chnext;
	char	*tmp;

	data->str = readdata(data->str, fd);
	if (!data->str || !(*(data->str)))
		return (NULL);
	chnext = ft_strchr_gnl(data->str, NEXT_LINE);
	if (!chnext)
	{
		chnext = ft_strdup_gnl(data->str, '\0');
		free(data->str);
		data->str = NULL;
		return (chnext);
	}
	tmp = ft_strdup_gnl(data->str, *chnext);
	chnext = ft_strdup_gnl(chnext + 1, '\0');
	free(data->str);
	data->str = chnext;
	return (tmp);
}

char	*get_next_line(int fd)
{
	static t_datafd	*data = NULL;
	char			*tmp;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!data)
		data = crtdata(NULL, NULL, fd);
	data = crtdata(data, data, fd);
	tmp = gnl(data, fd);
	if (!tmp)
		data = delnode(&data);
	return (tmp);
}
