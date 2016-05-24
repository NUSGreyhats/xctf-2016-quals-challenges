#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main(int ac, char **av)
{
    char pass[] = "XCTF{B4byS73pT0N3wL4ngu4g3}";
    if (ac != 2)
        printf("usage:\n%s <password>\n", av[0]), exit(1);
    if (!strcmp(av[1], pass))
        puts("GG YOU WIN");
    else
        puts("NOOOOB !");
    return (0);
}
