#include "main.h"

/**
 * Interactive calculator program that supports basic arithmetic operations
 * Allows continuous calculations with running result
 * Supports operations: addition, subtraction, multiplication, division
 */
int main() {
    int choice;
    history_count = 0;
    
    while (1) {
        displayMenu();
        scanf("%d", &choice);
        while (getchar() != '\n');  // Clear input buffer

        switch (choice) {
            case 0:
                clearScreen();
                startCalculator();
                break;
            case 1:
                clearScreen();
                displayHistory();
                break;
            case 2:
                printf("\nGoodbye!\n");
                return 0;
            default:
                printf("\nInvalid choice. Please try again.\n");
                sleep(1);
        }
    }
}

/**
 * Displays the main menu
 */
void displayMenu() {
    clearScreen();
    printf("\n╔════════════════════════╗\n");
    printf("║      CALCULATOR        ║\n");
    printf("╠════════════════════════╣\n");
    printf("║ (0) Start Calculator   ║\n");
    printf("║ (1) View Calc History  ║\n");
    printf("║ (2) Exit               ║\n");
    printf("╚════════════════════════╝\n");
    printf("\nEnter your choice: ");
}

/**
 * Displays the calculation history
 */
void displayHistory() {
    if (history_count == 0) {
        printf("\nNo calculations performed yet.\n");
    } else {
        printf("\n=== Calculation History ===\n");
        for (int j = 0; j < history_count; j++) {
            printf("%d: %.2f %c %.2f = %.2f\n", 
                j + 1, number[j], operator[j], 
                number[j + 1], results[j]);
        }
    }
    printf("\nPress Enter to continue...");
    getchar();
}

/**
 * Starts the calculator for new calculations
 */
void startCalculator() {
    double result = 0;
    i = 0;
    char input[100];

    // Main calculation loop
    while (i < MAX_OPERATIONS) {
        // Handle first number input differently
        if (i == 0) {
            printf("Enter first number: ");
            if (scanf("%lf", &number[i]) != 1) {
                printf("\n╔════════════════════════════════════╗");
                printf("\n║           ERROR: Input            ║");
                printf("\n║     Invalid number format!        ║");
                printf("\n║     Please enter a valid number   ║");
                printf("\n╚════════════════════════════════════╝\n\n");
                while (getchar() != '\n');  // Clear invalid input
                sleep(2);
                continue;
            }
        } else {
            // Show current result for continuing calculations
            printf("Current result: %.2f\n", result);
        }

        // Clear input buffer to prevent issues with subsequent inputs
        while (getchar() != '\n');
        
        // Get operator from user
        printf("Enter operator (+, -, *, /) or 'q' to quit: ");
        scanf(" %c", &operator[i]);

        // Check for quit condition
        if (operator[i] == 'q') {
            break;
        }

        // Validate operator input
        if (!validateOperator()) {
            continue;  // Skip this iteration if operator is invalid
        }

        // Get the second number
        printf("Enter next number: ");
        if (scanf("%lf", &number[i + 1]) != 1) {
            printf("\n╔════════════════════════════════════╗");
            printf("\n║           ERROR: Input             ║");
            printf("\n║     Invalid number format!         ║");
            printf("\n║     Please enter a valid number    ║");
            printf("\n╚════════════════════════════════════╝\n\n");
            while (getchar() != '\n');  // Clear invalid input
            sleep(2);
            continue;
        }

        // Check for division by zero
        if (operator[i] == '/' && number[i + 1] == 0) {
            printf("\n╔════════════════════════════════════╗");
            printf("\n║           ERROR: Division          ║");
            printf("\n║      Cannot divide by zero,        ║", number[i]);
            printf("\n║      Operation will be skipped     ║");
            printf("\n╚════════════════════════════════════╝\n\n");
            sleep(2);  // Give user time to read the error
            continue;
        }

        // Perform calculation
        if (i == 0) {
            // First calculation uses both input numbers
            result = calculate(number[i], number[i + 1], operator[i]);
        } else {
            // Subsequent calculations use previous result and new number
            result = calculate(result, number[i + 1], operator[i]);
        }

        // Display the result
        displayResult(result);
        results[history_count++] = result;  // Store the result in history
        i++;  // Move to next operation
    }

    // Show final result when calculations are complete
    printf("\nFinal result: %.2f\n\n", result);
}

/**
 * Validates the operator input
 * @return 1 if operator is valid, 0 otherwise
 */
int validateOperator() {
    // Check if operator is one of the valid arithmetic operators
    if (operator[i] == '+' || operator[i] == '-' || 
        operator[i] == '*' || operator[i] == '/') {
        return 1;
    }
    
    // Display error message for invalid operator
    printf("'%c' is not a valid operator\n", operator[i]);
    sleep(1);  // Pause briefly to show error message
    return 0;
}

/**
 * Performs the arithmetic calculation
 * @param num1 First operand
 * @param num2 Second operand
 * @param op Operator
 * @return Result of the calculation
 */
double calculate(double num1, double num2, char op) {
    switch (op) {
        case '+': return num1 + num2;  // Addition
        case '-': return num1 - num2;  // Subtraction
        case '*': return num1 * num2;  // Multiplication
        case '/': return num1 / num2;  // Division
        default: return 0;             // Should never reach here due to validation
    }
}

/**
 * Displays the calculation result
 * @param result The result to display
 */
void displayResult(double result) {
    printf("= %.2f\n\n", result);
}

/**
 * Clears the screen
 */
void clearScreen() {
    printf("\033[2J\033[H");  // ANSI escape sequence to clear screen
}
