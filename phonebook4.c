#include <cs50.h>
#include <stdio.h>
#include <string.h>

typedef struct
{
    string name;
    string number;
}
person;

int main(void)
{
    person people[2];

    people[0].name = "Beyene";
    people[0].number = "+251937220207";

    people[1].name = "Tadelech";
    people[1].name = "+251916138748";

    string n = get_string("name: ");
    for (int i = 0; i < 2; i++)
    {
        if (strcmp(people[i].name, n) == 0)
        {
            printf("found %s\n", people[i].number);
            return 0;
        }
    }
    printf("not found\n");
    return 1;
}

