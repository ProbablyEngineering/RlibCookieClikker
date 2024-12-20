#include <iostream>
#include <cmath>
#include <thread>
#include <chrono>

class CookieClicker {
private:
    double cookies;
    double clickPower;
    double cookiesPerSecond;
    double upgradeCost;
    double automationCost;

public:
    CookieClicker() : cookies(0), clickPower(1), cookiesPerSecond(0), upgradeCost(10), automationCost(50) {}

    void click() {
        cookies += clickPower;
        std::cout << "You clicked! Cookies: " << cookies << "\n";
    }

    void upgradeClickPower() {
        if (cookies >= upgradeCost) {
            cookies -= upgradeCost;
            clickPower += 1;
            upgradeCost *= 1.5;
            std::cout << "Upgraded click power! New power: " << clickPower << ", Next upgrade cost: " << upgradeCost << "\n";
        } else {
            std::cout << "Not enough cookies for upgrade! Need: " << upgradeCost - cookies << " more.\n";
        }
    }

    void buyAutomation() {
        if (cookies >= automationCost) {
            cookies -= automationCost;
            cookiesPerSecond += 1;
            automationCost *= 2;
            std::cout << "Automation added! Generating " << cookiesPerSecond << " cookies/second. Next automation cost: " << automationCost << "\n";
        } else {
            std::cout << "Not enough cookies for automation! Need: " << automationCost - cookies << " more.\n";
        }
    }

    void generateCookies() {
        cookies += cookiesPerSecond;
    }

    void displayStatus() const {
        std::cout << "\n--- Current Status ---\n";
        std::cout << "Cookies: " << cookies << "\n";
        std::cout << "Click Power: " << clickPower << "\n";
        std::cout << "Cookies per Second: " << cookiesPerSecond << "\n";
        std::cout << "Upgrade Cost: " << upgradeCost << "\n";
        std::cout << "Automation Cost: " << automationCost << "\n";
    }
};

int main() {
    CookieClicker game;
    char choice;

    std::cout << "Welcome to Cookie Clicker!\n";

    while (true) {
        game.displayStatus();
        std::cout << "Choose an action: (C)lick, (U)pgrade, (A)utomate, (Q)uit: ";
        std::cin >> choice;

        switch (choice) {
            case 'C':
            case 'c':
                game.click();
                break;
            case 'U':
            case 'u':
                game.upgradeClickPower();
                break;
            case 'A':
            case 'a':
                game.buyAutomation();
                break;
            case 'Q':
            case 'q':
                std::cout << "Exiting game. Thanks for playing!\n";
                return 0;
            default:
                std::cout << "Invalid choice! Please try again.\n";
        }

        // Simulate idle cookie generation
        std::this_thread::sleep_for(std::chrono::seconds(1));
        game.generateCookies();
    }

    return 0;
}
