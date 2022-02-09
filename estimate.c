#include <stdio.h>
#include <stdlib.h>

double **transpose(double **matrix, int rows, int cols)
{
    double **transp = (double **)malloc(cols * sizeof(int*));

    for (int i = 0; i < cols; i++)
    {
        transp[i] = (double *)malloc(rows * sizeof(int*));
    }

    for (int i = 0; i < rows; i++)
    {
        for (int n = 0; n < cols; n++)
        {
            transp[n][i] = matrix[i][n];
        }
    }

    return transp;
}

double **multiply(double **a, int arows, int acols, double **b, int brows, int bcols)
{
    double **mult = (double **)malloc(arows * sizeof(int*));

    for (int i = 0; i < arows; i++)
    {
        mult[i] = (double *)malloc(bcols * sizeof(int*));
    }

    for (int i = 0; i < arows; i++)
    {
        for (int n = 0; n < bcols; n++)
        {
            mult[i][n] = 0;

            for (int p = 0; p < acols; p++)
            {
                mult[i][n] += a[i][p] * b[p][n];
            }
        }
    }

    return mult;
}

double **inverse(double **matrix, int n)
{
    double **identity = (double **)malloc(n * sizeof(int*));

    for (int i = 0; i < n; i++)
    {
        identity[i] = (double *)malloc(n * sizeof(int*));
    }

    for (int r = 0; r < n; r++)
    {
        for (int c = 0; c < n; c++)
        {
            identity[r][c] = 0;

            if (r == c)
            {
                identity[r][c] = 1;
            }
        }
    }

    for (int p = 0; p < n; p++)
    {
        double x = matrix[p][p];

        for (int q = 0; q < n; q++)
        {
            matrix[p][q] = matrix[p][q] / x;
            identity[p][q] = identity[p][q] / x;
        }

        for (int i = p + 1; i < n; i++)
            {
                double y = matrix[i][p];

                for (int r = 0; r < n; r++)
                {
                    matrix[i][r] = matrix[i][r] - (matrix[p][r] * y);
                    identity[i][r] = identity[i][r] - (identity[p][r] * y);
                }
            }
    }

    for (int p = n - 1; p >= 0; p--)
    {
        for (int i = p - 1; i >= 0; i--)
        {
            double z = matrix[i][p];

            for (int q = 0; q < n; q++)
            {
                matrix[i][q] = matrix[i][q] - (matrix[p][q] * z);
                identity[i][q] = identity[i][q] - (identity[p][q] * z);
            }
        }
    }

    return identity;
}

void printMatrix(double **a, int r, int c)
{
    for (int i = 0; i < r; i++)
    {
        for (int n = 0; n < c; n++)
        {
            printf("%lf  ", a[i][n]);
        }
        printf("\n");
    }
}

void print(double **p, int r)
{
    for (int i = 0; i < r; i++)
    {
        printf("%.0lf\n", p[i][0]);
    }
}

int main(int argc, char **argv)
{
    /*double **a = (double **)malloc(2 * sizeof(int*));

    for (int i = 0; i < 2; i++)
    {
        a[i] = (double *)malloc(3 * sizeof(int*));
    }

    a[0][0] = 1.004;
    a[0][1] = 2.003;
    a[0][2] = 4.002;
    a[1][0] = 1.012;
    a[1][1] = 6.932;
    a[1][2] = 8.001;
    //a[2][0] = 1.034;
    //a[2][1] = 1.092;
    //a[2][2] = 6.993;

    //print(a, 3, 3);

    double **transp = transpose(a, 2, 3);

    print(transp, 3, 2);

    for (int i = 0; i < 3; i++)
    {
        free(transp[i]);
    }
    free(transp);

    double **b = (double **)malloc(3 * sizeof(int*));

    for (int i = 0; i < 3; i++)
    {
        b[i] = (double *)malloc(4 * sizeof(int*));
    }

    b[0][0] = 3.134;
    b[0][1] = 5.323;
    b[0][2] = 4.556;
    b[0][3] = 2.32233;
    b[1][0] = 8.674;
    b[1][1] = 2.436;
    b[1][2] = 4.345;
    b[1][3] = 56.3243;
    b[2][0] = 1.735;
    b[2][1] = 24.312;
    b[2][2] = 33.2;
    b[2][3] = 1.1;

    double **mult = multiply(a, 2, 3, b, 3, 4);

    print(mult, 2, 4);

    for (int i = 0; i < 2; i++)
    {
        free(mult[i]);
    }
    free(mult);

    for (int i = 0; i < 3; i++)
    {
        free(b[i]);
    }
    free(b);

    int **inv = inverse(a, 3);

    print(inv, 3, 3);

    for (int i = 0; i < 3; i++)
    {
        free(inv[i]);
    }
    free(inv);

    for (int i = 0; i < 2; i++)
    {
        free(a[i]);
    }
    free(a);*/

    FILE *train = fopen(argv[1], "r");

    FILE *data = fopen(argv[2], "r");

    if (train == NULL || data == NULL)
    {
        exit(EXIT_FAILURE);
        return 0;
    }

    char tname[10];

    fscanf(train, "%s\n", tname);

    /*fscanf(train, "%s\n", tname);

    if (strcmp(tname, "train") != 0)
    {
        exit(EXIT_FAILURE);
        return 0;
    }*/

    int trows, tcols;

    fscanf(train, "%d\n", &tcols);
    fscanf(train, "%d\n", &trows);

    double **X = (double **)malloc(trows * sizeof(int*));
    double **Y = (double **)malloc(trows * sizeof(int*));

    for (int i = 0; i < trows; i++)
    {
        X[i] = (double *)malloc((tcols + 1) * sizeof(int*));
        Y[i] = (double *)malloc(1 * sizeof(int*));
    }

    for (int r = 0; r < trows; r++)
    {
        X[r][0] = 1;
    }

    for (int r = 0; r < trows; r++)
    {
        for (int c = 0; c < tcols + 1; c++)
        {
            double temp = 0;
            fscanf(train, "%lf\t", &temp);

            if (c == tcols)
            {
                Y[r][0] = temp;
            }
            else
            {
                X[r][c + 1] = temp;
            }
        }
        fscanf(train, "\n");
    }    

    char dname[10];

    fscanf(data, "%s\n", dname);

    int drows, dcols;

    fscanf(data, "%d\n", &dcols);
    fscanf(data, "%d\n", &drows);
    
    double **D = (double **)malloc(drows * sizeof(int*));

    for (int i = 0; i < drows; i++)
    {
        D[i] = (double *)malloc((dcols + 1) * sizeof(int*));
    }

    for (int i = 0; i < drows; i++)
    {
        D[i][0] = 1;
    }

    for (int r = 0; r < drows; r++)
    {
        for (int c = 1; c < dcols + 1; c++)
        {
            double temp;
            fscanf(data, "%lf\t", &temp);
            D[r][c] = temp;
        }
        fscanf(data, "\n");
    }

    if (tcols != dcols)
    {
        exit(EXIT_FAILURE);
        return 0;
    }

    double **Xtrans = transpose(X, trows, tcols + 1);
    double **XTX = multiply(Xtrans, tcols + 1, trows, X, trows, tcols + 1);
    double **XTXinv = inverse(XTX, tcols + 1);
    double **timesXT = multiply(XTXinv, tcols + 1, tcols + 1, Xtrans, tcols + 1, trows);

    double **W = multiply(timesXT, tcols + 1, trows, Y, trows, 1);

    double **P = multiply(D, drows, dcols + 1, W, tcols + 1, 1);

    /*printMatrix(X, trows, tcols + 1);
    printf("\n");
    printMatrix(Y, trows, 1);
    printf("\n");
    printMatrix(D, drows, dcols + 1);
    printf("\n");
    printMatrix(W, tcols + 1, 1);
    printf("\n");*/
    
    print(P, drows);

    //printMatrix(XTXinv, tcols + 1, tcols + 1);

    //Free all matrices

    for (int i = 0; i < trows; i++)
    {
        free(X[i]);
        free(Y[i]);
    }
    free(X);
    free(Y);

    for (int i = 0; i < drows; i++)
    {
        free(D[i]);
    }
    free(D);

    for (int i = 0; i < tcols + 1; i++)
    {
        free(Xtrans[i]);
    }
    free(Xtrans);

    for (int i = 0; i < tcols + 1; i++)
    {
        free(XTX[i]);
    }
    free(XTX);

    for (int i = 0; i < tcols + 1; i++)
    {
        free(XTXinv[i]);
    }
    free(XTXinv);

    for (int i = 0; i < tcols + 1; i++)
    {
        free(timesXT[i]);
    }
    free(timesXT);

    for (int i = 0; i < tcols + 1; i++)
    {
        free(W[i]);
    }
    free(W);

    for (int i = 0; i < drows; i++)
    {
        free(P[i]);
    }
    free(P);

    exit(EXIT_SUCCESS);
    return 0;
}