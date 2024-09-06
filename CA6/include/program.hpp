#ifndef __PROGRAM__
#define __PROGRAM__

#include "manual.hpp"
#include "mission.hpp"
#include "driver.hpp"

class DrivingProgram
{
private:
    vector<shared_ptr<Mission>> missions;
    vector<shared_ptr<Driver>> drivers;
public:
    DrivingProgram();
    vector<string> make_apart(string line_of_file , char separator);
    bool is_duplicated_mission_id(string id);
    bool is_coorect_to_add_mission(vector<string> inputs);
    shared_ptr<Mission> find_mission_by_id(string id);
    shared_ptr<Driver> find_driver_by_id(string id);
    template<typename T>
    void add_mission(vector<string> inputs);
    void assign_mission(vector<string> inputs);
    void record_ride(vector<string> inputs);
    void show_missions_status(vector<string> inputs);
};

template<typename T>
void DrivingProgram::add_mission(vector<string> inputs)
{
    if (!is_coorect_to_add_mission(inputs))
        return; 
    missions.push_back(make_shared<T>(inputs[1],str_to_num(inputs[2]),str_to_num(inputs[3]),str_to_num(inputs[4]),str_to_num(inputs[5])));
    cout << OK_MESSAGE << endl;
}

#endif