// implement a list of numbers using linkeed list

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
    //memory for numbers
    node *list = NULL;

    for (int i = 1; i < argc; i++)
    {
        // change number to int argument
        int number = atoi(argv[i]);

        //allocate node for number
        node *n = malloc(sizeof(node));
        if (n == NULL)
        {
            return 1;
        }
        n -> number = number;
        n -> next = NULL;

        //if list is empty
        if (list == NULL)
        {
            //this node is the whole list
            list = n;
        }
        else
        {
            //iterate over nodes in list
            for (node *tmp = list; tmp != NULL; tmp = tmp -> next)

            {
                if (tmp -> next == NULL)
                {
                    tmp -> next = n;
                    break;
                }
            }
        }
}
          //print numbers
         for (node *tmp = list; tmp != NULL; tmp = tmp -> next)
         {

                 printf("%i\n", tmp -> number);
         }

         //free memory
         node *tmp = list;
         tmp = tmp -> next;
         while (tmp != NULL)
         {
            node *next = tmp -> next;
            free(tmp);
            tmp = next;
         }
}
