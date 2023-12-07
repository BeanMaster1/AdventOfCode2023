#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <cmath>
#include <map>

using namespace std;

int cardval(char c);
int compare_hands(string hand_1, string hand_2);
int get_type(map<char, int> hand_map);
void sort_by_hand(vector<string>& hands, vector<int>& bets);
int cardval(char c)
{
    switch(c)
    {
        case '2':
            return 2;
        case '3':
            return 3;
        case '4':
            return 4;
        case '5':
            return 5;
        case '6':
            return 6;
        case '7':
            return 7;
        case '8':
            return 8;
        case '9':
            return 9;
        case 'T':
            return 10;
        case 'J':
            return 11;
        case 'Q':
            return 12;
        case 'K':
            return 13;
        case 'A':
            return 14;
    }
    return 0;
        
}
int compare_hands(string hand_1, string hand_2)
{
    map<char, int> hand_1_cards;
    map<char, int> hand_2_cards;
    for(int i = 0; i < hand_1.length(); i++)
    {
        if(hand_1_cards.count(hand_1[i]) == 0)
        {
            hand_1_cards[hand_1[i]] = 1;
        }else
        {
            hand_1_cards[hand_1[i]]++;
        }
    }
    for(int i = 0; i < hand_2.length(); i++)
    {
        if(hand_2_cards.count(hand_2[i]) == 0)
        {
            hand_2_cards[hand_2[i]] = 1;
        }else
        {
            hand_2_cards[hand_2[i]]++;
        }
    }  
    if(get_type(hand_1_cards) > get_type(hand_2_cards))
    {
        return 1;
    }else if(get_type(hand_1_cards) < get_type(hand_2_cards))
    {
        return -1;
    }else
    {
        for(int i = 0; i < hand_1.size(); i++)
        {
            if(cardval(hand_1[i]) > cardval(hand_2[i]))
            {
                return 1;
            }else if(cardval(hand_1[i]) < cardval(hand_2[i]))
            {
                return -1;
            }
        }
    }

    return 0;
}
int get_type(map<char, int> hand_map)
{
    if(hand_map.size() == 5)
    {
        return 1;
    }else if(hand_map.size() == 4)
    {
        return 2;
    }else if(hand_map.size() == 3)
    {
        int max_cnt = 0;
        for(map<char,int>::iterator it = hand_map.begin(); it!=hand_map.end(); it++)
        {
            max_cnt = max(max_cnt, it->second);
        }
        if(max_cnt == 2)
        {
            return 3;
        }else if(max_cnt == 3)
        {
            return 4;
        }
    }else if(hand_map.size() == 2)
    {
        int max_cnt = 0;
        for(map<char,int>::iterator it = hand_map.begin(); it!=hand_map.end(); it++)
        {
            max_cnt = max(max_cnt, it->second);
        }
        if(max_cnt == 3)
        {
            return 5;
        }else if(max_cnt == 4)
        {
            return 6;
        }
    }else if(hand_map.size() == 1)
    {
        return 7;
    }
    return 0;
}
void sort_by_hand(vector<string>& hands, vector<int>& bets)
{
    for(int i = 0; i < hands.size(); i++)
    {
        int max_idx = i;
        string max_hand = hands[i];
        for(int j = i+1; j < hands.size(); j++)
        {
            if(compare_hands(hands[j], hands[max_idx]) > 0)
            {
                max_hand = hands[j];
                max_idx = j;
            }
        }
        string temp_hand = hands[max_idx];
        int temp_bet = bets[max_idx];
        hands[max_idx] = hands[i];
        bets[max_idx] = bets[i];
        hands[i] = temp_hand;
        bets[i] = temp_bet;
    }
}
int main()
{
    fstream finput("Day7Input.txt");
    vector<string> hands;
    vector<int> bets;
    string buf;
    while(finput >> buf)
    {
        hands.push_back(buf);
        int bet;
        finput >> bet;
        bets.push_back(bet);
    }
    sort_by_hand(hands, bets);
    int sum = 0;
    for(int i = 0; i < hands.size(); i++)
    {
        sum += (hands.size()-i)*bets[i];
    }
    cout << sum;
}

