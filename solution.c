#include <stdio.h>

// cc solution.c -o out/solution && ./out/solution

void copy_row(float *from, float *to);

// todo: convert dynamic image size
int main()
{
    // todo: dynamic size
    // todo: read image
    float image_buffer[5][5] = {
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 100, 0, 0},
        {0, 0, 0, 0, 0},
        {0, 0, 0, 0, 0}};

    float k = 0.2;

    int steps = 1;

    // todo: dynamic size
    float cache_row[5];
    float cache_value;

    for (int t = 0; t < steps; t++)
    {
        copy_row(image_buffer[0], cache_row);

        // todo: dynamic size
        // skip borders
        for (int x = 1; x < 4; x++)
        {
            cache_value = image_buffer[x][0];

            float new_row[5];

            // todo: dynamic size
            // skip borders
            for (int y = 1; y < 4; y++)
            {
                float new_x = k * cache_row[y] + 2 * (1 - k) * image_buffer[x][y] + k * image_buffer[x + 1][y];
                float new_y = k * cache_value + 2 * (1 - k) * image_buffer[x][y] + k * image_buffer[x][y + 1];

                cache_value = image_buffer[x][y];

                new_row[y] = (new_x + new_y) / 4;
            }

            copy_row(image_buffer[x], cache_row);

            copy_row(new_row, image_buffer[x]);
        }
    }

    printf("steal beam temperatures after %d steps:\n", steps);

    // todo: adjust to image dimensions
    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (j < 4)
            {
                printf(" %.3f,", image_buffer[i][j]);
            }
            else
            {
                printf(" %.3f ", image_buffer[i][j]);
            }
        }
        printf("\n");
    }

    return 0;
}

void copy_row(float *from, float *to)
{
    // todo: dynamic size
    for (int i = 0; i < 5; i++)
    {
        to[i] = from[i];
    }
}