#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>






int    main(void)
{
    int        fd;
    char    *str;

    fd = open("bob.txt", O_RDONLY);
    str = get_next_line(fd);
    //printf("\n%s\n", str);
    free(str);
    close(fd);
    return (0);
}


