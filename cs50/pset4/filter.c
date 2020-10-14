#include "helpers.h"
#include <math.h>
#include <stdio.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    // for each pixel -- find the average of the RGB values and use that as the new value for all RGB
    for (int i = 0, h = height; i < h; i ++)
    {
        for (int j = 0, w = width; j < w; j++)
        {
            // calculate average -- discovered I must use 3.0 instead of 3 to get a properly rounded number
            float avg = round((image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtGreen = avg;
            image[i][j].rgbtBlue = avg;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i = 0, h = height; i < h; i ++)
    {
        for (int j = 0, w = width; j < w; j++)
        {
            // formula to calculate each colors new 'sepia' value
            int sepiaRed = round(.393 * image[i][j].rgbtRed + .769 * image[i][j].rgbtGreen + .189 * image[i][j].rgbtBlue);
            int sepiaGreen = round(.349 * image[i][j].rgbtRed + .686 * image[i][j].rgbtGreen + .168 * image[i][j].rgbtBlue);
            int sepiaBlue = round(.272 * image[i][j].rgbtRed + .534 * image[i][j].rgbtGreen + .131 * image[i][j].rgbtBlue);
            // really wish I could do this a different way
            // tried to make a function but couldnt return the value properly :(
            if (sepiaRed > 255)
            {
                sepiaRed = 255;
            }
            if (sepiaGreen > 255)
            {
                sepiaGreen = 255;
            }
            if (sepiaBlue > 255)
            {
                sepiaBlue = 255;
            }
            // apply 'sepia' color values
            image[i][j].rgbtRed = sepiaRed;
            image[i][j].rgbtGreen = sepiaGreen;
            image[i][j].rgbtBlue = sepiaBlue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // temp struct to store values
    RGBTRIPLE tmp[height][width];
    // calulate width array length
    int reflectWidth = width - 1;
    for (int i = 0; i < height; i++)
    {
        // learned here that I only needed to go over HALF of the image (obviously)
        // because originally I was successfully swapping pixels but then reverting what I had done
        for (int j = 0; j <= reflectWidth / 2; j++)
        {
            // Store temporary variables;
            int tempRed = image[i][j].rgbtRed;
            int tempGreen = image[i][j].rgbtGreen;
            int tempBlue = image[i][j].rgbtBlue;
            // swap left side pixels
            image[i][j].rgbtRed = image[i][reflectWidth - j].rgbtRed;
            image[i][j].rgbtGreen = image[i][reflectWidth - j].rgbtGreen;
            image[i][j].rgbtBlue = image[i][reflectWidth - j].rgbtBlue;
            // swap right side pixels
            image[i][reflectWidth - j].rgbtRed = tempRed;
            image[i][reflectWidth - j].rgbtGreen = tempGreen;
            image[i][reflectWidth - j].rgbtBlue = tempBlue;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE tmp[height][width];
    // originally I tried to just copy the image to a new struct - which didnt work
    // so I had to create a new struct and then use it to store the new values
    // for each pixel and then just copy the temp to the original image
    // not sure why it didn't work the other way around?

    // initialize avg variables
    float avgRed = 0;
    float avgGreen = 0;
    float avgBlue = 0;
    float count = 0;
    // loop through all pixels in image
    for (int i = 0; i < height; i ++)
    {
        for (int j = 0; j < width; j++)
        {
            // learned that you can use && statements INSIDE for loops!
            // loop through all pixels touching the selected pixel
            for (int k = i - 1; k <= i + 1 && k < height; k ++)
            {
                // ensure to not go outside of the image parameters
                if (k < 0)
                {
                    k = i;
                }
                for (int l = j - 1; l <= j + 1 && l < width; l ++)
                {
                    // ensure to not go outside of the image parameters
                    if (l < 0)
                    {
                        l = j;
                    }
                    // increment avg values and count
                    avgRed += image[k][l].rgbtRed;
                    avgGreen += image[k][l].rgbtGreen;
                    avgBlue += image[k][l].rgbtBlue;
                    count++;
                }
            }
            // calculate the average using the count variable
            avgRed = avgRed / count;
            avgGreen = avgGreen / count;
            avgBlue = avgBlue / count;
            // round each value
            tmp[i][j].rgbtRed = round(avgRed);
            tmp[i][j].rgbtGreen = round(avgGreen);
            tmp[i][j].rgbtBlue = round(avgBlue);
            // reset variables for next loop
            avgRed = 0;
            avgGreen = 0;
            avgBlue = 0;
            count = 0;
        }
    }
    // for loop to copy each pixel to the original image from the temporary
    for (int x = 0; x < height; x ++)
    {
        for (int y = 0; y < width; y ++)
        {
            image[x][y] = tmp[x][y];
        }
    }
    return;
}
