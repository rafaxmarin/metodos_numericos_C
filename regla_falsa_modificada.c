#include <stdio.h>
#include <math.h>
#include <stdlib.h>


double f(double x) {
    return exp(3 * x) - 4;  // Ejemplo: exp(3*x) - 4
}

void falsa_modificada(double (*f)(double), double a, double b, double es, int imax, double *raiz, int *iter, double *ea) {
    int iter_count = 0;
    double xr = 0.0;
    double xr_old;
    *ea = 100.0;  // Error inicial del 100%
    double fl = f(a);
    double fu = f(b);
    int il = 0; 
    int iu = 0;  

    printf("\nIteración\t[a, xr, b]\t\t[f(a), f(xr), f(b)]\t\tError aprox. (%%)");
    printf("\n------------------------------------------------------------------------\n");

    while (1) {
        xr_old = xr;
        xr = b - fu * (a - b) / (fl - fu);  // Fórmula de la falsa posición
        double fr = f(xr);
        iter_count++;

        if (xr != 0.0) {
            *ea = fabs((xr - xr_old) / xr) * 100.0;  // Cálculo del error aproximado
        }

        // Mostrar valores de la iteración
        printf("%d\t\t[%.6f, %.6f, %.6f]\t[%.6f, %.6f, %.6f]\t\t%.6f\n", 
               iter_count, a, xr, b, fl, fr, fu, *ea);

        double test = fl * fr;

        if (test < 0.0) {
            b = xr;
            fu = fr;
            iu = 0;
            il += 1;
            if (il >= 2) {
                fl /= 2;  // Reducir fl a la mitad
            }
        } else if (test > 0.0) {
            a = xr;
            fl = fr;
            il = 0;
            iu += 1;
            if (iu >= 2) {
                fu /= 2;  // Reducir fu a la mitad
            }
        } else {
            *ea = 0.0;  // Raíz exacta encontrada
        }

        if (*ea < es || iter_count >= imax) {
            break;
        }
    }

    *raiz = xr;
    *iter = iter_count;
}

int main() {
    double a, b, es, raiz, ea;
    int imax, iter;

    // Solicitar parámetros del intervalo
    printf("Límite inferior del intervalo (a): ");
    scanf("%lf", &a);
    printf("Límite superior del intervalo (b): ");
    scanf("%lf", &b);

    // Validar intervalo
    if (a >= b) {
        printf("Error: b debe ser mayor que a.\n");
        printf("Presione cualquier tecla para salir...\n");
        getchar(); // Captura el salto de línea pendiente
        getchar(); // Espera a que el usuario presione una tecla
        return 1;
    }

    // Validar cambio de signo
    double fl = f(a);
    double fu = f(b);
    if (fl * fu >= 0) {
        printf("Error: f(a) y f(b) deben tener signos opuestos.\n");
        printf("Presione cualquier tecla para salir...\n");
        getchar(); // Captura el salto de línea pendiente
        getchar(); // Espera a que el usuario presione una tecla
        return 1;
    }

    // Solicitar tolerancia e iteraciones
    printf("Tolerancia deseada (ej. 0.01 para 1%%): ");
    scanf("%lf", &es);
    printf("Número máximo de iteraciones: ");
    scanf("%d", &imax);

    // Calcular raíz
    falsa_modificada(f, a, b, es, imax, &raiz, &iter, &ea);

    // Resultado final
    printf("\nResultado:\n");
    printf("Raíz aproximada: %.6f\n", raiz);
    printf("Iteraciones: %d\n", iter);
    printf("Error aproximado: %.6f%%\n", ea);

    // Esperar a que el usuario presione una tecla antes de cerrar
    printf("Presione cualquier tecla para salir...\n");
    getchar(); // Captura el salto de línea pendiente
    getchar(); // Espera a que el usuario presione una tecla

    return 0;
}