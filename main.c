//
// Created by Mohammad Sadeghi & Ted Ip on 2025-02-06.
// Purpose: To design and write a program that implements a simple, functional system for managing patient data and doctor schedules in a hospital.

#include <stdio.h>
#include <string.h>
#include <ctype.h>

// Constants
#define MAX_PATIENTS 50
#define MAX_NAME_LENGTH 50
#define MAX_DIG_LENGTH 100
#define DAYS_IN_WEEK 7
#define SHIFTS_PER_DAY 3

// Instance variables
int patientsIDs[MAX_PATIENTS] = {0};
int patientsAge[MAX_PATIENTS] = {0};
char patientsNames[MAX_PATIENTS][MAX_NAME_LENGTH];
char patientsDiagnosis[MAX_PATIENTS][MAX_DIG_LENGTH];
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
        printf("\nHospital Management System\n");
        printf("1. Add a New Patient Record\n");
        printf("2. View All Patient Records\n");
        printf("3. Search for a Patient\n");
        printf("4. Discharge a Patient\n");
        printf("5. Manage Doctor Schedule\n");
        printf("6. Exit\n");
        do {
            printf("Enter your choice: ");

            // Check if the input is an integer
            if (scanf("%d", &choice) != 1) {
                // Clear invalid input (non-integer)
                while (getchar() != '\n'); // consume invalid input until newline is encountered
                printf("Invalid input! Please enter a valid integer.\n");
            } else {
                // Check if the choice is within the valid range
                if (choice <= 0 || choice > 6) {
                    printf("Invalid input! Please enter a valid integer(1 to 6).\n");
                } else {
                    break; // valid input, exit the loop
                }
            }
        } while (1);

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
    char name[MAX_NAME_LENGTH];
    int age;
    char diagnosis[MAX_DIG_LENGTH];
    int roomNum;

    // validating and getting patients id
    do {
        printf("Enter Patient ID (positive number): ");

        // Check if the input is an integer
        if (scanf("%d", &id) != 1) {
            // Clear invalid input (non-integer)
            while (getchar() != '\n'); // consume invalid input until newline is encountered
            printf("Invalid input! Please enter a valid integer.\n");
        } else {
            // Check if the id is a positive integer
            if (id <= 0) {
                printf("Id must be 1 or higher.\n");
            } else {
                getchar(); // Consumes newline
                break; // valid input, exit the loop
            }
        }
    } while (1);

    // make sure the id is unique
    if (id <= 0 || idExists(patientsIDs, totalPatients, id) != -1) {
        printf("Invalid or duplicate Patient ID!\n");
        return;
    }

    // getting the patients name
    do {
        printf("Enter Patient Name: ");
        fgets(name, MAX_NAME_LENGTH, stdin);

        // Remove newline character if it exists
        name[strcspn(name, "\n")] = '\0';

        // Validate if the name contains only alphabetic characters and spaces
        int valid = 1; // Flag to check if the name is valid
        for (int i = 0; name[i] != '\0'; i++) {
            if (!isalpha(name[i]) && name[i] != ' ') {  // Check for invalid characters
                valid = 0;
                break;
            }
        }

        if (valid) {
            printf("\nPatient's name is: %s\n", name);
            break; // Exit loop if the name is valid
        } else {
            printf("Invalid name! Please enter a name with only alphabetic characters and spaces.\n");
        }
    } while (1);

    // Validating and getting the patients age
    do {
        printf("Enter Patient's Age (positive number between 1 and 149): ");

        // Check if the input is an integer
        if (scanf("%d", &age) != 1) {
            // Clear invalid input (non-integer)
            while (getchar() != '\n'); // consume invalid input until newline is encountered
            printf("Invalid input! Please enter a valid integer.\n");
        } else {
            // Check if the age is within the valid range
            if (age <= 0 || age >= 150) {
                printf("Age must be between 1 and 149.\n");
            } else {
                break; // valid input, exit the loop
            }
        }
    } while (1);

    // getting the patients diagnosis
    getchar();
    printf("Enter Patient Diagnosis: ");
    fgets(diagnosis, MAX_DIG_LENGTH, stdin);
    diagnosis[strcspn(diagnosis,"\n")] = 0; // Remove newline

    // validating and getting the patients room number
    do {
        printf("Enter Patients Room Number (positive number): ");

        // Check if the input is an integer
        if (scanf("%d", &roomNum) != 1) {
            // Clear invalid input (non-integer)
            while (getchar() != '\n'); // consume invalid input until newline is encountered
            printf("Invalid input! Please enter a valid integer.\n");
        } else {
            // Check if the age is within the valid range
            if (roomNum < 0) {
                printf("Room number cannot be negative.\n");
            } else {
                getchar(); // Consumes newline
                break; // valid input, exit the loop
            }
        }
    } while (1);

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
    char name[MAX_NAME_LENGTH];

    // Validating and getting the choice
    do {
        printf("Search by (1) ID or (2) Name: ");

        // Check if the input is an integer
        if (scanf("%d", &choice) != 1) {
            // Clear invalid input (non-integer)
            while (getchar() != '\n'); // consume invalid input until newline is encountered
            printf("Invalid input! Please enter a valid integer.\n");
        } else {
            // Check if the choice is within the valid range
            if (choice != 1 && choice != 2) {
                printf("Choice must be 1 or 2.\n");
            } else {
                getchar(); // Consumes newline
                break; // valid input, exit the loop
            }
        }
    } while (1);


    if (choice == 1) {
        // Validating and getting the id
        do {
            printf("Enter Patient ID: ");

            // Check if the input is an integer
            if (scanf("%d", &id) != 1) {
                // Clear invalid input (non-integer)
                while (getchar() != '\n'); // consume invalid input until newline is encountered
                printf("Invalid input! Please enter a valid integer.\n");
            } else {
                // Check if the id is within the valid range
                if (id <= 0) {
                    printf("Id must be 1 or higher.\n");
                } else {
                    index = idExists(patientsIDs, totalPatients, id);
                    break; // valid input, exit the loop
                }
            }
        } while (1);
    }

    else if (choice == 2) {
        printf("Enter Patient Name: ");
        fgets(name, MAX_NAME_LENGTH, stdin);
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

    // Validating and getting the patients id to be discharged
    do {
        printf("Enter Patient ID to discharge: ");

        // Check if the input is an integer
        if (scanf("%d", &discharge_id) != 1) {
            // Clear invalid input (non-integer)
            while (getchar() != '\n'); // consume invalid input until newline is encountered
            printf("Invalid input! Please enter a valid integer.\n");
        } else {
            // Check if the discharge_id is valid
            if (discharge_id <= 0) {
                printf("Id must be 1 or higher.\n");
            } else {
                break; // valid input, exit the loop
            }
        }
    } while (1);

    // loop through and find index of discharge patient
    // shift elements of all arrays down one
    // so there are no empty elements in middle of arrays
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
        printf("\nDoctor Schedule Management System\n");
        printf("1. Assign a doctor to a shift\n");
        printf("2. Display weekly schedule\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");

        // Validating and getting the choice
        do {
            // Check if the input is an integer
            if (scanf("%d", &choice) != 1) {
                // Clear invalid input (non-integer)
                while (getchar() != '\n'); // consume invalid input until newline is encountered
                printf("Invalid input! Please enter a valid integer.\n");
            } else {
                // Check if the id is within the valid range
                if (choice < 1 || choice > 3) {
                    printf("Please choose a choice between 1 and 3.\n");
                } else {
                    getchar(); // Consume new line
                    break; // valid input, exit the loop
                }
            }
        } while (1);

        switch (choice) {
            case 1:
            // Assign a doctor to a shift
            do {
                printf("Enter the day of the week (1=Monday, 7=Sunday): ");
                // Check if the input is an integer
                if (scanf("%d", &day) != 1) {
                    // Clear invalid input (non-integer)
                    while (getchar() != '\n'); // consume invalid input until newline is encountered
                    printf("Invalid input! Please enter a valid integer.\n");
                } else {
                    // Check if the id is within the valid range
                    if (day > 7 || day < 1) {
                        printf("Please choose a choice between 1 and 7.\n");
                    } else {
                        getchar(); // Consume new line
                        break; // valid input, exit the loop
                    }
                }
            } while (1);

                do {
                    printf("Enter the shift (1=Morning, 2=Afternoon, 3=Evening): ");
                    if (scanf("%d", &shift) != 1) {
                        // Clear invalid input (non-integer)
                        while (getchar() != '\n'); // consume invalid input until newline is encountered
                        printf("Invalid input! Please enter a valid integer.\n");
                    }

                } while (shift < 1 || shift>3);

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