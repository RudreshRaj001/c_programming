#include <stdio.h>
#include <time.h>
#include <windows.h>

int main() {
    int hour, minute, second;
    time_t s;
    struct tm* current_time;

    // Get current time
    s = time(NULL);
    current_time = localtime(&s);

    hour = current_time->tm_hour;
    minute = current_time->tm_min;
    second = current_time->tm_sec;
    
    while (1) {
        // Clear the console
        system("cls");

        // Print the current time
        printf("Current Time: %02d : %02d : %02d\n", hour, minute, second);

        // Increment second
        second++;

        // Update minute and hour
        if (second == 60) {
            minute++;
            second = 0;
        }
        if (minute == 60) {
            hour++;
            minute = 0;
        }
        if (hour == 24) {
            hour = 0;
        }

        // Sleep for 1 second
        Sleep(1000);
    }

    return 0;
}
