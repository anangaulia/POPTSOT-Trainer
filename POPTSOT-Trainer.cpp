// main.cpp - Prince of Persia: The Sand of Time Trainer (Win32 GUI) - MSVC 6.0/2003/2005 compatible
#include <windows.h>
#include <stdio.h>

#pragma comment(lib, "user32.lib")
#pragma comment(lib, "kernel32.lib")

// ---------------- Globals ----------------
HWND hMainWnd = NULL;
HWND hStatus = NULL;
HWND GameWindow = NULL;
DWORD PID = 0;
DWORD TID = 0;
HANDLE PHandle = NULL;

// Timer IDs
#define IDT_TITLE      1
#define IDT_GAMESTATE 10
#define IDT_HOTKEY    2

// Button IDs
#define IDC_BTN_DISABLE   101
#define IDC_BTN_SAND      102
#define IDC_BTN_POWER     103
#define IDC_BTN_RECALL    104
#define IDC_BTN_SLOW      105
#define IDC_BTN_HEALTH    106
#define IDC_BTN_SWORDSTATE_3RD 107
#define IDC_BTN_SWORDSTATE_2ND 108
#define IDC_BTN_SWORDSTATE_1ST 109
#define IDC_BTN_SWORDSTATE_ZERO 110
#define IDC_BTN_EXIT      198
#define IDC_BTN_GAMEEXIT      199
#define IDC_STATUS        200



// ---------------- Helpers ----------------
void SafeCloseProcessHandle() {
    if (PHandle) {
        CloseHandle(PHandle);
        PHandle = NULL;
    }
}

bool OpenGameProcess() {
    if (!GameWindow) return false;
    TID = GetWindowThreadProcessId(GameWindow, &PID);
    if (PID == 0) return false;
    PHandle = OpenProcess(PROCESS_ALL_ACCESS, FALSE, PID);
    if (!PHandle) return false;
    return true;
}

void WriteBytes(DWORD address, BYTE* bytes, SIZE_T size) {
    if (!PHandle) return;
    SIZE_T written = 0;
    // Remove memory protection if needed (optional) - skipping for simplicity
    WriteProcessMemory(PHandle, (LPVOID)address, bytes, size, &written);
}

void DoBeep() {
    MessageBeep(MB_OK); // Beep sound
}

void DoBeepX() {
    MessageBeep(MB_ICONERROR);
}

void StopBeep() {
    // nothing to do in most cases
}

// ---------------- All translated functions ----------------
void SandTanks() {
    BYTE Sand1[] = {0xC7,0x02,0x0A,0x00,0x00,0x00,0x8B,0x4F,0x1C,0xE9,0xB4,0x60,0xB7,0xFF};
    BYTE Sand2[] = {0x8B,0x10,0xC7,0x00,0x0A,0x00,0x00,0x00,0xA1,0xF4,0xB4,0xAD,0x00,0xE9,0x08,0x04,0xB7,0xFF};
    BYTE Sand3[] = {0x90,0x90,0x90,0x90,0x90,0x90};
    BYTE Sand4[] = {0xE9,0xE6,0xFB,0x48,0x00,0x90,0x90};
    BYTE Sand5[] = {0xE9,0x3E,0x9F,0x48,0x00};

    GameWindow = FindWindowA(NULL, "Prince of Persia");
    if (!OpenGameProcess()) { SafeCloseProcessHandle(); return; }

    WriteBytes(0x009EC000, Sand1, sizeof(Sand1));
    WriteBytes(0x009EC054, Sand2, sizeof(Sand2));
    WriteBytes(0x00581912, Sand3, sizeof(Sand3));
    WriteBytes(0x0055C469, Sand4, sizeof(Sand4));
    WriteBytes(0x005620BD, Sand5, sizeof(Sand5));

    DoBeep();
    SafeCloseProcessHandle();
}

void PowerTanks() {
    BYTE Power1[] = {0xE9,0x0A,0xFC,0x48,0x00};
    BYTE Power2[] = {0x8B,0x10,0xC7,0x00,0x14,0x00,0x00,0x00,0x89,0x56,0x3C,0xE9,0xE6,0x03,0xB7,0xFF};
    BYTE Power3[] = {0x90,0x90,0x90,0x90,0x90,0x90};
    BYTE Power4[] = {0x90,0x90,0x90,0x90,0x90,0x90,0x90};
    BYTE Power5[] = {0xE9,0x4D,0xFC,0x48,0x00,0x90};
    BYTE Power6[] = {0x8B,0x45,0x00,0xC7,0x45,0x00,0x14,0x00,0x00,0x00,0x99,0x29,0xD0,0xE9,0xA1,0x03,0xB7,0xFF};

    GameWindow = FindWindowA(NULL, "Prince of Persia");
    if (!OpenGameProcess()) { SafeCloseProcessHandle(); return; }

    WriteBytes(0x0055C487, Power1, sizeof(Power1));
    WriteBytes(0x009EC096, Power2, sizeof(Power2));
    WriteBytes(0x00581A2B, Power3, sizeof(Power3));
    WriteBytes(0x0063BC4E, Power4, sizeof(Power4));
    WriteBytes(0x0055C48C, Power5, sizeof(Power5));
    WriteBytes(0x009EC0DE, Power6, sizeof(Power6));

    DoBeep();
    SafeCloseProcessHandle();
}

void Recall() {
    BYTE Recall1[] = {0xE9,0x8D,0xFE,0x57,0x00,0x90};
    BYTE Recall2[] = {0xDF,0x68,0x38,0xC7,0x40,0x38,0x40,0x54,0x89,0x00,0xD9,0x1C,0x24,0xE9,0x61,0x01,0xA8,0xFF};

    GameWindow = FindWindowA(NULL, "Prince of Persia");
    if (!OpenGameProcess()) { SafeCloseProcessHandle(); return; }

    WriteBytes(0x0046C296, Recall1, sizeof(Recall1));
    WriteBytes(0x009EC128, Recall2, sizeof(Recall2));

    DoBeep();
    SafeCloseProcessHandle();
}

void SlowMotion() {
    BYTE Slow1[] = {0x89,0xAE,0xCC,0x0C,0x00,0x00};

    GameWindow = FindWindowA(NULL, "Prince of Persia");
    if (!OpenGameProcess()) { SafeCloseProcessHandle(); return; }

    WriteBytes(0x005816D8, Slow1, sizeof(Slow1));

    DoBeep();
    SafeCloseProcessHandle();
}

void Health() {
    BYTE Health1[] = {0xE9,0x34,0x3C,0x3A,0x00,0x90,0x90};
    BYTE Health2[] = {0x8B,0x10,0xC7,0x00,0x36,0x01,0x00,0x00,0xA1,0xFC,0xB4,0xAD,0x00,0xE9,0xBA,0xC3,0xC5,0xFF};
    BYTE Health3[] = {0xE9,0xB8,0x3B,0x3A,0x00,0x90,0x90};
    BYTE Health4[] = {0x8B,0x10,0xC7,0x00,0x36,0x01,0x00,0x00,0xA1,0xF8,0xB4,0xAD,0x00,0xE9,0x36,0xC4,0xC5,0xFF};
    BYTE HealthNOP1[] = {0x90,0x90,0x90,0x90,0x90,0x90};
    BYTE HealthNOP2[] = {0x90,0x90,0x90,0x90,0x90,0x90};
    BYTE HealthNOP3[] = {0x90,0x90,0x90,0x90,0x90,0x90};
    BYTE HealthNOP11[] = {0x90,0x90,0x90,0x90,0x90,0x90};
    BYTE HealthNOP12[] = {0x90,0x90,0x90,0x90,0x90,0x90};
    BYTE HealthNOP13[] = {0x90,0x90,0x90,0x90,0x90,0x90};
    BYTE HealthNOP14[] = {0x90,0x90,0x90,0x90,0x90,0x90};

    GameWindow = FindWindowA(NULL, "Prince of Persia");
    if (!OpenGameProcess()) { SafeCloseProcessHandle(); return; }

    WriteBytes(0x0055C455, Health1, sizeof(Health1));
    WriteBytes(0x0090008E, Health2, sizeof(Health2));
    WriteBytes(0x0055C45F, Health3, sizeof(Health3));
    WriteBytes(0x0090001C, Health4, sizeof(Health4));
    WriteBytes(0x005124EC, HealthNOP1, sizeof(HealthNOP1));
    WriteBytes(0x00643DC0, HealthNOP2, sizeof(HealthNOP2));
    WriteBytes(0x00643833, HealthNOP3, sizeof(HealthNOP3));
    WriteBytes(0x005F08B3, HealthNOP11, sizeof(HealthNOP11));
    WriteBytes(0x00613DD0, HealthNOP12, sizeof(HealthNOP12));
    WriteBytes(0x00613D7C, HealthNOP13, sizeof(HealthNOP13));
    WriteBytes(0x00613D64, HealthNOP14, sizeof(HealthNOP14));

    DoBeep();
    SafeCloseProcessHandle();
}

void Disabled() {
    BYTE Sand1[] = {0x8B,0x02,0x8B,0x4F,0x1C};
    BYTE Sand2[] = {0xFF,0x8E,0xAC,0x07,0x00,0x00};
    BYTE Sand3[] = {0x8B,0x10,0xA1,0xF4,0xB4,0xAD,0x00};
    BYTE Power1[] = {0x8B,0x10,0x89,0x56,0x3C};
    BYTE Power2[] = {0x89,0x86,0xA8,0x0C,0x00,0x00};
    BYTE Power3[] = {0x83,0x87,0xA8,0x0C,0x00,0x00,0xFE};
    BYTE Power4[] = {0x8B,0x45,0x00,0x99,0x2B,0xC2};
    BYTE Recall1[] = {0xDF,0x68,0x38,0xD9,0x1C,0x24};
    BYTE Slow1[] = {0x89,0x86,0xCC,0x0C,0x00,0x00};
    BYTE Health1[] = {0x8B,0x10,0xA1,0xFC,0xB4,0xAD,0x00};
    BYTE Health2[] = {0x8B,0x10,0xA1,0xF8,0xB4,0xAD,0x00};
    BYTE HNOP1[] = {0x89,0x86,0x9C,0x01,0x00,0x00};
    BYTE HNOP2[] = {0x89,0x8F,0x9C,0x01,0x00,0x00};
    BYTE HNOP3[] = {0x89,0x87,0x9C,0x01,0x00,0x00};
    BYTE HNOP11[] = {0x89,0x87,0x9C,0x01,0x00,0x00};
    BYTE HNOP12[] = {0x89,0x8E,0x9C,0x01,0x00,0x00};
    BYTE HNOP13[] = {0x89,0x96,0x9C,0x01,0x00,0x00};
    BYTE HNOP14[] = {0x89,0x96,0xF8,0x11,0x00,0x00};

    GameWindow = FindWindowA(NULL, "Prince of Persia");
    if (!OpenGameProcess()) { SafeCloseProcessHandle(); return; }

    WriteBytes(0x005620BD, Sand1, sizeof(Sand1));
    WriteBytes(0x00581912, Sand2, sizeof(Sand2));
    WriteBytes(0x0055C469, Sand3, sizeof(Sand3));
    WriteBytes(0x0055C487, Power1, sizeof(Power1));
    WriteBytes(0x00581A2B, Power2, sizeof(Power2));
    WriteBytes(0x0063BC4E, Power3, sizeof(Power3));
    WriteBytes(0x0055C48C, Power4, sizeof(Power4));
    WriteBytes(0x0046C296, Recall1, sizeof(Recall1));
    WriteBytes(0x005816D8, Slow1, sizeof(Slow1));
    WriteBytes(0x0055C455, Health1, sizeof(Health1));
    WriteBytes(0x0055C45F, Health2, sizeof(Health2));
    WriteBytes(0x005124EC, HNOP1, sizeof(HNOP1));
    WriteBytes(0x00643DC0, HNOP2, sizeof(HNOP2));
    WriteBytes(0x00643833, HNOP3, sizeof(HNOP3));
    WriteBytes(0x005F08B3, HNOP11, sizeof(HNOP11));
    WriteBytes(0x00613DD0, HNOP12, sizeof(HNOP12));
    WriteBytes(0x00613D7C, HNOP13, sizeof(HNOP13));
    WriteBytes(0x00613D64, HNOP14, sizeof(HNOP14));

    DoBeepX();
    SafeCloseProcessHandle();
}

void SetSwordState(int value) {
    GameWindow = FindWindowA(NULL, "Prince of Persia");
    if (!OpenGameProcess()) { SafeCloseProcessHandle(); return; }

    DWORD pointer0 = 0x00400000 + 0x0040DAB8;  // First pointer
    DWORD basePtr = 0, p1 = 0, p2 = 0;

    ReadProcessMemory(PHandle, (LPCVOID)pointer0, &basePtr, 4, NULL);
    if (!basePtr) return;

    ReadProcessMemory(PHandle, (LPCVOID)(basePtr + 0x14), &p1, 4, NULL);
    if (!p1) return;

    ReadProcessMemory(PHandle, (LPCVOID)(p1 + 0x4C4), &p2, 4, NULL);
    if (!p2) return;

    DWORD finalAddr = p2 + 0x73C;
    WriteProcessMemory(PHandle, (LPVOID)finalAddr, &value, 4, NULL);

    DoBeep();
    SafeCloseProcessHandle();
}

// ---------------- Running Update Title ----------------
static int titlePos = 0; // Anchor

VOID CALLBACK RunningUpdateTitle(HWND hwnd, UINT uMsg, UINT_PTR idEvent, DWORD dwTime) {
    static const char titleText[] = " Prince of Persia The Sand of Time Trainer - Prince of Persia The Sand of Time Trainer -";
    char displayText[44];
    int len = (int)strlen(titleText);

    titlePos = (titlePos + 1) % len;

    int bufIndex = 0;

    for (int i = titlePos; i < len && bufIndex < (int)sizeof(displayText) - 1; i++) {
        displayText[bufIndex++] = titleText[i];
    }

    for (int j = 0; j < titlePos && bufIndex < (int)sizeof(displayText) - 1; j++) {
        displayText[bufIndex++] = titleText[j];
    }

    // Null terminate
    displayText[bufIndex] = '\0';

    SetWindowText(hwnd, displayText);
}

// ---------------- Window procedure ----------------
// Allow dragging from client area by returning HTCAPTION from WM_NCHITTEST when appropriate.
LRESULT CALLBACK WndProc(HWND hWnd, UINT message, WPARAM wParam, LPARAM lParam) {
    switch (message) {
    case WM_CREATE:
        CreateWindow("BUTTON", "Disable (0)", WS_VISIBLE | WS_CHILD, 20, 10, 120, 24, hWnd, (HMENU)IDC_BTN_DISABLE, NULL, NULL);
        CreateWindow("BUTTON", "Sand Tanks (1)", WS_VISIBLE | WS_CHILD, 150, 10, 120, 24, hWnd, (HMENU)IDC_BTN_SAND, NULL, NULL);
        CreateWindow("BUTTON", "Power Tanks (2)", WS_VISIBLE | WS_CHILD, 20, 40, 120, 24, hWnd, (HMENU)IDC_BTN_POWER, NULL, NULL);
        CreateWindow("BUTTON", "Recall (3)", WS_VISIBLE | WS_CHILD, 150, 40, 120, 24, hWnd, (HMENU)IDC_BTN_RECALL, NULL, NULL);
        CreateWindow("BUTTON", "Slow Motion (4)", WS_VISIBLE | WS_CHILD, 20, 70, 120, 24, hWnd, (HMENU)IDC_BTN_SLOW, NULL, NULL);
        CreateWindow("BUTTON", "Max Health (5)", WS_VISIBLE | WS_CHILD, 150, 70, 120, 24, hWnd, (HMENU)IDC_BTN_HEALTH, NULL, NULL);
        CreateWindow("BUTTON", "Max Sword (6)", WS_VISIBLE | WS_CHILD, 20, 100, 120, 24, hWnd, (HMENU)IDC_BTN_SWORDSTATE_3RD, NULL, NULL);
        CreateWindow("BUTTON", "2nd Sword (7)", WS_VISIBLE | WS_CHILD, 150, 100, 120, 24, hWnd, (HMENU)IDC_BTN_SWORDSTATE_2ND, NULL, NULL);
        CreateWindow("BUTTON", "1st Sword (8)", WS_VISIBLE | WS_CHILD, 20, 130, 120, 24, hWnd, (HMENU)IDC_BTN_SWORDSTATE_1ST, NULL, NULL);
        CreateWindow("BUTTON", "Stock Sword (9)", WS_VISIBLE | WS_CHILD, 150, 130, 120, 24, hWnd, (HMENU)IDC_BTN_SWORDSTATE_ZERO, NULL, NULL);
        CreateWindow("BUTTON", "Close (End)", WS_VISIBLE | WS_CHILD, 20, 190, 120, 28, hWnd, (HMENU)IDC_BTN_EXIT, NULL, NULL);
        CreateWindow("BUTTON", "Quit Game (Home)", WS_VISIBLE | WS_CHILD, 150, 190, 120, 28, hWnd, (HMENU)IDC_BTN_GAMEEXIT, NULL, NULL);
        
        hStatus = CreateWindow("STATIC", "Waiting for game...", WS_VISIBLE | WS_CHILD, 20, 230, 250, 20, hWnd, NULL, NULL, NULL);

        // Timers: Game detection every 1s, hotkey scan every 150ms
        SetTimer(hWnd, IDT_GAMESTATE, 1000, NULL);
        SetTimer(hWnd, IDT_HOTKEY, 150, NULL);
        break;

    case WM_NCHITTEST: {
        LRESULT hit = DefWindowProc(hWnd, message, wParam, lParam);
        if (hit == HTCLIENT) return HTCAPTION; // allow dragging by client
        return hit;
    }

    case WM_COMMAND:
        switch (LOWORD(wParam)) {
        case IDC_BTN_DISABLE: Disabled(); break;
        case IDC_BTN_SAND: SandTanks(); break;
        case IDC_BTN_POWER: PowerTanks(); break;
        case IDC_BTN_RECALL: Recall(); break;
        case IDC_BTN_SLOW: SlowMotion(); break;
        case IDC_BTN_HEALTH: Health(); break;
        case IDC_BTN_SWORDSTATE_3RD: SetSwordState(3); break;
        case IDC_BTN_SWORDSTATE_2ND: SetSwordState(2); break;
        case IDC_BTN_SWORDSTATE_1ST: SetSwordState(1); break;
        case IDC_BTN_SWORDSTATE_ZERO: SetSwordState(0); break;
        case IDC_BTN_EXIT: PostMessage(hWnd, WM_CLOSE, 0, 0); break;
        case IDC_BTN_GAMEEXIT: PostMessage(GameWindow, WM_QUIT, 0, 0); break;

        }
        break;

    case WM_TIMER:
		GameWindow = FindWindowA(NULL, "Prince of Persia");
        // Running Update Title
        if (wParam == IDT_TITLE)
            RunningUpdateTitle(hMainWnd, 0, 0, 0);

        if (wParam == IDT_GAMESTATE) {
            if (FindWindowA(NULL, "Prince of Persia") || FindWindowA(NULL, "Prince of Persia : Sands of Time"))
            { SetWindowText(hStatus, "Game detected!"); } else { SetWindowText(hStatus, "Please! Run the Game."); }
        } else if (wParam == IDT_HOTKEY) {
            // hotkeys (MSVC used GetAsyncKeyState with keys '0'..'9', END, HOME, LWIN, RWIN)
            if (GetAsyncKeyState('0') & 0x8000) Disabled();
            else if (GetAsyncKeyState('1') & 0x8000) SandTanks();
            else if (GetAsyncKeyState('2') & 0x8000) PowerTanks();
            else if (GetAsyncKeyState('3') & 0x8000) Recall();
            else if (GetAsyncKeyState('4') & 0x8000) SlowMotion();
            else if (GetAsyncKeyState('5') & 0x8000) Health();
            else if (GetAsyncKeyState('6') & 0x8000) SetSwordState(3);
            else if (GetAsyncKeyState('7') & 0x8000) SetSwordState(2);
            else if (GetAsyncKeyState('8') & 0x8000) SetSwordState(1);
            else if (GetAsyncKeyState('9') & 0x8000) SetSwordState(0);
            else if (GetAsyncKeyState(VK_END) & 0x8000) PostMessage(hWnd, WM_CLOSE, 0, 0);
            else if ((GetAsyncKeyState(VK_HOME) & 0x8000) && GameWindow) PostMessage(GameWindow, WM_QUIT, 0, 0);
            else if ((GetAsyncKeyState(VK_LWIN) & 0x8000) && GameWindow) PostMessage(GameWindow, WM_SYSCOMMAND, SC_MINIMIZE, 0);
            else if ((GetAsyncKeyState(VK_RWIN) & 0x8000) && GameWindow) PostMessage(GameWindow, WM_SYSCOMMAND, SC_MINIMIZE, 0);
		}
        break;

    case WM_CLOSE:
        KillTimer(hWnd, IDT_TITLE);
        KillTimer(hWnd, IDT_GAMESTATE);
        KillTimer(hWnd, IDT_HOTKEY);
        DestroyWindow(hWnd);
        break;

    case WM_DESTROY:
        SafeCloseProcessHandle();
        PostQuitMessage(0);
        break;

    default:
        return DefWindowProc(hWnd, message, wParam, lParam);
    }
    return 0;
}

// ---------------- WinMain ----------------
int APIENTRY WinMain(HINSTANCE hInstance,
                     HINSTANCE hPrevInstance,
                     LPSTR     lpCmdLine,
                     int       nCmdShow)
{   
    WNDCLASS wc = {0};
    wc.style = CS_HREDRAW | CS_VREDRAW;
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hIcon = LoadIcon(hInstance, MAKEINTRESOURCE(1));
    wc.hbrBackground = (HBRUSH)(COLOR_WINDOW + 1);
    wc.lpszClassName = "POPTSOTTrainerClass";
    RegisterClass(&wc);

    hMainWnd = CreateWindow("POPTSOTTrainerClass", "Prince of Persia The Sand of Time Trainer",
	                    WS_OVERLAPPEDWINDOW & ~(WS_THICKFRAME | WS_MAXIMIZEBOX),
                            CW_USEDEFAULT, CW_USEDEFAULT, 300, 300,
                            NULL, NULL, hInstance, NULL);

    if (!hMainWnd) return 0;

    SetTimer(hMainWnd, 1, 400, NULL); // Running Update Title

    ShowWindow(hMainWnd, SW_SHOWNORMAL);
    UpdateWindow(hMainWnd);

    MSG msg;

    // Main Loop
    while (true)
    {
        // Get all message in queue
        while (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
        {
            if (msg.message == WM_QUIT)
                return (int)msg.wParam;

            TranslateMessage(&msg);
            DispatchMessage(&msg);
        }

        Sleep(5); 
    }

    return 0;
}

