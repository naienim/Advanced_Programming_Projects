#include <../include/manual.hpp>
#include <../include/trip.hpp>
#include <../include/mission.hpp>
#include <../include/driver_mission.hpp>
#include <../include/driver.hpp>
#include <../include/program.hpp>

int main()
{
    DrivingProgram program;
    vector<string> inputs;
    string line;

    while (getline(cin, line))
    {
        inputs = program.make_apart(line,WORDS_SEPARATOR);
        if (inputs.size() == 0)
            continue;
        else if (inputs[0] == ADD_TIME_MISSION)
            program.add_mission<TimeMission>(inputs);
        else if (inputs[0] == ADD_DISTANCE_MISSION)
            program.add_mission<DistanceMission>(inputs);
        else if (inputs[0] == ADD_COUNT_MISSION)
            program.add_mission<CountMission>(inputs);
        else if (inputs[0] == ASSIGN_MISSSION)
            program.assign_mission(inputs);
        else if (inputs[0] == RECORD_RIDE)
            program.record_ride(inputs);
        else if (inputs[0] == SHOW_MISSSION_STATUS)
            program.show_missions_status(inputs);
        else
            continue;
    }

    return 0;
}