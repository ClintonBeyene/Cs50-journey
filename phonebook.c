#include <cs50.h>
#include <stdio.h>

int main(void)

{
    string name= get_string("what's your name? ");
    int age= get_int("what's your age? ");
    string number= get_string("what's your phone number? ");

    printf(" Age is %i. Name is %s. Number is %s.", age, name, number);
    printf("\n");
}
{
    int start, end, years = 0;

    do
    {
        printf("Enter starting population size (minimum 9): ")
        scanf("%d", &start);
    }
    while (start < 9);

    do
    {
        printf("Enter ending population size (minimum %d): ", start);
        scanf("%d", &end);
    }
    while (end < start);

    while (start < end )
    {
        start - start + start / 3 - start / 4;
        years++;
    }

    printf("Years: %d\n", years);
    return 0;
}
