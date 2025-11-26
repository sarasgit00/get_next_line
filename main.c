
#include <stdio.h>
#include <fcntl.h>
#include <stdlib.h>
#include "get_next_line.h"

int main(void)
{
    int fd;
    char *line;

    // fd = open("1char.txt", O_RDONLY);
    fd = open("1char.txt", O_RDWR);

    if (fd < 0)
        return (1);

    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }

    close(fd);
    return (0);
}

	// TEST("1char.txt", {
	// 	int fd = open(_title, O_RDONLY);
	// 	/* 1 */ test_gnl(fd, "0");
	// 	/* 2 */ test_gnl(fd, NULL);
	// });