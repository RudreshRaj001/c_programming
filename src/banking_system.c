#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h> // For generating unique account numbers

// Structure to represent a bank account
typedef struct Account {
    int accountNumber;
    char name[50];
    char address[100];
    char phone[15];
    double balance;
    struct Account *next; // Pointer to the next account in the linked list
} Account;

Account *head = NULL; // Global pointer to the head of the linked list of accounts
static int latestAccountNumber = 1000; // Start account numbers from 1001

// Function prototypes
void createAccount();
void deposit();
void withdraw();
void checkBalance();
void transferFunds();
void deleteAccount();
void displayAllAccounts();
void saveAccountsToFile();
void loadAccountsFromFile();
int generateAccountNumber();
Account* findAccount(int accountNumber);
void clearInputBuffer();

int main() {
    int choice;

    loadAccountsFromFile(); // Load existing accounts when the program starts

    do {
        printf("\n--- Banking Management System ---\n");
        printf("1. Create New Account\n");
        printf("2. Deposit Funds\n");
        printf("3. Withdraw Funds\n");
        printf("4. Check Balance\n");
        printf("5. Transfer Funds\n");
        printf("6. Delete Account\n");
        printf("7. Display All Accounts\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            clearInputBuffer();
            continue;
        }
        clearInputBuffer(); // Clear the input buffer after reading an integer

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
                transferFunds();
                break;
            case 6:
                deleteAccount();
                break;
            case 7:
                displayAllAccounts();
                break;
            case 8:
                saveAccountsToFile(); // Save accounts before exiting
                printf("Exiting Banking System. Goodbye!\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 8);

    // Free all allocated memory before exiting
    Account *current = head;
    while (current != NULL) {
        Account *temp = current;
        current = current->next;
        free(temp);
    }

    return 0;
}

// Clears the standard input buffer
void clearInputBuffer() {
    int c;
    while ((c = getchar()) != '\n' && c != EOF);
}

// Generates a unique account number
int generateAccountNumber() {
    latestAccountNumber++;
    return latestAccountNumber;
}

// Finds an account by its account number
Account* findAccount(int accountNumber) {
    Account *current = head;
    while (current != NULL) {
        if (current->accountNumber == accountNumber) {
            return current;
        }
        current = current->next;
    }
    return NULL; // Not found
}

// Creates a new bank account
void createAccount() {
    Account *newAccount = (Account*) malloc(sizeof(Account));
    if (newAccount == NULL) {
        printf("Memory allocation failed. Cannot create account.\n");
        return;
    }

    printf("Enter Name: ");
    fgets(newAccount->name, sizeof(newAccount->name), stdin);
    newAccount->name[strcspn(newAccount->name, "\n")] = 0; // Remove newline

    printf("Enter Address: ");
    fgets(newAccount->address, sizeof(newAccount->address), stdin);
    newAccount->address[strcspn(newAccount->address, "\n")] = 0;

    printf("Enter Phone Number: ");
    fgets(newAccount->phone, sizeof(newAccount->phone), stdin);
    newAccount->phone[strcspn(newAccount->phone, "\n")] = 0;

    newAccount->accountNumber = generateAccountNumber();
    newAccount->balance = 0.0;
    newAccount->next = head; // Add to the beginning of the list
    head = newAccount;

    printf("\nAccount created successfully!\n");
    printf("Your Account Number is: %d\n", newAccount->accountNumber);
}

// Deposits funds into an account
void deposit() {
    int accNum;
    double amount;

    printf("Enter Account Number: ");
    scanf("%d", &accNum);
    clearInputBuffer();

    Account *account = findAccount(accNum);
    if (account == NULL) {
        printf("Error: Account not found.\n");
        return;
    }

    printf("Enter Amount to Deposit: ");
    scanf("%lf", &amount);
    clearInputBuffer();

    if (amount <= 0) {
        printf("Error: Deposit amount must be positive.\n");
        return;
    }

    account->balance += amount;
    printf("Deposit successful. New Balance: $%.2f\n", account->balance);
}

// Withdraws funds from an account
void withdraw() {
    int accNum;
    double amount;

    printf("Enter Account Number: ");
    scanf("%d", &accNum);
    clearInputBuffer();

    Account *account = findAccount(accNum);
    if (account == NULL) {
        printf("Error: Account not found.\n");
        return;
    }

    printf("Enter Amount to Withdraw: ");
    scanf("%lf", &amount);
    clearInputBuffer();

    if (amount <= 0) {
        printf("Error: Withdrawal amount must be positive.\n");
        return;
    }

    if (amount > account->balance) {
        printf("Error: Insufficient funds. Current Balance: $%.2f\n", account->balance);
        return;
    }

    account->balance -= amount;
    printf("Withdrawal successful. New Balance: $%.2f\n", account->balance);
}

// Checks the balance of an account
void checkBalance() {
    int accNum;
    printf("Enter Account Number: ");
    scanf("%d", &accNum);
    clearInputBuffer();

    Account *account = findAccount(accNum);
    if (account == NULL) {
        printf("Error: Account not found.\n");
        return;
    }

    printf("\n--- Account Details ---\n");
    printf("Account Number: %d\n", account->accountNumber);
    printf("Account Holder: %s\n", account->name);
    printf("Current Balance: $%.2f\n", account->balance);
    printf("-----------------------\n");
}

// Transfers funds between two accounts
void transferFunds() {
    int sourceAccNum, destAccNum;
    double amount;

    printf("Enter Your Account Number (Source): ");
    scanf("%d", &sourceAccNum);
    clearInputBuffer();

    printf("Enter Destination Account Number: ");
    scanf("%d", &destAccNum);
    clearInputBuffer();

    if (sourceAccNum == destAccNum) {
        printf("Error: Source and destination accounts cannot be the same.\n");
        return;
    }
    
    Account *sourceAccount = findAccount(sourceAccNum);
    if (sourceAccount == NULL) {
        printf("Error: Source account not found.\n");
        return;
    }
    
    Account *destAccount = findAccount(destAccNum);
    if (destAccount == NULL) {
        printf("Error: Destination account not found.\n");
        return;
    }

    printf("Enter Amount to Transfer: ");
    scanf("%lf", &amount);
    clearInputBuffer();

    if (amount <= 0) {
        printf("Error: Transfer amount must be positive.\n");
        return;
    }
    
    if (amount > sourceAccount->balance) {
        printf("Error: Insufficient funds in source account. Current Balance: $%.2f\n", sourceAccount->balance);
        return;
    }

    sourceAccount->balance -= amount;
    destAccount->balance += amount;

    printf("Transfer successful!\n");
    printf("Your New Balance: $%.2f\n", sourceAccount->balance);
}


// Deletes a bank account
void deleteAccount() {
    int accNum;
    printf("Enter Account Number to Delete: ");
    scanf("%d", &accNum);
    clearInputBuffer();

    Account *current = head;
    Account *prev = NULL;

    while (current != NULL && current->accountNumber != accNum) {
        prev = current;
        current = current->next;
    }

    if (current == NULL) {
        printf("Error: Account not found.\n");
        return;
    }

    char confirm[4];
    printf("Are you sure you want to delete account %d for %s? (yes/no): ", current->accountNumber, current->name);
    fgets(confirm, sizeof(confirm), stdin);
    confirm[strcspn(confirm, "\n")] = 0;

    if (strcmp(confirm, "yes") == 0) {
        if (prev == NULL) { // Account to delete is the head
            head = current->next;
        } else { // Account is in the middle or end
            prev->next = current->next;
        }
        free(current);
        printf("Account deleted successfully.\n");
    } else {
        printf("Account deletion cancelled.\n");
    }
}

// Displays all accounts in the system
void displayAllAccounts() {
    Account *current = head;
    if (current == NULL) {
        printf("No accounts in the system.\n");
        return;
    }

    printf("\n--- All Registered Accounts ---\n");
    while (current != NULL) {
        printf("----------------------------------\n");
        printf("Account Number: %d\n", current->accountNumber);
        printf("Name: %s\n", current->name);
        printf("Address: %s\n", current->address);
        printf("Phone: %s\n", current->phone);
        printf("Balance: $%.2f\n", current->balance);
        current = current->next;
    }
    printf("----------------------------------\n");
}


// Saves all account data to a binary file
void saveAccountsToFile() {
    FILE *file = fopen("accounts.dat", "wb");
    if (file == NULL) {
        perror("Error opening file for writing");
        return;
    }

    Account *current = head;
    while (current != NULL) {
        // We write the struct but not the 'next' pointer itself
        fwrite(current, sizeof(Account) - sizeof(Account*), 1, file);
        current = current->next;
    }

    fclose(file);
    printf("Account data saved successfully.\n");
}


// Loads all account data from a binary file
void loadAccountsFromFile() {
    FILE *file = fopen("accounts.dat", "rb");
    if (file == NULL) {
        // This is normal if the file doesn't exist yet
        printf("No existing account data found. Starting fresh.\n");
        return;
    }

    // Temporary struct to hold data read from file
    Account temp;
    
    // Clear existing list in memory before loading
    while(head != NULL){
        Account* tempNode = head;
        head = head->next;
        free(tempNode);
    }
    
    Account *tail = NULL; // To efficiently add to the end of the list

    while (fread(&temp, sizeof(Account) - sizeof(Account*), 1, file) == 1) {
        Account *newAccount = (Account*) malloc(sizeof(Account));
        if (newAccount == NULL) {
            printf("Memory allocation failed during file load.\n");
            fclose(file);
            return;
        }
        
        // Copy data from temp struct to the new node
        newAccount->accountNumber = temp.accountNumber;
        strcpy(newAccount->name, temp.name);
        strcpy(newAccount->address, temp.address);
        strcpy(newAccount->phone, temp.phone);
        newAccount->balance = temp.balance;
        newAccount->next = NULL;

        // Add the new account to our linked list
        if (head == NULL) {
            head = newAccount;
            tail = newAccount;
        } else {
            tail->next = newAccount;
            tail = newAccount;
        }

        // Keep track of the highest account number to avoid reuse
        if (newAccount->accountNumber > latestAccountNumber) {
            latestAccountNumber = newAccount->accountNumber;
        }
    }

    fclose(file);
    printf("Account data loaded successfully.\n");
}