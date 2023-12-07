#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int getNumber(string str, int pos)
{
    if(pos < 0 || pos >= str.length() || !isdigit(str[pos]))
    {
        return 0;
    }
    string num;
    num += str[pos];
    int lpos = pos-1;
    while(lpos >= 0 && isdigit(str[lpos]))
    {
        num = str[lpos] + num;
        lpos--;
    }
    int rpos = pos+1;
    while(rpos < str.length() && isdigit(str[rpos]))
    {
        num = num + str[rpos];
        rpos++;
    }
    int val;
    istringstream(num) >> val;
    return val;
}
int main()
{
    ifstream finput("Day3Input.txt");
    int linecount = 0;
    string buf;
    while(getline(finput, buf))
    {
        linecount++;
    }
    finput.clear();
    finput.seekg(0, ios::beg);
    string matrix[linecount];
    for(int i = 0; getline(finput, matrix[i]); i++);
    finput.clear(); finput.close();
    
    int sum = 0;
    for(int r = 0; r < linecount; r++)
    {
        for(int c = 0; c < matrix[r].length(); c++)
        {
            if(!isdigit(matrix[r][c]) && matrix[r][c]!='.')
            {
                if(r > 0)
                {   
                    if(isdigit(matrix[r-1][c]))
                    {
                        sum+=getNumber(matrix[r-1], c);
                    }else
                    {
                        sum += getNumber(matrix[r-1], c-1) + getNumber(matrix[r-1], c+1);
                    }
                }
                if (r < linecount - 1)
                {
                    if(isdigit(matrix[r+1][c]))
                    {
                        sum+=getNumber(matrix[r+1], c);
                    }else
                    {
                        sum += getNumber(matrix[r+1], c-1) + getNumber(matrix[r+1], c+1);
                    }
                }
                sum += getNumber(matrix[r], c-1) + getNumber(matrix[r], c+1);
            }
            
        }
    }
    cout << sum;
}