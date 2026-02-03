#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <unordered_set>

using Table = std::unordered_map<std::string, void*>;  // Fixed: removed const and &
using StrCol = std::vector<std::string>;
using IntCol = std::vector<int>;
using CharCol = std::vector<char>;

class DBMS {
private:
    enum class DbTypes {
        INT,
        FLOAT,
        STRING
    };

    std::unordered_map<std::string, std::unique_ptr<Table>> tables;  // Fixed: removed const and &
    std::unordered_set<std::string> tableNames;     // Fixed: removed const and &


    void insert_coaches();
    void insert_teams();

public:  // Fixed: moved constructors to public
    DBMS() = default;
    DBMS(const DBMS&) = delete;  // Better than default for RAII
    DBMS(DBMS&&) = default;

    void createDatabase() {
        // Create coaches Table
        tables["coaches"] = std::make_unique<Table>();
		tables["teams"] = std::make_unique<Table>();
		Table& coachesTable = *tables["coaches"];
		Table& teamsTable = *tables["teams"];

		// Create Coaches Table
        coachesTable["Coach_ID"]         = (void*) new StrCol();
        coachesTable["first_name"]       = (void*) new StrCol();
		coachesTable["last_name"]        = (void*) new StrCol();
		coachesTable["season_wins"]      = (void*) new IntCol();
		coachesTable["season_losses"]    = (void*) new IntCol();
		coachesTable["play_offs_wins"]   = (void*) new IntCol();
		coachesTable["play_offs_losses"] = (void*) new IntCol;
		coachesTable["team"]             = (void*) new StrCol();


        // Create Teams Table
        teamsTable["team_id"]  = (void*) new StrCol();
        teamsTable["Location"] = (void*) new StrCol();
        teamsTable["Name"]     = (void*) new StrCol();
        teamsTable["League"]   = (void*) new CharCol();
    }

    void deleteDatabase() {
        tables.clear();
        tableNames.clear();
    }

    ~DBMS() {
        deleteDatabase();
    }

    // Database Queries
    void addCoaches();
    void addTeams();
    
    void loadCoaches();
    void loadTeams();

    void CoachesByName(const std::string& CoachLastName) {
        auto cols = std::vector<std::string>(); // columns that are going to be displayied
        auto indexes = std::vector<int>(); // indexes that are going to be displayied

        
        StrCol& last_names = (StrCol*)((tables["coaches"])["last_name"]);

        for (int i = 0; i < last_names.size(); i++) {
            if (last_names[i] == CoachLastName)
                indexes.push_back(i);
        }

        display_coaches(cols, indexes);


    };
    void TeamsByCity();
    
    void bestCoach();
    void coachesByTeam();

    void coachCareerStats();
    void searchCoaches();

    void display_coaches(std::vector<std::string>& cols, std::vector<int>& indexes);
    void display_tables(std::vector<std::string>& cols, std::vector<int>& indexes);
};

int main() {
    DBMS db;
    db.createDatabase();

    std::cout << "Database working!\n";
    return 0;
}
