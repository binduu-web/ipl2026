#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Structure for Circle
struct Circle {
    int center_x;      // x-coordinate of center
    int center_y;      // y-coordinate of center
    int radius;        // radius of circle
    char character;    // character used to draw the circle
};

// Function prototypes (4+ functions as required)
void initialize_circle(struct Circle *c, int cx, int cy, int r, char ch);
void create_2d_buffer(char **buffer, int width, int height);
void free_2d_buffer(char **buffer, int height);
void clear_buffer(char **buffer, int width, int height, char fill);
void draw_circle(struct Circle c, char **buffer, int width, int height);
void print_buffer(char **buffer, int width, int height);

int main() {
    // Define buffer dimensions
    int width = 50;
    int height = 30;
    
    // Create circle structure
    struct Circle my_circle;
    
    // Initialize the circle (center at 25,15 with radius 10)
    initialize_circle(&my_circle, 25, 15, 10, '*');
    
    // Create 2D buffer
    char **buffer;
    create_2d_buffer(&buffer, width, height);
    
    // Clear buffer with spaces
    clear_buffer(buffer, width, height, ' ');
    
    // Draw the circle on the buffer
    draw_circle(my_circle, buffer, width, height);
    
    // Print the buffer to screen
    print_buffer(buffer, width, height);
    
    // Free the buffer memory
    free_2d_buffer(buffer, height);
    
    return 0;
}

// Function 1: Initialize circle structure
void initialize_circle(struct Circle *c, int cx, int cy, int r, char ch) {
    c->center_x = cx;
    c->center_y = cy;
    c->radius = r;
    c->character = ch;
}

// Function 2: Create 2D buffer dynamically
void create_2d_buffer(char **buffer[], int width, int height) {
    // Allocate array of row pointers
    *buffer = (char **)malloc(height * sizeof(char *));
    
    // Allocate each row
    for (int i = 0; i < height; i++) {
        (*buffer)[i] = (char *)malloc(width * sizeof(char));
    }
}

// Function 3: Free 2D buffer memory
void free_2d_buffer(char **buffer, int height) {
    for (int i = 0; i < height; i++) {
        free(buffer[i]);
    }
    free(buffer);
}

// Function 4: Clear buffer with fill character
void clear_buffer(char **buffer, int width, int height, char fill) {
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            buffer[y][x] = fill;
        }
    }
}

// Function 5: Draw circle using midpoint circle algorithm
void draw_circle(struct Circle c, char **buffer, int width, int height) {
    int cx = c.center_x;
    int cy = c.center_y;
    int r = c.radius;
    char ch = c.character;
    
    // Midpoint circle algorithm
    int x = r;
    int y = 0;
    int error = 0;
    
    while (x >= y) {
        // Draw 8 symmetrical points
        // Function to plot a point if within bounds
        auto plot_point = [&](int px, int py) {
            if (px >= 0 && px < width && py >= 0 && py < height) {
                buffer[py][px] = ch;
            }
        };
        
        plot_point(cx + x, cy + y);
        plot_point(cx + y, cy + x);
        plot_point(cx - y, cy + x);
        plot_point(cx - x, cy + y);
        plot_point(cx - x, cy - y);
        plot_point(cx - y, cy - x);
        plot_point(cx + y, cy - x);
        plot_point(cx + x, cy - y);
        
        y++;
        error += 1 + 2 * y;
        
        if (2 * (error - x) + 1 > 0) {
            x--;
            error += 1 - 2 * x;
        }
    }
}

// Function 6: Print buffer to screen
void print_buffer(char **buffer, int width, int height) {
    printf("\n");
    printf("=== CIRCLE DRAWN ON 2D BUFFER ===\n\n");
    
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
            printf("%c", buffer[y][x]);
        }
        printf("\n");
    }
    
    printf("\n");
    printf("Circle Details:\n");
    printf("  Center: (%d, %d)\n", buffer[0] ? 0 : 0, 0);  // Placeholder
}