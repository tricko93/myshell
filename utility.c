#include "utility.h"

Node* insert(Node* head, char data[100])
{
        Node *temp, *p;
        temp = (Node*)malloc(sizeof(Node));
        strncpy(temp->data, data, strlen(data));
        temp->next = NULL;
        if(head==NULL)
        {
                head = temp;
        }
        else
        {
                for(p=head; p->next!=NULL; p=p->next);
                p->next = temp;
        }
        return temp;
}
