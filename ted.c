//
// Created by Mohammad Sadeghi & Ted Ip on 2025-02-06.
// Purpose: To design and write a program that implements a simple, functional system for managing patient data and doctor schedules in a hospital.

#include <stdio.h>
#include <string.h>

#define MAX_PATIENTS 50
#define MAX_NAME_LENGTH 50

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

void displaySchedule();

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
            case 1:
                addPatient();
                break;
            case 2:
                viewPatient();
                break;
            case 3:
                searchPatient();
                break;
            case 4:
                dischargePatient();
                break;
            case 5:
                manageDoctorSchedule();
                break;
            case 6:
                printf("Exiting...\n");
                break;
            default:
                printf("Invalid choice! Try again.\n");
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

//Ted is working on this
void manageDoctorSchedule() {
    puts("Managing doctors schedule.");


#define DAYS_IN_WEEK 7
#define SHIFTS_PER_DAY 3


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


    char schedule[DAYS_IN_WEEK][SHIFTS_PER_DAY][MAX_NAME_LENGTH] = {{"", "", ""},
                                                                    {"", "", ""},
                                                                    {"", "", ""},
                                                                    {"", "", ""},
                                                                    {"", "", ""},
                                                                    {"", "", ""},
                                                                    {"", "", ""}};

    char doctorName[MAX_NAME_LENGTH];
    int day, shift;

    while (1) {
        printf("Doctor Schedule Management System\n");
        printf("1. Assign a doctor to a shift\n");
        printf("2. Display weekly schedule\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        int choice;
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
                printf("Exiting.\n");


            default:
                printf("Invalid choice! Please try again.\n");
        }
    }
}


int main(void) {
    menu();
    return 0;
}