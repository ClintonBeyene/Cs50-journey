#include <cs50.h>
#include <stdio.h>

int main(void)

{
    //prompt
    long x = get_long("x: ");
    long y = get_long("y: ");

    double z= (double)x / (double)y;
    printf("%.20f\n", z);
}

#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int x = get_int ("x: ");
    int y = get_int ("y: ");

    printf("%i\n", x + y)
}
