#include <stdio.h>
#include <math.h>
#include <assert.h>

/*!
 * @file
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

//-----------Unit test constants-----------------------------------------------------------------------------------------------
const int QUANTITY_OF_TESTS=10;
const double arr_a[QUANTITY_OF_TESTS]     = {100.295,     0,  9e-7,             1e-40,  0, 3.125,   6.25,   6.25,   -2, -5};
const double arr_b[QUANTITY_OF_TESTS]     = {  50.87,  -1.5,  0.05,              7e-8,  0,     5,     10,     10,    3,  4};
const double arr_c[QUANTITY_OF_TESTS]     = {101.387, 30.51, -3.17,              5e-9, -1,     2, 4+1e-8, 4-1e-8,    9, -4};
const int arr_quantity[QUANTITY_OF_TESTS] = {      0,     1,     1, INFIFNTE_QUANTITY,  0,     1,      1,      1,    2,  0};
const double arr_x1[QUANTITY_OF_TESTS]    = {      0, 20.34,  63.4,                 3,  0,  -0.8,   -0.8,   -0.8, -1.5,  0};
const double arr_x2[QUANTITY_OF_TESTS]    = {      0,     0,     0,                 3,  0,     0,      0,      0,    3,  0};
//-----------Unit test constants-----------------------------------------------------------------------------------------------

/*!
* @brief unit_test() tests function solve_square. It prints OK if test was passed and FAILED, values of variables and expected values of variables, if test was failed
* @param const double *ptr_arr_a, *ptr_arr_b and *ptr_arr_c are pointers to zero elements of arrays of coefficients a, b and c
* @param const int *ptr_arr_quantity is pointer to zero element of array of quantities of roots
* @param const double *ptr_arr_x1, const double *ptr_arr_x2 are pointers to zero elements of arrays of roots
* @return int - quantity of failed tests
*/

int unit_test(const double *ptr_arr_a, const double *ptr_arr_b, const double *ptr_arr_c, const int *ptr_arr_quantity, const double *ptr_arr_x1, const double *ptr_arr_x2);

int main()
{
    double a = 0, b = 0, c = 0, x1 = 0, x2 = 0;

    //comment lines from this line if you want to use unit test
    printf("Enter 3 coefficients\n");
    while (scanf("%lg%lg%lg", &a, &b, &c) != 3)
    {
        fflush(stdin);
        printf("Wrong input, try again\n");
    }

    int quantity = solve_square(a, b, c, &x1, &x2);

    switch(quantity)
    {
        case 0: printf("No roots");
            return 0;
        case 1: printf("x=%.10lf", x1);
            return 0;
        case 2: printf("x1=%.10lf, x2=%.10lf", x1, x2);
            return 0;
        case INFIFNTE_QUANTITY: printf("Any number");
            return 0;
        default: printf("main():ERROR:nRoots =%d\n", quantity);
            return ERROR;
    }
    ////comment lines till this line if you want to use unit test

    //comment the next 2 lines if you don't want to use unit test
    //printf("%d of %d tests failed\n", unit_test(&arr_a[0], &arr_b[0], &arr_c[0], &arr_quantity[0], &arr_x1[0], &arr_x2[0]), QUANTITY_OF_TESTS);
    //return 0;
}

int solve_square(double a, double b, double c, double *x1, double *x2)
{
    assert(isfinite(a));
    assert(isfinite(b));
    assert(isfinite(c));

    assert(x1 != NULL);
    assert(x2 != NULL);
    assert(x1 != x2);

    int res = ERROR;

    if(is_near_zero(a))
    {
         res = solve_linear(b, c, x1, res);
    }
    else
    {
         if(is_near_zero(b*b - 4*a*c))
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
    }

    assert(isfinite(*x1));
    assert(isfinite(*x2));

    return res;
}

int solve_linear(double b, double c, double *x1, int res)
{
    if(is_near_zero(b))
    {
        if(is_near_zero(c))
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
    return (difference < TOLERANCE);
}

int unit_test(const double *ptr_arr_a, const double *ptr_arr_b, const double *ptr_arr_c, const int *ptr_arr_quantity, const double *ptr_arr_x1, const double *ptr_arr_x2)
{
    int quantity = 0, fails = 0;
    double x1 = 0, x2 = 0;
    bool x1_equality, x2_equality, quantity_equality;

    for(int i=0; i<QUANTITY_OF_TESTS; i++)
    {
        quantity = solve_square(*(ptr_arr_a+i), *(ptr_arr_b+i), *(ptr_arr_c+i), &x1, &x2);
        quantity_equality = (quantity == *(ptr_arr_quantity+i));
        x1_equality = (x1 == *(ptr_arr_x1+i));
        x2_equality = (x2 == *(ptr_arr_x2+i));
        if(quantity_equality)
        {
            if((*(ptr_arr_quantity+i) == 0) || (*(ptr_arr_quantity+i) == INFIFNTE_QUANTITY))
            {
                printf("OK\n");
            }
            else if(*(ptr_arr_quantity+i) == 1)
            {
                if(x1_equality)
                {
                    printf("OK\n");
                }
                else
                {
                    fails++;
                    printf("Test %d FAILED. x1 = %.10lf, expected: x1 = %.10lf\n", i, x1, *(ptr_arr_x1+i));
                }
            }
            else if(*(ptr_arr_quantity+i) == 2)
            {
                if(x1_equality && x2_equality)
                {
                    printf("OK\n");
                }
                else
                {
                    fails++;
                    printf("Test %d FAILED. x1 = %.10lf, x2 = %.10lf, expected: x1 = %.10lf, x2 = %.10lf\n", i, x1, x2, *(ptr_arr_x1+i), *(ptr_arr_x2+i));
                }
            }
        }
        else
        {
            fails++;
            printf("Test %d FAILED. quantity = %d, x1 = %.10lf, x2 = %.10lf, expected: quantity = %d, x1 = %.10lf, x2 = %.10lf\n", i, quantity, x1, x2, *(ptr_arr_quantity+i), *(ptr_arr_x1+i), *(ptr_arr_x2+i));
        }
    }
    return fails;
}
