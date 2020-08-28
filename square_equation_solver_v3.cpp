#include <stdio.h>
#include <math.h>

int solve(double a, double b, double c, double *x1, double *x2);
int solve_square(double a, double b, double c, double *x1, double *x2, int res);
int solve_linear(double b, double c, double *x1, int res);
bool near_zero(double a, double b, double c);
double abs_double(double number);

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
        int quantity=solve(a, b, c, &x1, &x2);

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

int solve(double a, double b, double c, double *x1, double *x2)
{
    int res = ERROR;

    if(a == 0)
    {
         res=solve_linear(b, c, x1, res);
    }
    else
    {
         res=solve_square(a, b, c, x1, x2, res);
    }
    return res;
}

int solve_square(double a, double b, double c, double *x1, double *x2, int res)
{
    if(near_zero(a, b, c))
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
        double d = sqrt(b*b - 4*a*c);
        *x1 = (-b + d)/(2*a);
        *x2 = (-b - d)/(2*a);
        res = 2;
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

bool near_zero(double a, double b, double c)
{
    double difference = abs_double(b*b - 4*a*c);
    if (difference <= TOLERANCE)
    {
        return true;
    }
    else
    {
        return false;
    }
}

double abs_double(double number)
{
    if(number >= 0)
    {
        return number;
    }
    else
    {
        return -number;
    }
}
