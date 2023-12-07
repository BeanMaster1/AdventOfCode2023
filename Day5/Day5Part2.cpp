#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>


using namespace std;

typedef struct 
{
    long long start;
    long long end;
} range;

typedef struct
{
    long long start;
    long long end;
    long long dest;
} mapping;


void sort_by_start(vector<range>& v)
{
    for(int i = 0; i < v.size(); i++)
    {
        long long min = v[i].start;
        int min_idx = i;
        for(int j = i+1; j < v.size(); j++)
        {
            if(v[j].start < min)
            {
                min = v[j].start;
                min_idx = j;
            }
        }
        range temp = v[i];
        v[i] = v[min_idx];
        v[min_idx] = temp;
    }
}
void sort_by_start(vector<mapping>& v)
{
    for(int i = 0; i < v.size(); i++)
    {
        long long min = v[i].start;
        int min_idx = i;
        for(int j = i+1; j < v.size(); j++)
        {
            if(v[j].start < min)
            {
                min = v[j].start;
                min_idx = j;
            }
        }
        mapping temp = v[i];
        v[i] = v[min_idx];
        v[min_idx] = temp;
    }
}
int main()
{
    //set up input, throw away trash
    fstream finput("Day5Input.txt");
    string buf;
    getline(finput, buf);
    istringstream line(buf);
    getline(finput, buf);
    line >> buf;
    vector<range> ranges;
    long long numbuf;
    //input starting ranges of seeds into ranges, a range has a start number(inclusive) and an end number(exclusive)
    while(line >> numbuf)
    {
        range new_range;
        new_range.start = numbuf;
        line >> numbuf;
        new_range.end = new_range.start + numbuf;
        ranges.push_back((new_range));
    }
    //sorts the ranges to be in numerical order by their startingpoints, by problem definition no overlap in ranges when sorted this way
    sort_by_start(ranges);
    /*cout << "ranges: [";
    for(int i = 0; i < ranges.size(); i++)
    {
        cout << "[" << ranges[i].start << "," << ranges[i].end << "),";
    }cout << "]" << endl;*/
    
    //go through each layer of mapping
    for(int layer = 0; layer < 7; layer++)
    {
        //read in this layer of mapping
        vector<range> new_ranges;
        vector<mapping> mappings;
        getline(finput, buf);
        while(getline(finput, buf) && buf!="")
        {
            line = istringstream(buf);
            long long dest;
            long long source;
            long long range;
            line >> dest >> source >> range;
            mapping m;
            m.start = source;
            m.end = source + range;
            m.dest = dest;
            mappings.push_back(m);
        }
        //sort read mappings numerically
        sort_by_start(mappings);
        //for each range of available values...
        for(int range_idx = 0; range_idx < ranges.size(); range_idx++)
        {
            //start at the begining of the range
            long long current_spot_in_range = ranges[range_idx].start;
            //start using the map with the lowest input values
            long long current_mapping_idx = 0;
            //while we havent transformed the whole range     and       theres still mappings we can use
            while(current_spot_in_range < ranges[range_idx].end && current_mapping_idx < mappings.size())
            {
                //if current mapping has input values too small
                if(mappings[current_mapping_idx].end <= current_spot_in_range)
                {
                    //go to next mapping and try again
                    current_mapping_idx++;
                    continue;
                }
                //if this mapping (and all later mappings) have input values too high
                if(mappings[current_mapping_idx].start >= ranges[range_idx].end)
                {
                    //stop checking
                    break;
                }
                //OTHERWISE: The current mapping has some overlap with the current range
                //check mappings[current_mapping_idx] for overlap
                range new_range;
                //if the mapping we are using starts lower than our current position
                if(mappings[current_mapping_idx].start <= current_spot_in_range)
                {
                    //we start the new range at the output of our current position
                    new_range.start = mappings[current_mapping_idx].dest + (current_spot_in_range - mappings[current_mapping_idx].start);
                    //if the mapping ends before the current range ends
                    if(mappings[current_mapping_idx].end < ranges[range_idx].end)
                    {
                        //the new range will end after                 the difference of where we started and the end of the mapping input
                        new_range.end = new_range.start + (mappings[current_mapping_idx].end - current_spot_in_range);
                        current_spot_in_range = mappings[current_mapping_idx].end;
                    //else the mapping ends after our current range ends
                    }else
                    {
                        //so we end the new range            after the distance we still have to travel 
                        new_range.end = new_range.start + (ranges[range_idx].end - current_spot_in_range);
                        current_spot_in_range = ranges[range_idx].end;
                    }
                //our mapping starts after our current position
                }else
                {
                    //we will do a 1:1 mapping all the way to the start of the next mapping
                    range to_range;
                    to_range.start = current_spot_in_range;
                    to_range.end = mappings[current_mapping_idx].start;
                    new_ranges.push_back(to_range);
                    current_spot_in_range = mappings[current_mapping_idx].start;
                    new_range.start = mappings[current_mapping_idx].dest;
                    //then...
                    //if the mapping ends before the current range ends
                    if(mappings[current_mapping_idx].end < ranges[range_idx].end)
                    {
                        //same as above
                        new_range.end = new_range.start + (mappings[current_mapping_idx].end - current_spot_in_range);
                        current_spot_in_range = mappings[current_mapping_idx].end;
                    //the mapping ends after the current range ends
                    }else
                    {
                        //same as above
                        new_range.end = new_range.start + (ranges[range_idx].end - current_spot_in_range);
                        current_spot_in_range = ranges[range_idx].end;
                    }
                } 
                //add the newly mapped range to the next level of available points and continue working through available points
                new_ranges.push_back(new_range);
                    
                
            }
            //if we still have numbers in our current range but no maps to apply, we add an ending 1:1 mapping to the next level
            if(current_spot_in_range != ranges[range_idx].end)
            {
                range new_range;
                new_range.start = current_spot_in_range;
                new_range.end = ranges[range_idx].end;
                new_ranges.push_back(new_range);
            }
        }
        //our new set of ranges of available points updates to the current layer
        ranges = new_ranges;
        /*cout << "ranges: [";
        for(int i = 0; i < ranges.size(); i++)
        {
            cout << "[" << ranges[i].start << "," << ranges[i].end << "),";
        }cout << "]" << endl;*/
    }
    //the lowest available point is the first point in the smallest range
    sort_by_start(ranges);
    cout << ranges[0].start;
}