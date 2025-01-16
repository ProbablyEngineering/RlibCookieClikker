#include "raylib.h"
#include <raymath.h>
#include <vector>
#include <string>

#define SCREEN_WIDTH 800 
#define SCREEN_HEIGHT 450
#define WINDOW_TITLE "Cookie Clicker" 

struct Upgrade {
    std::string name; 
    float cost;
    int effect;
    bool isAutomation; // Whether this upgrade is for automation
};

int main(void)
{
    // Initialize game state
    int cookieCount = 0;
    int clickPower = 1;
    int cookiesPerSecond = 0;
    std::vector<Upgrade> upgrades = {
        {"Click Power +1", 10, 1, false},
        {"Click Power +2", 50, 2, false},
        {"Click Power +3", 150, 3, false},
        {"Automation +1 CPS", 100, 1, true},
        {"Automation +2 CPS", 250, 2, true},
        {"Automation +3 CPS", 500, 3, true},
        {"Automation +4 CPS", 1000, 4, true},
        {"Automation +5 CPS", 1500, 5, true}
    };

    // UI Scrollbar state
    float scrollPosition = 0.0f;
    const float scrollSpeed = 10.0f;
    const int upgradeHeight = 60; // Height of each upgrade button
    const int upgradesVisible = 7; // Number of upgrades visible at a time

    // Initialize Raylib window
    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, WINDOW_TITLE);
    SetTargetFPS(60);

    // Define cookie button properties
    Vector2 cookiePos = { SCREEN_WIDTH / 2 - 200, SCREEN_HEIGHT / 2 - 50 };
    float cookieRadius = 50.0f;

    // Main game loop
    while (!WindowShouldClose())
    {
        // Scroll upgrades list
        int maxScroll = upgrades.size() * upgradeHeight - upgradesVisible * upgradeHeight;
        if (IsKeyDown(KEY_DOWN)) scrollPosition += scrollSpeed;
        if (IsKeyDown(KEY_UP)) scrollPosition -= scrollSpeed;
        scrollPosition = Clamp(scrollPosition, 0, maxScroll);

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

        // Check for upgrades click
        for (int i = 0; i < upgrades.size(); i++)
        {
            // Calculate the button's position considering scrolling
            Rectangle upgradeButton = {
                SCREEN_WIDTH - 200,
                20 + i * upgradeHeight - scrollPosition,
                180,
                upgradeHeight - 10
            };

            // Check if the button is visible
            if (upgradeButton.y < 20 || upgradeButton.y > SCREEN_HEIGHT - 20) continue;

            if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && CheckCollisionPointRec(GetMousePosition(), upgradeButton))
            {
                if (cookieCount >= upgrades[i].cost)
                {
                    cookieCount -= (int)upgrades[i].cost; // Deduct cost
                    if (upgrades[i].isAutomation)
                    {
                        cookiesPerSecond += upgrades[i].effect;
                    }
                    else
                    {
                        clickPower += upgrades[i].effect;
                    }
                    upgrades[i].cost *= 1.5; // Increase cost dynamically
                }
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
        DrawText(cookieText, SCREEN_WIDTH / 2 - 200 - textWidth / 2, 20, fontSize, BLACK);

        // Display click power
        const char* powerText = TextFormat("Click Power: %d", clickPower);
        DrawText(powerText, SCREEN_WIDTH / 2 - 200 - textWidth / 2, 50, fontSize, DARKGRAY);

        // Display cookies per second
        const char* automationText = TextFormat("Cookies/Sec: %d", cookiesPerSecond);
        DrawText(automationText, SCREEN_WIDTH / 2 - 200 - textWidth / 2, 80, fontSize, DARKGRAY);

        // Draw upgrades list
        for (int i = 0; i < upgrades.size(); i++)
        {
            // Calculate the button's position considering scrolling
            Rectangle upgradeButton = {
                SCREEN_WIDTH - 200,
                20 + i * upgradeHeight - scrollPosition,
                180,
                upgradeHeight - 10
            };

            // Check if the button is visible
            if (upgradeButton.y < 20 || upgradeButton.y > SCREEN_HEIGHT - 20) continue;

            DrawRectangleRec(upgradeButton, LIGHTGRAY);
            DrawText(upgrades[i].name.c_str(), upgradeButton.x + 10, upgradeButton.y + 10, 20, BLACK);
            DrawText(TextFormat("%.0f Cookies", upgrades[i].cost), upgradeButton.x + 10, upgradeButton.y + 30, 15, DARKGRAY);
        }

        // Draw scrollbar
        Rectangle scrollBar = { SCREEN_WIDTH - 20, 20, 10, SCREEN_HEIGHT - 40 };
        DrawRectangleRec(scrollBar, LIGHTGRAY);
        float scrollBarThumbHeight = (float)upgradesVisible / upgrades.size() * scrollBar.height;
        float scrollBarThumbY = scrollBar.y + (scrollPosition / maxScroll) * (scrollBar.height - scrollBarThumbHeight);
        DrawRectangle(scrollBar.x, scrollBarThumbY, scrollBar.width, scrollBarThumbHeight, DARKGRAY);

        EndDrawing();
    }

    // Close the window and clean up resources
    CloseWindow();

    return 0;
}
