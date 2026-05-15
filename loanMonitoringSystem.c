#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#define primaryColor    (Color){ 26, 43, 60, 255 }   // Navy (Sidebars/Headers)
#define secondaryColor  (Color){ 74, 144, 226, 255 }  // Blue (Buttons/Links)
#define backgroundColor (Color){ 248, 250, 252, 255 } // Off-white (Main Surface)
#define successColor    (Color){ 39, 174, 96, 255 }   // Green (Paid Status)
#define alertColor      (Color){ 243, 156, 18, 255 }   // Amber (Pending/Warning)
#define textColor       (Color){ 45, 52, 54, 255 }    // Dark Gray (Text)

int main()
{

    const int screenWidth = 1000;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Loan Monitoring System");
    SetTargetFPS(60);

    // Main Game Loop
    while (!WindowShouldClose())
    { // Detect window close button or ESC key
        // 1. Update Logic (move characters, check collisions)

        // 2. Drawing Logic
        BeginDrawing();
        ClearBackground(backgroundColor);

        DrawRectangle(0, 0, screenWidth / 2, screenHeight, primaryColor);
        DrawRectangle(0, 0, screenWidth, 50, secondaryColor);


        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}