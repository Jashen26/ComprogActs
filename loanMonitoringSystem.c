#include <stdio.h>
#include <stdlib.h>
#include <raylib.h>

#define primaryColor (Color){26, 43, 60, 255}            // Navy (Sidebars/Headers)
#define secondaryColor (Color){74, 144, 226, 255}        // Blue (Buttons/Links)
#define secondaryColorClicked (Color){44, 104, 176, 255} // Darker Blue (Clicked)
#define backgroundColor (Color){248, 250, 252, 255}      // Off-white (Main Surface)
#define successColor (Color){39, 174, 96, 255}           // Green (Paid Status)
#define alertColor (Color){243, 156, 18, 255}            // Amber (Pending/Warning)
#define textColor (Color){45, 52, 54, 255}               // Dark Gray (Text)

struct client
{
    char name[50];
    char ocp[50];
    int cvs;
    int phone;
    char email[50];
    float income;
};
struct client details;

typedef enum
{
    clientView,
    paymentView
} leftPanel;

int main()
{
    const int screenWidth = 1000;
    const int screenHeight = 800;
    InitWindow(screenWidth, screenHeight, "Loan Monitoring System");
    SetTargetFPS(60);

    leftPanel activeView = clientView;

    // declaring rectangle(and button)
    Rectangle clientButton = {20, 10, 80, 30};
    Rectangle paymentButton = {120, 10, 108, 30};
    Rectangle nav = {0, 0, (float)screenWidth, 50};
    Rectangle name = {20, 80, 260, 30};
    Rectangle occupation = {20, 135, 260, 30};
    Rectangle civilStatus = {20, 190, 260, 30};
    Rectangle phoneNumber = {20, 245, 260, 30};
    Rectangle email = {20, 300, 260, 30};
    Rectangle income = {20, 355, 260, 30};

    // color for buttons
    Color clientButtonColor = secondaryColorClicked;
    Color paymentButtonColor = secondaryColor;
    Color bgColor = primaryColor;

    // drawing starts
    while (!WindowShouldClose())
    {
        //------------for client / payment button-------------------
        Vector2 mousePos = GetMousePosition();

        if (CheckCollisionPointRec(mousePos, clientButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            clientButtonColor = secondaryColorClicked;
            paymentButtonColor = secondaryColor;
            activeView = clientView;
            // bgColor = BLUE;
        }
        if (CheckCollisionPointRec(mousePos, paymentButton) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
        {
            clientButtonColor = secondaryColor;
            paymentButtonColor = secondaryColorClicked;
            activeView = paymentView;
            // bgColor = BLUE;
        }

        // 2. Drawing Logic
        BeginDrawing();
        ClearBackground(backgroundColor);
        DrawRectangle(0, 0, 300, screenHeight, bgColor); // client/payment ui
        if (activeView == clientView)
        {
            DrawRectangle(20, 80, 260, 30, RAYWHITE); // input name
            DrawRectangleRec(name, RAYWHITE);
            DrawRectangleLinesEx(name, 2.0f, DARKBLUE);
            DrawText("Name:", 20, 66, 15, RAYWHITE);

            DrawRectangle(20, 135, 260, 30, RAYWHITE); // input occupation
            DrawRectangleRec(occupation, RAYWHITE);
            DrawRectangleLinesEx(occupation, 2.0f, DARKBLUE);
            DrawText("Occupation", 20, 119, 15, RAYWHITE);

            DrawRectangle(20, 190, 260, 30, RAYWHITE); // input civil status
            DrawRectangleRec(civilStatus, RAYWHITE);
            DrawRectangleLinesEx(civilStatus, 2.0f, DARKBLUE);
            DrawText("Civil Status", 20, 174, 15, RAYWHITE);

            DrawRectangle(20, 245, 260, 30, RAYWHITE); // input phone number
            DrawRectangleRec(phoneNumber, RAYWHITE);
            DrawRectangleLinesEx(phoneNumber, 2.0f, DARKBLUE);
            DrawText("Phone Number", 20, 229, 15, RAYWHITE);

            DrawRectangle(20, 300, 260, 30, RAYWHITE); // input email
            DrawRectangleRec(email, RAYWHITE);
            DrawRectangleLinesEx(email, 2.0f, DARKBLUE);
            DrawText("Email", 20, 284, 15, RAYWHITE);

            DrawRectangle(20, 355, 260, 30, RAYWHITE); // input income
            DrawRectangleRec(income, RAYWHITE);
            DrawRectangleLinesEx(income, 2.0f, DARKBLUE);
            DrawText("Income", 20, 339, 15, RAYWHITE);
        }
        if (activeView == paymentView)
        {
            //if
            DrawRectangle(20, 80, 260, 30, BLACK);  // input name
            DrawRectangle(20, 135, 260, 30, BLACK); // input occupation
            DrawRectangle(20, 190, 260, 30, BLACK); // input civil status
            DrawRectangle(20, 245, 260, 30, BLACK); // input phone number
            DrawRectangle(20, 300, 260, 30, BLACK); // input email
            DrawRectangle(20, 355, 260, 30, BLACK); // input income
        }

        DrawRectangle(300, 0, 350, screenHeight, RED);  // brwlist/brwreq
        DrawRectangle(300, 50, 350, 50, PINK);          // brwlist
        DrawRectangle(650, 0, 450, screenHeight, BLUE); // admin panel
        DrawRectangle(650, 50, 450, 50, GREEN);

        DrawRectangle(0, 0, screenWidth, 50, primaryColor); // nav
        DrawRectangleRec(nav, primaryColor);
        DrawRectangleLinesEx(nav, 2.0f, DARKBLUE);
        DrawText("Day 1", 935, 20, 20, RAYWHITE);

        DrawRectangle(20, 10, 80, 30, clientButtonColor); // client button
        DrawText("Client", 28, 15, 20, textColor);
        DrawRectangle(120, 10, 108, 30, paymentButtonColor); // payment button
        DrawText("Payment", 128, 15, 20, primaryColor);
        EndDrawing();
    }

    // De-Initialization
    CloseWindow();

    return 0;
}