#include <stdio.h>
#include <stdlib.h>
#define MAX_BOOKED_FLIGHTS 10

typedef struct {
    char flight_no[10];
    char airlines[50];
    char origin[50];
    char destination[50];
    char departure_time[20];
    char arrival_time[20];
    int flight_hours;
    float price;
    int seats_left;
    int seats_booked;
} Flight;

Flight booked_flights[MAX_BOOKED_FLIGHTS];
int num_booked_flights = 0;

// Function to read flights from a file
void load_flights(const char *filename) {
    FILE *file = fopen(filename, "r");
    if (!file) {
        printf("Cannot open file %s\n", filename);
        return;
    }

    while (fscanf(file, "%[^,],%[^,],%[^,],%[^,],%[^,],%[^,],%d,%f,%d,%d",
                   booked_flights[num_booked_flights].flight_no,
                   booked_flights[num_booked_flights].airlines,
                   booked_flights[num_booked_flights].origin,
                   booked_flights[num_booked_flights].destination,
                   booked_flights[num_booked_flights].departure_time,
                   booked_flights[num_booked_flights].arrival_time,
                   &booked_flights[num_booked_flights].flight_hours,
                   &booked_flights[num_booked_flights].price,
                   &booked_flights[num_booked_flights].seats_left,
                   &booked_flights[num_booked_flights].seats_booked) == 10) {
        num_booked_flights++;
    }

    fclose(file);
}

// Function to write booked flights to a file
void save_flights(const char *filename) {
    FILE *file = fopen(filename, "w");
    if (!file) {
        printf("Cannot open file %s\n", filename);
        return;
    }

    for (int i = 0; i < num_booked_flights; ++i) {
        fprintf(file, "%s,%s,%s,%s,%s,%s,%d,%.2f,%d,%d\n",
                booked_flights[i].flight_no,
                booked_flights[i].airlines,
                booked_flights[i].origin,
                booked_flights[i].destination,
                booked_flights[i].departure_time,
                booked_flights[i].arrival_time,
                booked_flights[num_booked_flights].flight_hours,
                booked_flights[num_booked_flights].price,
                booked_flights[num_booked_flights].seats_left,
                booked_flights[num_booked_flights].seats_booked);
    }

    fclose(file);
}

// Function to display available flights
void display_flights() {
    if (num_booked_flights == 0) {
        printf("No flights are currently available.\n");
        return;
    }

    printf("\nAvailable Flights:\n");
    for (int i = 0; i < num_booked_flights; ++i) {
        printf("%d. Flight No: %s, Airlines: %s, Origin: %s, Destination: %s, Departure Time: %s, Arrival Time: %s, Flight Hours: %d, Price: %.2f\n",
               i + 1,
               booked_flights[i].flight_no,
               booked_flights[i].airlines,
               booked_flights[i].origin,
               booked_flights[i].destination,
               booked_flights[i].departure_time,
               booked_flights[i].arrival_time,
               booked_flights[i].flight_hours,
               booked_flights[i].price);
    }
}

// Function to add a new flight
void book_flight() {
    if (num_booked_flights >= MAX_BOOKED_FLIGHTS) {
        printf("Cannot book more flights, database is full.\n");
        return;
    }

    display_flights();

    int choice;
    printf("Enter the number of the flight you want to book: ");
    scanf("%d", &choice);

    if (choice < 1 || choice > num_booked_flights) {
        printf("Invalid choice. Please try again.\n");
        return;
    }

    // Decrease seats left and increase seats booked
    booked_flights[choice - 1].seats_left--;
    booked_flights[choice - 1].seats_booked++;

    printf("\nFlight booked successfully!\n");
}

// Function to delete a booked flight
void delete_flight() {
    char flight_no[10];
    printf("Enter Flight No of the flight you want to delete: ");
    scanf("%s", flight_no);
    for (int i = 0; i < num_booked_flights; ++i) {
        if (strcmp(booked_flights[i].flight_no, flight_no) == 0) {
            for (int j = i; j < num_booked_flights - 1; ++j) {
                booked_flights[j] = booked_flights[j + 1];
            }
            --num_booked_flights;
            printf("Flight deleted successfully.\n");
            save_flights("flights.txt");
            return;
        }
    }
    printf("No flight found with this Flight No.\n");
}

// Function to view all booked flights
void view_flights() {
    if (num_booked_flights == 0) {
        printf("No flights are currently booked.\n");
        return;
    }

    for (int i = 0; i < num_booked_flights; ++i) {
        printf("%s, %s, %s, %s, %s, %s, %d, %.2f,%d,%d\n",
               booked_flights[i].flight_no,
               booked_flights[i].airlines,
               booked_flights[i].origin,
               booked_flights[i].destination,
               booked_flights[i].departure_time,
               booked_flights[i].arrival_time,
               booked_flights[i].flight_hours,
               booked_flights[i].price,
               booked_flights[i].seats_left,
               booked_flights[i].seats_booked);
    }
}

// Function to print a single flight ticket
void print_ticket() {
    char flight_no[10];
    printf("Enter Flight No of the flight you want to print the ticket for: ");
    scanf("%s", flight_no);
    for (int i = 0; i < num_booked_flights; ++i) {
        if (strcmp(booked_flights[i].flight_no, flight_no) == 0) {
            printf("Flight No: %s\nAirlines: %s\nOrigin: %s\nDestination: %s\nDeparture Time: %s\nArrival Time: %s\nFlight Hours: %d\nPrice: %.2f\nSeats Left: %d\nSeats Booked: %d\n",
                   booked_flights[i].flight_no,
                   booked_flights[i].airlines,
                   booked_flights[i].origin,
                   booked_flights[i].destination,
                   booked_flights[i].departure_time,
                   booked_flights[i].arrival_time,
                   booked_flights[i].flight_hours,
                   booked_flights[i].price,
                   booked_flights[i].seats_left,
                   booked_flights[i].seats_booked);
            return;
        }
    }
    printf("No flight found with this Flight No.\n");
}

int main() {
    load_flights("allFlights.txt");

    while (1) {
        printf("\nFlight Booking System\n");
        printf("1. Book a new flight\n");
        printf("2. Delete a booked flight\n");
        printf("3. View booked flights\n");
        printf("4. Print flight ticket\n");
        printf("5. Quit\n");
        int choice;
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                book_flight();
                save_flights("flights.txt");
                break;
            case 2:
                delete_flight();
                break;
            case 3:
                view_flights();
                break;
            case 4:
                print_ticket();
                break;
            case 5:
                save_flights("flights.txt");
                exit(0);
            default:
                printf("Invalid choice, please try again.\n");
        }
    }

    return 0;
}
