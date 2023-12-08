#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

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
    string current = "AAA";
    int move_count = 0;
    while(current!="ZZZ")
    {
        switch(instructions[move_count%instructions.size()])
        {
            case 'L':
                current = node_map[current][0];
                break;
            case 'R':
                current = node_map[current][1];
                break;
        }   
        move_count++;
    }
    cout << move_count;
}