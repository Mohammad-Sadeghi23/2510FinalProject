/*
* Created by Mohammad Sadeghi & Ted Ip & ChatGPT on 2025-04-05.
* Purpose: To design and write a program that implements a robust,
 * functional system for managing patient data and doctor schedules in a hospital.
*/
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

#define MAX_NAME_LENGTH 50
#define MAX_DIG_LENGTH 100
#define DAYS_IN_WEEK 7
#define SHIFTS_PER_DAY 3
#define PATIENT_FILE "patients.txt"
#define SCHEDULE_FILE "schedule.txt"

// [PHASE 2 CHANGE] - Define a linked list node for patients
typedef struct Patient {
    int id;
    char name[MAX_NAME_LENGTH];
    int age;
    char diagnosis[MAX_DIG_LENGTH];
    int roomNumber;
    char admissionDate[11]; // [PHASE 2 CHANGE]
    struct Patient *next;
} Patient;

Patient *head = NULL; // [PHASE 2 CHANGE] - Head of the patient linked list
char schedule[DAYS_IN_WEEK][SHIFTS_PER_DAY][MAX_NAME_LENGTH] = {0}; // [PHASE 2 CHANGE] - Moved to global for persistence

void addPatient();
void viewPatients();
void searchPatient();
void dischargePatient();
void manageDoctorSchedule();
void displaySchedule(char schedule[DAYS_IN_WEEK][SHIFTS_PER_DAY][MAX_NAME_LENGTH]);
void saveData(); // [PHASE 2 CHANGE]
void loadData(); // [PHASE 2 CHANGE]
void generateReports(); // [PHASE 2 CHANGE]

void menu() {
    int choice;
    loadData(); // [PHASE 2 CHANGE]
    do {
        printf("\nHospital Management System\n");
        printf("1. Add a New Patient Record\n");
        printf("2. View All Patient Records\n");
        printf("3. Search for a Patient\n");
        printf("4. Discharge a Patient\n");
        printf("5. Manage Doctor Schedule\n");
        printf("6. Save Data\n");
        printf("7. Generate Reports\n");
        printf("8. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1: addPatient(); break;
            case 2: viewPatients(); break;
            case 3: searchPatient(); break;
            case 4: dischargePatient(); break;
            case 5: manageDoctorSchedule(); break;
            case 6: saveData(); break;
            case 7: generateReports(); break; // [PHASE 2 CHANGE]
            case 8: printf("Exiting...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 8);
}

int idExists(int id) {
    Patient *temp = head;
    while (temp) {
        if (temp->id == id) return 1;
        temp = temp->next;
    }
    return 0;
}

void addPatient() {
    Patient *newPatient = (Patient*) malloc(sizeof(Patient)); // [PHASE 2 CHANGE]
    if (!newPatient) {
        printf("Memory allocation failed!\n");
        return;
    }

    printf("Enter Patient ID: ");
    scanf("%d", &newPatient->id);
    getchar();
    if (idExists(newPatient->id)) {
        printf("Duplicate ID!\n");
        free(newPatient);
        return;
    }

    printf("Enter Name: ");
    fgets(newPatient->name, MAX_NAME_LENGTH, stdin);
    newPatient->name[strcspn(newPatient->name, "\n")] = '\0';

    printf("Enter Age: ");
    scanf("%d", &newPatient->age);
    getchar();

    printf("Enter Diagnosis: ");
    fgets(newPatient->diagnosis, MAX_DIG_LENGTH, stdin);
    newPatient->diagnosis[strcspn(newPatient->diagnosis, "\n")] = '\0';

    printf("Enter Room Number: ");
    scanf("%d", &newPatient->roomNumber);
    getchar();

    printf("Enter Admission Date (YYYY-MM-DD): ");
    fgets(newPatient->admissionDate, 11, stdin);
    newPatient->admissionDate[strcspn(newPatient->admissionDate, "\n")] = '\0';

    newPatient->next = head; // [PHASE 2 CHANGE]
    head = newPatient;

    printf("Patient added successfully!\n");
}

void viewPatients() {
    if (!head) {
        printf("No Patient Records.\n");
        return;
    }
    printf("| ID | Name | Age | Diagnosis | Room # |\n");
    Patient *temp = head;
    while (temp) {
        printf("| %d | %s | %d | %s | %d |\n", temp->id, temp->name, temp->age, temp->diagnosis, temp->roomNumber);
        temp = temp->next;
    }
}

void searchPatient() {
    int choice, id;
    char name[MAX_NAME_LENGTH];
    Patient *temp = head;

    printf("Search by (1) ID or (2) Name: ");
    scanf("%d", &choice);
    getchar();

    if (choice == 1) {
        printf("Enter ID: ");
        scanf("%d", &id);
        getchar();
        while (temp) {
            if (temp->id == id) {
                printf("Found: %s, Age %d, Diagnosis: %s, Room %d\n", temp->name, temp->age, temp->diagnosis, temp->roomNumber);
                return;
            }
            temp = temp->next;
        }
    } else if (choice == 2) {
        printf("Enter Name: ");
        fgets(name, MAX_NAME_LENGTH, stdin);
        name[strcspn(name, "\n")] = '\0';
        while (temp) {
            if (strcmp(temp->name, name) == 0) {
                printf("Found: ID %d, Age %d, Diagnosis: %s, Room %d\n", temp->id, temp->age, temp->diagnosis, temp->roomNumber);
                return;
            }
            temp = temp->next;
        }
    }
    printf("Patient not found.\n");
}

void dischargePatient() {
    int id;
    printf("Enter Patient ID to discharge: ");
    scanf("%d", &id);
    getchar();

    Patient *temp = head, *prev = NULL;
    while (temp) {
        if (temp->id == id) {
            if (prev) prev->next = temp->next;
            else head = temp->next;
            free(temp); // [PHASE 2 CHANGE]
            printf("Patient discharged successfully!\n");
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    printf("Patient ID not found.\n");
}

void manageDoctorSchedule() {
    char doctorName[MAX_NAME_LENGTH];
    int day, shift, choice;

    do {
        printf("\nDoctor Schedule Management System\n");
        printf("1. Assign a doctor to a shift\n");
        printf("2. Display weekly schedule\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);
        getchar();

        switch (choice) {
            case 1:
                printf("Enter the day (1-7): ");
                scanf("%d", &day);
                getchar();
                printf("Enter the shift (1-3): ");
                scanf("%d", &shift);
                getchar();
                printf("Enter doctor's name: ");
                fgets(doctorName, MAX_NAME_LENGTH, stdin);
                doctorName[strcspn(doctorName, "\n")] = '\0';
                strcpy(schedule[day - 1][shift - 1], doctorName);
                break;
            case 2:
                displaySchedule(schedule);
                break;
        }
    } while (choice != 3);
}

void displaySchedule(char schedule[DAYS_IN_WEEK][SHIFTS_PER_DAY][MAX_NAME_LENGTH]) {
    const char *days[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        printf("%s: ", days[i]);
        for (int j = 0; j < SHIFTS_PER_DAY; j++) {
            printf("Shift %d: %s\t", j + 1, schedule[i][j]);
        }
        printf("\n");
    }
}

void saveData() {
    FILE *pf = fopen(PATIENT_FILE, "w");
    Patient *temp = head;
    while (temp) {
        fprintf(pf, "%d|%s|%d|%s|%d\n", temp->id, temp->name, temp->age, temp->diagnosis, temp->roomNumber);
        temp = temp->next;
    }
    fclose(pf);

    FILE *sf = fopen(SCHEDULE_FILE, "w");
    for (int i = 0; i < DAYS_IN_WEEK; i++)
        for (int j = 0; j < SHIFTS_PER_DAY; j++)
            fprintf(sf, "%s\n", schedule[i][j]);
    fclose(sf);
}

void loadData() {
    FILE *pf = fopen(PATIENT_FILE, "r");
    if (pf) {
        while (!feof(pf)) {
            Patient *newPatient = malloc(sizeof(Patient));
            if (fscanf(pf, "%d|%[^|]|%d|%[^|]|%d\n", &newPatient->id, newPatient->name, &newPatient->age, newPatient->diagnosis, &newPatient->roomNumber) == 5) {
                newPatient->next = head;
                head = newPatient;
            } else {
                free(newPatient);
                break;
            }
        }
        fclose(pf);
    }

    FILE *sf = fopen(SCHEDULE_FILE, "r");
    if (sf) {
        for (int i = 0; i < DAYS_IN_WEEK; i++)
            for (int j = 0; j < SHIFTS_PER_DAY; j++)
                fgets(schedule[i][j], MAX_NAME_LENGTH, sf);
        for (int i = 0; i < DAYS_IN_WEEK; i++)
            for (int j = 0; j < SHIFTS_PER_DAY; j++)
                schedule[i][j][strcspn(schedule[i][j], "\n")] = '\0';
        fclose(sf);
    }
}

void generateReports() {
    int totalPatients = 0;
    int roomUsage[1000] = {0}; // Assuming room numbers < 1000
    FILE *rf = fopen("report.txt", "w");

    if (!rf) {
        printf("Error opening report file!\n");
        return;
    }

    // Doctor schedule tracking
    const char *days[] = {"Mon", "Tue", "Wed", "Thu", "Fri", "Sat", "Sun"};
    int doctorShifts[DAYS_IN_WEEK][SHIFTS_PER_DAY] = {0};

    // Count total patients, rooms, and print admission dates
    Patient *temp = head;
    fprintf(rf, "--- Report Summary ---\n");
    fprintf(rf, "Admitted Patients:\n");

    while (temp) {
        fprintf(rf, "ID: %d, Name: %s, Age: %d, Diagnosis: %s, Room: %d, Admitted: %s\n",
                temp->id, temp->name, temp->age, temp->diagnosis, temp->roomNumber, temp->admissionDate);
        totalPatients++;
        if (temp->roomNumber > 0 && temp->roomNumber < 1000)
            roomUsage[temp->roomNumber]++;
        temp = temp->next;
    }

    fprintf(rf, "\nTotal Current Patients: %d\n", totalPatients);

    // Room Usage
    fprintf(rf, "\nRoom Usage:\n");
    for (int i = 0; i < 1000; i++) {
        if (roomUsage[i] > 0)
            fprintf(rf, "Room %d: Occupied\n", i);
    }

    // Doctor Schedule
    fprintf(rf, "\nDoctor Shift Assignments:\n");
    for (int i = 0; i < DAYS_IN_WEEK; i++) {
        fprintf(rf, "%s:\t", days[i]);
        for (int j = 0; j < SHIFTS_PER_DAY; j++) {
            fprintf(rf, "Shift %d: %s\t", j + 1, strlen(schedule[i][j]) > 0 ? schedule[i][j] : "Unassigned");
        }
        fprintf(rf, "\n");
    }

    fclose(rf);
    printf("Report successfully generated in 'report.txt'.\n");
}


int main() {
    menu();
    return 0;
}