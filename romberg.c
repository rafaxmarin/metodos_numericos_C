#include <stdio.h>
#include <math.h>

// Definir la función a integrar
double f(double x) {
    return x * x * exp(-x); // Ejemplo: f(x) = x^2 * e^(-x)
}

// Método de Romberg
double romberg(double a, double b, int n) {
    double R[n][n]; // Matriz para almacenar los resultados
    double h = b - a; // Tamaño del intervalo inicial

    // Primera iteración (regla del trapecio simple)
    R[0][0] = 0.5 * h * (f(a) + f(b));

    // Iteraciones para llenar la primera columna
    for (int i = 1; i < n; i++) {
        h /= 2; // Reducir el tamaño del intervalo a la mitad
        double sum = 0;

        // Calcular la suma de los puntos intermedios
        for (int k = 1; k <= pow(2, i) - 1; k += 2) {
            sum += f(a + k * h);
        }

        // Aplicar la regla del trapecio compuesta
        R[i][0] = 0.5 * R[i - 1][0] + h * sum;
    }

    // Extrapolación de Richardson para llenar el resto de la tabla
    for (int j = 1; j < n; j++) {
        for (int i = j; i < n; i++) {
            R[i][j] = R[i][j - 1] + (R[i][j - 1] - R[i - 1][j - 1]) / (pow(4, j) - 1);
        }
    }

    // Mostrar la tabla de Romberg
    printf("Tabla de Romberg:\n");
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= i; j++) {
            printf("%.6f\t", R[i][j]);
        }
        printf("\n");
    }

    // Devolver el resultado final
    return R[n - 1][n - 1];
}

int main() {
    double a = 0; // Límite inferior
    double b = 1; // Límite superior
    int n = 4;    // Número de iteraciones

    double resultado = romberg(a, b, n);
    printf("\nResultado final: %.6f\n", resultado);

    return 0;
}