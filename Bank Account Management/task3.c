#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ACCOUNTS 100
#define MAX_NAME_LENGTH 100

typedef enum {
    SAVINGS,
    CHECKING,
    FIXED_DEPOSIT
} AccountType;

typedef struct {
    int accountNumber;
    char name[MAX_NAME_LENGTH];
    AccountType type;
    double balance;
    double interestRate;
} Account;

int accountCount = 0;
Account accounts[MAX_ACCOUNTS];

void createAccount();
void deposit();
void withdraw();
void checkBalance();
void calculateInterest();
void displayAccount(const Account *account);
const char* getAccountTypeName(AccountType type);

int main() {
    int choice;

    while (1) {
        printf("\nBank Account Management System\n");
        printf("1. Create Account\n");
        printf("2. Deposit Funds\n");
        printf("3. Withdraw Funds\n");
        printf("4. Check Balance\n");
        printf("5. Calculate Interest\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();  // Consume the newline character left by scanf

        switch (choice) {
            case 1:
                createAccount();
                break;
            case 2:
                deposit();
                break;
            case 3:
                withdraw();
                break;
            case 4:
                checkBalance();
                break;
            case 5:
                calculateInterest();
                break;
            case 6:
                exit(0);
            default:
                printf("Invalid choice. Please try again.\n");
        }
    }

    return 0;
}

void createAccount() {
    if (accountCount >= MAX_ACCOUNTS) {
        printf("Maximum number of accounts reached.\n");
        return;
    }

    Account newAccount;
    newAccount.accountNumber = accountCount + 1;

    printf("Enter account holder name: ");
    fgets(newAccount.name, MAX_NAME_LENGTH, stdin);
    newAccount.name[strcspn(newAccount.name, "\n")] = '\0';  // Remove newline character

    printf("Select account type (0: Savings, 1: Checking, 2: Fixed Deposit): ");
    int type;
    scanf("%d", &type);
    getchar();  // Consume the newline character left by scanf

    if (type < 0 || type > 2) {
        printf("Invalid account type.\n");
        return;
    }

    newAccount.type = (AccountType)type;

    switch (newAccount.type) {
        case SAVINGS:
            newAccount.interestRate = 0.03;
            break;
        case CHECKING:
            newAccount.interestRate = 0.01;
            break;
        case FIXED_DEPOSIT:
            newAccount.interestRate = 0.05;
            break;
    }

    newAccount.balance = 0.0;
    accounts[accountCount++] = newAccount;

    printf("Account created successfully!\n");
    displayAccount(&newAccount);
}

void deposit() {
    int accountNumber;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    getchar();  // Consume the newline character left by scanf

    if (accountNumber <= 0 || accountNumber > accountCount) {
        printf("Invalid account number.\n");
        return;
    }

    printf("Enter amount to deposit: ");
    scanf("%lf", &amount);
    getchar();  // Consume the newline character left by scanf

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    accounts[accountNumber - 1].balance += amount;
    printf("Amount deposited successfully!\n");
    displayAccount(&accounts[accountNumber - 1]);
}

void withdraw() {
    int accountNumber;
    double amount;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    getchar();  // Consume the newline character left by scanf

    if (accountNumber <= 0 || accountNumber > accountCount) {
        printf("Invalid account number.\n");
        return;
    }

    printf("Enter amount to withdraw: ");
    scanf("%lf", &amount);
    getchar();  // Consume the newline character left by scanf

    if (amount <= 0) {
        printf("Invalid amount.\n");
        return;
    }

    if (accounts[accountNumber - 1].balance < amount) {
        printf("Insufficient balance.\n");
        return;
    }

    accounts[accountNumber - 1].balance -= amount;
    printf("Amount withdrawn successfully!\n");
    displayAccount(&accounts[accountNumber - 1]);
}

void checkBalance() {
    int accountNumber;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    getchar();  // Consume the newline character left by scanf

    if (accountNumber <= 0 || accountNumber > accountCount) {
        printf("Invalid account number.\n");
        return;
    }

    displayAccount(&accounts[accountNumber - 1]);
}

void calculateInterest() {
    int accountNumber;

    printf("Enter account number: ");
    scanf("%d", &accountNumber);
    getchar();  // Consume the newline character left by scanf

    if (accountNumber <= 0 || accountNumber > accountCount) {
        printf("Invalid account number.\n");
        return;
    }

    Account *account = &accounts[accountNumber - 1];
    double interest = account->balance * account->interestRate;

    printf("Interest for account number %d (%.2f%%): %.2f\n", 
        account->accountNumber, account->interestRate * 100, interest);
}

void displayAccount(const Account *account) {
    printf("\nAccount Details:\n");
    printf("Account Number: %d\n", account->accountNumber);
    printf("Account Holder: %s\n", account->name);
    printf("Account Type: %s\n", getAccountTypeName(account->type));
    printf("Balance: %.2f\n", account->balance);
    printf("Interest Rate: %.2f%%\n", account->interestRate * 100);
}

const char* getAccountTypeName(AccountType type) {
    switch (type) {
        case SAVINGS:
            return "Savings";
        case CHECKING:
            return "Checking";
        case FIXED_DEPOSIT:
            return "Fixed Deposit";
        default:
            return "Unknown";
    }
}
