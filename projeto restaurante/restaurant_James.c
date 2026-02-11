/*********** RESTAURANT RESERVATION SYSTEM **************

* TITLE: RESTAURANT RESERVATION SYSTEM
* AUTHOR: [JAMES_ALCON]
* DATE: 2026-02-06
* DESCRIPTION: Algorithm to manage restaurant reservations.
* CONCEPTS: Logical Operators, Conditional Structures, Loops, Data Structures, Functions, Arrays, Matrices, Strings.
*/

#include <stdio.h>
#include <string.h>

#define MAX_RESERVATIONS 100
#define MAX_NAME_LENGTH 50

// Structure to store client information
typedef struct {
    int clientID;
    char name[MAX_NAME_LENGTH];
} Client;

// Structure to store a reservation
typedef struct {
    int clientID;
    int day;
    int month;
    int hour;
    int minute;
} Reservation;

// Arrays to store clients and reservations
Client clients[MAX_RESERVATIONS];
Reservation reservations[MAX_RESERVATIONS];

int totalClients = 0;
int totalReservations = 0;

// Function to search for a client by ID, returns index or -1 if not found
int findClient(int id) {
    for (int i = 0; i < totalClients; i++) {
        if (clients[i].clientID == id) {
            return i;
        }
    }
    return -1;
}

// Function to read an integer with validation using fgets and sscanf
int readInteger(const char* message) {
    char buffer[100];
    int value;
    char extra;

    while (1) {
        printf("%s", message);
        if (fgets(buffer, sizeof(buffer), stdin) == NULL) {
            printf("Invalid input. Please try again.\n");
            continue;
        }
        // Check if input is a valid integer without extra characters
        if (sscanf(buffer, "%d %c", &value, &extra) == 1) {
            return value;
        } else {
            printf("Invalid input. Please enter a valid integer number.\n");
        }
    }
}

// Function to create a reservation
void createReservation() {
    if (totalReservations >= MAX_RESERVATIONS) {
        printf("Reservation limit reached.\n");
        return;
    }

    int id, day, month, hour, minute;
    char name[MAX_NAME_LENGTH];

    id = readInteger("Client ID: ");

    int clientIndex = findClient(id);
    if (clientIndex == -1) {
        // Client does not exist, ask for name and add
        printf("Client Name: ");
        if (fgets(name, sizeof(name), stdin) == NULL) {
            printf("Error reading name.\n");
            return;
        }
        // Remove trailing newline if present
        name[strcspn(name, "\n")] = 0;

        clients[totalClients].clientID = id;
        strncpy(clients[totalClients].name, name, MAX_NAME_LENGTH);
        totalClients++;
    } else {
        // Client exists, use existing name
        strncpy(name, clients[clientIndex].name, MAX_NAME_LENGTH);
    }

    day = readInteger("Reservation day (1-31): ");
    month = readInteger("Reservation month (1-12): ");
    hour = readInteger("Reservation hour (0-23): ");
    minute = readInteger("Reservation minute (0-59): ");

    reservations[totalReservations].clientID = id;
    reservations[totalReservations].day = day;
    reservations[totalReservations].month = month;
    reservations[totalReservations].hour = hour;
    reservations[totalReservations].minute = minute;
    totalReservations++;

    printf("Reservation created for %s on %02d/%02d at %02d:%02d.\n", name, day, month, hour, minute);
}

// Function to list all reservations
void listReservations() {
    if (totalReservations == 0) {
        printf("No reservations registered.\n");
        return;
    }

    printf("List of Reservations:\n");
    for (int i = 0; i < totalReservations; i++) {
        int clientIndex = findClient(reservations[i].clientID);
        if (clientIndex != -1) {
            printf("Client: %s (ID %d) - Date: %02d/%02d - Time: %02d:%02d\n",
                   clients[clientIndex].name,
                   reservations[i].clientID,
                   reservations[i].day,
                   reservations[i].month,
                   reservations[i].hour,
                   reservations[i].minute);
        }
    }
}

// Function to show reservations by client ID
void reservationsByClient() {
    int id = readInteger("Client ID to list reservations: ");

    int clientIndex = findClient(id);
    if (clientIndex == -1) {
        printf("Client with ID %d not found.\n", id);
        return;
    }

    printf("Reservations for client %s (ID %d):\n", clients[clientIndex].name, id);
    int found = 0;
    for (int i = 0; i < totalReservations; i++) {
        if (reservations[i].clientID == id) {
            printf("Date: %02d/%02d - Time: %02d:%02d\n",
                   reservations[i].day,
                   reservations[i].month,
                   reservations[i].hour,
                   reservations[i].minute);
            found = 1;
        }
    }
    if (!found) {
        printf("No reservations found for this client.\n");
    }
}

// Function to show reservations by date
void reservationsByDate() {
    int day = readInteger("Reservation day to list: ");
    int month = readInteger("Reservation month to list: ");

    printf("Reservations for %02d/%02d:\n", day, month);
    int found = 0;
    for (int i = 0; i < totalReservations; i++) {
        if (reservations[i].day == day && reservations[i].month == month) {
            int clientIndex = findClient(reservations[i].clientID);
            if (clientIndex != -1) {
                printf("Client: %s (ID %d) - Time: %02d:%02d\n",
                       clients[clientIndex].name,
                       reservations[i].clientID,
                       reservations[i].hour,
                       reservations[i].minute);
                found = 1;
            }
        }
    }
    if (!found) {
        printf("No reservations found for this date.\n");
    }
}

// User menu
int main() {
    int option;

    do {
        printf("\n--- Sabor in Loop Reservation System ---\n");
        printf("1 - Create reservation\n");
        printf("2 - List reservations\n");
        printf("3 - Reservations by client\n");
        printf("4 - Reservations by date\n");
        printf("0 - Exit\n");
        option = readInteger("Choose an option: ");

        switch (option) {
            case 1:
                createReservation();
                break;
            case 2:
                listReservations();
                break;
            case 3:
                reservationsByClient();
                break;
            case 4:
                reservationsByDate();
                break;
            case 0:
                printf("Exiting the system...\n");
                break;
            default:
                printf("Invalid option. Please try again.\n");
        }
    } while (option != 0);

    return 0;
}
