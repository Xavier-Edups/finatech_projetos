#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdint.h>
#include <stdbool.h>

int main(int argc, char *argv[])
{
    // check the number of arguments
    if (argc != 2)
    {
        fprintf(stderr, "ERROR: Invalid number of arguments.\nUsage:recover <file name>");
        return 1;
    }

    // open infile
    char *infile = argv[1];
    FILE *inptr = fopen(infile, "r");

    // check if infile is valid
    if (!inptr)
    {
        fprintf(stderr, "ERROR: Could not open %s.\n", infile);
        return 2;
    }

    // create array for bytes in the FAT blocks
    uint8_t fat[512];

    // name for files
    char name[100];
    int nameint = 0;

    // iterates beetween bytes checking the jpeg signature
    while (!feof(inptr))
    {
        fread(fat, 512, 1, inptr);
        if (fat[0] == 255 &&
            fat[1] == 216 &&
            fat[2] == 255 &&
            (fat[3] & 0xf0) == 0xe0)
        {
            // open outfile
            sprintf(name, "%03i.jpg", nameint);
            FILE *outptr = fopen(name, "w");

            // write first block
            fwrite(fat, 512, 1, outptr);

            // add 1 to the file name
            ++nameint;

            // check for existence of other jpeg or end of file
            do
            {
                // write outfile
                fread(fat, 512, 1, inptr);
                if (fat[0] == 255 &&
                    fat[1] == 216 &&
                    fat[2] == 255 &&
                    (fat[3] & 0xf0) == 0xe0)
                {
                    fclose(outptr);
                    break;
                }
                if (feof(inptr))
                {
                    fclose(outptr);
                    break;
                }
                fwrite(fat, 512, 1, outptr);
            }
            while (true);

            // go back a block if not end of file
            if (!feof(inptr))
            {
                fseek(inptr, -512, SEEK_CUR);
            }
        }
    }

    // close infile
    fclose(inptr);

    return 0;
}