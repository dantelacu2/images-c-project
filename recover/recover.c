#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    //checks for the correct amount of arguments
    if (argc != 2)
    {
        printf("Usage: ./recover 'filename'");
        return 1;
    }
    // create output file

    char filename[8];
    FILE *p = NULL;

    // opens card.raw
    FILE *q = fopen(argv[1], "r");
    // creates buffer array
    unsigned char buffer[512];
    // reads the card.raw in to a buffer string
    int jpegCounter = 0;

    // n is 1 when the fread function correctly reads one block of 512

    while (fread(buffer, 1, 512, q) == 512)
    {
        if ((buffer[0] == 0xff) && (buffer[1] == 0xd8) && (buffer[2] == 0xff) && ((buffer[3] & 0xf0) == 0xe0))
        {
            if (jpegCounter > 0)
            {
                fclose(p);
            }
            // creates a new file
            sprintf(filename, "%03i.jpg", jpegCounter);
            p = fopen(filename, "w+");


            // writes to the new file
            fwrite(buffer, 1, 512, p);
            jpegCounter++;
        }
        else
        {
            if (jpegCounter > 0)
            {
                fwrite(buffer, 1, 512, p);
            }
        }
    }

    fclose(p);
    fclose(q);
}
