#include "raylib.h"
#include <raymath.h>

#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 450
#define WINDOW_TITLE "Cookie Clicker"

// Constants for initial costs
#define INITIAL_UPGRADE_COST 10
#define INITIAL_AUTOMATION_COST 50

int main(void)
{
    // Initialize game state
    int cookieCount = 0;
    int clickPower = 1;
    int cookiesPerSecond = 0;
    float upgradeCost = INITIAL_UPGRADE_COST;
    float automationCost = INITIAL_AUTOMATION_COST;

    // Initialize Raylib window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Define cookie button properties
    Vector2 cookiePos = { SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2 - 50 };
    float cookieRadius = 50.0f;

    // Define upgrade button properties
    Rectangle upgradeButton = { 50, SCREEN_HEIGHT - 100, 200, 50 };
    Rectangle automationButton = { SCREEN_WIDTH - 250, SCREEN_HEIGHT - 100, 200, 50 };

    // Main game loop
    while (!WindowShouldClose())
    {
        // Check for cookie click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            Vector2 mousePos = GetMousePosition();
            float distance = Vector2Distance(mousePos, cookiePos);
            if (distance <= cookieRadius)
            {
                cookieCount += clickPower; // Increment cookie count by click power
            }
        }

        // Check for upgrade button click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), upgradeButton))
        {
            if (cookieCount >= upgradeCost)
            {
                cookieCount -= (int)upgradeCost; // Deduct cookies
                clickPower++;                   // Increase click power
                upgradeCost *= 1.5;             // Scale the upgrade cost
            }
        }

        // Check for automation button click
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), automationButton))
        {
            if (cookieCount >= automationCost)
            {
                cookieCount -= (int)automationCost; // Deduct cookies
                cookiesPerSecond++;                // Increase cookies generated per second
                automationCost *= 1.7f;               // Scale the automation cost
            }
        }

        // Automation: Add cookies based on cookiesPerSecond
        static double lastUpdateTime = GetTime();
        double currentTime = GetTime();
        if (currentTime - lastUpdateTime >= 1.0) // Update every second
        {
            cookieCount += cookiesPerSecond;
            lastUpdateTime = currentTime;
        }

        // Draw the game
        BeginDrawing();

        ClearBackground(RAYWHITE);

        // Draw the cookie
        DrawCircleV(cookiePos, cookieRadius, BROWN);

        // Display cookie count
        const char* cookieText = TextFormat("Cookies: %d", cookieCount);
        int fontSize = 20;
        int textWidth = MeasureText(cookieText, fontSize);
        DrawText(cookieText, SCREEN_WIDTH / 2 - textWidth / 2, 20, fontSize, BLACK);

        // Display click power
        const char* powerText = TextFormat("Click Power: %d", clickPower);
        int powerTextWidth = MeasureText(powerText, fontSize);
        DrawText(powerText, SCREEN_WIDTH / 2 - powerTextWidth / 2, 50, fontSize, DARKGRAY);

        // Display cookies per second
        const char* automationText = TextFormat("Cookies/Sec: %d", cookiesPerSecond);
        int automationTextWidth = MeasureText(automationText, fontSize);
        DrawText(automationText, SCREEN_WIDTH / 2 - automationTextWidth / 2, 80, fontSize, DARKGRAY);

        // Draw upgrade button
        DrawRectangleRec(upgradeButton, LIGHTGRAY);
        const char* upgradeButtonText = TextFormat("Upgrade (%.0f C)", upgradeCost);
        DrawText(upgradeButtonText, upgradeButton.x + 10, upgradeButton.y + 15, 20, BLACK);

        // Draw automation button
        DrawRectangleRec(automationButton, LIGHTGRAY);
        const char* automationButtonText = TextFormat("Automate (%.0f C)", automationCost);
        DrawText(automationButtonText, automationButton.x + 10, automationButton.y + 15, 20, BLACK);

        EndDrawing();
    }

    // Close the window and clean up resources
    CloseWindow();

    return 0;
}
