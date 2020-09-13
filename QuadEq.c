#include <stdio.h>
#include <math.h>


int SolveEq(double a, double b, double c, double* root1, double* root2);
int SolveQuadEq(double a, double b, double c, double* root1, double* root2);
int SolveLinEq(double a, double c, double* root);
bool IsZero (double value);
void GetCoef(char c, double* value);
double StrtoFlo(char *str);


const int NumbLen = 12;
const double nil = 1e-7;
const int noRoots = -1;
const int infRoots = 3;

//------------------------------------------------------------------------------

int main()
{
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

        default: printf("\n error with NumbRoots line 72 \n"); break;
    }


    printf("\n");


    return 0;
}

//------------------------------------------------------------------------------

int SolveEq(double a, double b, double c, double *root1, double *root2)
{
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
    if ((value <= nil) && (value >= - nil)) return true;

    else return false;
}

//------------------------------------------------------------------------------

void GetCoef(char c, double* value)
{
    char str[NumbLen] {'\0'};
    int error = 0;

    printf("\n Enter %c: ", c);
    scanf("%s", str);

    do {
        for (int i = 0; i != NumbLen; ++i) {

            if (str[i] == '\0') {

                    error = 0;
                    break;
            }


            if (!('0' <= str[i] && str[i] <= '9' || str[i] == '-'
                                                 || str[i] == '.')) {

                error = 1;
                break;
            }


            if (str[i] == '-' && i != 0) {

                error = 1;
                break;
            }


            error = 0;
        }

        if (error) {

            printf("\n Error. Enter number %c: ", c);
            scanf("%s", str);
        }

    } while (error);

    *value = StrtoFlo(str);
}

//------------------------------------------------------------------------------

double StrtoFlo(char *str)
{
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
