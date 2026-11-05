# programa_practice
2026-2 팀 실습


#define _CRT_SECURE_NO_WARNINGS
#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#define WIDTH 800
#define HEIGHT 600
#define TOTAL 10

HWND hwnd;
HINSTANCE hInst;

int x, y;
int radius = 38;
int hits = 0;
int misses = 0;
int gameStarted = 0;
int gameOver = 0;

DWORD startTime;
DWORD elapsedTime;

void CreateTarget() {
    x = radius + rand() % (WIDTH - radius * 2);
    y = 120 + radius + rand() % (HEIGHT - 180 - radius * 2);
}

void StartGame() {
    hits = 0;
    misses = 0;
    radius = 38;
    gameOver = 0;
    gameStarted = 1;

    startTime = GetTickCount();
    CreateTarget();

    InvalidateRect(hwnd, NULL, TRUE);
    SetTimer(hwnd, 1, 50, NULL);
}

void DrawGame(HDC hdc) {
    RECT rect;
    GetClientRect(hwnd, &rect);

    HBRUSH bg = CreateSolidBrush(RGB(20, 28, 45));
    FillRect(hdc, &rect, bg);
    DeleteObject(bg);

    SetBkMode(hdc, TRANSPARENT);
    SetTextColor(hdc, RGB(255, 255, 255));

    char text[100];

    sprintf(text, "MOUSE TARGET CHALLENGE");
    TextOutA(hdc, 250, 20, text, strlen(text));

    sprintf(text, "Hits: %d / %d", hits, TOTAL);
    TextOutA(hdc, 30, 65, text, strlen(text));

    sprintf(text, "Misses: %d", misses);
    TextOutA(hdc, 200, 65, text, strlen(text));

    int remaining = 30 - (int)(elapsedTime / 1000);

    if (remaining < 0)
        remaining = 0;

    sprintf(text, "Time: %d", remaining);
    TextOutA(hdc, 650, 65, text, strlen(text));

    if (!gameStarted) {
        TextOutA(hdc, 280, 250,
            "Press SPACE to Start", 21);
        return;
    }

    if (gameOver) {
        TextOutA(hdc, 320, 250,
            "GAME OVER!", 10);
        return;
    }

    HBRUSH brush = CreateSolidBrush(RGB(50, 220, 140));
    HBRUSH oldBrush = SelectObject(hdc, brush);

    Ellipse(hdc,
        x - radius, y - radius,
        x + radius, y + radius);

    SelectObject(hdc, oldBrush);
    DeleteObject(brush);
}

LRESULT CALLBACK WindowProc(
    HWND hwnd,
    UINT msg,
    WPARAM wParam,
    LPARAM lParam
) {
    switch (msg) {

    case WM_PAINT: {
        PAINTSTRUCT ps;
        HDC hdc = BeginPaint(hwnd, &ps);

        DrawGame(hdc);

        EndPaint(hwnd, &ps);
        return 0;
    }

    case WM_KEYDOWN:
        if (wParam == VK_SPACE && !gameStarted) {
            StartGame();
        }
        return 0;

    case WM_LBUTTONDOWN:
        if (gameStarted && !gameOver) {
            int mouseX = LOWORD(lParam);
            int mouseY = HIWORD(lParam);

            int dx = mouseX - x;
            int dy = mouseY - y;

            if (dx * dx + dy * dy <= radius * radius) {
                hits++;

                if (hits >= TOTAL) {
                    gameOver = 1;
                    KillTimer(hwnd, 1);
                }
                else {
                    radius -= 3;

                    if (radius < 12)
                        radius = 12;

                    CreateTarget();
                }
            }
            else {
                misses++;
            }

            InvalidateRect(hwnd, NULL, TRUE);
        }
        return 0;

    case WM_TIMER:
        elapsedTime = GetTickCount() - startTime;

        if (elapsedTime >= 30000) {
            gameOver = 1;
            KillTimer(hwnd, 1);
        }

        InvalidateRect(hwnd, NULL, TRUE);
        return 0;

    case WM_DESTROY:
        KillTimer(hwnd, 1);
        PostQuitMessage(0);
        return 0;
    }

    return DefWindowProc(hwnd, msg, wParam, lParam);
}

int WINAPI WinMain(
    HINSTANCE hInstance,
    HINSTANCE hPrevInstance,
    LPSTR lpCmdLine,
    int nCmdShow
) {
    srand((unsigned int)time(NULL));

    hInst = hInstance;

    WNDCLASSA wc = { 0 };

    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "TargetGame";
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);

    RegisterClassA(&wc);

    hwnd = CreateWindowA(
        "TargetGame",
        "Mouse Target Challenge",
        WS_OVERLAPPEDWINDOW,
        CW_USEDEFAULT,
        CW_USEDEFAULT,
        WIDTH,
        HEIGHT,
        NULL,
        NULL,
        hInstance,
        NULL
    );

    if (!hwnd)
        return 0;

    ShowWindow(hwnd, nCmdShow);
    UpdateWindow(hwnd);

    MSG msg;

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return (int)msg.wParam;
}
