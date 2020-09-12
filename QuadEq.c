#include <stdio.h>
#include <math.h>


bool IsZero (double value);
void SolveEq(double a, double b, double c, double* root1, double* root2);
int SolveQuadEq(double a, double b, double c, double* root1, double* root2);
int SolveLinEq(double a, double c, double* root);


const double nil = 1e-7;
const int noRoots = -1;
const int infRoots = 3;



int main()
{
    double a = 0;
    double b = 0;
    double c = 0;
    double root1 = 0;
    double root2 = 0;


    printf("\n ** -- ** Program solves quadratic equations ** -- **\n"
           "\n a*x*x + b*x + c = 0 format\n");


    printf("\n Enter a: ");
    scanf("%lf", &a);


    printf("\n Enter b: ");
    scanf("%lf", &b);


    printf("\n Enter c: ");
    scanf("%lf", &c);


    SolveEq(a, b, c, &root1, &root2);

    printf("\n");


    return 0;
}



void SolveEq(double a, double b, double c, double *root1, double *root2)
{
    int NumbRoots = 0;

    if (IsZero(a))
        NumbRoots = SolveLinEq(b, c, root1);
    else
        NumbRoots = SolveQuadEq(a, b, c, root1, root2);


    switch(NumbRoots)
    {
        case noRoots:  printf("\n There are no roots"); break;

        case infRoots: printf("\n There are infinity number of roots"); break;

        case 1:        printf("\n There are one root: %lf",          *root1);
                break;

        case 2:        printf("\n There are two roots: %lf and %lf", *root1,
                                                                     *root2);
                break;

        default: printf("\n error with NumbRoots line 72 \n"); break;
    }
}



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



bool IsZero (double value)
{
    if ((value <= nil) && (value >= - nil)) return true;

    else return false;
}

