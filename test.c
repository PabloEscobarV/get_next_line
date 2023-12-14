/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: polenyc <polenyc@student.fr>               +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/14 15:17:58 by polenyc           #+#    #+#             */
/*   Updated: 2023/12/14 15:30:06 by polenyc          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include <fcntl.h>

int main(void)
{
	char	*str;
	int		file;

	file = open("file.txt", O_RDONLY);
	str = get_next_line(0);
	while (str)
	{
		printf("%s", str);
		str = get_next_line(0);
	}
	close(file);
	return (0);
}