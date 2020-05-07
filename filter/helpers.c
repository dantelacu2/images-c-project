#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            float average = ((float) image[h][w].rgbtBlue + (float) image[h][w].rgbtRed + (float) image[h][w].rgbtGreen) / 3.0;
            average = round(average);
            image[h][w].rgbtBlue = average;
            image[h][w].rgbtGreen = average;
            image[h][w].rgbtRed = average;
        }
    }
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            int originalRed = image[h][w].rgbtRed;
            int originalGreen = image[h][w].rgbtGreen;
            int originalBlue = image[h][w].rgbtBlue;

            float sepiaRed = .393 * (float) originalRed + .769 * (float) originalGreen + .189 * (float) originalBlue;
            float sepiaGreen = .349 * (float) originalRed + .686 * (float) originalGreen + .168 * (float) originalBlue;
            float sepiaBlue = .272 * (float) originalRed + .534 * (float) originalGreen + .131 * (float) originalBlue;

            sepiaRed = round(sepiaRed);
            sepiaGreen = round(sepiaGreen);
            sepiaBlue = round(sepiaBlue);
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

            image[h][w].rgbtBlue = sepiaBlue;
            image[h][w].rgbtGreen = sepiaGreen;
            image[h][w].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int h = 0; h < (height); h++)
    {
        for (int w = 0; w < (width / 2); w++)
        {
            int redInter = image[h][w].rgbtRed;
            int greenInter = image[h][w].rgbtGreen;
            int blueInter = image[h][w].rgbtBlue;

            image[h][w].rgbtRed = image[h][(width - 1) - w].rgbtRed;
            image[h][w].rgbtGreen = image[h][(width - 1) - w].rgbtGreen;
            image[h][w].rgbtBlue = image[h][(width - 1) - w].rgbtBlue;

            image[h][(width - 1) - w].rgbtRed = redInter;
            image[h][(width - 1) - w].rgbtGreen = greenInter;
            image[h][(width - 1) - w].rgbtBlue = blueInter;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE newImage[height][width];

    int widthStart = 0;
    int heightStart = 0;
    int gap = 0;
    int gap2 = 0;
//loops through each picture
    for (int h = 0; h < height; h++)
    {
        for (int w = 0; w < width; w++)
        {
            widthStart = 0;
            heightStart = 0;
            gap = 0;
            gap2 = 0;

            float blueValue = 0.0, greenValue = 0.0, redValue = 0.0;

            if (h == 0)
            {
                heightStart = 1;
                gap = 1;
            }
            else if (h == height - 1)
            {
                gap = 1;
            }
            if (w == 0)
            {
                widthStart = 1;
                gap2 = 1;
            }
            else if (w == width - 1)
            {
                gap2 = 1;
            }

            float counter = 0;

            for (int y = (h - 1 + heightStart); y < (h - 1 + heightStart + 3 - gap); y++)
            {
                for (int x = (w - 1 + widthStart); x < (w - 1 + widthStart + 3 - gap2); x++)
                {
                    blueValue += image[y][x].rgbtBlue;
                    greenValue += image[y][x].rgbtGreen;
                    redValue += image[y][x].rgbtRed;
                    counter++;
                }
            }

            blueValue = blueValue / counter;
            greenValue = greenValue / counter;
            redValue = redValue / counter;

            blueValue = round(blueValue);
            greenValue = round(greenValue);
            redValue = round(redValue);

            int nBlueValue = (int) blueValue;
            int nGreenValue = (int) greenValue;
            int nRedValue = (int) redValue;

            newImage[h][w].rgbtBlue = nBlueValue;
            newImage[h][w].rgbtGreen = nGreenValue;
            newImage[h][w].rgbtRed = nRedValue;


        }
    }

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtBlue = newImage[a][b].rgbtBlue;
            image[a][b].rgbtGreen = newImage[a][b].rgbtGreen;
            image[a][b].rgbtRed = newImage[a][b].rgbtRed;
        }
    }
    return;
}
