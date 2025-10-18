#include <stdio.h>
#include <stdlib.h>
#include <conio.h>   // For _kbhit() and _getch()
#include <windows.h> // For Sleep() and console functions
#include <time.h>    // For srand()

// --- Game Configuration ---
#define WIDTH 40
#define HEIGHT 20
#define INITIAL_SPEED 200 // Milliseconds

// --- Data Structures ---
typedef struct SnakeSegment {
    int x, y;
    struct SnakeSegment* next;
} SnakeSegment;

typedef enum { STOP = 0, LEFT, RIGHT, UP, DOWN } Direction;
typedef enum { MENU, PLAYING, GAME_OVER } GameState;

// --- Global Variables ---
SnakeSegment* head = NULL;
int foodX, foodY;
int score = 0;
int highScore = 0;
int gameSpeed;
Direction dir;
GameState currentState;

// --- Function Prototypes ---
void setCursorPosition(int x, int y);
void hideCursor();
void setup();
void displayMenu();
void displayGameOver();
void generateFood();
void draw();
void input();
void logic();
void freeSnake();
void loadHighScore();
void saveHighScore();

// --- Main Game Loop ---
int main() {
    srand(time(NULL)); // Seed for random number generation
    hideCursor();
    loadHighScore();
    currentState = MENU;

    while (1) {
        switch (currentState) {
            case MENU:
                displayMenu();
                break;
            case PLAYING:
                input();
                logic();
                draw();
                Sleep(gameSpeed);
                break;
            case GAME_OVER:
                saveHighScore();
                displayGameOver();
                break;
        }
    }
    return 0;
}

// --- Utility Functions ---

// Hides the blinking console cursor for a cleaner look
void hideCursor() {
    HANDLE consoleHandle = GetStdHandle(STD_OUTPUT_HANDLE);
    CONSOLE_CURSOR_INFO info;
    info.dwSize = 100;
    info.bVisible = FALSE;
    SetConsoleCursorInfo(consoleHandle, &info);
}

// Moves the console cursor to a specific (x, y) position to redraw the screen
void setCursorPosition(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

// --- Game State Functions ---

// Initializes game variables for a new round
void setup() {
    freeSnake(); // Clear any previous snake
    dir = STOP;
    score = 0;

    // Create the initial snake head
    head = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    head->x = WIDTH / 2;
    head->y = HEIGHT / 2;
    head->next = NULL;

    generateFood();
    currentState = PLAYING;
}

// Displays the main menu and handles difficulty selection
void displayMenu() {
    system("cls");
    printf("\n\n");
    printf("    ==============================\n");
    printf("         WELCOME TO SNAKE\n");
    printf("    ==============================\n\n");
    printf("    Controls:\n");
    printf("    'w' - Up, 's' - Down, 'a' - Left, 'd' - Right\n\n");
    printf("    Select Difficulty:\n");
    printf("    1. Easy\n");
    printf("    2. Medium\n");
    printf("    3. Hard\n\n");
    printf("    Enter your choice: ");

    char choice = _getch();
    switch (choice) {
        case '1':
            gameSpeed = 200; // Slower
            break;
        case '2':
            gameSpeed = 120; // Medium
            break;
        case '3':
            gameSpeed = 70;  // Faster
            break;
        default:
            return; // Stay on menu if invalid choice
    }
    setup(); // Start the game with selected difficulty
}

// Displays the game over screen and waits for user action
void displayGameOver() {
    setCursorPosition(WIDTH / 2 - 10, HEIGHT / 2 - 2);
    printf("=====================");
    setCursorPosition(WIDTH / 2 - 10, HEIGHT / 2 - 1);
    printf("     GAME OVER!      ");
    setCursorPosition(WIDTH / 2 - 10, HEIGHT / 2);
    printf("  Final Score: %-4d ", score);
    setCursorPosition(WIDTH / 2 - 10, HEIGHT / 2 + 1);
    printf("=====================");
    setCursorPosition(WIDTH / 2 - 13, HEIGHT / 2 + 3);
    printf("Press 'R' to Play Again or 'Q' to Quit.");

    while (1) {
        if (_kbhit()) {
            char choice = _getch();
            if (choice == 'r' || choice == 'R') {
                currentState = MENU;
                break;
            } else if (choice == 'q' || choice == 'Q') {
                system("cls");
                printf("Thanks for playing!\n");
                exit(0);
            }
        }
    }
}

// --- Core Game Functions ---

// Generates food at a random position, avoiding the snake's body
void generateFood() {
    int onSnake;
    do {
        onSnake = 0;
        foodX = rand() % WIDTH;
        foodY = rand() % HEIGHT;
        SnakeSegment* current = head;
        while (current != NULL) {
            if (current->x == foodX && current->y == foodY) {
                onSnake = 1;
                break;
            }
            current = current->next;
        }
    } while (onSnake);
}

// Draws the entire game board, snake, and food
void draw() {
    setCursorPosition(0, 0);

    // Top border
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");

    // Game area
    for (int i = 0; i < HEIGHT; i++) {
        printf("#"); // Left border
        for (int j = 0; j < WIDTH; j++) {
            if (i == foodY && j == foodX) {
                printf("F"); // Food
            } else {
                SnakeSegment* current = head;
                int isBody = 0;
                while (current != NULL) {
                    if (current->x == j && current->y == i) {
                        printf(current == head ? "O" : "o");
                        isBody = 1;
                        break;
                    }
                    current = current->next;
                }
                if (!isBody) {
                    printf(" "); // Empty space
                }
            }
        }
        printf("#\n"); // Right border
    }

    // Bottom border
    for (int i = 0; i < WIDTH + 2; i++) printf("#");
    printf("\n");
    printf("Score: %d | High Score: %d\n", score, highScore);
}

// Handles user input for snake movement
void input() {
    if (_kbhit()) {
        switch (_getch()) {
            case 'a':
                if (dir != RIGHT) dir = LEFT;
                break;
            case 'd':
                if (dir != LEFT) dir = RIGHT;
                break;
            case 'w':
                if (dir != DOWN) dir = UP;
                break;
            case 's':
                if (dir != UP) dir = DOWN;
                break;
            case 'x':
                currentState = GAME_OVER;
                break;
        }
    }
}

// Updates the game state
void logic() {
    if (dir == STOP) return;

    // Create a new head for the snake's new position
    SnakeSegment* newHead = (SnakeSegment*)malloc(sizeof(SnakeSegment));
    newHead->x = head->x;
    newHead->y = head->y;

    // Move the new head in the current direction
    switch (dir) {
        case LEFT: newHead->x--; break;
        case RIGHT: newHead->x++; break;
        case UP: newHead->y--; break;
        case DOWN: newHead->y++; break;
    }

    // Check for wall collision
    if (newHead->x < 0 || newHead->x >= WIDTH || newHead->y < 0 || newHead->y >= HEIGHT) {
        free(newHead);
        currentState = GAME_OVER;
        return;
    }
    
    // Check for self-collision
    SnakeSegment* current = head;
    while(current != NULL) {
        if(current->x == newHead->x && current->y == newHead->y){
            free(newHead);
            currentState = GAME_OVER;
            return;
        }
        current = current->next;
    }

    // Link the new head to the old head
    newHead->next = head;
    head = newHead;

    // Check for food collision
    if (head->x == foodX && head->y == foodY) {
        score += 10;
        if (score > highScore) {
            highScore = score;
        }
        generateFood();
    } else {
        // If no food eaten, remove the tail segment to simulate movement
        current = head;
        while (current->next->next != NULL) {
            current = current->next;
        }
        free(current->next);
        current->next = NULL;
    }
}

// --- Memory and File I/O ---

// Frees all memory used by the snake linked list
void freeSnake() {
    SnakeSegment* current = head;
    while (current != NULL) {
        SnakeSegment* temp = current;
        current = current->next;
        free(temp);
    }
    head = NULL;
}

// Loads the high score from a file
void loadHighScore() {
    FILE *file = fopen("highscore.txt", "r");
    if (file != NULL) {
        fscanf(file, "%d", &highScore);
        fclose(file);
    } else {
        highScore = 0;
    }
}

// Saves the high score to a file
void saveHighScore() {
    FILE *file = fopen("highscore.txt", "w");
    if (file != NULL) {
        fprintf(file, "%d", highScore);
        fclose(file);
    }
}