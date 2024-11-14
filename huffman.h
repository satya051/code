#ifndef HUFFMAN_H
#define HUFFMAN_H

#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
#include <bitset>

using namespace std;

struct Node {
    char data;
    unsigned freq;
    Node *left, *right;
    
    Node(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
    
    // Comparator for priority queue
    bool operator>(const Node &other) const {
        return freq > other.freq;
    }
};

class HuffmanCoding {
private:
    unordered_map<char, string> huffmanCodes;
    unordered_map<char, unsigned> freqTable;

public:
    // Build the frequency table from the input string
    void buildFrequencyTable(const string &input) {
        for (char ch : input) {
            freqTable[ch]++;
        }
    }

    // Build Huffman Tree and generate Huffman codes
    void buildHuffmanTree() {
        priority_queue<Node*, vector<Node*>, greater<Node*>> pq;

        // Create a node for each character and add it to the priority queue
        for (const auto &entry : freqTable) {
            pq.push(new Node(entry.first, entry.second));
        }

        // Build the Huffman Tree
        while (pq.size() > 1) {
            Node *left = pq.top(); pq.pop();
            Node *right = pq.top(); pq.pop();
            Node *newNode = new Node('\0', left->freq + right->freq);
            newNode->left = left;
            newNode->right = right;
            pq.push(newNode);
        }

        // Generate Huffman codes from the tree
        generateHuffmanCodes(pq.top(), "");
    }

    // Recursive function to generate Huffman codes
    void generateHuffmanCodes(Node *root, const string &str) {
        if (root == nullptr) return;

        // If leaf node, store the code
        if (root->data != '\0') {
            huffmanCodes[root->data] = str;
        }

        generateHuffmanCodes(root->left, str + "0");
        generateHuffmanCodes(root->right, str + "1");
    }

    // Get the generated Huffman code for a character
    string getHuffmanCode(char ch) const {
        return huffmanCodes.at(ch);
    }

    // Get the Huffman codes for all characters
    unordered_map<char, string> getAllHuffmanCodes() const {
        return huffmanCodes;
    }
};

#endif
