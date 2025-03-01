#include <stdio.h>
#include <math.h>


double f(double x) {
    return -0.4*x*x+2.3*x+2.2;  
}


void secante(double x0, double x1, double tol, int itMax, double *raiz, double *error, int *iteraciones) {
    int it = 0;
    double Er = 100.0;  
    double xa1 = x0;
    double x = x1;

    // Encabezado de la tabla de iteraciones
    printf("\nIteracion\tx\t\tError relativo (%%)\n");
    printf("--------------------------------------------\n");

    while (Er >= tol && it < itMax) {
        double xa2 = xa1;
        xa1 = x;

        // Fórmula de la secante
        x = xa1 - f(xa1) * (xa2 - xa1) / (f(xa2) - f(xa1));

        // Calcular el error relativo
        if (it == 0) {
            Er = 100.0;  // Primera iteración: error del 100%
        } else {
            Er = fabs((x - xa1) / x) * 100;  // Error relativo porcentual
        }

        it++;

        // Mostrar los valores de la iteración actual
        printf("%d\t\t%.6f\t%.6f\n", it, x, Er);
    }

    *raiz = x;
    *error = Er;
    *iteraciones = it;
}

int main() {
    double x0, x1, tol;
    int itMax;

    // Solicitar valores al usuario
    printf("Ingrese el valor inicial x0: ");
    scanf("%lf", &x0);
    printf("Ingrese el valor inicial x1: ");
    scanf("%lf", &x1);
    printf("Ingrese la tolerancia deseada (Ejemplo: 0.00001): ");
    scanf("%lf", &tol);
    printf("Ingrese el numero maximo de iteraciones: ");
    scanf("%d", &itMax);

    // Limpiar el búfer de entrada
    while (getchar() != '\n');  // Captura todos los caracteres restantes en el búfer

    // Variables para almacenar los resultados
    double raiz, error;
    int iteraciones;

    // Calcular la raíz usando el método de la secante
    secante(x0, x1, tol, itMax, &raiz, &error, &iteraciones);

    // Mostrar resultados finales
    printf("\nResultado final:\n");
    printf("El valor de la raiz es: %.4f\n", raiz);
    printf("El error relativo fue: %.6f%%\n", error);
    // printf("El numero de iteraciones realizadas fue: %d\n", iteraciones);

    // Esperar a que el usuario presione una tecla antes de cerrar
    printf("Presione cualquier tecla para salir...\n");
    getchar(); // Espera a que el usuario presione una tecla

    return 0;
}