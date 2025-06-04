#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum algorithm {
    FCFS = 1,
    SCAN,
    CSCAN,
    LOOK,
    CLOOK,
    EXIT,
};

void copyArray(int *originalArray, int *newArray, int size);
void firstComeFirstServe(int *device, int deviceAmount);
void scan(int *device, int deviceAmount);
void cScan(int *device, int deviceAmount);
void cScan(int *device, int deviceAmount);
void look(int *device, int deviceAmount);
void cLook(int *device, int deviceAmount);

int main()
{
    int deviceAmount;
    printf("Amount of Devices: ");
    scanf(" %d", &deviceAmount);
    printf("\n");

    int device[deviceAmount];
    for (int i = 0; i < deviceAmount; i++)
    {
        printf("Device %d: ", i+1);
        scanf(" %d", &device[i]);

        if (device[i] > 199 || device[i] < 0)
            i--, printf("Please input a number from 0 - 199\n\n");
    }
    printf("\n");

    int deviceCopy[deviceAmount];

    int choice;
    while (choice != EXIT)
    {
        printf("Pick your Disk Scheduling Algorithm!\n");
        printf("%d First Come First Serve\n", FCFS);
        printf("%d SCAN\n", SCAN);
        printf("%d C-SCAN\n", CSCAN);
        printf("%d LOOK\n", LOOK);
        printf("%d C-LOOK\n", CLOOK);
        printf("%d Exit\n", EXIT);
        printf("Choice: ");
        scanf(" %d", &choice);

        copyArray(device, deviceCopy, deviceAmount);

        switch (choice)
        {
            case FCFS:
                firstComeFirstServe(device, deviceAmount);
                break;
            case SCAN:
                scan(device, deviceAmount);
                break;
            case CSCAN:
                cScan(device, deviceAmount);
                break;
            case LOOK:
                look(device, deviceAmount);
                break;
            case CLOOK:
                cLook(device, deviceAmount);
                break;
            case EXIT:
                break;
            default:
                printf("Pick a number from %d - %d", FCFS, EXIT);
        }
    }

    return 0;
}

void copyArray(int *originalArray, int *newArray, int size)
{
    for (int i = 0; i < size; i++)
    {
        newArray[i] = originalArray[i];
    }

    return ;
}

void firstComeFirstServe(int *device, int deviceAmount)
{

    return ;
}

void scan(int *device, int deviceAmount)
{

    return ;
}

void cScan(int *device, int deviceAmount)
{

    return ;
}

void look(int *device, int deviceAmount)
{

    return ;
}

void cLook(int *device, int deviceAmount)
{

    return ;
}

