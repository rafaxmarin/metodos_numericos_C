#include <stdio.h>
#include <math.h>

// Función para evaluar un polinomio usando el método de Horner
double evaluar_polinomio(double coeficientes[], int grado, double x) {
    double resultado = coeficientes[0];  // Inicializa con el coeficiente de mayor grado
    for (int i = 1; i <= grado; i++) {
        resultado = resultado * x + coeficientes[i];
    }
    return resultado;
}

// Función para calcular la derivada de un polinomio usando el método de Horner
double evaluar_derivada(double coeficientes[], int grado, double x) {
    double resultado = coeficientes[0] * grado;  // Coeficiente multiplicado por el grado
    for (int i = 1; i < grado; i++) {
        resultado = resultado * x + coeficientes[i] * (grado - i);
    }
    return resultado;
}

// Método de Newton-Raphson para encontrar raíces
double newton_raphson(double coeficientes[], int grado, double x0, double tolerancia, int max_iter) {
    double x = x0;
    for (int i = 0; i < max_iter; i++) {
        double f_x = evaluar_polinomio(coeficientes, grado, x);
        double f_prime_x = evaluar_derivada(coeficientes, grado, x);

        if (fabs(f_prime_x) < 1e-10) {  // Evita división por cero
            printf("Derivada cercana a cero. No se puede continuar.\n");
            return NAN;  // Retorna NaN (Not a Number)
        }

        double x_nuevo = x - f_x / f_prime_x;  // Fórmula de Newton-Raphson

        if (fabs(x_nuevo - x) < tolerancia) {  // Verifica convergencia
            return x_nuevo;
        }
       
        x = x_nuevo;
    }

    printf("El metodo no converge despues de %d iteraciones.\n", max_iter);
    return NAN;
}

int main() {
    int grado;
    printf("Ingrese el grado del polinomio: ");
    scanf("%d", &grado);

    double coeficientes[grado + 1];  // Arreglo para almacenar los coeficientes
    printf("Ingrese los coeficientes del polinomio (de mayor a menor grado):\n");
    for (int i = 0; i <= grado; i++) {
        printf("Coeficiente de x^%d: ", grado - i);
        scanf("%lf", &coeficientes[i]);
    }

    // Parámetros para el método de Newton-Raphson
    double x0, tolerancia;
    int max_iter;

    printf("Ingrese el valor inicial (x0): ");
    scanf("%lf", &x0);

    printf("Ingrese la tolerancia (ej. 1e-6): ");
    scanf("%lf", &tolerancia);

    printf("Ingrese el numero maximo de iteraciones: ");
    scanf("%d", &max_iter);

    // Encuentra la raíz
    double raiz = newton_raphson(coeficientes, grado, x0, tolerancia, max_iter);

    if (!isnan(raiz)) {
        printf("Raiz encontrada: %.6f\n", raiz);
    } else {
        printf("No se encontro una raíz.\n");
    }

    // Pausa antes de cerrar el programa
    printf("Presione Enter para salir...");
    getchar();  // Captura el carácter de nueva línea pendiente
    getchar();  // Espera a que el usuario presione Enter

    return 0;
}