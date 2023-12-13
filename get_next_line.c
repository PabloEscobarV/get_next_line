/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 17:43:28 by polenyc           #+#    #+#             */
/*   Updated: 2023/12/14 00:28:02 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <fcntl.h>

t_datafd	*crtdata(char *str, int fd)
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
	return (data);
}

t_datafd	*finddatafd(t_datafd **data, int fd)
{
	t_datafd	*tmp;

	if (!(*data))
	{
		*data = crtdata(ft_strdup("", '\0'), fd);
		return (*data);
	}
	tmp = *data;
	while (tmp->next && tmp->fd != fd)
		tmp = tmp->next;
	if (tmp->fd == fd)
		return (tmp);
	tmp->next = crtdata(ft_strdup("", '\0'), fd);
	return (tmp->next);
}

char	*readdata(int fd)
{
	char	*buffer;
	char	*str;
	int		count;

	buffer = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buffer)
		return (NULL);
	count = read(fd, buffer, BUFFER_SIZE);
	if (count < 1)
		return (NULL);
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

	chnext = ft_strchr(str, NEXT_LINE);
	if (!chnext)
		return (strjoinfree(data->str, str, 1));
	tmp = strjoinfree(data->str, ft_strdup(str, *chnext), 0);
	data->str = ft_strdup(chnext + 1, '\0');
	free(str);
	return (tmp);
}

char	*get_next_line(int fd)
{
	static t_datafd	*data = NULL;
	t_datafd		*tmp;
	char			*str;

	if (fd < 0 || BUFFER_SIZE < 1)
		return (NULL);
	str = readdata(fd);
	if (!str)
		return (NULL);
	tmp = finddatafd(&data, fd);
	return (splitdata(tmp, str));
}

void	ft_putstr_fd(char *s, int fd)
{
	while (*s)
		write(fd, s++, sizeof(char));
}

int main(void)
{
	char	*str;
	char	*str1;
	int		file;
	int		file1;

	file = open("file.txt", O_RDONLY);
	file1 = open("file1.txt", O_RDONLY);
	str = get_next_line(file);
	str1 = get_next_line(file1);
	while (str)
	{
		printf("%s", str);
		printf("%s", str1);
		str = get_next_line(file);
		str1 = get_next_line(file1);
	}
	close(file);
	close(file1);
	return (0);
}