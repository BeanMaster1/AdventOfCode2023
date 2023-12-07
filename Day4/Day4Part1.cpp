#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>

using namespace std;

int main()
{
    ifstream finput("Day4Input.txt");
    string line;
    int sum = 0;
    while(getline(finput, line))
    {
        istringstream lstr(line);
        string buf;
        lstr >> buf >> buf;
        int winning[100] = {0};
        while(lstr >> buf)
        {
            if(buf=="|")
            {
                break;
            }
            int idx;
            istringstream(buf) >> idx;
            winning[idx] = 1;
        }
        int count = 0;
        while(lstr >> buf)
        {
            int idx;
            istringstream(buf) >> idx;
            if(winning[idx])
            {
                count++;
            }
        }
        if(count!=0)
        {
            sum += pow(2, count-1);
        }
    }
    cout << sum;
}