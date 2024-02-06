#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <regex>

using namespace std;

int check(string spring, regex pattern)
{
    if(regex_match(spring, pattern))
    {
        return 1;
    }
    return 0;
}
int generate(string base, int idx, regex pattern)
{
    if(idx>=base.length())
    {
        return check(base, pattern);
    }else if(base[idx] == '?')
    {
        return generate(base.substr(0,idx) + '.' + base.substr(idx+1), idx+1 , pattern) + generate(base.substr(0,idx) + '#' + base.substr(idx+1), idx+1, pattern); 
    }else
    {
        return generate(base, idx+1, pattern);
    }
}
int main()
{
    fstream finput("Day12Input.txt");
    string buf;
    int sum;
    while(getline(finput, buf))
    {
        string symbols; string nums;
        istringstream(buf) >> symbols >> nums;
        symbols += symbols + symbols + symbols + symbols;
        nums += "," + nums + "," + nums + "," + nums + "," + nums;
        ostringstream patternstrbuf; patternstrbuf << "\\.*";
        istringstream nums_str(nums);
        while(getline(nums_str, buf, ','))
        {
            patternstrbuf << "#{" << buf << "}\\.+";
        }
        string patternstr = patternstrbuf.str().substr(0, patternstrbuf.str().length()-1) + "*";
        regex pattern(patternstr);
        sum+=generate(symbols, 0, pattern);

    }
    cout << sum;
}