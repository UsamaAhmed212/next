#include <stdio.h>
#include <windows.h>
#include <stdbool.h> // Include for bool type

// Define Unicode values for vowels (স্বরবর্ণ)
const wchar_t vowels[] = {
    0x985,  // অ
    0x986,  // আ
    0x987,  // ই
    0x988,  // ঈ
    0x989,  // উ
    0x98A,  // ঊ
    0x98B,  // ঋ
    0x98C,  // ঌ
    0x98F,  // এ
    0x990,  // ঐ
    0x993,  // ও
    0x994   // ঔ
};

const wchar_t vowel_signs[] = {
    0x9BE,  // া
    0x9BF,  // ি
    0x9C0,  // ী
    0x9C1,  // ু
    0x9C2,  // ূ
    0x9C3,  // ৃ
    0x9C7,  // ে
    0x9C8,  // ৈ
    0x9CB,  // ো
    0x9CC   // ৌ
};

// Define Unicode values for consonants (ব্যঞ্জনবর্ণ)
const wchar_t consonants[] = {
    0x995,  // ক
    0x996,  // খ
    0x997,  // গ
    0x998,  // ঘ
    0x999,  // ঙ
    0x99A,  // চ
    0x99B,  // ছ
    0x99C,  // জ
    0x99D,  // ঝ
    0x99E,  // ঞ
    0x99F,  // ট
    0x9A0,  // ঠ
    0x9A1,  // ড
    0x9A2,  // ঢ
    0x9A3,  // ণ
    0x9A4,  // ত
    0x9A5,  // থ
    0x9A6,  // দ
    0x9A7,  // ধ
    0x9A8,  // ন
    0x9AA,  // প
    0x9AB,  // ফ
    0x9AC,  // ব
    0x9AD,  // ভ
    0x9AE,  // ম
    0x9AF,  // য
    0x9B0,  // র
    0x9B2,  // ল
    0x9B6,  // শ
    0x9B7,  // ষ
    0x9B8,  // স
    0x9B9,  // হ
    0x9DC,  // ড়
    0x9DD,  // ঢ়
    0x9DF,  // য়
    0x9F0,  // র‍্য
    0x9F1   // ঱ (used in some dialects)
};


// Function to check if a Unicode character is a vowel
bool isVowel(wchar_t unicodeChar) {
    for (int i = 0; i < sizeof(vowels) / sizeof(vowels[0]); i++) {
        if (unicodeChar == vowels[i]) {
            return true;
        }
    }
    return false;
}

// Function to check if a Unicode character is a vowel
bool isVowelSign(wchar_t unicodeChar) {
    for (int i = 0; i < sizeof(vowel_signs) / sizeof(vowel_signs[0]); i++) {
        if (unicodeChar == vowel_signs[i]) {
            return true;
        }
    }
    return false;
}

// Function to check if a Unicode character is a consonant
bool isConsonant(wchar_t unicodeChar) {
    for (int i = 0; i < sizeof(consonants) / sizeof(consonants[0]); i++) {
        if (unicodeChar == consonants[i]) {
            return true;
        }
    }
    return false;
}

void SendBackspace(int count) {
    printf("SendBackspace() Function run \n");

    INPUT input[4]; // Maximum of 2 backspaces, hence 4 inputs (2 down + 2 up)

    for (int i = 0; i < count; i++) {
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
}

void push(wchar_t** arr, int* size, wchar_t value) {
    *size += 1;
    *arr = realloc(*arr, *size * sizeof(wchar_t)); // Resize the array
    if (*arr == NULL) {
        fwprintf(stderr, L"Memory allocation failed\n");
        exit(1);
    }
    (*arr)[*size - 1] = value; // Add the new element at the end
}


// To track the sequence of key presses 'ঋ'
int rie_keyPressCount = 0;

// Function to process key Press Count 'ঋ'
void rie_keyPressCountProcess(wchar_t unicodeChar) {
    // printf("Key pressed: 0x%X \n", unicodeChar);  // Del

    if (unicodeChar == 0x9B0) {  // 'র'
        rie_keyPressCount = 1; // Start counting for 'ঋ'
    } else if (unicodeChar == 0x987 || unicodeChar == 0x9BF || unicodeChar == 0x988 || unicodeChar == 0x9C0) {  // 'ই' || 'ি' || 'ঈ' || 'ী'
        // printf("unicodeChar: 0x%X \n", unicodeChar);  // Del
        // printf("rie_keyPressCount Inside 'I': %d\n", rie_keyPressCount);  // Del
        if (rie_keyPressCount == 1) {
            rie_keyPressCount = 2; // Increment count to indicate 'ঋ' is in progress
        } else {
            rie_keyPressCount = 0; // Reset if 'ই' is pressed out of order
        }
    } else {
        rie_keyPressCount = 0; // Reset the rie(ঋ) counter for any other key press
    }
}










// Function to determine if Shift is pressed
bool isShiftPressed() {
    return (GetAsyncKeyState(VK_LSHIFT) & 0x8000) || (GetAsyncKeyState(VK_RSHIFT) & 0x8000);
}

// Function to determine if Caps Lock is on
bool isCapsLockOn() {
    return (GetKeyState(VK_CAPITAL) & 0x0001) != 0;
}

// Function to determine if the pressed key should be uppercase
bool isUppercase() {
    return isShiftPressed() ^ isCapsLockOn(); // XOR to determine uppercase condition
}

// Track last key press Unicode Character
wchar_t lastKeyPressUnicodeChar = 0;

wchar_t* lastKeyPressUnicodeCharArray = NULL;
int unicodeCharArraySize = 0;

// Send Unicode character as keyboard input
void SendUnicodeChar(wchar_t unicodeChar) {
    // Check if the character is not Backspace (Unicode 0x8)  and not a vowel sign
    if (unicodeChar != 0x8 && !isVowelSign(unicodeChar)) {
        lastKeyPressUnicodeChar = unicodeChar; // Update last key press Unicode character

        push(&lastKeyPressUnicodeCharArray, &unicodeCharArraySize, unicodeChar); // Add the character to the array and update the array size
    }


    // printf("Loop Start \n");
    // printf("Size %d \n", unicodeCharArraySize);
    // for (int i = 0; i < unicodeCharArraySize; i++) {
    //     printf("0x%X \n", lastKeyPressUnicodeCharArray[i]);
    // }
    // printf("NExT Print \n");
    // printf("0x%X \n", lastKeyPressUnicodeCharArray[unicodeCharArraySize - 2]);
    
    rie_keyPressCountProcess(unicodeChar);  // 'ঋ'

    // printf("Size %d \n", unicodeCharArraySize);

    // printf("0x%X \n", lastKeyPressUnicodeCharArray[unicodeCharArraySize - 3]);

    // printf("Key pressed: 0x%X \n", unicodeChar);
    
    // printf("Key Code: %d\n", unicodeChar);

    // if (unicodeChar == 0x8) {
    //     printf("Yes\n");
    // } else {
    //     printf("NO\n");
    // }

    INPUT input[2] = {0}; // Array for sending key input

    // Simulate key press
    input[0].type = INPUT_KEYBOARD;
    input[0].ki.wScan = unicodeChar; // Unicode value of the character
    input[0].ki.dwFlags = KEYEVENTF_UNICODE;
    SendInput(1, &input[0], sizeof(INPUT));

    // Simulate key release
    input[1].type = INPUT_KEYBOARD;
    input[1].ki.wScan = unicodeChar;
    input[1].ki.dwFlags = KEYEVENTF_KEYUP | KEYEVENTF_UNICODE;
    SendInput(1, &input[1], sizeof(INPUT));

    
    // Alternative way

    // INPUT input = {0};

    // // Send the custom Unicode character
    // input.type = INPUT_KEYBOARD;
    // input.ki.wScan = unicodeChar; // Set the Unicode character
    // input.ki.dwFlags = KEYEVENTF_UNICODE; // Indicate Unicode input
    // SendInput(1, &input, sizeof(INPUT));
    
    // // Release the key (if needed)
    // input.ki.dwFlags = KEYEVENTF_KEYUP;
    // SendInput(1, &input, sizeof(INPUT));
}


LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam) {
    if (nCode == HC_ACTION) {
        KBDLLHOOKSTRUCT *pKeyboard = (KBDLLHOOKSTRUCT *)lParam;

        if (wParam == WM_KEYDOWN || wParam == WM_SYSKEYDOWN) {
            // bool isShiftPressed = (GetAsyncKeyState(VK_SHIFT) & 0x8000);  // Check if Shift is pressed
            
            bool isCtrlPressed = (GetAsyncKeyState(VK_CONTROL) & 0x8000);  // Check if Ctrl is pressed

            bool isAltPressed = (GetAsyncKeyState(VK_MENU) & 0x8000);  // Check if Alt is pressed
            
            switch (pKeyboard->vkCode) {
                case VK_SPACE:  // Space key
                    SendUnicodeChar(0x20);  // Unicode for space
                    return 1; // Block original space key

                case VK_BACK:  // Backspace key
                    SendUnicodeChar(0x8);  // Unicode for backspace (ASCII 8)
                    // printf("BlockSpace key Press \n");
                    return 0; // Block original backspace key


                /**
                ** Vowel (স্বরবর্ণ) Key Mapping 
                **/
                case 0x41: // 'A' or 'a'
                    if (isCtrlPressed) return 0; // Allow original key input if Ctrl key is pressed

                    if (!isUppercase()) {
                        // Handle Lowercase 'a'
                        if (!isConsonant(lastKeyPressUnicodeChar)) {
                            SendUnicodeChar(0x985);  // 'অ'
                        } else {
                            SendUnicodeChar(0x9be);  // 'া'
                        }
                    } else {
                        // Handle Uppercase 'A'
                        if (!isConsonant(lastKeyPressUnicodeChar)) {
                            SendUnicodeChar(0x986);  // 'আ'
                        } else {
                            SendUnicodeChar(0x9be);  // 'া'
                        }
                    }
                    return 1; // Block original 'A' or 'a'


                case 0x49: // 'I' or 'i'
                    if (isCtrlPressed) return 0; // Allow original key input if Ctrl key is pressed

                    if (!isUppercase()) {
                        // Handle Lowercase 'i'
                        if (!isConsonant(lastKeyPressUnicodeChar)) {
                            SendUnicodeChar(0x987);  // 'ই'
                        } else {
                            SendUnicodeChar(0x9BF);  // 'ি'
                        }
                    } else {
                        // Handle Uppercase 'I'
                        if (!isConsonant(lastKeyPressUnicodeChar)) {
                            SendUnicodeChar(0x988);  // 'ঈ'
                        } else {
                            SendUnicodeChar(0x9C0);  // 'ী'
                        }
                    }
                    return 1; // Block original 'I' or 'i'


                case 0x55: // 'U' or 'u'
                    if (isCtrlPressed) return 0; // Allow original key input if Ctrl key is pressed

                    if (!isUppercase()) {
                        // Handle Lowercase 'u'
                        if (!isConsonant(lastKeyPressUnicodeChar)) {
                            SendUnicodeChar(0x989);  // 'উ'
                        } else {
                            SendUnicodeChar(0x9C1);  // 'ু'
                        }
                    } else {
                        // Handle Uppercase 'U'
                        if (!isConsonant(lastKeyPressUnicodeChar)) {
                            SendUnicodeChar(0x98A);  // 'ঊ'
                        } else {
                            SendUnicodeChar(0x9C2);  // 'ূ'
                        }
                    }
                    return 1; // Block original 'U' or 'u'


                case 0x45: // 'E' or 'e'
                    if (rie_keyPressCount == 2) {
                        SendBackspace(2);  // Send two backspaces

                        if (unicodeCharArraySize < 3 || !isConsonant(lastKeyPressUnicodeCharArray[unicodeCharArraySize - 3])) {
                            SendUnicodeChar(0x98B);  // 'ঋ'
                        } else {
                            SendUnicodeChar(0x9C3);  // 'ৃ'
                        }
                        return 1; // Block original 'E' or 'e'
                    }
                    
                    if (isCtrlPressed) return 0; // Allow original key input if Ctrl key is pressed

                    if (!isUppercase()) {
                        // Handle Lowercase 'e'
                        if (!isConsonant(lastKeyPressUnicodeChar)) {
                        SendUnicodeChar(0x98F);  // 'এ'
                        } else {
                            SendUnicodeChar(0x9C7);  // 'ে'
                        }
                    } else {
                        // Handle Uppercase 'E'
                        if (!isConsonant(lastKeyPressUnicodeChar)) {
                            SendUnicodeChar(0x990);  // 'ঐ'
                        } else {
                            SendUnicodeChar(0x9C8);  // 'ৈ'
                        }
                    }
                    return 1; // Block original 'E' or 'e'


                case 0x4F: // 'O' or 'o'
                    if (isCtrlPressed) return 0; // Allow original key input if Ctrl key is pressed

                    if (!isUppercase()) {
                        // Handle Lowercase 'o'
                        if (!isConsonant(lastKeyPressUnicodeChar)) {
                            SendUnicodeChar(0x993);  // 'ও'
                        } else {
                            SendUnicodeChar(0x9CB);  // 'ো'
                        }
                    } else {
                        // Handle Uppercase 'O'
                        if (!isConsonant(lastKeyPressUnicodeChar)) {
                            SendUnicodeChar(0x994);  // 'ঔ'
                        } else {
                            SendUnicodeChar(0x9CC);  // 'ৌ'
                        }
                    }
                    return 1; // Block original 'O' or 'o'


                /**
                ** Consonant (ব্যঞ্জনবর্ণ)	Key Mapping
                **/
               case 0x4B: // 'K' or'k'
                    if (isCtrlPressed) return 0; // Allow original key input if Ctrl key is pressed
               
                    if (!isUppercase()) {
                        // Handle Lowercase 'k'
                        SendUnicodeChar(0x995);  // 'ক'
                    } else {
                        // Handle Uppercase 'K'
                        SendUnicodeChar(0x996);  // 'খ'
                    }
                    return 1; // Block original 'K' or'k'


               case 0x47: // 'G' or'g'
                    if (isCtrlPressed) return 0; // Allow original key input if Ctrl key is pressed
               
                    if (!isUppercase()) {
                        // Handle Lowercase 'g'
                        SendUnicodeChar(0x997);  // 'গ'
                    } else {
                        // Handle Uppercase 'G'
                        SendUnicodeChar(0x998);  // 'ঘ'
                    }
                    return 1; // Block original 'G' or'g'
            //    case 0x47: // 'G' or'g'
            //         // SendUnicodeChar(0x999);  // 'ঙ'
            //         return 1; // Block original 'G' or'g'


               case 0x43: // 'C' or'c'
                    if (isCtrlPressed) return 0; // Allow original key input if Ctrl key is pressed

                    if (!isUppercase()) {
                        // Handle Lowercase 'c'
                        SendUnicodeChar(0x99A);  // 'চ'
                    } else {
                        // Handle Uppercase 'C'
                        SendUnicodeChar(0x99B);  // 'ছ'
                    }
                    return 1; // Block original 'C' or'c'


               case 0x4A: // 'J' or'j'
                    if (isCtrlPressed) return 0; // Allow original key input if Ctrl key is pressed
               
                    if (!isUppercase()) {
                        // Handle Lowercase 'j'
                        SendUnicodeChar(0x99C);  // 'জ
                    } else {
                        // Handle Uppercase 'J'
                        SendUnicodeChar(0x99D);  // 'ঝ'
                    }
                    return 1; // Block original 'K' or'k'


                case 0x52: // 'R' or'r'
                    if (isCtrlPressed) return 0; // Allow original key input if Ctrl key is pressed

                    SendUnicodeChar(0x9B0);  // 'র'
                    return 1; // Block original 'R' or r
                    
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
