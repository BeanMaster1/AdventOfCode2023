#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>

using namespace std;

vector<vector<char>> map;
vector<vector<char>> isolated_pipe;
vector<vector<char>> big_map;

#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

void surround(int r, int c, int cnt)
{
    
    if(cnt>=32250)
    {
        return;
    }
    if(r < 0 || r >= big_map.size() || c < 0 || c >= big_map[r].size())
    {
        return;
    }
    if(big_map[r][c] == 'X' || big_map[r][c] == 'O')
    {
        return;
    }
    big_map[r][c] = 'O';
    surround(r+1, c, cnt+1);
    surround(r-1, c, cnt+1);
    surround(r, c+1, cnt+1);
    surround(r, c-1, cnt+1);
    
}
struct coord
{
    int r; int c;
};
void bfs_surround()
{
    //size_t max_q_size = 0;
    queue<coord> coords;
    coord start; start.r=0; start.c=0;
    coords.push(start);
    while(coords.size()>0)
    {
        //max_q_size = max(max_q_size, coords.size());
        coord curr = coords.front(); coords.pop();
        int r = curr.r; int c = curr.c;
        if(r < 0 || r >= big_map.size() || c < 0 || c >= big_map[r].size() || big_map[r][c] == 'X' || big_map[r][c] == 'O')
        {
            continue;
        }else
        {
            big_map[r][c] = 'O';
            coord up; up.r = r-1; up.c = c;
            coord down; down.r = r+1; down.c = c;
            coord left; left.r = r; left.c = c-1;
            coord right; right.r = r; right.c = c+1;
            coords.push(up); coords.push(down); coords.push(left); coords.push(right);
        }
    }
    //cout << "max_q_size: " << max_q_size << endl;
}
int explore(int r, int c, int steps_taken, int direction)
{
    if(r < 0 || r >= map.size() || c < 0 || c >= map[r].size() || map[r][c] == '.')
    {
        return 0;
    }
    if(map[r][c]=='S')
    {
        isolated_pipe[r][c] = 'S';
        return steps_taken;
    }
    char temp = map[r][c];
    isolated_pipe[r][c] = temp;
    int retval = 0;
    switch(direction)
    {
        case UP:
            switch(temp)
            {
                case '|':
                    retval = explore(r-1, c, steps_taken+1, UP);
                    break;
                case '7':
                    retval = explore(r, c-1, steps_taken+1, LEFT);
                    break;
                case 'F':
                    retval = explore(r, c+1, steps_taken+1, RIGHT);
                    break;
                default:
                    return 0; 
            }break;
        case DOWN:
            switch(temp)
            {
                case '|':
                    retval = explore(r+1, c, steps_taken+1, DOWN);
                    break;
                case 'L':
                    retval = explore(r, c+1, steps_taken+1, RIGHT);
                    break;
                case 'J':
                    retval = explore(r, c-1, steps_taken+1, LEFT);
                    break;
                default:
                    return 0;
                
            }break;
        case LEFT:
            switch(temp)
            {
                case '-':
                    retval = explore(r, c-1, steps_taken+1, LEFT);
                    break;
                case 'L':
                    retval = explore(r-1, c, steps_taken+1, UP);
                    break;
                case 'F':
                    retval = explore(r+1, c, steps_taken+1, DOWN);
                    break;
                default:
                    return 0;
            }break;
        case RIGHT:
            switch(temp)
            {
                case '-':
                    retval = explore(r, c+1, steps_taken+1, RIGHT);
                    break;
                case 'J':
                    retval = explore(r-1, c, steps_taken+1, UP);
                    break;
                case '7':
                    retval = explore(r+1, c, steps_taken+1, DOWN);
                    break;
                default:
                    return 0;
            }break;
    }
    if(retval==0)
        isolated_pipe[r][c] = '.';
    return retval;
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
    for(int i = 0; i < map.size(); i++)
    {
        vector<char> row;
        for(int j = 0; j < map[i].size(); j++)
        {
            row.push_back('.');
        }
        isolated_pipe.push_back(row);
    }
    int pipelen = 0;
    pipelen = max(pipelen, explore(startr + 1, startc, 1, DOWN));
    pipelen = max(pipelen, explore(startr - 1, startc, 1, UP));
    pipelen = max(pipelen, explore(startr, startc + 1, 1, RIGHT));
    pipelen = max(pipelen, explore(startr, startc - 1, 1, LEFT));
        
    /*for(int i = 0; i < map.size(); i++)
    {
        for(int j = 0; j < map[i].size(); j++)
        {
            cout << map[i][j];
        }cout << endl;
    }*/
    //At this point, isolated_pipe is ONLY the tiles used in the main pipe, 'S', or '.'
    int discriminant = 0;
    char above_s = isolated_pipe[startr-1][startc];
    if(above_s == '|' || above_s == 'F' || above_s == '7')
    {
        discriminant+=1;
    }
    char below_s = isolated_pipe[startr+1][startc];
    if(below_s == 'L' || below_s == 'J' || below_s == '|')
    {
        discriminant += 2;
    }
    char left_s = isolated_pipe[startr][startc-1];
    if(left_s == '-' || left_s == 'F' || left_s == 'L')
    {
        discriminant += 4;
    }
    char right_s = isolated_pipe[startr][startc+1];
    if(right_s == '-' || right_s == '7' || right_s == 'J')
    {
        discriminant += 8;
    }
    switch (discriminant)
    {
        case 3:
            isolated_pipe[startr][startc] = '|';
            break;
        case 5:
            isolated_pipe[startr][startc] = 'J';
            break;
        case 9:
            isolated_pipe[startr][startc] = 'L';
            break;
        case 6:
            isolated_pipe[startr][startc] = '7';
            break;
        case 10:
            isolated_pipe[startr][startc] = 'F';
            break;
        case 12:
            isolated_pipe[startr][startc] = '-';
    }
    /*cout << endl << endl << endl << endl;
    for(int i = 0; i < isolated_pipe.size(); i++)
    {
        for(int j = 0; j < isolated_pipe[i].size(); j++)
        {
            cout << isolated_pipe[i][j];
        }cout << endl;
    }*/
    //Now S has been properly replaced
    //Time to increase resolution
    
    for(int r = 0; r < isolated_pipe.size(); r++)
    {
        vector<char> row_1;
        vector<char> row_2;
        vector<char> row_3;
        for(int c = 0; c < isolated_pipe[r].size(); c++)
        {
            switch(isolated_pipe[r][c])
            {
                case '.':
                    row_1.push_back('.');row_1.push_back('.');row_1.push_back('.');
                    row_2.push_back('.');row_2.push_back('.');row_2.push_back('.');
                    row_3.push_back('.');row_3.push_back('.');row_3.push_back('.');
                    break;
                case '|':
                    row_1.push_back('.');row_1.push_back('X');row_1.push_back('.');
                    row_2.push_back('.');row_2.push_back('X');row_2.push_back('.');
                    row_3.push_back('.');row_3.push_back('X');row_3.push_back('.');
                    break;
                case '-':
                    row_1.push_back('.');row_1.push_back('.');row_1.push_back('.');
                    row_2.push_back('X');row_2.push_back('X');row_2.push_back('X');
                    row_3.push_back('.');row_3.push_back('.');row_3.push_back('.');
                    break;
                case 'L':
                    row_1.push_back('.');row_1.push_back('X');row_1.push_back('.');
                    row_2.push_back('.');row_2.push_back('X');row_2.push_back('X');
                    row_3.push_back('.');row_3.push_back('.');row_3.push_back('.');
                    break;
                case 'F':
                    row_1.push_back('.');row_1.push_back('.');row_1.push_back('.');
                    row_2.push_back('.');row_2.push_back('X');row_2.push_back('X');
                    row_3.push_back('.');row_3.push_back('X');row_3.push_back('.');
                    break;
                case 'J':
                    row_1.push_back('.');row_1.push_back('X');row_1.push_back('.');
                    row_2.push_back('X');row_2.push_back('X');row_2.push_back('.');
                    row_3.push_back('.');row_3.push_back('.');row_3.push_back('.');
                    break;
                case '7':
                    row_1.push_back('.');row_1.push_back('.');row_1.push_back('.');
                    row_2.push_back('X');row_2.push_back('X');row_2.push_back('.');
                    row_3.push_back('.');row_3.push_back('X');row_3.push_back('.');
                    break;
            }
        }
        big_map.push_back(row_1);big_map.push_back(row_2);big_map.push_back(row_3);
    }
    /*for(int r = 0; r < big_map.size(); r++)
    {
        for(int c = 0; c < big_map[r].size(); c++)
        {
            cout << big_map[r][c];
        }
        cout << endl;
    }cout << endl << endl << endl << endl;*/
    //surround(0,0,0); //recursively fills area around map. crashes ~32500 layers. Works at 32250 layers, does not work at 32000 layers due to not finishing recursion. Sucks
    bfs_surround(); //uses a queue to bfs fill map. Queue maxes out at size 856. Muy Bueno
    /*for(int r = 0; r < big_map.size(); r++)
    {
        for(int c = 0; c < big_map[r].size(); c++)
        {
            cout << big_map[r][c];
        }
        cout << endl;
    }*/
    int count = 0;
    for(int r = 0; r < isolated_pipe.size(); r++)
    {
        for(int c = 0; c < isolated_pipe[r].size(); c++)
        {
            if(big_map[3*r+1][3*c+1]=='.')
            {
                count++;
            }
        }
    }
    cout << count;
}