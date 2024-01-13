
#include "get_next_line_bonus.h"
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

// int	main()
// {
// 	int		size_file;
// 	int		size_str;
// 	int		*files;
// 	char	**data;
// 	files = malloc(8 * sizeof(int));
// 	data = malloc(8 * sizeof(char *));
// 	files[]

	
// 	returtn (0);
// }

int main(void)
{
	char	*str;
	char	*str1;
    char    *str2;
	char	*str3;

	int		file;
	int		file1;
    int     file2;
	int		la_ten;


	file = open("file.txt", O_RDONLY);
	file1 = open("file1.txt", O_RDONLY);
    file2 = open("file3.txt", O_RDONLY);
	la_ten = open("lines_around_10.txt", O_RDONLY);

    printf("BUFFER SIZE: %d\n", BUFFER_SIZE);
	str = get_next_line(file);
	str1 = get_next_line(file1);
    str2 = get_next_line(file2);
	str3 = get_next_line(la_ten);

	while (str || str1 || str2)
	{
		printf("file\t%s\n", str);
		printf("file1:\t%s\n", str1);
        printf("file2:\t%s\n", str2);
		printf("la_ten\t%s\n", str3);

		free(str);
		free(str1);
		free(str2);
		free(str3);

		str = get_next_line(file);
		str1 = get_next_line(file1);
        str2 = get_next_line(file2);	
		str3 = get_next_line(la_ten);

	}
	printf("end: %s\n", str);
	free(str);
	free(str1);
	free(str2);
	free(str3);
	close(file);
	close(file1);
    close(file2);
	close(la_ten);
	return (0);
}