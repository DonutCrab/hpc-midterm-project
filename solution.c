#include <stdio.h>
#include <stdlib.h>
#include <png.h> // libpng

// cc solution.c -o out/solution -lpng && ./out/solution

void copy_row(float *from, float *to, int width);

int main()
{

    // import image

    FILE *file = fopen("8-bit-256-x-256-Grayscale-Lena-Image.png", "r");
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info = png_create_info_struct(png);

    png_init_io(png, file);
    png_read_info(png, info);

    int width = png_get_image_width(png, info);
    int height = png_get_image_height(png, info);
    int color_type = png_get_color_type(png, info);

    png_bytep *row_pointers = (png_bytep *)malloc(sizeof(png_bytep) * height);
    for (int y = 0; y < height; y++)
    {
        row_pointers[y] = (png_byte *)malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, row_pointers);
    png_read_end(png, NULL);

    // convert data

    float image_buffer[width][height];

    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            png_byte gray = row_pointers[y][x];
            image_buffer[x][y] = gray;
        }
    }

    // smoothing

    float k = 0.3;

    int steps = 100;

    float cache_row[width];
    float cache_value;

    for (int t = 0; t < steps; t++)
    {
        copy_row(image_buffer[0], cache_row, width);

        // skip borders
        for (int x = 1; x < width - 1; x++)
        {
            cache_value = image_buffer[x][0];

            float new_row[width];

            // skip borders
            for (int y = 1; y < height - 1; y++)
            {
                float new_x = k * cache_row[y] + 2 * (1 - k) * image_buffer[x][y] + k * image_buffer[x + 1][y];
                float new_y = k * cache_value + 2 * (1 - k) * image_buffer[x][y] + k * image_buffer[x][y + 1];

                cache_value = image_buffer[x][y];

                new_row[y] = (new_x + new_y) / 4;
            }

            copy_row(image_buffer[x], cache_row, width);

            copy_row(new_row, image_buffer[x], width);
        }
    }

    // export image

    FILE *fp = fopen("out/steps.png", "wb");
    png_structp png_out = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop info_out = png_create_info_struct(png_out);

    png_init_io(png_out, fp);
    png_set_IHDR(png_out, info_out, width, height, 8, PNG_COLOR_TYPE_GRAY, PNG_INTERLACE_NONE, PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);
    png_write_info(png_out, info_out);

    png_bytep row = (png_bytep)malloc(1 * width);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            row[x] = (png_byte)image_buffer[x][y];
        }
        png_write_row(png_out, row);
    }

    png_write_end(png_out, NULL);
    free(row);
    png_destroy_write_struct(&png_out, &info_out);
    fclose(fp);

    return 0;
}

void copy_row(float *from, float *to, int width)
{
    for (int i = 0; i < width; i++)
    {
        to[i] = from[i];
    }
}
