#include<stdio.h>
#include<stdlib.h>

#define MAX_SIZE 10

int * PUSH( int *top , int stack[] , int elem )
{
    if( top != &stack[MAX_SIZE] - 1 )
    {
        top++;
        *top = elem;
        printf("%x\n",top);
        return top;
    }
    else
    {
        printf( "Stack has reached its maxminum capacity \n");
        return top;
    }

}
int * POP( int *top , int stack[] )
{

    if( top == &stack[0] - 1 )
    {
        printf( " Stack is empty \n" );
        return top;
    }
    else if( top > &stack[0] - 1 )
    {
        top--;
    }
    return top;
}

void display( int stack[] , int *top )
{
    int *ptr;
    ptr = &stack[0] - 1;

    if( ptr == top )
    {
        printf( " The Stack is empty! \n");
    }
    else
    {
        do
        {
            ptr++;
            printf( " %d \n" , *ptr );

        }while( ptr != top );
    }
}


/**
 * Implements a stack data structure using an array.
 *
 * @returns None
 */
int main()
{
    int choice;
    FILE *PTR1;
    int stack[MAX_SIZE];
    int *top;
    top = stack - 1; // increment then insert
    int elem;
    PTR1 = fopen("unique_input.txt","r");
    while( 1 )
    {
        printf( "1)PUSH\n2)POP\n3)Display\n4)Exit\n" );
        printf( "Enter Choice:\n" );
        scanf( "%d" , &choice );
        switch( choice )
        {
            case 1:
                    fscanf( PTR1, "%d", &elem);
                    top = PUSH( top , stack , elem );
                    break;
            case 2:
                    top = POP( top , stack );
                    break;
            case 3:
                    display( stack , top );
                    break;
            default:
                    exit(0);


        }
    }
    fclose(PTR1);
}
