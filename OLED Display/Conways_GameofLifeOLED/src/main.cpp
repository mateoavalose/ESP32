#include <Arduino.h>
#include <Wire.h>
#include <U8g2lib.h>

// Grid definition
#define ROWS 64
#define COLUMNS 128
// Map definition
int grid[64][128];
int auxGrid[64][128];

// I2C - OLED Display
U8G2_SH1106_128X64_NONAME_F_HW_I2C display(U8G2_R0, /* reset=*/ U8X8_PIN_NONE);

// Simulation delay
const int delayStartTime = 5000; // in milliseconds
const int delayTime = 100; // in milliseconds
unsigned long lastSimulation = 0;

// Define state variables
enum GameState {
  IDLE,
  CHECKING,
  UPDATE_GRID,
  WAITING,
  PAUSE, // not used
  RESET
};
GameState currentState = IDLE; // Set the initial state

// Functions
void updateOLED();
bool checkStayAlive(int row, int col);
bool checkRevive(int row, int col);
int countLiveNeighbors(int row, int col);
bool allDead();

void setup() {
  // Initialize the display
  Wire.begin();
  display.begin();
  display.setContrast(255);

  // Initialize the random seed
  for(int row = 0; row < ROWS; row++)
    for(int col = 0; col < COLUMNS; col++)
      grid[row][col] = random(0, 2);
}

void loop() {
  switch (currentState) {
    case IDLE:
        if(millis() - lastSimulation > delayStartTime) {
          lastSimulation = millis();
          currentState = WAITING;
        }
      break;
    case WAITING:
      if (millis() - lastSimulation > delayTime){
        lastSimulation = millis();
        currentState = CHECKING;
      }
      break;
    case CHECKING:
      for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLUMNS; col++) {
          if(grid[row][col] == 1)
            auxGrid[row][col] = checkStayAlive(row, col);
          else
            auxGrid[row][col] = checkRevive(row, col);
        }
      }
      currentState = UPDATE_GRID;
      break;
    case UPDATE_GRID:
      for(int row = 0; row < ROWS; row++)
        for(int col = 0; col < COLUMNS; col++)
          grid[row][col] = auxGrid[row][col];
      currentState = WAITING;
      break;
    case RESET:
      for(int row = 0; row < ROWS; row++){
        for(int col = 0; col < COLUMNS; col++) {
          grid[row][col] = random(0, 2);
          auxGrid[row][col] = 0;
        }
      }
      delay(1000);
      currentState = IDLE;
      break;
  }
  if (allDead()) {
    currentState = RESET;
  }
  updateOLED();
}

void updateOLED() {
  display.clearBuffer();
  // Cycle LEDs: turn on rows for each column
  for (int col = 0; col < COLUMNS; col++) {
    for (int row = 0; row < ROWS; row++) {
      // If the current cell is a wall, turn on the red and green LEDs
      if (grid[row][col] == 1) {
        display.drawPixel(col, row);
      }
    }
  }
  display.sendBuffer();
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
            if (newRow >= 0 && newRow < ROWS && newCol >= 0 && newCol < COLUMNS) {
                liveNeighbors += grid[newRow][newCol];
            }
        }
    }
    return liveNeighbors;
}

bool allDead() {
  for (int row = 0; row < ROWS; row++)
    for (int col = 0; col < COLUMNS; col++)
      if (grid[row][col] == 1)
        return false;
  return true;
}