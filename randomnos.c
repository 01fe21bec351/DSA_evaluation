#include<stdio.h>
#include<stdlib.h>
#include<time.h>
void random_num(int n,int ar[1000])
{
    srand(time(0));
    int u=10000,l=0;
    for(int i=0;i<n;i++)
    {
        int num = ((rand() % (u-l+1)) + l);
        printf("%d ",num);
        ar[i]=num;
    }

}
int main()
{
    int n=1000,ar[1000];

    random_num(n,ar);
    FILE *fileptr;

    fileptr=fopen("input.txt","w");

    fprintf(fileptr,"%d ",n);
    for(int i=0;i<n;i++)
    {

        fprintf(fileptr,"%d",ar[i]);
        fprintf(fileptr," ");
    }

    fclose(fileptr);

}
