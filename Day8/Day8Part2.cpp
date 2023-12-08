#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

int gcd(long long a, long long b)
{
    if (a == 0)
        return b;
    return gcd(b % a, a);
}
int main()
{
    fstream finput("Day8Input.txt");
    string instructions;
    getline(finput, instructions);
    string buf;
    getline(finput, buf);
    map<string, vector<string>> node_map;
    while(getline(finput, buf))
    {
        istringstream line(buf);
        string parent;
        string left;
        string right;
        line >> parent >> buf >> left >> right;
        left = left.substr(1,3);
        right = right.substr(0,3);
        vector<string> children;
        children.push_back(left);
        children.push_back(right);
        node_map[parent] = children;
    }
    vector<string> current_positions;
    for(map<string, vector<string>>::iterator it = node_map.begin(); it != node_map.end(); it++)
    {
        string s = it->first;
        if(s[2]=='A')
        {
            current_positions.push_back(s);
        }
    }
    vector<int> counts;
    for(int i = 0; i < current_positions.size(); i++)
    {
        
        int move_count = 0;
        while(current_positions[i][2]!='Z')
        {
            switch(instructions[move_count%instructions.size()])
            {
                case 'L':
                    current_positions[i] = node_map[current_positions[i]][0];
                    break;
                case 'R':
                    current_positions[i] = node_map[current_positions[i]][1];
                    break;
            }
            move_count++;
        }
        counts.push_back(move_count);
    }
    //This is a scam, I got lucky on my guess that they wanted LCM because it felt like an LCM problem,
    //but upon rereading the question there is no stated gurantee that LCM will work.
    //To fix the problem, it should be defined as
    //"If a ghost is already on a node ending with 'Z', it returns to the node that it started at originally"
    long long lcm = counts[0];
    for(int i = 1; i < counts.size(); i++)
    {
        lcm = (lcm*counts[i])/gcd(lcm, counts[i]);
    }
    cout << lcm;
}