#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DATA_POINTS 100

// Función para ajustar los datos a una función logarítmica y = a + b * ln(x)
void regresion_logaritmica(int n, double x[], double y[], double *a, double *b, double *r) {
    double sum_ln_x = 0.0, sum_y = 0.0;
    double sum_ln_x_cuadrado = 0.0, sum_ln_x_y = 0.0;

    // Calcular sumatorias
    for (int i = 0; i < n; i++) {
        if (x[i] <= 0) {
            printf("Error: x debe ser positivo para calcular ln(x).\n");
            *a = 0.0;
            *b = 0.0;
            *r = 0.0;
            return;
        }
        sum_ln_x += log(x[i]);
        sum_y += y[i];
        sum_ln_x_cuadrado += log(x[i]) * log(x[i]);
        sum_ln_x_y += log(x[i]) * y[i];
    }

    // Calcular los estimadores
    double denominador = n * sum_ln_x_cuadrado - sum_ln_x * sum_ln_x;
    if (fabs(denominador) < 1e-10) {
        printf("Error: Division por cero. Los datos pueden ser colineales.\n");
        *a = 0.0;
        *b = 0.0;
        *r = 0.0;
        return;
    }

    *b = (n * sum_ln_x_y - sum_ln_x * sum_y) / denominador;
    *a = (sum_y - (*b) * sum_ln_x) / n;

    // Calcular el coeficiente r
    double sum_y_cuadrado = 0.0;
    for (int i = 0; i < n; i++) {
        sum_y_cuadrado += y[i] * y[i];
    }

    *r = (n * sum_ln_x_y - sum_ln_x * sum_y) /
         sqrt((n * sum_ln_x_cuadrado - sum_ln_x * sum_ln_x) *
              (n * sum_y_cuadrado - sum_y * sum_y));
}

int main() {
    int n;
    double x[MAX_DATA_POINTS], y[MAX_DATA_POINTS];

    // Solicitar al usuario el numero de puntos de datos
    printf("Ingrese el numero de puntos de datos (maximo %d): ", MAX_DATA_POINTS);
    scanf("%d", &n);

    if (n > MAX_DATA_POINTS || n <= 0) {
        printf("Numero de puntos no valido.\n");
        return 1;
    }

    // Leer los valores de x e y
    printf("Ingrese los valores de x e y (x debe ser positivo):\n");
    for (int i = 0; i < n; i++) {
        printf("Punto %d: x = ", i + 1);
        scanf("%lf", &x[i]);

        if (x[i] <= 0) {
            printf("Error: x debe ser positivo para calcular ln(x).\n");
            return 1;
        }

        printf("Punto %d: y = ", i + 1);
        scanf("%lf", &y[i]);
    }

    // Ajustar los datos
    double a_fit, b_fit, rxy;
    regresion_logaritmica(n, x, y, &a_fit, &b_fit, &rxy);

   
    printf("Estimadores: a = %.6f, b = %.6f\n", a_fit, b_fit);
    printf("Coeficiente de correlación: r = %.6f\n", rxy);

   
    printf("\nPresione cualquier tecla para salir...");
    getchar();  
    getchar(); 

    return 0;
}