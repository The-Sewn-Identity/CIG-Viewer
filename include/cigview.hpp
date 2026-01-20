#ifndef CIGVIEW_HPP
#define CIGVIEW_HPP

#include <fstream>
#include <vector>

// Pixel display

static std::string truecolorToANSI(uint8_t r, uint8_t g, uint8_t b) {
    std::string ansi = "\x1b[38;2;";

    ansi += std::to_string(r); ansi += ';';
    ansi += std::to_string(g); ansi += ';';
    ansi += std::to_string(b); ansi += 'm';

    return ansi;
}

class Pixel final {
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

    private:
        std::ifstream file;
        std::vector<std::array<uint8_t, 4>> data;
        uint32_t size;
        uint16_t width;
        uint16_t height;
};

void Bitmap::readData(void) {
    if (this->file) {
        std::byte format[2];
        std::byte offset{};

        this->file.read(reinterpret_cast<char*>(format), sizeof(format));
        this->file.read(reinterpret_cast<char*>(&offset), sizeof(offset));

        std::cout << (int)offset << std::endl;
        this->file.seekg((uint8_t)offset, std::ios::beg);

        do {
            std::array<uint8_t, 4> pixel; 

            this->file.read(reinterpret_cast<char*>(pixel.data()), pixel.size());
            this->data.push_back(pixel);

        } while (!file.eof());

        for (std::array<uint8_t, 4> u : data) {
            std::printf("%x%x%x\n", u[0], u[1], u[2]);
        }
        std::cout << data.size();
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