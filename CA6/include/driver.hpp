#ifndef __DRIVER__
#define __DRIVER__

#include "manual.hpp"
#include "trip.hpp"
#include "mission.hpp"
#include "driver_mission.hpp"

long long int str_to_num(string input);

class Driver
{
private:
    string id;
    vector<shared_ptr<DriverMission>> missions;
    vector<shared_ptr<Trip>> trips;
public:
    Driver(string _id);
    string get_id();
    bool have_this_mission(string mission_id);
    void sort_missions();
    void add_mission(shared_ptr<Mission> new_mission);
    void add_trip(vector<string> inputs);
    void print_new_complete_missions(shared_ptr<Trip> trip);
    void print_missions();
};

#endif