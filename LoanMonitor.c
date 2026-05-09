#include "raylib.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define MAX_CLIENTS     100
#define MAX_HISTORY     200
//                                          raylib 
#define SCREEN_W        1200
#define SCREEN_H        700
#define PANEL_LEFT_W    320
#define PANEL_RIGHT_W   380
#define FONT_SIZE       16
#define SMALL_FONT      13
#define LINE_H          22

//                                          colors

#define COL_BG          (Color){15,  17,  23,  255}
#define COL_PANEL       (Color){22,  26,  35,  255}
#define COL_CARD        (Color){30,  35,  48,  255}
#define COL_ACCENT      (Color){90, 160, 255,  255}
#define COL_GREEN       (Color){60, 210, 130,  255}
#define COL_RED         (Color){255, 90,  90,  255}
#define COL_YELLOW      (Color){255, 200,  60,  255}
#define COL_WHITE       (Color){230, 235, 245,  255}
#define COL_MUTED       (Color){110, 120, 145,  255}
#define COL_BORDER      (Color){45,  52,  70,  255}
#define COL_INPUT_BG    (Color){18,  22,  32,  255}
#define COL_SEL         (Color){40,  80, 160,  255}
#define COL_HOVER       (Color){35,  42,  60,  255}
#define COL_OVERDUE     (Color){255, 60,  60,   40}
#define COL_PAID        (Color){60, 210, 130,   30}

//                                          Data types

typedef struct {
    int   day;
    char  desc[80];
    float amount;    // positive = payment, negative = penalty/charge
    float balance;   // balance after event
} HistoryEntry;

typedef struct {
    char  name[50];
    float salary;
    float loan;
    float maxLoan;
    float interestRate;
    float balance;
    float originalBalance;
    int   paymentMethod; // 0=weekly, 1=monthly
    int   daysPassed;
    int   active;        // 0=paid off
    HistoryEntry history[MAX_HISTORY];
    int   historyCount;
} Client;

// ─── Input field helper ───────────────────────────────────────────────────────

typedef struct {
    char  buf[64];
    int   len;
    bool  focused;
    char  placeholder[40];
} InputField;

void InputFieldUpdate(InputField *f) {
    if (!f->focused) return;
    int ch;
    while ((ch = GetCharPressed()) != 0) {
        if (ch >= 32 && f->len < 63) {
            f->buf[f->len++] = (char)ch;
            f->buf[f->len]   = '\0';
        }
    }
    if (IsKeyPressed(KEY_BACKSPACE) && f->len > 0) {
        f->buf[--f->len] = '\0';
    }
}

void InputFieldDraw(InputField *f, int x, int y, int w, int h, Font font) {
    Color border = f->focused ? COL_ACCENT : COL_BORDER;
    DrawRectangle(x, y, w, h, COL_INPUT_BG);
    DrawRectangleLinesEx((Rectangle){x, y, w, h}, 1, border);

    const char *txt  = f->len > 0 ? f->buf : f->placeholder;
    Color       tcol = f->len > 0 ? COL_WHITE : COL_MUTED;
    DrawTextEx(font, txt, (Vector2){x + 8, y + (h - FONT_SIZE) / 2}, FONT_SIZE, 1, tcol);

    // Blinking cursor
    if (f->focused && ((int)(GetTime() * 2) % 2 == 0)) {
        float cx = x + 8 + MeasureTextEx(font, f->buf, FONT_SIZE, 1).x;
        DrawRectangle((int)cx, y + 5, 2, h - 10, COL_ACCENT);
    }
}

void InputFieldClear(InputField *f) {
    f->buf[0] = '\0';
    f->len    = 0;
}

// ─── Button helper ────────────────────────────────────────────────────────────

bool DrawButton(const char *label, int x, int y, int w, int h, Color bg, Font font) {
    Rectangle r = {x, y, w, h};
    bool      hover = CheckCollisionPointRec(GetMousePosition(), r);
    Color     col   = hover ? (Color){bg.r + 20, bg.g + 20, bg.b + 20, 255} : bg;
    DrawRectangleRec(r, col);
    DrawRectangleLinesEx(r, 1, COL_BORDER);
    Vector2 ts = MeasureTextEx(font, label, FONT_SIZE, 1);
    DrawTextEx(font, label, (Vector2){x + (w - ts.x) / 2, y + (h - ts.y) / 2}, FONT_SIZE, 1, COL_WHITE);
    return hover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON);
}

// ─── Label helper ─────────────────────────────────────────────────────────────

void DrawLabel(Font font, const char *label, const char *value, int x, int y, Color vcol) {
    DrawTextEx(font, label, (Vector2){x, y}, SMALL_FONT, 1, COL_MUTED);
    float lw = MeasureTextEx(font, label, SMALL_FONT, 1).x;
    DrawTextEx(font, value, (Vector2){x + lw + 6, y}, SMALL_FONT, 1, vcol);
}

// ─── State ────────────────────────────────────────────────────────────────────

static Client clients[MAX_CLIENTS];
static int    clientCount   = 0;
static int    selectedIdx   = -1;  // selected client in list
static int    activeTab     = 0;   // 0=add client, 1=make payment
static int    listScroll    = 0;
static int    histScroll    = 0;

// Add-client fields
static InputField fName, fSalary, fLoan;
static int        selMethod = 0;
static char       addError[80] = "";

// Payment field
static InputField fPayment;
static char       payError[80] = "";

// Global day counter
static int globalDay = 1;

// ─── Business logic ───────────────────────────────────────────────────────────

void AddHistory(Client *c, const char *desc, float amount) {
    if (c->historyCount >= MAX_HISTORY) return;
    HistoryEntry *e = &c->history[c->historyCount++];
    e->day     = globalDay;
    e->amount  = amount;
    e->balance = c->balance;
    snprintf(e->desc, sizeof(e->desc), "%s", desc);
}

void AddClient() {
    addError[0] = '\0';
    if (fName.len == 0)   { snprintf(addError, sizeof(addError), "Name is required.");           return; }
    if (fSalary.len == 0) { snprintf(addError, sizeof(addError), "Salary is required.");         return; }
    if (fLoan.len == 0)   { snprintf(addError, sizeof(addError), "Loan amount is required.");    return; }
    if (clientCount >= MAX_CLIENTS) { snprintf(addError, sizeof(addError), "Client limit reached."); return; }

    float salary = atof(fSalary.buf);
    float loan   = atof(fLoan.buf);

    if (salary <= 0) { snprintf(addError, sizeof(addError), "Salary must be > 0.");              return; }
    if (loan   <= 0) { snprintf(addError, sizeof(addError), "Loan amount must be > 0.");         return; }

    float maxLoan = salary * 0.2f;
    if (loan > maxLoan) {
        snprintf(addError, sizeof(addError), "Exceeds max loan (%.2f = 20%% of salary).", maxLoan);
        return;
    }

    Client *c = &clients[clientCount];
    memset(c, 0, sizeof(Client));
    snprintf(c->name, sizeof(c->name), "%s", fName.buf);
    c->salary        = salary;
    c->loan          = loan;
    c->maxLoan       = maxLoan;
    c->paymentMethod = selMethod;
    c->interestRate  = selMethod == 0 ? 0.05f : 0.10f;
    c->balance       = loan * (1.0f + c->interestRate);
    c->originalBalance = c->balance;
    c->daysPassed    = 0;
    c->active        = 1;
    c->historyCount  = 0;

    char desc[80];
    snprintf(desc, sizeof(desc), "Loan approved  (%.0f%% interest, %s)",
        c->interestRate * 100,
        selMethod == 0 ? "weekly" : "monthly");
    AddHistory(c, desc, -loan);

    selectedIdx = clientCount;
    clientCount++;

    InputFieldClear(&fName);
    InputFieldClear(&fSalary);
    InputFieldClear(&fLoan);
}

void MakePayment(int idx) {
    payError[0] = '\0';
    if (idx < 0 || idx >= clientCount) { snprintf(payError, sizeof(payError), "No client selected."); return; }
    float payment = atof(fPayment.buf);
    if (payment <= 0) { snprintf(payError, sizeof(payError), "Payment must be > 0."); return; }
    if (!clients[idx].active) { snprintf(payError, sizeof(payError), "Loan already paid off."); return; }

    Client *c = &clients[idx];
    if (payment > c->balance) payment = c->balance;
    c->balance -= payment;

    char desc[80];
    snprintf(desc, sizeof(desc), "Payment received");
    AddHistory(c, desc, payment);

    if (c->balance <= 0.001f) {
        c->balance = 0;
        c->active  = 0;
        AddHistory(c, "Loan fully paid off", 0);
    }

    InputFieldClear(&fPayment);
}

void AdvanceTime(int days) {
    globalDay += days;
    for (int i = 0; i < clientCount; i++) {
        if (!clients[i].active) continue;
        clients[i].daysPassed += days;

        // Apply penalty if overdue (>30 days)
        if (clients[i].daysPassed > 30) {
            float penalty = clients[i].balance * 0.02f;
            clients[i].balance += penalty;
            char desc[80];
            snprintf(desc, sizeof(desc), "2%% overdue penalty (+%.2f)", penalty);
            AddHistory(&clients[i], desc, -penalty);
        }
    }
}

// ─── Drawing helpers ──────────────────────────────────────────────────────────

void DrawSectionHeader(Font font, const char *title, int x, int y, int w) {
    DrawRectangle(x, y, w, 28, COL_CARD);
    DrawRectangle(x, y + 26, w, 2, COL_ACCENT);
    DrawTextEx(font, title, (Vector2){x + 10, y + 6}, FONT_SIZE, 1, COL_ACCENT);
}

void DrawStat(Font font, const char *label, const char *val, Color vc, int x, int y) {
    DrawTextEx(font, label, (Vector2){x, y}, SMALL_FONT, 1, COL_MUTED);
    DrawTextEx(font, val,   (Vector2){x, y + 16}, FONT_SIZE, 1, vc);
}

float ProgressPct(Client *c) {
    if (c->originalBalance <= 0) return 1.0f;
    float paid = c->originalBalance - c->balance;
    float pct  = paid / c->originalBalance;
    return pct < 0 ? 0 : (pct > 1 ? 1 : pct);
}

void DrawProgressBar(int x, int y, int w, int h, float pct, Color fill) {
    DrawRectangle(x, y, w, h, COL_INPUT_BG);
    DrawRectangle(x, y, (int)(w * pct), h, fill);
    DrawRectangleLinesEx((Rectangle){x, y, w, h}, 1, COL_BORDER);
}

// ─── Panels ───────────────────────────────────────────────────────────────────

void DrawLeftPanel(Font font, int x, int y, int w, int h) {
    DrawRectangle(x, y, w, h, COL_PANEL);
    DrawRectangle(x + w - 1, y, 1, h, COL_BORDER);

    // ── Tabs ──
    int tw = w / 2;
    const char *tabs[] = {"Add Client", "Payment"};
    for (int t = 0; t < 2; t++) {
        Color bg = (activeTab == t) ? COL_SEL : COL_CARD;
        DrawRectangle(x + t * tw, y, tw, 36, bg);
        DrawRectangle(x + t * tw, y + 34, tw, 2, (activeTab == t) ? COL_ACCENT : COL_BORDER);
        Vector2 ts = MeasureTextEx(font, tabs[t], FONT_SIZE, 1);
        DrawTextEx(font, tabs[t], (Vector2){x + t * tw + (tw - ts.x) / 2, y + (36 - FONT_SIZE) / 2}, FONT_SIZE, 1,
                   (activeTab == t) ? COL_WHITE : COL_MUTED);
        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){x + t * tw, y, tw, 36})
            && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            activeTab = t;
        }
    }

    int cy = y + 46;

    if (activeTab == 0) {
        // ── Add Client tab ──
        DrawTextEx(font, "New Client", (Vector2){x + 10, cy}, FONT_SIZE, 1, COL_WHITE);
        cy += 26;

        const char *labels[] = {"Full Name", "Monthly Salary", "Loan Amount"};
        InputField *fields[] = {&fName, &fSalary, &fLoan};
        for (int i = 0; i < 3; i++) {
            DrawTextEx(font, labels[i], (Vector2){x + 10, cy}, SMALL_FONT, 1, COL_MUTED);
            cy += 16;
            Rectangle fr = {x + 10, cy, w - 20, 34};
            if (CheckCollisionPointRec(GetMousePosition(), fr) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
                fName.focused = fSalary.focused = fLoan.focused = false;
                fields[i]->focused = true;
            }
            InputFieldDraw(fields[i], x + 10, cy, w - 20, 34, font);
            cy += 42;
        }

        // Payment method
        DrawTextEx(font, "Payment Method", (Vector2){x + 10, cy}, SMALL_FONT, 1, COL_MUTED);
        cy += 16;
        const char *methods[] = {"Weekly (5%)", "Monthly (10%)"};
        for (int m = 0; m < 2; m++) {
            Color bg = selMethod == m ? COL_SEL : COL_CARD;
            int   bw = (w - 24) / 2;
            int   bx = x + 10 + m * (bw + 4);
            DrawRectangle(bx, cy, bw, 30, bg);
            DrawRectangleLinesEx((Rectangle){bx, cy, bw, 30}, 1, selMethod == m ? COL_ACCENT : COL_BORDER);
            Vector2 ts = MeasureTextEx(font, methods[m], SMALL_FONT, 1);
            DrawTextEx(font, methods[m], (Vector2){bx + (bw - ts.x) / 2, cy + (30 - SMALL_FONT) / 2}, SMALL_FONT, 1,
                       selMethod == m ? COL_WHITE : COL_MUTED);
            if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){bx, cy, bw, 30})
                && IsMouseButtonPressed(MOUSE_LEFT_BUTTON))
                selMethod = m;
        }
        cy += 38;

        // Error message
        if (addError[0]) {
            DrawTextEx(font, addError, (Vector2){x + 10, cy}, SMALL_FONT, 1, COL_RED);
            cy += 20;
        }

        if (DrawButton("Add Client", x + 10, cy, w - 20, 36, COL_SEL, font)) {
            AddClient();
        }
        cy += 46;

        // Time controls
        DrawRectangle(x, cy, w, 1, COL_BORDER);
        cy += 10;
        DrawTextEx(font, "Simulate Time", (Vector2){x + 10, cy}, SMALL_FONT, 1, COL_MUTED);
        cy += 18;

        struct { const char *lbl; int days; } timeBtns[] = {
            {"+1 Day", 1}, {"+1 Week", 7}, {"+1 Month", 30}
        };
        int bw = (w - 28) / 3;
        for (int t = 0; t < 3; t++) {
            if (DrawButton(timeBtns[t].lbl, x + 10 + t * (bw + 4), cy, bw, 30, COL_CARD, font))
                AdvanceTime(timeBtns[t].days);
        }
        cy += 38;

        char dayStr[30];
        snprintf(dayStr, sizeof(dayStr), "Global Day: %d", globalDay);
        DrawTextEx(font, dayStr, (Vector2){x + 10, cy}, SMALL_FONT, 1, COL_MUTED);

    } else {
        // ── Payment tab ──
        if (selectedIdx < 0 || selectedIdx >= clientCount) {
            DrawTextEx(font, "Select a client from", (Vector2){x + 10, cy + 20}, FONT_SIZE, 1, COL_MUTED);
            DrawTextEx(font, "the list to make a payment.", (Vector2){x + 10, cy + 44}, FONT_SIZE, 1, COL_MUTED);
            return;
        }
        Client *c = &clients[selectedIdx];

        DrawTextEx(font, c->name, (Vector2){x + 10, cy}, FONT_SIZE + 2, 1, COL_WHITE);
        cy += 24;

        char bstr[30]; snprintf(bstr, sizeof(bstr), "%.2f", c->balance);
        char ostr[30]; snprintf(ostr, sizeof(ostr), "%.2f", c->originalBalance);
        DrawStat(font, "Balance Due", bstr, c->active ? COL_YELLOW : COL_GREEN, x + 10, cy);
        DrawStat(font, "Original",    ostr, COL_MUTED, x + 130, cy);
        cy += 40;

        float pct = ProgressPct(c);
        DrawProgressBar(x + 10, cy, w - 20, 10, pct, COL_GREEN);
        char pstr[20]; snprintf(pstr, sizeof(pstr), "%.0f%% paid", pct * 100);
        DrawTextEx(font, pstr, (Vector2){x + 10, cy + 14}, SMALL_FONT, 1, COL_MUTED);
        cy += 34;

        if (!c->active) {
            DrawRectangle(x + 10, cy, w - 20, 36, COL_PAID);
            DrawRectangleLinesEx((Rectangle){x + 10, cy, w - 20, 36}, 1, COL_GREEN);
            Vector2 ts = MeasureTextEx(font, "Loan Fully Paid Off", FONT_SIZE, 1);
            DrawTextEx(font, "Loan Fully Paid Off", (Vector2){x + 10 + (w - 20 - ts.x) / 2, cy + 10}, FONT_SIZE, 1, COL_GREEN);
            return;
        }

        DrawTextEx(font, "Payment Amount", (Vector2){x + 10, cy}, SMALL_FONT, 1, COL_MUTED);
        cy += 16;
        Rectangle pr = {x + 10, cy, w - 20, 34};
        if (CheckCollisionPointRec(GetMousePosition(), pr) && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            fName.focused = fSalary.focused = fLoan.focused = false;
            fPayment.focused = true;
        }
        InputFieldDraw(&fPayment, x + 10, cy, w - 20, 34, font);
        cy += 42;

        if (payError[0]) {
            DrawTextEx(font, payError, (Vector2){x + 10, cy}, SMALL_FONT, 1, COL_RED);
            cy += 20;
        }

        if (DrawButton("Make Payment", x + 10, cy, w - 20, 36, COL_SEL, font))
            MakePayment(selectedIdx);
        cy += 46;

        // Quick-pay full balance
        if (DrawButton("Pay Full Balance", x + 10, cy, w - 20, 30, COL_CARD, font)) {
            char tmp[20]; snprintf(tmp, sizeof(tmp), "%.2f", c->balance);
            snprintf(fPayment.buf, sizeof(fPayment.buf), "%s", tmp);
            fPayment.len = strlen(fPayment.buf);
            MakePayment(selectedIdx);
        }
    }
}

void DrawMiddlePanel(Font font, int x, int y, int w, int h) {
    DrawRectangle(x, y, w, h, COL_BG);
    DrawRectangle(x + w - 1, y, 1, h, COL_BORDER);

    DrawSectionHeader(font, "Clients", x, y, w);
    int cy = y + 36;

    // Stats bar
    int active = 0, overdue = 0; float totalBal = 0;
    for (int i = 0; i < clientCount; i++) {
        if (clients[i].active)             active++;
        if (clients[i].daysPassed > 30)    overdue++;
        totalBal += clients[i].balance;
    }

    DrawRectangle(x, cy, w, 52, COL_CARD);
    char s1[20]; snprintf(s1, sizeof(s1), "%d", clientCount);
    char s2[20]; snprintf(s2, sizeof(s2), "%d", active);
    char s3[20]; snprintf(s3, sizeof(s3), "%d", overdue);
    DrawStat(font, "Total",   s1, COL_WHITE,  x + 10, cy + 6);
    DrawStat(font, "Active",  s2, COL_GREEN,  x + 80, cy + 6);
    DrawStat(font, "Overdue", s3, COL_RED,   x + 160, cy + 6);
    cy += 58;

    // Client list
    int visibleRows = (h - (cy - y) - 10) / 54;
    int maxScroll   = clientCount - visibleRows;
    if (maxScroll < 0) maxScroll = 0;

    // Scroll
    int wheel = (int)GetMouseWheelMove();
    Rectangle listArea = {x, cy, w, h - (cy - y)};
    if (CheckCollisionPointRec(GetMousePosition(), listArea)) {
        listScroll -= wheel;
        if (listScroll < 0)          listScroll = 0;
        if (listScroll > maxScroll)  listScroll = maxScroll;
    }

    if (clientCount == 0) {
        DrawTextEx(font, "No clients yet.", (Vector2){x + 10, cy + 10}, FONT_SIZE, 1, COL_MUTED);
        return;
    }

    BeginScissorMode(x, cy, w, h - (cy - y) - 4);
    for (int i = listScroll; i < clientCount && i < listScroll + visibleRows + 1; i++) {
        Client *c   = &clients[i];
        int     ry  = cy + (i - listScroll) * 54;
        bool    sel = (i == selectedIdx);
        bool    ov  = c->active && c->daysPassed > 30;
        bool    pd  = !c->active;

        Color rowbg = sel ? COL_SEL : (ov ? COL_OVERDUE : (pd ? COL_PAID : COL_CARD));
        DrawRectangle(x + 4, ry, w - 8, 50, rowbg);
        if (sel) DrawRectangle(x + 4, ry, 3, 50, COL_ACCENT);
        DrawRectangleLinesEx((Rectangle){x + 4, ry, w - 8, 50}, 0.5f, COL_BORDER);

        // Name + status badge
        DrawTextEx(font, c->name, (Vector2){x + 14, ry + 6}, FONT_SIZE, 1, COL_WHITE);
        const char *badge = pd ? "PAID" : (ov ? "OVERDUE" : "ACTIVE");
        Color       bcol  = pd ? COL_GREEN : (ov ? COL_RED : COL_ACCENT);
        Vector2     bts   = MeasureTextEx(font, badge, SMALL_FONT, 1);
        int         bx    = x + w - (int)bts.x - 16;
        DrawTextEx(font, badge, (Vector2){bx, ry + 8}, SMALL_FONT, 1, bcol);

        // Balance + progress
        char bstr[30];
        snprintf(bstr, sizeof(bstr), "%.2f", c->balance);
        DrawTextEx(font, bstr, (Vector2){x + 14, ry + 26}, SMALL_FONT, 1,
                   pd ? COL_GREEN : (ov ? COL_RED : COL_YELLOW));

        float pct = ProgressPct(c);
        DrawProgressBar(x + 80, ry + 30, w - 100, 6, pct, pd ? COL_GREEN : COL_ACCENT);

        char dstr[20]; snprintf(dstr, sizeof(dstr), "Day %d", c->daysPassed);
        DrawTextEx(font, dstr, (Vector2){x + w - 60, ry + 30}, SMALL_FONT, 1, COL_MUTED);

        if (CheckCollisionPointRec(GetMousePosition(), (Rectangle){x + 4, ry, w - 8, 50})
            && IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            selectedIdx = i;
            histScroll  = 0;
        }
    }
    EndScissorMode();
}

void DrawRightPanel(Font font, int x, int y, int w, int h) {
    DrawRectangle(x, y, w, h, COL_PANEL);

    if (selectedIdx < 0 || selectedIdx >= clientCount) {
        DrawSectionHeader(font, "Client Details", x, y, w);
        DrawTextEx(font, "Select a client to view details.", (Vector2){x + 14, y + 56}, FONT_SIZE, 1, COL_MUTED);
        return;
    }

    Client *c = &clients[selectedIdx];
    DrawSectionHeader(font, c->name, x, y, w);

    int cy = y + 40;

    // Details card
    DrawRectangle(x + 8, cy, w - 16, 100, COL_CARD);
    DrawRectangleLinesEx((Rectangle){x + 8, cy, w - 16, 100}, 0.5f, COL_BORDER);

    char tmp[50];
    snprintf(tmp, sizeof(tmp), "%.2f", c->salary);
    DrawLabel(font, "Salary:",  tmp, x + 16, cy + 8,  COL_WHITE);
    snprintf(tmp, sizeof(tmp), "%.2f", c->loan);
    DrawLabel(font, "Loan:",    tmp, x + 16, cy + 26, COL_WHITE);
    snprintf(tmp, sizeof(tmp), "%.2f", c->maxLoan);
    DrawLabel(font, "Max Loan:", tmp, x + 16, cy + 44, COL_MUTED);
    snprintf(tmp, sizeof(tmp), "%.0f%% (%s)", c->interestRate * 100, c->paymentMethod == 0 ? "weekly" : "monthly");
    DrawLabel(font, "Interest:", tmp, x + 16, cy + 62, COL_ACCENT);
    snprintf(tmp, sizeof(tmp), "%d days", c->daysPassed);
    DrawLabel(font, "Age:",     tmp, x + 16, cy + 80, c->daysPassed > 30 ? COL_RED : COL_MUTED);
    cy += 108;

    // Balance card
    DrawRectangle(x + 8, cy, w - 16, 70, COL_CARD);
    DrawRectangleLinesEx((Rectangle){x + 8, cy, w - 16, 70}, 0.5f, COL_BORDER);

    snprintf(tmp, sizeof(tmp), "%.2f", c->balance);
    DrawTextEx(font, "Balance Due", (Vector2){x + 16, cy + 6}, SMALL_FONT, 1, COL_MUTED);
    DrawTextEx(font, tmp,           (Vector2){x + 16, cy + 22}, FONT_SIZE + 6, 1,
               c->active ? (c->daysPassed > 30 ? COL_RED : COL_YELLOW) : COL_GREEN);

    float pct = ProgressPct(c);
    DrawProgressBar(x + 16, cy + 50, w - 32, 8, pct, c->active ? COL_ACCENT : COL_GREEN);
    snprintf(tmp, sizeof(tmp), "%.1f%%", pct * 100);
    DrawTextEx(font, tmp, (Vector2){x + w - 44, cy + 48}, SMALL_FONT, 1, COL_MUTED);
    cy += 78;

    // History
    DrawTextEx(font, "Transaction History", (Vector2){x + 16, cy}, FONT_SIZE, 1, COL_WHITE);
    cy += 22;

    int visH    = h - (cy - y) - 8;
    int rowH    = 44;
    int visRows = visH / rowH;
    int maxScH  = c->historyCount - visRows;
    if (maxScH < 0) maxScH = 0;

    Rectangle histArea = {x, cy, w, visH};
    if (CheckCollisionPointRec(GetMousePosition(), histArea)) {
        int wheel = (int)GetMouseWheelMove();
        histScroll -= wheel;
        if (histScroll < 0)         histScroll = 0;
        if (histScroll > maxScH)    histScroll = maxScH;
    }

    if (c->historyCount == 0) {
        DrawTextEx(font, "No history yet.", (Vector2){x + 16, cy + 6}, SMALL_FONT, 1, COL_MUTED);
        return;
    }

    // Draw newest first
    BeginScissorMode(x, cy, w, visH);
    for (int i = c->historyCount - 1 - histScroll; i >= 0 && (c->historyCount - 1 - i - histScroll) < visRows; i--) {
        HistoryEntry *e  = &c->history[i];
        int           ry = cy + (c->historyCount - 1 - i - histScroll) * rowH;

        DrawRectangle(x + 8, ry + 2, w - 16, rowH - 4, COL_CARD);
        DrawRectangleLinesEx((Rectangle){x + 8, ry + 2, w - 16, rowH - 4}, 0.5f, COL_BORDER);

        char dayStr[16]; snprintf(dayStr, sizeof(dayStr), "Day %d", e->day);
        DrawTextEx(font, dayStr, (Vector2){x + 16, ry + 6}, SMALL_FONT, 1, COL_MUTED);
        DrawTextEx(font, e->desc, (Vector2){x + 16, ry + 22}, SMALL_FONT, 1, COL_WHITE);

        if (e->amount != 0) {
            char astr[30];
            const char *sign = e->amount > 0 ? "+" : "";
            snprintf(astr, sizeof(astr), "%s%.2f", sign, e->amount);
            Color ac = e->amount > 0 ? COL_GREEN : COL_RED;
            Vector2 ats = MeasureTextEx(font, astr, SMALL_FONT, 1);
            DrawTextEx(font, astr, (Vector2){x + w - (int)ats.x - 16, ry + 6},  SMALL_FONT, 1, ac);
            char bstr2[30]; snprintf(bstr2, sizeof(bstr2), "%.2f", e->balance);
            Vector2 bts = MeasureTextEx(font, bstr2, SMALL_FONT, 1);
            DrawTextEx(font, bstr2, (Vector2){x + w - (int)bts.x - 16, ry + 22}, SMALL_FONT, 1, COL_MUTED);
        }
    }
    EndScissorMode();
}

// ─── Main ─────────────────────────────────────────────────────────────────────

int main(void) {
    SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_MSAA_4X_HINT);
    InitWindow(SCREEN_W, SCREEN_H, "Loan Monitoring System");
    SetTargetFPS(60);

    Font font = LoadFontEx("/usr/share/fonts/truetype/dejavu/DejaVuSans.ttf", 20, 0, 250);
    if (font.texture.id == 0)
        font = GetFontDefault();

    // Init input fields
    memset(&fName,    0, sizeof(fName));    snprintf(fName.placeholder,    40, "e.g. Maria Santos");
    memset(&fSalary,  0, sizeof(fSalary));  snprintf(fSalary.placeholder,  40, "e.g. 25000.00");
    memset(&fLoan,    0, sizeof(fLoan));    snprintf(fLoan.placeholder,    40, "e.g. 4000.00");
    memset(&fPayment, 0, sizeof(fPayment)); snprintf(fPayment.placeholder, 40, "e.g. 500.00");

    while (!WindowShouldClose()) {
        int sw = GetScreenWidth();
        int sh = GetScreenHeight();
        int midW = sw - PANEL_LEFT_W - PANEL_RIGHT_W;

        // Update focused input fields
        InputFieldUpdate(&fName);
        InputFieldUpdate(&fSalary);
        InputFieldUpdate(&fLoan);
        InputFieldUpdate(&fPayment);

        // Tab click to dismiss focus
        if (IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Vector2 mp = GetMousePosition();
            bool onInput =
                CheckCollisionPointRec(mp, (Rectangle){10, 0, PANEL_LEFT_W, sh}) ||
                CheckCollisionPointRec(mp, (Rectangle){PANEL_LEFT_W + midW, 0, PANEL_RIGHT_W, sh});
            if (!onInput) {
                fName.focused = fSalary.focused = fLoan.focused = fPayment.focused = false;
            }
        }

        BeginDrawing();
        ClearBackground(COL_BG);

        DrawLeftPanel  (font,  0,           0, PANEL_LEFT_W, sh);
        DrawMiddlePanel(font,  PANEL_LEFT_W, 0, midW,         sh);
        DrawRightPanel (font,  PANEL_LEFT_W + midW, 0, PANEL_RIGHT_W, sh);

        EndDrawing();
    }

    UnloadFont(font);
    CloseWindow();
    return 0;
}