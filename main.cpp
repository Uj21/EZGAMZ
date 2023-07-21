#include <bits/stdc++.h>
#define r 10
#define c 19
#define ROW 50
#define COL 50
const int MAX_PILE_SIZE = 100;
using namespace std;

void Display_Pattern(){
    cout<<"_____________________________________________________________________________________________________________________\n";
    cout<<"                                          ✿ WELCOME TO  EZGAMZ\n";
    cout<<"_____________________________________________________________________________________________________________________\n\n";
    cout<<"EZGAMZ is a menu driven mini-game platform which enables the user to choose any one out of the listed \ngames at a moment and enjoy it as a pastime.\nCreated using C++, this project utilizes a set of data structures and draws the use of backtracking algorithms\n\n";
    cout<<"List of Games:\n✿ The Word Search Game(1)\n✿ Maze Solver(2) \n✿ NIM Game(3) \n✿ Exit(4)" ;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
//MAZE SOLVER
bool visited[ROW][COL];

struct Point
{

    int x;
    int y;

    Point()
    {
        x = 0;
        y = 0;
    }
    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};

struct Node
{
    Point *point;
    int dist;
    Node *prev;
    Node(Point *p, int d, Node *node)
    {
        point = p;
        dist = d;
        prev = node;
    }
};

bool iisSafe(int row, int col)
{
    return (row >= 0) && (row < ROW) && (col >= 0) && (col < COL);
}

vector<Point> dir = {{-1, 0}, {0, -1}, {0, 1}, {1, 0}};

vector<Point *> solveMaze(int maze[][COL], Point *src, Point *dest)
{
    vector<Point *> path;
    if (!maze[src->x][src->y] || !maze[dest->x][dest->y])
        return path;

    visited[src->x][src->y] = true;

    queue<Node *> q;

    Node *s = new Node(src, 0, NULL);
    q.push(s);

    while (!q.empty())
    {
        Node *curr = q.front();
        Point *pt = curr->point;

        if (pt->x == dest->x && pt->y == dest->y)
        {

            do
            {
                path.push_back(new Point({curr->point->x, curr->point->y}));
                curr = curr->prev;
            } while (curr != NULL);
            return path;
        }

        q.pop();

        for (int i = 0; i < 4; i++)
        {
            int newX = pt->x + dir[i].x;
            int newY = pt->y + dir[i].y;

            if (iisSafe(newX, newY) && maze[newX][newY] && !visited[newX][newY])
            {
                visited[newX][newY] = true;
                Point *cell = new Point(newX, newY);

                q.push(new Node(cell, curr->dist + 1, curr));
            }
        }
    }

    return path;
}

void mazze()
{
    int maze[ROW][COL];

    ifstream obj;
    obj.open("maze1.txt", ios::in);
    int startX = 2, startY = 2, endX = 3, endY = 47;
    for (int i = 0; i < ROW; i++)
        for (int j = 0; j < COL; j++)
        {
            obj >> maze[i][j];
        }
    for (int i = 0; i < ROW; i++)
    {
        for (int j = 0; j < COL; j++)
            cout << maze[i][j] << " ";
        cout << endl;
    }

    obj.close();

    Point *source = new Point(startX, startY);
    Point *dest = new Point(endX, endY);

    vector<Point *> shortestPath = solveMaze(maze, source, dest);

    ofstream obj1;
    obj1.open("path.txt", ios::trunc | ios::in);
    if (!shortestPath.empty())
    {
        for (auto it : shortestPath)
        {
            maze[it->x][it->y] = 5;
        }

        obj1 << "\t\t\t\t\t\t\t\t\t\tYou Gotta shortest Path!!👌👍👍" << endl
             << endl;
        for (int i = 0; i < ROW; i++)
        {
            for (int j = 0; j < COL; j++)
                if (maze[i][j] == 0)
                    obj1 << "# ";
                else if (maze[i][j] == 1)
                    obj1 << "  ";
                else if (maze[i][j] == 5)
                    obj1 << ". ";
            obj1 << endl;
        }
    }
    else
    {
        obj1 << "Path does not exist👎👎";
    }
    obj1.close();
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////
class WordSearch{
    public:
   
    string wordsearch;
    int diff;
    char grid[r][c] = { "HORSECHESTNUTOHTSA",
                        "ALVULOILOARNOEPILC",
                        "FEBRPNAMSBESLIBKAO",
                        "GIMKAKIDNELDERTDER",
                        "YVETGECYHRSBULOMFN",
                        "AYOLSRTEVRBSPAFWHP",
                        "SPAHDUSXNILIEJLBAL",
                        "HELPAMONCESLCHYMIN",
                        "STRIELDRLSIVSWTCHO",
                        "BLACKTHORNREKLARKB",
    };
   
    void toggle(string& wordsearch) //function for making the case uniform
{
    int length = wordsearch.length();
    for (int i = 0; i < length; i++) {
        int cc = wordsearch[i];
        if (islower(cc))
            wordsearch[i] = toupper(cc);      
    }
}


// Function to check if a word exists in a grid
// x, y: current position in 2D array
bool findmatch(char mat[r][c], string pat, int x, int y,
            int nrow, int ncol, int level)
{
    int l = pat.length();
    if (level == l)
        return true;
    // Out of Boundary
    if (x < 0 || y < 0 || x >= nrow || y >= ncol)
        return false;
    // If grid matches with a letter while recursion
    if (mat[x][y] == pat[level]) {
        // Marking this cell as visited
        char temp = mat[x][y];
        mat[x][y] = '#';
        // finding subpattern in 4 directions
        bool res = findmatch(mat, pat, x - 1, y, nrow, ncol, level + 1) |
                   findmatch(mat, pat, x + 1, y, nrow, ncol, level + 1) |
                   findmatch(mat, pat, x, y - 1, nrow, ncol, level + 1) |
                   findmatch(mat, pat, x, y + 1, nrow, ncol, level + 1);
        // marking this cell as unvisited again
        mat[x][y] = temp;
        return res;
    }
    else // Not matching then false
        return false;
}
// Function to check if the word exists in the grid or not
bool checkMatch(char mat[r][c], string pat, int nrow, int ncol)
{
    int l = pat.length();
    // if total characters in matrix is less then pattern length
    if (l > nrow * ncol)
        return false;
    // Traverse in the grid
    for (int i = 0; i < nrow; i++) {
        for (int j = 0; j < ncol; j++) {
            // If first letter matches, then recur and check
            if (mat[i][j] == pat[0])
                if (findmatch(mat, pat, i, j, nrow, ncol, 0))
                    return true;
        }
    }
    return false;
}
   
   
void Play_WordSearch(){
    int loop;
    int score=0;
   
    for (int i = 0; i < r; i++)
       for (int j = 0; j < c; j++)
 
          cout << grid[i][j] << " \n"[j == c-1];
   
    cout<<"\n\nSelect difficulty level\n";
    cout<<"1. Easy- find 5 words (1)\n2. Medium- find 10 words (2)\n3. Hard- find 15 words(3)\n\n\n";
    cout<<"Your Choice: "; cin>>diff;
   
    if (diff == 1){
        loop=5;
    }
    else if (diff == 2){
        loop=10;
    }
    else if (diff == 3){
        loop=15;
    }
    else{
    cout<<"Invalid Input! Select a valid difficulty level.";
       
    }
   
       
for(int i=0; i<loop; i++){
    cout<<"Your Solution: ";
    cin>>  wordsearch;
    toggle(wordsearch);
          if (checkMatch(grid, wordsearch, r, c)) {
             cout << "You scored a point!\n";
             score= score+10;}
          else{
             cout << "No such word exists :(\n"; }
}
cout<<"\n\nYour final score: "<< score;
}
 
};

////////////////////////////////////////////////////////////////////////////////////////////////////////////
std::vector<int> nim_values(MAX_PILE_SIZE + 1, -1);

// Recursive function to calculate the Nim value for a given pile size
int calculate_nim_value(int pile_size) {
    if (nim_values[pile_size] != -1) {
        return nim_values[pile_size];
    }

    std::vector<bool> visited(MAX_PILE_SIZE + 1, false);
    for (int i = 1; i <= pile_size; ++i) {
        int nim_value = calculate_nim_value(pile_size - i);
        visited[nim_value] = true;
    }

    for (int i = 0; i < visited.size(); ++i) {
        if (!visited[i]) {
            nim_values[pile_size] = i;
            return i;
        }
    }

    return 0;
}

// Function to play a game of Nim
void play_nim_game() {
    int pile_size;
    std::cout << "Enter the starting size of the pile: ";
    std::cin >> pile_size;

    int current_player = 1;
    while (pile_size > 0) {
        std::cout << "Player " << current_player << ", enter the number of items to remove: ";
        int items_to_remove;
        std::cin >> items_to_remove;

        if (items_to_remove < 1 || items_to_remove > pile_size) {
            std::cout << "Invalid number of items to remove. Please try again." << std::endl;
            continue;
        }

        pile_size -= items_to_remove;
        if (pile_size == 0) {
            std::cout << "Player " << current_player << " wins!" << std::endl;
        }
        else {
            std::cout << "New pile size: " << pile_size << std::endl;
            current_player = (current_player == 1) ? 2 : 1;
        }
    }
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////

int main()
{
    int choice;
    Display_Pattern();
    cout<<"\n\nYour choice: "; cin>>choice;
    WordSearch game;
    
    switch(choice){
        case 1:
        cout<<"\n\nThe Word Search Game\n\n";
        game.Play_WordSearch();
        break;
       
        case 2:
        cout<<"\n\nMaze Solver\n\n";
        mazze();
        break;

        case 3:
        cout<<"\n\nNIM Game\n\n";
         // Calculate the Nim values for all possible pile sizes
         nim_values[0] = 0;
        for (int pile_size = 1; pile_size <= MAX_PILE_SIZE; ++pile_size) {
        calculate_nim_value(pile_size);
         }// Play a game of Nim
        play_nim_game();
        break;

        case 4:
        cout<<"Good Bye!";
        exit(1);
       
    }

    return 0;
}