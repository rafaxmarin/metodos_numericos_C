#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Definir la función f(x) manualmente
double f(double x) {
    return exp(3 * x) - 4;  // Ejemplo: exp(3*x) - 4
}

void falsa_posicion(double (*f)(double), double a, double c, double es, int imax, double *raiz, int *iter, double *ea) {
    int iter_count = 0;
    double b = 0.0;
    double b_old;
    *ea = 100.0;  

    printf("\nIteración\t[a, b, c]\t\t[f(a), f(b), f(c)]\t\tError aprox. (%%)");
    printf("\n------------------------------------------------------------------------\n");

    while (1) {
        b_old = b;
        b = a - (f(a) * (c - a)) / (f(c) - f(a));  
        iter_count++;

        if (b != 0.0) {
            *ea = fabs((b - b_old) / b) * 100.0;  
        }

        // Mostrar valores de la iteración
        printf("%d\t\t[%.6f, %.6f, %.6f]\t[%.6f, %.6f, %.6f]\t\t%.6f\n", 
               iter_count, a, b, c, f(a), f(b), f(c), *ea);

        double test = f(a) * f(b);

        if (test < 0.0) {
            c = b;  // La raíz está en [a, b]
        } else if (test > 0.0) {
            a = b;  // La raíz está en [b, c]
        } else {
            *ea = 0.0;  // Raíz exacta encontrada
        }

        if (*ea < es || iter_count >= imax) {
            break;
        }
    }

    *raiz = b;
    *iter = iter_count;
}

int main() {
    double a, c, es, raiz, ea;
    int imax, iter;

    // Solicitar parámetros del intervalo
    printf("Límite inferior del intervalo (a): ");
    scanf("%lf", &a);
    printf("Límite superior del intervalo (c): ");
    scanf("%lf", &c);

    // Validar intervalo
    if (a >= c) {
        printf("Error: c debe ser mayor que a.\n");
        printf("Presione cualquier tecla para salir...\n");
        getchar();
        getchar();  
        return 1;
    }

    // Validar cambio de signo
    double fa = f(a);
    double fc = f(c);
    if (fa * fc >= 0) {
        printf("Error: f(a) y f(c) deben tener signos opuestos.\n");
        printf("Presione cualquier tecla para salir...\n");
        getchar(); 
        getchar(); 
        return 1;
    }


    printf("Tolerancia deseada (ej. 0.01 para 1%%): ");
    scanf("%lf", &es);
    printf("Número máximo de iteraciones: ");
    scanf("%d", &imax);

   
    falsa_posicion(f, a, c, es, imax, &raiz, &iter, &ea);

  
    printf("\nResultado:\n");
    printf("Raíz aproximada: %.6f\n", raiz);
    printf("Iteraciones: %d\n", iter);
    printf("Error aproximado: %.6f%%\n", ea);

   
    printf("Presione cualquier tecla para salir...\n");
    getchar(); 

    return 0;
}