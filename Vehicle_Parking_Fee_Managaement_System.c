#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>
#include <windows.h> //for color functions

typedef struct {
    char vehicle_number[20];
    char type[20];
    int hours;
    float rate;
    int parked_hours;
    float total_fee;
} Vehicle;

void setColor(int color) {
    SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), color);
}

void printHeader() {
    setColor(11);
    printf("\n========================================================\n");
    setColor(14);
    printf("               VEHICLE PARKING FEE SYSTEM               \n");
    setColor(11);
    printf("========================================================\n\n");
    setColor(15);
}

void get_vehicle_rate() {
    FILE *file = fopen("prices.txt", "r");
    if (file == NULL) {
        printf("No previous rate records found.\n");
        return;
    }
    char line[200];
    printf("\n\t\t\tParking Rates:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void update_rates() {
    FILE *file = fopen("prices.txt", "w");
    float car, bike, truck, three;
    if (file == NULL) {
        printf("Error opening rate file.\n");
        return;
    }

    printf("Enter new rate for Car: ");
    scanf("%f", &car);
    printf("Enter new rate for Bike: ");
    scanf("%f", &bike);
    printf("Enter new rate for Truck: ");
    scanf("%f", &truck);
    printf("Enter new rate for Three-wheeler: ");
    scanf("%f", &three);

    fprintf(file, "Car: %.2f\nBike: %.2f\nTruck: %.2f\nThree-wheeler: %.2f\n", car, bike, truck, three);
    fclose(file);
    printf("Rates updated successfully!\n");
}

float get_rate_by_type(const char *type) {
    FILE *file = fopen("prices.txt", "r");
    float rate = 0.0;
    if (file == NULL) return 0.0;

    char name[50];
    float val;
    while (fscanf(file, "%[^:]: %f\n", name, &val) != EOF) {
        if (strcmp(type, name) == 0) {
            rate = val;
            break;
        }
    }
    fclose(file);
    return rate;
}

float calculate_fee(Vehicle v) {
    float total_fee = v.hours * v.rate;
    if (v.parked_hours > v.hours) {
        int extra_hours = v.parked_hours - v.hours;
        total_fee += extra_hours * (v.rate * 1.5);
    }
    return total_fee;
}

void save_to_file(Vehicle v) {
    FILE *file = fopen("parking_records.txt", "a");
    if (file == NULL) return;
    fprintf(file, "%s,%s,%d,%d,%.2f\n", v.vehicle_number, v.type, v.hours, v.parked_hours, v.total_fee);
    fclose(file);
}

void save_to_individual_file(Vehicle v) {
    char filename[100];
    snprintf(filename, sizeof(filename), "vehicle_%s.txt", v.vehicle_number);
    FILE *file = fopen(filename, "w");
    if (file == NULL) return;

    fprintf(file, "========== Vehicle Record ==========\n");
    fprintf(file, "Vehicle Number     : %s\n", v.vehicle_number);
    fprintf(file, "Vehicle Type       : %s\n", v.type);
    fprintf(file, "Allocated Hours    : %d\n", v.hours);
    fprintf(file, "Actual Hours Parked: %d\n", v.parked_hours);
    fprintf(file, "Total Fee          : %.2f\n", v.total_fee);
    fprintf(file, "====================================\n");

    fclose(file);
}

void display_records() {
    FILE *file = fopen("parking_records.txt", "r");
    if (file == NULL) {
        printf("No records found.\n");
        return;
    }

    char vehicle[20], type[20];
    int hrs, parked;
    float fee;
    printf("\n%-15s %-15s %-10s %-10s %-10s\n", "Vehicle No.", "Type", "Hours", "Parked", "Fee");
    printf("-------------------------------------------------------------\n");

    while (fscanf(file, "%[^,],%[^,],%d,%d,%f\n", vehicle, type, &hrs, &parked, &fee) != EOF) {
        printf("%-15s %-15s %-10d %-10d %.2f\n", vehicle, type, hrs, parked, fee);
    }
    fclose(file);
}

void search_vehicle() {
    char search[20], line[200];
    printf("Enter vehicle number to search: ");
    scanf("%s", search);

    char filename[100];
    snprintf(filename, sizeof(filename), "vehicle_%s.txt", search);
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        printf("No record found for vehicle: %s\n", search);
        return;
    }

    printf("\n--- Vehicle Record ---\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);
    }
    fclose(file);
}

void show_summary() {
    FILE *file = fopen("parking_records.txt", "r");
    if (file == NULL) {
        printf("No data available for summary.\n");
        return;
    }

    int count = 0, car = 0, bike = 0, truck = 0, three = 0;
    float total_fee = 0;
    char vehicle[20], type[20];
    int hrs, parked;
    float fee;

    while (fscanf(file, "%[^,],%[^,],%d,%d,%f\n", vehicle, type, &hrs, &parked, &fee) != EOF) {
        count++;
        total_fee += fee;
        if (strcmp(type, "Car") == 0) car++;
        else if (strcmp(type, "Bike") == 0) bike++;
        else if (strcmp(type, "Truck") == 0) truck++;
        else if (strcmp(type, "Three-wheeler") == 0) three++;
    }

    fclose(file);

    printf("\n--- Parking Summary ---\n");
    printf("Total Vehicles Parked : %d\n", count);
    printf("Total Fee Collected   : %.2f\n", total_fee);
    printf("Cars Parked           : %d\n", car);
    printf("Bikes Parked          : %d\n", bike);
    printf("Trucks Parked         : %d\n", truck);
    printf("Three-wheelers Parked : %d\n", three);
}

int login() {
    char username[20], password[20], ch;
    int i = 0;

    printHeader();
    printf("Username: ");
    scanf("%s", username);
    printf("Password: ");
    while (1) {
        ch = getch();
        if (ch == 13) {
            password[i] = '\0';
            break;
        } else if (ch == 8 && i > 0) {
            i--;
            printf("\b \b");
        } else if (ch != 8) {
            password[i++] = ch;
            printf("*");
        }
    }
    printf("\n");

    setColor(10);
    if ((strcmp(username, "admin") == 0 && strcmp(password, "admin123") == 0) ||
        (strcmp(username, "user") == 0 && strcmp(password, "user123") == 0)) {
        printf("Login successful. Welcome %s!\n", username);
        setColor(15);
        return 1;
    } else {
        setColor(12);
        printf("Log in Failed Invalid credentials!\n");
        setColor(15);
        return 0;
    }
}

void add_vehicle() {
    Vehicle v;
    int typeChoice;

    printf("\nEnter vehicle number: ");
    scanf("%s", v.vehicle_number);

    printf("Select vehicle type:\n");
    printf("1. Car\n2. Bike\n3. Truck\n4. Three-wheeler\n");
    scanf("%d", &typeChoice);

    switch (typeChoice) {
        case 1: strcpy(v.type, "Car"); break;
        case 2: strcpy(v.type, "Bike"); break;
        case 3: strcpy(v.type, "Truck"); break;
        case 4: strcpy(v.type, "Three-wheeler"); break;
        default: printf("Invalid choice\n"); return;
    }

    v.rate = get_rate_by_type(v.type);
    printf("Enter allocated hours: ");
    scanf("%d", &v.hours);
    printf("Enter actual parked hours: ");
    scanf("%d", &v.parked_hours);

    v.total_fee = calculate_fee(v);

    printf("\n--- Ticket ---\n");
    printf("Vehicle Number: %s \n", v.vehicle_number);
    printf("Vehicle Type: (%s)\n", v.type);
    printf("Rate: %.2f\hr\n Allocated: %d\n Parked: %d\n Fee: %.2f\n",
           v.rate, v.hours, v.parked_hours, v.total_fee);
    save_to_file(v);
    save_to_individual_file(v);
}

int main() {
    if (!login())
        return 0;

    int choice;
    while (1) {
        printf("1. Add Vehicle Entry\n");
        printf("2. View All Records\n");
        printf("3. Search Vehicle by Number\n");
        printf("4. Update Parking Rates\n");
        printf("5. Show Summary\n");
        printf("6. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_vehicle(); break;
            case 2: display_records(); break;
            case 3: search_vehicle(); break;
            case 4: update_rates(); break;
            case 5: show_summary(); break;
            case 6: printf("Exiting... Goodbye!\n"); return 0;
            default: printf("Invalid choice. Try again.\n");
        }

        printf("\nPress any key to return to menu...\n");
        getch();
    }

    return 0;
}
