#ifndef __TRIP__
#define __TRIP__

#include "manual.hpp"

class Trip
{
private:
    long long int start_time;
    long long int end_time;
    string driver_id;
    int distance;
public:
    Trip(long long int start , long long int end , string id , int interval);
    bool is_it_at_this_time(long long int start , long long int end);
    long long int get_spending_time();
    long long int get_end_time();
    int get_distance();
};

#endif