// Check that a password has at least one lowercase letter, uppercase letter, number and symbol
// Practice iterating through a string
// Practice using the ctype library

#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool valid(string password);

int main(void)
{
    string password = get_string("Enter your password: ");
    if (valid(password))
    {
        printf("Your password is valid!\n");
    }
    else
    {
        printf("Your password needs at least one uppercase letter, lowercase letter, number and symbol\n");
    }
}

// TODO: Complete the Boolean function below
bool valid(string password)
{
    int uppercase_letter = 0;
    int lowercase_letter = 0;
    int number = 0;
    int symbol = 0;

    for (int i = 0; i < strlen(password); i++)
    {
        if ((password[i]) >= 'a' && (password[i]) <= 'z')
        {
            lowercase_letter = 1;
        }
        if ((password[i]) >= 'A' && (password[i]) <= 'Z')
        {
            uppercase_letter = 1;
        }
        if ((password[i]) >= '0' && (password[i]) <= '9')
        {
            number = 1;
        }
        if ((password[i]) >= '!' && (password[i]) <= '/')
        {
            symbol = 1;
        }
    }
    if (lowercase_letter == 1 && uppercase_letter == 1 && number == 1 && symbol == 1)
    {
        return true;
    }
    return false;
}
