#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

int main()
{
    ifstream fin = ifstream("Day2Input.txt");
    string line;
    int sum = 0;
    while(getline(fin, line))
    {
        bool valid = true;
        istringstream lstr = istringstream(line);
        string buf;
        lstr >> buf;
        lstr >> buf;
        buf = buf.substr(0, buf.length() - 1);
        int id;
        istringstream(buf) >> id;
        int blue = 0; int red = 0; int green = 0; 
        while(lstr >> buf)
        {
            int num;
            istringstream(buf) >> num;
            lstr >> buf;
            char sep = buf[buf.length()-1];
            if(sep == ',' || sep == ';')
            {
                buf = buf.substr(0, buf.length()-1);
            }else
            {
                sep = '\0';
            }    
            if(buf == "blue")
            {
                blue = num;
            }else if(buf == "red")
            {
                red = num;
            }else if(buf == "green")
            {
                green = num;
            }
            if(sep == ';' || sep == '\0')
            {
                if(red > 12 || green > 13 || blue > 14)
                {
                    valid = false;
                }
                red = blue = green = 0;
            }
        }
        if(valid)
        {
            sum += id;
        }

    }
    cout << sum;
}