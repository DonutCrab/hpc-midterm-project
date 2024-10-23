#include <stdio.h>

float wine_concentration_equation(float c1, float dT, float k);

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

    printf("Concentration after %d steps: %f\n", days, concentration);

    return 0;
}

float wine_concentration_equation(float c_start, float delta_time, float k)
{
    return c_start - delta_time * k * c_start;
}
