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
    char expr[100];
    double result;
    
    printf("Enter expression (e.g., 324.56/34*67+2): ");
    scanf("%s", expr);
    
    result = parseExpression(expr);
    
    displayResult(result);
    results[history_count++] = result;
}

/**
 * Parses and calculates the result of a given expression
 * @param expr The expression to parse and calculate
 * @return The result of the calculation
 */
double parseExpression(char* expr) {
    double num = 0, stack[MAX_OPERATIONS];
    char op = '+';
    int stack_top = 0;
    
    for (int j = 0; expr[j]; j++) {
        if (expr[j] >= '0' && expr[j] <= '9' || expr[j] == '.') {
            num = num * 10 + (expr[j] - '0');
        } else {
            // Process operator
            switch (op) {
                case '+': stack[stack_top++] = num; break;
                case '-': stack[stack_top++] = -num; break;
                case '*': stack[stack_top-1] *= num; break;
                case '/': 
                    if (num == 0) {
                        printf("\n╔════════════════════════════════════╗");
                        printf("\n║           ERROR: Division          ║");
                        printf("\n║      Cannot divide by zero         ║");
                        printf("\n╚════════════════════════════════════╝\n\n");
                        return 0;
                    }
                    stack[stack_top-1] /= num;
                    break;
            }
            num = 0;
            op = expr[j];
        }
    }
    
    // Process last number
    if (op == '+') stack[stack_top++] = num;
    else if (op == '-') stack[stack_top++] = -num;
    else if (op == '*') stack[stack_top-1] *= num;
    else if (op == '/') {
        if (num == 0) {
            printf("Error: Division by zero!\n");
            return 0;
        }
        stack[stack_top-1] /= num;
    }
    
    // Sum up all numbers in stack
    result = 0;
    for (int j = 0; j < stack_top; j++) {
        result += stack[j];
    }
    
    return result;
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
