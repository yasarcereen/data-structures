//--- 2022-2023 Fall Semester Data Structure Assignment 2 ---//
//--------------------------//
//---Name & Surname: Ceren Yaşar
//---Student Number: 150210013
//--------------------------//

//-------------Do Not Add New Libraries-------------//
//-------------All Libraries Needed Were Given-------------//
#include <iostream>
#include <stdio.h>
#include <string.h>
#include <fstream>

#include "structs.h"

using namespace std;

//-------------Complete The Functions Below-------------//

//-------------Initialize Priority Queue-------------//
PriorityQueue::PriorityQueue(){
    head = nullptr;
};

//-------------Insert New Node To Priority Queue-------------//
void PriorityQueue::enque(Node* newnode){
    if (!head) {
        // If the head is null, the priority queue is empty. Hence, the new node will be the first and only node in the queue.
        head = newnode;
        return;
    }

    if (newnode->token.val < head->token.val) {
        newnode->next = head;
        head = newnode;
        return;
    }

    Node* cursor = head;

    while (true) {
        if (cursor->next) {
        /*
         * In the scenario where the cursor has a next node, we check if the next node's token value is greater than the new node.
         * If it is, we have found our insert position.
         * If not, we should move the cursor.
         */
            if (cursor->next->token.val > newnode->token.val) {
                newnode->next = cursor->next;
                cursor->next = newnode;
                break;
            } else {
                cursor = cursor->next;
            }
        } else {
        /* 
         * When moving the cursor, we might encounter a case where there is no next node.
         * This means that we were not able to find a node with a greater token value.
         * In other words, our new node has the greatest token value so far.
         * So we can just set the next node -tail of the queue- to newnode.
         */
            cursor->next = newnode;
            break;
        }
    }

};

//-------------Remove Node From Priority Queue-------------//
Node* PriorityQueue::dequeue(){
    Node* temp = head;
    head = head->next;

    temp->next = nullptr;

    return temp;
};

int PriorityQueue::getSize() {
    Node* cursor = head;
    int counter = 0;
    while (cursor) {
        counter++;
        cursor = cursor->next;
    }
    return counter;
}

//-------------Initialize Tree-------------//
Tree::Tree(){
    root = nullptr;
};

//-------------Delete Tree Nodes From Memory-------------//
Tree::~Tree(){
    deleteTree(root);
};

//-------------Delete Tree From Memory-------------//
void Tree::deleteTree(Node* node){
    //-------------This Function Is Not Necessary-------------//
    //-----------------Use It At Your Own Will----------------//
    if (!node) return;

    deleteTree(node->left);

    deleteTree(node->right);
    
    delete node;
    node = nullptr;
    return;
}

//-------------Merges Two Node Into One-------------//
Node* Tree::mergeNodes(Node* temp1, Node* temp2){
    Node* node = new Node;

    node->token.symbol = temp1->token.symbol + temp2->token.symbol;
    node->token.val = temp1->token.val + temp2->token.val;

    node->left = temp1;
    node->right = temp2;

    return node;
};

void Tree::printTree(Node* traverse, int level){
    cout << level << "\t";
    for (int i = 0; i < level; i++)
        cout << "\t"; 

    cout << traverse->token.symbol << "(" << traverse->token.val << ")" << endl;

    if(traverse->left)
        printTree(traverse->left, level + 1);  
    if(traverse->right)
        printTree(traverse->right, level + 1);
};