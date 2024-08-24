#include <cs50.h>
#include <stdint.h>
#include <stdio.h>

int main(int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Impropper message\n");
        return 1;
    }

    // check file

    string filename = argv[2];
    FILE *file = fopen("filename", "r");

    //open file

    if (file == NULL)
    {
        printf("No such found\n");
        return 1;
    }

    uint8_t buffer[4];
    uint8_t signature[] = {37, 80, 68, 70};

    fread(buffer, 1, 4, file);
    fclose(file);

    for (int i = 0; i < 4; i++)
    {
        {
            if (buffer[i] != signature[i])
            {
                printf("Likely not a pdf\n");
                flcose(file);
                return 0;
            }
        }
       printf("Likely pdf\n");
       fclose(file);
       return 0;
      }
}
