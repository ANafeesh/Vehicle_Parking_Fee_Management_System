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

    Vehicle v;
    int choice;

    get_vehicle_rate();

    printf("\n\nEnter vehicle number: ");
    scanf("%s", v.vehicle_number);


    printf("Select vehicle type:\n");
    printf("1. Car\n2. Bike\n3. Truck\n4. Three-wheeler\n");
    printf("Enter your choice (1-4): ");
    scanf("%d", &choice);

    switch (choice) {
        case 1:
            strcpy(v.type, "Car");
            v.rate = 50.0;
            break;
        case 2:
            strcpy(v.type, "Bike");
            v.rate = 30.0;
            break;
        case 3:
            strcpy(v.type, "Truck");
            v.rate = 70.0;
            break;
        case 4:
            strcpy(v.type, "Three-wheeler");
            v.rate = 40.0;
            break;
        default:
            printf("Invalid choice. Exiting...\n");
            return 1;
    }

    printf("Enter number of hours you want to park: ");
    scanf("%d", &v.hours);

    printf("Enter actual parked hours: ");
    scanf("%d", &v.parked_hours);


}
