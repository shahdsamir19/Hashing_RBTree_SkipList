#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <vector>
using namespace std;
/*
class Node {
public:
    int value;
    Node** forward;

    Node(int value, int level) {
        this->value = value;
        forward = new Node*[level + 1];
        for (int i = 0; i <= level; i++) {
            forward[i] = nullptr;
        }
    }

    ~Node() {
        delete[] forward;
    }
};

class SkipList {
private:
    int maxLevel;
    float probability;
    int currentLevel;
    Node* header;

    int randomLevel() {
        int level = 0;
        while (((float)rand() / RAND_MAX) < probability && level < maxLevel) {
            level++;
        }
        return level;
    }

public:
    SkipList(int maxLevel, float probability) {
        this->maxLevel = maxLevel;
        this->probability = probability;
        this->currentLevel = 0;
        this->header = new Node(-1, maxLevel); // Header node with dummy value
    }

    ~SkipList() {
        Node* current = header;
        while (current != nullptr) {
            Node* next = current->forward[0];
            delete current;
            current = next;
        }
    }

    void insert(int value) {
        Node* current = header;
        Node* update[maxLevel + 1];
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current == nullptr || current->value != value) {
            int newLevel = randomLevel();
            if (newLevel > currentLevel) {
                for (int i = currentLevel + 1; i <= newLevel; i++) {
                    update[i] = header;
                }
                currentLevel = newLevel;
            }

            Node* newNode = new Node(value, newLevel);
            for (int i = 0; i <= newLevel; i++) {
                newNode->forward[i] = update[i]->forward[i];
                update[i]->forward[i] = newNode;
            }
        }
    }

    void remove(int value) {
        Node* current = header;
        Node* update[maxLevel + 1];
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
            update[i] = current;
        }

        current = current->forward[0];

        if (current != nullptr && current->value == value) {
            for (int i = 0; i <= currentLevel; i++) {
                if (update[i]->forward[i] != current) break;
                update[i]->forward[i] = current->forward[i];
            }
            delete current;

            while (currentLevel > 0 && header->forward[currentLevel] == nullptr) {
                currentLevel--;
            }
        }
    }

    bool search(int value) {
        Node* current = header;
        for (int i = currentLevel; i >= 0; i--) {
            while (current->forward[i] != nullptr && current->forward[i]->value < value) {
                current = current->forward[i];
            }
        }

        current = current->forward[0];
        return current != nullptr && current->value == value;
    }

    void display() {
        for (int i = 0; i <= currentLevel; i++) {
            Node* node = header->forward[i];
            cout << "Level " << i << ": ";
            while (node != nullptr) {
                cout << node->value << " ";
                node = node->forward[i];
            }
            cout << endl;
        }
    }
};

int main() {
    srand((unsigned)time(0));

    SkipList list(5, 0.5);

    list.insert(3);
    list.insert(6);
    list.insert(7);
    list.insert(9);
    list.insert(12);
    list.insert(19);
    list.insert(17);
    list.insert(26);
    list.insert(21);

    cout << "Skip List after insertion:" << endl;
    list.display();

    cout << "\nSearching for 19: " << (list.search(19) ? "Found" : "Not Found") << endl;
    cout << "Searching for 15: " << (list.search(15) ? "Found" : "Not Found") << endl;

    list.remove(19);
    cout << "\nSkip List after removing 19:" << endl;
    list.display();

    return 0;
}*/
const int maxL = 4;

class node{
public:
    int data;
    vector <node*> next;
    node (int data, int level):data (data),next(level+1, nullptr){};
};
class skipList {
private:
    node* head;
    int level;
public:
    skipList();

    void insert(int data);  // To insert the value
    void remove(int data);  // To delete the value
    bool search(int data);  // To search for a value
    void display();         // Function to display a skip List

};
skipList:: skipList()
{
    head = new node(0, maxL);    // Initializing the skip list with the max number of levels

    level = 0;                               // At start the level is 0

}


void skipList::insert(int data)
{
    int newLevel = 0;


    // Deciding the level of inserting node on the basis of coin toss

    while (newLevel < maxL and (rand() % 2) == 1) // here rand()%2 is doing the coin toss
    {
        newLevel++;
    }
    // Resizing the size of the levels to make place for the inserting value

    if (level < newLevel)
    {
        head->next.resize(newLevel + 1, nullptr);

        level = newLevel;
    }


    node* current = head; // pointer to the head to traverse through the skip list


    vector<node*> Update(level + 1, nullptr); // To store the update node at eah level

    // Loop over the levels upto which we want the value to be inserted

    for (int i = level; i >= 0; i--)
    {
        // Finding the place for the inserting value

        while (current->next[i] and current->next[i]->data < data)
        {
            current = current->next[i];
        }
        // Updating the level accordingly

        Update[i] = current;

    }

    current = current->next[0];   // Moves the current to the next node at level 0

    if (current == nullptr or current->data != data) // if the current is null then it does not exit we need to insert the value
    {
        node* newNode = new node(data, level);

        for (int i = 0; i <= newLevel; i++)
        {
            newNode->next[i] = Update[i]->next[i];

            Update[i]->next[i] = newNode;  // To insert the value at each level

        }

        cout << "Element " << data << " inserted successfully.\n";
    }
    else
    {
        cout << "Element " << data << " already exists.\n";  // Incase if value already exists
    }
}

void skipList::remove(int data)
{
    // Function to remove value
    node* current = head; // start by setting a current pointer to the head node

    vector<node*> Update(level + 1, nullptr); // Create an update vector to store the updated node at each level, Remember only those nodes will be updated where the value to be deleted is present.



    for (int i = level; i >= 0; i--)
    {
        while (current->next[i] and current->next[i]->data < data)
        {
            current = current->next[i];
        }

        Update[i] = current;         // Update array is keeping the track, where the changes should be made, after deleting the node.
    }

    current = current->next[0];     // Set the current pointer to the next node at level 0.

    if (current != nullptr and current->data == data) // If the value is present then delete the value
    {
        for (int i = 0; i <= level; i++)      // Deleting the value from each level
        {
            // Setting the pointers
            if (Update[i]->next[i] != current)
            {
                break;
            }
            else
            {
                Update[i]->next[i] = current->next[i];
            }
        }

        delete current; // deleting the node

        while (level > 0 and head->next[level] == nullptr)  // decrement the level variable incase there is not any value at that level
        {
            level--;
        }

        cout << "Element " << data << " deleted successfully."<<endl;
    }
    else // Incase the value does not exist
    {
        cout << "Element " << data << " not found."<<endl;
    }
}

bool skipList::search(int data)
{
    node* current = head;           // start by setting a current pointer to the head node to traverse through the skip list


    for (int i = level; i >= 0; i--) // Begin traversing from the top level and iteratively approaching the bottom of the skip list
    {
        while (current->next[i] and current->next[i]->data < data) // keep on moving forward if the value of the next node is less than the searching node otherwise  move downward (handled by outer for loop)
        {
            current = current->next[i]; // moving forward

        }
    }

    current = current->next[0]; // Move to the next of the node at level 0

    if (current != nullptr && current->data == data) // if value is found
    {
        cout << "Element " << data << " found.\n";
        return true;
    }
    else  // Incase value does not exist
    {
        cout << "Element " << data << " not found.\n";
        return false;
    }
}
/*
void skipList::display()
{

    cout << "skip List:"<< endl;

    for (int i = level; i >= 0; i--) //
    {
        node* current = head->next[i]; // Initializes the pointer to the first node of that level

        cout << "Level " << i << ": ";

        while (current != nullptr)       // Start displaying all the values present at that level
        {
            cout << current->data << " ";
            current = current->next[i]; // Moving to the right of the node
        }
        cout << endl;
    }
}*/
void skipList::display() {
    for (int i = level; i >= 0; i--) { // Loop from the highest level to level 0
        cout << "Level " << i << ":   "; // Print the current level

        node* current = head->next[i]; // Start from the head's next pointer at this level

        while (current != nullptr) { // Traverse all nodes at this level
            cout << "[" << current->data << "] --> ";
            current = current->next[i]; // Move to the next node at this level
        }

        cout << "nullptr" << endl; // End of the level
    }
}


int main()
{

    skipList SkipList; // Creating the skip List

    // Inserting the Data in skip list

    SkipList.insert(10);
    SkipList.insert(20);
    SkipList.insert(30);
    SkipList.insert(40);
    SkipList.insert(50);

    // Display skip list after inserting the data

    SkipList.display();

    // Searching for the key

    SkipList.search(20);
    SkipList.search(40);


    // Deleting the key

    SkipList.remove(20);
    SkipList.remove(40);

    // Display the skip list after removing the data

    SkipList.display();

    return 0;
}