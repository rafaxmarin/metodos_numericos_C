#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_DATA_POINTS 100

// Función para ajustar los datos a una función de la forma y = b * x^m
void power_fit(int n, double x[], double y[], double *b, double *m, double *r) {
    double log_x[MAX_DATA_POINTS], log_y[MAX_DATA_POINTS];
    for (int i = 0; i < n; i++) {
        log_x[i] = log(x[i]);
        log_y[i] = log(y[i]);
    }

    double sum_log_x = 0.0, sum_log_y = 0.0;
    double sum_log_x_log_y = 0.0, sum_log_x_squared = 0.0, sum_log_y_squared = 0.0;

    for (int i = 0; i < n; i++) {
        sum_log_x += log_x[i];
        sum_log_y += log_y[i];
        sum_log_x_log_y += log_x[i] * log_y[i];
        sum_log_x_squared += log_x[i] * log_x[i];
        sum_log_y_squared += log_y[i] * log_y[i];
    }

    // Calcular los coeficientes m (pendiente) y C (intersección)
    *m = (n * sum_log_x_log_y - sum_log_x * sum_log_y) / (n * sum_log_x_squared - sum_log_x * sum_log_x);
    double c_fit = (sum_log_y - (*m) * sum_log_x) / n;

    // Convertir C de vuelta a b
    *b = exp(c_fit);

    // Calcular el coeficiente de correlación
    *r = ((n * sum_log_x_log_y) - (sum_log_x * sum_log_y)) /
         sqrt((n * sum_log_x_squared - sum_log_x * sum_log_x) *
              (n * sum_log_y_squared - sum_log_y * sum_log_y));
}

int main() {
    int n;
    double x[MAX_DATA_POINTS], y[MAX_DATA_POINTS];

    // Solicitar al usuario el número de puntos de datos
    printf("Ingrese el número de puntos de datos (máximo %d): ", MAX_DATA_POINTS);
    scanf("%d", &n);

    if (n > MAX_DATA_POINTS || n <= 0) {
        printf("Número de puntos no válido.\n");
        return 1;
    }

    // Leer los valores de x e y
    printf("Ingrese los valores de x e y:\n");
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
    double b_fit, m_fit, rxy;
    power_fit(n, x, y, &b_fit, &m_fit, &rxy);

    // Imprimir los parámetros ajustados
    printf("Parámetros ajustados: b = %.4f, m = %.4f\n", b_fit, m_fit);
    printf("Coeficiente de correlación: r = %.4f\n", rxy);

    return 0;
}
