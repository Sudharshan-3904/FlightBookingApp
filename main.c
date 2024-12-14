#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_FLIGHTS 100
#define MAX_STR_LEN 100

typedef struct {
    char flightNo[MAX_STR_LEN];
    char airline[MAX_STR_LEN];
    char origin[MAX_STR_LEN];
    char destination[MAX_STR_LEN];
    char departureTime[MAX_STR_LEN];
    char arrivalTime[MAX_STR_LEN];
    float flightHours;
    float price;
    int seatsLeft;
    int seatsBooked;
} Flight;

void loadFlights(const char *filename, Flight flights[], int *count) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    *count = 0;
    while (fscanf(file, "%[^,], %[^,], %[^,], %[^,], %[^,], %[^,], %f, %f, %d, %d\n",
                  flights[*count].flightNo, flights[*count].airline, flights[*count].origin,
                  flights[*count].destination, flights[*count].departureTime, flights[*count].arrivalTime,
                  &flights[*count].flightHours, &flights[*count].price,
                  &flights[*count].seatsLeft, &flights[*count].seatsBooked) != EOF) {
        (*count)++;
    }

    fclose(file);
}

void saveFlights(const char *filename, Flight flights[], int count) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Error: Could not open file %s\n", filename);
        return;
    }

    for (int i = 0; i < count; i++) {
        fprintf(file, "%s, %s, %s, %s, %s, %s, %.2f, %.2f, %d, %d\n",
                flights[i].flightNo, flights[i].airline, flights[i].origin, flights[i].destination,
                flights[i].departureTime, flights[i].arrivalTime, flights[i].flightHours,
                flights[i].price, flights[i].seatsLeft, flights[i].seatsBooked);
    }

    fclose(file);
}

void viewBookedFlights() {
    Flight flights[MAX_FLIGHTS];
    int count;
    loadFlights("bookedFlights.txt", flights, &count);

    if (count == 0) {
        printf("No booked flights available.\n");
        return;
    }

    printf("Booked Flights:\n");
    for (int i = 0; i < count; i++) {
        printf("%d. %s (%s) - %s to %s\n",
               i + 1, flights[i].flightNo, flights[i].airline,
               flights[i].origin, flights[i].destination);
    }
}

void bookNewFlight() {
    Flight allFlights[MAX_FLIGHTS], bookedFlights[MAX_FLIGHTS];
    int allCount, bookedCount;
    loadFlights("allFlights.txt", allFlights, &allCount);
    loadFlights("bookedFlights.txt", bookedFlights, &bookedCount);

    if (allCount == 0) {
        printf("No available flights to book.\n");
        return;
    }

    printf("Available Flights:\n");
    for (int i = 0; i < allCount; i++) {
        printf("%d. %s (%s) - %s to %s, $%.2f, Seats Left: %d\n",
               i + 1, allFlights[i].flightNo, allFlights[i].airline,
               allFlights[i].origin, allFlights[i].destination,
               allFlights[i].price, allFlights[i].seatsLeft);
    }

    int choice;
    printf("Enter the number of the flight you want to book: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > allCount) {
        printf("Invalid choice.\n");
        return;
    }

    Flight *selectedFlight = &allFlights[choice - 1];
    if (selectedFlight->seatsLeft == 0) {
        printf("No seats left on this flight.\n");
        return;
    }

    selectedFlight->seatsLeft--;
    selectedFlight->seatsBooked++;

    bookedFlights[bookedCount++] = *selectedFlight;

    saveFlights("allFlights.txt", allFlights, allCount);
    saveFlights("bookedFlights.txt", bookedFlights, bookedCount);

    printf("Flight booked successfully!\n");
}

void deleteBookedFlight() {
    Flight bookedFlights[MAX_FLIGHTS];
    int bookedCount;
    loadFlights("bookedFlights.txt", bookedFlights, &bookedCount);

    if (bookedCount == 0) {
        printf("No booked flights to delete.\n");
        return;
    }

    printf("Booked Flights:\n");
    for (int i = 0; i < bookedCount; i++) {
        printf("%d. %s (%s) - %s to %s\n",
               i + 1, bookedFlights[i].flightNo, bookedFlights[i].airline,
               bookedFlights[i].origin, bookedFlights[i].destination);
    }

    int choice;
    printf("Enter the number of the flight you want to delete: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > bookedCount) {
        printf("Invalid choice.\n");
        return;
    }

    for (int i = choice - 1; i < bookedCount - 1; i++) {
        bookedFlights[i] = bookedFlights[i + 1];
    }

    bookedCount--;
    saveFlights("bookedFlights.txt", bookedFlights, bookedCount);

    printf("Flight deleted successfully!\n");
}

void printFlightTicket() {
    Flight bookedFlights[MAX_FLIGHTS];
    int bookedCount;
    loadFlights("bookedFlights.txt", bookedFlights, &bookedCount);

    if (bookedCount == 0) {
        printf("No booked flights to print.\n");
        return;
    }

    printf("Booked Flights:\n");
    for (int i = 0; i < bookedCount; i++) {
        printf("%d. %s (%s) - %s to %s\n",
               i + 1, bookedFlights[i].flightNo, bookedFlights[i].airline,
               bookedFlights[i].origin, bookedFlights[i].destination);
    }

    int choice;
    printf("Enter the number of the flight ticket to print: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > bookedCount) {
        printf("Invalid choice.\n");
        return;
    }

    Flight *ticket = &bookedFlights[choice - 1];

    FILE *file = fopen("TicketPrint.txt", "w");
    if (!file) {
        printf("Error: Could not open file TicketPrint.txt\n");
        return;
    }

    fprintf(file, "\n======================== FLIGHT TICKET =========================\n");
    fprintf(file, "| Flight No: %-50s |\n", ticket->flightNo);
    fprintf(file, "| Airline: %-52s |\n", ticket->airline);
    fprintf(file, "| Origin: %-53s |\n", ticket->origin);
    fprintf(file, "| Destination: %-48s |\n", ticket->destination);
    fprintf(file, "| Departure: %-50s |\n", ticket->departureTime);
    fprintf(file, "| Arrival: %-52s |\n", ticket->arrivalTime);
    fprintf(file, "| Flight Hours: %-47.2f |\n", ticket->flightHours);
    fprintf(file, "| Price: $%-53.2f |\n", ticket->price);
    fprintf(file, "================================================================\n");

    fclose(file);

    printf("Flight ticket has been printed to TicketPrint.txt\n");
}

int main() {
    int choice;

    do {
        printf("\nFlight Booking System\n");
        printf("1. Book a New Flight\n");
        printf("2. Delete a Booked Flight\n");
        printf("3. View Booked Flights\n");
        printf("4. Print Flight Ticket\n");
        printf("5. Quit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                bookNewFlight();
                break;
            case 2:
                deleteBookedFlight();
                break;
            case 3:
                viewBookedFlights();
                break;
            case 4:
                printFlightTicket();
                break;
            case 5:
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 5);

    return 0;
}
