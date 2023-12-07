#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <climits>

using namespace std;

class Map
{
    public:
        vector<long long> destination;
        vector<long long> source;
        vector<long long> range;
        Map(fstream& finput)
        {
            string line;
            getline(finput, line);
            while(getline(finput, line))
            {
                if(line == "")
                {
                    break;
                }
                istringstream lstr(line);
                long long num;
                lstr >> num; destination.push_back(num);
                lstr >> num; source     .push_back(num);
                lstr >> num; range      .push_back(num);
            }
            
        }
        long long get(long long input)
        {
            for(int i = 0; i < destination.size(); i++)
            {
                if(input >= source[i] && input < source[i] + range[i])
                {
                    //cout << input << "->" << destination[i] + input - source[i] << "(" << i << ")" << endl;
                    return destination[i] + input - source[i];
                }
            }
            //cout << input << "->" << input << endl;
            return input;
        }

};
int main()
{
    fstream finput("Day5Input.txt");
    vector<long long> seeds;
    string line;
    getline(finput, line);
    istringstream lstr(line);
    string buf;
    lstr >> buf;
    long long numbuf;
    while(lstr >> numbuf)
    {
        seeds.push_back(numbuf);
    }
    getline(finput, line);
    Map seed_to_soil(finput);
    Map soil_to_fertilizer(finput);
    Map fertilizer_to_water(finput);
    Map water_to_light(finput);
    Map light_to_temperature(finput);
    Map temperature_to_humidity(finput);
    Map humidity_to_location(finput);

    long long min_location = LLONG_MAX;
    for(int i = 0; i < seeds.size(); i++)
    {
        long long seed = seeds[i]; //cout << "seed: " << seed << endl;
        long long soil = seed_to_soil.get(seed); //cout << "soil: " << soil << endl;
        long long fertilizer = soil_to_fertilizer.get(soil); //cout << "fertilizer: " << fertilizer << endl;
        long long water = fertilizer_to_water.get(fertilizer); //cout << "water: " << water << endl;
        long long light = water_to_light.get(water); //cout << "light: " << light << endl;
        long long temperature = light_to_temperature.get(light); //cout << "temperature: " << temperature << endl;
        long long humidity = temperature_to_humidity.get(temperature); //cout << "humidity: " << humidity << endl;
        long long location = humidity_to_location.get(humidity); //cout << "location: " << location << endl;
        min_location = min(min_location, location); //cout << "min_location: " << min_location << endl << endl;
    }
    cout << min_location;
}

