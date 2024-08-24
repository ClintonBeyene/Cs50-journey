#include <cs50.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, string argv[])
{
   if (argc != 2)
   {
    printf("Improper usage\n");
    return 1;
   }

   //open file
   string filename = argv[2];
   FILE *file = fopen("filename", "r");

    // check
    if (file == NULL)
    {
        printf("No such file found\n");
        return 1;
    }

    uint8_t buffer[4];
    fread(buffer, 1, 4, file);
    for (int i = 0; i < 4; i++)
    {
        printf("%i ", buffer[i]);
    }
    printf("\n");
}
