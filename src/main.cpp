#include <iostream>
#include <cigview.hpp>

#ifdef _WIN32
    #include <windows.h>

    void setup(void) {
        SetConsoleMode(GetStdHandle(STD_OUTPUT_HANDLE), ENABLE_PROCESSED_OUTPUT | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
        SetConsoleCP(CP_UTF8);
        SetConsoleOutputCP(CP_UTF8);
    }
#else
    void setup(void) {}
#endif


using namespace std;

int main(int argc, char *argv[]) {
    setup();

    BMP bmp("./shitass.bmp");
    bmp.readData();
    bmp.displayBitmap();

    return 0;
}