#include <stdio.h>

float wine_concentration_equation(float c1, float dT, float k);

int main()
{
    printf("Wine Example:\n");

    // Start Concentration
    float c1 = 1;

    // Replacement Amount
    float k = 0.1;

    float c2 = wine_concentration_equation(c1, 1, k);
    printf("day 2 concentration %f\n", c2);

    float c3 = wine_concentration_equation(c2, 1, k);
    printf("day 3 concentration %f\n", c3);

    float c4 = wine_concentration_equation(c3, 1, k);
    printf("day 4 concentration %f\n", c4);

    float c5 = wine_concentration_equation(c4, 1, k);
    printf("day 5 concentration %f\n", c5);

    float c6 = wine_concentration_equation(c5, 1, k);
    float c7 = wine_concentration_equation(c6, 1, k);
    float c8 = wine_concentration_equation(c7, 1, k);
    float c9 = wine_concentration_equation(c8, 1, k);
    float c10 = wine_concentration_equation(c9, 1, k);
    printf("day 10 concentration %f\n", c10);

    return 0;
}

float wine_concentration_equation(float c_start, float delta_time, float k)
{
    return c_start - delta_time * k * c_start;
}
