#include <stdio.h>
#include <math.h>

// Función a integrar (puedes cambiarla según tus necesidades)
double funcion(double x) {
    return sin(x);  // Ejemplo: integral de sin(x)
}

// Método de Simpson 1/3 para integrar numéricamente
double simpson_1_3(double a, double b, int n) {
    if (n % 2 != 0) {
        printf("Error: El número de subintervalos (n) debe ser par.\n");
        return 0.0;
    }

    double h = (b - a) / n;  // Ancho de cada subintervalo
    double suma = 0.0;

    // Sumar los valores de la función en los extremos
    suma += funcion(a) + funcion(b);

    // Sumar los valores de la función en los puntos intermedios
    for (int i = 1; i < n; i++) {
        double x = a + i * h;
        if (i % 2 == 0) {
            suma += 2 * funcion(x);  // Coeficiente 2 para índices pares
        } else {
            suma += 4 * funcion(x);  // Coeficiente 4 para índices impares
        }
    }

    // Multiplicar por h/3 para obtener el área total
    return (h / 3) * suma;
}

int main() {
    // Definir los límites de integración y el número de subintervalos directamente en el código
    double a = 0.0;       // Límite inferior de integración
    double b = M_PI;      // Límite superior de integración (π)
    int n = 1000;         // Número de subintervalos (debe ser par)

    // Verificar si el número de subintervalos es válido
    if (n <= 0 || n % 2 != 0) {
        printf("Error: El número de subintervalos debe ser positivo y par.\n");
        return 1;
    }

    // Calcular la integral usando el método de Simpson 1/3
    double resultado = simpson_1_3(a, b, n);

    // Mostrar los datos de entrada y el resultado
    printf("Limite inferior de integracion (a): %.6f\n", a);
    printf("Limite superior de integracion (b): π (%.6f)\n", b);
    printf("Número de subintervalos (n): %d\n", n);
    printf("El valor de la integral es: %.6f\n", resultado);

    // Pausa antes de cerrar el programa
    printf("\nPresione cualquier tecla para salir...");
    getchar();  // Captura el carácter de nueva línea pendiente
    getchar();  // Espera a que el usuario presione cualquier tecla

    return 0;
}