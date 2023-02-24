#include "my_code.h"
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

using namespace my_namespace;
using namespace std;

// The read function
void read_image(const std::string& filename, Image& image) {
    int w, h, d;
    uint8_t* data = stbi_load(filename.c_str(), &w, &h, &d, 0);
    if (data == nullptr) {
        std::cerr << "Failed to load image: " << filename << std::endl;
        return;
    }
    std::shared_ptr<uint8_t> data_ptr(data, stbi_image_free);

    // Fill the Image struct
    image.width = static_cast<uint16_t>(w);
    image.height = static_cast<uint16_t>(h);
    image.depth = static_cast<uint8_t>(d);
    image.data = data_ptr;
    std::cout << "image read successfully" << std::endl;
}

int main(int argc, char *argv[])
{

    my_code trial;
    const std::string &configDir = argv[1];
    Image image;
    string filepath = argv[2];
    read_image(filepath, image);

    trial.initialize(configDir);
    trial.doingInference(image, configDir);

    return 0;
}
