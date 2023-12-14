/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 14:53:17 by polenyc           #+#    #+#             */
/*   Updated: 2023/12/14 15:25:29 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

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
