#include <limits.h>
#include <stdio.h>

enum algorithm {
    FIFO = 1,
    SECONDCHANCE,
    LRU,
    LFU,
    OPTIMAL,
    EXIT,
};

void copyArray(int *originalArray, int *newArray, int size);
void cleanFrame(int *frame, int frameSize);
void firstInFirstOut(int *frame, int frameSize, int *reference, int referenceAmount, int pageFault, int pageHit);
void secondChance(int *frame, int frameSize, int *reference, int referenceAmount, int pageFault, int pageHit);
void leastRecentlyUsed(int *frame, int frameSize, int *reference, int referenceAmount, int pageFault, int pageHit);
void leastFrequentlyUsed(int *frame, int frameSize, int *reference, int referenceAmount, int pageFault, int pageHit);
void optimalPageReplacement(int *frame, int frameSize, int *reference, int referenceAmount, int pageFault, int pageHit);

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
        scanf(" %d", &referenceInput[i]);
    }
    printf("\n");

    int pageFault = 0;
    int pageHit = 0;
    int referenceCopy[referenceAmount];

    int choice;
    while (choice != EXIT)
    {
        printf("Pick your Replacement Algorithm!\n");
        printf("%d. First In First Out\n", FIFO);
        printf("%d. Second Chance\n", SECONDCHANCE);
        printf("%d. Least Recently Used\n", LRU);
        printf("%d. Least Frequently Used\n", LFU);
        printf("%d. Optimal Page Replacement\n", OPTIMAL);
        printf("%d. Exit\n", EXIT);
        printf("Choice: ");
        scanf(" %d", &choice);

        cleanFrame(frame, frameSize);
        copyArray(referenceInput, referenceCopy, referenceAmount);

        switch (choice)
        {
            case FIFO:
                firstInFirstOut(frame, frameSize, referenceCopy, referenceAmount, pageFault, pageHit);
                break;
            case SECONDCHANCE:
                secondChance(frame, frameSize, referenceCopy, referenceAmount, pageFault, pageHit);
                break;
            case LRU:
                leastRecentlyUsed(frame, frameSize, referenceCopy, referenceAmount, pageFault, pageHit);
                break;
            case LFU:
                leastFrequentlyUsed(frame, frameSize, referenceCopy, referenceAmount, pageFault, pageHit);
                break;
            case OPTIMAL:
                optimalPageReplacement(frame, frameSize, referenceCopy, referenceAmount, pageFault, pageHit);
                break;
            case EXIT:
                break;
            default:
                printf("Pick a number from %d - %d\n\n", FIFO, EXIT);
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

void printCurrentFrame(int *frame, int frameSize)
{
    printf("Inside Current Frame: ");
    for (int i = 0; i < frameSize; i++)
    {
        printf("%d ", frame[i]);
    }
    printf("\n");
}

void firstInFirstOut(int *frame, int frameSize, int *reference, int referenceAmount, int pageFault, int pageHit)
{
    for (int i = 0; i < referenceAmount; i++)
    {
        int found = 0;
        for (int j = 0; j < frameSize; j++)
        {
            if (frame[j] == reference[i])
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            pageHit++;
            printf("Page Hit of reference %d!\n", reference[i]);
            printCurrentFrame(frame, frameSize);
            printf("\n");
            continue;
        }

        for (int j = frameSize - 1; j > 0; j--)
        {
            frame[j] = frame[j-1];
        }
        frame[0] = reference[i];

        pageFault++;
        printf("Page Fault of reference %d!\n", reference[i]);
        printCurrentFrame(frame, frameSize);
        printf("\n");
    }

    printf("Amount of page fault: %d\n", pageFault);
    printf("Amount of page hit: %d\n\n", pageHit);

    return ;
}

void secondChance(int *frame, int frameSize, int *reference, int referenceAmount, int pageFault, int pageHit)
{
    int chance[frameSize];
    for (int i = 0; i < frameSize; i++)
    {
        chance[i] = 0;
    }

    for (int i = 0; i < referenceAmount; i++)
    {
        int found = 0;
        for (int j = 0; j < frameSize; j++)
        {
            if (frame[j] == reference[i])
            {
                chance[j] = 1;
                found = 1;
                break;
            }
        }

        if (found)
        {
            pageHit++;
            printf("Page Hit of reference %d!\n", reference[i]);
            printCurrentFrame(frame, frameSize);
            printf("\n");
            continue;
        }

        for (int j = frameSize - 1; j >= 0; j--)
        {
            if (chance[j] == 1)
            {
                chance[j] = 0;
                continue;
            }

            for (int k = j; k >= 0; k--)
            {
                if (k == 0)
                    frame[0] = reference[i];
                else
                {
                    if (chance[k-1] == 1)
                    {
                        chance[k-1] = 0;
                        chance[k] = 1;
                    }
                    frame[k] = frame[k-1];
                }
            }
            break;
        }

        pageFault++;
        printf("Page Fault of reference %d!\n", reference[i]);
        printCurrentFrame(frame, frameSize);
        printf("\n");
    }

    printf("Amount of page fault: %d\n", pageFault);
    printf("Amount of page hit: %d\n\n", pageHit);

    return ;
}

void leastRecentlyUsed(int *frame, int frameSize, int *reference, int referenceAmount, int pageFault, int pageHit)
{
    for (int i = 0; i < referenceAmount; i++)
    {
        int found = 0;
        for (int j = 0; j < frameSize; j++)
        {
            if (frame[j] == reference[i])
            {
                found = 1;

                for (int k = j; k >= 0; k--)
                {
                    if (k == 0)
                        frame[k] = reference[i];
                    else
                        frame[k] = frame[k-1];
                }

                break;
            }
        }

        if (found)
        {
            pageHit++;
            printf("Page Hit of reference %d!\n", reference[i]);
            printCurrentFrame(frame, frameSize);
            printf("\n");
            continue;
        }

        for (int j = frameSize - 1; j > 0; j--)
        {
            frame[j] = frame[j-1];
        }
        frame[0] = reference[i];

        pageFault++;
        printf("Page Fault of reference %d!\n", reference[i]);
        printCurrentFrame(frame, frameSize);
        printf("\n");
    }

    printf("Amount of page fault: %d\n", pageFault);
    printf("Amount of page hit: %d\n\n", pageHit);

    return ;
}

void leastFrequentlyUsed(int *frame, int frameSize, int *reference, int referenceAmount, int pageFault, int pageHit)
{
    int frequency[frameSize];
    for (int i = 0; i < frameSize; i++) // freq arr
    {
        frequency[i] = 0;
    }
    
    for (int i = 0; i < referenceAmount; i++)
    {
        int found = 0;
        for (int j = 0; j < frameSize; j++) // iterate to check if page is already in frame
        {
            if (frame[j] == reference[i])
            {
                frequency[j]++;
                found = 1;
                break;
            }
        }

        if (found)
        {
            pageHit++;
            printf("Page Hit of reference %d!\n", reference[i]);
            printCurrentFrame(frame, frameSize);
            printf("Frequency: ");
            for (int j = 0; j < frameSize; j++)
            {
                printf("%d ", frequency[j]);
            }
            printf("\n\n");
            continue;
        }

        // not found, find the page that are least frequently used
        int minFreq = INT_MAX;
        int replaceIndex = 0;
        int hasEmptySlot = 0;
        
        for (int j = 0; j < frameSize; j++)
        {
            if (frame[j] == INT_MIN) // Empty slot
            {
                replaceIndex = j;
                hasEmptySlot = 1;
                break;
            }
        }
        
        // no empty slot, find the least frequently used page
        if (!hasEmptySlot)
        {
            for (int j = 0; j < frameSize; j++)
            {
                if (frequency[j] < minFreq)
                {
                    minFreq = frequency[j];
                    replaceIndex = j;
                }
            }
        }

        frame[replaceIndex] = reference[i];
        frequency[replaceIndex] = 1;

        pageFault++;
        printf("Page Fault of reference %d!\n", reference[i]);
        printCurrentFrame(frame, frameSize);
        printf("\n");
    }

    printf("Amount of page fault: %d\n", pageFault);
    printf("Amount of page hit: %d\n\n", pageHit);

    return ;
}

void optimalPageReplacement(int *frame, int frameSize, int *reference, int referenceAmount, int pageFault, int pageHit)
{
    for (int i = 0; i < referenceAmount; i++)
    {
        int found = 0;
        for (int j = 0; j < frameSize; j++)
        {
            if (frame[j] == reference[i])
            {
                found = 1;
                break;
            }
        }

        if (found)
        {
            pageHit++;
            printf("Page Hit of reference %d!\n", reference[i]);
            printCurrentFrame(frame, frameSize);
            printf("\n");
            continue;
        }

        int longestIndex = i;

		for (int j = 0; j < frameSize; j++)
		{
			for (int k = i; k < referenceAmount; k++)
			{
			    if (k == referenceAmount - 1)
				{
					if (frame[j] == reference[k])
						longestIndex = k;
					else
						longestIndex = referenceAmount;
				}

				if (frame[j] == reference[k])
				{
					if (k > longestIndex)
						longestIndex = k;
					break;
				}
			}

			if (longestIndex == referenceAmount)
			{
				frame[j] = reference[i];
				break;
			}
		}

		if (longestIndex == 12)
        {
            pageFault++;
            printf("Page Fault of reference %d!\n", reference[i]);
            printCurrentFrame(frame, frameSize);
            printf("\n");
            continue;
        }

		for (int j = 0; j < frameSize; j++)
		{
			if (frame[j] == reference[longestIndex])
			{
				frame[j] = reference[i];
				break;
			}
		}

        pageFault++;
        printf("Page Fault of reference %d!\n", reference[i]);
        printCurrentFrame(frame, frameSize);
        printf("\n");

    }

    printf("Amount of page fault: %d\n", pageFault);
    printf("Amount of page hit: %d\n\n", pageHit);

    return ;
}
