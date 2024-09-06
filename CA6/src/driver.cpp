#include <../include/driver.hpp>

long long int str_to_num(string input)
{
    long long int number = 0;
    for (int i = 0; i < input.length() ; i++)
    {
        if (input[i] >= '0' && input[i] <= '9')
        {
            number = number + input[i] - '0';
            number = number*10; 
        }
    }
    if (input[0] == '-')
        return -(number/10);
    return number/10;
}
 
Driver::Driver(string _id) : id(_id) 
{
    missions.clear();
    trips.clear();
}

string Driver::get_id()
{
    return id;
}

bool Driver::have_this_mission(string mission_id)
{
    for (int i = 0; i < missions.size(); i++)
    {
        if (missions[i]->get_id() == mission_id)
        {
            return true;
        }
    }
    return false;
}

void Driver::sort_missions()
{
    shared_ptr<DriverMission> temp;
    for (int i = 0; i < missions.size()-1; i++)
    {
        for (int j = i+1; j < missions.size(); j++)
        {
            if(missions[i]->get_start_time() > missions[j]->get_start_time())
            {
                temp = missions[i];
                missions[i] = missions[j];
                missions[j] = temp;
            }
        }
    }
}

void Driver::add_mission(shared_ptr<Mission> new_mission)
{
    if (have_this_mission(new_mission->get_id()))
    {
        cout << DUPLICATE_DRIVER_MISSION << endl;
        return;
    }
    missions.push_back(make_shared<DriverMission>(new_mission));
    sort_missions();
    cout << OK_MESSAGE << endl;
}

void Driver::add_trip(vector<string> inputs)
{
   trips.push_back(make_shared<Trip>(str_to_num(inputs[1]),str_to_num(inputs[2]),inputs[3],str_to_num(inputs[4])));
}

void Driver::print_new_complete_missions(shared_ptr<Trip> trip)
{
    bool flag = false;
    cout << "completed missions for driver " << id  << ":" << endl;
    for (int i = 0; i < missions.size(); i++)
    {
        if (missions[i]->is_complete(trip))
        {
            if (flag) cout << endl;
            flag = true;
            missions[i]->print_new_mission();
        }
    }
}

void Driver::print_missions()
{
    bool flag = false;
    cout << "missions status for driver " << id << ":" << endl;
    if (missions.size() == 0)
    {
        cout << DRIVER_MISSION_NOT_FOUND << endl;
        return;
    }
    for (int i = 0; i < missions.size(); i++)
    {
        if (flag) cout << endl;
        flag = true;
        missions[i]->print_all_mission_details();
    }
}
