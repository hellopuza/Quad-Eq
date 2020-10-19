/*------------------------------------------------------------------------------
    * File: QuadEq.cpp
    * Description: Program solves quadratic equations.
    * Created: 14 sep 2020
    * Copyright: (C) 2020 MIPT
    * Author: Artem Puzankov
    * Email: puzankov.ao@phystech.edu
    */
//------------------------------------------------------------------------------


#include <stdio.h>
#include <stdlib.h>
#include <math.h>

//#define NDEBUG
#include <assert.h>


int    SolveQuadEq (double a, double b, double c, double* root1, double* root2);
int    SolveEq     (double a, double b, double c, double* root1, double* root2);
int    SolveLinEq  (double a, double c, double* root);

void   GetCoef     (const char* name, double* value);
int    Getline     (char* line);
int    IsZero      (double value);

void   doTest      ();
int    TestEq      (double a, double b, double c, double  root1, double  root2, int num);

const int NUMLEN     = 12;
const double NIL     = 1e-7;
const int NOROOTS    = -1;
const int INFROOTS   = 3;

//------------------------------------------------------------------------------

int main()
{
    doTest();


    double a     = 0;
    double b     = 0;
    double c     = 0;
    double root1 = 0;
    double root2 = 0;


    printf("\n ** -- ** Program solves quadratic equations ** -- **"
           "\n ** -- **        a*x*x + b*x + c = 0         ** -- **\n");


    GetCoef("a", &a);
    GetCoef("b", &b);
    GetCoef("c", &c);


    int NumbRoots = SolveEq(a, b, c, &root1, &root2);


    if (IsZero(a))
        if (IsZero(b))
            printf("\n Your equation is %lg = 0", c);
        else
            printf("\n Your equation is %lg*x + %lg = 0", b, c);
    else
        printf("\n Your equation is %lg*x*x + %lg*x + %lg = 0", a ,b, c);


    switch (NumbRoots)
    {
        case NOROOTS:  printf("\n There are no roots! But I am Groot.");      break;

        case INFROOTS: printf("\n There are infinity number of roots.");      break;

        case 1:        printf("\n There are one root: %lg.",          root1); break;

        case 2:        printf("\n There are two roots: %lg and %lg.", root1,
                                                                    root2);   break;

        default:       assert(0);                                             break;
    }


    printf("\n");


    return 0;
}

//------------------------------------------------------------------------------

/*!
 * Assign an equation type (linear or quadratic)
 * @param a first coefficient
 * @param b second coefficient
 * @param c third coefficient
 * @param *root1 is first root
 * @param *root2 is second root
 * @return number of roots
 */
int SolveEq(double a, double b, double c, double *root1, double *root2)
{
    assert(root1 != root2);

    int NumbRoots = 0;

    if (IsZero(a))
        NumbRoots = SolveLinEq(b, c, root1);
    else
        NumbRoots = SolveQuadEq(a, b, c, root1, root2);

    return NumbRoots;
}

//------------------------------------------------------------------------------

/*!
 * Solves quadratic equation a*x*x + b*x + c = 0
 * @param a first coefficient
 * @param b second coefficient
 * @param c third coefficient
 * @param *root1 is first root
 * @param *root2 is second root
 * @return number of roots
 */
int SolveQuadEq(double a, double b, double c, double *root1, double *root2)
{
    assert(root1 != root2);

    double discr = b*b - 4*a*c;

    if (IsZero(discr)) {

        *root1 = -b/2/a;
        return 1;
    }

    else if (discr < NIL) return NOROOTS;

    else {

        discr  = sqrt(discr);
        *root1 = (-b - discr)/2/a;
        *root2 = (-b + discr)/2/a;
        return 2;
    }

    return 0;
}

//------------------------------------------------------------------------------

/*!
 * Solves linear equation a*x + b = 0
 * @param a first coefficient
 * @param b second coefficient
 * @param *root is the root of the equation
 * @return number of roots
 */
int SolveLinEq(double a, double b, double *root)
{
    if (IsZero(a) && IsZero(b)) return INFROOTS;

    else if (IsZero(a)) return NOROOTS;

    else {

        *root = -b/a;
        return 1;
    }

    return 0;
}

//------------------------------------------------------------------------------

/*!
 * @return true if value is zero
 * @return false if value is not zero
 */
int IsZero (double value)
{
    return (fabs (value) < NIL);
}

//------------------------------------------------------------------------------

/*!
 * Checks that get line (str) is number
 * puts number to value using StrtoFlo()
 * @param *name is name of coefficient
 * @param *value is value of coefficient
 */
void GetCoef(const char* name, double* value)
{
    char str[NUMLEN] = "";
    int error = 0;

    printf("\n Enter %s: ", name);
    int len = Getline(str);

    do {
        for (int i = 0; i != NUMLEN; ++i) {

            if (str[0] == '\0') {

                error = 1;
                break;
            }

            if (str[i] == '\0') {

                error = 0;
                break;
            }

            if (str[i] == ' ') {

                error = 1;
                break;
            }

            if (!('0' <= str[i] && str[i] <= '9' || str[i] == '-'
                                                 || str[i] == '.')) {

                error = 1;
                break;
            }

            if ( (str[i] == '-') && ((i != 0) || (str[1] < '0')
                                              || (str[1] > '9')) ) {

                error = 1;
                break;

            } else {
                if (str[0] == '.') {

                    error = 1;
                    break;
                }
            }

            error = 0;
        }

        if (error) {

            printf("\n Error. Enter number %s: ", name);
            Getline(str);
        }

    } while (error);

    *value = strtod(str, 0);
}

//------------------------------------------------------------------------------

/*!
 * get string line from input
 * @param line is string that gets from INPUT
 * @return length of line
 */
int Getline(char* line)
{
    int c   = 0;
    int len = 0;

    for (len = 0; (len < NUMLEN - 1) && ((c = getchar()) != '\n'); ++len)
        line[len] = c;

    if (c == '\n') line[len] = '\0';

    return len;
}

//------------------------------------------------------------------------------

/*!
 * doing test of SolveEq()
 * @see SolveEq()
 * @param a first coefficient
 * @param b second coefficient
 * @param c third coefficient
 * @param root1 is first root
 * @param root2 is second root
 * @param num is number of roots
 * @return 0 if test successed
 * @return 1 if test falled
 */
int TestEq(double a, double b, double c, double root1, double root2, int num)
{

	double gotRoot1 = 0;
	double gotRoot2 = 0;

	int result = SolveEq(a, b, c, &gotRoot1, &gotRoot2);

	if ( (result == num) && (IsZero(root1 - gotRoot1) &&  IsZero(root2 - gotRoot2))
                         || (IsZero(root1 - gotRoot2) &&  IsZero(root2 - gotRoot1)) ) {

		printf("\n Test %lg, %lg, %lg is SUCCESSFUL\n", a, b, c);

		return 0;

    } else {

		printf("\n Test %lg, %lg, %lg is FAILED\n"

               "\n Expected num = %d, root1 = %lg, root2 = %lg\n"

		 	   "\n      Got num = %d, root1 = %lg, root2 = %lg\n",

			    a, b, c, num, root1, root2, result, gotRoot1, gotRoot2);
		return 1;
    }
}

//------------------------------------------------------------------------------

void doTest()
{
    TestEq (3,  4,  2,  0, 0, NOROOTS );
	TestEq (1, -2, -8, -2, 4, 2       );
	TestEq (0,  0, -1,  0, 0, 1       );
	TestEq (0,  0,  0,  0, 0, INFROOTS);
	TestEq (1,  1,  1,  0, 0, NOROOTS );
}

