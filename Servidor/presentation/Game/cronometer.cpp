#include <iostream>
#include <chrono>
#include <thread>

using namespace std;
using namespace std::chrono;

time_point<high_resolution_clock> iniciarCronometro() {
    auto inicio = high_resolution_clock::now();
    return inicio;
}

void detenerCronometro(time_point<high_resolution_clock> inicio) {
    auto fin = high_resolution_clock::now();
    duration<double> duracion = fin - inicio;
    cout << "Tiempo transcurrido: " << duracion.count() << " segundos" << endl;
}

int main() {
    char input;
    
    cout << "Presiona 's' para iniciar el cronómetro: ";
    cin >> input;

    if (input == 's') {
        auto inicio = iniciarCronometro();  // Recibe el tiempo de inicio
        
        cout << "Presiona 'e' para detener el cronómetro: ";
        cin >> input;

        if (input == 'e') {
            detenerCronometro(inicio);  // Pasa el tiempo de inicio para calcular el tiempo
        }
    }

    return 0;
}
