#include <../include/program.hpp>

DrivingProgram::DrivingProgram() 
{
    missions.clear();
    drivers.clear();
}

vector<string> DrivingProgram::make_apart(string line_of_file , char separator)
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

bool DrivingProgram::is_duplicated_mission_id(string id)
{
    for (int i = 0; i < missions.size(); i++)
    {
        if (missions[i]->get_id() == id)
        {
            return true;
        }
    }
    return false;
}

bool DrivingProgram::is_coorect_to_add_mission(vector<string> inputs)
{
    if (inputs.size() < NUM_OF_ADD_MISSION_ARGUMENTS)
    {
        cout << INVALID_ARGUMENTS << endl;
        return false;
    }
    else if (is_duplicated_mission_id(inputs[1]))
    {   cout << DUPLICATE_MISSION_ID << endl;
        return false;
    }
    else if (str_to_num(inputs[2]) > str_to_num(inputs[3]) || str_to_num(inputs[4]) < 0 || str_to_num(inputs[5]) < 0)
    {
        cout << INVALID_ARGUMENTS << endl;
        return false;
    }
    return true;
}

shared_ptr<Mission> DrivingProgram::find_mission_by_id(string id)
{
    for (int i = 0; i < missions.size(); i++)
    {
        if (missions[i]->get_id() == id)
        {
            return missions[i];
        }    
    }
    return NULL;
}

shared_ptr<Driver> DrivingProgram::find_driver_by_id(string id)
{
    for (int i = 0; i < drivers.size(); i++)
    {
        if (drivers[i]->get_id() == id)
        {
            return drivers[i];
        }    
    }
    return NULL;
}

void DrivingProgram::assign_mission(vector<string> inputs)
{
    if (inputs.size() < NUM_OF_ASSIGN_ARGUMENTS)
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    shared_ptr<Mission> new_mission = find_mission_by_id(inputs[1]);
    shared_ptr<Driver> new_driver =find_driver_by_id(inputs[2]);
    if (new_mission == NULL)
    {
        cout << MISSION_NOT_FOUND << endl;
        return;
    }
    if (new_driver == NULL)
    {
        new_driver = make_shared<Driver>(inputs[2]);
        drivers.push_back(new_driver);
    }
    new_driver->add_mission(new_mission);
}

void DrivingProgram::record_ride(vector<string> inputs)
{
    if (inputs.size() < NUM_OF_RECORD_RIDE_ARGUMENTS)
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    else if (str_to_num(inputs[1]) > str_to_num(inputs[2]) || str_to_num(inputs[4]) < 0)
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    shared_ptr<Driver> new_driver =find_driver_by_id(inputs[3]);
    shared_ptr<Trip> trip = make_shared<Trip>(str_to_num(inputs[1]),str_to_num(inputs[2]),inputs[3],str_to_num(inputs[4]));
    if (new_driver == NULL) return;
    new_driver->add_trip(inputs);
    new_driver->print_new_complete_missions(trip);
}

void DrivingProgram::show_missions_status(vector<string> inputs)
{
    if (inputs.size() < NUM_OF_SHOW_MISSSION_STATUS_ARGUMENTS)
    {
        cout << INVALID_ARGUMENTS << endl;
        return;
    }
    shared_ptr<Driver> new_driver =find_driver_by_id(inputs[1]);
    if (new_driver == NULL) return;
    new_driver->print_missions();
}



