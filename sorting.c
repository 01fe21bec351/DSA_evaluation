#include<stdio.h>
#include<stdlib.h>
#include<time.h>


struct Node // Creating Node
{
    int data;
    struct Node *next;

};
typedef struct Node *node;
node newnode,temp,head=NULL;
node getnode(int k) //Creating Newnode
{
    newnode=(node)malloc(sizeof(node));
    if(newnode==NULL)
    {
        exit(0);
    }
    newnode->data=k;
    newnode->next=NULL;
    return newnode;

}
node insert_end(node newnode,int k) // inserting newnode at the End of the head
{
    newnode=getnode(k);

    if(head==NULL)
    {
        return newnode;
    }
    else
    {


        temp=head;
        while(temp->next!=NULL)
        {
            temp=temp->next;
        }
        temp->next=newnode;
        return head;
    }

}
void display(node head) // display the linked List
{
    if(head==NULL)
    {
        printf("no node");
    }
    else
    {
        temp=head;
        while(temp!=NULL)
        {
            printf("%d->",temp->data);
            temp=temp->next;
        }

    }

}

node sort(node head, int n) // Sorting the linked list
{
    int m;
    node cur,nex;
    cur=head;
    nex=cur->next;
    for(int i=0;i<n-1;i++)
    {

        for(int j=i+1;j<n;j++)
        {
            if(cur->data<nex->data)
            {
                m=cur->data;
                cur->data=nex->data;
                nex->data=m;

            }
            nex=nex->next;
        }
        cur=cur->next;
        nex=cur->next;
    }
    return head;
}

int main()
{
    int ar[10000];
    FILE *fileptr;
    fileptr=fopen("theinput.txt","r");
    int n;
    fscanf(fileptr,"%d",&n);
    printf("%d",n);
    for(int i=0;i<n;i++) // reading the elements from the input file
    {
        printf("d");
        fscanf(fileptr,"%d",&ar[i]);
        head=insert_end(newnode,ar[i]);
    }
    fclose(fileptr);
    display(head);

    clock_t t;
    t=clock();
    head=sort(head,n);

    t=clock()-t;
    double time_taken=((double)t)/CLOCKS_PER_SEC;

    printf("\n");
    display(head);
    printf("\nTime Taken %f",time_taken); // displaying time taken

	fileptr3=fopen("file.txt","a"); // storing values in the file.txt file

    fprintf(fileptr3,"\n%d  %f",n,time_taken);

    fclose(fileptr3);



}
