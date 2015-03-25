#include <iostream>
#include <iomanip>
#include <vector>
#include <string>
using namespace std;

enum warrior_order { red, blue };
enum warrior_type { dragon, ninja, iceman, lion, wolf };
enum weapon { sword = 0, bomb = 1, arrow = 2 };

class Warrior;

class Warrior
{
private:
    int current_HP;
    int number;
};

class Dragon : public Warrior
{
    static int initial_HP;
    int weapon;
    double morale;
public:
    Dragon(double _morale, int _number)
    {
        morale = _morale;
        switch (_number % 3)
        {
            case 0:
                weapon = ::sword;
                break;
            case 1:
                weapon = ::bomb;
                break;
            case 2:
                weapon = ::arrow;
                break;
        }
    };
    void static set_initial_HP(int _HP)
    {
        initial_HP = _HP;
    }
    int static get_initial_HP()
    {
        return initial_HP;
    }
    string get_weapon()
    {
        switch (weapon)
        {
            case sword:
                return "sword";
                break;
            case bomb:
                return "bomb";
                break;
            case arrow:
                return "arrow";
                break;
            default:
                break;
        }
    }
    double get_morale()
    {
        return morale;
    }
};

class Ninja : public Warrior
{
    static int initial_HP;
    weapon first_weapon;
    weapon second_weapon;
public:
    Ninja(int _number)
    {
        switch (_number % 3)
        {
            case 0:
                first_weapon = sword;
                second_weapon = bomb;
                break;
            case 1:
                first_weapon = ::bomb;
                second_weapon = ::arrow;
                break;
            case 2:
                first_weapon = ::arrow;
                second_weapon = ::sword;
                break;
        }
    }
    void static set_initial_HP(int _HP)
    {
        initial_HP = _HP;
    }
    int static get_initial_HP()
    {
        return initial_HP;
    }
    string get_first_weapon()
    {
        switch (first_weapon)
        {
            case sword:
                return "sword";
                break;
            case bomb:
                return "bomb";
                break;
            case arrow:
                return "arrow";
                break;
            default:
                break;
        }
    }
    string get_second_weapon()
    {
        switch (second_weapon)
        {
            case sword:
                return "sword";
                break;
            case bomb:
                return "bomb";
                break;
            case arrow:
                return "arrow";
                break;
            default:
                break;
        }
    }
};

class Iceman : public Warrior
{
    static int initial_HP;
    int weapon;
public:
    Iceman(int _number)
    {
        switch (_number % 3)
        {
            case 0:
                weapon = ::sword;
                break;
            case 1:
                weapon = ::bomb;
                break;
            case 2:
                weapon = ::arrow;
                break;
        }
    };
    void static set_initial_HP(int _HP)
    {
        initial_HP = _HP;
    }
    int static get_initial_HP()
    {
        return initial_HP;
    }
    string get_weapon()
    {
        switch (weapon)
        {
            case sword:
                return "sword";
                break;
            case bomb:
                return "bomb";
                break;
            case arrow:
                return "arrow";
                break;
            default:
                break;
        }
    }
};

class Lion : public Warrior
{
    static int initial_HP;
    int loyalty;
public:
    Lion(int _loyalty){ loyalty = _loyalty; };
    void static set_initial_HP(int _HP)
    {
        initial_HP = _HP;
    }
    int static get_initial_HP()
    {
        return initial_HP;
    }
    int get_loyalty()
    {
        return loyalty;
    }
};

class Wolf : public Warrior
{
    static int initial_HP;
public:
    void static set_initial_HP(int _HP)
    {
        initial_HP = _HP;
    }
    int static get_initial_HP()
    {
        return initial_HP;
    }
};

class HeadQuarter
{
private:
    int HP;
    int next_number_of_warrior;
    int actual_number_of_warrior;

    int dragon_count;
    int ninja_count;
    int iceman_count;
    int lion_count;
    int wolf_count;
public:
    HeadQuarter(int _HP) :HP(_HP)
    {
        next_number_of_warrior = 0;
        actual_number_of_warrior = 0;
        dragon_count = 0;
        ninja_count = 0;
        iceman_count = 0;
        lion_count = 0;
        wolf_count = 0;
    }
    void produce_next_warrior(warrior_order order);

    bool can_produce_next_warrior();

    void update_numbers(warrior_order order);
};

int main()
{
    int case_num;
    cin >> case_num;
    for (int i = 0; i < case_num; i++)
    {
        cout << "Case:" << (i + 1) << endl;

        int headquarter_HP;
        cin >> headquarter_HP;
        HeadQuarter red(headquarter_HP), blue(headquarter_HP);

        int dragon_HP, ninja_HP, iceman_HP, lion_HP, wolf_HP;
        cin >> dragon_HP >> ninja_HP >> iceman_HP >> lion_HP >> wolf_HP;
        Dragon::set_initial_HP(dragon_HP);
        Ninja::set_initial_HP(ninja_HP);
        Iceman::set_initial_HP(iceman_HP);
        Lion::set_initial_HP(lion_HP);
        Wolf::set_initial_HP(wolf_HP);

        int time = 0;
        bool red_produce = true;
        bool blue_produce = true;
        while (true)
        {
            if (!red_produce && !blue_produce)
                break;
            if (red.can_produce_next_warrior())
            {
                warrior_order order = ::red;
                red.update_numbers(order);
                cout << setfill('0') << setw(3) << time << setfill(' ');
                red.produce_next_warrior(order);
            }
            else
            {
                if (red_produce)
                {
                    cout << setfill('0') << setw(3) << time << setfill(' ');
                    cout << " red headquarter stops making warriors" << endl;
                    red_produce = false;
                }
            }
            if (blue.can_produce_next_warrior())
            {
                warrior_order order = ::blue;
                blue.update_numbers(order);
                cout << setfill('0') << setw(3) << time << setfill(' ');
                blue.produce_next_warrior(order);
            }
            else
            {
                if (blue_produce)
                {
                    cout << setfill('0') << setw(3) << time << setfill(' ');
                    cout << " blue headquarter stops making warriors" << endl;
                    blue_produce = false;
                }
            }
            time++;
        }
    }
    return 0;
}

void HeadQuarter::produce_next_warrior(warrior_order order)
{
    switch (order)
    {
        case red:
            switch (actual_number_of_warrior % 5)
            {
                case 1:
                {
                    Iceman iceman(next_number_of_warrior);
                    HP -= Iceman::get_initial_HP();
                    iceman_count++;
                    cout << " red iceman " << next_number_of_warrior << " born with strength "
                            << Iceman::get_initial_HP() << "," << iceman_count << " iceman in red headquarter" << endl;
                    cout << "It has a " << iceman.get_weapon() << endl;
                    break;
                }
                case 2:
                {
                    Lion lion(HP - Lion::get_initial_HP());
                    HP -= Lion::get_initial_HP();
                    lion_count++;
                    cout << " red lion " << next_number_of_warrior << " born with strength "
                            << Lion::get_initial_HP() << "," << lion_count << " lion in red headquarter" << endl;
                    cout << "It's loyalty is " << lion.get_loyalty() << endl;
                    break;
                }
                case 3:
                {
                    Wolf wolf;
                    HP -= Wolf::get_initial_HP();
                    wolf_count++;
                    cout << " red wolf " << next_number_of_warrior << " born with strength "
                            << Wolf::get_initial_HP() << "," << wolf_count << " wolf in red headquarter" << endl;
                    break;
                }
                case 4:
                {
                    Ninja ninja(next_number_of_warrior);
                    HP -= Ninja::get_initial_HP();
                    ninja_count++;
                    cout << " red ninja " << next_number_of_warrior << " born with strength "
                            << Ninja::get_initial_HP() << "," << ninja_count << " ninja in red headquarter" << endl;
                    cout << "It has a " << ninja.get_first_weapon() << " and a " << ninja.get_second_weapon() << endl;
                    break;
                }
                case 0:
                {
                    Dragon dragon((double)(HP - Dragon::get_initial_HP()) / Dragon::get_initial_HP(), next_number_of_warrior);
                    HP -= Dragon::get_initial_HP();
                    dragon_count++;
                    cout << " red dragon " << next_number_of_warrior << " born with strength "
                            << Dragon::get_initial_HP() << "," << dragon_count << " dragon in red headquarter" << endl;
                    cout << "It has a " << dragon.get_weapon() << ",and it's morale is "
                            << setiosflags(ios::fixed) << setprecision(2) << dragon.get_morale() << endl;
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
        case blue:
            switch (actual_number_of_warrior % 5)
            {
                case 1:
                {
                    Lion lion(HP - Lion::get_initial_HP());
                    HP -= Lion::get_initial_HP();
                    lion_count++;
                    cout << " blue lion " << next_number_of_warrior << " born with strength "
                            << Lion::get_initial_HP() << "," << lion_count << " lion in blue headquarter" << endl;
                    cout << "It's loyalty is " << lion.get_loyalty() << endl;
                    break;
                }
                case 2:
                {
                    Dragon dragon((double)(HP - Dragon::get_initial_HP()) / Dragon::get_initial_HP(), next_number_of_warrior);
                    HP -= Dragon::get_initial_HP();
                    dragon_count++;
                    cout << " blue dragon " << next_number_of_warrior << " born with strength "
                            << Dragon::get_initial_HP() << "," << dragon_count << " dragon in blue headquarter" << endl;
                    cout << "It has a " << dragon.get_weapon() << ",and it's morale is "
                            << setiosflags(ios::fixed) << setprecision(2) << dragon.get_morale() << endl;
                    break;
                }
                case 3:
                {
                    Ninja ninja(next_number_of_warrior);
                    HP -= Ninja::get_initial_HP();
                    ninja_count++;
                    cout << " blue ninja " << next_number_of_warrior << " born with strength "
                            << Ninja::get_initial_HP() << "," << ninja_count << " ninja in blue headquarter" << endl;
                    cout << "It has a " << ninja.get_first_weapon() << " and a " << ninja.get_second_weapon() << endl;
                    break;
                }
                case 4:
                {
                    Iceman iceman(next_number_of_warrior);
                    HP -= Iceman::get_initial_HP();
                    iceman_count++;
                    cout << " blue iceman " << next_number_of_warrior << " born with strength "
                            << Iceman::get_initial_HP() << "," << iceman_count << " iceman in blue headquarter" << endl;
                    cout << "It has a " << iceman.get_weapon() << endl;
                    break;
                }
                case 0:
                {
                    Wolf wolf;
                    HP -= Wolf::get_initial_HP();
                    wolf_count++;
                    cout << " blue wolf " << next_number_of_warrior << " born with strength "
                            << Wolf::get_initial_HP() << "," << wolf_count << " wolf in blue headquarter" << endl;
                    break;
                }
                default:
                {
                    break;
                }
            }
            break;
    }
}

bool HeadQuarter::can_produce_next_warrior()
{
    if (HP >= Dragon::get_initial_HP())
        return true;
    if (HP >= Ninja::get_initial_HP())
        return true;
    if (HP >= Iceman::get_initial_HP())
        return true;
    if (HP >= Lion::get_initial_HP())
        return true;
    if (HP >= Wolf::get_initial_HP())
        return true;
    return false;
}

void HeadQuarter::update_numbers(warrior_order order)

{
    if (!can_produce_next_warrior())
        return;
    next_number_of_warrior++;
    switch (order)
    {
        case red:
            switch (actual_number_of_warrior % 5)
            {
                case 1:
                    if (Lion::get_initial_HP() <= HP)
                        actual_number_of_warrior++;
                    else if (Wolf::get_initial_HP() <= HP)
                        actual_number_of_warrior += 2;
                    else if (Ninja::get_initial_HP() <= HP)
                        actual_number_of_warrior += 3;
                    else if (Dragon::get_initial_HP() <= HP)
                        actual_number_of_warrior += 4;
                    else
                        actual_number_of_warrior += 5;
                    break;
                case 2:
                    if (Wolf::get_initial_HP() <= HP)
                        actual_number_of_warrior++;
                    else if (Ninja::get_initial_HP() <= HP)
                        actual_number_of_warrior += 2;
                    else if (Dragon::get_initial_HP() <= HP)
                        actual_number_of_warrior += 3;
                    else if (Iceman::get_initial_HP() <= HP)
                        actual_number_of_warrior += 4;
                    else
                        actual_number_of_warrior += 5;
                    break;
                case 3:
                    if (Ninja::get_initial_HP() <= HP)
                        actual_number_of_warrior++;
                    else if (Dragon::get_initial_HP() <= HP)
                        actual_number_of_warrior += 2;
                    else if (Iceman::get_initial_HP() <= HP)
                        actual_number_of_warrior += 3;
                    else if (Lion::get_initial_HP() <= HP)
                        actual_number_of_warrior += 4;
                    else
                        actual_number_of_warrior += 5;
                    break;
                case 4:
                    if (Dragon::get_initial_HP() <= HP)
                        actual_number_of_warrior++;
                    else if (Iceman::get_initial_HP() <= HP)
                        actual_number_of_warrior += 2;
                    else if (Lion::get_initial_HP() <= HP)
                        actual_number_of_warrior += 3;
                    else if (Wolf::get_initial_HP() <= HP)
                        actual_number_of_warrior += 4;
                    else
                        actual_number_of_warrior += 5;
                    break;
                case 0:
                    if (Iceman::get_initial_HP() <= HP)
                        actual_number_of_warrior++;
                    else if (Lion::get_initial_HP() <= HP)
                        actual_number_of_warrior += 2;
                    else if (Wolf::get_initial_HP() <= HP)
                        actual_number_of_warrior += 3;
                    else if (Ninja::get_initial_HP() <= HP)
                        actual_number_of_warrior += 4;
                    else
                        actual_number_of_warrior += 5;
                    break;
                default:
                    break;
            }
            break;
        case blue:
            switch (actual_number_of_warrior % 5)
            {
                case 1:
                    if (Dragon::get_initial_HP() <= HP)
                        actual_number_of_warrior++;
                    else if (Ninja::get_initial_HP() <= HP)
                        actual_number_of_warrior += 2;
                    else if (Iceman::get_initial_HP() <= HP)
                        actual_number_of_warrior += 3;
                    else if (Wolf::get_initial_HP() <= HP)
                        actual_number_of_warrior += 4;
                    else
                        actual_number_of_warrior += 5;
                    break;
                case 2:
                    if (Ninja::get_initial_HP() <= HP)
                        actual_number_of_warrior++;
                    else if (Iceman::get_initial_HP() <= HP)
                        actual_number_of_warrior += 2;
                    else if (Wolf::get_initial_HP() <= HP)
                        actual_number_of_warrior += 3;
                    else if (Lion::get_initial_HP() <= HP)
                        actual_number_of_warrior += 4;
                    else
                        actual_number_of_warrior += 5;
                    break;
                case 3:
                    if (Iceman::get_initial_HP() <= HP)
                        actual_number_of_warrior++;
                    else if (Wolf::get_initial_HP() <= HP)
                        actual_number_of_warrior += 2;
                    else if (Lion::get_initial_HP() <= HP)
                        actual_number_of_warrior += 3;
                    else if (Dragon::get_initial_HP() <= HP)
                        actual_number_of_warrior += 4;
                    else
                        actual_number_of_warrior += 5;
                    break;
                case 4:
                    if (Wolf::get_initial_HP() <= HP)
                        actual_number_of_warrior++;
                    else if (Lion::get_initial_HP() <= HP)
                        actual_number_of_warrior += 2;
                    else if (Dragon::get_initial_HP() <= HP)
                        actual_number_of_warrior += 3;
                    else if (Ninja::get_initial_HP() <= HP)
                        actual_number_of_warrior += 4;
                    else
                        actual_number_of_warrior += 5;
                    break;
                case 0:
                    if (Lion::get_initial_HP() <= HP)
                        actual_number_of_warrior++;
                    else if (Dragon::get_initial_HP() <= HP)
                        actual_number_of_warrior += 2;
                    else if (Ninja::get_initial_HP() <= HP)
                        actual_number_of_warrior += 3;
                    else if (Iceman::get_initial_HP() <= HP)
                        actual_number_of_warrior += 4;
                    else
                        actual_number_of_warrior += 5;
                    break;
                default:
                    break;
            }
    }
}

int Dragon::initial_HP = 0;
int Ninja::initial_HP = 0;
int Iceman::initial_HP = 0;
int Lion::initial_HP = 0;
int Wolf::initial_HP = 0;