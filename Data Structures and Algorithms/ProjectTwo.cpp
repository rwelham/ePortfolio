//============================================================================
// Name        : ProjectTwo.cpp
// Author      : Remy Welham
// Version     : 1.0
// Description : Project Two Binary Search Tree
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================

// Future methods declared
bool checkFileFormat(string csvPath, vector<string>& csvLines);
string toUpperCase(string& str);

// Structure for holding each course's information
struct Course {
    string courseNumber;
    string courseName;
    vector<string> prereqs;

    // Default constructor
    Course() {
        courseNumber = "";
        courseName = "";
        prereqs.resize(0);
    }
};

// Internal structure for tree node
struct Node {
    Course course;
    Node* left;
    Node* right;

    // default constructor
    Node() {
        left = nullptr;
        right = nullptr;
    }

    // initialize with a bid
    Node(Course aCourse) :
        Node() {
        course = aCourse;
    }
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/**
 * Define a class containing data members and methods to
 * implement a binary search tree
 */
class BinarySearchTree {

private:
    Node* root;

    void removeNode(Node* ncurrNode);
    void addNode(Node* node, Course course);
    void printInOrder(Node* node);
    void printCourse(string courseNumber);



public:
    BinarySearchTree();
    virtual ~BinarySearchTree();
    void Clear();
    void Insert(Course course);
    Course Search(string courseNumber);
    void PrintCourse(string courseNumber);
    void PrintAll();
};

//============================================================================
// BinarySearchTree public method definitions.
//============================================================================

/**
 * Default constructor
 */
BinarySearchTree::BinarySearchTree() {
    // Initialize housekeeping variables
    //root is equal to nullptr
    root = nullptr;
}

/**
 * Destructor
 */
BinarySearchTree::~BinarySearchTree() {
    // recurse from root deleting every node
    delete root;
}

/**
 * Traverse the tree in order and print
 */
void BinarySearchTree::PrintAll() {
    // call inOrder fuction and pass root 
    this->printInOrder(root);
}

void BinarySearchTree::Clear(){
    //recursively calls remove node starting at root
    removeNode(root);
    //sets root to null
    root = nullptr;
}

/**
 * Insert a course
 */
void BinarySearchTree::Insert(Course course) {
    // if root equarl to null ptr
    if (root == nullptr) {
        // root is equal to new node course
        root = new Node(course);
    }
    // else
    else {
        // add Node root and course
        addNode(root, course);
    }
}

/**
 * Search for a course
 */
Course BinarySearchTree::Search(string courseNumber) {
    // set current node equal to root
    Node* temp = new Node();
    temp = this->root;
    // keep looping downwards until bottom reached or matching courseNumber found
    while (temp != NULL) {
        // if match found, return current course
        if (temp->course.courseNumber.compare(courseNumber) == 0) {
            return temp->course;
        }
        // if course is smaller than current node then traverse left
        if (courseNumber.compare(temp->course.courseNumber) < 0) {
            temp = temp->left;
        }
        // else larger so traverse right
        else {
            temp = temp->right;
        }
    }
    // course wasn't found so return empty course
    Course aCourse;
    return aCourse;
}

void BinarySearchTree::PrintCourse(string courseNumber){
    printCourse(courseNumber);
}


//============================================================================
// BinarySearchTree private method definitions.
//============================================================================

/**
 * Remove nodes from the tree
 */
void BinarySearchTree::removeNode(Node* currNode) {
    // If the current node is not null
    if (currNode != nullptr) {
        // If the current node has no children
        if ((currNode->left == nullptr) && (currNode->right == nullptr)) {
            // Delete the current node from the tree
            delete currNode;
            currNode = nullptr;
        }
        // If the current node has children
        else {
            // Recursively delete the left node
            removeNode(currNode->left);

            // Recursively delete the right node
            removeNode(currNode->right);
        }
    }
}


/**
 * Add a course to some node (recursive)

 * @param node Current node in tree
 * @param course Course to be added
 */
void BinarySearchTree::addNode(Node* node, Course course) {
    // if node is larger then add to left
    if (node->course.courseNumber.compare(course.courseNumber) > 0) {
        // if no left node
        if (node->left == nullptr) {
            // this node becomes left
            node->left = new Node(course);
        }
        // else recurse down the left node
        else {
            this->addNode(node->left, course);
        }
    }
    // else
    else {
        // if no right node
        if (node->right == nullptr) {
            // this node becomes right
            node->right = new Node(course);
        }
        //else
        else {
            // recurse down the right node
            this->addNode(node->right, course);
        }
    }
}

void BinarySearchTree::printInOrder(Node* node) {
    //if node is not equal to null ptr
    if (node != nullptr) {
        //InOrder node left
        printInOrder(node->left);
        //output courseNumber, title, prereqs
        cout << node->course.courseNumber << ": " << node->course.courseName;
        if (node->course.prereqs.size() > 0) {
            cout << " | ";
            for (int i = 0; i < node->course.prereqs.size(); i++) {
                cout << node->course.prereqs.at(i) << " ";
            }
            cout << endl;
        }
        else {
            cout << endl;
        }
        //InOder right
        printInOrder(node->right);
    }
}

void BinarySearchTree::printCourse(string courseNumber){
    // Set the current node to the root.
    Node* currentNode = root;

    // Boolean to determine if the course was found.
    bool courseFound = false;

    // Keep looping downwards until the bottom of the tree is reached or a matching course number is found.
    while (currentNode != nullptr) {
        // If the current node's course contains the specified courseNumber...
        if (currentNode->course.courseNumber == courseNumber) {
            // Update the courseFound boolean since it was found.
            courseFound = true;

            // Print the node's course number and course name.
            cout << currentNode->course.courseNumber << ", "
                 << currentNode->course.courseName << endl;

            // Get the amount of prerequisites the current course has.
            int prerequisitesSize = currentNode->course.prereqs.size();

            // Prerequisite identifier string.
            cout << "Prerequisites: ";

            // If the course has any prerequisites...
            if (prerequisitesSize > 0) {
                // Print each prerequisite course number.
                for (int i = 0; i < prerequisitesSize; i++) {
                   // If the current prerequisite is not the last one in the prerequisites vector...
                   if (i < prerequisitesSize - 1) {
                       // Print the course number followed by a comma.
                        cout << currentNode->course.prereqs.at(i) << ", ";
                   }
                   // If it is the last or only element in the prerequisites vector...
                   else {
                       // Print the course number followed by a new line.
                       cout << currentNode->course.prereqs.at(i) << endl;
                   }
                }
            }
            else {
                // Print a message to show that the course has no prerequities.
                 cout << "None" << endl;
            }

            // Stop searching after the course is found.
            break;
        }
        // If the specified course number is smaller than the course number at the current node...
        else if (courseNumber < currentNode->course.courseNumber) {
            // Traverse the left sub-tree.
            currentNode = currentNode->left;
        }
        // If the specified course number is larger than the course number at the current node...
        else {
            // Traverse the right sub-tree.
            currentNode = currentNode->right;
        }
    }

    // If the specified course was not found...
    if (!courseFound) {
        // Print a message to show that the course was not found.
        cout << "Course not found." << endl;
    }
}


//============================================================================
// Static Methods
//============================================================================

/**
*  Checks the csv file for the correct format
*  and makes a vector of lines from the csv file
*
*  @param csvPath - This is the string path for the specified csv file
*  @param csvLines - This is the vector to store all course lines from the csv file
*
*  @return true or false given file formatting
*/
bool checkFileFormat(string csvPath, vector<string>& csvLines) {
    string currentLine;
    string courseElement;
    vector<string> courseNumbers;
    int elementCount;
    ifstream csvFile;

    // Try to open csv file
    csvFile.open(csvPath);

    // If the file can't be opened
    if (!csvFile.is_open()) {
        // Display an error message
        cout << endl << "Could not open file!" << endl;

        // exit method
        return false;
    }

    // Clear the csv lines vector before adding to it
    csvLines.clear();

    // csvLines and courseNumbers vectors
    while (getline(csvFile, currentLine)) {
        // Skip lines with only whitespace
        if (!all_of(currentLine.begin(), currentLine.end(), isspace)) {
            // Store the current line of the csv file for loading courses into the tree
            csvLines.push_back(currentLine);

            // Open the current line string as a stream
            istringstream currentLineStream(currentLine);

            // Get the first element from the current line
            while (getline(currentLineStream, courseElement, ',')) {
                // Store all encountered course numbers
                courseNumbers.push_back(toUpperCase(courseElement));

                // Only get the first courseElement to store in courseNumbers
                break;
            }
        }
    }

    // Close the file after getting all course numbers
    csvFile.close();

    // Reopen the specified csv file
    csvFile.open(csvPath);

    // Get each line in the csv file
    while (getline(csvFile, currentLine)) {
        // Skip lines with only whitespace
        if (!all_of(currentLine.begin(), currentLine.end(), isspace)) {
            // Open the current line string as a stream
            istringstream currentLineStream(currentLine);

            // The number of course elements from each line in the csv file
            elementCount = 0;

            // Define a variable to hold the course number for the current line
            string currentCourseNumber = "";

            // Define a variable to hold the course name for the current line
            string currentCourseName = "";

            // Define a variable to hold a prerequisite for the current line
            string currentPrerequisite = "";

            // Get each element in the current line
            while (getline(currentLineStream, courseElement, ',')) {
                // Increment the element count once a courseElement is retrieved
                elementCount++;

                // Store the current course number for the missing course name error
                if (elementCount == 1) {
                    currentCourseNumber = toUpperCase(courseElement);
                }

                // Store the current course number for the missing course name error
                if (elementCount == 2) {
                    currentCourseName = courseElement;
                }

                // Check if the current prerequisite exist in the file. Skip checking empty and whitespace course numbers
                if (elementCount > 2 && !all_of(courseElement.begin(), courseElement.end(), isspace)) {
                    // Store the current course element as the current prerequisite
                    currentPrerequisite = toUpperCase(courseElement);

                    // If the prerequisite was not previously added to the vector of course numbers
                    if (find(courseNumbers.begin(), courseNumbers.end(), currentPrerequisite) == courseNumbers.end()) {
                        // Print an error message for the missing prerequisite
                        cout << endl << "Prerequisite " << currentPrerequisite << " not found in the file." << endl;

                        return false;
                    }
                }
            }

            // After parsing the currentLineStream, if there is not a course name or it's only whitespace
            if (elementCount == 1 || all_of(currentCourseName.begin(), currentCourseName.end(), isspace)) {
                // Print an error message for the missing course name
                cout << endl << "No course name found for " << currentCourseNumber << "." << endl;

                return false;
            }

            // After parsing the currentLineStream, if there is not a course number (if it's only whitespace)
            if (elementCount >= 2 && all_of(currentCourseNumber.begin(), currentCourseNumber.end(), isspace)) {
                // Print an error message for the missing course number
                cout << endl << "No course number found for " << currentCourseName << "." << endl;

                return false;
            }
        }
    }

    // If no formatting errors are found
    return true;
}

/**
*  This method loads the BST with courses from a vector of raw string lines from the specified csv file
*
*  @param bst - This is the BinarySearchTree that will store all of the courses
*  @param csvPath - This is the string path for the specified csv file
*  @return - Whether the courses were successfully loaded
*/
bool loadCourses(BinarySearchTree* bst, string csvPath) {
    // This is the vector that stores all raw string lines from the csv file
    vector<string> csvLines;

    // Check the format of the csv file before continuing
    if (!checkFileFormat(csvPath, csvLines)) {
        cout << endl << "Incorrect file format." << endl;

        return false;
    }

    string courseElement;
    int elementIndex;
    int numberOfLoadedCourses = 0;

    // Parse through each line from the csv file
    for (string courseString : csvLines) {
        // Create a new Course struct to add to the tree
        Course newCourse;

        // Open the current course string as a stream
        istringstream courseStringStream(courseString);

        elementIndex = 0;

        // Get each element from the current course string stream
        while (getline(courseStringStream, courseElement, ',')) {
            // Update the new course struct with the course number from the current course element
            if (elementIndex == 0) {
                // The letters in the course number should be uppercase for searching purposes
                newCourse.courseNumber = toUpperCase(courseElement);
            }

            // Update the new course struct with the course name from the current course element
            if (elementIndex == 1) {
                newCourse.courseName = courseElement;
            }

            // Append the current course element (prerequisite) to the new course struct's prerequisites vector
            if (elementIndex >= 2) {
                // Skip empty strings or strings of whitespace
                if (!all_of(courseElement.begin(), courseElement.end(), isspace)) {
                    newCourse.prereqs.push_back(toUpperCase(courseElement));
                }
            }

            elementIndex++;
        }

        // Insert the new course into the BST after processing the current line
        bst->Insert(newCourse);

        // Update the number of courses that were loaded into the tree
        numberOfLoadedCourses++;
    }

    // Print the number of courses that were loaded into the BST
    if (numberOfLoadedCourses == 1) {
        cout << endl << numberOfLoadedCourses << " course was loaded." << endl;
    }
    else {
        cout << endl << numberOfLoadedCourses << " courses were loaded." << endl;
    }

    return true;
}

/**
* Convert all the letters in a given string to uppercase.
*
* @param str - The string to make uppercase.
*/
string toUpperCase(string& str) {
    // Loop through each character in the string and make it uppercase
    transform(str.begin(), str.end(), str.begin(), ::toupper);

    return str;
}

/**
 * main method for menu and going through the menu
 */
int main(int argc, char* argv[]) {
    
    string csvPath = "CS 300 ABCU_Advising_Program_Input.csv"; //path for the csv file
    string courseNumber; // coursenumber for finding and printing
    BinarySearchTree* tree = new BinarySearchTree(); // BST for holding courses
    bool coursesLoaded = false; // bool for course loading
    bool inputFailed = false; // bool for bad input
    int choice = 0; // user's choice of what to do

    cout << "Welcome to the ABCU course planner!" << endl;

    // loop while user doesn't choose 9 to exit the loop
    while (choice != 9) {
        // print menu and options (could later be made its own method if needed to print elsewhere as well)
        cout << endl << "Menu:" << endl;
        cout << "  1. Load Courses" << endl;
        cout << "  2. Display Courses" << endl;
        cout << "  3. Find Course" << endl;
        cout << "  9. Exit" << endl << endl;

        inputFailed = false; // Reset the input failed boolean

        // ask for user choice and put the  input as choice
        cout << "Enter an option number: ";
        cin >> choice;
        cout << endl;

        // ignore anything on the line other than the first integer
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // print error message if the choice isn't an integer first ie a string
        if (cin.fail()) {
            // update the input failed boolean to avoid duplicate messages
            inputFailed = true;

            // clear the input and ignore anymore
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            // print an error message
            cout << "Please enter an integer value of 1, 2, 3, or 9. " << endl;
        }

        switch (choice) {

        case 1:
            // Clear the tree so it is new for new loaded courses
            tree->Clear();

            // load all the courses from the specified csv file
            coursesLoaded = loadCourses(tree, csvPath);
            break; // end of task

        case 2:
            // if courses have been loaded
            if (coursesLoaded) {
                // print all courses in order
                tree->PrintAll();
            }
            else
            {
                // print error message if user has not loaded courses yet
                cout << "Please load courses with Option 1 first." << endl;
            }
            break; // end of task

        case 3:
            // if courses have been loaded
            if (coursesLoaded) {
                // get courseNumber to find
                cout << "Enter the course number to find: ";
                cin >> courseNumber;
                cout << endl;

                toUpperCase(courseNumber); // makes user input uppercase

                // print found course 
                tree->PrintCourse(courseNumber);
            }
            else
            {
                // print an error message if the user has not loaded courses yet
                cout << "Please load courses with Option 1 first." << endl;
            }
            break; // end of task

        case 9:
            break; // end of task

        default:
            // invalid input, but error message hasn't displayed yet
            if (!inputFailed) {
                // print error message
                cout << "Please enter an integer value of 1, 2, 3, or 9. " << endl;
            }
            break; // end of task
        }
    }
    return 0;
}