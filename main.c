//
// Created by Mohammad Sadeghi & Ted Ip on 2025-02-06.
// Purpose: To design and write a program that implements a simple, functional system for managing patient data and doctor schedules in a hospital.

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 50

int patientsIDs[MAX_PATIENTS] = {0};
int patientsAge[MAX_PATIENTS] = {0};
char patientsNames[MAX_PATIENTS][50];
char patientsDiagnosis[MAX_PATIENTS][100];
int roomNumber[MAX_PATIENTS] = {0};

// function prototypes
void addPatient();
void viewPatient();
void searchPatient();
void dischargePatient();
void manageDoctorSchedule();

void menu() {
    int choice;
    do {
        printf("\nLibrary Management System\n");
        printf("1. Add a New Patient Record\n");
        printf("2. View All Patient Records\n");
        printf("3. Search for a Patient\n");
        printf("4. Discharge a Patient\n");
        printf("5. Manage Doctor Schedule\n");
        printf("6. Exit\n");
        printf("enter you choice: ");
        scanf("%d", &choice);
        getchar(); // Consume newline

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatient(); break;
            case 3: searchPatient(); break;
            case 4: dischargePatient(); break;
            case 5: manageDoctorSchedule(); break;
            case 6: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 6);
}

void addPatient() {
    puts("Added a patient.");
}

void viewPatient() {
    puts("Viewing all patient.");
}

void searchPatient() {
    puts("Searching for a patient.");
}

void dischargePatient() {
    puts("Discharging a patient.");
}

void manageDoctorSchedule() {
    puts("Managing doctors schedule.");
}







int main(void) {
    menu();
    return 0;
}