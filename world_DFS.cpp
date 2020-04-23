#include <iostream>
#include <fstream>
#include <istream>
#include <stdio.h>
#include <queue>
using namespace std;

struct A{
  int x;
  int y;
};

queue <A> wavefront;

int rows = 8;
int cols = 16;
int arr[8][16];
int startx;
int starty;
int endx;
int endy;

void fillIn(int x, int y){
    int b = y;
    int a = x;
    if ((arr[b-1][a] == 0) && !((b-1) < 0) && !((b-1) >= rows)) {
        arr[b-1][a] = (arr[y][x]);

        if (((a != endx) || ((b-1) != endy)) && ((a != endx) || ((b+1) != endy)) && (((a+1) != endx) || (b != endy)) && (((a-1) != endx) || (b != endy))) {
          fillIn(a,b-1);
        }
    }
    if ((arr[b+1][a] == 0) && !((b+1) < 0) && !((b+1) >= rows)){
        arr[b+1][a] = 3;//(arr[b][a]);

        if (((a != endx) || ((b-1) != endy)) && ((a != endx) || ((b+1) != endy)) && (((a+1) != endx) || (b != endy)) && (((a-1) != endx) || (b != endy))) {
          fillIn(a,b+1);
        }
    }
    if ((arr[b][a+1] == 0) && !((a-1) < 0) && !((a-1) >= cols)){
        arr[b][a+1] = (arr[y][x]);

        if (((a != endx) || ((b-1) != endy)) && ((a != endx) || ((b+1) != endy)) && (((a+1) != endx) || (b != endy)) && (((a-1) != endx) || (b != endy))) {
          fillIn(a+1,b);
        }
    }
    if ((arr[b][a-1] == 0) && !((a-1) < 0) && !((a-1) >= cols)){
        arr[b][a-1] = (arr[y][x]);

        if (((a != endx) || ((b-1) != endy)) && ((a != endx) || ((b+1) != endy)) && (((a+1) != endx) || (b != endy)) && (((a-1) != endx) || (b != endy))) {
          fillIn(a-1,b);
        }
    }

    /*if (((a != endx) || ((b-1) != endy)) && ((a != endx) || ((b+1) != endy)) && (((a+1) != endx) || (b != endy)) && (((a-1) != endx) || (b != endy))) {
      //fillIn(a,(b-1));
      //fillIn(a,(b+1));
      //fillIn((a+1),b);
      //fillIn((a-1),b);
    }*/
    
}


int main(){
  fstream file;
  file.open("world1.dat");
  if (file.is_open()) {
    int x;
  //  string line;
  //  file.getline(line, ' ');
  //  while (getline(file, line)){
  //        rows++;
    //while (file >> x){
    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++) {
        file >> arr[i][j];
        cout << arr[i][j] << " ";
      }
      cout << "\n";
    }
  }
  else {
    cout << "world file not found";
  }

  cout << "Please enter the starting location's x value: ";
  cin >> startx;
  cout << "Please enter the starting location's y value: ";
  cin >> starty;
  cout << "Please enter the ending location's x value: ";
  cin >> endx;
  cout << "Please enter the ending location's y value: ";
  cin >> endy;


  // endx < startx    // x--
  // endx > startx    // x++
  // endx = startx    // x = x
  // endy < starty    // y--
  // endy > starty    // y++
  // endy = starty    // y = y

  arr[starty][startx] = 2;
  int x = startx;
  int y = starty;

  for (int i = 0; i < rows; i++)
  {
    for (int j = 0; j < cols; j++) {
      //file >> arr[i][j];
      cout << arr[i][j] << " ";
    }
    cout << "\n";
  }

  cout << "\n";


  fillIn(x, y);
  //while(arr[y][x] != arr[endy][endx]) {
  //    if (endy < starty) && (endx < startx) &&  {
  //      y = y--;
  //      x = x--;
  //    }
  //}

    for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++) {
        //file >> arr[i][j];
        cout << arr[i][j] << " ";
      }
      cout << "\n";
    }



}