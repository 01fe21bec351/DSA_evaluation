#include<stdio.h>
#include "rand_num.h"
/**
* Adds an element to the rear of the queue. The queue is filled with the value passed in
*
* @param front - pointer to the front element
* @param rear - pointer to the element to dequeue
* @param arr - array of integers that is used to store the data
*
* @return the index of the element that was enqueued from the queue.
*/
int* enqueue( int* front, int* rear, int arr[], int value )
{
    if( front == rear || rear <= &arr[MAX_SIZE-1] )
    {
        *rear = value;
        rear++;
    }
    else
    {
        printf("Queue is full.\n");
    }
    return rear;
}
/**
* Dequeue an element from the front of the queue.
*
* @param front - pointer to the front element
* @param rear - pointer to the element to dequeue
* @param arr - array of integers that is used to store the data
*
* @return the index after the element was dequeued from the queue.
*/
int* dequeue( int* front, int* rear, int arr[] )
{
    if( front == rear )
    {
        printf("Queue is empty.\n");
    }
    else
    {
        printf("Dequeued element is %d.\n", *front);
        front++;
    }
    return front;
}
/**
* Display the elements of the queue.
*
* @param front - Pointer to the front element of the queue
* @param rear - Pointer to the rear element of the queue
* @param arr - Array of elements to be displayed in the format
*/
void display( int* front , int * rear, int arr[] )
{
    if( front == rear )
    {
        printf("Queue is empty.\n");
    }
    else
    {
        int* temp;
        temp = front;
        do
        {
            printf("%d ",*temp);
            temp++;
        } while (temp != rear);

    }
}

int main()
{
    int *front, *rear;
    int arr[MAX_SIZE];
    front = &arr[0];
    rear = &arr[0] ;
    random_num(10,10,1);
    FILE *ptr1;

    ptr1 = fopen("input.txt","r");


    while(1)
    {
        int choice;
        int value;
        printf("\n1. Insert\n");
        printf("2. Delete\n");
        printf("3. Display\n");
        printf("4. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        switch(choice)
        {
            case 1:
                fscanf(ptr1, "%d", &value);
                //printf("%d",value);
                rear = enqueue(front, rear, arr, value);
                break;
            case 2:
                front = dequeue(front, rear, arr);
                break;
            case 3:
                display(front, rear, arr);
                break;
            case 4:
                exit(0);
                break;

            default:
                printf("Invalid choice\n");
                break;
        }

    }
    fclose(ptr1);
}
