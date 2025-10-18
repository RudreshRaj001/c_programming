#include <stdio.h>
#include <string.h>
#include <unistd.h> // For usleep

void print_progress_bar(int progress, int total, int bar_width) {
    if (total == 0) { // Avoid division by zero
        return;
    }

    float percentage = (float)progress / total; // Calculate percentage
    int filled_width = (int)(percentage * bar_width); // Number of '#' characters

    printf("\r["); // Move cursor to the beginning of the line and start the bar
    for (int i = 0; i < filled_width; i++) {
        printf("#"); // Print filled part
    }
    for (int i = 0; i < bar_width - filled_width; i++) {
        printf(" "); // Print empty part
    }
    printf("] %3d%%", (int)(percentage * 100)); // Print percentage, padded to 3 digits

    if (progress == total) {
        printf("\n"); // Newline at the end when progress is complete
    }

    fflush(stdout); // Flush the output buffer to ensure immediate display
}

// Example usage (for testing purposes)
int main() {
    int total_steps = 100;
    int bar_width = 50;

    for (int i = 0; i <= total_steps; i++) {
        print_progress_bar(i, total_steps, bar_width);
        usleep(50000); // Simulate some work (50 milliseconds) 
    }

    printf("Task completed!\n");
    return 0;
}