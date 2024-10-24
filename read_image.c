#include <stdio.h>
#include <stdlib.h>
#include <png.h>

// cc read_image.c -o out/read_image && ./out/read_image

int main()
{
    // int width = 256;
    // int height = 256;

    FILE *fp = fopen("8-bit-256-x-256-Grayscale-Lena-Image.png", "r");

    if (!fp)
    {
        fprintf(stderr, "Error: Unable to open file \n");
        return 1;
    }

    // Initialize libpng structures
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (!png)
    {
        fclose(fp);
        fprintf(stderr, "Error: png_create_read_struct failed\n");
        return 1;
    }

    png_infop info = png_create_info_struct(png);
    if (!info)
    {
        png_destroy_read_struct(&png, NULL, NULL);
        fclose(fp);
        fprintf(stderr, "Error: png_create_info_struct failed\n");
        return 1;
    }

    if (setjmp(png_jmpbuf(png)))
    {
        png_destroy_read_struct(&png, &info, NULL);
        fclose(fp);
        fprintf(stderr, "Error: An error occurred while reading the PNG file\n");
        return 1;
    }

    png_init_io(png, fp);
    png_read_info(png, info);

    // Get image dimensions and type
    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    int color_type = png_get_color_type(png, info);

    // Ensure it is grayscale
    if (color_type != PNG_COLOR_TYPE_GRAY && color_type != PNG_COLOR_TYPE_GRAY_ALPHA)
    {
        fprintf(stderr, "Error: Image is not grayscale\n");
        png_destroy_read_struct(&png, &info, NULL);
        fclose(fp);
        return 1;
    }

    // Read the image data
    png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++)
    {
        row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, row_pointers);
    png_read_end(png, NULL);

    // Process the image data (example: print pixel values)
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            png_byte gray = row_pointers[y][x]; // For grayscale images
            printf("Pixel [%d, %d]: %d\n", x, y, gray);
        }
    }

    // Cleanup
    for (int y = 0; y < height; y++)
    {
        free(row_pointers[y]);
    }
    free(row_pointers);
    png_destroy_read_struct(&png, &info, NULL);
    fclose(fp);

    return 0;
}