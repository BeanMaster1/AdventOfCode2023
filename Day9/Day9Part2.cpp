#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

bool is_zeroes(vector<int> v)
{
    for(int i = 0; i < v.size(); i++)
    {
        if(v[i]!=0)
        {
            return false;
        }
    }
    return true;
}
int main()
{
    fstream finput("Day9Input.txt");
    string buf;
    int sum = 0;
    while(getline(finput, buf))
    {
        istringstream line(buf);
        vector<vector<int>> sequences;
        vector<int> first_sequence;
        first_sequence.push_back(0);
        int num_buf;
        while(line >> num_buf)
        {
            first_sequence.push_back(num_buf);
        }
        sequences.push_back(first_sequence);
        for(int i = 0; !is_zeroes(sequences[i]); i++)
        {
            vector<int> next_sequence;
            next_sequence.push_back(0);
            for(int j = 2; j < sequences[i].size(); j++)
            {
                next_sequence.push_back(sequences[i][j] - sequences[i][j-1]);
            }
            sequences.push_back(next_sequence);
        }
        for(int i = sequences.size()-2; i >= 0; i--)
        {
            sequences[i][0] = sequences[i][1] - sequences[i+1][0];
        }
        sum += sequences[0][0];
    }
    cout << sum;
}