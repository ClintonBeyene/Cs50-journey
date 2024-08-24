#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./recover Image\n");
        return 1;
    }

    char *name = argv[1];
    FILE *card = fopen(name, "r");

    if (card == NULL)
    {
        printf("Error: can not open card\n");
        return 2;
    }
    BYTE buffer[512];
    int count = 0;
    FILE *new_card = NULL;
    char *filename = malloc(8 * sizeof(char));

    while (fread(buffer, sizeof(char), 512, card))
    {
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            if ((count != 0))
            {
                fclose(new_card);
            }
            sprintf(filename, "%03i.jpg", count);
            new_card = fopen(filename, "w");
            count++;
        }
        if ((new_card != NULL))
        {
            fwrite(&buffer, sizeof(char), 512, new_card);
        }
    }
    fclose(card);
    fclose(new_card);
    free(filename);

    return 0;
}
