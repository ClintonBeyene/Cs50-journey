#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
typedef uint8_t BYTE;

int main(int argc, char *argv[])
{
    //check argument from user
    if (argc != 2)
    {
        printf("Usage: ./recover Image\n");
        return 1;
    }

    // to take user input
    char *user_input = argv[1];
    FILE *input_pointer = fopen(user_input, "r");

    if (input_pointer == NULL)
    {
        printf("Error: could not open the file\n");
        return 2;
    }

    // intialize variables
    BYTE buffer[512];

    int count = 0;

    FILE *img_pointer = NULL;

    char *filename = malloc(8 * sizeof(char));

    //repeat until end of card
    while (fread(buffer, sizeof(char), 512, input_pointer))
    {
        // if start of a new jpg
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] * 0xf0) == 0xe0)
        {
            // if not first jpg, close previous
            if ((count != 0))
            {
                fclose(img_pointer);
            }

            //intialise file
            sprintf(filename, "%03i.jpg", count);
            img_pointer = fopen(filename, "w");
            count++;
        }
        //if jpg has been found, write to file
       if ((img_pointer != 0))
       {
        fwrite(&buffer, sizeof(char), 512, img_pointer);
       }
    }
    fclose(input_pointer);
    fclose(img_pointer);
    free(filename);

    return 0;
}
