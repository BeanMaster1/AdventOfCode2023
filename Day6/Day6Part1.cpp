#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

int main()
{
    fstream finput("Day6Input.txt");
    string buf;
    getline(finput,buf);
    istringstream line(buf);
    line >> buf;
    int numbuf;
    vector<int> times;
    while(line >> numbuf)
    {
        times.push_back(numbuf);
    }
    vector<int> distances;
    getline(finput, buf);
    line = istringstream(buf);
    line >> buf;
    while(line >> numbuf)
    {
        distances.push_back(numbuf);
    }
    int answer = 1;
    for(int race = 0; race < times.size(); race++)
    {
        int count = 0;
        for(int t = 0; t < times[race]; t++)
        {
            if(t*(times[race]-t) > distances[race])
            {
                count++;
            }
        }
        if(count > 0)
        {
            answer*=count;
        }
    }
    cout << answer;
}