#include <../include/mission.hpp>

Mission::Mission(string id , long long int start , long long int end , int award) 
        : start_time(start), end_time(end), id(id), reward(award) {}

Mission::Mission(const Mission &m)
{
    id = m.id;
    start_time = m.start_time;
    end_time = m.end_time;
    reward = m.reward; 
}

string Mission::get_id()
{
    return id;
}

long long int Mission::get_start_time()
{
    return start_time;
}

void Mission::print_mission(long long int end_timestamp, string status)
{
    if (status == NEW_COMPLETE_MISSION)
        cout << "mission: " << id << endl;
    else if (status == ALL_MISSION)
        cout << "mission " << id << ":" << endl;
    cout << "start timestamp: " << start_time << endl;
    cout << "end timestamp: " << end_timestamp << endl;
    cout << "reward: " << reward << endl;
}

TimeMission::TimeMission(string id , long long int start , long long int end , long long int time , int award) 
            : Mission(id,start,end,award) , minutes(time) {}

TimeMission::TimeMission(const TimeMission &m)
            : Mission(m)
{
    minutes = m.minutes;
}

bool TimeMission::is_complete(long long int &count , long long int &end_timestamp , shared_ptr<Trip> trip) 
{
    if (trip->is_it_at_this_time(start_time,end_time))
    {
        count += trip->get_spending_time();
    }
    if (count >= minutes*60)
    {
        end_timestamp = trip->get_end_time();
        return true;
    }
    return false;
}

DistanceMission::DistanceMission(string id , long long int start , long long int end , int interval , int award) 
                : Mission(id,start,end,award) , distance(interval) {}

DistanceMission::DistanceMission(const DistanceMission &m)
            : Mission(m)
{
    distance = m.distance;
}

bool DistanceMission::is_complete(long long int &count , long long int &end_timestamp , shared_ptr<Trip> trip) 
{

    if (trip->is_it_at_this_time(start_time,end_time))
    {
        count += trip->get_distance();
    }
    if (count >= distance)
    {
        end_timestamp = trip->get_end_time();
        return true;
    }
    return false;
}

CountMission::CountMission(string id , long long int start , long long int end , int num , int award) 
            : Mission(id,start,end,award) , number_of_trip(num) {}

CountMission::CountMission(const CountMission &m)
            : Mission(m)
{
    number_of_trip = m.number_of_trip;
}

bool CountMission::is_complete(long long int &count , long long int &end_timestamp , shared_ptr<Trip> trip) 
{
    if (trip->is_it_at_this_time(start_time,end_time))
    {
        count++;
    }
    if (count >= number_of_trip)
    {
        end_timestamp = trip->get_end_time();
        return true;
    }
    return false;
}