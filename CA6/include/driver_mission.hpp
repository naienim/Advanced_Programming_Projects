#ifndef __DRIVER_MISSION__
#define __DRIVER_MISSION__

#include "manual.hpp"
#include "trip.hpp"
#include "mission.hpp"

class DriverMission
{
private:
    shared_ptr<Mission> mission;
    long long int end_timestamp;
    long long int count;
    bool completed;
public:
    DriverMission(shared_ptr<Mission> input_mission);
    string get_id();
    long long int get_start_time();
    bool is_complete(shared_ptr<Trip> trip);
    void print_new_mission();
    void print_all_mission_details();
};

#endif