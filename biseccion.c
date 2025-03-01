#include <stdio.h>
#include <math.h>
#include <stdlib.h>

// Definir la función f(x) manualmente
double f(double x) {
    return exp(-x) - 2;  // Ejemplo: sin(x) - 0.5
}

void bisect(double (*f)(double), double a, double b, double es, int imax, double *raiz, int *iter, double *ea) {
    int iter_count = 0;
    double pm = 0.0;
    double oldpm;
    *ea = 100.0; 

    printf("\nIteración\t[a, pm, b]\t\t[f(a), f(pm), f(b)]\t\tError aprox. (%%)");
    printf("\n------------------------------------------------------------------------\n");

    while (1) {
        oldpm = pm;
        pm = (a + b) / 2.0;
        iter_count++;

        if (pm != 0.0) {
            *ea = fabs((pm - oldpm) / pm) * 100.0;
        }

        // Mostrar valores de la iteración
        printf("%d\t\t[%.6f, %.6f, %.6f]\t[%.6f, %.6f, %.6f]\t\t%.6f\n", 
               iter_count, a, pm, b, f(a), f(pm), f(b), *ea);

        double test = f(a) * f(pm);

        if (test < 0.0) {
            b = pm;
        } else if (test > 0.0) {
            a = pm;
        } else {
            *ea = 0.0;
        }

        if (*ea < es || iter_count >= imax) {
            break;
        }
    }

    *raiz = pm;
    *iter = iter_count;
}

int main() {
    double a, b, es, raiz, ea;
    int imax, iter;

 
    printf("Límite inferior del intervalo (a): ");
    scanf("%lf", &a);
    printf("Límite superior del intervalo (b): ");
    scanf("%lf", &b);


    if (a >= b) {
        printf("Error: b debe ser mayor que a.\n");
        printf("Presione cualquier tecla para salir...\n");
        getchar();
   
        return 1;
    }

    printf("Tolerancia deseada (ej. 0.01 para 1%%): ");
    scanf("%lf", &es);
    printf("Número máximo de iteraciones: ");
    scanf("%d", &imax);

    // Validar cambio de signo
    if (f(a) * f(b) >= 0) {
        printf("Error: f(a) y f(b) deben tener signos opuestos.\n");
        printf("Presione cualquier tecla para salir...\n");
        getchar(); 
      
        return 1;
    }

    // Calcular raíz
    bisect(f, a, b, es, imax, &raiz, &iter, &ea);

    // Resultado final
    printf("\nResultado:\n");
    printf("Raíz aproximada: %.6f\n", raiz);
    printf("Iteraciones: %d\n", iter);
    printf("Error aproximado: %.6f%%\n", ea);

 
    printf("Presione cualquier tecla para salir...\n");
    getchar(); 

    return 0;
}