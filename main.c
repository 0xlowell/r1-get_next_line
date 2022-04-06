
#include "get_next_line.h"

int    main(int argc, char **argv)
{
    int    fd = open(argv[1], O_RDONLY);
    char    *retour;
    int    i = 1;
    (void)argc;
	while (i)
    {
        retour = get_next_line(fd);
		if (!retour)
			return (0);
        printf("%s", retour);
        i++;
    }
}
