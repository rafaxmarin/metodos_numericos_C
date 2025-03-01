#include <stdio.h>
#include <math.h>

// Definimos la función que queremos integrar
double f(double x) {
    return sin(x); // Ejemplo: integral de sin(x)
}

// Función para calcular la integral usando el método del trapecio
double trapecio(double a, double b, int n) {
    double h = (b - a) / n; // Ancho de cada trapecio
    double suma = 0.5 * (f(a) + f(b)); // Suma de los extremos

    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        suma += f(x);
    }

    return suma * h;
}

int main() {
    double a, b;
    int n;

    // Solicitar los límites de integración y el número de trapecios
    printf("Introduce el límite inferior de integración (a): ");
    scanf("%lf", &a);
    printf("Introduce el límite superior de integración (b): ");
    scanf("%lf", &b);
    printf("Introduce el número de trapecios (n): ");
    scanf("%d", &n);

    // Calcular la integral usando el método del trapecio
    double resultado = trapecio(a, b, n);

    // Mostrar el resultado
    printf("El valor aproximado de la integral es: %.6lf\n", resultado);

    return 0;
}