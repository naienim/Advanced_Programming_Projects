#include <../include/driver_mission.hpp>

DriverMission::DriverMission(shared_ptr<Mission> input_mission)
{
    mission = input_mission;
    end_timestamp = -1;
    count = 0;
    completed = false;
}

string DriverMission::get_id()
{
    return mission->get_id();
}

long long int DriverMission::get_start_time()
{
    return mission->get_start_time();
}

bool DriverMission::is_complete(shared_ptr<Trip> trip)
{
    if (!completed)
    {
        if (mission->is_complete(count,end_timestamp,trip))
        {
            completed = true;
            return true;
        }
    }
    return false;
}

void DriverMission::print_new_mission()
{
    mission->print_mission(end_timestamp,NEW_COMPLETE_MISSION);
}

void DriverMission::print_all_mission_details()
{
    mission->print_mission(end_timestamp,ALL_MISSION);
    cout << "status: ";
    if (completed)
        cout << COMPLETED_MISSION << endl;
    else 
        cout << ONGOING_MISSION << endl;
}


