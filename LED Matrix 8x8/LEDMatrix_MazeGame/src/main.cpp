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
const int buttonUp = 36;
const int buttonRight = 39;
const int buttonLeft = 34;
const int buttonDown = 35;

// Variables to store the player's and ball's positions
int playerPositionX; 
int playerPositionY;
int ballPositionX;
int ballPositionY;

// Define state variables
enum GameState {
  IDLE,
  MOVING_PLAYER,
  CHECKING_FOR_WIN,
  TIMEOUT
};
GameState currentState = IDLE; // Set the initial state

// Debounce variables (ms)
unsigned long lastButtonPressTime = 0;
const unsigned long debounceDelay = 20;  // Delay to delete bounce

const unsigned long moveDelay = 100;     // Delay between moves
unsigned long lastMoveTime = 0;

// Point system
unsigned long startTime = 0;
const unsigned long timeoutDuration = 6000; // 60 seconds timeout

int greenDotCount = -1;

// Array to save the maze layout
bool maze[8][8] = {
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0},
  {0, 0, 0, 0, 0, 0, 0, 0}
};

// Functions
bool buttonPressed();
void flashLEDsAndWaitForStart();
void updateLEDs();
void initializeMaze();
void randomizeMaze();
void movePlayer();
void checkForWin();
void gameEnd();

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
  pinMode(buttonUp, INPUT_PULLUP);  
  pinMode(buttonRight, INPUT_PULLUP);
  pinMode(buttonLeft, INPUT_PULLUP);
  pinMode(buttonDown, INPUT_PULLUP);

  // Flash LEDs and wait for the start button
  flashLEDsAndWaitForStart();

  // Initialize the maze
  initializeMaze();
}

void loop() {
  switch(currentState) {
    case IDLE:
      if(buttonPressed() && millis() -  lastButtonPressTime > debounceDelay) {
        lastButtonPressTime = millis();
        currentState = MOVING_PLAYER;
        lastMoveTime = millis(); // Reset the move timer
        startTime = millis(); // Reset the start time
      }
      if(millis() - startTime >= timeoutDuration)
        currentState = TIMEOUT;
      break;
    case MOVING_PLAYER:
      if(millis() - lastMoveTime >= moveDelay) {
        movePlayer();
        currentState = CHECKING_FOR_WIN;
      }
      break;
    case CHECKING_FOR_WIN:
      checkForWin();
      currentState = IDLE;
      // Check if the player has won the game
      if (greenDotCount == 8)
        currentState = TIMEOUT;
      break;
    case TIMEOUT:
      gameEnd();
  }
  updateLEDs();
}

bool buttonPressed() {
  if (digitalRead(buttonUp) == LOW || digitalRead(buttonRight) == LOW || digitalRead(buttonLeft) == LOW || digitalRead(buttonDown) == LOW)
    return true;
  return false;
}

void flashLEDsAndWaitForStart() {
  int col = 0;
  for(int i = 0; i < 8; i++) {
    digitalWrite(row_pins[i], HIGH);
  }
  while (!buttonPressed()) {
    switch(col) {
      case 0:
        digitalWrite(col_pins_red[0], HIGH);
        delay(100);
        digitalWrite(col_pins_red[0], LOW);
        col++;
        break;
      case 1:
        digitalWrite(col_pins_red[1], HIGH);
        delay(100);
        digitalWrite(col_pins_red[1], LOW);
        col++;
        break;
      case 2:
        digitalWrite(col_pins_red[2], HIGH);
        delay(100);
        digitalWrite(col_pins_red[2], LOW);
        col++;
        break;
      case 3:
        digitalWrite(col_pins_red[3], HIGH);
        delay(100);
        digitalWrite(col_pins_red[3], LOW);
        col++;
        break;
      case 4:
        digitalWrite(col_pins_red[4], HIGH);
        delay(100);
        digitalWrite(col_pins_red[4], LOW);
        col++;
        break;
      case 5:
        digitalWrite(col_pins_red[5], HIGH);
        delay(100);
        digitalWrite(col_pins_red[5], LOW);
        col++;
        break;
      case 6:
        digitalWrite(col_pins_red[6], HIGH);
        delay(100);
        digitalWrite(col_pins_red[6], LOW);
        col++;
        break;
      case 7:
        digitalWrite(col_pins_red[7], HIGH);
        delay(100);
        digitalWrite(col_pins_red[7], LOW);
        col = 0;
        break;
    }
  }

  // Turn off all LEDs before starting the game
  for(int i = 0; i < 8; i++) {
    digitalWrite(row_pins[i], LOW);
    digitalWrite(col_pins_red[i], LOW); 
    digitalWrite(col_pins_green[i], LOW); 
  }
}

void updateLEDs() {
  // Cycle red LEDs through the rows
  for (int col = 0; col < 8; col++) {
    digitalWrite(col_pins_red[col], HIGH); 
    for (int row = 0; row < 8; row++) {
      // If the current cell is a wall, turn on the red and green LEDs
      if (maze[row][col] == 1) {
        digitalWrite(row_pins[row], HIGH);
      } else if (row == playerPositionY && col == playerPositionX) {
          digitalWrite(row_pins[row], HIGH);
      } else {
        digitalWrite(row_pins[row], LOW);
      }
    }
    delay(0.5);
    for (int i = 0; i < 8; i++) digitalWrite(row_pins[i], LOW);
    digitalWrite(col_pins_red[col], LOW);
  }

  // Cycle green LEDs through the rows
  for (int col = 0; col < 8; col++) {
    digitalWrite(col_pins_green[col], HIGH); 
    for (int row = 0; row < 8; row++) {
      // If the current cell is a wall, turn on the red and green LEDs
      if (maze[row][col] == 1) {
        digitalWrite(row_pins[row], HIGH);
      } else if (row == ballPositionY && col == ballPositionX) {
          digitalWrite(row_pins[row], HIGH);
      } else {
        digitalWrite(row_pins[row], LOW);
      }
    }
    delay(0.5);
    for (int i = 0; i < 8; i++) digitalWrite(row_pins[i], LOW);
    digitalWrite(col_pins_green[col], LOW);
  }
}

void initializeMaze() {
  // Initialize the player and ball positions
  playerPositionX = random(1, 7);
  playerPositionY = random(1, 7);
  ballPositionX = random(1, 7);
  ballPositionY = random(1, 7);

  // If the player and ball are in the same position, move the ball
  while(playerPositionX == ballPositionX && playerPositionY == ballPositionY) {
    ballPositionX = (ballPositionX + 1) % 8;
    ballPositionY = (ballPositionY + 1) % 8;
  }

  // Initialize the maze
  for(int row = 0; row < 8; row++)
    for(int col = 0; col < 8; col++)
        if(row == 0 || row == 7 || col == 0 || col == 7)
          maze[row][col] = 1;
        else
          maze[row][col] = 0;
}

void movePlayer() {
  // Move up
  if (digitalRead(buttonUp) == LOW && (maze[playerPositionY - 1][playerPositionX] == 0 || (playerPositionY - 1 == -1 && maze[7][playerPositionX] == 0))) {
    playerPositionY--;
    if (playerPositionY < 0) playerPositionY = 7;
  }
  // Move right
  if (digitalRead(buttonRight) == LOW && (maze[playerPositionY][playerPositionX + 1] == 0 || (playerPositionX + 1 == 8 && maze[playerPositionY][0] == 0))) {
    playerPositionX++;
    if (playerPositionX > 7) playerPositionX = 0;
  }
  // Move left
  if (digitalRead(buttonLeft) == LOW && (maze[playerPositionY][playerPositionX - 1] == 0 || (playerPositionX - 1 == -1 && maze[playerPositionY][7] == 0))) {
    playerPositionX--;
    if (playerPositionX < 0) playerPositionX = 7;
  }
  // Move down
  if (digitalRead(buttonDown) == LOW && (maze[playerPositionY + 1][playerPositionX] == 0 || (playerPositionY + 1 == 8 && maze[0][playerPositionX] == 0))) {
    playerPositionY++;
    if (playerPositionY > 7) playerPositionY = 0;
  }
}

void checkForWin() {
  // Update the maze and check for collision with the ball
  if (playerPositionX == ballPositionX && playerPositionY == ballPositionY) {
    greenDotCount++;
    
    // Change maze layout 
    randomizeMaze();
    // Move player if they are inside a wall
    while (maze[playerPositionY][playerPositionX] == 1) {
      playerPositionX = random(1, 7);
      playerPositionY = random(1, 7);
    }
    // Move the ball to a new position
    ballPositionX = random(1, 7);
    ballPositionY = random(1, 7);
    // Move the ball if it is in the same position as the player or if its in a wall
    while (playerPositionX == ballPositionX && playerPositionY == ballPositionY || maze[ballPositionY][ballPositionX] == 1) {
      ballPositionX = random(1, 7);
      ballPositionY = random(1, 7);
    }
  }
}

void randomizeMaze() {
  // Pick a random maze layout
  int randomValue = random(0, 4);
  switch(randomValue) {
    case 0: {
      bool nextMaze[8][8] = {
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {1, 0, 1, 0, 1, 0, 1, 0},
        {0, 1, 0, 0, 0, 1, 0, 1},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 0, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 1, 0, 0, 0}
      };
      for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
          maze[i][j] = nextMaze[i][j];
        }
      }
      
    } break;
    case 1: {
      bool nextMaze[8][8] = {
        {1, 1, 0, 1, 0, 1, 1, 1},
        {0, 0, 1, 0, 0, 0, 0, 1},
        {1, 0, 1, 1, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 1, 0},
        {1, 1, 1, 0, 1, 0, 1, 1},
        {0, 0, 0, 0, 1, 0, 0, 0},
        {1, 0, 1, 1, 1, 1, 0, 1},
        {1, 0, 0, 1, 0, 0, 0, 1}
      };
      for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          maze[i][j] = nextMaze[i][j];
        }
      }
    } break;
    case 2: {
      bool nextMaze[8][8] = {
        {0, 0, 0, 0, 1, 0, 0, 0},
        {0, 1, 0, 0, 1, 1, 1, 0},
        {0, 1, 0, 0, 0, 0, 0, 0},
        {0, 1, 0, 1, 0, 0, 0, 0},
        {0, 0, 0, 0, 0, 0, 0, 0},
        {0, 1, 1, 1, 0, 0, 1, 0},
        {0, 1, 0, 0, 0, 0, 1, 0},
        {0, 0, 0, 0, 0, 1, 0, 0}
      };
      for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          maze[i][j] = nextMaze[i][j];
        }
      }
    } break;
    case 3: {
      bool nextMaze[8][8] = {
        {0, 0, 1, 0, 0, 1, 1, 0},
        {1, 0, 1, 1, 0, 0, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 1, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 0, 1, 0, 1},
        {1, 0, 0, 0, 0, 1, 0, 1},
        {1, 0, 1, 1, 0, 0, 0, 0},
        {1, 1, 1, 1, 1, 0, 1, 1}
      };
      for(int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
          maze[i][j] = nextMaze[i][j];
        }
      }
    } break;
    default: 
      for(int i = 0; i < 8; i++) {
        for(int j = 0; j < 8; j++) {
          maze[i][j] = 0;
        }
      }
      break;
  }
}

void gameEnd() {
  int score = greenDotCount;
  
  // Reset maze
  for(int i = 0; i < 8; i++) {
    for(int j = 0; j < 8; j++) {
      maze[i][j] = 0;
    }
  }
  // Reset player and ball positions
  playerPositionX = -1;
  playerPositionY = -1;
  ballPositionX = -1;
  ballPositionY = -1;

  // Turn off all LEDs first to reset the display
  for (int i = 0; i < 8; i++) {
    digitalWrite(row_pins[i], LOW);
    digitalWrite(col_pins_red[i], LOW); 
    digitalWrite(col_pins_green[i], LOW); 
  }
  // Display the score
  // Cycle green LEDs through the rows
  for (int col = 0; col < 8; col++) {
    digitalWrite(col_pins_green[col], HIGH); 
    for (int row = 0; row < score; row++)
        digitalWrite(row_pins[row], HIGH);
    delay(1);
    for (int i = 0; i < 8; i++) digitalWrite(row_pins[i], LOW);
    digitalWrite(col_pins_green[col], LOW);
  }

  // Wait for the start button to be pressed
  if(buttonPressed() && millis() - lastButtonPressTime > 2000)   {
    // Reset variables  
    lastButtonPressTime = millis();
    lastMoveTime = millis();
    startTime = millis();
    greenDotCount = -1;
    currentState = IDLE;
    delay(debounceDelay);
    flashLEDsAndWaitForStart();
    initializeMaze();
  }
}