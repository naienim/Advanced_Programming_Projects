#include <iostream>
#include <string>
#include <vector>
using namespace std;

string to_upper(string line)
{   
    if (line.size() <= 0)
    {
        return "";
    }
    if (islower(line[0]))
    {
        line[0]=toupper(line[0]);
    }
    
    return line[0] + to_upper(line.substr(1));
}

int main() 
{
    string line;
    while (getline(cin, line)) 
    {
        cout << to_upper(line) << endl;
    }

    return 0;
}
