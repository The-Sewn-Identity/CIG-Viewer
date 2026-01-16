#ifndef DISPLAY_HPP
#define DISPLAY_HPP

static std::string truecolorToANSI(uint8_t r, uint8_t g, uint8_t b) {
    std::string ansi = "\x1b[38;2;";

    ansi += std::to_string(r); ansi += ';';
    ansi += std::to_string(g); ansi += ';';
    ansi += std::to_string(b); ansi += 'm';

    return ansi;
}

class Pixel {
    public:
        Pixel(uint8_t r, uint8_t g, uint8_t b) {
            this->color_code = truecolorToANSI(r, g, b);
        }
        
        void echoPixel(void);

    protected:
        const std::string utf_char = "█";
        const std::string color_esc = "\x1b[0m";
        std::string color_code;
};

void Pixel::echoPixel(void) {
    std::cout << this->color_code + this->utf_char + this->color_esc;
}

#endif