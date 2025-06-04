#include <limits.h>
#include <stdio.h>
#include <stdlib.h>

enum algorithm {
    FIFO = 1,
    SECONDCHANCE,
    LRU,
    OPTIMAL,
    EXIT,
};

void copyArray(int *originalArray, int *newArray, int size);
void cleanFrame(int *frame, int frameSize);
void firstInFirstOut(int *frame, int frameSize, int *reference, int referenceAmount);
void secondChance(int *frame, int frameSize, int *reference, int referenceAmount);
void leastRecentlyUsed(int *frame, int frameSize, int *reference, int referenceAmount);
void optimalPageReplacement(int *frame, int frameSize, int *reference, int referenceAmount);

int main()
{
    int frameSize;
    int referenceAmount;
    printf("Frame Size: ");
    scanf(" %d", &frameSize);
    printf("Amount of References: ");
    scanf(" %d", &referenceAmount);
    printf("\n");

    int frame[frameSize];
    int referenceInput[referenceAmount];
    for (int i = 0; i < referenceAmount; i++)
    {
        printf("Reference %d: ", i+1);
        scanf(" %d", &frame[i]);
    }
    printf("\n");

    int referenceCopy[referenceAmount];

    int choice;
    while (choice != EXIT)
    {
        printf("Pick your Replacement Algorithm!\n");
        printf("%d First In First Out\n", FIFO);
        printf("%d Second Chance\n", SECONDCHANCE);
        printf("%d Least Recently Used\n", LRU);
        printf("%d Optimal Page Replacement\n", OPTIMAL);
        printf("%d Exit\n", EXIT);
        printf("Choice: ");
        scanf(" %d", &choice);

        cleanFrame(frame, frameSize);
        copyArray(referenceInput, referenceCopy, referenceAmount);

        switch (choice)
        {
            case FIFO:
                firstInFirstOut(frame, frameSize, referenceCopy, referenceAmount);
                break;
            case EXIT:
                break;
            default:
                printf("Pick a number from %d - %d", FIFO, EXIT);
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

void cleanFrame(int *frame, int frameSize)
{
    for (int i = 0; i < frameSize; i++)
    {
        frame[i] = INT_MIN;
    }

    return ;
}

void firstInFirstOut(int *frame, int frameSize, int *reference, int referenceAmount)
{

    return ;
}

void secondChance(int *frame, int frameSize, int *reference, int referenceAmount)
{

    return ;
}

void leastRecentlyUsed(int *frame, int frameSize, int *reference, int referenceAmount)
{

    return ;
}
void optimalPageReplacement(int *frame, int frameSize, int *reference, int referenceAmount)
{

    return ;
}
