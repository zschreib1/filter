#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
        //Loop through the rows
    for (int i = 0; i < height; i++)
    {
        //Loop through the columns
        for (int j = 0; j < width; j++)
        {
            //1. Determine the average of the red, green and blue values (per pixel)
            //a) Add up red, green and blue values (sum)
            float sum = image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed;

            //b) Calculate average (avg) by dividing the sum by 3
            float avg = sum / 3;

            //2. Round avg to the nearest integer and update value of
            //   red, green and blue in each pixel to the value of avg.
            image[i][j].rgbtBlue = round(avg);
            image[i][j].rgbtGreen = round(avg);
            image[i][j].rgbtRed = round(avg);
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    // Loop through all the rows
    for (int i = 0; i < height; i++)
    {
        int k = 1;

        // Loop through the columns until half of the width in order to
        // reflect the image horizontally
        for (int j = 0; j < width / 2; j++)
        {
            //Swap the red pixels using a temporary variable (Redtemp): swap the leftmost
            //pixel with the rightmost pixel, then the inner left most pixel with the inner
            //right most pixel etc until you get to the pixel in the middle column (width / 2)
            int Redtemp = image[i][j].rgbtRed;
            image[i][j].rgbtRed = image[i][width - k].rgbtRed;
            image[i][width - k].rgbtRed = Redtemp;

            //Swap the green pixels using a temporary variable (Greentemp): same reasoning
            //as for red pixels
            int Greentemp = image[i][j].rgbtGreen;
            image[i][j].rgbtGreen = image[i][width - k].rgbtGreen;
            image[i][width - k].rgbtGreen = Greentemp;

            //Swap the blue pixels using a temporary variable (Bluetemp): same reasoning
            //as for red pixels
            int Bluetemp = image[i][j].rgbtBlue;
            image[i][j].rgbtBlue = image[i][width - k].rgbtBlue;
            image[i][width - k].rgbtBlue = Bluetemp;

            //Update value of k in order to move columns and swap other pixels in the 2D array
            k++;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    //Copy the original image using a nested for loop to copy each color value for each pixel
    //into the new imgcpy data struct that will be used to calculate the blur filter averages
    RGBTRIPLE imgcpy[height][width];

    //Loop through the rows
    for (int i = 0; i < height; i++)
    {
        //Loop through the columns
        for (int j = 0; j < width; j++)
        {
            imgcpy[i][j].rgbtRed = image[i][j].rgbtRed;
		    imgcpy[i][j].rgbtGreen = image[i][j].rgbtGreen;
		    imgcpy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //Loop through the rows
    for (int i = 0; i < height; i++)
    {
        //Loop through the columns
        for (int j = 0; j < width; j++)
        {
            //For top row of the image: If upper left corner pixel
            if (i == 0 && j == 0)
            {
                //Determine the red color value
                float sumRed = imgcpy[i][j].rgbtRed + imgcpy[i][j + 1].rgbtRed + imgcpy[i + 1][j].rgbtRed + imgcpy[i + 1][j + 1].rgbtRed;
                float avgRed = sumRed / 4;
                int blurRed = round(avgRed);
                image[i][j].rgbtRed = blurRed;

                //Determine the green color value
                float sumGreen = imgcpy[i][j].rgbtGreen + imgcpy[i][j + 1].rgbtGreen + imgcpy[i + 1][j].rgbtGreen + imgcpy[i + 1][j + 1].rgbtGreen;
                float avgGreen = sumGreen / 4;
                int blurGreen = round(avgGreen);
                image[i][j].rgbtGreen = blurGreen;

                //Determine the blue color value
                float sumBlue = imgcpy[i][j].rgbtBlue + imgcpy[i][j + 1].rgbtBlue + imgcpy[i + 1][j].rgbtBlue + imgcpy[i + 1][j + 1].rgbtBlue;
                float avgBlue = sumBlue / 4;
                int blurBlue = round(avgBlue);
                image[i][j].rgbtBlue = blurBlue;
            }

            //For top row of the image: If upper right corner pixel
            else if (i == 0 && j == (width - 1))
            {
                //Determine the red color value
                float sumRed = imgcpy[i][j].rgbtRed + imgcpy[i][j - 1].rgbtRed + imgcpy[i + 1][j - 1].rgbtRed + imgcpy[i + 1][j].rgbtRed;
                float avgRed = sumRed / 4;
                int blurRed = round(avgRed);
                image[i][j].rgbtRed = blurRed;

                //Determine the green color value
                float sumGreen = imgcpy[i][j].rgbtGreen + imgcpy[i][j - 1].rgbtGreen + imgcpy[i + 1][j - 1].rgbtGreen + imgcpy[i + 1][j].rgbtGreen;
                float avgGreen = sumGreen / 4;
                int blurGreen = round(avgGreen);
                image[i][j].rgbtGreen = blurGreen;

                //Determine the blue color value
                float sumBlue = imgcpy[i][j].rgbtBlue + imgcpy[i][j - 1].rgbtBlue + imgcpy[i + 1][j - 1].rgbtBlue + imgcpy[i + 1][j].rgbtBlue;
                float avgBlue = sumBlue / 4;
                int blurBlue = round(avgBlue);
                image[i][j].rgbtBlue = blurBlue;
            }

            //For top row of the image: If top row pixel (excluding upper left and upper right corner pixels)
            else if (i == 0 && j > 0 && j < width - 1)
            {
                //Determine the red color value
                float sumRed =  imgcpy[i][j].rgbtRed + imgcpy[i][j - 1].rgbtRed + imgcpy[i][j + 1].rgbtRed + imgcpy[i + 1][j - 1].rgbtRed +
                                imgcpy[i + 1][j].rgbtRed + imgcpy[i + 1][j + 1].rgbtRed;
                float avgRed = sumRed / 6;
                int blurRed = round(avgRed);
                image[i][j].rgbtRed = blurRed;

                //Determine the green color value
                float sumGreen = imgcpy[i][j].rgbtGreen + imgcpy[i][j - 1].rgbtGreen + imgcpy[i][j + 1].rgbtGreen + imgcpy[i + 1][j - 1].rgbtGreen +
                                 imgcpy[i + 1][j].rgbtGreen + imgcpy[i + 1][j + 1].rgbtGreen;
                float avgGreen = sumGreen / 6;
                int blurGreen = round(avgGreen);
                image[i][j].rgbtGreen = blurGreen;

                //Determine the blue color value
                float sumBlue = imgcpy[i][j].rgbtBlue + imgcpy[i][j - 1].rgbtBlue + imgcpy[i][j + 1].rgbtBlue + imgcpy[i + 1][j - 1].rgbtBlue +
                                imgcpy[i + 1][j].rgbtBlue + imgcpy[i + 1][j + 1].rgbtBlue;
                float avgBlue = sumBlue / 6;
                int blurBlue = round(avgBlue);
                image[i][j].rgbtBlue = blurBlue;
            }

            //For bottom row of the image: If lower left corner pixel
            else if (i == (height - 1) && j == 0)
            {
                //Determine the red color value
                float sumRed = imgcpy[i][j].rgbtRed + imgcpy[i][j + 1].rgbtRed + imgcpy[i - 1][j].rgbtRed + imgcpy[i - 1][j + 1].rgbtRed;
                float avgRed = sumRed / 4;
                int blurRed = round(avgRed);
                image[i][j].rgbtRed = blurRed;

                //Determine the green color value
                float sumGreen = imgcpy[i][j].rgbtGreen + imgcpy[i][j + 1].rgbtGreen + imgcpy[i - 1][j].rgbtGreen + imgcpy[i - 1][j + 1].rgbtGreen;
                float avgGreen = sumGreen / 4;
                int blurGreen = round(avgGreen);
                image[i][j].rgbtGreen = blurGreen;

                //Determine the blue color value
                float sumBlue = imgcpy[i][j].rgbtBlue + imgcpy[i][j + 1].rgbtBlue + imgcpy[i - 1][j].rgbtBlue + imgcpy[i - 1][j + 1].rgbtBlue;
                float avgBlue = sumBlue / 4;
                int blurBlue = round(avgBlue);
                image[i][j].rgbtBlue = blurBlue;
            }

            //For bottom row of the image: If lower right corner pixel
            else if (i == (height - 1) && j == (width - 1))
            {
                //Determine the red color value
                float sumRed = imgcpy[i][j].rgbtRed + imgcpy[i][j - 1].rgbtRed + imgcpy[i - 1][j - 1].rgbtRed + imgcpy[i - 1][j].rgbtRed;
                float avgRed = sumRed / 4;
                int blurRed = round(avgRed);
                image[i][j].rgbtRed = blurRed;

                //Determine the green color value
                float sumGreen = imgcpy[i][j].rgbtGreen + imgcpy[i][j - 1].rgbtGreen + imgcpy[i - 1][j - 1].rgbtGreen + imgcpy[i - 1][j].rgbtGreen;
                float avgGreen = sumGreen / 4;
                int blurGreen = round(avgGreen);
                image[i][j].rgbtGreen = blurGreen;

                //Determine the blue color value
                float sumBlue = imgcpy[i][j].rgbtBlue + imgcpy[i][j - 1].rgbtBlue + imgcpy[i - 1][j - 1].rgbtBlue + imgcpy[i - 1][j].rgbtBlue;
                float avgBlue = sumBlue / 4;
                int blurBlue = round(avgBlue);
                image[i][j].rgbtBlue = blurBlue;
            }

            //For bottom row of the image: If bottom row pixel (excluding bottom left and bottom right corner pixels)
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
                //Determine the red color value
                float sumRed =  imgcpy[i][j].rgbtRed + imgcpy[i][j - 1].rgbtRed + imgcpy[i][j + 1].rgbtRed + imgcpy[i - 1][j - 1].rgbtRed +
                                imgcpy[i - 1][j].rgbtRed + imgcpy[i - 1][j + 1].rgbtRed;
                float avgRed = sumRed / 6;
                int blurRed = round(avgRed);
                image[i][j].rgbtRed = blurRed;

                //Determine the green color value
                float sumGreen = imgcpy[i][j].rgbtGreen + imgcpy[i][j - 1].rgbtGreen + imgcpy[i][j + 1].rgbtGreen + imgcpy[i - 1][j - 1].rgbtGreen +
                                 imgcpy[i - 1][j].rgbtGreen + imgcpy[i - 1][j + 1].rgbtGreen;
                float avgGreen = sumGreen / 6;
                int blurGreen = round(avgGreen);
                image[i][j].rgbtGreen = blurGreen;

                //Determine the blue color value
                float sumBlue = imgcpy[i][j].rgbtBlue + imgcpy[i][j - 1].rgbtBlue + imgcpy[i][j + 1].rgbtBlue + imgcpy[i - 1][j - 1].rgbtBlue +
                                imgcpy[i - 1][j].rgbtBlue + imgcpy[i - 1][j + 1].rgbtBlue;
                float avgBlue = sumBlue / 6;
                int blurBlue = round(avgBlue);
                image[i][j].rgbtBlue = blurBlue;
            }

            //For left side of the image (excluding top or bottom row)
            else if (i > 0 && i < height - 1 && j == 0)
            {
                //Determine the red color value
                float sumRed =  imgcpy[i][j].rgbtRed + imgcpy[i][j + 1].rgbtRed + imgcpy[i - 1][j].rgbtRed + imgcpy[i - 1][j + 1].rgbtRed +
                                imgcpy[i + 1][j].rgbtRed + imgcpy[i + 1][j + 1].rgbtRed;
                float avgRed = sumRed / 6;
                int blurRed = round(avgRed);
                image[i][j].rgbtRed = blurRed;

                //Determine the green color value
                float sumGreen = imgcpy[i][j].rgbtGreen + imgcpy[i][j + 1].rgbtGreen + imgcpy[i - 1][j].rgbtGreen + imgcpy[i - 1][j + 1].rgbtGreen +
                                 imgcpy[i + 1][j].rgbtGreen + imgcpy[i + 1][j + 1].rgbtGreen;
                float avgGreen = sumGreen / 6;
                int blurGreen = round(avgGreen);
                image[i][j].rgbtGreen = blurGreen;

                //Determine the blue color value
                float sumBlue = imgcpy[i][j].rgbtBlue + imgcpy[i][j + 1].rgbtBlue + imgcpy[i - 1][j].rgbtBlue + imgcpy[i - 1][j + 1].rgbtBlue +
                                imgcpy[i + 1][j].rgbtBlue + imgcpy[i + 1][j + 1].rgbtBlue;
                float avgBlue = sumBlue / 6;
                int blurBlue = round(avgBlue);
                image[i][j].rgbtBlue = blurBlue;
            }

            //For right side of the image (excluding top or bottom row)
            else if (i > 0 && i < height - 1 && j == (width - 1))
            {
                //Determine the red color value
                float sumRed =  imgcpy[i][j].rgbtRed + imgcpy[i][j - 1].rgbtRed + imgcpy[i - 1][j - 1].rgbtRed + imgcpy[i - 1][j].rgbtRed +
                                imgcpy[i + 1][j - 1].rgbtRed + imgcpy[i + 1][j].rgbtRed;
                float avgRed = sumRed / 6;
                int blurRed = round(avgRed);
                image[i][j].rgbtRed = blurRed;

                //Determine the green color value
                float sumGreen = imgcpy[i][j].rgbtGreen + imgcpy[i][j - 1].rgbtGreen + imgcpy[i - 1][j - 1].rgbtGreen + imgcpy[i - 1][j].rgbtGreen +
                                 imgcpy[i + 1][j - 1].rgbtGreen + imgcpy[i + 1][j].rgbtGreen;
                float avgGreen = sumGreen / 6;
                int blurGreen = round(avgGreen);
                image[i][j].rgbtGreen = blurGreen;

                //Determine the blue color value
                float sumBlue = imgcpy[i][j].rgbtBlue + imgcpy[i][j - 1].rgbtBlue + imgcpy[i - 1][j - 1].rgbtBlue + imgcpy[i - 1][j].rgbtBlue +
                                imgcpy[i + 1][j - 1].rgbtBlue + imgcpy[i + 1][j].rgbtBlue;
                float avgBlue = sumBlue / 6;
                int blurBlue = round(avgBlue);
                image[i][j].rgbtBlue = blurBlue;
            }

            //For middle pixels (not on an edge of the image)
            else
            {
                //Determine the red color value
                float sumRed =  imgcpy[i][j].rgbtRed + imgcpy[i][j - 1].rgbtRed + imgcpy[i][j + 1].rgbtRed + imgcpy[i - 1][j - 1].rgbtRed +
                                imgcpy[i - 1][j].rgbtRed + imgcpy[i - 1][j + 1].rgbtRed + imgcpy[i + 1][j - 1].rgbtRed + imgcpy[i + 1][j].rgbtRed +
                                imgcpy[i + 1][j + 1].rgbtRed;
                float avgRed = sumRed / 9;
                int blurRed = round(avgRed);
                image[i][j].rgbtRed = blurRed;

                //Determine the green color value
                float sumGreen = imgcpy[i][j].rgbtGreen + imgcpy[i][j - 1].rgbtGreen + imgcpy[i][j + 1].rgbtGreen + imgcpy[i - 1][j - 1].rgbtGreen +
                                 imgcpy[i - 1][j].rgbtGreen + imgcpy[i - 1][j + 1].rgbtGreen + imgcpy[i + 1][j - 1].rgbtGreen + imgcpy[i + 1][j].rgbtGreen +
                                 imgcpy[i + 1][j + 1].rgbtGreen;
                float avgGreen = sumGreen / 9;
                int blurGreen = round(avgGreen);
                image[i][j].rgbtGreen = blurGreen;

                //Determine the blue color value
                float sumBlue = imgcpy[i][j].rgbtBlue + imgcpy[i][j - 1].rgbtBlue + imgcpy[i][j + 1].rgbtBlue + imgcpy[i - 1][j - 1].rgbtBlue +
                                imgcpy[i - 1][j].rgbtBlue + imgcpy[i - 1][j + 1].rgbtBlue + imgcpy[i + 1][j - 1].rgbtBlue + imgcpy[i + 1][j].rgbtBlue +
                                imgcpy[i + 1][j + 1].rgbtBlue;
                float avgBlue = sumBlue / 9;
                int blurBlue = round(avgBlue);
                image[i][j].rgbtBlue = blurBlue;
            }
        }
    }
    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    //Copy the original image using a nested for loop to copy each color value for each pixel
    //into the new imgcpy data struct that will be used to calculate the blur filter averages
    RGBTRIPLE imgcpy[height][width];

    //Loop through the rows
    for (int i = 0; i < height; i++)
    {
        //Loop through the columns
        for (int j = 0; j < width; j++)
        {
                imgcpy[i][j].rgbtRed = image[i][j].rgbtRed;
			    imgcpy[i][j].rgbtGreen = image[i][j].rgbtGreen;
			    imgcpy[i][j].rgbtBlue = image[i][j].rgbtBlue;
        }
    }

    //Loop through the rows
    for (int i = 0; i < height; i++)
    {
        //Loop through the columns
        for (int j = 0; j < width; j++)
        {
            //Treat the image as if there was a 1 pixel solid black border around the edge of the image:
            //therefore, trying to access a pixel past the edge of the image should be treated as a
            //solid black pixel (values of 0 for each of red, green, and blue).
            int outofbounds = 0;

            //For top row of the image: If upper left corner pixel
            if (i == 0 && j == 0)
            {
            //DETERMINE THE RED COLOR VALUE
                //Compute GXRed
                float GXRed =   -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds) +
                                -2 * (outofbounds) + 0 * (imgcpy[i][j].rgbtRed) + 2 * (imgcpy[i][j + 1].rgbtRed) +
                                -1 * (outofbounds) + 0 * (imgcpy[i + 1][j].rgbtRed) + 1 * (imgcpy[i + 1][j + 1].rgbtRed);

                //Compute GYRed
                float GYRed =   -1 * (outofbounds) + -2 * (outofbounds) + -1 * (outofbounds) +
                                0 * (outofbounds) + 0 * (imgcpy[i][j].rgbtRed) + 0 * (imgcpy[i][j + 1].rgbtRed) +
                                1 * (outofbounds) + 2 * (imgcpy[i + 1][j].rgbtRed) + 1 * (imgcpy[i + 1][j + 1].rgbtRed);

                //Determine edgeRed
                float newRed = sqrt((GXRed*GXRed) + (GYRed*GYRed));
                int edgeRed = round(newRed);
                image[i][j].rgbtRed = edgeRed;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }

            //DETERMINE THE GREEN COLOR VALUE
                //Compute GXGreen
                float GXGreen = -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds) +
                                -2 * (outofbounds) + 0 * (imgcpy[i][j].rgbtGreen) + 2 * (imgcpy[i][j + 1].rgbtGreen) +
                                -1 * (outofbounds) + 0 * (imgcpy[i + 1][j].rgbtGreen) + 1 * (imgcpy[i + 1][j + 1].rgbtGreen);

                //Compute GYGreen
                float GYGreen = -1 * (outofbounds) + -2 * (outofbounds) + -1 * (outofbounds) +
                                0 * (outofbounds) + 0 * (imgcpy[i][j].rgbtGreen) + 0 * (imgcpy[i][j + 1].rgbtGreen) +
                                1 * (outofbounds) + 2 * (imgcpy[i + 1][j].rgbtGreen) + 1 * (imgcpy[i + 1][j + 1].rgbtGreen);

                //Determine edgeGreen
                float newGreen = sqrt((GXGreen*GXGreen) + (GYGreen*GYGreen));
                int edgeGreen = round(newGreen);
                image[i][j].rgbtGreen = edgeGreen;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }

            //DETERMINE THE BLUE VALUE
                //Compute GXBlue
                float GXBlue =  -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds) +
                                -2 * (outofbounds) + 0 * (imgcpy[i][j].rgbtBlue) + 2 * (imgcpy[i][j + 1].rgbtBlue) +
                                -1 * (outofbounds) + 0 * (imgcpy[i + 1][j].rgbtBlue) + 1 * (imgcpy[i + 1][j + 1].rgbtBlue);

                //Compute GYBlue
                float GYBlue =  -1 * (outofbounds) + -2 * (outofbounds) + -1 * (outofbounds) +
                                0 * (outofbounds) + 0 * (imgcpy[i][j].rgbtBlue) + 0 * (imgcpy[i][j + 1].rgbtBlue) +
                                1 * (outofbounds) + 2 * (imgcpy[i + 1][j].rgbtBlue) + 1 * (imgcpy[i + 1][j + 1].rgbtBlue);

                //Determine edgeBlue
                float newBlue = sqrt((GXBlue*GXBlue) + (GYBlue*GYBlue));
                int edgeBlue = round(newBlue);
                image[i][j].rgbtBlue = edgeBlue;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
            }

            //For top row of the image: If upper right corner pixel
            else if (i == 0 && j == (width - 1))
            {
            //DETERMINE THE RED COLOR VALUE
                //Compute GXRed
                float GXRed =   -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds) +
                                -2 * (imgcpy[i][j - 1].rgbtRed) + 0 * (imgcpy[i][j].rgbtRed) + 2 * (outofbounds) +
                                -1 * (imgcpy[i + 1][j - 1].rgbtRed) + 0 * (imgcpy[i + 1][j].rgbtRed) + 1 * (outofbounds);

                //Compute GYRed
                float GYRed =   -1 * (outofbounds) + -2 * (outofbounds) + -1 * (outofbounds) +
                                0 * (imgcpy[i][j - 1].rgbtRed) + 0 * (imgcpy[i][j].rgbtRed) + 0 * (outofbounds) +
                                1 * (imgcpy[i + 1][j - 1].rgbtRed) + 2 * (imgcpy[i + 1][j].rgbtRed) + 1 * (outofbounds);

                //Determine edgeRed
                float newRed = sqrt((GXRed*GXRed) + (GYRed*GYRed));
                int edgeRed = round(newRed);
                image[i][j].rgbtRed = edgeRed;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }

            //DETERMINE THE GREEN COLOR VALUE
                //Compute GXGreen
                float GXGreen = -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds) +
                                -2 * (imgcpy[i][j - 1].rgbtGreen) + 0 * (imgcpy[i][j].rgbtGreen) + 2 * (outofbounds) +
                                -1 * (imgcpy[i + 1][j - 1].rgbtGreen) + 0 * (imgcpy[i + 1][j].rgbtGreen) + 1 * (outofbounds);

                //Compute GYGreen
                float GYGreen = -1 * (outofbounds) + -2 * (outofbounds) + -1 * (outofbounds) +
                                0 * (imgcpy[i][j - 1].rgbtGreen) + 0 * (imgcpy[i][j].rgbtGreen) + 0 * (outofbounds) +
                                1 * (imgcpy[i + 1][j - 1].rgbtGreen) + 2 * (imgcpy[i + 1][j].rgbtGreen) + 1 * (outofbounds);

                //Determine edgeGreen
                float newGreen = sqrt((GXGreen*GXGreen) + (GYGreen*GYGreen));
                int edgeGreen = round(newGreen);
                image[i][j].rgbtGreen = edgeGreen;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }

            //DETERMINE THE BLUE COLOR VALUE
                //Compute GXBlue
                float GXBlue =  -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds) +
                                -2 * (imgcpy[i][j - 1].rgbtBlue) + 0 * (imgcpy[i][j].rgbtBlue) + 2 * (outofbounds) +
                                -1 * (imgcpy[i + 1][j - 1].rgbtBlue) + 0 * (imgcpy[i + 1][j].rgbtBlue) + 1 * (outofbounds);

                //Compute GYBlue
                float GYBlue =  -1 * (outofbounds) + -2 * (outofbounds) + -1 * (outofbounds) +
                                0 * (imgcpy[i][j - 1].rgbtBlue) + 0 * (imgcpy[i][j].rgbtBlue) + 0 * (outofbounds) +
                                1 * (imgcpy[i + 1][j - 1].rgbtBlue) + 2 * (imgcpy[i + 1][j].rgbtBlue) + 1 * (outofbounds);

                //Determine edgeBlue
                float newBlue = sqrt((GXBlue*GXBlue) + (GYBlue*GYBlue));
                int edgeBlue = round(newBlue);
                image[i][j].rgbtBlue = edgeBlue;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
            }

            //For top row of the image: If top row pixel (excluding upper left and upper right corner pixels)
            else if (i == 0 && j > 0 && j < width - 1)
            {
            //DETERMINE THE RED COLOR VALUE
                //Compute GXRed
                float GXRed =   -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds) +
                                -2 * (imgcpy[i][j - 1].rgbtRed) + 0 * (imgcpy[i][j].rgbtRed) + 2 * (imgcpy[i][j + 1].rgbtRed) +
                                -1 * (imgcpy[i + 1][j - 1].rgbtRed) + 0 * (imgcpy[i + 1][j].rgbtRed) + 1 * (imgcpy[i + 1][j + 1].rgbtRed);

                //Compute GYRed
                float GYRed =   -1 * (outofbounds) + -2 * (outofbounds) + -1 * (outofbounds) +
                                0 * (imgcpy[i][j - 1].rgbtRed) + 0 * (imgcpy[i][j].rgbtRed) + 0 * (imgcpy[i][j + 1].rgbtRed) +
                                1 * (imgcpy[i + 1][j - 1].rgbtRed) + 2 * (imgcpy[i + 1][j].rgbtRed) + 1 * (imgcpy[i + 1][j + 1].rgbtRed);

                //Determine edgeRed
                float newRed = sqrt((GXRed*GXRed) + (GYRed*GYRed));
                int edgeRed = round(newRed);
                image[i][j].rgbtRed = edgeRed;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }

            //DETERMINE THE GREEN COLOR VALUE
                //Compute GXGreen
                float GXGreen = -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds) +
                                -2 * (imgcpy[i][j - 1].rgbtGreen) + 0 * (imgcpy[i][j].rgbtGreen) + 2 * (imgcpy[i][j + 1].rgbtGreen) +
                                -1 * (imgcpy[i + 1][j - 1].rgbtGreen) + 0 * (imgcpy[i + 1][j].rgbtGreen) + 1 * (imgcpy[i + 1][j + 1].rgbtGreen);

                //Compute GYGreen
                float GYGreen = -1 * (outofbounds) + -2 * (outofbounds) + -1 * (outofbounds) +
                                0 * (imgcpy[i][j - 1].rgbtGreen) + 0 * (imgcpy[i][j].rgbtGreen) + 0 * (imgcpy[i][j + 1].rgbtGreen) +
                                1 * (imgcpy[i + 1][j - 1].rgbtGreen) + 2 * (imgcpy[i + 1][j].rgbtGreen) + 1 * (imgcpy[i + 1][j + 1].rgbtGreen);

                //Determine edgeGreen
                float newGreen = sqrt((GXGreen*GXGreen) + (GYGreen*GYGreen));
                int edgeGreen = round(newGreen);
                image[i][j].rgbtGreen = edgeGreen;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }

            //DETERMINE THE BLUE VALUE
                //Compute GXBlue
                float GXBlue =  -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds) +
                                -2 * (imgcpy[i][j - 1].rgbtBlue) + 0 * (imgcpy[i][j].rgbtBlue) + 2 * (imgcpy[i][j + 1].rgbtBlue) +
                                -1 * (imgcpy[i + 1][j - 1].rgbtBlue) + 0 * (imgcpy[i + 1][j].rgbtBlue) + 1 * (imgcpy[i + 1][j + 1].rgbtBlue);

                float GYBlue =  -1 * (outofbounds) + -2 * (outofbounds) + -1 * (outofbounds) +
                                0 * (imgcpy[i][j - 1].rgbtBlue) + 0 * (imgcpy[i][j].rgbtBlue) + 0 * (imgcpy[i][j + 1].rgbtBlue) +
                                1 * (imgcpy[i + 1][j - 1].rgbtBlue) + 2 * (imgcpy[i + 1][j].rgbtBlue) + 1 * (imgcpy[i + 1][j + 1].rgbtBlue);

                //Determine edgeBlue
                float newBlue = sqrt((GXBlue*GXBlue) + (GYBlue*GYBlue));
                int edgeBlue = round(newBlue);
                image[i][j].rgbtBlue = edgeBlue;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
            }

            //For bottom row of the image: If lower left corner pixel
            else if (i == (height - 1) && j == 0)
            {
            //DETERMINE THE RED COLOR VALUE
                //Compute GXRed
                float GXRed =   -1 * (outofbounds) + 0 * (imgcpy[i - 1][j].rgbtRed) + 1 * (imgcpy[i - 1][j + 1].rgbtRed) +
                                -2 * (outofbounds) + 0 * (imgcpy[i][j].rgbtRed) + 2 * (imgcpy[i][j + 1].rgbtRed) +
                                -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds);

                //Compute GYRed
                float GYRed =   -1 * (outofbounds) + -2 * (imgcpy[i - 1][j].rgbtRed) + -1 * (imgcpy[i - 1][j + 1].rgbtRed) +
                                0 * (outofbounds) + 0 * (imgcpy[i][j].rgbtRed) + 0 * (imgcpy[i][j + 1].rgbtRed) +
                                1 * (outofbounds) + 2 * (outofbounds) + 1 * (outofbounds);

                //Determine edgeRed
                float newRed = sqrt((GXRed*GXRed) + (GYRed*GYRed));
                int edgeRed = round(newRed);
                image[i][j].rgbtRed = edgeRed;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }

            //DETERMINE THE GREEN COLOR VALUE
                //Compute GXGreen
                float GXGreen = -1 * (outofbounds) + 0 * (imgcpy[i - 1][j].rgbtGreen) + 1 * (imgcpy[i - 1][j + 1].rgbtGreen) +
                                -2 * (outofbounds) + 0 * (imgcpy[i][j].rgbtGreen) + 2 * (imgcpy[i][j + 1].rgbtGreen) +
                                -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds);

                //Compute GYGreen
                float GYGreen = -1 * (outofbounds) + -2 * (imgcpy[i - 1][j].rgbtGreen) + -1 * (imgcpy[i - 1][j + 1].rgbtGreen) +
                                0 * (outofbounds) + 0 * (imgcpy[i][j].rgbtGreen) + 0 * (imgcpy[i][j + 1].rgbtGreen) +
                                1 * (outofbounds) + 2 * (outofbounds) + 1 * (outofbounds);

                //Determine edgeGreen
                float newGreen = sqrt((GXGreen*GXGreen) + (GYGreen*GYGreen));
                int edgeGreen = round(newGreen);
                image[i][j].rgbtGreen = edgeGreen;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }

            //DETERMINE THE BLUE COLOR VALUE
                //Compute GXBlue
                float GXBlue =  -1 * (outofbounds) + 0 * (imgcpy[i - 1][j].rgbtBlue) + 1 * (imgcpy[i - 1][j + 1].rgbtBlue) +
                                -2 * (outofbounds) + 0 * (imgcpy[i][j].rgbtBlue) + 2 * (imgcpy[i][j + 1].rgbtBlue) +
                                -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds);

                //Compute GYBlue
                float GYBlue =  -1 * (outofbounds) + -2 * (imgcpy[i - 1][j].rgbtBlue) + -1 * (imgcpy[i - 1][j + 1].rgbtBlue) +
                                0 * (outofbounds) + 0 * (imgcpy[i][j].rgbtBlue) + 0 * (imgcpy[i][j + 1].rgbtBlue) +
                                1 * (outofbounds) + 2 * (outofbounds) + 1 * (outofbounds);

                //Determine edgeBlue
                float newBlue = sqrt((GXBlue*GXBlue) + (GYBlue*GYBlue));
                int edgeBlue = round(newBlue);
                image[i][j].rgbtBlue = edgeBlue;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
            }

            //For bottom row of the image: If lower right corner pixel
            else if (i == (height - 1) && j == (width - 1))
            {
            //DETERMINE THE RED COLOR VALUE
                //Compute GXRed
                float GXRed =   -1 * (imgcpy[i - 1][j - 1].rgbtRed) + 0 * (imgcpy[i - 1][j].rgbtRed) + 1 * (outofbounds) +
                                -2 * (imgcpy[i][j - 1].rgbtRed) + 0 * (imgcpy[i][j].rgbtRed) + 2 * (outofbounds) +
                                -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds);

                //Compute GYRed
                float GYRed =   -1 * (imgcpy[i - 1][j - 1].rgbtRed) + -2 * (imgcpy[i - 1][j].rgbtRed) + -1 * (outofbounds) +
                                0 * (imgcpy[i][j - 1].rgbtRed) + 0 * (imgcpy[i][j].rgbtRed) + 0 * (outofbounds) +
                                1 * (outofbounds) + 2 * (outofbounds) + 1 * (outofbounds);

                //Determine edgeRed
                float newRed = sqrt((GXRed*GXRed) + (GYRed*GYRed));
                int edgeRed = round(newRed);
                image[i][j].rgbtRed = edgeRed;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }

            //DETERMINE THE GREEN COLOR VALUE
                //Compute GXGreen
                float GXGreen = -1 * (imgcpy[i - 1][j - 1].rgbtGreen) + 0 * (imgcpy[i - 1][j].rgbtGreen) + 1 * (outofbounds) +
                                -2 * (imgcpy[i][j - 1].rgbtGreen) + 0 * (imgcpy[i][j].rgbtGreen) + 2 * (outofbounds) +
                                -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds);

                //Compute GYGreen
                float GYGreen = -1 * (imgcpy[i - 1][j - 1].rgbtGreen) + -2 * (imgcpy[i - 1][j].rgbtGreen) + -1 * (outofbounds) +
                                0 * (imgcpy[i][j - 1].rgbtGreen) + 0 * (imgcpy[i][j].rgbtGreen) + 0 * (outofbounds) +
                                1 * (outofbounds) + 2 * (outofbounds) + 1 * (outofbounds);

                //Determine edgeGreen
                float newGreen = sqrt((GXGreen*GXGreen) + (GYGreen*GYGreen));
                int edgeGreen = round(newGreen);
                image[i][j].rgbtGreen = edgeGreen;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }

            //DETERMINE THE BLUE COLOR VALUE
                //Compute GXBlue
                float GXBlue =  -1 * (imgcpy[i - 1][j - 1].rgbtBlue) + 0 * (imgcpy[i - 1][j].rgbtBlue) + 1 * (outofbounds) +
                                -2 * (imgcpy[i][j - 1].rgbtBlue) + 0 * (imgcpy[i][j].rgbtBlue) + 2 * (outofbounds) +
                                -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds);

                //Compute GYBlue
                float GYBlue =  -1 * (imgcpy[i - 1][j - 1].rgbtBlue) + -2 * (imgcpy[i - 1][j].rgbtBlue) + -1 * (outofbounds) +
                                0 * (imgcpy[i][j - 1].rgbtBlue) + 0 * (imgcpy[i][j].rgbtBlue) + 0 * (outofbounds) +
                                1 * (outofbounds) + 2 * (outofbounds) + 1 * (outofbounds);

                //Determine edgeBlue
                float newBlue = sqrt((GXBlue*GXBlue) + (GYBlue*GYBlue));
                int edgeBlue = round(newBlue);
                image[i][j].rgbtBlue = edgeBlue;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
            }

            //For bottom row of the image: If bottom row pixel (excluding bottom left and bottom right corner pixels)
            else if (i == height - 1 && j > 0 && j < width - 1)
            {
            //DETERMINE THE RED COLOR VALUE
                //Compute GXRed
                float GXRed =   -1 * (imgcpy[i - 1][j - 1].rgbtRed) + 0 * (imgcpy[i - 1][j].rgbtRed) + 1 * (imgcpy[i - 1][j + 1].rgbtRed) +
                                -2 * (imgcpy[i][j - 1].rgbtRed) + 0 * (imgcpy[i][j].rgbtRed) + 2 * (imgcpy[i][j + 1].rgbtRed) +
                                -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds);

                //Compute GYRed
                float GYRed =   -1 * (imgcpy[i - 1][j - 1].rgbtRed) + -2 * (imgcpy[i - 1][j].rgbtRed) + -1 * (imgcpy[i - 1][j + 1].rgbtRed) +
                                0 * (imgcpy[i][j - 1].rgbtRed) + 0 * (imgcpy[i][j].rgbtRed) + 0 * (imgcpy[i][j + 1].rgbtRed) +
                                1 * (outofbounds) + 2 * (outofbounds) + 1 * (outofbounds);

                //Determine edgeRed
                float newRed = sqrt((GXRed*GXRed) + (GYRed*GYRed));
                int edgeRed = round(newRed);
                image[i][j].rgbtRed = edgeRed;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }

            //DETERMINE THE GREEN COLOR VALUE
                //Compute GXGreen
                float GXGreen = -1 * (imgcpy[i - 1][j - 1].rgbtGreen) + 0 * (imgcpy[i - 1][j].rgbtGreen) + 1 * (imgcpy[i - 1][j + 1].rgbtGreen) +
                                -2 * (imgcpy[i][j - 1].rgbtGreen) + 0 * (imgcpy[i][j].rgbtGreen) + 2 * (imgcpy[i][j + 1].rgbtGreen) +
                                -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds);

                //Compute GYGreen
                float GYGreen = -1 * (imgcpy[i - 1][j - 1].rgbtGreen) + -2 * (imgcpy[i - 1][j].rgbtGreen) + -1 * (imgcpy[i - 1][j + 1].rgbtGreen) +
                                0 * (imgcpy[i][j - 1].rgbtGreen) + 0 * (imgcpy[i][j].rgbtGreen) + 0 * (imgcpy[i][j + 1].rgbtGreen) +
                                1 * (outofbounds) + 2 * (outofbounds) + 1 * (outofbounds);

                //Determine edgeGreen
                float newGreen = sqrt((GXGreen*GXGreen) + (GYGreen*GYGreen));
                int edgeGreen = round(newGreen);
                image[i][j].rgbtGreen = edgeGreen;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }

            //DETERMINE THE BLUE COLOR VALUE
                //Compute GXBlue
                float GXBlue =  -1 * (imgcpy[i - 1][j - 1].rgbtBlue) + 0 * (imgcpy[i - 1][j].rgbtBlue) + 1 * (imgcpy[i - 1][j + 1].rgbtBlue) +
                                -2 * (imgcpy[i][j - 1].rgbtBlue) + 0 * (imgcpy[i][j].rgbtBlue) + 2 * (imgcpy[i][j + 1].rgbtBlue) +
                                -1 * (outofbounds) + 0 * (outofbounds) + 1 * (outofbounds);

                //Compute GYBlue
                float GYBlue =  -1 * (imgcpy[i - 1][j - 1].rgbtBlue) + -2 * (imgcpy[i - 1][j].rgbtBlue) + -1 * (imgcpy[i - 1][j + 1].rgbtBlue) +
                                0 * (imgcpy[i][j - 1].rgbtBlue) + 0 * (imgcpy[i][j].rgbtBlue) + 0 * (imgcpy[i][j + 1].rgbtBlue) +
                                1 * (outofbounds) + 2 * (outofbounds) + 1 * (outofbounds);

                //Determine edgeBlue
                float newBlue = sqrt((GXBlue*GXBlue) + (GYBlue*GYBlue));
                int edgeBlue = round(newBlue);
                image[i][j].rgbtBlue = edgeBlue;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
            }

            //For left side of the image (excluding top or bottom row)
            else if (i > 0 && i < height - 1 && j == 0)
            {
            //DETERMINE THE RED COLOR VALUE
                //Compute GXRed
                float GXRed =   -1 *(outofbounds) + 0 * (imgcpy[i - 1][j].rgbtRed) + 1 * (imgcpy[i - 1][j + 1].rgbtRed) +
                                -2 * (outofbounds) + 0 * imgcpy[i][j].rgbtRed + 2 * (imgcpy[i][j + 1].rgbtRed) +
                                -1 * (outofbounds) + 0 * (imgcpy[i + 1][j].rgbtRed) + 1 * (imgcpy[i + 1][j + 1].rgbtRed);

                //Compute GYRed
                float GYRed =   -1 *(outofbounds) + -2 * (imgcpy[i - 1][j].rgbtRed) + -1 * (imgcpy[i - 1][j + 1].rgbtRed) +
                                0 * (outofbounds) + 0 * imgcpy[i][j].rgbtRed + 0 * (imgcpy[i][j + 1].rgbtRed) +
                                1 * (outofbounds) + 2 * (imgcpy[i + 1][j].rgbtRed) + 1 * (imgcpy[i + 1][j + 1].rgbtRed);

                //Determine edgeRed
                float newRed = sqrt((GXRed*GXRed) + (GYRed*GYRed));
                int edgeRed = round(newRed);
                image[i][j].rgbtRed = edgeRed;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }

            //DETERMINE THE GREEN COLOR VALUE
                //Compute GXGreen
                float GXGreen = -1 *(outofbounds) + 0 * (imgcpy[i - 1][j].rgbtGreen) + 1 * (imgcpy[i - 1][j + 1].rgbtGreen) +
                                -2 * (outofbounds) + 0 * imgcpy[i][j].rgbtGreen + 2 * (imgcpy[i][j + 1].rgbtGreen) +
                                -1 * (outofbounds) + 0 * (imgcpy[i + 1][j].rgbtGreen) + 1 * (imgcpy[i + 1][j + 1].rgbtGreen);

                //Compute GYGreen
                float GYGreen = -1 *(outofbounds) + -2 * (imgcpy[i - 1][j].rgbtGreen) + -1 * (imgcpy[i - 1][j + 1].rgbtGreen) +
                                0 * (outofbounds) + 0 * imgcpy[i][j].rgbtGreen + 0 * (imgcpy[i][j + 1].rgbtGreen) +
                                1 * (outofbounds) + 2 * (imgcpy[i + 1][j].rgbtGreen) + 1 * (imgcpy[i + 1][j + 1].rgbtGreen);

                //Determine edgeGreen
                float newGreen = sqrt((GXGreen*GXGreen) + (GYGreen*GYGreen));
                int edgeGreen = round(newGreen);
                image[i][j].rgbtGreen = edgeGreen;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }

            //DETERMINE THE BLUE COLOR VALUE
                //Compute GXBlue
                float GXBlue =  -1 *(outofbounds) + 0 * (imgcpy[i - 1][j].rgbtBlue) + 1 * (imgcpy[i - 1][j + 1].rgbtBlue) +
                                -2 * (outofbounds) + 0 * imgcpy[i][j].rgbtBlue + 2 * (imgcpy[i][j + 1].rgbtBlue) +
                                -1 * (outofbounds) + 0 * (imgcpy[i + 1][j].rgbtBlue) + 1 * (imgcpy[i + 1][j + 1].rgbtBlue);

                //Compute GYBlue
                float GYBlue =  -1 *(outofbounds) + -2 * (imgcpy[i - 1][j].rgbtBlue) + -1 * (imgcpy[i - 1][j + 1].rgbtBlue) +
                                0 * (outofbounds) + 0 * imgcpy[i][j].rgbtBlue + 0 * (imgcpy[i][j + 1].rgbtBlue) +
                                1 * (outofbounds) + 2 * (imgcpy[i + 1][j].rgbtBlue) + 1 * (imgcpy[i + 1][j + 1].rgbtBlue);

                //Determine edgeBlue
                float newBlue = sqrt((GXBlue*GXBlue) + (GYBlue*GYBlue));
                int edgeBlue = round(newBlue);
                image[i][j].rgbtBlue = edgeBlue;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
            }

            //For right side of the image (excluding top or bottom row)
            else if (i > 0 && i < height - 1 && j == (width - 1))
            {
            //DETERMINE THE RED COLOR VALUE
                //Compute GXRed
                float GXRed =   -1 * imgcpy[i - 1][j - 1].rgbtRed + 0 * imgcpy[i - 1][j].rgbtRed + 1 * (outofbounds) +
                                -2 * imgcpy[i][j - 1].rgbtRed + 0 * imgcpy[i][j].rgbtRed + 2 * (outofbounds) +
                                -1 * imgcpy[i + 1][j - 1].rgbtRed + 0 * imgcpy[i + 1][j].rgbtRed + 1 * (outofbounds);

                //Compute GYRed
                float GYRed =   -1 * imgcpy[i - 1][j - 1].rgbtRed + -2 * imgcpy[i - 1][j].rgbtRed + -1 * (outofbounds) +
                                0 * imgcpy[i][j - 1].rgbtRed + 0 * imgcpy[i][j].rgbtRed + 0 * (outofbounds) +
                                1 * imgcpy[i + 1][j - 1].rgbtRed + 2 * imgcpy[i + 1][j].rgbtRed + 1 * (outofbounds);

                //Determine edgeRed
                float newRed = sqrt((GXRed*GXRed) + (GYRed*GYRed));
                int edgeRed = round(newRed);
                image[i][j].rgbtRed = edgeRed;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeRed > 255)
                {
                    image[i][j].rgbtRed = 255;
                }

            //DETERMINE THE GREEN COLOR VALUE
                //Compute GXGreen
                float GXGreen = -1 * imgcpy[i - 1][j - 1].rgbtGreen + 0 * imgcpy[i - 1][j].rgbtGreen + 1 * (outofbounds) +
                                -2 * imgcpy[i][j - 1].rgbtGreen + 0 * imgcpy[i][j].rgbtGreen + 2 * (outofbounds) +
                                -1 * imgcpy[i + 1][j - 1].rgbtGreen + 0 * imgcpy[i + 1][j].rgbtGreen + 1 * (outofbounds);

                //Compute GYGreen
                float GYGreen = -1 * imgcpy[i - 1][j - 1].rgbtGreen + -2 * imgcpy[i - 1][j].rgbtGreen + -1 * (outofbounds) +
                                0 * imgcpy[i][j - 1].rgbtGreen + 0 * imgcpy[i][j].rgbtGreen + 0 * (outofbounds) +
                                1 * imgcpy[i + 1][j - 1].rgbtGreen + 2 * imgcpy[i + 1][j].rgbtGreen + 1 * (outofbounds);

                //Determine edgeGreen
                float newGreen = sqrt((GXGreen*GXGreen) + (GYGreen*GYGreen));
                int edgeGreen = round(newGreen);
                image[i][j].rgbtGreen = edgeGreen;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeGreen > 255)
                {
                    image[i][j].rgbtGreen = 255;
                }

            //DETERMINE THE BLUE COLOR VALUE
                //Compute GXBlue
                float GXBlue =  -1 * imgcpy[i - 1][j - 1].rgbtBlue + 0 * imgcpy[i - 1][j].rgbtBlue + 1 * (outofbounds) +
                                -2 * imgcpy[i][j - 1].rgbtBlue + 0 * imgcpy[i][j].rgbtBlue + 2 * (outofbounds) +
                                -1 * imgcpy[i + 1][j - 1].rgbtBlue + 0 * imgcpy[i + 1][j].rgbtBlue + 1 * (outofbounds);

                //Compute GYBlue
                float GYBlue = -1 * imgcpy[i - 1][j - 1].rgbtBlue + -2 * imgcpy[i - 1][j].rgbtBlue + -1 * (outofbounds) +
                                0 * imgcpy[i][j - 1].rgbtBlue + 0 * imgcpy[i][j].rgbtBlue + 0 * (outofbounds) +
                                1 * imgcpy[i + 1][j - 1].rgbtBlue + 2 * imgcpy[i + 1][j].rgbtBlue + 1 * (outofbounds);

                //Determine edgeBlue
                float newBlue = sqrt((GXBlue*GXBlue) + (GYBlue*GYBlue));
                int edgeBlue = round(newBlue);
                image[i][j].rgbtBlue = edgeBlue;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                if (edgeBlue > 255)
                {
                    image[i][j].rgbtBlue = 255;
                }
            }

    //For middle pixels (not on an edge of the image)
            else
            {
                //DETERMINE THE RED COLOR VALUE
                //Compute GX
                float GXRed =   (-1) * (imgcpy[i - 1][j - 1].rgbtRed) + 0 * (imgcpy[i - 1][j].rgbtRed) + 1 * (imgcpy[i - 1][j + 1].rgbtRed) +
                                (-2) * (imgcpy[i][j - 1].rgbtRed) + 0 * (imgcpy[i][j].rgbtRed) + 2 * (imgcpy[i][j + 1].rgbtRed) +
                                (-1) * imgcpy[i + 1][j - 1].rgbtRed + 0 * (imgcpy[i + 1][j].rgbtRed) + 1 * (imgcpy[i + 1][j + 1].rgbtRed);

                //Compute GY
                float GYRed =   (-1) * (imgcpy[i - 1][j - 1].rgbtRed) + (-2) * (imgcpy[i - 1][j].rgbtRed) + (-1) * (imgcpy[i - 1][j + 1].rgbtRed) +
                                0 * (imgcpy[i][j - 1].rgbtRed) + 0 * (imgcpy[i][j].rgbtRed) + 0 * (imgcpy[i][j + 1].rgbtRed) +
                                1 * imgcpy[i + 1][j - 1].rgbtRed + 2 * (imgcpy[i + 1][j].rgbtRed) + 1 * (imgcpy[i + 1][j + 1].rgbtRed);

                float newRed = sqrt((GXRed*GXRed) + (GYRed*GYRed));
                int edgeRed = round(newRed);
                image[i][j].rgbtRed = edgeRed;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                    if (edgeRed > 255)
                    {
                        image[i][j].rgbtRed = 255;
                    }

                //DETERMINE THE GREEN COLOR VALUE
                //Compute GX
                float GXGreen = (-1) * (imgcpy[i - 1][j - 1].rgbtGreen) + 0 * (imgcpy[i - 1][j].rgbtGreen) + 1 * (imgcpy[i - 1][j + 1].rgbtGreen) +
                                (-2) * (imgcpy[i][j - 1].rgbtGreen) + 0 * (imgcpy[i][j].rgbtGreen) + 2 * (imgcpy[i][j + 1].rgbtGreen) +
                                (-1) * imgcpy[i + 1][j - 1].rgbtGreen + 0 * (imgcpy[i + 1][j].rgbtGreen) + 1 * (imgcpy[i + 1][j + 1].rgbtGreen);

                //Compute GY
                float GYGreen = (-1) * (imgcpy[i - 1][j - 1].rgbtGreen) + (-2) * (imgcpy[i - 1][j].rgbtGreen) + (-1) * (imgcpy[i - 1][j + 1].rgbtGreen) +
                                0 * (imgcpy[i][j - 1].rgbtGreen) + 0 * (imgcpy[i][j].rgbtGreen) + 0 * (imgcpy[i][j + 1].rgbtGreen) +
                                1 * imgcpy[i + 1][j - 1].rgbtGreen + 2 * (imgcpy[i + 1][j].rgbtGreen) + 1 * (imgcpy[i + 1][j + 1].rgbtGreen);

                float newGreen = sqrt((GXGreen*GXGreen) + (GYGreen*GYGreen));
                int edgeGreen = round(newGreen);
                image[i][j].rgbtGreen = edgeGreen;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                    if (edgeGreen > 255)
                    {
                        image[i][j].rgbtGreen = 255;
                    }

                //DETERMINE THE BLUE COLOR VALUE
                //Compute GX
                float GXBlue =  (-1) * (imgcpy[i - 1][j - 1].rgbtBlue) + 0 * (imgcpy[i - 1][j].rgbtBlue) + 1 * (imgcpy[i - 1][j + 1].rgbtBlue) +
                                (-2) * (imgcpy[i][j - 1].rgbtBlue) + 0 * (imgcpy[i][j].rgbtBlue) + 2 * (imgcpy[i][j + 1].rgbtBlue) +
                                (-1) * imgcpy[i + 1][j - 1].rgbtBlue + 0 * (imgcpy[i + 1][j].rgbtBlue) + 1 * (imgcpy[i + 1][j + 1].rgbtBlue);

                //Compute GY
                float GYBlue =  (-1) * (imgcpy[i - 1][j - 1].rgbtBlue) + (-2) * (imgcpy[i - 1][j].rgbtBlue) + (-1) * (imgcpy[i - 1][j + 1].rgbtBlue) +
                                0 * (imgcpy[i][j - 1].rgbtBlue) + 0 * (imgcpy[i][j].rgbtBlue) + 0 * (imgcpy[i][j + 1].rgbtBlue) +
                                1 * imgcpy[i + 1][j - 1].rgbtBlue + 2 * (imgcpy[i + 1][j].rgbtBlue) + 1 * (imgcpy[i + 1][j + 1].rgbtBlue);

                float newBlue = sqrt((GXBlue*GXBlue) + (GYBlue*GYBlue));
                int edgeBlue = round(newBlue);
                image[i][j].rgbtBlue = edgeBlue;

                //Cap the result to 255 (the maximum value for an 8-bit color value)
                    if (edgeBlue > 255)
                    {
                        image[i][j].rgbtBlue = 255;
                    }
                }
            }
        }
    return;
}