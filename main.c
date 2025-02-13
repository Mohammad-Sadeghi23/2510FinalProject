//
// Created by Mohammad Sadeghi & Ted Ip on 2025-02-06.
// Purpose: To design and write a program that implements a simple, functional system for managing patient data and doctor schedules in a hospital.

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 50
#define MAX_NAME_LENGTH 50
#define DAYS_IN_WEEK 7
#define SHIFTS_PER_DAY 3

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
void displaySchedule(char schedule[DAYS_IN_WEEK][SHIFTS_PER_DAY][MAX_NAME_LENGTH]);

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
    do {
        printf("Enter Patient ID (positive number): ");
        scanf("%d", &id);
        getchar(); // Consumes newline
    } while (id <= 0);

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
        getchar(); // Consumes newline
    } while (age <= 0);

    // getting the patients diagnosis
    printf("Enter Patient Diagnosis: ");
    fgets(diagnosis, 100, stdin);
    diagnosis[strcspn(diagnosis,"\n")] = 0; // Remove newline

    // getting the patients room number
    do {
        printf("Enter Patients Room Number (positive number): ");
        scanf("%d", &roomNum);
        getchar(); // Consumes newline
    } while (roomNum <= 0);

    // inputting values of new patient into arrays
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
        printf("No Patient Records.\n");
        return;
    }

    puts("\nPatient found:\n");
    printf("| %-5s | %-20s | %-3s | %-25s | %-6s |\n",
           "ID", "Name", "Age", "Diagnosis", "Room #");
    for (int i = 0; i < totalPatients; ++i) {
        printf("| %-5d | %-20s | %-3d | %-25s | %-6d |\n",
               patientsIDs[i], patientsNames[i], patientsAge[i], patientsDiagnosis[i], roomNumber[i]);
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
        puts("\nPatient found:\n");
        printf("| %-5s | %-20s | %-3s | %-25s | %-6s |\n",
               "ID", "Name", "Age", "Diagnosis", "Room #");
        printf("| %-5d | %-20s | %-3d | %-25s | %-6d |\n",
               patientsIDs[index], patientsNames[index], patientsAge[index], patientsDiagnosis[index], roomNumber[index]);
    } else {
        printf("Patient not found\n");
    }
}

void dischargePatient() {
    int discharge_id;
    printf("Enter Patient ID to discharge: ");
    scanf("%d", &discharge_id);

    // loop through and find index of discharge patient
    // shift elements of all arrays down one
    // so no there are no empty elements in middle of arrays
    for (int i = 0; i < totalPatients; i++) {
        if (patientsIDs[i] == discharge_id) {
            for (int j = i; j < totalPatients - 1; j++) {
                patientsIDs[j] = patientsIDs[j + 1];
                strcpy(patientsNames[j], patientsNames[j + 1]);
                patientsAge[j] = patientsAge[j + 1];
                strcpy(patientsDiagnosis[j], patientsDiagnosis[j + 1]);
                roomNumber[j] = roomNumber[j + 1];
            }
            totalPatients--;  // Reduce patient count
            printf("Patient discharged successfully!\n");
            return;  // Exit function after discharge
        }
    }
    printf("Patient ID not found.\n");
}

void manageDoctorSchedule() {
        char schedule[DAYS_IN_WEEK][SHIFTS_PER_DAY][MAX_NAME_LENGTH] = {{"", "", ""},
                                                                    {"", "", ""},
                                                                    {"", "", ""},
                                                                    {"", "", ""},
                                                                    {"", "", ""},
                                                                    {"", "", ""},
                                                                    {"", "", ""}};

    char doctorName[MAX_NAME_LENGTH];
    int day, shift, choice;

    do {
        printf("Doctor Schedule Management System\n");
        printf("1. Assign a doctor to a shift\n");
        printf("2. Display weekly schedule\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                // Assign a doctor to a shift
                printf("Enter the day of the week (1=Monday, 7=Sunday): ");
                scanf("%d", &day);
                printf("Enter the shift (1=Morning, 2=Afternoon, 3=Evening): ");
                scanf("%d", &shift);
                printf("Enter the doctor's name: ");
                getchar();  // Consume the newline character from previous input
                fgets(doctorName, MAX_NAME_LENGTH, stdin);
                doctorName[strcspn(doctorName, "\n")] = '\0';  // Remove newline character from input

                // Assign the doctor to the specific shift and day
                if (day >= 1 && day <= 7 && shift >= 1 && shift <= 3) {
                    strcpy(schedule[day - 1][shift - 1], doctorName);
                    printf("Doctor %s assigned to shift %d on day %d.\n", doctorName, shift, day);
                } else {
                    printf("Invalid day or shift number!\n");
                }
                break;

            case 2:
                // Display the schedule
                displaySchedule(schedule);
                break;

            case 3:
                // Exit the program
                printf("Exiting...\n");
                break;

            default:
                printf("Invalid choice! Please try again.\n");
        }
    } while (choice != 3);
}

void displaySchedule(char schedule[DAYS_IN_WEEK][SHIFTS_PER_DAY][MAX_NAME_LENGTH]) {
    // Array of days for displaying
    const char *daysOfWeek[] = {
        "Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"
};

    printf("\nWeekly Doctor Schedule:\n");
    printf("--------------------------------------------\n");

    // Print the schedule for each day
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%s:\n", daysOfWeek[i]);
        for (int j = 0; j < SHIFTS_PER_DAY; j++) {
            printf("  Shift %d: %s\n", j + 1, schedule[i][j]);
        }
        printf("\n");
    }
}

int main(void) {
    menu();
    return 0;
}