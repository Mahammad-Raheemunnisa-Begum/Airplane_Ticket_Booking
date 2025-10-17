#include <stdio.h>
#include <string.h>

#define MAX_FLIGHTS 5
#define MAX_SEATS 10

typedef struct {
    int flightID;
    char origin[20];
    char destination[20];
    char departureTime[10];
    int seatsAvailable;
    int bookedSeats[MAX_SEATS];
} Flight;

typedef struct {
    int bookingID;
    int flightID;
    char passengerName[50];
    int seatNumber;
} Booking;

Flight flights[MAX_FLIGHTS];
Booking bookings[MAX_FLIGHTS * MAX_SEATS];
int bookingCount = 0;

void initFlights() {
    flights[0] = (Flight){101, "New York", "London", "09:00AM", MAX_SEATS, {0}};
    flights[1] = (Flight){102, "London", "Paris", "11:30AM", MAX_SEATS, {0}};
    flights[2] = (Flight){103, "Paris", "Rome", "02:00PM", MAX_SEATS, {0}};
    flights[3] = (Flight){104, "Tokyo", "Sydney", "04:00PM", MAX_SEATS, {0}};
    flights[4] = (Flight){105, "Dubai", "Mumbai", "06:30PM", MAX_SEATS, {0}};
}

void printFlights() {
    printf("Available Flights:\n");
    printf("ID\tOrigin\t\tDestination\tDeparture\tSeats Available\n");
    for (int i = 0; i < MAX_FLIGHTS; i++) {
        printf("%d\t%-10s\t%-10s\t%s\t%d\n",
               flights[i].flightID,
               flights[i].origin,
               flights[i].destination,
               flights[i].departureTime,
               flights[i].seatsAvailable);
    }
}

int findFlightIndexByID(int flightID) {
    for (int i = 0; i < MAX_FLIGHTS; i++) {
        if (flights[i].flightID == flightID)
            return i;
    }
    return -1;
}

int findAvailableSeat(Flight *flight) {
    for (int i = 0; i < MAX_SEATS; i++) {
        if (flight->bookedSeats[i] == 0)
            return i + 1; // seat numbers start from 1
    }
    return -1;
}

void bookTicket() {
    int flightID;
    char name[50];

    printFlights();
    printf("Enter Flight ID to book: ");
    scanf("%d", &flightID);
    int fIndex = findFlightIndexByID(flightID);
    if (fIndex == -1) {
        printf("Flight ID not found.\n");
        return;
    }
    if (flights[fIndex].seatsAvailable == 0) {
        printf("No seats available on this flight.\n");
        return;
    }
    printf("Enter Passenger Name: ");
    getchar(); // consume newline left by scanf
    fgets(name, sizeof(name), stdin);
    name[strcspn(name, "\n")] = 0; // remove newline

    int seatNum = findAvailableSeat(&flights[fIndex]);
    if (seatNum == -1) {
        printf("Unexpected error: no available seat found.\n");
        return;
    }

    flights[fIndex].bookedSeats[seatNum - 1] = 1;
    flights[fIndex].seatsAvailable--;

    bookings[bookingCount].bookingID = bookingCount + 1;
    bookings[bookingCount].flightID = flightID;
    strcpy(bookings[bookingCount].passengerName, name);
    bookings[bookingCount].seatNumber = seatNum;
    bookingCount++;

    printf("Booking successful! Your Booking ID is %d\n", bookingCount);
}

void printTicket() {
    int bookingID;
    printf("Enter Booking ID to print ticket: ");
    scanf("%d", &bookingID);

    if (bookingID < 1 || bookingID > bookingCount) {
        printf("Invalid Booking ID.\n");
        return;
    }

    Booking *b = &bookings[bookingID - 1];
    int fIndex = findFlightIndexByID(b->flightID);
    if (fIndex == -1) {
        printf("Flight details not found.\n");
        return;
    }

    Flight *f = &flights[fIndex];
    printf("\n----- TICKET -----\n");
    printf("Booking ID: %d\n", b->bookingID);
    printf("Passenger: %s\n", b->passengerName);
    printf("Flight ID: %d\n", f->flightID);
    printf("From: %s\n", f->origin);
    printf("To: %s\n", f->destination);
    printf("Departure: %s\n", f->departureTime);
    printf("Seat Number: %d\n", b->seatNumber);
    printf("------------------\n\n");
}

void menu() {
    int choice;
    do {
        printf("Airplane Ticket Booking System\n");
        printf("1. Show Available Flights\n");
        printf("2. Book Ticket\n");
        printf("3. Print Ticket\n");
        printf("4. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1: printFlights(); break;
            case 2: bookTicket(); break;
            case 3: printTicket(); break;
            case 4: printf("Exiting...\n"); break;
            default: printf("Invalid choice.\n");
        }
    } while (choice != 4);
}

int main() {
    initFlights();
    menu();
    return 0;
}