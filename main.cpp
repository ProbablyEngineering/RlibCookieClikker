#include "raylib.h"
#include <raymath.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define WINDOW_TITLE "Cookie Clicker"

int main(void)
{
    // Initialize the game state
    int cookieCount = 0;

    // Initialize Raylib window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Define cookie button properties
    Vector2 cookiePos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 };
    float cookieRadius = 50.0f;
    Color cookieColor = BROWN;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Check for click on the circle
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            float distance = Vector2Distance(mousePos, cookiePos);
            if (distance <= cookieRadius)
            {
                cookieCount++; // Increment cookie count on click
            }
        }

        // Draw the game
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw the cookie (circle)
        DrawCircleV(cookiePos, cookieRadius, cookieColor);

        // Display the cookie count
        const char* cookieText = TextFormat("Cookies: %d", cookieCount);
        int fontSize = 20;
        int textWidth = MeasureText(cookieText, fontSize);
        DrawText(cookieText, SCREEN_WIDTH / 2 - textWidth / 2, 50, fontSize, BLACK);

        EndDrawing();
    }

    // Close the window and clean up resources
    CloseWindow();

    return 0;
}
