#include <windows.h>
#include <stdio.h>

#define ID_BUTTON_ADD 1
#define ID_BUTTON_SUB 2
#define ID_BUTTON_MUL 3
#define ID_BUTTON_DIV 4
#define ID_EDIT1 5
#define ID_EDIT2 6

LRESULT CALLBACK WndProc(HWND hwnd, UINT Message, WPARAM wParam, LPARAM lParam) {
    static HWND hEdit1, hEdit2, hLabel;
    char num1[100], num2[100];
    double result, n1, n2;

    switch (Message) {
        case WM_CREATE:
            // Label for instruction
            hLabel = CreateWindow("STATIC", "Please input two numbers", WS_CHILD | WS_VISIBLE,
                20, 10, 200, 20, hwnd, NULL, NULL, NULL);
            SendMessage(hLabel, WM_SETFONT, (WPARAM)GetStockObject(DEFAULT_GUI_FONT), TRUE);
            
            // Input fields
            hEdit1 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                20, 40, 100, 20, hwnd, (HMENU)ID_EDIT1, NULL, NULL);
            hEdit2 = CreateWindowEx(0, "EDIT", "", WS_CHILD | WS_VISIBLE | WS_BORDER | ES_NUMBER,
                20, 70, 100, 20, hwnd, (HMENU)ID_EDIT2, NULL, NULL);

            // Buttons
            CreateWindow("BUTTON", "+", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                20, 100, 40, 30, hwnd, (HMENU)ID_BUTTON_ADD, NULL, NULL);
            CreateWindow("BUTTON", "-", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                70, 100, 40, 30, hwnd, (HMENU)ID_BUTTON_SUB, NULL, NULL);
            CreateWindow("BUTTON", "*", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                120, 100, 40, 30, hwnd, (HMENU)ID_BUTTON_MUL, NULL, NULL);
            CreateWindow("BUTTON", "/", WS_TABSTOP | WS_VISIBLE | WS_CHILD | BS_DEFPUSHBUTTON,
                170, 100, 40, 30, hwnd, (HMENU)ID_BUTTON_DIV, NULL, NULL);
            break;

        case WM_COMMAND:
            if (HIWORD(wParam) == BN_CLICKED) {
                int id = LOWORD(wParam);
                GetWindowText(hEdit1, num1, 100);
                GetWindowText(hEdit2, num2, 100);
                n1 = atof(num1);
                n2 = atof(num2);
                
                switch (id) {
                    case ID_BUTTON_ADD:
                        result = n1 + n2;
                        break;
                    case ID_BUTTON_SUB:
                        result = n1 - n2;
                        break;
                    case ID_BUTTON_MUL:
                        result = n1 * n2;
                        break;
                    case ID_BUTTON_DIV:
                        if (n2 != 0) {
                            result = n1 / n2;
                        } else {
                            MessageBox(hwnd, "Cannot divide by zero!", "Error", MB_ICONEXCLAMATION | MB_OK);
                            return 0;
                        }
                        break;
                    default:
                        return 0;
                }
                
                char resultStr[100];
                sprintf(resultStr, "Result: %.2f", result);
                MessageBox(hwnd, resultStr, "Result", MB_OK);
            }
            break;

        case WM_DESTROY:
            PostQuitMessage(0);
            break;

        default:
            return DefWindowProc(hwnd, Message, wParam, lParam);
    }
    return 0;
}

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow) {
    WNDCLASSEX wc;
    HWND hwnd;
    MSG msg;

    memset(&wc, 0, sizeof(wc));
    wc.cbSize = sizeof(WNDCLASSEX);
    wc.lpfnWndProc = WndProc;
    wc.hInstance = hInstance;
    wc.hCursor = LoadCursor(NULL, IDC_ARROW);
    wc.hbrBackground = CreateSolidBrush(RGB(255, 0, 102)); // สีชมพูเข้ม
    wc.lpszClassName = "WindowClass";
    wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
    wc.hIconSm = LoadIcon(NULL, IDI_APPLICATION);

    if (!RegisterClassEx(&wc)) {
        MessageBox(NULL, "Window Registration Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    hwnd = CreateWindowEx(WS_EX_CLIENTEDGE, "WindowClass", "My Calculator",
        WS_VISIBLE | WS_OVERLAPPEDWINDOW & ~WS_SIZEBOX, CW_USEDEFAULT, CW_USEDEFAULT,
        250, 200, NULL, NULL, hInstance, NULL);

    if (hwnd == NULL) {
        MessageBox(NULL, "Window Creation Failed!", "Error!", MB_ICONEXCLAMATION | MB_OK);
        return 0;
    }

    while (GetMessage(&msg, NULL, 0, 0) > 0) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    return msg.wParam;
}