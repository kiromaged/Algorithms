#include <iostream>
#include <queue>
#include <unordered_map>
#include <vector>
using namespace std;

// A Tree node for Huffman
struct Node {
    char ch;
    int freq;
    Node* left;
    Node* right;

    Node(char c, int f) : ch(c), freq(f), left(nullptr), right(nullptr) {}
};

// Compare function for the priority queue (min-heap)
struct Compare {
    bool operator()(Node* a, Node* b) {
        return a->freq > b->freq;
    }
};

// Function to encode the characters using the Huffman tree
void encode(Node* root, string code, unordered_map<char, string>& huffmanCode) {
    if (!root) return;

    // Leaf node: assign the code
    if (!root->left && !root->right) {
        huffmanCode[root->ch] = code;
    }

    // Traverse left
    encode(root->left, code + "0", huffmanCode);

    // Traverse right
    encode(root->right, code + "1", huffmanCode);
}

// Function to decode a Huffman-encoded string
string decode(Node* root, string encodedStr) {
    string decodedStr = "";
    Node* current = root;

    for (char bit : encodedStr) {
        // Go left for '0' and right for '1'
        if (bit == '0') current = current->left;
        else current = current->right;

        // If we reach a leaf node
        if (!current->left && !current->right) {
            decodedStr += current->ch;
            current = root;  // Restart from the root for the next character
        }
    }

    return decodedStr;
}

int main() {
    // Input string
    string text;
    cout << "Enter the text to encode: ";
    getline(cin, text);

    // Count frequency of each character
    unordered_map<char, int> freq;
    for (char ch : text) freq[ch]++;

    // Priority queue (min-heap)
    priority_queue<Node*, vector<Node*>, Compare> pq;

    // Create a node for each character and push into the queue
    for (auto pair : freq) {
        pq.push(new Node(pair.first, pair.second));
    }

    // Build the Huffman Tree
    while (pq.size() > 1) {
        Node* left = pq.top(); pq.pop();
        Node* right = pq.top(); pq.pop();

        // Merge the two nodes
        Node* merged = new Node('\0', left->freq + right->freq);
        merged->left = left;
        merged->right = right;
        pq.push(merged);
    }

    // Root of the Huffman Tree
    Node* root = pq.top();

    // Generate Huffman Codes
    unordered_map<char, string> huffmanCode;
    encode(root, "", huffmanCode);

    // Print the Huffman Codes
    cout << "Huffman Codes:\n";
    for (auto pair : huffmanCode) {
        cout << pair.first << " : " << pair.second << "\n";
    }

    // Encode the input text
    string encodedStr = "";
    for (char ch : text) {
        encodedStr += huffmanCode[ch];
    }
    cout << "\nEncoded String: " << encodedStr << "\n";

    // Decode the encoded string
    string decodedStr = decode(root, encodedStr);
    cout << "Decoded String: " << decodedStr << "\n";

    return 0;
}
