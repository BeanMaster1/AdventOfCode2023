#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>

using namespace std;

int main()
{
    fstream finput("Day6Input.txt");
    string buf;
    getline(finput,buf);
    istringstream line(buf);
    line >> buf;
    long long time = 0;
    string time_str = "";
    while(line >> buf)
    {
        time_str += buf;
    }
    long long distance = 0;
    getline(finput, buf);
    line = istringstream(buf);
    line >> buf;
    string distance_str = "";
    while(line >> buf)
    {
        distance_str += buf;
    }
    istringstream(time_str) >> time;
    istringstream(distance_str) >> distance;
    int count = 0;
    for(long long t = 0; t < time; t++)
    {
        if(t*(time-t) > distance)
        {
            count++;
        }
    }
    cout << count;
}