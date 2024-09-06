#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <cstdlib>
using namespace std;

typedef struct _TEXT_
{
    string date;
    vector<int> intDate;
    vector<string> words;
    vector<char> textOfDay;
    int numOfPositiveWords;
}text;

vector <string> get_positive_words(vector <string> positive_words);
string find_first_word(string line);
string find_date(string line);
vector<int> string_to_number(string date);
vector<text> start_day(vector<text> myTexts , int numOfTexts , string line);
void show_day(vector<text> myTexts , int numOfTexts , string line);
int find_longest_day(vector<text> myTexts , int numOfTexts);
void print_short_type(vector<text> myTexts , int index);
vector<text> get_text(vector<text> myTexts , int numOfTexts , string inputString);
vector<text> find_positive_words(vector<text> myTexts , int numOfTexts , vector<string> positive_words);
vector<int> find_best_days(vector<text> myTexts , int numOfTexts);
int find_oldest_day(vector<text> myTexts , vector<int> days);

int main()
{
    vector<text> myTexts;
    vector<string> positive_words;
    vector<int> bestDays;
    string inputString;
    string line;
    int flag = 0;
    int numOfTexts = 0;
    int longestDay = 0; 
    int bestDay = 0;

    positive_words = get_positive_words(positive_words);
    
    while (getline(cin,line))
    {
        inputString = find_first_word(line);
        if (inputString == "start_day")
        {
            flag=1; 
            numOfTexts++;
            myTexts = start_day(myTexts , numOfTexts , line);
        }
        else if (inputString == "show_day")
        {
            show_day(myTexts , numOfTexts , line);    
        }
        else if (inputString == "show_the_longest_day" && flag == 1)
        {
            longestDay = find_longest_day(myTexts,numOfTexts);
            print_short_type(myTexts , longestDay);
        }
        else if (inputString == "show_the_best_day" && flag == 1)
        {
            myTexts = find_positive_words(myTexts , numOfTexts , positive_words);
            bestDays = find_best_days(myTexts , numOfTexts);
            bestDay = find_oldest_day(myTexts , bestDays);
            print_short_type(myTexts , bestDay);   
        }
        else if (inputString == "exit_program")
        {
            break;
        }
        else if (flag == 1)
        {
            myTexts = get_text(myTexts , numOfTexts , line);
        }
    }
    return 0;
}

vector<string> get_positive_words(vector <string> positive_words)
{
    string inputFromFile;
    ifstream fin;
    fin.open("positive-words.txt");
    while (getline(fin, inputFromFile)) 
    {
        positive_words.push_back(inputFromFile);
    }
    fin.close();
    return positive_words;
}

string find_first_word(string line)
{
    string word;
    int pos = line.find(' ');
    word = line.substr(0,pos);
    return word;
}

string find_date(string line)
{
    string word;
    int pos = line.find(' ');
    line = line.substr(pos+1);
    pos = line.find(' ');
    word = line.substr(0,pos);
    return word;
}

vector<int> string_to_number(string date)
{
    vector<int> intDate(3);
    vector<int> dateSize(3);
    vector<char> temp;
    char** charDate = (char**)calloc(3,sizeof(char*)); 
    int i=0 , j=-1 , k=0;
    copy(date.begin(),date.end(),back_inserter(temp));

    for (i=0 ; i < 3 ; i++)
    {
        for (j++ ; temp[j] != '/' && j<temp.size() ; j++);
        dateSize[i]=j;
    }
    dateSize[1]=dateSize[1]-dateSize[0]-1;
    dateSize[2]=dateSize[2]-dateSize[1]-dateSize[0]-2;

    for (i=0 , j=-1 ; i < 3 ; i++)
    {
        charDate[i]= (char*)calloc(dateSize[i],sizeof(char));
        for (j++ , k=0 ; k < dateSize[i] ; j++ , k++)
            charDate[i][k]=temp[j];
        intDate[i]=atoi(charDate[i]);
    }

    free(charDate);
    for (i=0 ; i<3 ; i++)
        free(charDate[i]);   
    return intDate;
}

vector<text> start_day(vector<text> myTexts , int numOfTexts , string line)
{
    string inputString;
    text temp;
    myTexts.push_back(temp);
    inputString = find_date(line);
    myTexts[numOfTexts-1].date = inputString;
    myTexts[numOfTexts-1].numOfPositiveWords = 0;
    myTexts[numOfTexts-1].intDate = string_to_number(myTexts[numOfTexts-1].date);
    return myTexts;
}

void show_day(vector<text> myTexts , int numOfTexts , string line)
{
    string inputString;
    inputString = find_date(line);
    for (int i = 0; i < numOfTexts; i++)
    {
        if (inputString == myTexts[i].date)
        {
            for (int j = 0; j < myTexts[i].textOfDay.size(); j++)
            {
                cout << myTexts[i].textOfDay[j];;
            }
            break;
        }
    }
}

int find_longest_day(vector<text> myTexts , int numOfTexts)
{
    int longestDay = 0;
    int maxLength = 0;

    for (int i = 0; i < numOfTexts; i++)
    {
        if (myTexts[i].textOfDay.size() >= maxLength)
        {
            maxLength = myTexts[i].textOfDay.size();
            longestDay = i;
        }
    }
    return longestDay;
}

void print_short_type(vector<text> myTexts , int index)
{
    cout << myTexts[index].date << endl;
    if (myTexts[index].textOfDay.size() <= 20)
    {
        for (int i = 0; i < myTexts[index].textOfDay.size(); i++)
        {
                    cout << myTexts[index].textOfDay[i];;
        }
    }
    else
    {
        for (int i = 0; i < 20; i++)
        {
            cout << myTexts[index].textOfDay[i];;
        }
        cout <<"...\n";
    }
}

vector<text> get_text(vector<text> myTexts , int numOfTexts , string inputString)
{
    string word = "";
    for (int i = 0 ; i < inputString.size() ; i++)   
    {
        if (inputString[i] == ' ')
        {
            myTexts[numOfTexts-1].words.push_back(word);
            word = "";
        }
        else 
        {
            word = word + inputString[i];
        }
    }
    myTexts[numOfTexts-1].words.push_back(word);
    
    copy(inputString.begin(),inputString.end(),back_inserter(myTexts[numOfTexts-1].textOfDay));
    myTexts[numOfTexts-1].textOfDay.push_back('\n');

    return myTexts;
}

vector<text> find_positive_words(vector<text> myTexts , int numOfTexts , vector<string> positive_words)
{
    for (int i = 0; i < numOfTexts ; i++)
    {
        myTexts[i].numOfPositiveWords = 0;
        for (int j = 0; j < myTexts[i].words.size() ; j++)
        {
            for (int k = 0; k < positive_words.size(); k++)
            {
                if (myTexts[i].words[j] == positive_words[k])
                {
                    myTexts[i].numOfPositiveWords = myTexts[i].numOfPositiveWords + 1;
                }
            }
        } 
    }
    return myTexts;
}

vector<int> find_best_days(vector<text> myTexts , int numOfTexts)
{
    vector<int> bestDays;
    int max = 0;

    for (int i = 0; i < numOfTexts ; i++)
        if (myTexts[i].numOfPositiveWords >= max)
            max = myTexts[i].numOfPositiveWords;
    
    for (int i = 0; i < numOfTexts ; i++)
        if (myTexts[i].numOfPositiveWords == max)
            bestDays.push_back(i);

    return bestDays;
}

int find_oldest_day(vector<text> myTexts , vector<int> days)
{
    int oldestDay = 0;
    int year = 3000;
    int month = 13;
    int day = 32;
    for (int i = 0; i < days.size() ; i++)
    {
        if ((myTexts[days[i]].intDate[2] < year) || 
            (myTexts[days[i]].intDate[2] ==year && myTexts[days[i]].intDate[1] < month) || 
            (myTexts[days[i]].intDate[2] ==year && myTexts[days[i]].intDate[1] ==month && myTexts[days[i]].intDate[0] <= day))
        {
            year = myTexts[days[i]].intDate[2];
            month = myTexts[days[i]].intDate[1];
            day = myTexts[days[i]].intDate[0];
            oldestDay = days[i];
        }
    }
    
    return oldestDay;
}



