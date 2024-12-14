# Flight Booking System

## Overview

The Flight Booking System is a C program designed to manage and operate a basic flight booking system. This system allows users to book new flights, delete booked flights, view all currently booked flights, print a flight ticket, and quit the program.

## Features

1. **Booking a New Flight**: Users can browse available flights and select one to book.
2. **Deleting a Booked Flight**: Allows users to remove a previously booked flight.
3. **Viewing Booked Flights**: Lists all currently booked flights.
4. **Printing a Flight Ticket**: Generates and saves a printable ticket for a booked flight.
5. **User Interface**: Simple and intuitive menu-driven interface.

## Installation

This program is written in C and requires a C compiler to be installed on your system. The following steps will guide you through the installation process:

1. **Download the Source Code**:
   - Clone this repository or download the source code ZIP file from the provided link.
2. **Compile the Program**:

   ```bash
   gcc main.c -o flight_booking_system
   ```

3. **Run the Program**:
   ```bash
   ./flight_booking_system
   ```

## Usage

The program runs in a command-line interface and provides a menu-driven system for managing flights. Here’s how to use it:

1. **Book a New Flight**:

   - Choose option 1.
   - Select a flight from the available list.
   - Confirm your booking.

2. **Delete a Booked Flight**:

   - Choose option 2.
   - Select a booked flight from the list.
   - Confirm deletion.

3. **View Booked Flights**:

   - Choose option 3 to see all currently booked flights.

4. **Print a Flight Ticket**:

   - Choose option 4 to print a ticket for a booked flight.
   - The ticket will be saved in `TicketPrint.txt`.

5. **Quit the Program**:
   - Choose option 5 to exit the program.

## Data Files

- **allFlights.txt**: Contains all available flights data.
- **bookedFlights.txt**: Stores data of flights that have been booked.

Ensure these files are correctly formatted and located in the same directory as your `flight_booking_system` executable.

## Contributing

Contributions to this project are welcome! If you encounter any issues or have suggestions for improvement, please feel free to open an issue or submit a pull request.

## License

This project is licensed under the MIT License. See the [LICENSE](LICENSE) file for details.

```

**Note:** Please ensure that the `allFlights.txt` and `bookedFlights.txt` files are properly formatted as CSV (Comma Separated Values) with the appropriate headers before running the program. The format should match the expected input in the `loadFlights` function, which is:

flightNo,airline,origin,destination,departureTime,arrivalTime,flightHours,price,seatsLeft,seatsBooked
```
