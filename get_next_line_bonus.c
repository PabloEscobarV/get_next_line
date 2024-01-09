/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:43:28 by polenyc           #+#    #+#             */
/*   Updated: 2024/01/09 15:06:22 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

t_datafd	*crtdata(char *str, int fd, t_datafd *previos)
{
	t_datafd	*data;

	data = malloc(sizeof(t_datafd));
	if (!data)
		return (NULL);
	data->fd = fd;
	data->str = str;
	if (!data->str)
		return (NULL);
	data->next = NULL;
	data->previos = previos;
	return (data);
}

t_datafd	*finddatafd(t_datafd **data, int fd)
{
	t_datafd	*tmp;

	if (!(*data) || !data)
		return (NULL);
	tmp = *data;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->next;
	}
	tmp = *data;
	while (tmp)
	{
		if (tmp->fd == fd)
			return (tmp);
		tmp = tmp->previos;
	}
	return (NULL);
}

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

char	*splitdata(t_datafd *data, char *str)
{
	char	*chnext;
	char	*tmp;

	chnext = ft_strchr(data->str, NEXT_LINE);
	if (chnext)
	{
		tmp = ft_strdup(data->str, *chnext);
		chnext = ft_strdup(chnext + 1, '\0');
		free(data->str);
		data->str = strjoinfree(chnext, str, 2);
		return (tmp);
	}
	chnext = ft_strchr(str, NEXT_LINE);
	if (!chnext)
		return (strjoinfree(data->str, str, 2));
	tmp = strjoinfree(data->str, ft_strdup(str, *chnext), 2);
	data->str = ft_strdup(chnext + 1, '\0');
	free(str);
	return (tmp);
}

void	delnode(t_datafd **data, t_datafd *tmp)
{
	if (tmp->previos)
	{
		tmp->previos->next = tmp->next;
		return ;
	}
	if (!tmp->next)
	{
		free(tmp->str);
		free(tmp);
		// *data = NULL;
		return ;
	}
	*data = (*data)->next;
	free(tmp->str);
	free(tmp);
	return ;
}

char	*get_next_line(int fd)
{
	static t_datafd	*data = NULL;
	t_datafd		*tmp;
	char			*str;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	if (!data)
		data = crtdata(ft_strdup("", '\0'), fd, NULL);
	str = readdata(fd);
	if (!str)
	{
		tmp = finddatafd(&data, fd);
		if (!tmp)
			return (NULL);
		delnode(&data, tmp);
		return (NULL);
	}
	tmp = finddatafd(&data, fd);
	if (!tmp)
		tmp = crtdata(ft_strdup("", '\0'), fd, data);
	data = tmp;
	return (splitdata(data, str));
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

int main(void)
{
	char	*str;
	char	*str1;
    char    *str2;
	int		file;
	int		file1;
    int     file2;

	file = open("file.txt", O_RDONLY);
	file1 = open("file1.txt", O_RDONLY);
    file2 = open("file3.txt", O_RDONLY);
    printf("BUFFER SIZE: %d\n", BUFFER_SIZE);
	str = get_next_line(file);
	str1 = get_next_line(file1);
    str2 = get_next_line(file2);
	while (str || str1 || str2)
	{
		printf("file\t%s", str);
		printf("file1:\t%s", str1);
        printf("file2:\t%s", str2);
		free(str);
		free(str1);
		free(str2);
		str = get_next_line(file);
		str1 = get_next_line(file1);
        str2 = get_next_line(file2);
	}
	free(str);
	free(str1);
	free(str2);
	close(file);
	close(file1);
    close(file2);
	return (0);
}