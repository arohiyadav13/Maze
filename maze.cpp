/*
maze.cpp
*/

#include <iostream>
#include "mazeio.h"
#include "queue.h"

using namespace std;

// Prototype for maze_search, which you will fill in below.
int maze_search(char**, int, int);

// Add other prototypes here for any functions you wish to use


// main function to read, solve maze, and print result
int main(int argc, char* argv[]) {
    int rows, cols, result;
    char** mymaze=NULL;
    const char* invalid_char_message = "Error, invalid character.";
    const char* invalid_maze_message = "Invalid maze.";
    const char* no_path_message = "No path could be found!";

    if(argc < 2)
    {
        cout << "Please provide a maze input file" << endl;
        return 1;
    }

    mymaze = read_maze(argv[1], &rows, &cols); // <---TASK: COMPLETE THIS FOR CHECKPOINT 1

    // For checkpoint 2 you should check the validity of the maze
    // You may do so anywhere you please and can abstract that
    // operation with a function or however you like.
  
  
    bool valid = true;

    for(int i = 0; i < rows; i++)
    {
      for(int j = 0; j < cols; j++)
      {
        if((mymaze[i][j] != '.') && (mymaze[i][j] != '#') && (mymaze[i][j] != 'S') && (mymaze[i][j] != 'F'))
        {
          //cout << mymaze[i][j];
          cout << invalid_char_message << endl; 
          valid = false;
          break;
        }
      }
    }

    result = maze_search(mymaze, rows, cols);

    if(valid)
    {
      if (result == -1)
      {
        cout << invalid_maze_message << endl; 
      }
      if(result == 0)
      {
        cout << no_path_message << endl;
      }
      if(result == 1)
      {
        //cout << "entered" << endl;
        print_maze(mymaze, rows, cols);
      }
    }
    //================================
    // When working on Checkpoint 4, you will need to call maze_search
    // and output the appropriate message or, if successful, print
    // the maze.  But for Checkpoint 1, we print the maze, regardless.
    //print_maze(mymaze, rows, cols);
    

    //================================
    // ADD CODE BELOW 
    // to delete all memory that read_maze allocated: CHECKPOINT 2

    for (int i = 0; i < rows; i++) 
    {
    delete[] mymaze[i];
    }
    delete[] mymaze;

    return 0;
}

/**************************************************
 * Attempt to find shortest path and return:
 *  1 if successful
 *  0 if no path exists
 *
 * If path is found fill it in with '*' characters
 *  but don't overwrite the 'S' and 'F' cells
 * NOTE: don't forget to deallocate memory in here too!
 *************************************************/
int maze_search(char** maze, int rows, int cols)
{
    // *** You complete **** CHECKPOINT 4
    Location start;  
    int hasStart = 0;
    int hasEnd = 0;
    for(int i = 0; i< rows; i++)
    {
      for(int j = 0; j< cols; j++)
      {
        if (maze[i][j] == 'S')
        {
          start.row = i;
          start.col = j;
          hasStart++;
        }
        if (maze[i][j] == 'F')
        {
          hasEnd++; 
        }
      }
    }

    if((hasStart != 1) || (hasEnd != 1))
    {
      return -1; 
    }

    Queue q(rows*cols);
    

    Location** predecessor = new Location*[rows];
    for(int i=0; i<rows; i++)
    {
      predecessor[i] = new Location[cols];
      for (int j =0; j<cols; j++){
          predecessor[i][j].row = -1; //maybe here 
          predecessor[i][j].col = -1;
      }         
    }

    bool** explored = new bool*[rows];
    for(int i=0; i<rows; i++)
    {
      explored[i] = new bool[cols];
      for (int j =0; j<cols; j++){
          explored[i][j] = false;
      }                 
    }


    explored[start.row][start.col] = true;
    q.add_to_back(start);

    // if(end.row == 10000)
    // {
    //   end.row = 1; 
    // }

    bool finish = false; 
    Location last; 

    while(q.is_empty() == false)
    { 
      Location loc = q.remove_from_front();
      
      Location north; 
      north.row = loc.row -1;
      north.col = loc.col;

      bool ninbound = (north.row>=0) && (north.row<rows) && (north.col>=0) && (north.col<cols);

      if(ninbound)
      {

      if(maze[north.row][north.col] == 'F')
      {
        finish = true; 
        last = loc; 
        break; 
      }

      if(maze[north.row][north.col] == '.' && explored[north.row][north.col] == false)
      {
        explored[north.row][north.col] = true;
        q.add_to_back(north); 
        predecessor[north.row][north.col] = loc; 
         
      }

      }
      
      Location south; 
      south.row = loc.row +1;
      south.col = loc.col;
      bool sinbound = (south.row>=0) && (south.row<rows) && (south.col>=0) && (south.col<cols);

      if(sinbound)
      {

      if(maze[south.row][south.col] == 'F')
      {
        finish = true; 
        last = loc;
        break; 
      }

      if(maze[south.row][south.col] == '.' && explored[south.row][south.col] == false)
      {
        explored[south.row][south.col] = true;
        q.add_to_back(south); 
        predecessor[south.row][south.col] = loc; 
         
      }

      }

      Location west; 
      west.row = loc.row;
      west.col = loc.col -1;
      bool winbound = (west.row>=0) && (west.row<rows) && (west.col>=0) && (west.col<cols); 

      if(winbound)
      {

      if(maze[west.row][west.col] == 'F')
      {
        finish = true; 
        last = loc;
        break; 
      }

      if(maze[west.row][west.col] == '.' && explored[west.row][west.col] == false)
      {
        explored[west.row][west.col] = true;
        q.add_to_back(west); 
        predecessor[west.row][west.col] = loc; 
         
      }

      }


      Location east; 
      east.row = loc.row;
      east.col = loc.col +1;
      bool einbound = (east.row>=0) && (east.row<rows) && (east.col>=0) && (east.col<cols); 

      if(einbound)
      {

      if(maze[east.row][east.col] == 'F')
      {
        finish = true; 
        last = loc;
        break; 
      }

      if(maze[east.row][east.col] == '.' && explored[east.row][east.col] == false)
      {
        explored[east.row][east.col] = true;
        q.add_to_back(east); 
        predecessor[east.row][east.col] = loc; 
         
      }

      }
    }

    if(finish == true)
      {
        while(!(last.row == start.row && last.col == start.col))
        {
          //cout << "here" << endl; 
          //cout << last.row << last.col << endl;
          maze[last.row][last.col] = '*';
          last = predecessor[last.row][last.col];
        } 
      }

      for(int i = 0; i< rows; i++)
      {
        delete [] predecessor[i];
        delete [] explored[i];
      }

      delete [] predecessor;
      delete [] explored;
      
      return finish;

}
