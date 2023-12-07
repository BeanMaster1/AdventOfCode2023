#include <iostream>
#include <fstream>
#include <sstream>

#define NUMBER_OF_ORIGINALS 218

using namespace std;

int main()
{
    ifstream finput("Day4Input.txt");
    long numCards[NUMBER_OF_ORIGINALS];
    int numMatches[NUMBER_OF_ORIGINALS];
    for(int i = 0; i < NUMBER_OF_ORIGINALS; i++)
    {
        numCards[i] = 1;
        numMatches[i] = 0;
    }
    string line;
    while(getline(finput, line))
    {
        istringstream linestream(line);
        string buf;
        linestream >> buf >> buf;
        int current_card;
        istringstream(buf.substr(0, buf.length()-1)) >> current_card; current_card--;
        
        int winning_numbers[100] = {0};
        while(linestream >> buf)
        {
            if(buf=="|")
            {
                break;
            }
            int idx;
            istringstream(buf) >> idx;
            winning_numbers[idx] = 1;
        }
        int count = 0;
        while(linestream >> buf)
        {
            int idx;
            istringstream(buf) >> idx;
            if(winning_numbers[idx])
            {
                count++;
            }
        }
        numMatches[current_card] = count;
        for(int i = 1; i <= count; i++)
        {
            numCards[current_card+i] += numCards[current_card];
        }
    }
    long sum = 0;
    for(int i = 0; i < NUMBER_OF_ORIGINALS; i++)
    {
        sum += numCards[i];
    }
    cout << sum;
}