#include <stdio.h>
#include <math.h>


double funcion(double x) {
    return exp(x*x*x*x); 
}

// Metodo del trapecio 
double trapecio(double a, double b, int n) {
    double h = (b - a) / n; 
    double suma = 0.0;

    // Sumar los valores de la funcion en los extremos y en los puntos intermedios
    suma += funcion(a) + funcion(b);  // Extremos
    for (int i = 1; i < n; i++) {
        suma += 2 * funcion(a + i * h);  // Puntos intermedios
    }

    // Multiplicar por h/2 para obtener el área total
    return (h / 2) * suma;
}

int main() {
    double a, b;
    int n;

    // Solicitar al usuario los límites de integración y el número de subintervalos
    printf("Ingrese (a): ");
    scanf("%lf", &a);

    printf("Ingrese (b): ");
    scanf("%lf", &b);

    printf("Ingrese el numero de subintervalos (n): ");
    scanf("%d", &n);

    if (n <= 0) {
        printf("Error: El numero de subintervalos debe ser positivo.\n");
        return 1;
    }

    // Calcular la integral usando el método del trapecio
    double resultado = trapecio(a, b, n);

    // Mostrar el resultado
    printf("El valor de la integral es: %.6f\n", resultado);

    // Pausa antes de cerrar el programa
    printf("\nPresione cualquier tecla para salir...");
    getchar();  // Captura el carácter de nueva línea pendiente
    getchar();  // Espera a que el usuario presione cualquier tecla

    return 0;
}