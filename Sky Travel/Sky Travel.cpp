#include <iostream>
#include <vector>
#include <cstdlib>
#include "csv.h"

using namespace std;

enum class GameState { gs_Menu = 0, gs_Selection, gs_Travel, gs_Town, gs_Shopping, gs_Quit };
enum class Gender { Male = 0, Female };
enum class Skill { None = 0, Pilot, Mechanic, Diplomat };
enum class Location { Lotan = 0, Arvand, Nimoy, Patok, Braetar, Cafta, Riv, Rupta };

std::ostream& operator<<(std::ostream& os, const Gender data) {
    os << static_cast<int>(data);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Skill data) {
    os << static_cast<int>(data);
    return os;
}

std::ostream& operator<<(std::ostream& os, const Location data) {
    os << static_cast<int>(data);
    return os;
}

Location CurrentLocation = Location::Lotan;

int CrewSize = 1;

int rollDie()
{
    int roll;
    int min = 1;
    int max = 20;

    roll = rand() % (max - min + 1) + min;

    return roll;
}

class Character
{
protected:
    string m_Name;
    Gender m_Gender;
    Skill m_Skill;
    int m_Influence;
    Location m_CharacterLocation;
    bool inCrew;
    int m_Currency;
    
public:
    Character(string t_Name, Gender t_Gender, Skill t_Skill, int t_Influence, Location t_CharacterLocation)
    {
        m_Name = t_Name;
        m_Gender = t_Gender;
        m_Skill = t_Skill;
        m_Influence = t_Influence;
        m_CharacterLocation = t_CharacterLocation;
        inCrew = false;
    }
    
    string getName()
    {
        return m_Name;
    }
    Gender getGender()
    {
        return m_Gender;
    }
    Skill getSkill()
    {
        return m_Skill;
    }
    int getInfluence()
    {
        return m_Influence;
    }
    Location getCharacterLocation()
    {
        return m_CharacterLocation;
    }
    bool isInCrew()
    {
        return inCrew;
    }
    int getCurrency()
    {
        return m_Currency;
    }
    void printName()
    {
        cout << m_Name << endl;
    }
};

vector <Character> LotanCharacters = {};
vector <Character> ArvandCharacters = {};
vector <Character> NimoyCharacters = {};
vector <Character> PatokCharacters = {};
vector <Character> BraetarCharacters = {};
vector <Character> CaftaCharacters = {};
vector <Character> RivCharacters = {};
vector <Character> RuptaCharacters = {};
vector <Character> Crew = {};

class Ships
{
protected:
    string m_ShipName;
    int m_ShipSpeed;
    int m_CargoSpace;
    int m_CabinSpace;
    int m_CrewRequired;
    int m_ShipCost;
    int m_Fuel;

public:

};

class Quests
{
protected:
    string m_QuestName;
    Location m_QuestOrigin;
    Location m_QuestDestination;
    int m_GoodsRequired;
    int m_PassengersRequired;
    int m_Reward;
    bool isLegal;
    bool haveStarted;
    bool isComplete;

public:
    Quests(string t_QuestName, Location t_QuestOrigin, Location t_QuestDestination, int t_GoodsRequired, int t_PassengersRequired,
           int t_Reward, bool t_isLegal)
    {
        m_QuestName = t_QuestName;
        m_QuestOrigin = t_QuestOrigin;
        m_QuestDestination = t_QuestDestination;
        m_GoodsRequired = t_GoodsRequired;
        m_PassengersRequired = t_PassengersRequired;
        m_Reward = t_Reward;
        isLegal = t_isLegal;
        haveStarted = false;
        isComplete = false;
    }

};

vector <Quests> LotanQuests = {};
vector <Quests> ArvandQuests = {};
vector <Quests> NimoyQuests = {};
vector <Quests> PatokQuests = {};
vector <Quests> BraetarQuests = {};
vector <Quests> CaftaQuests = {};
vector <Quests> RivQuests = {};
vector <Quests> RuptaQuests = {};

class StateEngine
{
protected:
    GameState m_GameState;

public:        
    GameState getCurrentState()
    {
        return m_GameState;
    }
    void changeState(GameState newState, StateEngine Game)
    {
        m_GameState = newState;

        switch (m_GameState)
        {
        case GameState::gs_Menu:
            gs_Menu(Game);
            break;

        case GameState::gs_Selection:
            gs_Selection(Game);
            break;

        case GameState::gs_Travel:
            gs_Travel(Game);
            break;

        case GameState::gs_Town:
            gs_Town(Game);
            break;

        case GameState::gs_Shopping:
            gs_Shopping(Game);
            break;

        case GameState::gs_Quit:
            gs_Quit(Game);
            break;
        }
    }

    void gs_Menu(StateEngine Game)
    {
        int choice = 0;

        while (choice != 1 && choice != 2 && choice != 3)
        {
            system("cls");
            cout <<
                "Welcome to Sky Travel\n"
                "1. Start Over\n"
                "2. Continue Adventure\n"
                "3. Exit\n"
                << endl;
            cin >> choice;
        }

        system("cls");

        switch (choice)
        {
        case 1:
            //load new world
            break;

        case 2:
            //load game
            break;

        case 3:
            changeState(GameState::gs_Quit, Game);
        }
    }
    void gs_Selection(StateEngine Game)
    {
        char selection;

        do
        {
            cout << "What would you like to do next?" << endl;

            cout << "Return to the main (M)enu" << endl;

            cout << "(T)ravel" << endl;

            cout << "(E)xplore the town" << endl;

            cout << "(Q)uit" << endl;

            cin >> selection;
        } while (selection != 'm' && selection != 'M' && selection != 't' && selection != 'T' &&
            selection != 'e' && selection != 'E' && selection != 'q' && selection != 'Q');

        if (selection == 'm' || selection == 'M')
        {
            Game.changeState(GameState::gs_Menu, Game);
        }
        else if (selection == 't' || selection == 'T')
        {
            Game.changeState(GameState::gs_Travel, Game);
        }
        else if (selection == 'e' || selection == 'E')
        {
            Game.changeState(GameState::gs_Town, Game);
        }
        else if (selection == 'q' || selection == 'Q')
        {
            Game.changeState(GameState::gs_Quit, Game);
        }
    }
    void gs_Travel(StateEngine Game)
    {

    }
    void gs_Town(StateEngine Game)
    {
        int choice = 0;

        while (choice != 1 && choice != 2)
        {
            cout << "What would you like to do in the town?" << endl;
            cout << "1. Look for more crew" << endl;
            cout << "2. Look for jobs" << endl;
            cin >> choice;
        }

        switch(choice)
        {
        case 1:
            if (CurrentLocation == Location::Lotan)
            {
                if (LotanCharacters.size() >= 0)
                {
                    int newCrew = -1;

                    while (newCrew < 0 && newCrew > LotanCharacters.size())
                    {                    
                    cout << "You come across the following people:" << endl;
                    for (size_t i = 0; i < LotanCharacters.size(); i++)
                    {
                        cout << i+1 << ". ";
                        LotanCharacters[i].printName();
                    }
                    cout << "Who would you like to try to convince to join your crew?" << endl;
                    cin >> newCrew;
                    }

                    newCrew = newCrew - 1;

                    if (rollDie() <= LotanCharacters[newCrew].getInfluence())
                    {
                        CrewSize++;
                        cout << LotanCharacters[newCrew].getName() << " has decided to join your crew." << endl;
                        Crew.push_back(LotanCharacters[newCrew]);
                        LotanCharacters.erase(LotanCharacters.begin()+newCrew);                        
                    }
                    else
                    {
                        cout << LotanCharacters[newCrew].getName() << " has decided not to join your crew." << endl;
                    }

                }
                else
                {
                    cout << "No one in the town is looking for a job right now." << endl;
                }
            }
            break;

        case 2:
            break;
        }              
    }
    void gs_Shopping(StateEngine Game)
    {

    }
    void gs_Quit(StateEngine Game)
    {
        //add save game
    }
};


int main()
{
    srand(time(0));
    StateEngine Game = {};
            
    Game.changeState(GameState::gs_Menu, Game);
    
    io::CSVReader<5> in("Sky Travel - Characters.csv");
    in.read_header(io::ignore_extra_column, "Name", "Gender", "Skill", "Influence", "CharacterLocation");
    string name;
    int gender;
    int skill;
    int influence;
    int characterlocation;

    while (in.read_row(name, gender, skill, influence, characterlocation))
    {
        if (static_cast<Location>(characterlocation) == Location::Lotan)
        {
            LotanCharacters.push_back(Character(name, static_cast<Gender>(gender), static_cast<Skill>(skill),
                influence, static_cast<Location>(characterlocation)));
        }
        if (static_cast<Location>(characterlocation) == Location::Arvand)
        {
            ArvandCharacters.push_back(Character(name, static_cast<Gender>(gender), static_cast<Skill>(skill),
                influence, static_cast<Location>(characterlocation)));
        }
        if (static_cast<Location>(characterlocation) == Location::Nimoy)
        {
            NimoyCharacters.push_back(Character(name, static_cast<Gender>(gender), static_cast<Skill>(skill),
                influence, static_cast<Location>(characterlocation)));
        }
        if (static_cast<Location>(characterlocation) == Location::Patok)
        {
            PatokCharacters.push_back(Character(name, static_cast<Gender>(gender), static_cast<Skill>(skill),
                influence, static_cast<Location>(characterlocation)));
        }
        if (static_cast<Location>(characterlocation) == Location::Braetar)
        {
            BraetarCharacters.push_back(Character(name, static_cast<Gender>(gender), static_cast<Skill>(skill),
                influence, static_cast<Location>(characterlocation)));
        }
        if (static_cast<Location>(characterlocation) == Location::Cafta)
        {
            CaftaCharacters.push_back(Character(name, static_cast<Gender>(gender), static_cast<Skill>(skill),
                influence, static_cast<Location>(characterlocation)));
        }
        if (static_cast<Location>(characterlocation) == Location::Riv)
        {
            RivCharacters.push_back(Character(name, static_cast<Gender>(gender), static_cast<Skill>(skill),
                influence, static_cast<Location>(characterlocation)));
        }
        if (static_cast<Location>(characterlocation) == Location::Rupta)
        {
            RuptaCharacters.push_back(Character(name, static_cast<Gender>(gender), static_cast<Skill>(skill),
                influence, static_cast<Location>(characterlocation)));
        }                
    }

    io::CSVReader<5> in("Sky Travel - Quests.csv");
    in.read_header(io::ignore_extra_column, "QuestName", "Origin", "Destination", "Goods", "Passengers", "Reward", "isLegal");
    string questname;
    int origin;
    int destination;
    int goods;
    int passengers;
    int reward;
    bool islegal;

    while (in.read_row(questname, origin, destination, goods, passengers, reward, islegal))
    {
        if (static_cast<Location>(origin) == Location::Lotan)
        {
            LotanQuests.push_back(Quests(questname, static_cast<Location>(origin), static_cast<Location>(destination),
                goods, passengers, reward, static_cast<bool>(islegal)));
        }
        if (static_cast<Location>(origin) == Location::Arvand)
        {
            ArvandQuests.push_back(Quests(questname, static_cast<Location>(origin), static_cast<Location>(destination),
                goods, passengers, reward, static_cast<bool>(islegal)));
        }
        if (static_cast<Location>(origin) == Location::Nimoy)
        {
            NimoyQuests.push_back(Quests(questname, static_cast<Location>(origin), static_cast<Location>(destination),
                goods, passengers, reward, static_cast<bool>(islegal)));
        }
        if (static_cast<Location>(origin) == Location::Patok)
        {
            PatokQuests.push_back(Quests(questname, static_cast<Location>(origin), static_cast<Location>(destination),
                goods, passengers, reward, static_cast<bool>(islegal)));
        }
        if (static_cast<Location>(origin) == Location::Braetar)
        {
            BraetarQuests.push_back(Quests(questname, static_cast<Location>(origin), static_cast<Location>(destination),
                goods, passengers, reward, static_cast<bool>(islegal)));
        }
        if (static_cast<Location>(origin) == Location::Cafta)
        {
            CaftaQuests.push_back(Quests(questname, static_cast<Location>(origin), static_cast<Location>(destination),
                goods, passengers, reward, static_cast<bool>(islegal)));
        }
        if (static_cast<Location>(origin) == Location::Riv)
        {
            RivQuests.push_back(Quests(questname, static_cast<Location>(origin), static_cast<Location>(destination),
                goods, passengers, reward, static_cast<bool>(islegal)));
        }
        if (static_cast<Location>(origin) == Location::Rupta)
        {
            RuptaQuests.push_back(Quests(questname, static_cast<Location>(origin), static_cast<Location>(destination),
                goods, passengers, reward, static_cast<bool>(islegal)));
        }
    }
            
    cout << "What's your name?" << endl;
    string tempName;
    cin >> tempName;
    system("cls");

    char yesorno = 'n';

    while (yesorno != 'Y' && yesorno != 'y')
    {
        cout << "Your name is " << tempName << ". Is that correct? (Y/N)" << endl;
        cin >> yesorno;
        if (yesorno == 'Y' || yesorno == 'y')
        {
            
        }
        else
        {
            cout << "Please spell your name again." << endl;
            cin >> tempName;
        }
    }

    //Character Player1;
    //Add Player1 to crew vector

    cout << "You are currently in Lotan. You are the pilot of a skippy ship." << endl;
    cout << "A skippy ship has a speed of 2, cargo space of 6, and no additional space for crew." << endl;

    Game.changeState(GameState::gs_Selection, Game);

    system("pause");

    return 0;
}
