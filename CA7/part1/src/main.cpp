#include "../include/manual.hpp"
#include "../include/player.hpp"
#include "../include/team.hpp"
#include "../include/match.hpp"
#include "../include/week.hpp"
#include "../include/person.hpp"
#include "../include/football_fantasy.hpp"

void input(FootballFantasy &program)
{
    string line;
    vector<string> inputs;
    while (getline(cin, line))
    {
        try
        {
            inputs = make_apart(line, COMMAND_SEPARATOR);
            if (inputs.size() == 0)
                continue;
            else if (inputs[0] == commands[POST])
                program.handle_post_commands(inputs);
            else if (inputs[0] == commands[GET])
                program.handle_get_commands(inputs);
            else if (inputs[0] == commands[PUT])
                program.handle_put_commands(inputs);
            else if (inputs[0] == commands[DELETE])
                program.handle_delete_commands(inputs);
            else
                throw Bad_Request();
        }
        catch (Error const &e)
        {
            e.print_err();
        }
    }
}

int main()
{
    FootballFantasy program;

    program.get_teams_from_file(FOLDER_NAME_DATA, FILE_NAME_LEAGUE);
    program.get_weeks_from_file(FOLDER_NAME_DATA, FILE_NAME_WEEkS, NUMBER_OF_WEEKS);
    
    input(program);

    return 0;
}
