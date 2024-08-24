#include <cs50.h>
#include <stdio.h>
#include <string.h>

int main(void)
{
    string names[] = {"Beyene", "Tadelech"};
    string numbers[] = {"+251937220207", "+251916138748"};

    string n = get_string("Name: ");
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(names[i], n) == 0 )
        {
            printf("found %s\n", numbers[i]);
            return 0;
        }
    }
    printf("not found\n");
    return 1;
}
