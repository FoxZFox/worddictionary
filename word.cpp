#include <iostream>
#include <fstream>
#include <map>
#include <vector>
#include <algorithm>
#include <chrono>

using namespace std;
using namespace chrono;

vector<string> ans;

bool compareByLength(const string &a, const string &b)
{
    return a.length() < b.length();
}

struct TrieNode
{
    map<string, TrieNode *> children;
    bool full_word = false;
};

struct TrieNode *root = new TrieNode;

void Maketrie()
{
    ifstream dictionaryFile("dictionary.txt");
    string word;
    if (!dictionaryFile.is_open())
    {
        cout << "Error: Could can't open dictionary.txt";
    }
    else
    {
        cout << "[info] Can open dictionary.txt\n";
        cout << "[info] Create a map\n";
        string word;
        while (!dictionaryFile.eof())
        {
            struct TrieNode *current = root;
            dictionaryFile >> word;
            for (size_t i = 0; i < word.length(); i++)
            {
                string letter = string(1, word[i]);
                if ((current->children).find(letter) == (current->children).end())
                    (current->children)[letter] = new TrieNode;
                current = (current->children)[letter];
                if (i == word.length() - 1)
                    current->full_word = true;
            }
        }
    }
}

void makeword(string word, string letters, TrieNode *node)
{
    if (node->full_word && word.length() > 2 && find(ans.begin(), ans.end(), word) == ans.end())
    {
        ans.push_back(word);
    }
    if (letters.length() < 1)
        return;

    for (size_t i = 0; i < letters.length(); i++)
    {
        // cout << "[log] letters : " << letters << endl;
        string letter = string(1, letters[i]);
        // cout << "[log] letter : " << letter << endl;

        if (node->children.find(letter) != node->children.end())
        {
            string remaining_letters = letters;
            remaining_letters.erase(i, 1);
            // cout << "[log] remaining_letters : " << remaining_letters << endl;
            makeword(word + letter, remaining_letters, node->children[letter]);
        }
    }
}

int main()
{

    Maketrie();

    while (true)
    {
        system("cls");
        cout << "[input] Enter Letters of the board bitch : ";
        string letters;
        letters.clear();
        cin.sync();
        cin >> letters;
        auto start_time = high_resolution_clock::now();
        makeword("", letters, root);
        sort(ans.begin(), ans.end(), compareByLength);
        for (int i = 0; i < ans.size(); i++)
        {
            cout << "[info] word : " << ans[i] << endl;
        }

        auto end_time = high_resolution_clock::now();
        duration<double> elapsed_seconds = end_time - start_time;
        cout << "[info] use time : " << elapsed_seconds.count() << " s\n";
        cout << "[info] Continue ? [y/n]: ";
        char loop;
        cin >> loop;
        if (loop != 'y')
        {
            break;
        }
        ans.clear();
    }

    return 0;
}