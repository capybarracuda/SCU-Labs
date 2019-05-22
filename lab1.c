#include <stdio.h>
#define REPEAT 10

void main(void);
int division(x,y);
int division(x,y)
{
    int answer;
    printf("%d / %d?\n",y, x);
    scanf("%d",&answer);
    if(y/x==answer)
    {
        printf("Correct! %d / %d = %d ",y,x,y/x)
        return 1;
    }
    else
    {
        printf("Incorrect! %d / %d = %d ",y,x,y/x)
        return 0;
    }
}

void main(void)
{
    int divisor, i,counter = 0,quotient;
    srand((int)time(NULL));
    for(i=0;i<REPEAT;i++)
    {
        divisor = rand() % 12 + 1;
        quotient = rand() % 13;
        counter += division(divisor,quotient);
    }
    printf("You got %d% right!",counter*10);
}