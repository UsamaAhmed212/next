#include <windows.h>
#include <stdbool.h> // For bool type

// To track the sequence of key presses
int keyPressCount = 0;

LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT *)lParam;

        if (wParam == WM_KEYDOWN) {
            // Reset count for any key press other than 'R', 'I', 'E'
            // if (pKeyboard->vkCode != 0x52 && pKeyboard->vkCode != 0x49 && pKeyboard->vkCode != 0x45) {
            //     keyPressCount = 0; // Reset the counter for any other key
            // }

            // Check if Shift is pressed
            bool isShiftPressed = (GetKeyState(VK_SHIFT) & 0x8000);
            
            INPUT input[2] = {0};

            switch (pKeyboard->vkCode) {
                case 0x52: // 'R'
                    keyPressCount = 1; // Start counting for 'rie'
                    return 1; // Block original 'R'
                    
                case 0x49: // 'I'
                    // Simulate typing 'ই' (lowercase i)
                    input[0].type = INPUT_KEYBOARD;
                    input[0].ki.wScan = 0x0987; // Unicode for 'ই'
                    input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                    SendInput(1, &input[0], sizeof(INPUT));

                    input[1].type = INPUT_KEYBOARD;
                    input[1].ki.wScan = 0x0987; // Unicode for 'ই'
                    input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                    SendInput(1, &input[1], sizeof(INPUT));
                    
                    if (keyPressCount == 1) {
                        keyPressCount = 2; // Increment count to indicate 'rie' is in progress
                    } else {
                        keyPressCount = 0; // Reset if 'I' is pressed out of order
                    }
                    return 1; // Block original 'I'
                    
                case 0x45: // 'E'
                    if (keyPressCount == 2) {
                        // Simulate pressing Backspace
                        {
                            INPUT input[2] = {0};

                            // Key down for Backspace
                            input[0].type = INPUT_KEYBOARD;
                            input[0].ki.wVk = VK_BACK; // Virtual key code for Backspace
                            input[0].ki.dwFlags = 0; // Key down
                            SendInput(1, &input[0], sizeof(INPUT));

                            // Key up for Backspace
                            input[1].type = INPUT_KEYBOARD;
                            input[1].ki.wVk = VK_BACK; // Virtual key code for Backspace
                            input[1].ki.dwFlags = KEYEVENTF_KEYUP; // Key up
                            SendInput(1, &input[1], sizeof(INPUT));
                        }

                        // Simulate typing 'ঋ' (Unicode for 'ঋ')
                        {
                            INPUT input[2] = {0};

                            input[0].type = INPUT_KEYBOARD;
                            input[0].ki.wScan = 0x098B; // Unicode for 'ঋ'
                            input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                            SendInput(1, &input[0], sizeof(INPUT));

                            input[1].type = INPUT_KEYBOARD;
                            input[1].ki.wScan = 0x098B; // Unicode for 'ঋ'
                            input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                            SendInput(1, &input[1], sizeof(INPUT));
                        }
                        keyPressCount = 0; // Reset the counter after the sequence
                        return 1; // Block original 'E'
                    } else {
                        keyPressCount = 0; // Reset if 'E' is pressed out of order
                    }
                    
                    // Simulate typing 'এ' (lowercase e)
                    input[0].type = INPUT_KEYBOARD;
                    input[0].ki.wScan = 0x098f; // Unicode for 'এ'
                    input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                    SendInput(1, &input[0], sizeof(INPUT));

                    input[1].type = INPUT_KEYBOARD;
                    input[1].ki.wScan = 0x098f; // Unicode for 'এ'
                    input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                    SendInput(1, &input[1], sizeof(INPUT));
                    return 1; // Block original 'E'
            }
        }
    }
    return CallNextHookEx(NULL, nCode, wParam, lParam);
}

int main() {
    // Set the low-level keyboard hook
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
