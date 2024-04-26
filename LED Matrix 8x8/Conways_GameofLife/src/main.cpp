#include <Arduino.h>

/* Pin definitions
LED Matrix 8x8 bicolor HL-M2388BRG: 
The row pins (top to bottom) are: [22, 23, 33, 32, 1, 3, 21, 19]. 
The column pins (from left to right (red; green)) are: [(27;27), (5;13), (14;12), (25;26), (0;4), (15,2), (17;16), (18;18). 
The 4 buttons are U:36, R:39, L:34, D:35.
*/

// Define the pins for the rows and columns
const int row_pins[] = {22, 23, 33, 32, 1, 3, 21, 19};
const int col_pins_red[] = {27, 5, 14, 25, 0, 15, 17, 18};
const int col_pins_green[] = {27, 13, 12, 26, 4, 2, 16, 18};

// Define the pins for the buttons
const int buttonRight = 39;
const int buttonLeft = 34;

// Simulation delay
const int delayTime = 500; // in milliseconds
unsigned long lastSimulation = 0;

const int debounceTime = 200; // in milliseconds
unsigned long lastDebounceTime = 0;

// Define state variables
enum GameState {
  IDLE,
  CHECKING,
  UPDATE_GRID,
  WAITING,
  PAUSE,
  RESET
};
GameState currentState = IDLE; // Set the initial state

// Define the map
int grid[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};
int auxGrid[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

#define SIZE 8

// Functions
bool startButton();
bool resetButton();
void updateLEDs();
bool checkStayAlive(int row, int col);
bool checkRevive(int row, int col);
int countLiveNeighbors(int row, int col);
bool allDead();

void setup() {
  // Initialize row pins
  for (int i = 0; i < 8; i++) {
    pinMode(row_pins[i], OUTPUT);
  }

  // Initialize column pins for red and green LEDs
  for (int i = 0; i < 8; i++) {
    pinMode(col_pins_red[i], OUTPUT);
    pinMode(col_pins_green[i], OUTPUT);
  }

  // Initialize button pins
  pinMode(buttonRight, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);

  // Initialize the random seed
  for(int row = 0; row < SIZE; row++)
    for(int col = 0; col < SIZE; col++)
      grid[row][col] = random(0, 2);
}

void loop() {
  switch (currentState) {
    case IDLE:
      if (startButton() && millis() - lastDebounceTime > debounceTime){
        currentState = WAITING;
        lastDebounceTime = millis();
      }
      break;
    case WAITING:
      if (millis() - lastSimulation > delayTime){
        lastSimulation = millis();
        currentState = CHECKING;
      }
      break;
    case CHECKING:
      for(int row = 0; row < SIZE; row++){
        for(int col = 0; col < SIZE; col++) {
          if(grid[row][col] == 1)
            auxGrid[row][col] = checkStayAlive(row, col);
          else
            auxGrid[row][col] = checkRevive(row, col);
        }
      }
      currentState = UPDATE_GRID;
      break;
    case UPDATE_GRID:
      for(int row = 0; row < SIZE; row++)
        for(int col = 0; col < SIZE; col++)
          grid[row][col] = auxGrid[row][col];
      currentState = WAITING;
      break;
    case PAUSE:
      if (startButton() && millis() - lastDebounceTime > debounceTime) {
        lastDebounceTime = millis();
        currentState = WAITING;
      }
        
      if (resetButton() && millis() - lastDebounceTime > debounceTime) {
        lastDebounceTime = millis();
        currentState = RESET;
      }
      break;
    case RESET:
      for(int row = 0; row < SIZE; row++){
        for(int col = 0; col < SIZE; col++) {
          grid[row][col] = random(0, 2);
          auxGrid[row][col] = 0;
        }
      }
      delay(1000);
      currentState = IDLE;
      break;
  }
  if (resetButton() && millis() - lastDebounceTime > debounceTime) {
    lastDebounceTime = millis();
    currentState = PAUSE;
  } else if (allDead()) {
    currentState = RESET;
  }
  updateLEDs();
}

bool startButton() {
  return !digitalRead(buttonRight);
}

bool resetButton() {
  return !digitalRead(buttonLeft);
}

void updateLEDs() {
  // Cycle LEDs: turn on rows for each column
  for (int col = 0; col < SIZE; col++) {
    digitalWrite(col_pins_red[col], HIGH);
    digitalWrite(col_pins_green[col], HIGH);
    for (int row = 0; row < SIZE; row++) {
      // If the current cell is a wall, turn on the red and green LEDs
      if (grid[row][col] == 1) {
        digitalWrite(row_pins[row], HIGH);
      } else {
        digitalWrite(row_pins[row], LOW);
      }
    }
    delay(2);
    for (int i = 0; i < SIZE; i++) digitalWrite(row_pins[i], LOW);
    digitalWrite(col_pins_red[col], LOW);
    digitalWrite(col_pins_green[col], LOW);
  }
}

bool checkStayAlive(int row, int col) {
  int liveNeighbors = countLiveNeighbors(row, col);
    return (liveNeighbors == 2 || liveNeighbors == 3);
}

bool checkRevive(int row, int col) {
  int liveNeighbors = countLiveNeighbors(row, col);
    return (liveNeighbors == 3);
}

int countLiveNeighbors(int row, int col) {
  int liveNeighbors = 0;
    for (int i = -1; i <= 1; i++) {
        for (int j = -1; j <= 1; j++) {
            if (i == 0 && j == 0) continue; // Skip the cell itself
            int newRow = row + i;
            int newCol = col + j;
            // Check the bounds of the grid
            if (newRow >= 0 && newRow < SIZE && newCol >= 0 && newCol < SIZE) {
                liveNeighbors += grid[newRow][newCol];
            }
        }
    }
    return liveNeighbors;
}

bool allDead() {
  for (int row = 0; row < SIZE; row++)
    for (int col = 0; col < SIZE; col++)
      if (grid[row][col] == 1)
        return false;
  return true;
}