#include <stdio.h>
#include <stdlib.h>

typedef struct
{
    int intdata;
    char* p_chardata;
} mystruct;

struct Node
{
    Node* p_next;
    Node* p_previous;
    mystruct* p_data;
};

typedef struct Node node;

void dumpmystruct(const mystruct* p_data)
{
    if (p_data != NULL)
    {
        if (p_data->p_chardata != NULL)
        {
            printf("mystruct (%p): intdata = %d, chardata = %s\n",
                p_data, p_data->intdata, p_data->p_chardata);
        }
        else
        {
            printf("p_chardata is NULL\n");
        }
    }
    else
    {
        printf("mystruct is NULL\n");
    }
}

void dumpnode(node * p_node)
{
    if (p_node != NULL)
    {
        printf("node (%p): p_next = %p, p_previous = %p, p_data = %p\n",
            p_node, p_node->p_next, p_node->p_previous, p_node->p_data);
    }
    else
    {
        printf("node is NULL\n");
    }
}

node* addnode(node *p_previous, const mystruct* p_mystruct)
{
    node* p_newnode = (node*)malloc(sizeof(node));
    if (p_newnode != NULL)
    {
        p_newnode->p_previous = p_previous;
        p_newnode->p_next = NULL;
        if (p_previous != NULL)
        {
            p_previous->p_next = p_newnode;
        }
        mystruct* p_newmystruct = (mystruct*)malloc(sizeof(mystruct));
        if (p_newmystruct != NULL)
        {
            p_newmystruct->intdata = p_mystruct->intdata;
            p_newmystruct->p_chardata = p_mystruct->p_chardata;
            p_newnode->p_data = p_newmystruct;

            printf("Previous node: ");
            dumpnode(p_previous);
            printf("Created node: ");
            dumpnode(p_newnode);
            dumpmystruct(p_newmystruct);
            return p_newnode;
        }
    }
    
    return NULL;
}

node* freenode(node* p_nodetofree)
{
    if (p_nodetofree != NULL)
    {
        printf("Free node: ");
        dumpnode(p_nodetofree);
        node* p_previous = p_nodetofree->p_previous;
        if (p_previous != NULL)
        {
            p_previous->p_next = NULL;
        }
        free(p_nodetofree->p_data);
        free(p_nodetofree);
        return p_previous;
    }

    return NULL;
}


int main(int argc, char **argv)
{
    char string1[] = "This is string1";
    char string2[] = "This is string2";
    char string3[] = "This is string3";
    mystruct data1 = { 1, string1 };
    mystruct data2 = { 2, string2 };
    mystruct data3 = { 3, string3 };

    dumpmystruct(&data1);
    dumpmystruct(&data2);
    dumpmystruct(&data3);

    node* p_node = addnode(NULL, &data1);
    node* p_basenode = p_node;
    p_node = addnode(p_node, &data2);
    p_node = addnode(p_node, &data3);

    printf("\n\nNodes\n");
    for (node* p_node1 = p_basenode; p_node1 != NULL; p_node1 = p_node1->p_next)
    {
        dumpnode(p_node1);
        dumpmystruct(p_node1->p_data);
    }

    p_node = freenode(p_node);
    p_node = freenode(p_node);
    p_node = freenode(p_node);
}
