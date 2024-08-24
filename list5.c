//implement a sorted list of number by using linked list

#include <cs50.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct node
{
    int number;
    struct node *next;
}
node;

int main(int argc, char *argv[])
{
    // place memory for list
    node *list = NULL;

    for (int i = 1; i < argc; i++)
    {
        int number = atoi(argv[i]);

        node *n =malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }

        n -> number = number;
        n -> next = NULL;

        //if list is empty
        if (list == NULL)
        {
            list = n;
        }

        else if (n -> number < list -> number)
        {
            n -> next = list;
            list = n;
        }

        else
        {
            for (node *tmp = list; tmp != NULL; tmp = tmp -> next)
            {
                if (tmp -> next == NULL)
                {
                    tmp -> next = n;
                    break;
                }
                if (n -> number < tmp->next->number)
                {
                    n->next = tmp->next;
                    tmp->next = n;
                    break;
                }
            }

         }
    }

    //print numbers
    for (node *tmp = list; tmp != NULL; tmp = tmp->next)
    {
      printf("%i\n", tmp->number);
    }

    //free memory
    node *tmp =list;
    while (tmp != NULL)
    {
        node *next = tmp->next;
        free(tmp);
        tmp = next;
    }
}
