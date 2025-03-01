#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <conio.h>

#define MAX_DEGREE 100
#define TOLERANCE 1e-6

void quadroot(double r, double s, double *r1, double *i1, double *r2, double *i2) {
    double discriminant = r * r + 4 * s;
    if (discriminant > 0) {
        *r1 = (r + sqrt(discriminant)) / 2.0;
        *i1 = 0.0;
        *r2 = (r - sqrt(discriminant)) / 2.0;
        *i2 = 0.0;
    } else {
        *r1 = r / 2.0;
        *i1 = sqrt(-discriminant) / 2.0;
        *r2 = r / 2.0;
        *i2 = -sqrt(-discriminant) / 2.0;
    }
}

void bairstow(double *a, int nn, double es, double rr, double ss, int maxit, double *re, double *im, int *ier) {
    double b[MAX_DEGREE], c[MAX_DEGREE];
    double r = rr, s = ss;
    int n = nn;
    *ier = 0;
    double ea1 = 1, ea2 = 1;

    while (n >= 3 && *ier == 0) {
        int iter = 0;
        while ((ea1 > es || ea2 > es) && iter < maxit) {
            iter++;
            b[n] = a[n];
            b[n - 1] = a[n - 1] + r * b[n];
            c[n] = b[n];
            c[n - 1] = b[n - 1] + r * c[n];
            
            for (int i = n - 2; i >= 0; i--) {
                b[i] = a[i] + r * b[i + 1] + s * b[i + 2];
                c[i] = b[i] + r * c[i + 1] + s * c[i + 2];
            }

            double det = c[2] * c[2] - c[3] * c[1];
            if (det != 0) {
                double dr = (-b[1] * c[2] + b[0] * c[3]) / det;
                double ds = (-b[0] * c[2] + b[1] * c[1]) / det;
                r += dr;
                s += ds;
                if (r != 0) ea1 = fabs(dr / r) * 100;
                if (s != 0) ea2 = fabs(ds / s) * 100;
            } else {
                r += 1;
                s += 1;
                iter = 0;
            }
        }
        if (iter >= maxit) {
            *ier = 1;
            return;
        }

        double r1, i1, r2, i2;
        quadroot(r, s, &r1, &i1, &r2, &i2);
        re[n - 1] = r1;
        im[n - 1] = i1;
        re[n - 2] = r2;
        im[n - 2] = i2;
        n -= 2;

        for (int i = 0; i <= n; i++) {
            a[i] = b[i + 2];
        }
    }

    if (n == 2) {
        double r1, i1, r2, i2;
        r = -a[1] / a[2];
        s = -a[0] / a[2];
        quadroot(r, s, &r1, &i1, &r2, &i2);
        re[1] = r1;
        im[1] = i1;
        re[0] = r2;
        im[0] = i2;
    } else if (n == 1) {
        re[0] = -a[0] / a[1];
        im[0] = 0;
    }
}

int main() {
    double a[MAX_DEGREE];
    double re[MAX_DEGREE], im[MAX_DEGREE];
    int ier;
    int degree;
    double es = 0.0001; // Tolerancia
    double rr, ss; // Estimaciones iniciales
    int maxit = 100; // Máximo número de iteraciones

    printf("Ingrese el grado del polinomio: ");
    scanf("%d", &degree);

    printf("Ingrese los coeficientes del polinomio (del término de mayor grado al término independiente):\n");
    for (int i = degree; i >= 0; i--) {
        printf("Coeficiente de x^%d: ", i);
        scanf("%lf", &a[i]);
    }

    printf("Ingrese el valor inicial de r: ");
    scanf("%lf", &rr);
    printf("Ingrese el valor inicial de s: ");
    scanf("%lf", &ss);

    bairstow(a, degree, es, rr, ss, maxit, re, im, &ier);

    if (ier == 0) {
        printf("Raíces del polinomio:\n");
        for (int i = degree - 1; i >= 0; i--) {
            if (im[i] == 0)
                printf("Raíz %d: %.6f\n", degree - i, re[i]);
            else
                printf("Raíz %d: %.6f + %.6fi\n", degree - i, re[i], im[i]);
        }
    } else {
        printf("No se encontraron todas las raíces después de %d iteraciones.\n", maxit);
    }

    // Pausar el programa antes de salir
    printf("Presione cualquier tecla para salir...");
    getch(); // Esperar a que el usuario presione una tecla

    return 0;
}
