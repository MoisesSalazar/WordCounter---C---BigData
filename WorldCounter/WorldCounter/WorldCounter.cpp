#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <set>
#include <chrono>
#include <cctype>

void contar_palabras(const std::string& archivo_entrada, const std::string& archivo_salida) {
    // Abrir el archivo
    std::ifstream archivo(archivo_entrada);
    if (!archivo) {
        std::cerr << "Error al abrir el archivo" << std::endl;
        return;
    }

    // Crear un unordered_map para contar las palabras
    std::unordered_map<std::string, int> contador;
    contador.reserve(100000); // Reservar espacio para 100,000 palabras (ajustar según la cantidad esperada)

    // Medir el tiempo de procesamiento
    auto inicio = std::chrono::steady_clock::now();
    int total_scores = 0;

    std::string linea;
    while (std::getline(archivo, linea)) { // Leer cada línea del archivo
        std::string palabra;
        for (char c : linea) { // Recorrer cada caracter de la línea
            if (std::isalnum(c)) { // Si el caracter es alfanumérico, agregarlo a la palabra actual
                palabra.push_back(std::tolower(c));
            }
            else if (!palabra.empty()) { // Si el caracter no es alfanumérico y hay una palabra actual, incrementar el contador
                contador[palabra]++;
                total_scores++;
                palabra.clear(); // Limpiar la palabra actual
            }
        }
        if (!palabra.empty()) { // Si hay una palabra actual al final de la línea, incrementar el contador
            contador[palabra]++;
            total_scores++;
        }
    }

    // Calcular el tiempo de procesamiento
    auto fin = std::chrono::steady_clock::now();
    auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio);

    // Imprimir el resultado en la consola
    std::cout << "Tiempo de procesamiento: " << duracion.count() << " ms" << std::endl;
    std::cout << "Número de palabras diferentes: " << contador.size() << std::endl;
    std::cout << "Suma de los scores de todas las palabras: " << total_scores << std::endl;

    // Guardar el resultado en un archivo de texto
    std::ofstream resultado(archivo_salida);
    for (const auto& par : contador) {
        resultado << par.first << " " << par.second << std::endl;
    }
    resultado.close();
}


int main() {
    
    contar_palabras("C:/Users/Moises/Documents/Universidad/BigData/WorldCounter/loremmoises.txt", "resultado.txt");
    
    return 0;
}