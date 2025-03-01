#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DATA_POINTS 100

// Funcion para ajustar los datos a una funcion lineal y = m * x +- b
void regresion_lineal(int n, double x[], double y[], double *a, double *b, double *r) {
    double sum_x = 0.0, sum_y = 0.0;
    double sum_x_cuadrado = 0.0, sum_xy = 0.0;

   
    for (int i = 0; i < n; i++) {
        sum_x = sum_x + x[i];
        sum_y = sum_y + y[i];
        sum_x_cuadrado = sum_x_cuadrado + x[i] * x[i];
        sum_xy = sum_xy + x[i] * y[i];
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

    *a = (n * sum_xy - sum_x * sum_y) / denominador;
    *b = (sum_y - (*a) * sum_x) / n;

    // Calcular (r)
    double sum_y_cuadrado = 0.0;
    for (int i = 0; i < n; i++) {
        sum_y_cuadrado += y[i] * y[i];
    }

    *r = (n * sum_xy - sum_x * sum_y) /
         sqrt((n * sum_x_cuadrado - sum_x * sum_x) *
              (n * sum_y_cuadrado - sum_y * sum_y));
}

int main() {
    int n;
    double x[MAX_DATA_POINTS], y[MAX_DATA_POINTS];

    // Solicitar al usuario el número de puntos de datos
    printf("Ingrese el numero de puntos de datos (maximo %d): ", MAX_DATA_POINTS);
    scanf("%d", &n);

    if (n > MAX_DATA_POINTS || n <= 0) {
        printf("Numero de puntos no valido.\n");
        return 1;
    }

    // Leer los valores de x e y
    printf("Ingrese los valores de x e y:\n");
    for (int i = 0; i < n; i++) {
        printf("Punto %d: x = ", i + 1);
        scanf("%lf", &x[i]);
        printf("Punto %d: y = ", i + 1);
        scanf("%lf", &y[i]);
    }

    // Ajustar los datos
    double a_fit, b_fit, rxy;
    regresion_lineal(n, x, y, &a_fit, &b_fit, &rxy);

    // Imprimir los parámetros ajustados
    printf("Estimadores: a = %.4f, b = %.4f\n", a_fit, b_fit);
    printf("Coeficiente de correlacion: r = %.4f\n", rxy);

    // Pausa antes de cerrar el programa
    printf("\nPresione cualquier tecla para salir...");
    getchar();  // Captura el carácter de nueva línea pendiente
    getchar();  // Espera a que el usuario presione cualquier tecla

    return 0;
}