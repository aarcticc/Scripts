#ifndef MAIN_H
#define MAIN_H

// Required standard libraries
#include <stdio.h>
#include <stdbool.h>
#include <unistd.h>

// Maximum number of operations that can be performed in sequence
#define MAX_OPERATIONS 100

// Global variables for storing calculation history
double number[MAX_OPERATIONS];    // Array to store operands
char operator[MAX_OPERATIONS];    // Array to store operators
int i;                           // Current operation index

// Additional variables for history
double results[MAX_OPERATIONS];  // Store calculation results
int history_count;              // Number of calculations performed

// Function prototypes
/**
 * Validates if the input operator is valid (+, -, *, /)
 * @return 1 if valid, 0 if invalid
 */
int validateOperator(void);

/**
 * Performs arithmetic calculation based on given operator
 * @param num1 First operand
 * @param num2 Second operand
 * @param op Operator (+, -, *, /)
 * @return Result of the calculation
 */
double calculate(double num1, double num2, char op);

/**
 * Displays the calculation result
 * @param result The result to display
 */
void displayResult(double result);

/**
 * Displays the calculator menu options
 */
void displayMenu(void);

/**
 * Displays the history of calculations
 */
void displayHistory(void);

/**
 * Starts the calculator program, handling user input and operations
 */
void startCalculator(void);

/**
 * Clears the screen for a clean display
 */
void clearScreen(void);

/**
 * Validates numeric input
 * @return true if input is valid number, false otherwise
 */
bool validateNumber(void);

#endif
