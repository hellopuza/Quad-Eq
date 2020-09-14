/*------------------------------------------------------------------------------
     * File: QuadEq.c
     * Description: Program solves quadratic equations.
     * Created: 14 sep 2020
     * Copyright: (C) 2020 MIPT
     * Author: Artem Puzankov
     * Email: puzankov.ao@phystech.edu
     */
//------------------------------------------------------------------------------


#include <stdio.h>
#include <math.h>


int TestEq  (double a, double b, double c, int num, double root1, double root2);
int SolveEq    (double a, double b, double c, double* root1, double* root2);
int SolveQuadEq(double a, double b, double c, double* root1, double* root2);
int SolveLinEq (double a, double c, double* root);
bool IsZero    (double value);
void GetCoef   (char c, double* value);
double StrtoFlo(char *str);
int Getline    (char* line);


const int NumbLen  = 12;
const double nil   = 1e-7;
const int noRoots  = -1;
const int infRoots = 3;

//------------------------------------------------------------------------------

int main()
{
// Tests ----------------------------------------------------------------------
//>
	TestEq(3, 4, 2, noRoots, 0, 0);
	TestEq(5, 8, -9, 2, 0.762049935, -2.362049935);
	TestEq(1, 0, -4, 2, -2, 2);
	TestEq(1, 6, 9, 1, -3, 0);
//>

/*!
 *
 */

    double a = 0;
    double b = 0;
    double c = 0;
    double root1 = 0;
    double root2 = 0;


    printf("\n ** -- ** Program solves quadratic equations ** -- **"
           "\n ** -- **        a*x*x + b*x + c = 0         ** -- **\n");


    GetCoef('a', &a);
    GetCoef('b', &b);
    GetCoef('c', &c);


    int NumbRoots = SolveEq(a, b, c, &root1, &root2);


    switch(NumbRoots)
    {
        case noRoots:  printf("\n There are no roots"); break;

        case infRoots: printf("\n There are infinity number of roots"); break;

        case 1:        printf("\n There are one root: %lf",          root1);
                break;

        case 2:        printf("\n There are two roots: %lf and %lf", root1,
                                                                     root2);
                break;

        default: printf("\n error with NumbRoots line 54 \n"); break;
    }


    printf("\n");


    return 0;
}

//------------------------------------------------------------------------------

int SolveEq(double a, double b, double c, double *root1, double *root2)
{

/*!
 * Assign an equation type (linear or quadratic)
 * return number of roots
 */

    int NumbRoots = 0;

    if (IsZero(a))
        NumbRoots = SolveLinEq(b, c, root1);
    else
        NumbRoots = SolveQuadEq(a, b, c, root1, root2);

    return NumbRoots;
}

//------------------------------------------------------------------------------

int SolveQuadEq(double a, double b, double c, double *root1, double *root2)
{

/*!
 * Solves quadratic equation a*x*x + b*x + c = 0
 * return number of roots
 * a, b, c - coefficients
 */

    double discr = b*b - 4*a*c;

    if (IsZero(discr)) {

        *root1 = -b/2/a;
        return 1;
    }

    else if (discr < nil) return noRoots;

    else {

        *root1 = (-b - sqrt(discr))/2/a;
        *root2 = (-b + sqrt(discr))/2/a;
        return 2;
    }

    return 0;
}

//------------------------------------------------------------------------------

int SolveLinEq(double a, double b, double *root)
{

/*!
 * Solves linear equation a*x + b = 0
 * return number of roots
 * a, b, - coefficients
 */

    if (IsZero(a) && IsZero(b)) return infRoots;

    else if (IsZero(a)) return noRoots;

    else {

        *root = -b/a;
        return 1;
    }

    return 0;
}

//------------------------------------------------------------------------------

bool IsZero (double value)
{

/*!
 * return true if value is zero
 * return false if value is not zero
 */

    if ((value <= nil) && (value >= - nil)) return true;

    else return false;
}

//------------------------------------------------------------------------------

void GetCoef(char c, double* value)
{

/*!
 * Checks that get line (str) is number
 * puts number to value using StrtoFlo()
 */

    char str[NumbLen] {'\0'};
    int error = 0;

    printf("\n Enter %c: ", c);
    Getline(str);

    do {
        for (int i = 0; i != NumbLen; ++i) {

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

            printf("\n Error. Enter number %c: ", c);
            Getline(str);
        }

    } while (error);

    *value = StrtoFlo(str);
}

//------------------------------------------------------------------------------

double StrtoFlo(char *str)
{

/*!
 * Сonverts a string to a signed double number
 * return number
 */

    double numb = 0;
    int sign = 1;
    if (*str == '-') {

        sign = -1;
        *str++;
    }

    while (*str != '.' && *str != '\0') {

        numb = numb * 10 + (*str) - '0';
        str++;
    }

    if (*str == '\0')
        return numb*sign;
    str++;

    int k = 10;
    while (*str != '\0') {

        numb += (double)((*str) - '0') / k;
        k *= 10;
        str++;
    }

    return numb*sign;
}

//------------------------------------------------------------------------------

int Getline(char* line)
{

/*!
 * get string line from input
 * return length of line
 */

    int c, i;

    for (i = 0; (i < NumbLen - 1) && ((c = getchar()) != '\n'); ++i)
        line[i] = c;

    if (c == '\n') line[i] = '\0';

    return i;
}

//------------------------------------------------------------------------------

int TestEq(double a, double b, double c, int num, double root1, double root2)
{

/*!
 * doing test of SolveEq()
 */

	double gotRoot1 = 0;
	double gotRoot2 = 0;

	int result = SolveEq(a, b, c, &gotRoot1, &gotRoot2);

	if ( (result == num) && (IsZero(root1 - gotRoot1)
                         &&  IsZero(root2 - gotRoot2))
                         || (IsZero(root1 - gotRoot2)
                         &&  IsZero(root2 - gotRoot1)) ) {

		printf("\n Test %lf, %lf, %lf is SUCCESSFUL\n", a, b, c);

		return 0;

    } else {

		printf("\n Test %lf, %lf, %lf is FAILED\n"

               "\n Expected num = %d, root1 = %lg, root2 = %lg\n"

		 	   "\n Got num = %d, root1 = %lg, root2 = %lg\n",

			    a, b, c, num, root1, root2, result, gotRoot1, gotRoot2);
		return 1;
    }
}

//------------------------------------------------------------------------------

