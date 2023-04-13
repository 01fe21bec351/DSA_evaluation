#include <stdio.h>
#include <stdlib.h>
#include <time.h>
int main()
{
    FILE *fp;
    fp=fopen("random.txt","w");
    int n;
    printf("\nEnter number: ");
    scanf("%d",&n);
    int arr[n];
    for(int i=0;i<n;i++)
    {
        arr[i]=rand()%100;
    }
    for(int i=0;i<n;i++)
    {
        fprintf(fp,"%d ",arr[i]);
    }
    fclose(fp);
    fp=fopen("random.txt","r");
    int m;
    printf("\nEnter sorting number: ");
    scanf("%d",&m);
    int arr1[m];
    for(int i=0;i<m;i++)
    {
        fscanf(fp,"%d",&arr1[i]);
    }
    fclose(fp);
    /*for(int i=0;i<m;i++)
    {
        printf("%d ",arr1[i]);
    }*/
    time_t t1,t2,t;
    t1=time(NULL);
    for(int i=0;i<m;i++)
    {
        for(int j=0;j<m-1-i;j++)
        {
            if(arr1[j]>arr1[j+1])
            {
                int temp=0;
                temp=arr1[j];
                arr1[j]=arr1[j+1];
                arr1[j+1]=temp;
            }
        }
    }
    for(int i=0;i<m;i++)
    {
        printf("%d ",arr1[i]);
    }
    t2=time(NULL);
    t=t2-t1;
    printf("\n\nTime %d",t);
}
