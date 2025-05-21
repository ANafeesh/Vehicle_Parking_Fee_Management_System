#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int login() {
    char username[20], password[20];

    printf("=== Parking system ===\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    // Hardcoded for now
    if ((strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) ||
        (strcmp(username, "user") == 0 && strcmp(password, "user123") == 0)) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Login failed! Exiting.\n");
        return 0;
    }
}

int main(){

if (!login()) return 0;

}
