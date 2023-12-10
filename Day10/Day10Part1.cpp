#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

vector<vector<char>> map;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int explore(int r, int c, int steps_taken, int direction)
{
    if(r < 0 || r >= map.size() || c < 0 || c >= map[r].size() || map[r][c] == '.')
    {
        return 0;
    }
    if(map[r][c]=='S')
    {
        return steps_taken;
    }
    char temp = map[r][c];
    switch(direction)
    {
        case UP:
            switch(temp)
            {
                case '|':
                    return explore(r-1, c, steps_taken+1, UP);
                case '7':
                    return explore(r, c-1, steps_taken+1, LEFT);
                case 'F':
                    return explore(r, c+1, steps_taken+1, RIGHT);
                default:
                    return 0; 
            }
        case DOWN:
            switch(temp)
            {
                case '|':
                    return explore(r+1, c, steps_taken+1, DOWN);
                case 'L':
                    return explore(r, c+1, steps_taken+1, RIGHT);
                case 'J':
                    return explore(r, c-1, steps_taken+1, LEFT);
                default:
                    return 0;
                
            }
        case LEFT:
            switch(temp)
            {
                case '-':
                    return explore(r, c-1, steps_taken+1, LEFT);
                case 'L':
                    return explore(r-1, c, steps_taken+1, UP);
                case 'F':
                    return explore(r+1, c, steps_taken+1, DOWN);
                default:
                    return 0;
            }
        case RIGHT:
            switch(temp)
            {
                case '-':
                    return explore(r, c+1, steps_taken+1, RIGHT);
                case 'J':
                    return explore(r-1, c, steps_taken+1, UP);
                case '7':
                    return explore(r+1, c, steps_taken+1, DOWN);
                default:
                    return 0;
            }
    }
    return 0;
}
int main()
{
    fstream finput("Day10Input.txt");
    string buf;
    int startr = 0; int startc = 0;
    for(int r = 0; getline(finput, buf); r++)
    {
        vector<char> row;
        for(int c = 0; c < buf.length(); c++)
        {
            row.push_back(buf[c]);
            if(buf[c] == 'S')
            {
                startr = r;
                startc = c;
            }
        }
        map.push_back(row);
    }
    int path_length = 
    max(explore(startr-1, startc, 1, UP),
        max(explore(startr+1, startc, 1, DOWN),
            max(explore(startr, startc-1, 1, LEFT),
                explore(startr, startc+1, 1, RIGHT)
               )
           )
       );
        
    cout << path_length/2 << endl;;
    /*for(int i = 0; i < map.size(); i++)
    {
        for(int j = 0; j < map[i].size(); j++)
        {
            cout << map[i][j];
        }cout << endl;
    }*/
    
}