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



void  get_vehicle_rate() {
    FILE *file = fopen("prices.txt", "r");
    if (file == NULL) {
        printf("No previous records found.\n");
        return;
    }
        char line[200];
    printf("\n\t\t\tParking Records:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

float calculate_fee(Vehicle v) {
    float total_fee = v.hours * v.rate;
    if (v.parked_hours > v.hours) {
        int extra_hours = v.parked_hours - v.hours;
        total_fee += extra_hours * (v.rate * 1.5); // Fine for exceeding time
    }
    return total_fee;
}

void save_to_file(Vehicle v) {
    FILE *file = fopen("parking_records.txt", "a");
    if (file == NULL) {
        printf("Error opening file.\n");
        return;
    }
    fprintf(file, "\n\n\t\t\tVehicle Number: %s,\n\t\t\t Type: %s,\n\t\t\t Allocated Hours: %d,\n\t\t\t Actual Hours Parked: %d,\n\t\t\t Total Fee: %.2f\n",
            v.vehicle_number, v.type, v.hours, v.parked_hours, v.total_fee);
    fclose(file);
}

void display_records() {
    FILE *file = fopen("parking_records.txt", "r");
    if (file == NULL) {
        printf("No previous records found.\n");
        return;
    }
    char line[200];
    printf("\nParking Records:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

int login() {
    char username[20], password[20];

    printf("=== Parking Fee Management System ===\n");
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    scanf("%s", password);

    if ((strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) ||
        (strcmp(username, "user") == 0 && strcmp(password, "user123") == 0)) {
        printf("Login successful!\n");
        return 1;
    } else {
        printf("Login failed! Exiting.\n");
        return 0;
    }
}


int main() {

    if (!login())
        return 0;

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

    v.total_fee = calculate_fee(v);

    printf("\nParking Ticket:\n");
    printf("Vehicle Number: %s\n", v.vehicle_number);
    printf("Vehicle Type: %s\n", v.type);
    printf("Allocated Hours: %d\n", v.hours);
    printf("Actual Hours Parked: %d\n", v.parked_hours);
    printf("Total Fee: %.2f\n", v.total_fee);

    save_to_file(v);

    printf("\nDo you want to view all parking records? (1 for Yes, 0 for No): ");
    scanf("%d", &choice);
    if (choice == 1) {
        display_records();
    }

    return 0;
}
