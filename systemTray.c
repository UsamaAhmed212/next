#include <windows.h>
#include <shellapi.h>

NOTIFYICONDATA nid;

// Window Procedure to handle messages
LRESULT CALLBACK WindowProc(HWND hwnd, UINT uMsg, WPARAM wParam, LPARAM lParam) {
    switch (uMsg) {
        case WM_APP:
            if (lParam == WM_RBUTTONUP) {
                // Handle right-click on the tray icon
                MessageBox(NULL, "SpikE Right-click on the tray icon!", "Info", MB_OK);
            } else if (lParam == WM_LBUTTONDBLCLK) {
                // Handle double-click on the tray icon
                MessageBox(NULL, "SpikE Double-click on the tray icon!", "Info", MB_OK);
            }
            break;
        case WM_DESTROY:
            Shell_NotifyIcon(NIM_DELETE, &nid); // Remove the icon
            PostQuitMessage(0);
            break;
        default:
            return DefWindowProc(hwnd, uMsg, wParam, lParam);
    }
    return 0;
}

int main() {
    HINSTANCE hInstance = GetModuleHandle(NULL);
    
    // Register the window class
    WNDCLASS wc = {0};
    wc.lpfnWndProc = WindowProc;
    wc.hInstance = hInstance;
    wc.lpszClassName = "TrayApp";
    RegisterClass(&wc);
    
    // Create the hidden window
    HWND hwnd = CreateWindow("TrayApp", "Tray Application", WS_OVERLAPPEDWINDOW,
                             CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT, CW_USEDEFAULT,
                             NULL, NULL, hInstance, NULL);
    
    // Set up the tray icon
    nid.cbSize = sizeof(NOTIFYICONDATA);
    nid.hWnd = hwnd;
    nid.uID = 1;
    nid.uFlags = NIF_ICON | NIF_MESSAGE | NIF_TIP;
    nid.hIcon = (HICON)LoadImage(NULL, "keyboard.ico", IMAGE_ICON, 0, 0, LR_LOADFROMFILE); // Load your icon
    nid.uCallbackMessage = WM_APP;
    strcpy(nid.szTip, "Keyboard Application"); // Tooltip text
    
    Shell_NotifyIcon(NIM_ADD, &nid); // Add the icon to the tray
    
    // Hide the window
    ShowWindow(hwnd, SW_HIDE);

    // Message loop
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }
    
    return 0;
}
