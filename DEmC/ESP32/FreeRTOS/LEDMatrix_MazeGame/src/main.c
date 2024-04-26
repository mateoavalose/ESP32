#include <stddef.h>
#include "driver/gpio.h"
#include "freertos/FreeRTOS.h"
#include "freertos/task.h"
#include <stdlib.h>
#include "esp_timer.h" // Blinking every 5 seconds. May be a variable overflow

/* Pin definitions
LED Matrix 8x8 bicolor HL-M2388BRG: 
The row pins (top to bottom) are: [22, 23, 33, 32, 1, 3, 21, 19]. 
The column pins (from left to right (red; green)) are: [(27;27), (5;13), (14;12), (25;26), (0;4), (15,2), (17;16), (18;18). 
The 4 buttons are U:36, R:39, L:34, D:35.
*/

// Define the pin assignments for the LED matrix
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
enum GameState currentState = IDLE; // Set the initial state

// Debounce variables (ms)
unsigned long lastButtonPressTime = 0;
const unsigned long debounceDelay = 20;  // Delay to delete bounce

const unsigned long moveDelay = 100;     // Delay between moves
unsigned long lastMoveTime = 0;

// Point system
unsigned long startTime = 0;
const unsigned long timeoutDuration = 6000; // 6 seconds timeout

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

// Pin initialization for the LED Matrix
#define GPIO_row0 row_pins[0]
#define GPIO_row0_PIN_SEL (1ULL << GPIO_row0)
#define GPIO_row1 row_pins[1]
#define GPIO_row1_PIN_SEL (1ULL << GPIO_row1)
#define GPIO_row2 row_pins[2]
#define GPIO_row2_PIN_SEL (1ULL << GPIO_row2)
#define GPIO_row3 row_pins[3]
#define GPIO_row3_PIN_SEL (1ULL << GPIO_row3)
#define GPIO_row4 row_pins[4]
#define GPIO_row4_PIN_SEL (1ULL << GPIO_row4)
#define GPIO_row5 row_pins[5]
#define GPIO_row5_PIN_SEL (1ULL << GPIO_row5)
#define GPIO_row6 row_pins[6]
#define GPIO_row6_PIN_SEL (1ULL << GPIO_row6)
#define GPIO_row7 row_pins[7]
#define GPIO_row7_PIN_SEL (1ULL << GPIO_row7)

#define GPIO_colR0 col_pins_red[0]
#define GPIO_colR0_PIN_SEL (1ULL << GPIO_colR0)
#define GPIO_colR1 col_pins_red[1]
#define GPIO_colR1_PIN_SEL (1ULL << GPIO_colR1)
#define GPIO_colR2 col_pins_red[2]
#define GPIO_colR2_PIN_SEL (1ULL << GPIO_colR2)
#define GPIO_colR3 col_pins_red[3]
#define GPIO_colR3_PIN_SEL (1ULL << GPIO_colR3)
#define GPIO_colR4 col_pins_red[4]
#define GPIO_colR4_PIN_SEL (1ULL << GPIO_colR4)
#define GPIO_colR5 col_pins_red[5]
#define GPIO_colR5_PIN_SEL (1ULL << GPIO_colR5)
#define GPIO_colR6 col_pins_red[6]
#define GPIO_colR6_PIN_SEL (1ULL << GPIO_colR6)
#define GPIO_colR7 col_pins_red[7]
#define GPIO_colR7_PIN_SEL (1ULL << GPIO_colR7)

#define GPIO_colG0 col_pins_green[0]
#define GPIO_colG0_PIN_SEL (1ULL << GPIO_colG0)
#define GPIO_colG1 col_pins_green[1]
#define GPIO_colG1_PIN_SEL (1ULL << GPIO_colG1)
#define GPIO_colG2 col_pins_green[2]
#define GPIO_colG2_PIN_SEL (1ULL << GPIO_colG2)
#define GPIO_colG3 col_pins_green[3]
#define GPIO_colG3_PIN_SEL (1ULL << GPIO_colG3)
#define GPIO_colG4 col_pins_green[4]
#define GPIO_colG4_PIN_SEL (1ULL << GPIO_colG4)
#define GPIO_colG5 col_pins_green[5]
#define GPIO_colG5_PIN_SEL (1ULL << GPIO_colG5)
#define GPIO_colG6 col_pins_green[6]
#define GPIO_colG6_PIN_SEL (1ULL << GPIO_colG6)
#define GPIO_colG7 col_pins_green[7]
#define GPIO_colG7_PIN_SEL (1ULL << GPIO_colG7)

// Pin initialization for the buttons
#define GPIO_BUTU buttonUp
#define GPIO_BUTU_PIN_SEL (1ULL << GPIO_BUTU)
#define ESP_INTR_FLAG_DEFAULT 0
#define GPIO_BUTR buttonRight
#define GPIO_BUTR_PIN_SEL (1ULL << GPIO_BUTR)
#define ESP_INTR_FLAG_DEFAULT 0
#define GPIO_BUTL buttonLeft
#define GPIO_BUTL_PIN_SEL (1ULL << GPIO_BUTL)
#define ESP_INTR_FLAG_DEFAULT 0
#define GPIO_BUTD buttonDown
#define GPIO_BUTD_PIN_SEL (1ULL << GPIO_BUTD)
#define ESP_INTR_FLAG_DEFAULT 0

// Functions
unsigned long millis();
bool buttonPressed();
void flashLEDsAndWaitForStart();
void updateLEDs();
void initializeMaze();
void randomizeMaze();
void movePlayer();
void checkForWin();
void gameEnd();

void init_hw(void){
    // Pin configuration
    gpio_config_t io_conf;
    // Rows
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_row0_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_row1_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_row2_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_row3_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_row4_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_row5_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_row6_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_row7_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // Red Columns
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colR0_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colR1_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colR2_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colR3_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colR4_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colR5_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colR6_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colR7_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    // Green Columns
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colG0_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colG1_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colG2_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colG3_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colG4_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colG5_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colG6_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_OUTPUT;
    io_conf.pin_bit_mask = GPIO_colG7_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_down_en = 0;
    io_conf.pull_up_en = 0;
    gpio_config(&io_conf);

    // Button configuration
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BUTU_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BUTR_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BUTL_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
    io_conf.mode = GPIO_MODE_INPUT;
    io_conf.pin_bit_mask = GPIO_BUTD_PIN_SEL;
    io_conf.intr_type = GPIO_INTR_DISABLE;
    io_conf.pull_up_en = 1;
    gpio_config(&io_conf);
}

void init_sw(void) {
  flashLEDsAndWaitForStart(); // Flash LEDs and wait for the start button
  srand(millis()); // Seed the random number generator: random: min + rand() % (max + 1 - min);
  initializeMaze(); // Initialize the maze
}

void app_main(void) {
  init_hw();
  init_sw();
  while(1) {
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
}

unsigned long millis() {
  return (unsigned long) esp_timer_get_time() / 1000; // Time in ms since boot
}

bool buttonPressed() {
  return !gpio_get_level(GPIO_BUTU) || !gpio_get_level(GPIO_BUTR) || !gpio_get_level(GPIO_BUTL) || !gpio_get_level(GPIO_BUTD);
}

void flashLEDsAndWaitForStart() {
  int col = 0;
  // Turn on all rows
  for(int i = 0; i < 8; i++) {
    gpio_set_level(row_pins[i], 1);
  }
  // LED sequence while waiting
  while(!buttonPressed()) {
    switch(col){
      case 0:
        gpio_set_level(col_pins_red[0], 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(col_pins_red[0], 0);
        col++;
        break;
      case 1:
        gpio_set_level(col_pins_red[1], 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(col_pins_red[1], 0);
        col++;
        break;
      case 2:
        gpio_set_level(col_pins_red[2], 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(col_pins_red[2], 0);
        col++;
        break;
      case 3:
        gpio_set_level(col_pins_red[3], 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(col_pins_red[3], 0);
        col++;
        break;
      case 4:
        gpio_set_level(col_pins_red[4], 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(col_pins_red[4], 0);
        col++;
        break;
      case 5:
        gpio_set_level(col_pins_red[5], 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(col_pins_red[5], 0);
        col++;
        break;
      case 6:
        gpio_set_level(col_pins_red[6], 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(col_pins_red[6], 0);
        col++;
        break;
      case 7:
        gpio_set_level(col_pins_red[7], 1);
        vTaskDelay(100 / portTICK_PERIOD_MS);
        gpio_set_level(col_pins_red[7], 0);
        col = 0;
        break;
    }
  }
  // Turn off all LEDs before starting the game
  for(int i = 0; i < 8; i++) {
    gpio_set_level(row_pins[i], 0);
    gpio_set_level(col_pins_red[i], 0);
    gpio_set_level(col_pins_green[i], 0);
  }
}

void updateLEDs() {
  // Cycle red LEDs
  for(int col = 0; col < 8; col++) {
    gpio_set_level(col_pins_red[col], 1);
    for(int row = 0; row < 8; row++) {
      if(maze[row][col] == 1) {
        gpio_set_level(row_pins[row], 1);
      } else if(playerPositionX == col && playerPositionY == row) {
        gpio_set_level(row_pins[row], 1);
      } else {
        gpio_set_level(row_pins[row], 0);
      }
    }
    vTaskDelay(1 / portTICK_PERIOD_MS);
    for(int i = 0; i < 8; i++) gpio_set_level(row_pins[i], 0);
    gpio_set_level(col_pins_red[col], 0);
  }
  // Cycle green LEDs
  for(int col = 0; col < 8; col++) {
    gpio_set_level(col_pins_green[col], 1);
    for(int row = 0; row < 8; row++) {
      if(maze[row][col] == 1) {
        gpio_set_level(row_pins[row], 1);
      } else if(ballPositionX == col && ballPositionY == row) {
        gpio_set_level(row_pins[row], 1);
      } else {
        gpio_set_level(row_pins[row], 0);
      }
    }
    vTaskDelay(1 / portTICK_PERIOD_MS);
    for(int i = 0; i < 8; i++) gpio_set_level(row_pins[i], 0);
    gpio_set_level(col_pins_green[col], 0);
  }
}

void initializeMaze() {
  // Set the player and ball positions randomly
  playerPositionX = 1 + rand() % (6 + 1 - 1);
  playerPositionY = 1 + rand() % (6 + 1 - 1);
  ballPositionX = 1 + rand() % (6 + 1 - 1);
  ballPositionY = 1 + rand() % (6 + 1 - 1);
  // Change the ball if its in the same position as the player
  while(playerPositionX == ballPositionX && playerPositionY == ballPositionY) {
    ballPositionX = 1 + rand() % (6 + 1 - 1);
    ballPositionY = 1 + rand() % (6 + 1 - 1);
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
  if(!gpio_get_level(GPIO_BUTU) && (maze[playerPositionY - 1][playerPositionX] == 0 || (playerPositionY - 1 == -1 && maze[7][playerPositionX] == 0))) {
    playerPositionY--;
    if(playerPositionY < 0) playerPositionY = 7;
  }
  // Move right
  if(!gpio_get_level(GPIO_BUTR) && (maze[playerPositionY][playerPositionX + 1] == 0 || (playerPositionX + 1 == 8 && maze[playerPositionY][0] == 0))) {
    playerPositionX++;
    if(playerPositionX > 7) playerPositionX = 0;
  }
  // Move left
  if(!gpio_get_level(GPIO_BUTL) && (maze[playerPositionY][playerPositionX - 1] == 0 || (playerPositionX - 1 == -1 && maze[playerPositionY][7] == 0))) {
    playerPositionX--;
    if(playerPositionX < 0) playerPositionX = 7;
  }
  // Move down
  if(!gpio_get_level(GPIO_BUTD) && (maze[playerPositionY + 1][playerPositionX] == 0 || (playerPositionY + 1 == 8 && maze[0][playerPositionX] == 0))) {
    playerPositionY++;
    if(playerPositionY > 7) playerPositionY = 0;
  }
}

void checkForWin() {
  // Update the maze and check for collision with the ball
  if(playerPositionX == ballPositionX && playerPositionY == ballPositionY) {
    greenDotCount++; // Increase score
    randomizeMaze(); // Change maze layout
    // Move the player if inside a wall
    while(maze[playerPositionY][playerPositionX] == 1) {
      playerPositionX = 1 + rand() % (6 + 1 - 1);
      playerPositionY = 1 + rand() % (6 + 1 - 1);
    }
    // Move the ball to a new position
    ballPositionX = 1 + rand() % (6 + 1 - 1);
    ballPositionY = 1 + rand() % (6 + 1 - 1);
    // Move the ball if its in the same position as the player or if its inside a wall
    while((playerPositionX == ballPositionX && playerPositionY == ballPositionY) || maze[ballPositionY][ballPositionX] == 1) {
      ballPositionX = 1 + rand() % (6 + 1 - 1);
      ballPositionY = 1 + rand() % (6 + 1 - 1);
    }
  }
}

void randomizeMaze() {
  int randomValue = 0 + rand() % (3 + 1 - 0); // Pick a random world
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
      for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
          maze[i][j] = nextMaze[i][j];
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
      for(int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
          maze[i][j] = nextMaze[i][j];
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
      for(int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
          maze[i][j] = nextMaze[i][j];
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
      for(int i = 0; i < 8; i++)
        for (int j = 0; j < 8; j++)
          maze[i][j] = nextMaze[i][j];
    } break;
    default: 
      for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
          maze[i][j] = 0;
      break;
  }
}

void gameEnd() {
  int score = greenDotCount;
  // Reset maze
  for(int i = 0; i < 8; i++)
    for(int j = 0; j < 8; j++)
      maze[i][j] = 0;
  // Reset and hide player and ball positions
  playerPositionX = -1;
  playerPositionY = -1;
  ballPositionX = -1;
  ballPositionY = -1;
  // Turn off all LEDs
  for(int i = 0; i < 8; i++) {
    gpio_set_level(row_pins[i], 0);
    gpio_set_level(col_pins_red[i], 0);
    gpio_set_level(col_pins_green[i], 0);
  }
  // Display the score
  // Cycle green LEDs through the rows
  for(int col = 0; col < 8; col++) {
    gpio_set_level(col_pins_green[col], 1);
    for (int row = 0; row < score; row++)
      gpio_set_level(row_pins[row], 1);
    vTaskDelay(1 / portTICK_PERIOD_MS);
    for(int i = 0; i < 8; i++) gpio_set_level(row_pins[i], 0);
    gpio_set_level(col_pins_green[col], 0);
  }
  // Wait for a button to be pressed to start
  if(buttonPressed() && millis() -  lastButtonPressTime > 2000) {
    // Reset varibles
    lastButtonPressTime = millis();
    lastMoveTime = millis();
    startTime = millis();
    greenDotCount = -1;
    currentState = IDLE;
    vTaskDelay(debounceDelay / portTICK_PERIOD_MS);
    flashLEDsAndWaitForStart();
    initializeMaze();
  } 
}