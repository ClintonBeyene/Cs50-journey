#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int start, end, years = 0;
    // TODO: Prompt for start size
    do
    {
        printf("Enter starting population size: ");
        scanf("%d", &start);
    }
    while (start < 9);
    // TODO: Prompt for end size
    do
    {
        printf("Enter ending population size: ");
        scanf("%d", &end);
    }
    while (end < start);
    // TODO: Calculate number of years until we reach threshold
    while (start < end)
    {
        start += start / 3 - start / 4;
        years++;
    }

    // TODO: Print number of years
    printf("Years: %d\n", years);
    return 0;
}
