#include <stdio.h>
#include <math.h>

// Definir la función f(x) manualmente
double f(double x) {
    return exp(-x) - x;  // Ejemplo: exp(-x) - x
}

// Definir la derivada de f(x) manualmente
double df(double x) {
    return -exp(-x) - 1;  // Ejemplo: -exp(-x) - 1
}

void NewtonRaphson(double (*f)(double), double (*df)(double), double x0, double tol, int n) {
    double x1, error;
    for (int k = 0; k < n; k++) {
        x1 = x0 - f(x0) / df(x0);  // Fórmula de Newton-Raphson
        error = fabs((x1 - x0) / x1) * 100;  // Cálculo del error relativo porcentual

        if (fabs(x1 - x0) < tol) {
            printf("x%d = %.6f Es la raiz con un error de %.6f%%\n", k + 1, x1, error);
            return;
        }

        x0 = x1;  // Actualizar x0 para la siguiente iteración
        printf("x%d = %.6f con un error de %.6f%%\n", k + 1, x1, error);
    }

    printf("No se encontro la raiz en el numero maximo de iteraciones.\n");
}

int main() {
    double x0, tol;
    int n;

    // Solicitar parámetros
    printf("Valor inicial (x0): ");
    scanf("%lf", &x0);
    printf("Tolerancia deseada (ej. 0.0000001): ");
    scanf("%lf", &tol);
    printf("Numero maximo de iteraciones: ");
    scanf("%d", &n);

    // Calcular raíz
    NewtonRaphson(f, df, x0, tol, n);

    // Esperar a que el usuario presione una tecla antes de cerrar
    printf("Presione cualquier tecla para salir...\n");
    getchar(); // Captura el salto de línea pendiente
    getchar(); // Espera a que el usuario presione una tecla

    return 0;
}