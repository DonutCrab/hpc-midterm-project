#include <stdio.h>

// cc wine_example.c -o out/wine_example && ./out/wine_example

float wine_concentration_equation(float c1, float dT, float k);
float wine_concentration_recursive(float c_start, float days, float k);

int main()
{
    // replacement amount
    float k = 0.1;

    float concentration = 1;
    int days = 10;

    for (int i = 0; i < days; i++)
    {
        concentration = wine_concentration_equation(concentration, 1, k);
    }

    printf("Iterative: Concentration after %d steps: %f\n", days, concentration);

    concentration = 1;
    concentration = wine_concentration_recursive(concentration, days, k);

    printf("Recursive: Concentration after %d steps: %f\n", days, concentration);

    return 0;
}

float wine_concentration_equation(float c_start, float delta_time, float k)
{
    return c_start - delta_time * k * c_start;
}

float wine_concentration_recursive(float c_start, float days, float k)
{
    float concentration = wine_concentration_equation(c_start, 1, k);

    if (days > 1)
    {
        return wine_concentration_recursive(concentration, days - 1, k);
    }

    return concentration;
}
