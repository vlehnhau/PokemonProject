#include "ConsoleDemo.h"
#include <cstdlib>


/// random number between 0..max_value-1
int rrnd(int min_value, int max_value)
{
    double v = std::rand();
    v /= (static_cast<double>(RAND_MAX) + 1.0);
    v *= (max_value - min_value);
    v += min_value;
    return static_cast<int>(v);
}

void ConsoleDemo::onRefresh()
{
    char c = 0;
    if (getPressedKey() == 0) {
        c = static_cast<char>(rrnd(int('a'), int('z')));
    } else if (getPressedKey() >= ' ') {
        c = getPressedKey();
    }

    if (c > 0) {
        if (c == '+'){
            for (int i = 0; i < 42; i++) {
                QString str = QString("\360\237\230\204"); // QString("\u265d");
                setCharacter(rrnd(0, 80), rrnd(0, 60), str);
            }
        }
        else{
        for (int i = 0; i < 42; i++) {
            setCharacter(rrnd(0, 80), rrnd(0, 60), c);
        }}
    }
    int dx = 0;
    int dy = 0;
    if (getPressedKey() == CURSOR_UP)
        dy = -1;
    if (getPressedKey() == CURSOR_DOWN)
        dy = 1;
    if (getPressedKey() == CURSOR_LEFT)
        dx = -1;
    if (getPressedKey() == CURSOR_RIGHT)
        dx = 1;

    if (dx != 0 || dy != 0) {
        int width = int(getWidth());
        int height = int(getHeight());
        std::vector<QString> buffer(size_t(width * height));

        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                int xsource = x + dx;
                int ysource = y + dy;
                if (xsource < 0)
                    xsource = width - 1;
                if (xsource >= width)
                    xsource = 0;
                if (ysource < 0)
                    ysource = height - 1;
                if (ysource >= height)
                    ysource = 0;

                buffer[size_t(x + y * width)] = getCharacter(xsource, ysource);
            }
        }
        for (int y = 0; y < height; y++) {
            for (int x = 0; x < width; x++) {
                setCharacter(x, y, buffer[size_t(x + y * width)]);
            }
        }
    }
    if (c == '-') {
        clear();
    }
    writeString(5,  4, "*****************************************************");
    writeString(5,  5, "* Console Demo                                      *");
    writeString(5,  6, "* ------------                                      *");
    writeString(5,  7, "* draws random characters to the screen             *");
    writeString(5,  8, "* Press any key to draw the corresponding character *");
    writeString(5,  9, "* Use cursor keys to scroll                         *");
    writeString(5, 10, "* '-' clears the screen                             *");
    writeString(5, 11, "* '+' draws a unicode character                     *");
    writeString(5, 12, "*****************************************************");
}

ConsoleDemo::ConsoleDemo()
    : ConsoleWindow()
{

}
