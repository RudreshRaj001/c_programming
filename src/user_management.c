#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h> // For INT_MAX
// #include "user_management.h" // This line was causing the error and is now commented out.

// Define constants for user management if user_management.h is not found
#ifndef USER_MANAGEMENT_H
#define USER_MANAGEMENT_H

#define MAX_USERS 100
#define MAX_USERNAME_LEN 50
#define MAX_PASSWORD_LEN 50

typedef struct {
    int user_id;
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
} User;

// Function Prototypes (Good practice even in a single file)
void initialize_users();
int create_user(const char *username, const char *password);
int authenticate_user(const char *username, const char *password);
int delete_user(const char *username);
int update_password(const char *username, const char *new_password);
void list_users();
int save_users_to_file();
int load_users_from_file();
User* get_user_by_id(int user_id);

#endif // USER_MANAGEMENT_H

// Global variables for the user management system
static User users[MAX_USERS];
static int user_count = 0; // Initialize to 0
static int next_user_id = 1; // To ensure unique IDs even after deletion/loading

static const char *USER_FILE = "users.dat";

void initialize_users() {
    load_users_from_file(); // Load users on initialization
}


int create_user(const char *username, const char *password) {
    if (user_count >= MAX_USERS) {
        printf("Error: Maximum number of users reached.\n");
        return 0; // Failure
    }
    if (strlen(username) >= MAX_USERNAME_LEN || strlen(password) >= MAX_PASSWORD_LEN) {
        printf("Error: Username or password too long.\n");
        return 0; // Failure
    }
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            printf("Error: Username already exists.\n");
            return 0; // Failure
        }
    }

    strcpy(users[user_count].username, username);
    strcpy(users[user_count].password, password);
    // Ensure next_user_id is unique and not 0
    if (next_user_id == 0) { // Handle potential overflow or initial state
        next_user_id = 1;
    }
    users[user_count].user_id = next_user_id;
    next_user_id++; // Increment for the next user
    user_count++;
    printf("User '%s' created successfully with ID %d.\n", username, users[user_count - 1].user_id);
    return 1; // Success
}

int authenticate_user(const char *username, const char *password) { // Returns user_id on success, 0 on failure
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0 && strcmp(users[i].password, password) == 0) {
            printf("Authentication successful for user '%s'.\n", username);
            return users[i].user_id; // Return user ID on success
        }
    }
    printf("Authentication failed for user '%s'. Invalid username or password.\n", username);
    return 0; // Failure
}

int delete_user(const char *username) {
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            // Shift remaining users to fill the gap
            for (int j = i; j < user_count - 1; j++) {
                users[j] = users[j+1];
            }
            user_count--;
            printf("User '%s' deleted successfully.\n", username);
            return 1; // Success
        }
    }
    printf("Error: User '%s' not found.\n", username);
    return 0; // Failure
}

int update_password(const char *username, const char *new_password) {
    if (strlen(new_password) >= MAX_PASSWORD_LEN) {
        printf("Error: New password too long.\n");
        return 0; // Failure
    }
    for (int i = 0; i < user_count; i++) {
        if (strcmp(users[i].username, username) == 0) {
            strcpy(users[i].password, new_password);
            printf("Password for user '%s' updated successfully.\n", username);
            return 1; // Success
        }
    }
    printf("Error: User '%s' not found.\n", username);
    return 0; // Failure
}

void list_users() {
    if (user_count == 0) {
        printf("No users registered.\n");
        return;
    }
    printf("--- Registered Users ---\n");
    for (int i = 0; i < user_count; i++) {
        printf("ID: %d, Username: %s\n", users[i].user_id, users[i].username);
    }
    printf("------------------------\n");
}

int save_users_to_file() {
    FILE *file = fopen(USER_FILE, "wb");
    if (file == NULL) {
        perror("Error opening user file for writing");
        return 0; // Failure
    }

    fwrite(&user_count, sizeof(int), 1, file);
    fwrite(&next_user_id, sizeof(int), 1, file); // Save next_user_id
    fwrite(users, sizeof(User), user_count, file);

    fclose(file);
    printf("User data saved to '%s'.\n", USER_FILE);
    return 1; // Success
}

int load_users_from_file() {
    FILE *file = fopen(USER_FILE, "rb");
    if (file == NULL) {
        // This is not an error if the program is run for the first time.
        // perror("Error opening user file for reading (or file does not exist)");
        user_count = 0; // No users loaded
        return 0; // Failure
    }

    // Read user_count and next_user_id
    fread(&user_count, sizeof(int), 1, file);
    fread(&next_user_id, sizeof(int), 1, file);

    if (user_count > MAX_USERS) {
        printf("Warning: User count in file (%d) exceeds MAX_USERS (%d). Loading only first %d users.\n", user_count, MAX_USERS, MAX_USERS);
        fread(users, sizeof(User), MAX_USERS, file);
        user_count = MAX_USERS;
        // Adjust next_user_id if it was read from a file with more users than MAX_USERS
        // Find the maximum ID among loaded users and set next_user_id to max_id + 1
        int max_id = 0;
        for (int i = 0; i < user_count; i++) {
            if (users[i].user_id > max_id) {
                max_id = users[i].user_id;
            }
        }
        next_user_id = max_id + 1;
    } else {
        fread(users, sizeof(User), user_count, file);
    }

    fclose(file);
    printf("User data loaded from '%s'. Total users: %d.\n", USER_FILE, user_count);
    return 1; // Success
}
User* get_user_by_id(int user_id) {
    for (int i = 0; i < user_count; i++) {
        if (users[i].user_id == user_id) {
            return &users[i];
        }
    }
    return NULL; // User not found
}

// Main function for demonstration
int main() {
    initialize_users();

    int choice;
    char username[MAX_USERNAME_LEN];
    char password[MAX_PASSWORD_LEN];
    char new_password[MAX_PASSWORD_LEN];
    int authenticated_user_id = 0; // 0 means no user is authenticated

    do {
        printf("\n--- User Management System ---\n");
        if (authenticated_user_id == 0) {
            printf("1. Create User\n");
            printf("2. Authenticate User\n");
            printf("3. List Users\n");
            printf("4. Save Users to File\n");
            printf("5. Load Users from File\n");
            printf("6. Exit\n");
        } else {
            User* currentUser = get_user_by_id(authenticated_user_id);
            if (currentUser) {
                printf("Logged in as: %s (ID: %d)\n", currentUser->username, currentUser->user_id);
            }
            printf("7. Update Password\n");
            printf("8. Delete User (Self)\n");
            printf("9. Logout\n");
            printf("10. List Users\n"); // Allow listing even when logged in
            printf("11. Save Users to File\n");
            printf("12. Exit\n");
        }
        printf("Enter your choice: ");

        // Input validation for choice
        if (scanf("%d", &choice) != 1) {
            printf("Invalid input. Please enter a number.\n");
            while (getchar() != '\n'); // Clear input buffer
            continue;
        }
        while (getchar() != '\n'); // Clear input buffer

        if (authenticated_user_id == 0) { // Not logged in
            switch (choice) {
                case 1:
                    printf("Enter username: ");
                    fgets(username, sizeof(username), stdin);
                    username[strcspn(username, "\n")] = 0; // Remove newline
                    printf("Enter password: ");
                    fgets(password, sizeof(password), stdin);
                    password[strcspn(password, "\n")] = 0; // Remove newline
                    create_user(username, password);
                    break;
                case 2:
                    printf("Enter username: ");
                    fgets(username, sizeof(username), stdin);
                    username[strcspn(username, "\n")] = 0;
                    printf("Enter password: ");
                    fgets(password, sizeof(password), stdin);
                    password[strcspn(password, "\n")] = 0;
                    authenticated_user_id = authenticate_user(username, password);
                    break;
                case 3:
                    list_users();
                    break;
                case 4:
                    save_users_to_file();
                    break;
                case 5:
                    load_users_from_file();
                    break;
                case 6:
                    printf("Exiting program. Saving user data...\n");
                    save_users_to_file();
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        } else { // Logged in
            User* currentUser = get_user_by_id(authenticated_user_id);
            if (!currentUser) { // Should not happen if authenticated_user_id is valid
                printf("Error: Authenticated user not found. Logging out.\n");
                authenticated_user_id = 0;
                continue;
            }
            switch (choice) {
                case 7:
                    printf("Enter new password: ");
                    fgets(new_password, sizeof(new_password), stdin);
                    new_password[strcspn(new_password, "\n")] = 0;
                    update_password(currentUser->username, new_password);
                    break;
                case 8:
                    printf("Are you sure you want to delete your account '%s'? (yes/no): ", currentUser->username);
                    char confirm[5];
                    fgets(confirm, sizeof(confirm), stdin);
                    confirm[strcspn(confirm, "\n")] = 0;
                    if (strcmp(confirm, "yes") == 0) {
                        delete_user(currentUser->username);
                        authenticated_user_id = 0; // Log out after deletion
                    } else {
                        printf("Account deletion cancelled.\n");
                    }
                    break;
                case 9:
                    printf("Logging out from user '%s'.\n", currentUser->username);
                    authenticated_user_id = 0;
                    break;
                case 10:
                    list_users();
                    break;
                case 11:
                    save_users_to_file();
                    break;
                case 12:
                    printf("Exiting program. Saving user data...\n");
                    save_users_to_file();
                    break;
                default:
                    printf("Invalid choice. Please try again.\n");
            }
        }

    } while ((authenticated_user_id == 0 && choice != 6) || (authenticated_user_id != 0 && choice != 12));

    return 0;
}