#include <stdio.h>
#include <math.h>

int solve_square(double a, double b, double c, double *x1, double *x2);
int solve_linear(double b, double c, double *x1, int res);
bool is_near_zero(double d);

const int INFIFNTE_QUANTITY = -1, ERROR = -2;
const double TOLERANCE=0.000001;

int main()
{
    printf("Enter 3 coefficients\n");

    double a = 0, b = 0, c = 0;
    int scanf_return = scanf("%lg%lg%lg", &a, &b, &c);
    if(scanf_return == 3)
    {
        double x1 = 0, x2 = 0;
        int quantity=solve_square(a, b, c, &x1, &x2);

        switch (quantity)
        {
            case 0: printf("No roots");
                return 0;
                break;
            case 1: printf("x=%.10lf", x1);
                return 0;
                break;
            case 2: printf("x1=%.10lf, x2=%.10lf", x1, x2);
                return 0;
                break;
            case INFIFNTE_QUANTITY: printf("Any number");
                return 0;
                break;
            default: printf("main():ERROR:nRoots =%d\n", quantity);
                return ERROR;
        }
    }
    else
    {
        printf("Wrong input");
        return ERROR;
    }
}

int solve_square(double a, double b, double c, double *x1, double *x2)
{
    int res = ERROR;

    if(a == 0)
    {
         res=solve_linear(b, c, x1, res);
    }
    else
    {
         double d = sqrt(b*b - 4*a*c);

         if(is_near_zero(d))
         {
             *x1 = -b/(2*a);
             res = 1;
         }
         else if((b*b) < (4*a*c))
         {
             res = 0;
         }
         else if((b*b) > (4*a*c))
         {
             *x1 = (-b + d)/(2*a);
             *x2 = (-b - d)/(2*a);
             res = 2;
         }
    }
    return res;
}

int solve_linear(double b, double c, double *x1, int res)
{
    if(b == 0)
    {
        if(c == 0)
        {
            res = INFIFNTE_QUANTITY;
        }
        else
        {
            res = 0;
        }
    }
    else
    {
        *x1 = -c/b;
        res = 1;
    }
    return res;
}

bool is_near_zero(double d)
{
    double difference = fabs(d);
    return (difference <= TOLERANCE);
}


