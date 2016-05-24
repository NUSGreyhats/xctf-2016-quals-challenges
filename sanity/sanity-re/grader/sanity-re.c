#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char buf[] = "XCTF{34sy_p3a5y_no?}";
    strcpy(buf, "potatoes potatoes\n");
    printf("%s", buf);
    return 0;
}
