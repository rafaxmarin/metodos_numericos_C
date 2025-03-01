#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DATA_POINTS 100

//  y = a * e^(b * x)
void regresion_exponencial(int n, double x[], double y[], double *a, double *b, double *r) {
    double sum_x = 0.0, sum_ln_y = 0.0;
    double sum_x_cuadrado = 0.0, sum_x_ln_y = 0.0;

    // Calcular sumatorias
    for (int i = 0; i < n; i++) {
        sum_x = sum_x + x[i];
        sum_ln_y = sum_ln_y + log(y[i]);
        sum_x_cuadrado = sum_x_cuadrado + x[i] * x[i];
        sum_x_ln_y = sum_x_ln_y + x[i] * log(y[i]);
    }

    // Calcular los estimadores
    double denominador = n * sum_x_cuadrado - sum_x * sum_x;
    if (fabs(denominador) < 1e-10) {
        printf("Error: Division por cero. Los datos pueden ser colineales.\n");
        *a = 0.0;
        *b = 0.0;
        *r = 0.0;
        return;
    }

    *b = (n * sum_x_ln_y - sum_x * sum_ln_y) / denominador;
    double ln_a = (sum_ln_y - (*b) * sum_x) / n;

    // Convertir ln(a) de vuelta a a
    *a = exp(ln_a);

    // Calcular el coeficiente r
    double sum_ln_y_cuadrado = 0.0;
    for (int i = 0; i < n; i++) {
        sum_ln_y_cuadrado = sum_ln_y_cuadrado + log(y[i]) * log(y[i]);
    }

    *r = (n * sum_x_ln_y - sum_x * sum_ln_y) /
         sqrt((n * sum_x_cuadrado - sum_x * sum_x) *
              (n * sum_ln_y_cuadrado - sum_ln_y * sum_ln_y));
}

int main() {
    int n;
    double x[MAX_DATA_POINTS], y[MAX_DATA_POINTS];

   
    printf("Ingrese el numero de puntos de datos (maximo %d): ", MAX_DATA_POINTS);
    scanf("%d", &n);

    if (n > MAX_DATA_POINTS || n <= 0) {
        printf("Numero de puntos no valido.\n");
        return 1;
    }

    // Leer los valores de x e y
    printf("Ingrese los valores de x e y (y debe ser positivo):\n");
    for (int i = 0; i < n; i++) {
        printf("Punto %d: x = ", i + 1);
        scanf("%lf", &x[i]);

        do {
            printf("Punto %d: y = ", i + 1);
            scanf("%lf", &y[i]);
            if (y[i] <= 0) {
                printf("El valor de y debe ser positivo. Intente nuevamente.\n");
            }
        } while (y[i] <= 0); // Asegurarse que y sea positivo
    }

    // Ajustar los datos
    double a_fit, b_fit, rxy;
    regresion_exponencial(n, x, y, &a_fit, &b_fit, &rxy);

    // Imprimir los parámetros ajustados
    printf("Estimadores: a = %.4f, b = %.4f\n", a_fit, b_fit);
    printf("Coeficiente de correlacion: r = %.4f\n", rxy);

    // Pausa antes de cerrar el programa
    printf("\nPresione cualquier tecla para salir...");
    getchar();  
    getchar(); 

    return 0;
}