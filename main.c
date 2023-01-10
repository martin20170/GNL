#include "get_next_line.h"
#include <stdio.h>
#include <stdlib.h>






int    main(void)
{
    int        fd;
    char    *str;

    fd = open("bob.txt", O_RDONLY);

    // str = get_next_line(fd);
    // str = get_next_line(fd);
    // str = get_next_line(fd);
    // str = get_next_line(fd);
    // str = get_next_line(fd);
    // str = get_next_line(fd);
    // str = get_next_line(fd);

    printf("%s", str = get_next_line(fd));
    printf("%s", str = get_next_line(fd));
    printf("%s", str = get_next_line(fd));
    printf("%s", str = get_next_line(fd));
    printf("%s", str = get_next_line(fd));
    printf("%s", str = get_next_line(fd));
    printf("%s", str = get_next_line(fd));
    printf("%s", str = get_next_line(fd));

    free(str);
    close(fd);
    return (0);
}


