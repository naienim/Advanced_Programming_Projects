#include <../include/trip.hpp>

Trip::Trip(long long int start , long long int end , string id , int interval) 
    : start_time(start), end_time(end), driver_id(id), distance(interval) {}

bool Trip::is_it_at_this_time(long long int start , long long int end)
{
    return start_time >= start && end_time <= end;
}

long long int Trip::get_spending_time()
{
    return end_time - start_time;
}

long long int Trip::get_end_time()
{
    return end_time;
}

int Trip::get_distance()
{
    return distance;
}
