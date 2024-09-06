#ifndef __MISSION__
#define __MISSION__

#include "manual.hpp"
#include "trip.hpp"

class Mission
{
protected:
    long long int start_time;
    long long int end_time;
    string id;
    int reward;
public:
    Mission(string id , long long int start , long long int end , int award);
    Mission(const Mission &m);
    string get_id();
    long long int get_start_time();
    virtual bool is_complete(long long int &count , long long int &end_timestamp , shared_ptr<Trip> trip) = 0;
    void print_mission(long long int end_timestamp, string status);
};

class TimeMission : public Mission
{
private:
    long long int minutes;
public:
    TimeMission(string id , long long int start , long long int end , long long int time , int award);
    TimeMission(const TimeMission &m);
    bool is_complete(long long int &count , long long int &end_timestamp , shared_ptr<Trip> trip);
};

class DistanceMission : public Mission
{
private:
    int distance;
public:
    DistanceMission(string id , long long int start , long long int end , int interval , int award);
    DistanceMission(const DistanceMission &m);
    bool is_complete(long long int &count , long long int &end_timestamp , shared_ptr<Trip> trip);
};

class CountMission : public Mission
{
private:
    int number_of_trip;
public:
    CountMission(string id , long long int start , long long int end , int num , int award);
    CountMission(const CountMission &m);
    bool is_complete(long long int &count , long long int &end_timestamp , shared_ptr<Trip> trip);
};

#endif