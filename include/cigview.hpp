#ifndef CIGVIEW_HPP
#define CIGVIEW_HPP

#include <fstream>
#include <deque>

// Pixel display

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


// BMP file reading (must be 24-bit!)

class Bitmap {
    public:
        Bitmap(std::string path) {
            this->file.open(path, std::ios::binary);
        }
        ~Bitmap() {
            this->file.close();
        }

        void readData(void);
        void displayBitmap(void);

    private:
        std::ifstream file;
        std::deque<std::array<uint8_t, 4>> data;
        uint32_t size;
        uint16_t width;
        uint16_t height;
};

void Bitmap::readData(void) {
    if (this->file) {
        uint8_t format[2];
        uint8_t offset;

        this->file.read(reinterpret_cast<char*>(format), sizeof(format));
        this->file.read(reinterpret_cast<char*>(&offset), sizeof(offset));

        this->file.seekg(18, std::ios::beg);
        this->file.read(reinterpret_cast<char*>(&this->width), sizeof(width));
        this->file.read(reinterpret_cast<char*>(&this->height), sizeof(height));

        this->file.seekg(offset + 1, std::ios::beg);

        while (!file.eof()) {
            std::array<uint8_t, 4> pixel; 

            this->file.read(reinterpret_cast<char*>(pixel.data()), pixel.size());
            this->data.push_front(pixel);
        }

        std::cout << data.size();
    }
}

void Bitmap::displayBitmap(void) {

    for (std::array<uint8_t, 4> p : data) {
        echoPixel(truecolorToANSI(p.at(2), p.at(1), p.at(0)));
        std::cout << std::to_string(p.at(0));
        std::cout << std::to_string(p.at(1));
        std::cout << std::to_string(p.at(2));
        std::cout << std::to_string(p.at(3)) << std::endl;
        //std::cout << truecolorToANSI(p.at(0), p.at(1), p.at(2)) << std::endl;
    }
}


class CIGImage {
    public:
        CIGImage(std::string path) {
            this->file.open(path);
        }
        ~CIGImage() {
            this->file.close();
        }

        void readData(void);

    private:
        std::ifstream file;
        int width;
        int height;
};

void CIGImage::readData(void) {
    if (this->file) {
        
    }
}

#endif