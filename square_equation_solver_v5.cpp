#include <stdio.h>
#include <math.h>
#include <assert.h>

/*!
 * @file square_equation_solver_v4
 * @author some-repository
 * @date 28.08.2020
 * @see something
 */

/*!
* @brief solve_square() solves square equation and calls solve_linear if the first coefficient is 0
* @param double a, b and c are coefficients in equation ax^2+bx+c=0
* @param double *x1 and *x2 are variable pointers for variables that contain roots, function needs both variable pointers
* @return int - quantity of roots or error code
*/

int solve_square(double a, double b, double c, double *x1, double *x2);

/*!
* @brief solve_linear() solves linear equation
* @param double b and c are coefficients in equation bx+c=0
* @param double *x1 is variable pointer for variables that contains root
* @return int - quantity of roots or error code
*/

int solve_linear(double b, double c, double *x1, int res);

/*!
* @brief is_near_zero() checks if the the absolute value of a number not more than TOLERANCE
* @param double value
* @return boolean
*/

bool is_near_zero(double value);

/*!
* @brief solve_linear() returns INFIFNTE_QUANTITY if linear equation have infinite quantity of roots
* @brief solve_square() returns ERROR in case of an unforeseen situation
*/

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
    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    int res = ERROR;

    if(a == 0)
    {
         res = solve_linear(b, c, x1, res);
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

bool is_near_zero(double value)
{
    double difference = fabs(value);
    return (difference <= TOLERANCE);
}


