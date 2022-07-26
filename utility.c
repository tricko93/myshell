#include "utility.h"

Node *insert(Node *head, char data[100])
{
        Node *temp, *p;
        temp = (Node *)malloc(sizeof(Node));
        strncpy(temp->data, data, 100);
        temp->next = NULL;
        if (head == NULL)
        {
                head = temp;
        }
        else
        {
                for (p = head; p->next != NULL; p = p->next)
                        ;
                p->next = temp;
        }
        return temp;
}

void removeLastElement(Node *head)
{
        Node *temp;
        if(head)
        {
                for (temp = head; temp->next->next != NULL; temp = temp->next);
                free(temp->next);
                temp->next = NULL;
        }
}

void convertToVariable(Node *head, char *variable)
{
        int offset = 0, sum = 0;
        Node *temp = head;
        while (temp != NULL)
        {
                offset = strlen(temp->data);
                strncpy(variable + sum, temp->data, offset);
                temp = temp->next;
                sum += offset;
        }
        variable[sum] = '\0';
}

void deleteAll(Node *head)
{
        if (head)
        {
                deleteAll(head->next);
                free(head);
        }
}

