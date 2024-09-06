#ifndef __MANUAL__
#define __MANUAL__

#include <iterator>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <numeric>
#include <algorithm>
#include <utility>
#include <memory>
#include <set>

using namespace std;

const int NUM_OF_ADD_MISSION_ARGUMENTS = 6;
const int NUM_OF_ASSIGN_ARGUMENTS = 3;
const int NUM_OF_RECORD_RIDE_ARGUMENTS = 5;
const int NUM_OF_SHOW_MISSSION_STATUS_ARGUMENTS = 2;

const string DUPLICATE_MISSION_ID = "DUPLICATE_MISSION_ID";
const string DUPLICATE_DRIVER_MISSION = "DUPLICATE_DRIVER_MISSION";
const string INVALID_ARGUMENTS = "INVALID_ARGUMENTS";
const string MISSION_NOT_FOUND = "MISSION_NOT_FOUND";
const string DRIVER_MISSION_NOT_FOUND = "DRIVER_MISSION_NOT_FOUND";
const string OK_MESSAGE = "OK";
const string COMPLETED_MISSION = "completed";
const string ONGOING_MISSION = "ongoing";
const string NEW_COMPLETE_MISSION = "new_complete_mission";
const string ALL_MISSION = "all_mission";

const char WORDS_SEPARATOR = ' ';
const string ADD_TIME_MISSION = "add_time_mission";
const string ADD_DISTANCE_MISSION = "add_distance_mission";
const string ADD_COUNT_MISSION = "add_count_mission";
const string ASSIGN_MISSSION = "assign_mission";
const string RECORD_RIDE = "record_ride";
const string SHOW_MISSSION_STATUS = "show_missions_status";

#endif