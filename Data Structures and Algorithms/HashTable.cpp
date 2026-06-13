//============================================================================
// Name        : HashTable.cpp
// Author      : Remy Welham
// Version     : 1.0
// Copyright   : Copyright © 2023 SNHU COCE
// Description : Lab 4-2 Hash Table
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>

#include "CSVparser.hpp"

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

// forward declarations
double strToDouble(string str, char ch);

// define a structure to hold bid information
struct Bid {
    string bidId; // unique identifier
    string title;
    string fund;
    double amount;
    Bid() {
        amount = 0.0;
    }
};

//============================================================================
// Hash Table class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a hash table with chaining.
 */
class HashTable {

private:
    // Define structures to hold bids
    struct Node {
        Bid bid;
        unsigned int key;
        Node *next;

        // default constructor
        Node() {
            key = UINT_MAX;
            next = nullptr;
        }

        // initialize with a bid
        Node(Bid aBid) : Node() {
            bid = aBid;
        }

        // initialize with a bid and a key
        Node(Bid aBid, unsigned int aKey) : Node(aBid) {
            key = aKey;
        }
    };

    vector<Node> nodes;

    unsigned int tableSize = DEFAULT_SIZE;

    unsigned int hash(int key);

public:
    HashTable();
    HashTable(unsigned int size);
    virtual ~HashTable();
    void Insert(Bid bid);
    void PrintAll();
    void Remove(string bidId);
    Bid Search(string bidId);
    size_t Size();
};

/**
 * Default constructor
 */
HashTable::HashTable() {    
    // Initalize node structure by resizing tableSize
    nodes.resize(tableSize);
}

/**
 * Constructor for specifying size of the table
 * Use to improve efficiency of hashing algorithm
 * by reducing collisions without wasting memory.
 */
HashTable::HashTable(unsigned int size) {
    // invoke local tableSize to size with this->
    this->tableSize = size;
    // resize nodes size
    nodes.resize(size);
}


/**
 * Destructor
 */
HashTable::~HashTable() {
    // erase nodes beginning
    nodes.erase(nodes.begin());
}

/**
 * Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 *
 * @param key The key to hash
 * @return The calculated hash
 */
unsigned int HashTable::hash(int key) {
    // return key tableSize using the modulo hash
    unsigned int keyReturn = key % tableSize;
    return keyReturn;
} 

/**
 * Insert a bid
 *
 * @param bid The bid to insert
 */
void HashTable::Insert(Bid bid) {
    // create the key for the given bid
    unsigned int tempKey = hash(stoi(bid.bidId));
    // retrieve node using key
    // if entry found for the key at default
    if (nodes.at(tempKey).key == UINT_MAX) {
        // make a new node
        Node newNode = Node(bid, tempKey);
        // add the item
        nodes.at(tempKey) = newNode;
    }
    else {
        // curser node for iterating pointing at hash location
        Node* currNode = &nodes.at(tempKey);
        //new node pointer
        Node* newNode = new Node(bid, tempKey);
        //look for last position in linked list
        while (currNode->next != NULL) {
            currNode = currNode->next;
        }
        //append new node
        currNode->next = newNode;
    }
}

/**
 * Print all bids
 */
void HashTable::PrintAll() {
    // for node begin to end iterate
    for (int i = 0; i < this->tableSize; i++) {
        Node* currNode = &nodes.at(i);
        //   if key not equal to UINT_MAx
        if (currNode->key != UINT_MAX) {
                // output key, bidID, title, amount and fund
                cout << currNode->key << ": " << currNode->bid.bidId << " | " << currNode->bid.amount << " | "
                    << currNode->bid.fund << endl;
        }
                // node is equal to next iter
                // while node not equal to nullptr
        while (currNode->next != nullptr) {
            // node is equal to next node
            currNode = currNode->next;
            // output key, bidID, title, amount and fund
            cout << currNode->key << ": " << currNode->bid.bidId << " | " << currNode->bid.amount << " | "
                << currNode->bid.fund << endl;
        }
    }

}

/**
 * Remove a bid
 *
 * @param bidId The bid id to search for
 */
void HashTable::Remove(string bidId) {
    // set key equal to hash atoi bidID cstring
    // erase node begin and key

    // get head node as currNode
    Node* currNode = &nodes.at(hash(stoi(bidId)));
    Node* tempNode = NULL; // temp node for moving around removed node

    //check there is a chain of nodes
    if (currNode->next != nullptr) {
        // bid to be removed is the head node
        if (currNode->bid.bidId == bidId) {
            tempNode = currNode->next;
            currNode->key = tempNode->key;
            currNode->bid = tempNode->bid;
            currNode->next = tempNode->next;
            free(tempNode);
            return;
        }
        //search list until a match is found or the list end is found
        while (currNode != NULL && currNode->bid.bidId != bidId) {
            tempNode = currNode;
            currNode = currNode->next;
        }
        // end of list was reached with no match
        if (currNode == NULL) {
            cout << "Bid not found." << endl;
            return;
        }
        tempNode->next = currNode->next;
        delete currNode;
    }
    // there isn't more than one element in the hash
    else {
        if (currNode->bid.bidId == bidId) {
            Node newNode = Node();
            currNode->key = newNode.key;
            currNode->bid = newNode.bid;
            currNode->next = nullptr;
            return;
        }
        // no bid was found
        else{
            cout << "Bid not found." << endl;
        }
    }
}

/**
 * Search for the specified bidId
 *
 * @param bidId The bid id to search for
 */
Bid HashTable::Search(string bidId) {
    Bid bid;

    // create the key for the given bid
    Node* currNode = &nodes.at(hash(stoi(bidId)));
    // if entry found for the key
         //return node bid

    // if no entry found for the key
      // return bid
    // while node not equal to nullptr
    while (currNode != nullptr) {
        // if the current node matches, return it
        if (currNode->bid.bidId == bidId) {
            return currNode->bid;
        }
        //node is equal to next node
        currNode = currNode->next;
    }
    return bid;
}

//============================================================================
// Static methods used for testing
//============================================================================

/**
 * Display the bid information to the console (std::out)
 *
 * @param bid struct containing the bid info
 */
void displayBid(Bid bid) {
    cout << bid.bidId << ": " << bid.title << " | " << bid.amount << " | "
            << bid.fund << endl;
    return;
}

/**
 * Load a CSV file containing bids into a container
 *
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read
 */
void loadBids(string csvPath, HashTable* hashTable) {
    cout << "Loading CSV file " << csvPath << endl;

    // initialize the CSV Parser using the given path
    csv::Parser file = csv::Parser(csvPath);

    // read and display header row - optional
    vector<string> header = file.getHeader();
    for (auto const& c : header) {
        cout << c << " | ";
    }
    cout << "" << endl;

    try {
        // loop to read rows of a CSV file
        for (unsigned int i = 0; i < file.rowCount(); i++) {

            // Create a data structure and add to the collection of bids
            Bid bid;
            bid.bidId = file[i][1];
            bid.title = file[i][0];
            bid.fund = file[i][8];
            bid.amount = strToDouble(file[i][4], '$');

            //cout << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

            // push this bid to the end
            hashTable->Insert(bid);
        }
    } catch (csv::Error &e) {
        std::cerr << e.what() << std::endl;
    }
}

/**
 * Simple C function to convert a string to a double
 * after stripping out unwanted char
 *
 * credit: http://stackoverflow.com/a/24875936
 *
 * @param ch The character to strip out
 */
double strToDouble(string str, char ch) {
    str.erase(remove(str.begin(), str.end(), ch), str.end());
    return atof(str.c_str());
}

/**
 * The one and only main() method
 */
int main(int argc, char* argv[]) {

    // process command line arguments
    string csvPath, bidKey;
    switch (argc) {
    case 2:
        csvPath = argv[1];
        bidKey = "98223";
        break;
    case 3:
        csvPath = argv[1];
        bidKey = argv[2];
        break;
    default:
        csvPath = "eBid_Monthly_Sales.csv";
        bidKey = "98223";
    }

    // Define a timer variable
    clock_t ticks;

    // Define a hash table to hold all the bids
    HashTable* bidTable;

    Bid bid;
    bidTable = new HashTable();
    
    int choice = 0;
    while (choice != 9) {
        cout << "Menu:" << endl;
        cout << "  1. Load Bids" << endl;
        cout << "  2. Display All Bids" << endl;
        cout << "  3. Find Bid" << endl;
        cout << "  4. Remove Bid" << endl;
        cout << "  9. Exit" << endl;
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {

        case 1:
            
            // Initialize a timer variable before loading bids
            ticks = clock();

            // Complete the method call to load the bids
            loadBids(csvPath, bidTable);

            // Calculate elapsed time and display result
            ticks = clock() - ticks; // current clock ticks minus starting clock ticks
            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 2:
            bidTable->PrintAll();
            break;

        case 3:
            ticks = clock();

            bid = bidTable->Search(bidKey);

            ticks = clock() - ticks; // current clock ticks minus starting clock ticks

            if (!bid.bidId.empty()) {
                displayBid(bid);
            } else {
                cout << "Bid Id " << bidKey << " not found." << endl;
            }

            cout << "time: " << ticks << " clock ticks" << endl;
            cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl;
            break;

        case 4:
            bidTable->Remove(bidKey);
            break;
        }
    }

    cout << "Good bye." << endl;

    return 0;
}
