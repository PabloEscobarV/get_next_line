/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: blackrider <blackrider@student.42.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:17:58 by polenyc           #+#    #+#             */
/*   Updated: 2024/01/12 22:12:10 by blackrider       ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	char	*str;
	int		file;

	file = open("file.txt", O_RDONLY);
    printf("BUFFER SIZE: %d\n", BUFFER_SIZE);
	str = get_next_line(file);
	while (str)
	{
		printf("result: %s", str);
		free(str);
		str = get_next_line(file);
	}
	printf("end: %s\n", str);
	free(str);
	close(file);
	return (0);
}