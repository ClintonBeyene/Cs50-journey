// pretends numbers to linked list using while loop to print

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc,char *argv[1])
{
    //memory for numbers
    node *list = NULL;

    //for each command line argument
    for(int  i =1; i < argc; i++)
    {
        //conver argument to int
        int number = atoi(argv[i]);

        //allocate node for malloc
        node *n= malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n -> number = number;
        n -> next = NULL;

        //pretend node to list
        n -> next = list;
        list = n;
    }

    //print numbers
    node *tmp = list;
    while (tmp != 0)
    {
        printf("%i\n", tmp -> number);
        tmp = tmp -> next;
    }

    //free memory
    tmp = list;
    while (tmp != NULL)
    {
        node *next = tmp -> next;
        free(tmp);
        tmp = next;
    }
}

