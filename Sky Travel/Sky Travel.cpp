#include <iostream>
#include <vector>
#include <cstdlib>
#include "csv.h"

using namespace std;

enum class GameState { gs_Menu = 0, gs_Selection, gs_Travel, gs_Town, gs_Shopping, gs_Quit };
enum class Gender { Male = 0, Female };
enum class Skill { None = 0, Pilot, Mechanic, Diplomat };
enum class Location { Lotan = 0, Arvand, Nimoy, Patok, Braetar, Cafta, Riv, Rupta };

vector<string> SkillNames = { "None", "Pilot", "Mechanic", "Diplomat" };
vector<string> LocationNames = {"Lotan", "Arvand", "Nimoy", "Patok", "Braetar", "Cafta", "Riv", "Rupta"};

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
int BusyCrew = 1;
int usedCargoSpace = 0;
int maxCargoSpace = 5;
int usedCabinSpace = 0;
int maxCabinSpace = 2;
int Fuel = 30;
int Currency = 20;
int numOfShips = 1;

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
    void setInCrew(bool ifInCrew)
    {
        inCrew = ifInCrew;
    }
    void printName()
    {
        cout << m_Name;
    }
    void printSkill(vector<Character>& CharacterVector, int tempSkill)
    {
        cout << SkillNames[static_cast<int>(CharacterVector[tempSkill].getSkill())];
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

    string getQuestName()
    {
        return m_QuestName;
    }
    Location getQuestOrigin()
    {
        return m_QuestOrigin;
    }
    Location getQuestDestination()
    {
        return m_QuestDestination;
    }
    int getGoodsRequired()
    {
        return m_GoodsRequired;
    }
    int getPassengersRequired()
    {
        return m_PassengersRequired;
    }
    int getReward()
    {
        return m_Reward;
    }
    bool isItLegal()
    {
        return isLegal;
    }
    bool hasBeenStarted()
    {
        return haveStarted;
    }
    bool hasBeenCompleted()
    {
        return isComplete;
    }
    void printQuestName()
    {
        cout << m_QuestName;
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
vector <Quests> QuestList = {};

class Ships
{
protected:
    string m_ShipName;
    int m_ShipSpeed;
    int m_CargoSpace;
    int m_CabinSpace;
    int m_CrewRequired;
    int m_ShipCost;
    
public:
    Ships(string t_ShipName, int t_ShipSpeed, int t_CargoSpace, int t_CabinSpace, int t_CrewRequired, int t_ShipCost)
    {
        m_ShipName = t_ShipName;
        m_ShipSpeed = t_ShipSpeed;
        m_CargoSpace = t_CargoSpace;
        m_CabinSpace = t_CabinSpace;
        m_CrewRequired = t_CrewRequired;
        m_ShipCost = t_ShipCost;
    }

    int getCargoSpace()
    {
        return m_CargoSpace;
    }
    int getCabinSpace()
    {
        return m_CabinSpace;
    }
    int getCrewRequired()
    {
        return m_CrewRequired;
    }
    int getShipCost()
    {
        return m_ShipCost;
    }
};

vector <Ships> AllShips = {};

void addCrew(vector<Character> &CharacterVector)
{
    if ((maxCabinSpace - usedCabinSpace) > 0)
    {
        if (CharacterVector.size() >= 0)
        {
            int newCrew = -1;

            while (newCrew < 0 && newCrew > CharacterVector.size() + 1)
            {
                cout << "You have space for " << (maxCabinSpace - usedCabinSpace) << " crew." << endl;
                cout << "You come across the following people:" << endl;
                for (size_t i = 0; i < CharacterVector.size(); i++)
                {
                    cout << i + 1 << ". ";
                    CharacterVector[i].printName();
                    cout << " (";
                    CharacterVector[i].printSkill(CharacterVector, i);
                    cout << ")" << endl;
                }
                cout << CharacterVector.size() + 1 << ". None" << endl;
                cout << "Who would you like to try to convince to join your crew?" << endl;
                cin >> newCrew;
                system("cls");
            }

            if (newCrew == CharacterVector.size() + 1)
            {
                return;
            }

            newCrew = newCrew - 1;

            if (rollDie() <= CharacterVector[newCrew].getInfluence())
            {
                CrewSize++;
                usedCabinSpace++;
                CharacterVector[newCrew].setInCrew(true);
                cout << CharacterVector[newCrew].getName() << " has decided to join your crew." << endl;
                Crew.push_back(CharacterVector[newCrew]);
                CharacterVector.erase(CharacterVector.begin() + newCrew);
            }
            else
            {
                cout << CharacterVector[newCrew].getName() << " has decided not to join your crew." << endl;
            }

        }
        else
        {
            cout << "No one in the area is looking for a job right now." << endl;
        }
    }
    else
    {
        cout << "There is no additional space on your ship for more crew." << endl;
    }
}

void activeQuests()
{
    if (QuestList.size() > 0)
    {
        cout << "You have the following active quests: ";
        for (int i = 0; i < QuestList.size(); i++)
        {
            cout << QuestList[i].getQuestName();
            if (i < QuestList.size() - 1)
            {
                cout << ", ";
            }
        }
        cout << endl;
    }
}

void addQuest(vector<Quests> &QuestVector)
{
    if (QuestVector.size() >= 0)
    {
        int newQuest = -1;

        while (newQuest < 0 && newQuest > QuestVector.size() + 1)
        {
            cout << "You have " << (maxCargoSpace - usedCargoSpace) << " cargo space." << endl;
            cout << "You have " << (maxCabinSpace - usedCabinSpace) << " cabin space." << endl;
            activeQuests();
            cout << "You find the following jobs:" << endl;
            for (size_t i = 0; i < QuestVector.size(); i++)
            {
                cout << i + 1 << ". ";
                QuestVector[i].printQuestName();
                cout << " (" << QuestVector[i].getGoodsRequired() << " cargo, " << QuestVector[i].getPassengersRequired() << " passengers)" << endl;
            }
            cout << QuestVector.size() + 1 << ". None" << endl;
            cout << "Which job would you like to take on?" << endl;
            cin >> newQuest;
            system("cls");
        }

        if (newQuest == QuestVector.size() + 1)
        {
            return;
        }

        newQuest = newQuest - 1;

        if ((QuestVector[newQuest].getGoodsRequired() <= (maxCargoSpace - usedCargoSpace)) && 
             QuestVector[newQuest].getPassengersRequired() <= (maxCabinSpace - usedCabinSpace))
        {
            usedCargoSpace = usedCargoSpace + QuestVector[newQuest].getGoodsRequired();
            usedCabinSpace = usedCabinSpace + QuestVector[newQuest].getPassengersRequired();
            cout << "You have taken on the job " << QuestVector[newQuest].getQuestName() << "." << endl;
            QuestList.push_back(QuestVector[newQuest]);
            QuestVector.erase(QuestVector.begin() + newQuest);
        }
        else
        {
            cout << "You don't have enough space to take on that quest." << endl;
        }        
    }
    else
    {
        cout << "There are no more jobs in this area." << endl;
    }
}

void changeLocation(Location &newLocation)
{
    CurrentLocation = newLocation;

    for (int i = 0; i < QuestList.size(); i++)
    {
        if (CurrentLocation == QuestList[i].getQuestDestination())
        {
            usedCargoSpace = usedCargoSpace - QuestList[i].getGoodsRequired();
            usedCabinSpace = usedCabinSpace - QuestList[i].getPassengersRequired();
            Currency = Currency + QuestList[i].getReward();
            cout << "You have completed the quest " << QuestList[i].getQuestName() << ", and earned " 
                 << QuestList[i].getReward() << " coins." << endl;
            QuestList.erase(QuestList.begin()+i);
            i--;
        }
    }
}

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
                "1. Start New Adventure\n"
                "2. Continue Adventure\n"
                "3. Exit\n"
                << endl;
            cin >> choice;
            system("cls");
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
            cout << "You are currently in " << LocationNames[static_cast<int>(CurrentLocation)] << "." << endl;
            activeQuests();
            cout << "What would you like to do next?" << endl;
            cout << "Return to the main (M)enu" << endl;
            cout << "(T)ravel" << endl;
            cout << "(E)xplore the town" << endl;
            cout << "Go (S)hopping" << endl;
            cout << "(Q)uit" << endl;

            cin >> selection;

            system("cls");
        } while (selection != 'm' && selection != 'M' && selection != 't' && selection != 'T' &&
            selection != 'e' && selection != 'E' && selection != 's' && selection != 'S' && selection != 'q' && selection != 'Q');

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
        else if (selection == 's' || selection == 'S')
        {
            Game.changeState(GameState::gs_Shopping, Game);
        }
        else if (selection == 'q' || selection == 'Q')
        {
            Game.changeState(GameState::gs_Quit, Game);
        }
    }
    void gs_Travel(StateEngine Game)
    {
        int destination = 0;
        int tempLocation = static_cast<int>(CurrentLocation);

        while (destination < 1 || destination > 8)
        {
            cout << "You are currently in " << LocationNames[static_cast<int>(CurrentLocation)] << "." << endl;
            cout << "You have " << Fuel << " fuel and " << Currency << " coins." << endl;
            activeQuests();
            cout << "Where would you like to travel to?" << endl;
            cout << "1. Lotan (" << ((abs(0 - tempLocation) * 10) * numOfShips) << " fuel)" << endl;
            cout << "2. Arvand (" << ((abs(1 - tempLocation) * 10) * numOfShips) << " fuel)" << endl;
            cout << "3. Nimoy (" << ((abs(2 - tempLocation) * 10) * numOfShips) << " fuel)" << endl;
            cout << "4. Patok (" << ((abs(3 - tempLocation) * 10) * numOfShips) << " fuel)" << endl;
            cout << "5. Braetar (" << ((abs(4 - tempLocation) * 10) * numOfShips) << " fuel)" << endl;
            cout << "6. Cafta (" << ((abs(5 - tempLocation) * 10) * numOfShips) << " fuel)" << endl;
            cout << "7. Riv (" << ((abs(6 - tempLocation) * 10) * numOfShips) << " fuel)" << endl;
            cout << "8. Rupta (" << ((abs(7 - tempLocation) * 10) * numOfShips) << " fuel)" << endl;
            cin >> destination;
            system("cls");
        }
        
        destination = destination - 1;
        
        if (destination == tempLocation)
        {
            cout << "You are currently in that location." << endl;
        }
        if (((abs(destination - tempLocation)*10)*numOfShips) <= Fuel)
        {
            Location newLocation = static_cast<Location>(destination);
            changeLocation(newLocation);
            Fuel = Fuel - ((abs(destination - tempLocation) * 10) * numOfShips);
        }
        else
        {
            cout << "You don't have enough fuel to get there." << endl;
        }

        Game.changeState(GameState::gs_Selection, Game);
    }
    void gs_Town(StateEngine Game)
    {
        int choice = 0;

        while (choice != 1 && choice != 2)
        {
            cout << "You are currently in " << LocationNames[static_cast<int>(CurrentLocation)] << "." << endl;
            cout << "What would you like to do in the town?" << endl;
            cout << "1. Look for more crew" << endl;
            cout << "2. Look for jobs" << endl;
            cin >> choice;
            system("cls");
        }

        if (choice == 1)
        {
            if (CurrentLocation == Location::Lotan)
            {
                addCrew(LotanCharacters);
            }
            if (CurrentLocation == Location::Arvand)
            {
                addCrew(ArvandCharacters);
            }
            if (CurrentLocation == Location::Nimoy)
            {
                addCrew(NimoyCharacters);
            }
            if (CurrentLocation == Location::Patok)
            {
                addCrew(PatokCharacters);
            }
            if (CurrentLocation == Location::Braetar)
            {
                addCrew(BraetarCharacters);
            }
            if (CurrentLocation == Location::Cafta)
            {
                addCrew(CaftaCharacters);
            }
            if (CurrentLocation == Location::Riv)
            {
                addCrew(RivCharacters);
            }
            if (CurrentLocation == Location::Rupta)
            {
                addCrew(RuptaCharacters);
            }
        }
        else if (choice == 2)
        {
            if (CurrentLocation == Location::Lotan)
            {
                addQuest(LotanQuests);
            }
            if (CurrentLocation == Location::Arvand)
            {
                addQuest(ArvandQuests);
            }
            if (CurrentLocation == Location::Nimoy)
            {
                addQuest(NimoyQuests);
            }
            if (CurrentLocation == Location::Patok)
            {
                addQuest(PatokQuests);
            }
            if (CurrentLocation == Location::Braetar)
            {
                addQuest(BraetarQuests);
            }
            if (CurrentLocation == Location::Cafta)
            {
                addQuest(CaftaQuests);
            }
            if (CurrentLocation == Location::Riv)
            {
                addQuest(RivQuests);
            }
            if (CurrentLocation == Location::Rupta)
            {
                addQuest(RuptaQuests);
            }
        }  

        Game.changeState(GameState::gs_Selection, Game);
    }
    void gs_Shopping(StateEngine Game)
    {
        int choice = 0;

        while (choice != 1 && choice != 2 && choice != 3)
        {
            cout << "You have " << Currency << " coins." << endl;
            cout << "What would you like to buy?" << endl;
            cout << "1. Ships" << endl;
            cout << "2. Fuel" << endl;
            cout << "3. Nothing" << endl;
            cin >> choice;
            system("cls");
        }

        if (choice == 1)
        {
            int buyShip = 0;
            
            while (buyShip != 1 && buyShip != 2 && buyShip != 3 && buyShip != 4 && buyShip != 5)
            {
                cout << "You have " << Currency << " coins." << endl;
                cout << "Which ship would you like to buy?" << endl;
                cout << "1. Skippy (cargo 5, cabin 2, crew 1, cost 200)" << endl;
                cout << "2. Cruiser (cargo 10, cabin 4, crew 2, cost 400)" << endl;
                cout << "3. Carrier (cargo 2, cabin 12, crew 3, cost 400)" << endl;
                cout << "4. Cruiser (cargo 20, cabin 10, crew 4, cost 700)" << endl;
                cout << "5. None" << endl;
                cin >> buyShip;
                system("cls");
            }          
            
            if (buyShip == 5)
            {
                Game.changeState(GameState::gs_Selection, Game);
            }

            int newShip = buyShip - 1;

            if (Currency >= AllShips[newShip].getShipCost() && (CrewSize - BusyCrew) >= AllShips[newShip].getCrewRequired())
            {                                
                maxCargoSpace = maxCargoSpace + AllShips[newShip].getCargoSpace();
                maxCabinSpace = maxCabinSpace + AllShips[newShip].getCabinSpace();
                BusyCrew = BusyCrew + AllShips[newShip].getCrewRequired();
                Currency = Currency - AllShips[newShip].getShipCost();
                numOfShips = numOfShips + 1;
                cout << "You have purchased a ship." << endl;
            }
            else if (Currency < AllShips[newShip].getShipCost())
            {
                cout << "You don't have enough money to buy that." << endl;
            }
            else if (Currency >= AllShips[newShip].getShipCost() && (CrewSize - BusyCrew) < AllShips[newShip].getCrewRequired())
            {
                cout << "You don't have enough crew to fly that." << endl;
            }
        }
        else if (choice == 2)
        {
            int buyFuel = 0;

            cout << "You have " << Fuel << " fuel and " << Currency << " coins." << endl;
            cout << "How much fuel would you like to buy?" << endl;
            cin >> buyFuel;
            system("cls");
            char yesorno = 'n';

            while (yesorno != 'Y' && yesorno != 'y')
            {
                cout << "You would like to buy " << buyFuel << " fuel. Is that correct? (Y/N)" << endl;
                cin >> yesorno;
                system("cls");
                if (yesorno == 'Y' || yesorno == 'y')
                {
                    if (Currency >= buyFuel)
                    {
                        Currency = Currency - buyFuel;
                        Fuel = Fuel + buyFuel;
                    }
                    else
                    {
                        cout << "You don't have enough money to buy that." << endl;
                    }                    
                }
                else
                {
                    cout << "You have " << Fuel << " fuel and " << Currency << " coins." << endl;
                    cout << "How much fuel would you like to buy?" << endl;
                    cin >> buyFuel;
                    system("cls");
                }
            }
        }
        else if (choice == 3)
        {

        }

        Game.changeState(GameState::gs_Selection, Game);
    }
    void gs_Quit(StateEngine Game)
    {
        return;
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

    io::CSVReader<7> QuestFile("Sky Travel - Quests.csv");
    QuestFile.read_header(io::ignore_extra_column, "QuestName", "Origin", "Destination", "Goods", "Passengers", "Reward", "isLegal");
    string questname;
    int origin;
    int destination;
    int goods;
    int passengers;
    int reward;
    int islegal;

    while (QuestFile.read_row(questname, origin, destination, goods, passengers, reward, islegal))
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
    
    io::CSVReader<6> ShipFile("Sky Travel - Ships.csv");
    ShipFile.read_header(io::ignore_extra_column, "ShipName", "ShipSpeed", "CargoSpace", "CabinSpace", "CrewRequired", "ShipCost");
    string shipname;
    int shipspeed;
    int cargospace;
    int cabinspace;
    int crewrequired;
    int shipcost;

    while (ShipFile.read_row(shipname, shipspeed, cargospace, cabinspace, crewrequired, shipcost))
    {
        AllShips.push_back(Ships(shipname, shipspeed, cargospace, cabinspace, crewrequired, shipcost));
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
        system("cls");
        if (yesorno == 'Y' || yesorno == 'y')
        {
            
        }
        else
        {
            cout << "Please spell your name again." << endl;
            cin >> tempName;
        }
    }

    char tempGender = 'a';

    while (tempGender != 'm' && tempGender != 'M' && tempGender != 'f' && tempGender != 'F')
    {
        cout << "What gender are you? (M/F)" << endl;
        cin >> tempGender;
        system("cls");
    }   

    Gender playerGender = {};

    if (tempGender == 'm' || tempGender == 'M')
    {
        Gender playerGender = Gender::Male;
    }
    else if (tempGender == 'f' || tempGender == 'F')
    {
        Gender playerGender = Gender::Female;
    }
     
    Character Player1(tempName, playerGender, Skill::Pilot, 20, Location::Lotan);
    Player1.setInCrew(true);
    Crew.push_back(Player1);

    cout << "You are the pilot of a skippy ship." << endl;
    cout << "A skippy ship has cargo space of 5 and 2 additional space for crew." << endl;

    Game.changeState(GameState::gs_Selection, Game);

    system("pause");

    return 0;
}
