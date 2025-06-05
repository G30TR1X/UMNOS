#include <limits.h>
#include <stdio.h>

enum algorithm {
    FCFS = 1,
    SSTF,
    SCAN,
    CSCAN,
    LOOK,
    CLOOK,
    EXIT,
};

void copyArray(int *originalArray, int *newArray, int size);
void firstComeFirstServe(int *device, int deviceAmount, int headStart);
void shortestSeekTimeFirst(int *device, int deviceAmount, int headStart);
void scan(int *device, int deviceAmount, int headStart);
void cScan(int *device, int deviceAmount, int headStart);
void cScan(int *device, int deviceAmount, int headStart);
void look(int *device, int deviceAmount, int headStart);
void cLook(int *device, int deviceAmount, int headStart);

int main()
{
    int headStart;
    int deviceAmount;
    printf("Head Start: ");
    scanf(" %d", &headStart);

    while (headStart > 199 || headStart < 0)
    {
        printf("Please input a head start from 0 - 199: ");
        scanf(" %d", &headStart);
    }

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
        printf("%d. First Come First Serve\n", FCFS);
        printf("%d. Shortest Seek Time First\n", SSTF);
        printf("%d. SCAN\n", SCAN);
        printf("%d. C-SCAN\n", CSCAN);
        printf("%d. LOOK\n", LOOK);
        printf("%d. C-LOOK\n", CLOOK);
        printf("%d. Exit\n", EXIT);
        printf("Choice: ");
        scanf(" %d", &choice);
        printf("\n");

        copyArray(device, deviceCopy, deviceAmount);

        switch (choice)
        {
            case FCFS:
                firstComeFirstServe(deviceCopy, deviceAmount, headStart);
                break;
            case SSTF:
                shortestSeekTimeFirst(deviceCopy, deviceAmount, headStart);
                break;
            case SCAN:
                scan(deviceCopy, deviceAmount, headStart);
                break;
            case CSCAN:
                cScan(deviceCopy, deviceAmount, headStart);
                break;
            case LOOK:
                look(deviceCopy, deviceAmount, headStart);
                break;
            case CLOOK:
                cLook(deviceCopy, deviceAmount, headStart);
                break;
            case EXIT:
                break;
            default:
                printf("Pick a number from %d - %d\n\n", FCFS, EXIT);
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

int abs(int n)
{
    return n < 0 ? n * -1 : n;
}

void sortingDevice(int *device, int deviceAmount)
{
    for (int i = 0; i < deviceAmount - 1; i++)
    {
        int smallest = i;
        for (int j = i + 1; j < deviceAmount; j++)
        {
            if (device[j] < device[smallest])
                smallest = j;
        }

        int temp = device[i];
        device[i] = device[smallest];
        device[smallest] = temp;
    }
}

void printDeviceRequest(int *device, int deviceAmount)
{
    printf("Device Request:\n");
    for (int i = 0; i < deviceAmount; i++)
    {
        printf("%d ", device[i]);
    }
    printf("\n\n");
}

void firstComeFirstServe(int *device, int deviceAmount, int headStart)
{
    printDeviceRequest(device, deviceAmount);

    int finalSeekTime = 0, step = 1;
    for (int i = 0; i < deviceAmount; i++, step++)
    {
        int difference = abs(headStart - device[i]);
        printf("Step %d\n", step);
        printf("Head = %d\n", headStart);
        printf("Device = %d\n", device[i]);
        printf("Head to device difference = %d\n\n", difference);
        finalSeekTime += difference;
        headStart = device[i];
    }

    printf("Final Seek Time = %d\n\n", finalSeekTime);

    return ;
}

void shortestSeekTimeFirst(int *device, int deviceAmount, int headStart)
{
    printDeviceRequest(device, deviceAmount);

    int finalSeekTime = 0, step = 1;
    int used[deviceAmount];

    for (int i = 0; i < deviceAmount; i++)
    {
        used[i] = 0;
    }

    for (int i = 0; i < deviceAmount; i++, step++)
    {
        int shortestSeekTime = INT_MAX;
        int shortestSeekTimeIndex = i;
        for (int j = 0; j < deviceAmount; j++)
        {
            if (used[j])
                continue;

            int difference = abs(headStart - device[j]);
            if (difference < shortestSeekTime)
            {
                shortestSeekTime = difference;
                shortestSeekTimeIndex = j;
            }
        }

        printf("Step %d\n", step);
        printf("Head = %d\n", headStart);
        printf("Device = %d\n", device[shortestSeekTimeIndex]);
        printf("Head to device difference = %d\n\n", shortestSeekTime);
        finalSeekTime += shortestSeekTime;
        headStart = device[shortestSeekTimeIndex];
        used[shortestSeekTimeIndex] = 1;
    }

    printf("Final Seek Time = %d\n\n", finalSeekTime);

    return ;
}

void scan(int *device, int deviceAmount, int headStart)
{
    printDeviceRequest(device, deviceAmount);
    sortingDevice(device, deviceAmount);

    int choice;
    while (choice != 1 && choice != 2)
    {
        printf("Direction:\n");
        printf("1. Up\n");
        printf("2. Down\n");
        printf("Choice: ");
        scanf(" %d", &choice);
        printf("\n");

        if (choice != 1 && choice != 2)
            printf("Please choose either 1 or 2\n\n");
    }

    int headIndex = deviceAmount;
    for (int i = 0; i < deviceAmount; i++)
    {
        if (headStart < device[i])
        {
            headIndex = i;
            break;
        }
    }

    int finalSeekTime = 0, step = 1;
    switch (choice)
    {
        case 1:
            for (int i = headIndex; i < deviceAmount; i++, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }

            printf("Step %d\n", step);
            printf("Head = %d\n", headStart);
            printf("Device = 199\n");
            printf("Head to device difference = %d\n\n", abs(headStart - 199));
            finalSeekTime += abs(headStart - 199);
            headStart = 199;
            step++;

            for (int i = headIndex - 1; i >= 0; i--, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }
            break;
        case 2:
            for (int i = headIndex - 1; i >= 0; i--, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }

            printf("Step %d\n", step);
            printf("Head = %d\n", headStart);
            printf("Device = 0\n");
            printf("Head to device difference = %d\n\n", headStart);
            finalSeekTime += headStart;
            headStart = 0;
            step++;

            for (int i = headIndex; i < deviceAmount; i++, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }
            break;
    }

    printf("Final Seek Time = %d\n\n", finalSeekTime);

    return ;
}

void cScan(int *device, int deviceAmount, int headStart)
{
    printDeviceRequest(device, deviceAmount);
    sortingDevice(device, deviceAmount);

    int choice;
    while (choice != 1 && choice != 2)
    {
        printf("Direction:\n");
        printf("1. Up\n");
        printf("2. Down\n");
        printf("Choice: ");
        scanf(" %d", &choice);
        printf("\n");

        if (choice != 1 && choice != 2)
            printf("Please choose either 1 or 2\n\n");
    }

    int headIndex = deviceAmount;
    for (int i = 0; i < deviceAmount; i++)
    {
        if (headStart < device[i])
        {
            headIndex = i;
            break;
        }
    }

    int finalSeekTime = 0, step = 1;
    switch (choice)
    {
        case 1:
            for (int i = headIndex; i < deviceAmount; i++, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }

            printf("Step %d\n", step);
            printf("Head = %d\n", headStart);
            printf("Device = 199\n");
            printf("Head to device difference = %d\n\n", abs(headStart - 199));
            finalSeekTime += abs(headStart - 199);
            headStart = 199;
            step++;

            printf("Step %d\n", step);
            printf("Head = 199\n");
            printf("Device = 0\n");
            printf("Head to device difference = 199\n\n");
            finalSeekTime += 199;
            headStart = 0;
            step++;

            for (int i = 0; i < headIndex; i++, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }
            break;
        case 2:
            for (int i = headIndex - 1; i >= 0; i--, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }

            printf("Step %d\n", step);
            printf("Head = %d\n", headStart);
            printf("Device = 0\n");
            printf("Head to device difference = %d\n\n", headStart);
            finalSeekTime += headStart;
            headStart = 0;
            step++;

            printf("Step %d\n", step);
            printf("Head = 0\n");
            printf("Device = 199\n");
            printf("Head to device difference = 199\n\n");
            finalSeekTime += 199;
            headStart = 199;
            step++;

            for (int i = deviceAmount - 1; i >= headIndex; i--, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }
            break;
    }

    printf("Final Seek Time = %d\n\n", finalSeekTime);

    return ;
}

void look(int *device, int deviceAmount, int headStart)
{
    printDeviceRequest(device, deviceAmount);
    sortingDevice(device, deviceAmount);

    int choice;
    while (choice != 1 && choice != 2)
    {
        printf("Direction:\n");
        printf("1. Up\n");
        printf("2. Down\n");
        printf("Choice: ");
        scanf(" %d", &choice);
        printf("\n");

        if (choice != 1 && choice != 2)
            printf("Please choose either 1 or 2\n\n");
    }

    int headIndex = deviceAmount;
    for (int i = 0; i < deviceAmount; i++)
    {
        if (headStart < device[i])
        {
            headIndex = i;
            break;
        }
    }

    int finalSeekTime = 0, step = 1;
    switch (choice)
    {
        case 1:
            for (int i = headIndex; i < deviceAmount; i++, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }

            for (int i = headIndex - 1; i >= 0; i--, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }
            break;
        case 2:
            for (int i = headIndex - 1; i >= 0; i--, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }

            for (int i = headIndex; i < deviceAmount; i++, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }
            break;
    }

    printf("Final Seek Time = %d\n\n", finalSeekTime);

    return ;
}

void cLook(int *device, int deviceAmount, int headStart)
{
    printDeviceRequest(device, deviceAmount);
    sortingDevice(device, deviceAmount);

    int choice;
    while (choice != 1 && choice != 2)
    {
        printf("Direction:\n");
        printf("1. Up\n");
        printf("2. Down\n");
        printf("Choice: ");
        scanf(" %d", &choice);
        printf("\n");

        if (choice != 1 && choice != 2)
            printf("Please choose either 1 or 2\n\n");
    }

    int headIndex = deviceAmount;
    for (int i = 0; i < deviceAmount; i++)
    {
        if (headStart < device[i])
        {
            headIndex = i;
            break;
        }
    }

    int finalSeekTime = 0, step = 1;
    switch (choice)
    {
        case 1:
            for (int i = headIndex; i < deviceAmount; i++, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }

            for (int i = 0; i < headIndex; i++, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }
            break;
        case 2:
            for (int i = headIndex - 1; i >= 0; i--, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }

            for (int i = deviceAmount - 1; i >= headIndex; i--, step++)
            {
                int difference = abs(headStart - device[i]);
                printf("Step %d\n", step);
                printf("Head = %d\n", headStart);
                printf("Device = %d\n", device[i]);
                printf("Head to device difference = %d\n\n", difference);
                finalSeekTime += difference;
                headStart = device[i];
            }
            break;
    }

    printf("Final Seek Time = %d\n\n", finalSeekTime);

    return ;
}

