#include <windows.h>
#include <stdbool.h> // Include this for bool type

LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT *)lParam;

        if (wParam == WM_KEYDOWN) {
            bool isShiftPressed = (GetKeyState(VK_SHIFT) & 0x8000); // Check if Shift is pressed
            INPUT input[2] = {0};

            switch (pKeyboard->vkCode) {
                case 0x41: // 'A' or 'a'
                    if (isShiftPressed) {
                        // Simulate typing 'আ'
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = 0x0986; // Unicode for 'আ'
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input[0], sizeof(INPUT));

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = 0x0986; // Unicode for 'আ'
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                        SendInput(1, &input[1], sizeof(INPUT));
                        return 1; // Block original 'A'
                    } else {
                        // Simulate typing 'অ'
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = 0x0985; // Unicode for 'অ'
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input[0], sizeof(INPUT));

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = 0x0985; // Unicode for 'অ'
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                        SendInput(1, &input[1], sizeof(INPUT));
                        return 1; // Block original 'a'
                    }
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    HHOOK hKeyboardHook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, NULL, 0);
    
    if (hKeyboardHook == NULL) {
        MessageBox(NULL, "Failed to set hook!", "Error", MB_ICONERROR);
        return 1; // Exit if the hook couldn't be set
    }

    // Message loop to keep the hook active
    MSG msg;
    while (GetMessage(&msg, NULL, 0, 0)) {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    // Unhook when done
    UnhookWindowsHookEx(hKeyboardHook);
    return 0;
}
