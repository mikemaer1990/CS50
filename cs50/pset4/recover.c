#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

int main(int argc, char *argv[])
{
    // initializing variables
    // filename to fit ###.jpg\0
    char filename[8];
    // keep track of how many jpegs we have found for naming purposes
    int jpegCount = 0;
    // keep track of whether or not we are currently inside of a jpeg in the loop
    int jpegOpen = 0;
    // creating buffer to search through 512 byte chunks
    unsigned char buffer[512];
    // file for storing each chunk and writing the data to
    FILE *jpg = NULL;
    // validating user inputs
    if (argc != 2)
    {
        printf("Usage: ./recover filename.jpg\n");
        return 1;
    }
    // opening file to match users input (filename.jpg)
    FILE *f = fopen(argv[1], "r");
    // validating file exists and can be read
    if (f == NULL)
    {
        printf("Invalid file\n");
        return 1;
    }
    // loop through the file in 512 byte chunks until there is less than 512 bytes remaining
    while (fread(&buffer, 512, 1, f))
    {
        // check for jpeg signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] & 0xf0) == 0xe0)
        {
            // if already inside of a jpeg
            if (jpegOpen == 1)
            {
                // close current file
                fclose(jpg);
                // create new file name
                sprintf(filename, "%03i.jpg", jpegCount);
                // create new file
                jpg = fopen(filename, "a");
                // increment our jpeg count
                jpegCount++;
            }
            // if not inside of a file already
            else if (jpegOpen == 0)
            {
                // create new file name
                sprintf(filename, "%03i.jpg", jpegCount);
                // create new file
                jpg = fopen(filename, "w");
                // set jpegOpen to 1
                jpegOpen = 1;
                // increment jpeg count
                jpegCount++;
            }
            // write the buffer to our file
            fwrite(&buffer, 512, 1, jpg);
        }
        // if not the beginning of a new jpeg file (based on the signature)
        else
        {
            // check if we are inside of a jpeg already
            if (jpegOpen == 1)
            {
                // write the buffer to our file
                fwrite(&buffer, 512, 1, jpg);
            }
        }
    }
    // close both images and return 0
    fclose(f);
    fclose(jpg);
    return 0;
}
