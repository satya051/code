#include <iostream>
#include <fstream>
#include <bitset>
#include <sstream>
#include <unordered_map>
#include "huffman.h"

using namespace std;

// Function to compress input string and return the compressed bit string
string compress(const string &input, HuffmanCoding &huffman) {
    stringstream compressed;
    for (char ch : input) {
        compressed << huffman.getHuffmanCode(ch);
    }
    return compressed.str();
}

// Function to decompress the compressed bit string using the Huffman Tree
string decompress(const string &compressed, const HuffmanCoding &huffman) {
    unordered_map<string, char> reverseHuffmanCodes;
    for (const auto &pair : huffman.getAllHuffmanCodes()) {
        reverseHuffmanCodes[pair.second] = pair.first;
    }

    stringstream decompressed;
    string temp = "";
    for (char bit : compressed) {
        temp += bit;
        if (reverseHuffmanCodes.find(temp) != reverseHuffmanCodes.end()) {
            decompressed << reverseHuffmanCodes[temp];
            temp = "";
        }
    }
    return decompressed.str();
}

// Function to read file contents into a string
string readFile(const string &filename) {
    ifstream file(filename, ios::in | ios::binary);
    stringstream buffer;
    buffer << file.rdbuf();
    return buffer.str();
}

// Function to write compressed data to a file
void writeCompressedFile(const string &filename, const string &compressed) {
    ofstream outFile(filename, ios::binary);
    outFile << compressed;
}

// Function to write decompressed data to a file
void writeDecompressedFile(const string &filename, const string &decompressed) {
    ofstream outFile(filename, ios::out | ios::binary);
    outFile << decompressed;
}

int main() {
    string inputFile = "input.txt";  // Input file to be compressed
    string outputFile = "output_compressed.txt";  // Output file for compressed data
    string decompressedFile = "output_decompressed.txt";  // Output file for decompressed data

    // Step 1: Read input file
    string input = readFile(inputFile);
    if (input.empty()) {
        cout << "Failed to read the file or file is empty!" << endl;
        return -1;
    }

    // Step 2: Build Huffman Tree and generate codes
    HuffmanCoding huffman;
    huffman.buildFrequencyTable(input);
    huffman.buildHuffmanTree();

    // Step 3: Compress the input data
    string compressed = compress(input, huffman);
    writeCompressedFile(outputFile, compressed);
    cout << "File compressed successfully!" << endl;

    // Step 4: Decompress the compressed data
    string decompressed = decompress(compressed, huffman);
    writeDecompressedFile(decompressedFile, decompressed);
    cout << "File decompressed successfully!" << endl;

    return 0;
}
