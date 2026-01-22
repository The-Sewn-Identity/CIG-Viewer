#ifndef CIGVIEW_HPP
#define CIGVIEW_HPP

#include <fstream>
#include <deque>

#define BMP_OFFSET 0x0A
#define BMP_DIMENSIONS 0x12

extern const std::string utf_char = "█";
extern const std::string color_esc = "\x1b[0m";

inline std::string truecolorToANSI(uint8_t r, uint8_t g, uint8_t b) {
    std::string ansi = "\x1b[38;2;";

    ansi += std::to_string(r); ansi += ';';
    ansi += std::to_string(g); ansi += ';';
    ansi += std::to_string(b); ansi += 'm';

    return ansi;
}

void echoPixel(std::string color_code) {
    std::cout << color_code + utf_char + color_esc;
}

typedef class BMP {
    public:
        BMP(std::string path) {
            this->file.open(path, std::ios::binary);
        }
        ~BMP() {
            this->file.close();
        }

        void readData(void);
        void displayBitmap(void);

    private:
        std::ifstream file;
        std::deque<std::array<uint8_t, 4>> data;
        uint32_t size;
        uint32_t width;
        uint32_t height;
        
} BMP;

void BMP::readData(void) {
    if (this->file) {
        uint16_t format;
        uint32_t offset;

        this->file.read(reinterpret_cast<char*>(&format), sizeof(format));
        this->file.read(reinterpret_cast<char*>(&this->size), sizeof(this->size));

        this->file.seekg(BMP_OFFSET, std::ios::beg);
        this->file.read(reinterpret_cast<char*>(&offset), sizeof(offset));

        this->file.seekg(BMP_DIMENSIONS, std::ios::beg);
        this->file.read(reinterpret_cast<char*>(&this->width), sizeof(this->width));
        this->file.read(reinterpret_cast<char*>(&this->height), sizeof(this->height));

        this->file.seekg(offset + 1, std::ios::beg);

        while (!file.eof()) {
            std::array<uint8_t, 4> pixel; 

            this->file.read(reinterpret_cast<char*>(pixel.data()), pixel.size());

            this->data.push_back(pixel);
        }
    }
}

void BMP::displayBitmap(void) {
    for (unsigned int y = this->height - 1; y > 0; y--)
    {
        for (unsigned int x = 0; x < this->width; x++)
        {
            std::array<uint8_t, 4> p = this->data.at(y * this->width + x);
            float a = static_cast<float>(p.at(2)) / 0xFF;

            uint8_t r = p.at(1) * a;
            uint8_t g = p.at(0) * a;
            uint8_t b = p.at(3) * a;

            echoPixel(truecolorToANSI(r, g, b));
        }
        
        std::cout << std::endl;
    }
}

#endif