#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <set>

using namespace std;

const string JUNIOR = "junior";
const string EXPERT = "expert";
const string SENIOR = "senior";
const string TEAM_LEAD = "team_lead";
const string SALARY_CONFIGS = "salary_configs.csv";
const string WORKING_HOURS = "working_hours.csv";
const string EMPLOYEE = "employees.csv";
const string TEAMS = "teams.csv";
const char SEPARATOR = ',';
const char TIME_SEPARATOR = '-';
const char PERSON_SEPARATOR = '$';
const string INVALID_INPUT ="INVALID_INPUT";
const string EMPLOYEE_NOT_FOUND = "EMPLOYEE_NOT_FOUND";
const string TEAM_NOT_FOUND = "TEAM_NOT_FOUND";
const string INVALID_ARGUMENTS = "INVALID_ARGUMENTS";
const string INVALID_LEVEL = "INVALID_LEVEL";
const string INVALID_INTERVAL = "INVALID_INTERVAL";
const string NO_BONUS_TEAMS = "NO_BONUS_TEAMS";
const string OK = "OK";
const int NUM_OF_DAYS_PER_MONTH = 30;
const int NUM_OF_HOURS_PER_DAY = 24;
const int MAX_PERCENTAGE = 100;


class Team;

class Level
{
private:
    string level;
    int base_salary;
    int salary_per_hour; 
    int salary_per_extra_hour;
    int official_working_hours;
    int tax_percentage;
public:
    Level(string new_level , int base , int salary , int extra , int official , int tax);
    string get_level() { return level; };
    int get_tax() { return tax_percentage; };
    int find_salary(int total_hours);
    int find_total_earning(int salary , int bonus);
    void print_salary_configs();
    void change_parameters(string base , string per_hour , string extra_salary , string official_hours , string tax);
};

class Working_hours
{
private:
    int employee_id;
    int day;
    int start_time;
    int finish_time;
public:
    Working_hours(int new_id , int new_day , int start , int finish); 
    int get_day() { return day; };
    int get_employee_id() { return employee_id; };
    int get_start_time() { return start_time; };
    int get_finish_time() { return finish_time; };
    int get_working_hours() { return finish_time - start_time; };
    bool have_this_shift(int start , int end) { return (start >= start_time && end <= finish_time); };
    bool have_this_new_shift(int new_day , int start , int end);
    bool have_this_day(int id , int input_day) {return (employee_id == id && day == input_day); };
};

class Employee
{
private:
    int id;
    int age;
    string name;
    Team* my_team;
    Level* my_level;
    vector<Working_hours*> shifts;
public:
    Employee() {};
    int get_id() { return id; };
    int get_age() { return age; };
    string get_name() { return name; };
    Team* get_team() { return my_team; };
    Level* get_level() { return my_level; };
    vector<Working_hours*> get_shifts() { return shifts; };
    void set_personal_details(int new_id , string new_name , int new_age);
    void set_level(string level_name , vector<Level*> levels);
    void set_shifts(int id , vector<Working_hours*> shifts);
    void set_team(Team* new_team);
    void add_new_shift(Working_hours* new_shift) { shifts.push_back(new_shift); };
    int get_total_working_hours();
    int get_salary() { return my_level->find_salary(get_total_working_hours()); };
    int get_total_earning() { return my_level->find_total_earning(get_salary(),find_bonus()); };
    int find_bonus();
    int get_number_of_days();
};

class Team
{
private:
    int id;
    Employee* head_id;
    vector<Employee*> employees;
    int bonus_percentage;
    int bonus_min_working_hours;
    float bonus_working_hours_max_variance;
public:
    Team() {};
    int get_id() { return id; };
    Employee* get_head_id() { return head_id; };
    int get_bonus() { return bonus_percentage; };
    vector<Employee*> get_employees() { return employees; };
    void set_bonus(int bonus) { bonus_percentage = bonus; };
    int get_bonus_min_working_hours() { return bonus_min_working_hours; };
    float get_bonus_working_hours_max_variance() { return bonus_working_hours_max_variance; };
    bool is_suitable_for_bonus() { return (get_members_working_hours() > bonus_min_working_hours && find_variance() < bonus_working_hours_max_variance); };
    void set_team_details(int new_id , Employee* new_head_id , int min_bonus , float max_bonus);
    void set_employees(vector<Employee*> firm_employees , vector<string> persons);
    bool have_this_member(Employee* member);
    int get_members_working_hours();
    float find_variance();
    void sort_employees_by_id();
};

class Firm
{
private:
    vector<Employee*> employees;
    vector<Team*> teams;
    vector<Level*> levels;
    vector<Working_hours*> shifts;
public:
    Firm() {};
    string make_address(string folder_name , string file_name) { return ("./" + folder_name + "/" + file_name); };
    vector<string> make_apart(string line , char separator);
    void find_levels(string folder_name , string file_name);
    void find_shifts(string folder_name , string file_name);
    void find_employees(string folder_name , string file_name);
    Employee* find_person_by_id(int id);
    Team* find_team_by_id(int id);
    Level* find_level_by_name(string name);
    void find_teams(string folder_name , string file_name);
    void find_teams_for_employees();
    float round_number(float number);
    int find_hours_for_this_day(int day);
    vector<int> find_items(vector<float> numbers , string type , bool (*func)(float, float));
    int find_number_of_this_shift(int start_time , int end_time);
    void report_salaries();
    void report_employee_salary();
    void report_team_salary();
    void report_total_hours_per_day(); 
    void report_employee_per_hour();
    void show_salary_config();
    void update_salary_parameters();
    void add_working_hours();
    void delete_working_hours();
    void update_team_bonus();
    void find_teams_for_bonus();
};


bool is_greater(float x , float y) 
{ 
    return x >= y; 
}

bool is_lower(float x , float y) 
{ 
    return x <= y; 
}

Firm build_company(string folder_name)
{
    Firm company;
    company.find_levels(folder_name , SALARY_CONFIGS);
    company.find_shifts(folder_name , WORKING_HOURS);
    company.find_employees(folder_name , EMPLOYEE);
    company.find_teams(folder_name , TEAMS);
    company.find_teams_for_employees();
    return company;
}


Level::Level(string new_level , int base , int salary , int extra , int official , int tax)
{
    level = new_level;
    base_salary = base;
    salary_per_hour = salary;
    salary_per_extra_hour = extra;
    official_working_hours = official;
    tax_percentage = tax;
}

int Level::find_salary(int total_hours)
{  
    int sum = base_salary;
    if (total_hours <= official_working_hours)
    {
        sum += total_hours * salary_per_hour; 
    }
    else
    {
        sum += official_working_hours * salary_per_hour; 
        sum =+ (total_hours - official_working_hours) * salary_per_extra_hour;
    }
    return sum;
}

int Level::find_total_earning(int salary , int bonus)
{
    int sum = salary;
    sum += (salary*bonus)/100;
    sum -+ (sum*tax_percentage)/100;
    return sum;
}

void Level::print_salary_configs()
{
    cout << "Base Salary:" << base_salary << endl;
    cout << "Salary Per Hour:" << salary_per_hour << endl;
    cout << "Salary Per Extra Hour:" << salary_per_extra_hour << endl;
    cout << "Official Working Hours:" << official_working_hours  << endl;
    cout << "tax:" << tax_percentage << "%" << endl;
}

void Level::change_parameters(string base , string per_hour , string extra_salary , string official_hours , string tax)
{
    if (base != "-")
        base_salary = stoi(base);
    if (per_hour != "-")
        salary_per_hour = stoi(per_hour);
    if (extra_salary != "-")
        salary_per_extra_hour = stoi(extra_salary);
    if (official_hours != "-")
        official_working_hours = stoi(official_hours);
    if (tax != "-")
        tax_percentage = stoi(tax);
}
 

Working_hours::Working_hours(int new_id , int new_day , int start , int finish)
{
    employee_id = new_id;
    day = new_day;
    start_time = start;
    finish_time = finish;
}

bool Working_hours::have_this_new_shift(int new_day , int start , int end)
{
    if (day == new_day)
    {
        if (end <= start_time || start >= finish_time)
        {
            return false;
        }
        return true;
    }
    return false;
}


void Employee::set_personal_details(int new_id , string new_name , int new_age)
{
    id = new_id;
    age = new_age;
    name = new_name;
}

void Employee::set_level(string level_name , vector<Level*> levels)
{
    for (int i = 0; i < levels.size() ; i++)
    {
        if (level_name == levels[i]->get_level())
        {
            my_level = levels[i];
            return;
        }
    }
}

void Employee::set_shifts(int id , vector<Working_hours*> shifts_list)
{
    shifts.clear();
    for (int i = 0; i < shifts_list.size() ; i++)
    {
        if (id == shifts_list[i]->get_employee_id())
        {
            shifts.push_back(shifts_list[i]);
        }
    }
}

void Employee::set_team(Team* new_team)
{
    my_team = new_team;
}

int Employee::get_total_working_hours()
{
    int sum = 0;
    for (int i = 0; i < shifts.size() ; i++)
    {
        sum += shifts[i]->get_working_hours();
    }
    return sum;
}

int Employee::find_bonus()
{
    if (my_team == NULL)
    {
        return 0;
    }
    else
    {
        return my_team->get_bonus();
    }
}

int Employee::get_number_of_days()
{
    set<int> days;
    for (int i = 0; i < shifts.size(); i++)
    {
        days.insert(shifts[i]->get_day());
    }
    return days.size();
}


void Team::set_team_details(int new_id , Employee* new_head_id , int min_bonus , float max_bonus)
{
    id = new_id;
    bonus_percentage = 0;
    head_id = new_head_id;
    bonus_min_working_hours = min_bonus;
    bonus_working_hours_max_variance = max_bonus;
}

void Team::set_employees(vector<Employee*> firm_employees , vector<string> persons)
{
    for (int i = 0 ; i < persons.size() ; i++)
    {
        for (int j = 0; j < firm_employees.size() ; j++)
        {
            if (stoi(persons[i]) == firm_employees[j]->get_id())
            {
                employees.push_back(firm_employees[j]);
                break;
            }
        }
    }
}

bool Team::have_this_member(Employee* member)
{
    for (int i = 0; i < employees.size() ; i++)
    {
        if (member->get_id() == employees[i]->get_id())
        {
            return true;
        }
    }
    return false;
}

int Team::get_members_working_hours()
{
    int sum = 0;
    for (int i = 0; i < employees.size() ; i++)
    {
        sum += employees[i]->get_total_working_hours();
    }
    return sum;
}

float Team::find_variance()
{
    float variance = 0 , average = 0 , sum = 0;
    for (int i = 0; i < employees.size() ; i++)
        sum += employees[i]->get_total_working_hours();
    average = sum / employees.size();
    sum = 0;
    for (int i = 0; i < employees.size() ; i++)
        sum += (average - employees[i]->get_total_working_hours())*(average - employees[i]->get_total_working_hours());
    variance = sum / (employees.size() - 1);
    return variance;
}

void Team::sort_employees_by_id()
{
    Employee* temp;
    for (int i = 0; i < employees.size() ; i++)
        for (int j = i+1 ; j < employees.size() ; j++)
            if (employees[i]->get_id() > employees[j]->get_id())
            {
                temp = employees[i];
                employees[i] = employees[j];
                employees[j] = temp; 
            }  
}


vector<string> Firm::make_apart(string line_of_file , char separator)
{
    string file_element;
    vector<string> inputs;
    istringstream line(line_of_file);
    while (getline(line, file_element, separator)) 
    {
        inputs.push_back(file_element);
    }
    return inputs;
}

void Firm::find_levels(string folder_name , string file_name)
{
    vector<string> inputs;
    string address = make_address(folder_name,file_name);
    ifstream input_file(address);
    string line_of_file;
    getline(input_file, line_of_file);
    while (getline(input_file, line_of_file)) 
    {
        inputs = make_apart(line_of_file,SEPARATOR);
        Level *new_level = new Level(inputs[0],stoi(inputs[1]),stoi(inputs[2]),stoi(inputs[3]),stoi(inputs[4]),stoi(inputs[5]));
        levels.push_back(new_level);
    }
    input_file.close();
    return;
}

void Firm::find_shifts(string folder_name , string file_name)
{
    vector<string> inputs;
    vector<string> time;
    string address = make_address(folder_name,file_name);
    ifstream input_file(address);
    string line_of_file;
    getline(input_file, line_of_file);
    while (getline(input_file, line_of_file)) 
    {
        inputs = make_apart(line_of_file,SEPARATOR);
        time = make_apart(inputs[2],TIME_SEPARATOR);
        Working_hours *new_shift = new Working_hours(stoi(inputs[0]),stoi(inputs[1]),stoi(time[0]),stoi(time[1]));
        shifts.push_back(new_shift);
    }
    input_file.close();
    return;
}

void Firm::find_employees(string folder_name , string file_name)
{
    vector<string> inputs;
    string address = make_address(folder_name,file_name);
    ifstream input_file(address);
    string line_of_file;
    getline(input_file, line_of_file);
    while (getline(input_file, line_of_file)) 
    {
        inputs = make_apart(line_of_file,SEPARATOR);
        Employee *new_employee = new Employee();
        new_employee->set_personal_details(stoi(inputs[0]),inputs[1],stoi(inputs[2]));
        new_employee->set_level(inputs[3],levels);
        new_employee->set_shifts(stoi(inputs[0]),shifts);
        employees.push_back(new_employee);
    }
    input_file.close();
    return;
}

Employee* Firm::find_person_by_id(int id)
{
    for (int i = 0 ; i < employees.size() ; i++)
    {
        if (id == employees[i]->get_id())
        {
            return employees[i];
        }
    }
    return NULL;
}

Team* Firm::find_team_by_id(int id)
{
    for (int i = 0 ; i < teams.size() ; i++)
    {
        if (id == teams[i]->get_id())
        {
            return teams[i];
        }
    }
    return NULL;
}

Level* Firm::find_level_by_name(string name)
{
    for (int i = 0 ; i < levels.size() ; i++)
    {
        if (name == levels[i]->get_level())
        {
            return levels[i];
        }
    }
    return NULL;
}

void Firm::find_teams(string folder_name , string file_name)
{
    vector<string> inputs;
    vector<string> persons;
    string address = make_address(folder_name,file_name);
    ifstream input_file(address);
    string line_of_file;
    getline(input_file, line_of_file);
    while (getline(input_file, line_of_file)) 
    {
        inputs = make_apart(line_of_file,SEPARATOR);
        persons = make_apart(inputs[2],PERSON_SEPARATOR);
        Team *new_team = new Team();
        new_team->set_team_details(stoi(inputs[0]),find_person_by_id(stoi(inputs[1])),stoi(inputs[3]),stof(inputs[4]));
        new_team->set_employees(employees,persons);
        new_team->sort_employees_by_id();
        teams.push_back(new_team);
    }
    input_file.close();
    return;
}

void Firm::find_teams_for_employees()
{
    bool flag = true;
    for (int i = 0; i < employees.size() ; i++)
    {
        flag = true;
        for (int j = 0; j < teams.size() ; j++)
        {
            if (teams[j]->have_this_member(employees[i]))
            {
                flag = false;
                employees[i]->set_team(teams[j]);
                break;
            }
        }
        if (flag)
        {
            employees[i]->set_team(NULL);
        }
    }      
}

float Firm::round_number(float number)
{
    float value = (int)(number * 10 + 0.5);
    return (float)value / 10;
}

int Firm::find_hours_for_this_day(int day)
{
    int sum = 0;
    for (int i = 0; i < shifts.size() ; i++)
    {
        if (day == shifts[i]->get_day())
            sum += shifts[i]->get_working_hours();
    }
    return sum;
}

vector<int> Firm::find_items(vector<float> numbers , string type , bool (*func)(float,float) )
{
    float num = 0;
    vector<int> items;
    if (type == "min")
        num = 1000;
    for (int i = 0; i < numbers.size() ; i++)
    {
        if (func(numbers[i],num))
            num = numbers[i];
    }
    for (int i = 0; i < numbers.size() ; i++)
    {
        if (num == numbers[i])
        {
            items.push_back(i);
        } 
    }
    return items;
}

int Firm::find_number_of_this_shift(int start_time , int end_time)
{
    int sum = 0;
    for (int i = 0; i < shifts.size() ; i++)
    {
        if (shifts[i]->have_this_shift(start_time,end_time))
            sum++;
    }
    return sum;
}

void Firm::report_salaries()
{
    for (int i = 0 ; i < employees.size() ; i++)
    {
        cout << "ID: " << employees[i]->get_id() << endl;
        cout << "Name: " << employees[i]->get_name() << endl;
        cout << "Total Working Hours: " << employees[i]->get_total_working_hours() << endl;
        cout << "Total Earning: " << employees[i]->get_total_earning() << endl;
        cout << "---" << endl;
    } 
}

void Firm::report_employee_salary()
{
    int tax = 0;
    int bonus =0;
    int input_id = 0;
    cin >> input_id;
    Employee* person = find_person_by_id(input_id);
    if (person == NULL)
    {
        cout << EMPLOYEE_NOT_FOUND << endl;
        return;
    }
    cout << "ID: " << person->get_id() << endl;
    cout << "Name: " << person->get_name() << endl;
    cout << "Age: " << person->get_age() << endl;
    cout << "Level: " << person->get_level()->get_level() << endl;
    cout << "Team ID: ";
    if (person->get_team() == NULL)
        cout << "N/A" << endl;
    else
        cout << person->get_team()->get_id() << endl;
    cout << "Total Working Hours: " << person->get_total_working_hours() << endl;
    cout << "Absent Days: " << 30-person->get_number_of_days() << endl;
    cout << "Salary: " << person->get_salary() << endl;
    bonus = (person->find_bonus()*person->get_salary())/100;
    cout << "Bonus: " << bonus << endl;
    tax = (person->get_level()->get_tax()*(bonus + person->get_salary()))/100;
    cout << "Tax: " << tax << endl;
    cout << "Total Earning: " << person->get_total_earning() << endl;
}

void Firm::report_team_salary()
{
    int hours = 0;
    int input_id = 0;
    cin >> input_id;
    Team* group = find_team_by_id(input_id);
    if (group == NULL)
    {
        cout << TEAM_NOT_FOUND << endl;
        return;
    }
    cout << "ID: " << group->get_id() << endl;
    cout << "Head ID: " << group->get_head_id()->get_id() << endl;
    cout << "Head Name: " << group->get_head_id()->get_name() << endl;
    hours = group->get_members_working_hours();
    cout << "Team Total Working Hours: " << hours << endl;
    cout << "Average Member Working Hour: " << round_number((float)hours/group->get_employees().size()) << endl;
    cout << "Bonus: " << group->get_bonus() << endl << "---" << endl;
    for (int i = 0 ; i < group->get_employees().size() ; i++)
    {
        cout << "Member ID: " <<  group->get_employees()[i]->get_id() << endl;
        cout << "Total Earning: " <<  group->get_employees()[i]->get_total_earning() << endl << "---" << endl;
    }
}

void Firm::report_total_hours_per_day()
{
    int start_day = 100 , end_day = 100;
    vector<int> days , items;
    vector<float> sum_of_hour;
    cin >> start_day >> end_day;
    if (start_day < 1 || start_day > NUM_OF_DAYS_PER_MONTH || end_day < 1 || end_day > NUM_OF_DAYS_PER_MONTH || start_day > end_day)
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    } 
    for (int i = 0; i < end_day-start_day+1 ; i++)
        days.push_back(start_day+i);
    for (int i = 0; i < days.size() ; i++)
    {
        sum_of_hour.push_back(find_hours_for_this_day(days[i]));
        cout << "Day #" << days[i] << ": " << sum_of_hour[i] << endl;
    }
    cout << "---" << endl;
    cout << "Period(s) with Max Working Hours: ";
    items = find_items(sum_of_hour, "max" , &is_greater);
    for (int i = 0; i < items.size() ; i++)
        cout << days[items[i]] << " ";
    cout << endl;
    cout << "Period(s) with Min Working Hours: ";
    items = find_items(sum_of_hour, "min" , &is_lower);
    for (int i = 0; i < items.size() ; i++)
        cout << days[items[i]] << " ";
    cout << endl;
}

void Firm::report_employee_per_hour()
{
    int start_hour = 100 , end_hour = 100;
    vector<float> average_hour;
    vector<int> hours , items;
    float num = 0;
    cin >> start_hour >> end_hour;
    if (start_hour < 0 || start_hour > NUM_OF_HOURS_PER_DAY || end_hour < 0 || end_hour > NUM_OF_HOURS_PER_DAY || start_hour >= end_hour)
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    for (int i = 0; i < end_hour-start_hour ; i++)
        hours.push_back(start_hour+i);
    for (int i = 0; i < hours.size() ; i++)
    {
        num = (float)find_number_of_this_shift(hours[i],hours[i]+1);
        average_hour.push_back(round_number(num/NUM_OF_DAYS_PER_MONTH));
        cout << hours[i] << "-" << hours[i]+1 << ": " << average_hour[i] << endl;
    }
    cout << "---" << endl;
    cout << "Period(s) with Max Working Employees: ";
    items = find_items(average_hour, "max" , &is_greater);
    for (int i = 0; i < items.size() ; i++)
        cout << hours[items[i]] << "-" << hours[items[i]]+1 << " ";
    cout << endl;
    cout << "Period(s) with Min Working Employees: ";
    items = find_items(average_hour, "min" , &is_lower);
    for (int i = 0; i < items.size() ; i++)
        cout << hours[items[i]] << "-" << hours[items[i]]+1 << " ";
    cout << endl;
}

void Firm::show_salary_config()
{
    string input;
    cin >> input;
    Level* my_level = find_level_by_name(input);
    if (my_level == NULL)
    {
        cout << INVALID_LEVEL << endl;
        return;
    }
    my_level->print_salary_configs();
}

void Firm::update_salary_parameters()
{
    string input , base , salary_per_hour , extra_salary , official_hours , tax;
    cin >> input >> base >> salary_per_hour >> extra_salary >> official_hours >> tax;
    Level* new_level = find_level_by_name(input);
    if (new_level == NULL)
    {
        cout << INVALID_LEVEL << endl;
        return;
    }
    new_level->change_parameters(base,salary_per_hour,extra_salary,official_hours,tax);
    cout << OK << endl;
}

void Firm::add_working_hours()
{
    int input_id , day , start_time , end_time;
    cin >> input_id >> day >> start_time >> end_time;
    Employee* person = find_person_by_id(input_id);
    if (person == NULL)
    {
        cout << EMPLOYEE_NOT_FOUND << endl;
        return;
    }
    if (day < 1 || day > NUM_OF_DAYS_PER_MONTH || end_time < 0 || end_time > NUM_OF_HOURS_PER_DAY ||
        start_time < 0 || start_time > NUM_OF_HOURS_PER_DAY || start_time >= end_time)
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    for (int i = 0; i < person->get_shifts().size() ; i++)
    {
        if (person->get_shifts()[i]->have_this_new_shift(day,start_time,end_time))
        {
            cout << INVALID_INTERVAL << endl;
            return;
        }
    }
    Working_hours *new_shift = new Working_hours(input_id,day,start_time,end_time);
    shifts.push_back(new_shift); 
    person->add_new_shift(new_shift);
    cout << OK << endl;
}

void Firm::delete_working_hours()
{
    int input_id , day;
    cin >> input_id >> day;
    Employee* person = find_person_by_id(input_id);
    if (person == NULL)
    {
        cout << EMPLOYEE_NOT_FOUND << endl;
        return;
    }
    if (day < 1 || day > NUM_OF_DAYS_PER_MONTH)
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    for (int i = 0; i < shifts.size() ; i++)
    {
        if (shifts[i]->have_this_day(input_id,day))
        {
            shifts.erase(shifts.begin() + i);
        }
    }
    person->set_shifts(input_id,shifts);
    cout << OK << endl;
}

void Firm::update_team_bonus()
{
    int input_id = 0;
    int bonus = 0;
    cin >> input_id >> bonus;
    Team* group = find_team_by_id(input_id);
    if (group == NULL)
    {
        cout << TEAM_NOT_FOUND << endl;
        return;
    }
    if (bonus < 0 || bonus > MAX_PERCENTAGE)
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    group->set_bonus(bonus);
    cout << OK << endl;
}

void Firm::find_teams_for_bonus()
{
    vector<Team*> best_teams;
    Team* temp;
    for (int i = 0; i < teams.size() ; i++)
        if (teams[i]->is_suitable_for_bonus())
            best_teams.push_back(teams[i]);
    if (best_teams.size() == 0)
    {
        cout << NO_BONUS_TEAMS << endl; 
        return;
    }
    for (int i = 0; i < best_teams.size() ; i++)
        for (int j = i+1 ; j < best_teams.size() ; j++)
            if (best_teams[i]->get_members_working_hours() < best_teams[j]->get_members_working_hours())
            {
                temp = best_teams[i];
                best_teams[i] = best_teams[j];
                best_teams[j] = temp; 
            }  
    for (int i = 0; i < best_teams.size() ; i++)
        cout << "Team ID: " << best_teams[i]->get_id() << endl;
}



int main(int argc, char* argv[])
{
    string input;
    Firm company = build_company(argv[1]);

    while (cin >> input)
    {
        if (input == "report_salaries")
            company.report_salaries();
        else if (input == "report_employee_salary")
            company.report_employee_salary();
        else if (input == "report_team_salary")
            company.report_team_salary();
        else if (input == "report_total_hours_per_day")
            company.report_total_hours_per_day();
        else if (input == "report_employee_per_hour")
            company.report_employee_per_hour();
        else if (input == "show_salary_config")
            company.show_salary_config();
        else if (input == "update_salary_config")
            company.update_salary_parameters();
        else if (input == "add_working_hours")
            company.add_working_hours();
        else if (input == "delete_working_hours")
            company.delete_working_hours();
        else if (input == "update_team_bonus")
            company.update_team_bonus();
        else if (input == "find_teams_for_bonus")
            company.find_teams_for_bonus();
        else
            continue;
    }

    return 0;
}




