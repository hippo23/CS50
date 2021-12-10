#include "helpers.h"
#include <stdio.h>
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			int average = (image[i][j].rgbtBlue + image[i][j].rgbtGreen + image[i][j].rgbtRed) / 3;
			image[i][j].rgbtBlue = average;
			image[i][j].rgbtGreen = average;
			image[i][j].rgbtRed = average;
		}
	}
	return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
	printf("%i", width);
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < floor(width/2); j++)
		{
			RGBTRIPLE temp = image[i][j];

			image[i][j].rgbtBlue = image[i][(width-1)-j].rgbtBlue;
			image[i][j].rgbtGreen = image[i][(width-1)-j].rgbtGreen;
			image[i][j].rgbtRed = image[i][(width-1)-j].rgbtRed;

			image[i][(width-1)-j].rgbtBlue = temp.rgbtBlue;
			image[i][(width-1)-j].rgbtGreen = temp.rgbtGreen;
			image[i][(width-1)-j].rgbtRed = temp.rgbtRed;
		}
	}
	return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE image_clone[height][width];

	// iterate throught the pixels in the original image
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			int sum_blue = 0, sum_green = 0, sum_red = 0;
			int total_elements = 0;

			// getting the average
			for(int x = -1; x <= 1; x++)
			{
				for(int y = -1; y <= 1; y++)
				{
					if(i+x < height && i+x >= 0 && y+j < width && y+j >= 0)
					{
						sum_blue += image[x+i][y+j].rgbtBlue;
						sum_red += image[x+i][y+j].rgbtRed;
						sum_green += image[x+i][y+j].rgbtGreen;
						total_elements++;
					}
				}
			}

			// copy the blurred value to a temporary image holder, so that the following pixel values won't be affected	
			image_clone[i][j].rgbtBlue = floor(sum_blue / total_elements);
			image_clone[i][j].rgbtRed = floor(sum_red / total_elements);
			image_clone[i][j].rgbtGreen = floor(sum_green / total_elements);
		}
	}

	// assign blur to original image
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			image[i][j] = image_clone[i][j];
		}
	}
	return;
}
// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
	RGBTRIPLE image_clone[height][width];

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			// Gx
			int leftsum_blue = 0, leftsum_red = 0, leftsum_green = 0;
			int rightsum_blue = 0, rightsum_red = 0, rightsum_green = 0;
			int gx_blue, gx_red, gx_green;

			for(int x = -1; x <= 1; x++)
			{
				for(int y = -1; y <= 1; y++)
				{
					if(i+x < height && i+x >= 0 && y+j < width && y+j >= 0)
					{
						if (x == 0)
						{
							if (y < 0)
							{
								leftsum_blue += image[i+x][j+y].rgbtBlue * -2;
								leftsum_red += image[i+x][j+y].rgbtRed * -2;
								leftsum_green += image[i+x][j+y].rgbtGreen * -2;
							}
							else if (y > 0)
							{
								rightsum_blue += image[i+x][j+y].rgbtBlue * 2;
								rightsum_red += image[i+x][j+y].rgbtRed * 2;
								rightsum_green += image[i+x][j+y].rgbtGreen * 2;
							}
						}
						else
						{
							if (y < 0)
							{
								leftsum_blue += image[i+x][j+y].rgbtBlue * -1;
								leftsum_red += image[i+x][j+y].rgbtRed * -1;
								leftsum_green += image[i+x][j+y].rgbtGreen * -1;
							}
							else if (y > 0)
							{
								rightsum_blue += image[i+x][j+y].rgbtBlue * 1;
								rightsum_red += image[i+x][j+y].rgbtRed * 1;
								rightsum_green += image[i+x][j+y].rgbtGreen * 1;
							}
						}
					}
				}
			}

			gx_blue = rightsum_blue + leftsum_blue;
			gx_red = rightsum_red + leftsum_red;
			gx_green = rightsum_green + leftsum_green;
			
			//Gy
			int topsum_blue = 0, topsum_red = 0, topsum_green = 0;
			int bottomsum_blue = 0, bottomsum_red = 0, bottomsum_green = 0;
			int gy_blue, gy_red, gy_green;

			for(int x = -1; x <= 1; x++)
			{
				for(int y = -1; y <= 1; y++)
				{
					if(i+y < height && i+y >= 0 && x+j < width && x+j >= 0)
					{
						if (x == 0)
						{
							if (y < 0)
							{
								topsum_blue += image[i+y][j+x].rgbtBlue * -2;
								topsum_red += image[i+y][j+x].rgbtRed * -2;
								topsum_green += image[i+y][j+x].rgbtGreen * -2;
							}
							else if (y > 0)
							{
								bottomsum_blue += image[i+y][j+x].rgbtBlue * 2;
								bottomsum_red += image[i+y][j+x].rgbtRed * 2;
								bottomsum_green += image[i+y][j+x].rgbtGreen * 2;
							}
						}
						else
						{
							if (y < 0)
							{
								topsum_blue += image[i+y][j+x].rgbtBlue * -1;
								topsum_red += image[i+y][j+x].rgbtRed * -1;
								topsum_green += image[i+y][j+x].rgbtGreen * -1;
							}
							else if (y > 0)
							{
								bottomsum_blue += image[i+y][j+x].rgbtBlue * 1;
								bottomsum_red += image[i+y][j+x].rgbtRed * 1;
								bottomsum_green += image[i+y][j+x].rgbtGreen * 1;
							}
						}
					}
				}
			}

			gy_blue = topsum_blue + bottomsum_blue;
			gy_red = topsum_red + bottomsum_red;
			gy_green = topsum_green + bottomsum_green;

			// assign to temporary image clone
			if (floor(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2))) > 255)
			{
				image_clone[i][j].rgbtBlue = 255;
			}
			else
			{
				image_clone[i][j].rgbtBlue = floor(sqrt(pow(gx_blue, 2) + pow(gy_blue, 2))); 
			}

			if (floor(sqrt(pow(gx_red, 2) + pow(gy_red, 2))) > 255)
			{
				image_clone[i][j].rgbtRed = 255;
			}
			else
			{
				image_clone[i][j].rgbtRed = floor(sqrt(pow(gx_red, 2) + pow(gy_red, 2)));
			}

			if (floor(sqrt(pow(gx_green, 2) + pow(gy_green, 2))) > 255)
			{
				image_clone[i][j].rgbtGreen = 255;
			}
			else
			{
				image_clone[i][j].rgbtGreen = floor(sqrt(pow(gx_green, 2) + pow(gy_green, 2)));
			}
		}
	}

	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			image[i][j] = image_clone[i][j];
		}
	}
	return;
}

