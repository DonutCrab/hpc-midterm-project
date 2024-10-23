#include <stdio.h>

// cc steel_beam_example.c -o out/steel_beam_example && ./out/steel_beam_example

int main()
{
    // initial condition
    float steel_beam[10] = {75, 0, 0, 0, 0, 0, 0, 0, 0, 50};

    // conductivity
    float k = 0.5;

    int steps = 10;

    float cache = 0;

    for (int i = 0; i < steps; i++)
    {
        cache = steel_beam[0];

        // ignore constant boundaries
        for (int i = 1; i < 9; i++)
        {
            float new_value = k * (cache + steel_beam[i + 1]) - (1 - k * 2) * steel_beam[i];

            // store current value to not influence the next step
            cache = steel_beam[i];

            steel_beam[i] = new_value;
        }
    }

    printf("steal beam temperatures after %d steps: {", steps);
    for (int i = 0; i < 10; i++)
    {
        if (i != 9)
        {
            printf(" %f,", steel_beam[i]);
        }
        else
        {
            printf(" %f ", steel_beam[i]);
        }
    }
    printf("}\n");

    return 0;
}