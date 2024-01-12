/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:43:28 by polenyc           #+#    #+#             */
/*   Updated: 2024/01/12 22:03:25 by blackrider       ###   ########.fr       */
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
	
	if (data && ft_strchr(data, NEXT_LINE))
		return (data);
	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	count = read(fd, buffer, BUFFER_SIZE);
	while (count > 0)
	{
		buffer[count] = '\0';
		data = strjoinfree(data, buffer, 0);
		if (ft_strchr(buffer, NEXT_LINE))
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
	if (!data->str)
		return (NULL);
	chnext = ft_strchr(data->str, NEXT_LINE);
	if (!chnext)
	{
		chnext = ft_strdup(data->str, '\0');
		free(data->str);
		data->str = NULL;
		return (chnext);
	}
	tmp = ft_strdup(data->str, *chnext);
	chnext = ft_strdup(chnext + 1, '\0');
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

// char	*readdata(char *data, int fd)
// {
// 	char	*buffer;
// 	int		count;
	
// 	if (data && ft_strchr(data, NEXT_LINE))
// 		return (data);
// 	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	count = read(fd, buffer, BUFFER_SIZE);
// 	while (count > 0)
// 	{
// 		buffer[count] = '\0';
// 		data = strjoinfree(data, buffer, 0);
// 		if (ft_strchr(buffer, NEXT_LINE))
// 			break ;
// 		count = read(fd, buffer, BUFFER_SIZE);
// 	}
// 	free(buffer);
// 	return (data);
// }

// char	*splitdata(char **data)
// {
// 	char	*chnext;
// 	char	*tmp;

// 	chnext = ft_strchr(*data, NEXT_LINE);
// 	if (!chnext)
// 	{
// 		chnext = ft_strdup(*data, '\0');
// 		free(*data);
// 		*data = NULL;
// 		return (chnext);
// 	}
// 	tmp = ft_strdup(*data, *chnext);
// 	chnext = ft_strdup(chnext + 1, '\0');
// 	if (!(*chnext))
// 	{
// 		free(chnext);
// 		chnext = NULL;
// 	}
// 	free(*data);
// 	*data = chnext;
// 	return (tmp);
// }

// char	*get_next_line(int fd)
// {
// 	static t_datafd	*data = NULL;
// 	t_datafd		*tmp;

// 	if (fd < 0 || BUFFER_SIZE < 1)
// 		return (NULL);
// 	if (!data)
// 		data = crtdata(NULL, fd);
// 	tmp = data;
//     while (tmp->next && tmp->fd != fd)
//         tmp = tmp->next;
//     if (!tmp->next && tmp->fd != fd)
//     {
// 		tmp->next = crtdata(ft_strdup("", '\0'), fd);
//         tmp = tmp->next;
//     }
// 	tmp->str = readdata(tmp->str, fd);
// 	if (!tmp->str)
// 		return (delnode(&data, fd));
// 	return (splitdata(&(tmp->str)));
// }

// char	*readdata(int fd)
// {
// 	char	*buffer;
// 	char	*str;
// 	int		count;

// 	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
// 	count = read(fd, buffer, BUFFER_SIZE);
// 	if (count < 1)
// 	{
// 		free(buffer);
// 		return (NULL);
// 	}
// 	buffer[count] = '\0';
// 	str = ft_strdup("", '\0');
// 	while (count && !ft_strchr(buffer, NEXT_LINE))
// 	{
// 		str = strjoinfree(str, buffer, 0);
// 		if (!str)
// 		{
// 			free(buffer);
// 			return (str);
// 		}
// 		count = read(fd, buffer, BUFFER_SIZE);
// 		buffer[count] = '\0';
// 	}
// 	return (strjoinfree(str, buffer, 2));
// }

// char	*splitdata(t_datafd *data, char *str)
// {
// 	char	*chnext;
// 	char	*tmp;

// 	chnext = ft_strchr(data->str, NEXT_LINE);
// 	if (chnext)
// 	{
// 		tmp = ft_strdup(data->str, *chnext);
// 		chnext = ft_strdup(chnext + 1, '\0');
// 		free(data->str);
// 		data->str = strjoinfree(chnext, str, 2);
// 		return (tmp);
// 	}
// 	chnext = ft_strchr(str, NEXT_LINE);
// 	if (!chnext)
// 		return (strjoinfree(data->str, str, 2));
// 	tmp = strjoinfree(data->str, ft_strdup(str, *chnext), 2);
// 	data->str = ft_strdup(chnext + 1, '\0');
// 	free(str);
// 	return (tmp);
// }

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

// int main(void)
// {
// 	char	*str;
// 	char	*str1;
//     char    *str2;
// 	int		file;
// 	int		file1;
//     int     file2;

// 	file = open("file.txt", O_RDONLY);
// 	file1 = open("file1.txt", O_RDONLY);
//     file2 = open("file3.txt", O_RDONLY);
//     printf("BUFFER SIZE: %d\n", BUFFER_SIZE);
// 	str = get_next_line(file);
// 	str1 = get_next_line(file1);
//     str2 = get_next_line(file2);
// 	while (str || str1 || str2)
// 	{
// 		printf("file\t%s", str);
// 		printf("file1:\t%s", str1);
//         printf("file2:\t%s", str2);
// 		free(str);
// 		free(str1);
// 		free(str2);
// 		str = get_next_line(file);
// 		str1 = get_next_line(file1);
//         str2 = get_next_line(file2);
// 	}
// 	free(str);
// 	free(str1);
// 	free(str2);
// 	close(file);
// 	close(file1);
//     close(file2);
// 	return (0);
// }