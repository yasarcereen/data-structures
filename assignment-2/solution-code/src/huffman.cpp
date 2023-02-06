//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Ceren Yaşar
//---Student Number: 150210013
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <fstream>
#include <string.h>
#include <bits/stdc++.h>

#include "huffman.h"
#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-----------------------------------------------------//
//-----------Reads the key from text file--------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::readKey(const char* argv){
    ifstream readKeyFile;
    readKeyFile.open(argv);

    if(readKeyFile.is_open()){
        while(!readKeyFile.eof()){
            readKeyFile >> key;
        }
    }
    readKeyFile.close();
    //cout << "\nSuccessfuly read the key" << endl;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------Sorts the key in an alpabetic order---------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::sortKey(){
    sortedKey = key;
    sort(sortedKey.begin(), sortedKey.end());
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//-------Finds the frequency of the characters---------//
//-----------------------------------------------------//
void Huffman::findFrequency(){
    //DO NOT CHANGE THIS
    sortKey();
    //DO NOT CHANGE THIS
    
    
    int count = 1;

    for (unsigned int i=1; i<sortedKey.size(); i++) {
        /*
         * Starting from index 1, this loop iterates over elements while comparing them to their successor and incrementing that character's count
         * if they are the same and putting them into the queue when that character is done.
         */
        Node* newNode = new Node;
        if (sortedKey[i] == sortedKey[i-1]) {
            count++;
        } else {
            newNode->token.symbol = sortedKey[i-1];
            newNode->token.val = count;
            queue.enque(newNode);
            count = 1;
        }
    }
    Node* newNode = new Node;
    newNode->token.symbol = sortedKey[sortedKey.size()-1];
    newNode->token.val = count;
    queue.enque(newNode);
};
//-----------------------------------------------------//


//-----------------------------------------------------//
//----------------Creates Huffman Tree-----------------//
//-----------------------------------------------------//
void Huffman::createHuffmanTree(){
    findFrequency();

    while (queue.getSize() > 1) {
        /*
         * While the queue has more than one element, first two should be merged and put back into its new position.
         * When there is only one element left in the queue, the loop will break because that one element will be the
         * root of the huffman tree.
         */
        Node* node1 = queue.dequeue();
        Node* node2 = queue.dequeue();
        queue.enque(huffmanTree.mergeNodes(node1, node2));
    }
    huffmanTree.root = queue.dequeue();
};
// After this function is called, there will be one Node pointer in the priority queue pointing to the root of the tree
//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Prints the Huffman Tree---------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printHuffmanTree(){
    huffmanTree.printTree(huffmanTree.root, 0);
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Finds and returns the binary------------//
//----------------value to given character-------------//
//-----------------------------------------------------//
string Huffman::getTokenBinary(char tokenChar, Node* traverse, string tokenBinary){
    /*
     * We are looking for the binary value of tokenChar character.
     * In the Huffman tree we created, we have stored decimal values of each character.
     * Starting from the Node* traverse, we will traverse the subtree looking for tokenChar
     * By updating these parameters at each function call, we can implement a recursive function
     * and append 0 or 1 digits to string tokenBinary
    */
    if (traverse->left && traverse->left->token.symbol.find(tokenChar) != string::npos) {
        /*
         * To avoid segmentation fault, first we check whether the left node exists or not. Secondly, we should check
         * whether the left subtree contains the character we are looking for. If both these conditions hold, it should be 
         * okay to make the recursive function call. Same things go for the right subtree check below as well.
         */
        tokenBinary = "0" + getTokenBinary(tokenChar, traverse->left, tokenBinary);
        return tokenBinary;
    } else if (traverse->right && traverse->right->token.symbol.find(tokenChar) != string::npos) {
        tokenBinary = "1" + getTokenBinary(tokenChar, traverse->right, tokenBinary);
        return tokenBinary;
    }

    return ""; // If tokenChar is not found
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//--------------Encodes the given password-------------//
//-----------------------------------------------------//
void Huffman::encodePassword(string password){
    for (char c: password) {
        // For every character in password, binary password and value password must be updated
        // Character value is equal to its binary value's length
        string tokenBinary = getTokenBinary(c, huffmanTree.root, "");
        encodedBinaryPassword += tokenBinary;
        encodedValPassword += to_string(tokenBinary.length());
    }
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the encoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printEncodedPassword(){
    cout << "Encoded Password Binary: " << encodedBinaryPassword << endl;
    cout << "Encoded Password Value: " << encodedValPassword << endl;
};

//-----------------------------------------------------//
//--------------Decodes the given password-------------//
//-----------------------------------------------------//
void Huffman::decodePassword(string encodedBinaryPassword, string encodedValPassword){
    int start = 0;
    for (char c: encodedValPassword) {
        int depth = c - '0'; // char to int conversion
        decodeToken(encodedBinaryPassword.substr(start, depth));
        start += depth;
    }
};

//-----------------------------------------------------//

//-----------------------------------------------------//
//---------------Decodes the given binary--------------//
//-----------------------------------------------------//
void Huffman::decodeToken(string encodedToken){
    Node* cursor = huffmanTree.root;
    for (char c: encodedToken) {
        if (c == '0') {
            cursor = cursor->left;
        } else {
            cursor = cursor->right;
        }
    }

    decodedPassword += cursor->token.symbol;
};
//-----------------------------------------------------//

//-----------------------------------------------------//
//-------------Prints the decoded password-------------//
//------------DO NOT CHANGE THIS FUNCTION--------------//
//-----------------------------------------------------//
void Huffman::printDecodedPassword(){
    cout << "Decoded Password: " << decodedPassword << endl;
};