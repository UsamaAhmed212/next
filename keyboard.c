#include <windows.h>
#include <stdbool.h> // Include for bool type

LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT *)lParam;

        if (wParam == WM_KEYDOWN) {
            bool isShiftPressed = (GetKeyState(VK_SHIFT) & 0x8000); // Check if Shift is pressed
            INPUT input[2] = {0}; // Array for sending key input

            switch (pKeyboard->vkCode) {
                case 0x41: // 'A' or 'a'
                    if (isShiftPressed) {
                        // Simulate typing 'আ' (uppercase A)
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = 0x0986; // Unicode for 'আ'
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input[0], sizeof(INPUT));

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = 0x0986; // Unicode for 'আ'
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                        SendInput(1, &input[1], sizeof(INPUT));
                    } else {
                        // Simulate typing 'অ' (lowercase a)
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = 0x0985; // Unicode for 'অ'
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input[0], sizeof(INPUT));

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = 0x0985; // Unicode for 'অ'
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                        SendInput(1, &input[1], sizeof(INPUT));
                    }
                    return 1; // Block original 'A' or 'a'

                case 0x49: // 'I' or 'i'
                    if (isShiftPressed) {
                        // Simulate typing 'ঈ' (uppercase I)
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = 0x0988; // Unicode for 'ঈ'
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input[0], sizeof(INPUT));

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = 0x0988; // Unicode for 'ঈ'
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                        SendInput(1, &input[1], sizeof(INPUT));
                    } else {
                        // Simulate typing 'ই' (lowercase i)
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = 0x0987; // Unicode for 'ই'
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input[0], sizeof(INPUT));

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = 0x0987; // Unicode for 'ই'
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                        SendInput(1, &input[1], sizeof(INPUT));
                    }
                    return 1; // Block original 'I' or 'i'

                case 0x55: // 'U' or 'u'
                    if (isShiftPressed) {
                        // Simulate typing 'ঊ' (uppercase U)
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = 0x098A; // Unicode for 'ঊ'
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input[0], sizeof(INPUT));

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = 0x098A; // Unicode for 'ঊ'
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                        SendInput(1, &input[1], sizeof(INPUT));
                    } else {
                        // Simulate typing 'উ' (lowercase u)
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = 0x0989; // Unicode for 'উ'
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input[0], sizeof(INPUT));

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = 0x0989; // Unicode for 'উ'
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                        SendInput(1, &input[1], sizeof(INPUT));
                    }
                    return 1; // Block original 'U' or 'u'

                case 0x45: // 'E' or 'e'
                    if (isShiftPressed) {
                        // Simulate typing 'ঐ' (uppercase E)
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = 0x098F; // Unicode for 'ঐ'
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input[0], sizeof(INPUT));

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = 0x098F; // Unicode for 'ঐ'
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                        SendInput(1, &input[1], sizeof(INPUT));
                    } else {
                        // Simulate typing 'এ' (lowercase e)
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = 0x0986; // Unicode for 'এ'
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input[0], sizeof(INPUT));

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = 0x0986; // Unicode for 'এ'
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                        SendInput(1, &input[1], sizeof(INPUT));
                    }
                    return 1; // Block original 'E' or 'e'

                case 0x4F: // 'O' or 'o'
                    if (isShiftPressed) {
                        // Simulate typing 'ঔ' (uppercase O)
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = 0x0994; // Unicode for 'ঔ'
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input[0], sizeof(INPUT));

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = 0x0994; // Unicode for 'ঔ'
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                        SendInput(1, &input[1], sizeof(INPUT));
                    } else {
                        // Simulate typing 'ও' (lowercase o)
                        input[0].type = INPUT_KEYBOARD;
                        input[0].ki.wScan = 0x0993; // Unicode for 'ও'
                        input[0].ki.dwFlags = KEYEVENTF_UNICODE;
                        SendInput(1, &input[0], sizeof(INPUT));

                        input[1].type = INPUT_KEYBOARD;
                        input[1].ki.wScan = 0x0993; // Unicode for 'ও'
                        input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
                        SendInput(1, &input[1], sizeof(INPUT));
                    }
                    return 1; // Block original 'O' or 'o'

                // Handle more vowel mappings here if needed
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
