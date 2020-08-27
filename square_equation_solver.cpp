#include <stdio.h>
#include <math.h>

int solver(double a, double b, double c, double *, double *);
const int infinite_quantity=-1;

int main()
{
    printf("Enter 3 coefficients\n");

    double a=0, b=0, c=0;
    scanf("%lg%lg%lg", &a, &b, &c);

    int quantity;
    double x1=0, x2=0;
    quantity=solver(a, b, c, &x1, &x2);

    switch (quantity)
    {
        case 0: printf("No roots");
                return 0;
                break;
        case 1: printf("x=%lg", x1);
                return 0;
                break;
        case 2: printf("x1=%lg, x2=%lg", x1, x2);
                return 0;
                break;
        case infinite_quantity: printf("Any number");
                return 0;
                break;
        default: printf("main():ERROR:nRoots =%d\n", quantity);
                return 1;
     }

}

int solver(double a, double b, double c, double *x1, double *x2)
{
    int res=-2;

    if(a==0)
    {
         if(b==0)
         {
             if(c==0)
             {
                 res=infinite_quantity;
             }
             else
             {
                 res=0;
             }
         }
         else
         {
             *x1=-c/b;
             res=1;
         }
    }
    else
    {
        if((b*b)<(4*a*c))
        {
            res=0;
        }
        else if((b*b)==(4*a*c))
        {
            *x1=-b/(2*a);
            res=1;
        }
        else if((b*b)>(4*a*c))
        {
            *x1=(-b+sqrt(b*b-4*a*c))/(2*a);
            *x2=(-b-sqrt(b*b-4*a*c))/(2*a);
            res=2;
        }
    }
    return res;
}

