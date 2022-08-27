//Bishal Giri


#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

void insertionSort(int array[], int size);
void print_array(int nlist[], int n);

void ReadFile(int argc, char *argv[], int **ptr, int **n)
{
    FILE *myFile;
    char file_name[100];
    char file_line[10];
    int file_number, total_sum = 0, file_line_tracker = 0;
    char *token;


    if (argc == 2)
    {
        strcpy(file_name, argv[1]);
        myFile = fopen(file_name, "r");
    }
    else
    {
        printf("File must be provided on command line...exiting\n");
        exit(0);
    }

     //myFile = fopen("500000nums.txt", "r");
    while (fgets(file_line, sizeof(file_line) - 1, myFile))
    {
        file_line_tracker++; //this will be the number of entries in the file
    }

    **n = file_line_tracker;
    //mallocing an array for the number of lines in the file
    *ptr = malloc(file_line_tracker* sizeof(int));
    fseek(myFile, 0, SEEK_SET);

    //reading through the file again and adding the integers to the dynamic array
    int id=0;
    while (fgets(file_line, sizeof(file_line) - 1, myFile))
    {
        token = strtok(file_line, " ");
        file_number = atoi(file_line);
        (*ptr)[id] = file_number;
        id++;
    }


    fclose(myFile);
}


void merge(int arr[], int left, int middle, int right)
{
    int i, j,k;
    int n1 = middle-left+1;
    int n2 = right - middle;

    int L[n1], R[n2];

    for (i=0; i<n1; i++)
    {
        L[i] = arr[left+i];
    }
    for (j=0; j<n2; j++)
    {
        R[j] = arr[middle+1+j];
    }

    i=0;
    j=0;
    k=left;

    while(i<n1 && j<n2)
    {
        if (L[i] <= R[j])
        {
            arr[k] = L[i];
            i++;
        }
        else
        {
            arr[k]=R[j];
            j++;
        }
        k++;
    }

    //next--part 3
    while (i<n1)
    {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j<n2)
    {
        arr[k]=R[j];
        j++;
        k++;
    }
}

void mergeSort(int arr[], int L, int R)
{
    if (L < R)
    {
        int M = (L+R)/2;
        mergeSort(arr, L, M);
        mergeSort(arr,M+1, R);
        merge(arr, L, M, R);
    }
}
void insertionSort(int array[], int size)
{

    int i, key, j;
    for (j=1; j<size; j++)
    {
        key = array[j];
        i = j-1;

        while (i>=0 && array[i]>key)
        {
            array[i+1]=array[i];
            i=i-1;
        }
        array[i+1]=key;
    }

}

void print_array(int list[], int n)
{
    int i;
    for (i=0; i<n; i++)
    {
        printf("%d\n", list[i]);
    }
}

int main(int argc, char *argv[])
{
    clock_t start, end,mStart, mEnd;

    //pointer for array and its length
    int *list_ptr=NULL;
    int n_items=0;
    int *ptr_to_n_items = &n_items;
    ReadFile(argc, argv, &list_ptr,&ptr_to_n_items);

    //printing before merge sort
    #ifdef PRINTARRAY
    print_array(list_ptr, n_items);
    printf("\n");
    #endif

    //starting the clock for merge sort
    mStart = clock();
    mergeSort(list_ptr, 0, n_items-1);
    mEnd = clock();

    //printing after merge sort
    #ifdef PRINTARRAY
    print_array(list_ptr, n_items);
    printf("\n");
    #endif

    free(list_ptr);
    ReadFile(argc, argv, &list_ptr,&ptr_to_n_items);

    //printing before insertion sort
    #ifdef PRINTARRAY
    print_array(list_ptr, n_items);
    printf("\n");
    #endif

    //running insertion sort
    start = clock();
    insertionSort(list_ptr, n_items);
    end = clock();

    //printing after insertion sort
    #ifdef PRINTARRAY
    print_array(list_ptr, n_items);
    printf("\n");
    #endif


    free(list_ptr);

    printf("Processed %d records\n", n_items);
    printf("Merge Sort = %ld\n", mEnd-mStart);
    printf("Insertion Sort = %ld\n", end-start);
    return 0;
}




