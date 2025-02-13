//
// Created by Mohammad Sadeghi & Ted Ip on 2025-02-06.
// Purpose: To design and write a program that implements a simple, functional system for managing patient data and doctor schedules in a hospital.

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 50
#define MAX_NAME_LENGTH 50

int patientsIDs[MAX_PATIENTS] = {0};
int patientsAge[MAX_PATIENTS] = {0};
char patientsNames[MAX_PATIENTS][MAX_NAME_LENGTH];
char patientsDiagnosis[MAX_PATIENTS][100];
int roomNumber[MAX_PATIENTS] = {0};
int totalPatients = 0;

// function prototypes
void addPatient();
int idExists(int arr[], int size, int id);
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

    // check if hospital is full
    if (totalPatients >= MAX_PATIENTS) {
        printf("Hospital is full! Cannot add more patients.\n");
        return;
    }

    int id;
    char name[50];
    int age;
    char diagnosis[50];
    int roomNum;

    // getting patients id
    printf("Enter Patient ID (positive number): ");
    scanf("%d", &id);
    getchar(); // Consumes newline

    // make sure the id is unique
    if (id <= 0 || idExists(patientsIDs, totalPatients, id) != -1) {
        printf("Invalid or duplicate Patient ID!\n");
        return;
    }

    // getting the patients name
    printf("Enter Patient Name: ");
    fgets(name, 50, stdin);
    name[strcspn(name,"\n")] = 0; // Remove newline

    // getting the patients age
    do {
        printf("Enter Patients Age (positive number): ");
        scanf("%d", &age);
    } while (age <= 0);

    getchar(); // Consumes newline

    // getting the patients diagnosis
    printf("Enter Patient Diagnosis: ");
    fgets(diagnosis, 100, stdin);
    diagnosis[strcspn(diagnosis,"\n")] = 0; // Remove newline

    // getting the patients room number
    printf("Enter Patients Room Number (positive number): ");
    scanf("%d", &roomNum);
    getchar(); // Consumes newline

    patientsIDs[totalPatients] = id;
    strcpy(patientsNames[totalPatients], name);
    patientsAge[totalPatients] = age;
    strcpy(patientsDiagnosis[totalPatients], diagnosis);
    roomNumber[totalPatients] = roomNum;
    totalPatients++;

    puts("Patient added successfully!\n");
}

int idExists(int arr[], int size, int id) {
    for (int i = 0; i < size; ++i) {
        if (arr[i] == id) {
            return i;
        }
    }
    return -1;
}

void viewPatient() {
    if (totalPatients == 0) {
        printf("No books available.\n");
        return;
    }

    printf("\nHospital Patients:\n");
    printf("ID\tName\t\t\tAge\t\t\tDiagnosis\t\t\tRoom #\n");
    for (int i = 0; i < totalPatients; ++i) {
        printf("%d\t%-20s\t%d\t%-20s\t%d\n", patientsIDs[i], patientsNames[i], patientsAge[i], patientsDiagnosis[i], roomNumber[i]);
    }
}

void searchPatient() {
    int choice, id, index = -1;
    char name[50];

    printf("Search by (1) ID or (2) Title: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Enter Patient ID: ");
        scanf("%d", &id);
        index = idExists(patientsIDs, totalPatients, id);
    } else if (choice == 2) {
        printf("Enter Patient Name: ");
        fgets(name, 50, stdin);
        name[strcspn(name, "\n")] = 0;

        for (int i = 0; i < totalPatients; ++i) {
            if (strcmp(patientsNames[i], name) == 0) {
                index = i;
                break;
            }
        }
    }

    if (index != -1) {
        puts("Patient found:\n");
        printf("ID\tName\t\t\tAge\t\t\tDiagnosis\t\t\tRoom #\n");
        printf("%d\t%-20s\t%d\t%-20s\t%d\n", patientsIDs[index], patientsNames[index], patientsAge[index], patientsDiagnosis[index], roomNumber[index]);
    } else {
        printf("Patient not found\n");
    }
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