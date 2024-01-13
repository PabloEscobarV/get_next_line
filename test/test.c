#include "get_next_line.h"
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
	int		file;

	// file = open("file.txt", O_RDONLY);
    file = 42;
    printf("BUFFER SIZE: %d\n", BUFFER_SIZE);
    str = get_next_line(file);
	while (str)
	{
		printf("file\t%s", str);
		free(str);
		str = get_next_line(file);
	}
	printf("end: %s\n", str);
	free(str);
	return (0);
}