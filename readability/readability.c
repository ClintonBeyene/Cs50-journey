#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float count_letters(string text, int str_length);
float count_words(string text, int str_length);
float count_sentences(string sentences, int str_length);

int main(void)
{
    string text = get_string("text: ");
    int length = strlen(text);
    float letter_count = count_letters(text, length);
    float words_count = count_words(text, length);
int sentences_count = count_sentences(text, length);

    float L = ((100 / words_count) * letter_count);
    float S = ((100 / words_count) * sentences_count);

    float index = round(0.0588 * L - 0.296 * S - 15.8);readability/readability.c

    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) index);
    }
}

float count_letters(string text, int str_length)
{
    int l = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (isupper(text[i]))
        {
            l++;
        }
        else if (islower(text[i]))
        {
            l++;
        }
    }
    return l;
}

float count_words(string text, int str_length)
{
    int w = 1;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == 32)
        {
            w++;
        }
    }
    return w;
}
float count_sentences(string text, int str_length)
{
    int s = 0;

    for (int i = 0, n = strlen(text); i < n; i++)
    {
        if (text[i] == '!' || text[i] == '.' || text[i] == '?')
        {
            s++;
        }
    }
    return s;
}
