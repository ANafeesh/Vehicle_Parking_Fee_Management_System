#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
    char vehicle_number[20];
    char type[20];
    int hours;
    float rate;
    int parked_hours;
    float total_fee;
} Vehicle;

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
void  get_vehicle_rate() {
    FILE *file = fopen("prices.txt", "r");
    if (file == NULL) {
        printf("No previous records found in the system.\n");
        return;
    }
        char line[200];
    printf("\n\t\t\tParking Records:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

int main(){

if (!login()) return 0;

get_vehicle_rate();
}
