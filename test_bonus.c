/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:53:17 by polenyc           #+#    #+#             */
/*   Updated: 2024/01/12 22:13:22 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

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
		// printf("file1:\t%s\n", str1);
        // printf("file2:\t%s\n", str2);
		free(str);
		free(str1);
		free(str2);
		str = get_next_line(file);
		str1 = get_next_line(file1);
        str2 = get_next_line(file2);
	}
	printf("end: %s\n", str);
	free(str);
	free(str1);
	free(str2);
	close(file);
	close(file1);
    close(file2);
	return (0);
}
