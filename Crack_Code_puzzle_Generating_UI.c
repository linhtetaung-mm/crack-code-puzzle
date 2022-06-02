#include<stdio.h>
#include<stdlib.h>
#include<time.h>
//May 30,2021
//Crack Code Puzzle from "Brain Training- Logic Puzzles"
//Generating UI(Questioning UI)

void main()
{
    int Digits[20], GPN[10];
    int nDigits, nGPN, notGPN;
    // nDigits means numbers of digits
    // nGPN means numbers of Given Possible Numbers
    // notGPN means count of numbers to fill GPN
    int i, j, k = 0;

    do{
    printf("How many digits do you want to try?\n");
    scanf("%d", &nDigits);
    } while(nDigits<0 || nDigits>20);

    printf("\nOK , Let's start!\n");

    srand(time(0));
    for(i=0; i<nDigits; i++)
    {
        Digits[i] = rand()%10;
        //printf(" %d ", Digits[i]);
    }
    //printf("\n");

    //Given Possible Numbers
    if(nDigits<8)
        nGPN = nDigits + 2;
    else
        nGPN = 10;

    notGPN = nGPN;

    for(i=0; i<10; i++)
        for(j=0; j<nDigits; j++)
            if(Digits[j] == i)
            {
                GPN[k++] = i;
                notGPN--;
                j = nDigits;
            }
    /*printf("\nCount of numbers to fill : %d \n", notGPN);*/

    int temp[10];
    for (i=0; i<10; i++)
    {
        int okay = 0;
        while(!okay)
        {
            temp[i] = rand()%10;
            okay = 1;

            for (j=0; j<i; j++)
                if (temp[i] == temp[j])
                    okay = 0;
        }
        /*printf(" %d ", temp[i]);*/
    }

    //To output GPN

    /*printf("\n");
    printf("Involving : ");
    for(i=0; i<k; i++)
        printf(" %d ", GPN[i]);*/

    printf("\n");
    /*printf("notGPN : %d\n", notGPN);*/
    printf("Given Possible Numbers are : ");

    for(i=0; i<10; i++)
        for(j=0; j<k; j++)
        {
            if(temp[i] == GPN[j]){
                printf(" %d ", temp[i]);
                j = k;}
            else if(temp[i] != GPN[j] && j == k-1 && notGPN>0){
                printf(" %d ", temp[i]);
                notGPN--;
                }
        }

    printf("\n\n");
    //Requesting input and give signals back
    int greens, reds, nulls;
    int pos[nDigits];
    int t=1;

    printf("Caution : Input method is straight input, a dot '.' between two numbers and in the end.\n");
    printf("Example: 1.2.3.4.5.\n\n");

    do{
        printf("Trying %d : What have you got?\n", t);
        printf("Input %d : ", t++);
        for(i=0; i<nDigits; i++)
            scanf("%d.", &pos[i]);

        /*printf("\nYou typed : ");
        for(i=0; i<nDigits; i++)
            printf("%d ", pos[i]);*/

        printf("\n");

        greens= reds= nulls =0;
        for(i=0; i<nDigits; i++)
            if(pos[i] == Digits[i])
                greens++;

        int vecA[10] = {0}, vecB[10] = {0};
        int countA, countB, p;
        for(i=0; i<10; i++){
            countA = countB = p = 0;
            for(j=0; j<nDigits; j++){
                if(Digits[j] == i){
                    countA++;
                    vecA[i] = countA;
                }
                if(pos[j] == i){
                    countB++;
                    vecB[i] = countB;
                }
            }
            if(countA > countB){
                p = countA-countB;
                nulls = nulls+p;
            }
            else
                nulls = nulls;
        }

        /*for(i=0; i<10; i++)
            printf(" %d ", vecA[i]);
        printf("\n");
        for(i=0; i<10; i++)
            printf(" %d ", vecB[i]);*/


        reds = nDigits - greens - nulls;
        printf(" %d Greens, %d Reds, %d Nulls\n", greens, reds, nulls);
        printf("--------------------\n");

    }while(greens != nDigits);

}
