#include<Windows.h>
#include<iostream>
#include<conio.h>
#include<ctime>
using namespace std;
const int rows = 10;
const int cols = 10;

class candycrush {
private:
    // class node that represents the double linked list 
    class Node {
    public:
        Node* prev;
        Node* next;
        char candy;
        Node(char c) :candy(c), prev(0), next(0) {}
    };
    //array of double linked list 
    Node* board[rows];

    char getrandomcandy() const {
        char candies[] = { 'A', 'B', 'C', 'D','E' };
        //int numcandies = sizeof(candies) / sizeof(candies[0]);
        int randomindex = rand() % 5;
        return candies[randomindex];
    }

public:
    candycrush() {
        for (int i = 0; i < rows; i++) {
            board[i] = nullptr;
        }
    }

    Node* getnode(int row, int col) const {
        if (isValidPosition(row, col)) {
            Node* current = board[row];
            for (int i = 0; i < col && current != nullptr; i++) {
                current = current->next;
            }
            return current;
        }
        return nullptr;
    }

    //Done
    bool isValidPosition(int ROWS, int COLS) const {
        return ROWS >= 0 && ROWS <= rows && COLS >= 0 && COLS < cols;
    }

    //Done
    void initializeboard() {
        srand(time(NULL));
        for (int i = 0; i < rows; i++) {
            for (int j = 0; j < cols; j++) {
                char candy = getrandomcandy();
                Node* newnode = new Node(candy);
                if (board[i] == nullptr) {
                    board[i] = newnode;
                }
                else {
                    Node* current = board[i];
                    while (current->next != nullptr) {
                        current = current->next;
                    }
                    current->next = newnode;
                    newnode->prev = current;
                }
            }
        }
    }

    //Done 
    void printborder(int score, int moves, int currentrow, int currentcol) const {
        system("cls");
        //the gravity effection that makes the candies fall down
        for (int c = 0; c < cols; c++) {
            for (int r = rows - 1; r > 0; r--) {
                if (getnode(r, c)->candy == '\0') {
                    Node* tempCandy = getnode(r - 1, c);
                    getnode(r, c)->candy = tempCandy->candy;
                }
            }
        }
        cout << "score: " << score << "  moves: " << moves << endl;
        // the top of the border 
        for (int i = 0; i <= cols + 3; i++) {
                cout << "___";
        }
        cout << endl;
        for (int i = 0; i < rows; i++) {
            cout << "|";//the left wall
            Node* current = board[i];
            int colindex = 0;
            while (current != nullptr) {
                if (current->candy != '\0') {//if the candy exist then do the following code   /0 = null charcter
                    if (i == currentrow && colindex == currentcol) {//this condition is to check the current selected candy
                        // Change the color to purple for the selected candy
                        HANDLE selectedcandy = GetStdHandle(STD_OUTPUT_HANDLE);
                        SetConsoleTextAttribute(selectedcandy, 13); // 13 represents the color code for pink
                        cout << "[" << current->candy << "]";
                        SetConsoleTextAttribute(selectedcandy, 15); // Reset text color to white
                    }
                    else {
                        // Set colors for other candies
                        HANDLE candies = GetStdHandle(STD_OUTPUT_HANDLE);
                        int color;
                        switch (current->candy) {
                        case 'A':
                            color = 12; //light red
                            break;
                        case 'B':
                            color = 9; //light blue
                            break;
                        case 'C':
                            color = 10; //light green
                            break;
                        case 'D':
                            color = 14; //light yellow
                            break;
                        case 'E':
                            color = 15; // white
                            break;
                        default:
                            color = 15; // Default color is white
                            break;
                        }
                        SetConsoleTextAttribute(candies, color);
                        cout << " " << current->candy << " ";
                        SetConsoleTextAttribute(candies, 15); // Reset text color to white
                    }
                }
                else {
                    cout << "   ";
                }
                current = current->next;
                colindex++;
                cout << "|";
            }

            cout << endl;
        }
        //print the bottom of the border 
        for (int i = 0; i <= cols + 3; i++) {
                cout << "___";
        }
        cout << endl;
    }

    //Done
    void moveselection(int& row, int& col, char input) {
        switch (input) {
        case 'w':
            row = (row - 1 + rows) % rows;
            break;
        case 'a':
            col = (col - 1 + cols) % cols;
            break;
        case 's':
            row = (row + 1) % rows;
            break;
        case 'd':
            col = (col + 1) % cols;
            break;
        case 'e':
            // Store the current position as the selected candy
            int selectedRow = row;
            int selectedCol = col;
            while (true) {
                char userInput = _getch();
                if (userInput == 'w' || userInput == 'a' || userInput == 's' || userInput == 'd') {
                    nextmove(selectedRow, selectedCol, userInput);
                    break;

                }
            }
            // Swap the selected candy with the user's move
            swapcandies(row, col, selectedRow, selectedCol);
            break;
        }
    }

    //Done
    void nextmove(int& row, int& col, char input) {
        switch (input) {
        case 'w':
            row = (row - 1 + rows) % rows;
            break;
        case 's':
            row = (row + 1) % rows;
            break;
        case 'a':
            col = (col - 1 + cols) % cols;
            break;
        case 'd':
            col = (col + 1) % cols;
            break;
        }
    }

    //Done
    void swapcandies(int row1, int col1, int row2, int col2) {
        if (isValidPosition(row1, col1) && isValidPosition(row2, col2)) {
            Node* node1 = getnode(row1, col1);
            Node* node2 = getnode(row2, col2);
            char temp = node1->candy;
            node1->candy = node2->candy;
            node2->candy = temp;
        }
    }

    //Done
    void generatenewcandies(int startrow, int col, int count) {
        for (int row = startrow; row >= count; row--) {
            getnode(row, col)->candy = getnode(row - count, col)->candy;
        }
        for (int row = count - 1; row >= 0; row--) {
            getnode(row, col)->candy = getrandomcandy();
        }
    }

    //Done
    bool checkmatch(int row, int col) {
        char candy = getnode(row, col)->candy;
        // Check horizontal matches
        int left = col - 1;
        int right = col + 1;
        int matches = 1;
        while (left >= 0 && getnode(row, left)->candy == candy) {
            left--;
            matches++;
        }
        while (right < cols && getnode(row, right)->candy == candy) {
            right++;
            matches++;
        }
        if (matches >= 3) {
            return true;
        }
        // Check vertical matches
        int up = row - 1;
        int down = row + 1;
        matches = 1;
        while (up >= 0 && getnode(up, col)->candy == candy) {
            up--;
            matches++;
        }
        while (down < rows && getnode(down, col)->candy == candy) {
            down++;
            matches++;
        }
        if (matches >= 3) {
            return true;
        }
        return false;
    }

    //Done
    void destroycandies(int row, int col) {
        char candy = getnode(row, col)->candy;
        getnode(row, col)->candy = '\0';
        // Destroy horizontal candies
        int left = col - 1;
        int right = col + 1;
        while (left >= 0 && getnode(row, left)->candy == candy) {
            getnode(row, left)->candy = '\0';
            left--;
        }
        while (right < cols && getnode(row, right)->candy == candy) {
            getnode(row, right)->candy = '\0';
            right++;
        }
        // Destroy vertical candies
        int up = row - 1;
        int down = row + 1;
        while (up >= 0 && getnode(up, col)->candy == candy) {
            getnode(up, col)->candy = '\0';
            up--;
        }
        while (down < rows && getnode(down, col)->candy == candy) {
            getnode(down, col)->candy = '\0';
            down++;
        }
    }

    //Done
    bool checkbordermatches() {
        // Check horizontal matches on borders
        for (int row = 0; row < rows; row++) {
            if (getnode(row, 0)->candy != '\0' && getnode(row, 0)->candy == getnode(row, 1)->candy && getnode(row, 0)->candy == getnode(row, 2)->candy) {
                return true;
            }
            if (getnode(row, cols - 1)->candy != '\0' && getnode(row, cols - 1)->candy == getnode(row, cols - 2)->candy && getnode(row, cols - 1)->candy == getnode(row, cols - 3)->candy) {
                return true;
            }
        }
        // Check vertical matches on borders
        for (int col = 0; col < cols; col++) {
            if (getnode(0, col)->candy != '\0' && getnode(0, col)->candy == getnode(1, col)->candy && getnode(0, col)->candy == getnode(2, col)->candy) {
                return true;
            }
            if (getnode(rows - 1, col)->candy != '\0' && getnode(rows - 1, col)->candy == getnode(rows - 2, col)->candy && getnode(rows - 1, col)->candy == getnode(rows - 3, col)->candy) {
                return true;
            }
        }
        return false;
    }

};

int main() {
    candycrush c;
    int currentrow = 0;
    int currentcol = 0;
    char input;
    int score = 0;
    int moves = 0;
    c.initializeboard();
    while (true) {
        c.printborder(score, moves, currentrow, currentcol);
        cout <<" Press q to quit.\n"
             <<"\n Use the following arrows to move in the game border \n"
             <<" W to move up \n"
             <<" A to move left \n"
             <<" S to move down \n"
             <<" D to move right \n"
             <<" e to select a candy and swap it when you make the second move\n"
             <<" ALL LETTERS ARE IN A LOWER CASE ..........\n";
        input = _getch();
        if (input == 'q'||input=='Q') {
            exit(0);
        }
        else {
            c.moveselection(currentrow, currentcol, input);
            moves++;
            if (c.checkmatch(currentrow, currentcol)) {
                c.destroycandies(currentrow, currentcol);
                score += 10;
                c.generatenewcandies(0, currentcol, currentrow + 1);
            }
            else if (c.checkbordermatches()) {
                // Handle border matches
                // Generate new candies in their place
                for (int row = 0; row < rows; row++) {
                    if (c.getnode(row, 0)->candy == c.getnode(row, 1)->candy && c.getnode(row, 0)->candy == c.getnode(row, 2)->candy) {
                        c.destroycandies(row, 0);
                        c.destroycandies(row, 1);
                        c.destroycandies(row, 2);
                        score += 10;
                        c.generatenewcandies(row, 0, 3);
                    }
                    if (c.getnode(row, cols - 1)->candy == c.getnode(row, cols - 2)->candy && c.getnode(row, cols - 1)->candy == c.getnode(row, cols - 3)->candy) {
                        c.destroycandies(row, cols - 1);
                        c.destroycandies(row, cols - 2);
                        c.destroycandies(row, cols - 3);
                        score += 10;
                        c.generatenewcandies(row, cols - 3, 3);
                    }
                }
                for (int col = 0; col < cols; col++) {
                    if (c.getnode(0, col)->candy == c.getnode(1, col)->candy && c.getnode(0, col)->candy == c.getnode(2, col)->candy) {
                        c.destroycandies(0, col);
                        c.destroycandies(1, col);
                        c.destroycandies(2, col);
                        score += 10;
                        c.generatenewcandies(2, col, 3);
                    }
                    if (c.getnode(rows - 1, col)->candy == c.getnode(rows - 2, col)->candy && c.getnode(rows - 1, col)->candy == c.getnode(rows - 3, col)->candy) {
                        c.destroycandies(rows - 1, col);
                        c.destroycandies(rows - 2, col);
                        c.destroycandies(rows - 3, col);
                        score += 10;
                        c.generatenewcandies(rows - 3, col, 3);
                    }
                }
            }
        }
    }
}
