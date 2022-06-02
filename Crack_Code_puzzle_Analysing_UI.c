#include<stdio.h>

int Digits[20];
int GPN[10];
int N[20];
int Steps[40][20];
int Signals[40][3];
int cStep = 0;//count of steps
int x = 0;//count of numbers from GPN
int found = 0;//First possible outcome

void CheckSteps(int *digs, int n)
{
    //printf(","); - Testing purpose
    int i,j, check = 0;
    int greens;

    for(i=1; i<=cStep; i++){
        greens=0;
        for(j=0; j<n; j++){
            if(Steps[i][j] == digs[j])
                greens++;
        }
        if(Signals[i][0] == greens)
            check++;
    }
    if(check == cStep){
        found++;
        if(found == 1)
            for(i=0; i<n; i++)
                Digits[i] = digs[i];
    }
}

void swap(int *p, int *q)
{
	int temp;
	temp = *p;
	*p = *q;
	*q = temp;
}

void permute(int *arr, int l, int r)//r=count of digits-1
{
    int i;
    if (l == r)
         CheckSteps(arr, r+1);

    else
    {
        for (i = l; i <= r; i++)
        {
            if(found > 0)
                break;
            //printf("."); - Testing purpose
            swap((arr+l), (arr+i));
            permute(arr, l+1, r);
            swap((arr+l), (arr+i)); //backtrack
        }
    }

}

void Analysing(int a, int b, int c)//a=nDigits, b=cStep, c=GPN[p]
{
    printf("\nAnalyzing....");
    int greens, reds, nulls;
    int i, j, m;
    int tempDigits[a];
    int Involvings[x];

    greens = Signals[b][0];
    reds = Signals[b][1];
    nulls = Signals[b][2];

    for(i=0; i<a; i++)
        Digits[i] = Steps[b][i];

    for(i=0; i<x; i++)
        Involvings[i] = N[i];

    for(j=0; j<a; j++){
        int change = 1;
        for(int k=0; k<x; k++){
            if(Digits[j] == Involvings[k]){
                Involvings[k] = -1;
                change = 0;
                break;
            }
        }
        if(change == 1)
            Digits[j] = c;
    }

    for(i=0; i<a; i++)
        tempDigits[i] = Digits[i];
    found = 0;
    permute(tempDigits, 0, a-1);
}

void main()
{
    int nDigits, nGPN;
    int i, j;

    printf("Welcome Chief...\n");
    do{
    printf("How many digits are there?\n");
    scanf("%d", &nDigits);
    }while(nDigits<0 || nDigits>20);

    if(nDigits<8)
        nGPN = nDigits+2;
    else
        nGPN = 10;

    printf("\n");
    printf("Caution : Input method is straight input, a dot '.' between two numbers and at the end.\n");
    printf("Example: 1.2.3.4.5.\n");
    printf("Remember that counts of possible numbers has two extra numbers below 8 digits.\n");
    printf("What are '%d' possible numbers?\n", nGPN);

    int n = 0;
    for(i=0; i<nGPN; i++)
        scanf("%d.", &GPN[i]);

    printf("\n");
    printf("Given Possible Numbers are : ");
    for(i=0; i<nGPN; i++)
        printf("%d ", GPN[i]);

    printf("\n\n OK! Let's Try.\n Please Help me with the signals. (Trying 0 - 0.0.%d.)\n\n", nDigits);

    int greens, reds, nulls;
    int p = 0;
    int k = 0;

    //Loop
    while(greens != nDigits){
        printf("Trying %d - Signals(Greens.Reds.Nulls.) : ", cStep);
        scanf("%d.%d.%d.", &greens, &reds, &nulls);

        Signals[cStep][0] = greens;
        Signals[cStep][1] = reds;
        Signals[cStep][2] = nulls;

        //Skipping steps at beginning
        if(nulls == nDigits){
            for(i=0; i<nDigits; i++)
                Digits[i] = GPN[p];
        }
        else if(greens != nDigits){
            for(i=0; i<Signals[cStep-1][2]-nulls; i++)
                N[x++] = GPN[p-1];
            Analysing(nDigits, cStep, GPN[p]);
        }

        cStep++;//arranging steps and signals in same row
        p++;

        for(i=0; i<nDigits; i++)
            Steps[cStep][i] = Digits[i];

        if(greens == nDigits)
            printf("\nCongratulation, Chief $$$");
        else{
            printf("\nPlease try this(%d): ", cStep);
            for(i=0; i<nDigits; i++)
                printf("%d.", Digits[i]);
            printf("\n");
        }
    }

    printf("\nSignals\n");
    for(i=0; i<cStep; i++){
        printf("(%d)", i);
        for(j=0; j<3; j++)
            printf(" %d", Signals[i][j]);
        printf("\n");
    }

    for(i=0; i<nDigits; i++)
        Steps[0][i] = -1;

    printf("Steps\n");
    for(i=0; i<cStep; i++){
        printf("(%d)", i);
        for(j=0; j<nDigits; j++)
            printf(" %d", Steps[i][j]);
        printf("\n");
    }

}

