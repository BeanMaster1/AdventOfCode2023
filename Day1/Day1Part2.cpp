#include <iostream>
#include <fstream>
#include <chrono>
#include <iomanip>

using namespace std;

int numberAt(string str, int i)
{
    string l3 = str.substr(i,3);
    string l4 = str.substr(i,4);
    string l5 = str.substr(i,5);
    if(l3 == "one") return 1;
    if(l3 == "two") return 2;
    if(l5 == "three") return 3;
    if(l4 == "four") return 4;
    if(l4 == "five") return 5;
    if(l3 == "six") return 6;
    if(l5 == "seven") return 7;
    if(l5 == "eight") return 8;
    if(l4 == "nine") return 9;

    return 0;
}
int main()
{
    auto t1 = chrono::high_resolution_clock::now();
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
            if(int x = numberAt(line, i))
            {
                sum += 10*x;
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
            
            if(int x = numberAt(line, i))
            {
                sum += x;
                break;
            }

        }
        
    }
    cout << sum << endl;
    auto t2 = chrono::high_resolution_clock::now();
    /* Getting number of milliseconds as a double. */
    chrono::duration<double, std::milli> ms_double = t2 - t1;

   
    std::cout << ms_double.count() << "ms\n";;
}