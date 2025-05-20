#include "raylib.h"
#include <stdlib.h>
#include <time.h>

enum Choice { ROCK, PAPER, SCISSORS, NONE };
#define CHOICE_COUNT 3

enum Choice GetComputerChoice() {
    return (enum Choice)GetRandomValue(0, CHOICE_COUNT - 1);
}

const char* ChoiceToString(enum Choice choice) {
    switch (choice) {
        case ROCK: return "Rock";
        case PAPER: return "Paper";
        case SCISSORS: return "Scissors";
        default: return "";
    }
}

const char* DetermineWinner(enum Choice player, enum Choice computer) {
    if (player == computer) return "It's a draw!";
    if ((player == ROCK && computer == SCISSORS) ||
        (player == SCISSORS && computer == PAPER) ||
        (player == PAPER && computer == ROCK)) {
        return "You win!";
    }
    return "You lose!";
}

int main() {
    const int screenWidth = 800;
    const int screenHeight = 600;
    InitWindow(screenWidth, screenHeight, "Rock Paper Scissors");
    SetTargetFPS(60);
    srand((unsigned int)time(NULL));

    Rectangle rockButton = { screenWidth / 2.0f - 160, 200, 100, 50 };
    Rectangle paperButton = { screenWidth / 2.0f - 50, 200, 100, 50 };
    Rectangle scissorsButton = { screenWidth / 2.0f + 60, 200, 100, 50 };

    enum Choice playerChoice = NONE;
    enum Choice computerChoice = NONE;
    const char* resultText = "";
    int gameStarted = 0;

    while (!WindowShouldClose()) {
        if (!gameStarted) {
            if (IsKeyPressed(KEY_R)) {
                playerChoice = ROCK;
            } else if (IsKeyPressed(KEY_P)) {
                playerChoice = PAPER;
            } else if (IsKeyPressed(KEY_S)) {
                playerChoice = SCISSORS;
            } else if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                Vector2 mousePos = GetMousePosition();
                if (CheckCollisionPointRec(mousePos, rockButton)) {
                    playerChoice = ROCK;
                } else if (CheckCollisionPointRec(mousePos, paperButton)) {
                    playerChoice = PAPER;
                } else if (CheckCollisionPointRec(mousePos, scissorsButton)) {
                    playerChoice = SCISSORS;
                }
            }

            if (playerChoice != NONE) {
                computerChoice = GetComputerChoice();
                resultText = DetermineWinner(playerChoice, computerChoice);
                gameStarted = 1;
            }
        } else {
            if (IsKeyPressed(KEY_SPACE)) {
                gameStarted = 0;
                playerChoice = NONE;
                computerChoice = NONE;
                resultText = "";
            }
        }

        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawText("Rock Paper Scissors!", screenWidth / 2 - MeasureText("Rock Paper Scissors!", 30) / 2, 50, 30, BLACK);

        DrawRectangleRec(rockButton, LIGHTGRAY);
        DrawRectangleRec(paperButton, LIGHTGRAY);
        DrawRectangleRec(scissorsButton, LIGHTGRAY);
        DrawText("Rock (R)", rockButton.x + 5, rockButton.y + 15, 20, DARKGRAY);
        DrawText("Paper (P)", paperButton.x + 5, paperButton.y + 15, 20, DARKGRAY);
        DrawText("Scissors (S)", scissorsButton.x + 5, scissorsButton.y + 15, 20, DARKGRAY);

        DrawText("Make your move (R, P, S or click a button)", screenWidth / 2 - 220, 300, 20, GRAY);

        if (gameStarted) {
            DrawText(TextFormat("You chose: %s", ChoiceToString(playerChoice)), 50, 400, 20, BLUE);
            DrawText(TextFormat("Computer chose: %s", ChoiceToString(computerChoice)), 50, 430, 20, RED);
            DrawText(resultText, screenWidth / 2 - MeasureText(resultText, 30) / 2, 500, 30, DARKGREEN);
            DrawText("Press SPACE to play again", screenWidth / 2 - 180, 550, 20, GRAY);
        } else {
            DrawText("Waiting for your choice...", screenWidth / 2 - 150, 550, 20, GRAY);
        }

        EndDrawing();
    }

    CloseWindow();
    return 0;
}
