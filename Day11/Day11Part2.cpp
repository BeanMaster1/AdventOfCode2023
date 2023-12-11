#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

using namespace std;

struct coord
{
    int r; int c;
};

int main()
{
    fstream finput("Day11Input.txt");
    vector<vector<char>> space;
    vector<coord> galaxies;
    string buf;
    while(getline(finput, buf))
    {
        vector<char> row;
        for(int i = 0; i < buf.length(); i++)
        {
            row.push_back(buf[i]);
        }
        space.push_back(row);
    }
    vector<int> empty_rows;
    vector<int> empty_columns;
    for(int r = 0; r < space.size(); r++)
    {
        bool flag = true;
        for(int c = 0; c < space[r].size(); c++)
        {
            if(space[r][c]!='.')
            {
                coord new_galaxy;
                new_galaxy.r = r;
                new_galaxy.c = c;
                galaxies.push_back(new_galaxy);
                flag = false;
            }
        }
        if(flag)
        {
            empty_rows.push_back(r);
        }
    }
    for(int c = 0; c < space[0].size(); c++)
    {
        bool flag = true;
        for(int r = 0; r < space.size(); r++)
        {
            if(space[r][c]!='.')
            {
                flag = false;
                break;
            }
        }
        if(flag)
        {
            empty_columns.push_back(c);
        }
    }
    long long sum = 0;
    for(int i = 0; i < galaxies.size(); i++)
    {
        for(int j = i+1; j < galaxies.size(); j++)
        {
            int startr = galaxies[i].r;
            int startc = galaxies[i].c;
            int endr = galaxies[j].r;
            int endc = galaxies[j].c;
            int dist = abs(endr-startr) + abs(endc-startc);
            for(int empty_row_idx = 0; empty_row_idx < empty_rows.size(); empty_row_idx++)
            {
                int row_num = empty_rows[empty_row_idx];
                if( (startr < row_num && endr > row_num) || (startr > row_num && endr < row_num) )
                {
                    dist += 999999;
                }
            }
            for(int empty_col_idx = 0; empty_col_idx < empty_columns.size(); empty_col_idx++)
            {
                int col_num = empty_columns[empty_col_idx];
                if( (startc < col_num && endc > col_num) || (startc > col_num && endc < col_num) )
                {
                    dist += 999999;
                }
            }
            sum += dist;
        }
    }
    cout << sum;
}