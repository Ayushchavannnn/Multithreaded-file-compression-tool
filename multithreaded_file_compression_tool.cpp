#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

// Function to compress a file using Run-Length Encoding (RLE)
bool compress_file(const std::string& input_filename, const std::string& output_filename) {
    std::ifstream input(input_filename, std::ios::binary);
    if (!input) {
        std::cerr << "Error opening input file!" << std::endl;
        return false;
    }

    std::ofstream output(output_filename, std::ios::binary);
    if (!output) {
        std::cerr << "Error opening output file!" << std::endl;
        return false;
    }

    char current_char, previous_char;
    int count = 1;

    input.get(previous_char); // Read the first character

    while (input.get(current_char)) {
        if (current_char == previous_char) {
            count++; // If the character is the same, increment the count
        } else {
            // Write the previous character and its count to the output file
            output.put(previous_char);
            output.write(reinterpret_cast<char*>(&count), sizeof(count));
            count = 1; // Reset count for the new character
        }
        previous_char = current_char;
    }

    // Write the last character and its count
    output.put(previous_char);
    output.write(reinterpret_cast<char*>(&count), sizeof(count));

    return true;
}

// Function to decompress a file using Run-Length Encoding (RLE)
bool decompress_file(const std::string& input_filename, const std::string& output_filename) {
    std::ifstream input(input_filename, std::ios::binary);
    if (!input) {
        std::cerr << "Error opening input file!" << std::endl;
        return false;
    }

    std::ofstream output(output_filename, std::ios::binary);
    if (!output) {
        std::cerr << "Error opening output file!" << std::endl;
        return false;
    }

    char current_char;
    int count;

    while (input.get(current_char)) {
        input.read(reinterpret_cast<char*>(&count), sizeof(count));
        // Write the character `count` times to the output file
        for (int i = 0; i < count; i++) {
            output.put(current_char);
        }
    }

    return true;
}

int main() {
    std::string input_filename = "input.txt";   // The file to be compressed
    std::string compressed_filename = "output.rle";  // Compressed file
    std::string decompressed_filename = "decompressed.txt"; // Decompressed file

    std::cout << "Compressing file: " << input_filename << std::endl;
    if (compress_file(input_filename, compressed_filename)) {
        std::cout << "File compressed successfully!" << std::endl;
    } else {
        std::cerr << "Compression failed!" << std::endl;
    }

    std::cout << "Decompressing file: " << compressed_filename << std::endl;
    if (decompress_file(compressed_filename, decompressed_filename)) {
        std::cout << "File decompressed successfully!" << std::endl;
    } else {
        std::cerr << "Decompression failed!" << std::endl;
    }

    return 0;
}






