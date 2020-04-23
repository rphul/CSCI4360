#include <iostream>
#include <fstream>
#include <istream>
#include <stdio.h>
#include <queue>
using namespace std;

struct A{
  int x;
  int y;
  int value;
  A *next = nullptr;
  A *prev = nullptr;
  bool visited = false;
};

queue <A> wavefront;

int rows = 8;
int cols = 16;
A arr[8][16];
int startx;
int starty;
int endx;
int endy;

void printMaze() {
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++) {
      cout << arr[i][j].value << " ";
    }
    cout << "\n";
  }
}

void InitializeMaze(string f) {
  fstream file;
  file.open(f);
  if (file.is_open()) {
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++) {
        file >> arr[i][j].value;
        arr[i][j].x = j;
        arr[i][j].y = i;
        //cout << arr[i][j].value << " ";
      }
      //cout << "\n";
    }
  }
  else {
    cout << "world file not found";
  }
}

void StartEnd(){
  cout << "Please enter the starting location's x value: ";
  cin >> startx;
  while ((startx < 0) || (startx >= cols)) {
    cout << "Please enter a starting location of 0 or a positive integer less than the number of columns " << cols << ": ";
    cin >> startx;
  }
  cout << "Please enter the starting location's y value: ";
  cin >> starty;
  while ((starty < 0) || (startx >= rows)) {
    cout << "Please enter a starting location of 0 or a positive integer less than the number of rows " << rows << ": ";
    cin >> starty;
  }
  cout << "Please enter the ending location's x value: ";
  cin >> endx;
  while ((endx < 0) || (endx >= cols)) {
    cout << "Please enter an ending location of 0 or a positive integer less than the number of columns " << cols << ": ";
    cin >> endx;
  }
  cout << "Please enter the ending location's y value: ";
  cin >> endy;
  while ((endx < 0) || (endx >= rows)) {
    cout << "Please enter a starting location of 0 or a positive integer less than the number of columns " << rows << ": ";
    cin >> endx;
  }

  if (arr[starty][startx].value == 1) {
    cout << "Starting location is an obstacle.\n";
    StartEnd();
  }
  if (arr[endy][endx].value == 1) {
    cout << "Ending location is an obstacle.\n";
    StartEnd();
  }
  if ((startx == endx) && (starty == endy)) {
    cout << "Starting location is the same as ending location.\n";
    StartEnd();
  }
  

}

void PrintMaze() {
  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++) {
      cout << arr[i][j].value << " ";
    }
    cout << "\n";
  }
  cout << "\n";
}

void BFS(A node){
  int y = node.y;
  int x = node.x;
  arr[y][x].visited = true;
  if (arr[y][x].prev != nullptr){
    node.value = node.prev->value + 1;
    arr[y][x].value = arr[y][x].prev->value + 1;
  }
  else {
    node.value = 2;
    arr[y][x].value = 2;
  }
  
  if ((arr[y+1][x].value == 0)  && !((y+1) < 0) && !((y+1) >= rows) && !arr[y+1][x].visited) {
    arr[y+1][x].prev = &arr[y][x];
    wavefront.push(arr[y+1][x]);
  }
  
  if ((arr[y-1][x].value == 0) && !((y-1) < 0) && !((y-1) >= rows)  && !arr[y-1][x].visited){
    arr[y-1][x].prev = &arr[y][x];
    wavefront.push(arr[y-1][x]);
  }
  
  if ((arr[y][x+1].value == 0) && !((x+1) < 0) && !((x+1) >= cols) && !arr[y][x+1].visited){
    arr[y][x+1].prev = &arr[y][x];
    wavefront.push(arr[y][x+1]);
  }
  
  if ((arr[y][x-1].value == 0) && !((x-1) < 0) && !((x-1) >= cols)  && !arr[y][x-1].visited){
    arr[y][x-1].prev = &arr[y][x];
    wavefront.push(arr[y][x-1]);
  }
}

void PrintPath(){
  int b = endy;
  int a = endx;
  A position;
  position = arr[endy][endx];
  int count = 0;
  cout << "The path is: ";
  deque <A> path;
  int y = b;
  int x = a;
  path.push_front(arr[y][x]);
  while ((position.y != starty) || (position.x != startx) ){
    //cout << "(" << position.x << "," << position.y << "),";
    b = arr[y][x].prev->y;
    a = arr[y][x].prev->x;
    y = b;
    x = a;
    count += 1;
    position = arr[y][x];
    path.push_front(arr[y][x]);
  }

  A position2;
  while (!path.empty()) {
    position2 = path.front();
    
    cout << "(" << position2.x << "," << position2.y << "),";
    path.pop_front();
  }
  cout << "\n";
  cout << "The number of steps from (" << startx << "," << starty << ") to (" << endx << "," << endy << ") is " << count << "\n";
}


int main(int argc, char** argv){
  if (argc == 2) {
    string file;
    file = argv[1];
    InitializeMaze(file);
    StartEnd();

    wavefront.push(arr[starty][startx]);
    while (!wavefront.empty()){
      BFS(wavefront.front());
      wavefront.pop();
    }
    PrintPath();

    //PrintMaze();
  }
  else {
    cout << "No file input";
  }
}
