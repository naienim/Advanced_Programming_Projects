#ifndef __PLAYER__
#define __PLAYER__

#include "manual.hpp"
#include <cmath>

struct goals_taken_from
{
    int left;
    int mid;
    int right;
    int mds;
    int total;
};

class Player
{
private:
    int yellow_cards;
    int red_cards;
    float total_scores;
    int num_of_play;

protected:
    string name;
    string role;
    float score;
    float base_score;
    int goals;
    int price;
    int own_goals;
    int assist;
    int clean_sheets;
    roles_in_playground role_in_match;

public:
    Player(string _name, float _score, int _price);
    virtual shared_ptr<Player> make_copy() = 0;
    void change_score(float new_score);
    virtual void calculate_score(result _result, goals_taken_from goals_taken);
    string get_name();
    float get_score();
    float get_base_score();
    int get_average_score();
    string get_role();
    int get_goals();
    int get_price();
    int get_yellow_cards();
    void empty_yelloW_cards();
    void increase_yellow_cards();
    virtual void print_player_data() = 0;
    void update_player(float num);
    /* float round_number(float number); */
    void increase_num_of_element(string element);
    void set_role_in_match(roles_in_playground _role);
};

#endif