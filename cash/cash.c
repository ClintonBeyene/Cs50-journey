#include <cs50.h>
#include <stdio.h>

int get_cents(void);
int calculate_quarters(int cents);
int calculate_dimes(int cents);
int calculate_nickels(int cents);
int calculate_pennies(int cents);

int main(void)
{
    // Ask how many cents the customer is owed
    int cents = get_cents();

    // Calculate the number of quarters to give the customer
    int quarters = calculate_quarters(cents);
    cents = cents - quarters * 25;

    // Calculate the number of dimes to give the customer
    int dimes = calculate_dimes(cents);
    cents = cents - dimes * 10;

    // Calculate the number of nickels to give the customer
    int nickels = calculate_nickels(cents);
    cents = cents - nickels * 5;

    // Calculate the number of pennies to give the customer
    int pennies = calculate_pennies(cents);
    cents = cents - pennies * 1;

    // Sum coins
    int coins = quarters + dimes + nickels + pennies;

    // Print total number of coins to give the customer
    printf("%i\n", coins);
}
// prompt the user to input the charge owed and return value as an int
int get_cents(void)
{
    int cents;
    // promp user to input until non-neg value provided
    do
    {
        cents = get_int(" change owed: ");
    }
    while (cents < 0);
    return cents;
}

int calculate_quarters(int cents)
{
    // calculate number of quarter for given amount in cents
    return cents / 25;
}

int calculate_dimes(int cents)
{
    // calculate number of dimes for given amount in cents
    return cents / 10;
}

int calculate_nickels(int cents)
{
    // calculate number of nickels for given amount in cents
    return cents / 5;
}

int calculate_pennies(int cents)
{
    // calculate number of pennies for given amount in cents
    return cents / 1;
}
