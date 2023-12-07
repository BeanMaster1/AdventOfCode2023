#include <iostream>
#include <fstream>

using namespace std;

int main()
{
    ifstream in = ifstream("Day1Input.txt");
    int sum = 0;
    string line;
    while(in >> line)
    {
        for(int i = 0; i < line.length(); i++)
        {
            if(isdigit(line[i]))
            {
                sum += 10*(line[i] - '0');
                break;
            }
        }
        for(int i = line.length()-1; i >= 0; i--)
        {
            if(isdigit(line[i]))
            {
                sum += (line[i] - '0');
                break;
            }
        }
    }
    cout << sum;
}