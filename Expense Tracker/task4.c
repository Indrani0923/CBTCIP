#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_EXPENSES 100
#define MAX_CATEGORY_LENGTH 50
#define MAX_DATE_LENGTH 20

typedef struct {
    char date[MAX_DATE_LENGTH];
    char category[MAX_CATEGORY_LENGTH];
    double amount;
} Expense;

Expense expenses[MAX_EXPENSES];
int expenseCount = 0;

void addExpense();
void displayExpenses();
void displayCategoryReport();
void displayTotalExpenses();
void displayMenu();

int main() {
    int choice;

    while (1) {
        displayMenu();
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume the newline character left by scanf

        switch (choice) {
            case 1:
                addExpense();
                break;
            case 2:
                displayExpenses();
                break;
            case 3:
                displayCategoryReport();
                break;
            case 4:
                displayTotalExpenses();
                break;
            case 5:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void displayMenu() {
    printf("\nExpense Tracker\n");
    printf("1. Add Expense\n");
    printf("2. Display All Expenses\n");
    printf("3. Display Category Report\n");
    printf("4. Display Total Expenses\n");
    printf("5. Exit\n");
}

void addExpense() {
    if (expenseCount >= MAX_EXPENSES) {
        printf("Expense limit reached.\n");
        return;
    }

    Expense newExpense;

    printf("Enter date (YYYY-MM-DD): ");
    fgets(newExpense.date, MAX_DATE_LENGTH, stdin);
    newExpense.date[strcspn(newExpense.date, "\n")] = '\0';  // Remove newline character

    printf("Enter category: ");
    fgets(newExpense.category, MAX_CATEGORY_LENGTH, stdin);
    newExpense.category[strcspn(newExpense.category, "\n")] = '\0';  // Remove newline character

    printf("Enter amount: ");
    scanf("%lf", &newExpense.amount);
    getchar();  // Consume the newline character left by scanf

    expenses[expenseCount++] = newExpense;
    printf("Expense added successfully!\n");
}

void displayExpenses() {
    printf("\nAll Expenses:\n");
    printf("+------------+----------------------+---------+\n");
    printf("| Date       | Category             | Amount  |\n");
    printf("+------------+----------------------+---------+\n");

    for (int i = 0; i < expenseCount; i++) {
        printf("| %-10s | %-20s | %7.2f |\n", expenses[i].date, expenses[i].category, expenses[i].amount);
    }

    printf("+------------+----------------------+---------+\n");
}

void displayCategoryReport() {
    char category[MAX_CATEGORY_LENGTH];

    printf("Enter category to report: ");
    fgets(category, MAX_CATEGORY_LENGTH, stdin);
    category[strcspn(category, "\n")] = '\0';  // Remove newline character

    printf("\nExpenses for category '%s':\n", category);
    printf("+------------+---------+\n");
    printf("| Date       | Amount  |\n");
    printf("+------------+---------+\n");

    double total = 0.0;
    for (int i = 0; i < expenseCount; i++) {
        if (strcmp(expenses[i].category, category) == 0) {
            printf("| %-10s | %7.2f |\n", expenses[i].date, expenses[i].amount);
            total += expenses[i].amount;
        }
    }

    printf("+------------+---------+\n");
    printf("| Total      | %7.2f |\n", total);
    printf("+------------+---------+\n");
}

void displayTotalExpenses() {
    double total = 0.0;

    for (int i = 0; i < expenseCount; i++) {
        total += expenses[i].amount;
    }

    printf("\nTotal Expenses: %.2f\n", total);
}
