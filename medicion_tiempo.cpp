#include <chrono>
#include <iostream>

// Función que se desea medir
void miFuncion()
{
    for(int i=0; i<1000; i++) {
        std::cout << "Hola mundo." << std::endl;
    }
}

int main()
{
  // Inicio del cronómetro
  auto inicio = std::chrono::high_resolution_clock::now();

  // Llamada a la función que se desea medir
  miFuncion();

  // Fin del cronómetro
  auto fin = std::chrono::high_resolution_clock::now();

  // Cálculo del tiempo transcurrido en milisegundos
  auto duracion = std::chrono::duration_cast<std::chrono::milliseconds>(fin - inicio).count();

  // Impresión del tiempo transcurrido en milisegundos
  std::cout << "La funcion tardo " << duracion << " milisegundos en ejecutarse." << std::endl;

  return 0;
}