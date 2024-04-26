#include <Arduino.h>

// Definir los números de pines para las filas y columnas
const int row_pins[8] = {22, 23, 33, 32, 1, 3, 21, 19};
const int col_pins_red[8] = {27, 5, 14, 25, 0, 15, 17, 18};
const int col_pins_green[8] = {27, 13, 12, 26, 4, 2, 16, 18};

// Inicializar los pines como salidas
void setup() {
  for (int i = 0; i < 8; i++) {
    pinMode(row_pins[i], OUTPUT);
    pinMode(col_pins_red[i], OUTPUT);
    pinMode(col_pins_green[i], OUTPUT);
  }
}

// Función para encender un LED individual
void turn_on_led(int row, int col, bool isRed) {
  // Apagar todas las filas y columnas
  for (int i = 0; i < 8; i++) {
    digitalWrite(row_pins[i], LOW);
    digitalWrite(col_pins_red[i], LOW);
    digitalWrite(col_pins_green[i], LOW);
  }
  
  // Encender la fila seleccionada
  digitalWrite(row_pins[row], HIGH);
  
  // Encender la columna seleccionada según el color
  if (isRed) {
    digitalWrite(col_pins_red[col], HIGH);
  } else {
    digitalWrite(col_pins_green[col], HIGH);
  }
}

// Función para probar la matriz de LEDs
void test_matrix() {
  // Recorrer cada fila y columna
  for (int row = 0; row < 8; row++) {
    for (int col = 0; col < 8; col++) {
      // Encender el LED rojo
      turn_on_led(row, col, true);
      delay(100);
      
      // Encender el LED verde
      turn_on_led(row, col, false);
      delay(100);
    }
  }
}

void loop() {
  // Llamar a la función test_matrix
  test_matrix();
}