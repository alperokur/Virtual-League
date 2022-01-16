#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
#include <vector>

using namespace std;

#define underline "\033[4m"
#define ununderline "\033[0m"

// ------------------ player.h ------------------

class Player{
    private:
        string firstName, lastName;
        int age;
        char position;
        int performance;
        int jesusNumber;

    public:
        Player(const string& firstName, const string& lastName, const char& position);

        void SetPlayerAge(const int& a);
        void SetPlayerJesusNumber(const int& jesusNumber);
        void SetPlayerPerformance(const int& performance);

        string GetPlayerName() const;
        char GetPlayerPosition() const;
        int GetPlayerAge() const;
        int GetPlayerPerformance() const;
        int GetPlayerJesusNumber() const;
};

// ------------------ coach.h ------------------

class Coach{
    private:
        string firstName, lastName;

    public:
        Coach(const string& firstName, const string& lastName);

        string GetCoachName() const;
};

class Team{
    private:
        string teamName;
        char shortName[3];
        Coach* coach;
        int defence, midfielder, striker;
        vector<Player*> player;
        int averageAge, averagePerformance;
        int averagePerformanceDefence, averagePerformanceMidfielder, averagePerformanceStriker;
        int played = 0, won = 0, draw = 0, lost = 0, goal = 0, against = 0, goalDifference = 0, point = 0;

    public:
        Team(const string& teamName, Coach* coach);

        void SetShortName(const string& teamName);
        void AddPlayer(const char& position);
        void SetTactic(const int& defence, const int& midfielder, const int& striker);
        void SetMatchResult(const int& goal, const int& against);

        string GetTeamName() const;
        string GetShortName() const;
        string GetCoach() const;
        int GetTeamAverageAge() const;
        int GetTeamAveragePerformance() const;

        int GetTeamPlayed() const;
        int GetTeamWon() const;
        int GetTeamDraw() const;
        int GetTeamLost() const;
        int GetTeamGoal() const;
        int GetTeamAgainst() const;
        int GetTeamGoalDifference() const;
        int GetTeamPoint() const;
        int GetAveragePerformancePosition(const char& p);

        void GetTeamInfo(const int& state) const;
        void GetPlayersName() const;
        Player* GetPlayer(const int& index);
};

// ------------------ match.h ------------------

class Match{
    private:
        int id = 0;
        Team* home;
        Team* away;
        bool played = false;
        int homeGoal = 0;
        int awayGoal = 0;

    public:
        Match(Team* home, Team* away);

        void SetMatchId(const int& id);

        int GetMatchID() const;
        Team* GetMatchHomeTeam() const;
        Team* GetMatchAwayTeam() const;
        bool GetPlayed() const;
        int GetMatchHomeGoal() const;
        int GetMatchAwayGoal() const;

        void GetMatchInfo(const int& round, const int& match) const;
        void CalcMatchResult(Team* home, Team* away);
        void MatchResult(Team* home, const int& homeGoal, Team* away, const int& awayGoal);
};

// ------------------ main.h ------------------

vector<Team*> teams;
vector<string*> shortNames;
vector<string> playerFirstNames, playerLastNames;
vector<vector<Match*>> matchs;
vector<vector<Match*>> season1_matchs;
vector<vector<Match*>> season2_matchs;

int teamPlayer = 11;
int season = 0;
int totalRounds = 0; // weeks
int matchesPerRound = 0; // matchs
int minPerformance = 30, maxPerformance = 100;
int averageMinPerformance = 60, averageMaxPerformance = 100;
int terminalWidth = 162;

void CreateTeam(const string& teamName, const string& coachFirstName, const string& coachLastName);
void LoadTeamInfo(const string& fileName);
void LoadPlayerInfo(const string& fileName, vector<string>& listName);
void RandomFixture();
void RandomMatch();
void SetAllMatchIdThenSeasons();
void StartFixture(const int& season);
void CalcMatchResultWithSeason(vector<vector<Match*>> array);

Team* SelectTeam();
Player* SelectPlayer(Team* team, const int& menuStateForBack);
void GetTeamsName();
void GetMatchWithTeam(Team* team);
void GetAllMatch();
void GetMatchInfoWithID(const int& id);

void Sort(const string& type);
void Scoreboard();
void MenuProcess(const int& value);
void Back(const int& state);
void Menu();

int RandomNumber(const int& minValue, const int& maxValue);
void Repeat(const char& character, const int& repeatTime);
void Title(const string& title);
char Position(const char& position);
int DecreaseNumber(int number);
int WrongValue(const int& minValue, const int& maxValue, const string& warningText, const string& tryAgainText);
string StringLeftAlignment(string str, const int& maxCharacter, const int& pointNumber);

// ------------------ player.cpp ------------------

Player::Player(const string& fN, const string& lN, const char& p){
    firstName = fN;
    lastName = lN;
    position = p;
}

void Player::SetPlayerAge(const int& a){
    age = a;
}

void Player::SetPlayerPerformance(const int& pm){
    performance = pm;
}

void Player::SetPlayerJesusNumber(const int& jN){
    jesusNumber = jN;
}

string Player::GetPlayerName() const{
    return firstName + " " + lastName;
}

char Player::GetPlayerPosition() const{
    return position;
}

int Player::GetPlayerAge() const{
    return age;
}

int Player::GetPlayerPerformance() const{
    return performance;
}

int Player::GetPlayerJesusNumber() const{
    return jesusNumber;
}

// ------------------ coach.cpp ------------------

Coach::Coach(const string& fN, const string& lN){
    firstName = fN;
    lastName = lN;
}

string Coach::GetCoachName() const{
    return firstName + " " + lastName;
}

// ------------------ team.cpp ------------------

Team::Team(const string& tN, Coach* c){
    teamName = tN;
    coach = c;
    SetShortName(tN);
    SetTactic(4, 4, 2);
}

void Team::SetShortName(const string& tN){
// First Character
    shortName[0] = tN[0];

    // Second Character
    int space = tN.find(" ");
    if (space > 0){
        shortName[1] = tN[space+1];
    }
    else{
        shortName[1] = tN[1];
    }

    // Third Character
    string* temp;
    temp += shortName[0] + shortName[1];
    if(find(shortNames.begin(), shortNames.end(), temp) != shortNames.end()){
        if (space > 0){
            shortName[2] = tN[space+2];
        }
        else{
            shortName[2] = tN[2];
        }
        temp += shortName[2];
    }
    else{
        shortName[2] = '\0';
    }
    shortName[1] = toupper(shortName[1]);
    shortName[2] = toupper(shortName[2]);
    shortNames.push_back(temp);
}

void Team::AddPlayer(const char& po){
    string randomFirstName = playerFirstNames[RandomNumber(0, playerFirstNames.size() - 1)];
    string randomLastName = playerLastNames[RandomNumber(0, playerLastNames.size() - 1)];
    Player* p = new Player(randomFirstName, randomLastName, po);
    player.push_back(p);
}

void Team::SetTactic(const int& d, const int& m, const int& s){
    if (d + m + s != 10){
        cout << "Taktikteki oyuncu sayısının toplamı 10 olmalıdır. (Örn: 4-4-2)" << endl;
    }
    else {
        // Goalkeeper
        AddPlayer('G');

        // Defence
        for (int i = 1; i <= d; i++){
            AddPlayer('D');
        }

        // Midfielder
        for (int i = 1; i <= m; i++){
            AddPlayer('M');
        }

        // Striker
        for (int i = 1; i <= s; i++){
            AddPlayer('S');
        }

        int minAge = 18, maxAge = 36;
        int averageMinAge = 25, averageMaxAge = 32;

        do{
            averageAge = 0;
            int totalAge = 0;
            for (int i = 0; i < player.size(); i++){
                player[i]->SetPlayerAge(RandomNumber(minAge, maxAge));
                totalAge += player[i]->GetPlayerAge();
            }
            averageAge += totalAge / player.size();
        } while (!(averageAge >= averageMinAge && averageAge <= averageMaxAge));

        do{
            averagePerformance = 0;
            int totalPerformance = 0;
            for (int i = 0; i < player.size(); i++){
                player[i]->SetPlayerPerformance(RandomNumber(minPerformance, maxPerformance));
                totalPerformance += player[i]->GetPlayerPerformance();
            }
            averagePerformance += totalPerformance / player.size();
        } while(!(averagePerformance >= averageMinPerformance && averagePerformance <= averageMaxPerformance));

        int minJesusNumber = 1, maxJesusNumber = 99;
        bool alreadyHave = false;
        int randomNumber; 
        for (int i = 0; i < player.size(); i++){
            randomNumber = RandomNumber(minJesusNumber, maxJesusNumber);
            while(alreadyHave == false){
                for (int j = 0; j < player.size(); j++){
                    if (player[j]->GetPlayerJesusNumber() == randomNumber)
                        alreadyHave = true;
                }
                if (alreadyHave == false)
                    break;
                else
                    randomNumber = RandomNumber(minJesusNumber, maxJesusNumber);    
            }
            player[i]->SetPlayerJesusNumber(randomNumber);
        }
    }
}

void Team::SetMatchResult(const int& g, const int& a){
    if (g > a){
        won++;
        point += 3;
    }
    else if (g == a){
        draw++;
        point += 1;
    }
    else {
        lost++;
        point += 0;
    }
    played++;
    goal += g;
    against += a;
    goalDifference += g - a;
}

string Team::GetTeamName() const{
    return teamName;
}

string Team::GetShortName() const{
    return shortName;
}

string Team::GetCoach() const{
    return coach->GetCoachName();
}

int Team::GetTeamAverageAge() const{
    int total = 0;
    for (int i = 0; i < player.size(); i++){
        Player* p = player[i];
        total += p->GetPlayerAge();
    }
    return total / player.size();
}

int Team::GetTeamAveragePerformance() const{
    int total = 0;
    for (int i = 0; i < player.size(); i++){
        Player* p = player[i];
        total += p->GetPlayerPerformance();
    }
    return total / player.size();
}

int Team::GetTeamPlayed() const{
    return played;
}

int Team::GetTeamWon() const{
    return won;
}

int Team::GetTeamDraw() const{
    return draw;
}

int Team::GetTeamLost() const{
    return lost;
}

int Team::GetTeamGoal() const{
    return goal;
}

int Team::GetTeamAgainst() const{
    return against;
}

int Team::GetTeamGoalDifference() const{
    return goalDifference;
}

int Team::GetTeamPoint() const{
    return point;
}

int Team::GetAveragePerformancePosition(const char& p){
    int total = 0, number = 0;
    for (int i = 0; i < player.size(); i++){
        if (player[i]->GetPlayerPosition() == p){
            total += player[i]->GetPlayerPerformance();
            number += 1;
        }
    }
    return total / number;
}

void Team::GetTeamInfo(const int& s) const{
    Title(GetTeamName() + " | " + GetShortName() + " | " + GetCoach() + " | Ortalama Performans: " + to_string(GetTeamAveragePerformance()) + " | Ortalama Yaş: " + to_string(GetTeamAverageAge()) + " | Galibiyet: " + to_string(GetTeamWon()) + " | Yenilgi: " + to_string(GetTeamLost()) + " | Atılan Gol: " + to_string(GetTeamGoal()) + " | Yenilen Gol: " + to_string(GetTeamAgainst()) + " | Averaj: " + to_string(GetTeamGoalDifference()));
    cout << endl;
    
    cout << string(36, ' ') << underline << " Sıra No " << ununderline << "    "<< underline << "    İsim Soyisim    " << ununderline << "    " << underline << " Mevki " << ununderline << "    " << underline << " Yaş " << ununderline << "    " << underline << " Performans " << ununderline << "    " << underline " Forma Numarası " << ununderline << endl;
    for (int i = 0; i < player.size(); i++){ 
        Player* p = player[i];
        string playerName = p->GetPlayerName();
        int showMaximumCharacterInPlayerName = 19;
        int pointNumber = 3;
        if (playerName.size() < showMaximumCharacterInPlayerName){
            for (int j = playerName.size(); j < showMaximumCharacterInPlayerName - 1; j++){
                playerName += ' ';
            }
        }
        else{
            for (int j = showMaximumCharacterInPlayerName - pointNumber - 1; j < showMaximumCharacterInPlayerName - 1; j++){
                playerName[j] = '.';
                for (int k = showMaximumCharacterInPlayerName - 1; k < playerName.size(); k++){
                    playerName[k] = '\0';
                }
            }
        }
        cout << string(36, ' ') << "   " << setw(2) << i+1 << "         " << playerName << "        "  << Position(p->GetPlayerPosition()) << "         " << setw(2) << p->GetPlayerAge() << "         " << setw(3) << p->GetPlayerPerformance() << "                " << setw(2) << p->GetPlayerJesusNumber() << endl;
	}
    cout << endl;
    cout << "1. Oyuncu Performansını Düzenle " << endl;
    cout << endl;
    cout << "0. Geri Dön" << endl;
    cout << endl;
    cout << "Lütfen yapmak istediğiniz işlem numarasını giriniz: ";
    int state = WrongValue(0, 1, "Hatalı işlem numarası girdiniz.", "Lütfen tekrar giriniz: ");
    switch(state){
        case 0: {
            MenuProcess(s);
            break;
        }
        case 1: {
            cout << endl;
            cout << "Lütfen performansını değiştirmek istediğiniz oyuncunun sıra numarasını giriniz: ";
            int no = WrongValue(1, 11, "Hatalı oyuncu sıra numarası girdiniz.", "Lütfen oyuncu sıra numarası tekrar giriniz: ");
            Player* p = player[no-1];
            cout << endl;
            cout << "Lütfen güncellemek istediğiniz yeni performans değerini giriniz: ";
            int newPerf = WrongValue(30, 100, "Oyuncu performansı 30 ile 100 arasında olmalıdır.", "Lütfen oyuncu performans değerini tekrar giriniz: ");
            p->SetPlayerPerformance(newPerf);
            GetTeamInfo(s);
        }
    }
}

void Team::GetPlayersName() const{
    cout << endl;
    for (int i = 0; i < player.size(); i++){
        string empty = "";
        if (i < 9)
            empty = " ";
        cout << empty << i+1 << ". " << setw(24) << player[i]->GetPlayerName() << " | " << setw(3) <<player[i]->GetPlayerPerformance() << "  |" << endl;
    }
    cout << endl;
}

Player* Team::GetPlayer(const int& index){
    return player[index];
}

// ------------------ match.cpp ------------------

Match::Match(Team* h, Team* a){
    home = h;
    away = a;
}

void Match::SetMatchId(const int& i){
    id = i;
}

int Match::GetMatchID() const{
    return id;
}

Team* Match::GetMatchHomeTeam() const{
    return home;
}

Team* Match::GetMatchAwayTeam() const{
    return away;
}

bool Match::GetPlayed() const{
    return played;
}

int Match::GetMatchHomeGoal() const{
    return homeGoal;
}

int Match::GetMatchAwayGoal() const{
    return awayGoal;
}

void Match::GetMatchInfo(const int& round, const int& match) const{
    cout << endl;
    string emptyf = "", emptys = "", emptyt = "";
    if (id <= 9){
        emptyf = " ";
    }
    
    if (id <= 99){
        emptyf += " ";
    }

    if (round < 9){
        emptys = " ";
    }

    if (match < 9){
        emptyt = " ";
    }

    string winHomeS, winHomeE, winAwayS, winAwayE;
    if (homeGoal > awayGoal){
        winHomeS += underline;
        winHomeE += ununderline;
    }
    else if (awayGoal > homeGoal){
        winAwayS += underline;
        winAwayE += ununderline;
    }

    if (played == 0){
        cout << "ID: " << emptyf << id << " | " << emptys << round + 1 << ". Hafta " << emptyt << match + 1 << ". Maç:" << setw(24) << home->GetTeamName() << "   -   " << away->GetTeamName() << endl;
    }
    else
    {
        cout << "ID: " << emptyf << id << " | " << emptys << round + 1 << ". Hafta " << emptyt << match + 1 << ". Maç:" << setw(24) << home->GetTeamName() << " " << winHomeS << homeGoal << winHomeE << " - " << winAwayS << awayGoal << winAwayE << " " << away->GetTeamName() << endl;
    }
}

void Match::CalcMatchResult(Team* home, Team* away){
    int homeGoalValue = RandomNumber(0, 6);
    int awayGoalValue = RandomNumber(0, 6);

    if (home->GetAveragePerformancePosition('S') > away->GetAveragePerformancePosition('S')){
        homeGoalValue++;
    }
    else if (away->GetAveragePerformancePosition('S') > home->GetAveragePerformancePosition('S')){
        awayGoalValue++;
    }

    if (home->GetAveragePerformancePosition('D') > away->GetAveragePerformancePosition('D')){
        DecreaseNumber(awayGoalValue);
    }
    else if (away->GetAveragePerformancePosition('D') > home->GetAveragePerformancePosition('D')){
        DecreaseNumber(homeGoalValue);
    }

    if (home->GetAveragePerformancePosition('M') > away->GetAveragePerformancePosition('M')){
        homeGoalValue++;
        DecreaseNumber(awayGoalValue);
    }
    else if (away->GetAveragePerformancePosition('M') > home->GetAveragePerformancePosition('M')){
        awayGoalValue++;
        DecreaseNumber(homeGoalValue);
    }

    if(home->GetTeamAveragePerformance() > away->GetTeamAveragePerformance()){
        int random = RandomNumber(0, 1);
        if (random == 0)
            homeGoalValue++;
        else
            DecreaseNumber(awayGoalValue);
    }
    else if(away->GetTeamAveragePerformance() > home->GetTeamAveragePerformance()){
        int random = RandomNumber(0, 1);
        if (random == 0)
            awayGoalValue++;
        else
            DecreaseNumber(homeGoalValue);
    }

    MatchResult(home, homeGoalValue, away, awayGoalValue);
}

void Match::MatchResult(Team* home, const int& hG, Team* away, const int& aG){
    home->SetMatchResult(hG, aG);
    away->SetMatchResult(aG, hG);

    homeGoal = hG;
    awayGoal = aG;

    played = 1;
}

// ------------------ main.cpp ------------------

void CreateTeam(const string& tN, const string& cFN, const string& cLN){
    Coach* c = new Coach(cFN, cLN);
    Team* t = new Team(tN, c);
    teams.push_back(t);
}

void LoadTeamInfo(const string& fN){
    string line, teamName, coachName, coachFirstName, coachLastName;
    ifstream file(fN);
    if (file.is_open()){
        while (getline(file, line)){
            int reagent = line.find('-');
            teamName = line.substr(0, reagent - 1);
            string coachName = line.substr(reagent + 2, line.length());
            int space = coachName.find(' ');
            string coachFirstName = coachName.substr(0, space);
            string coachLastName = coachName.substr(space + 1, coachName.length());
            CreateTeam(teamName, coachFirstName, coachLastName);
        }
        file.close();
    }
}

void LoadPlayerInfo(const string& fN, vector<string>& list){
    string line;
    ifstream file(fN);
    if (file.is_open()){
        while(getline(file, line)){
            list.push_back(line);
        }
        file.close();
    }
}

void RandomFixture(){
    totalRounds = teams.size() - 1;
    matchesPerRound = teams.size() / 2;
    for (int round = 0; round < totalRounds; round++) {
        vector<Match*> season1_rounds;
        vector<Match*> season2_rounds;
        for (int match = 0; match < matchesPerRound; match++) {
            int home = (round + match) % (teams.size() - 1);
            int away = (teams.size() - 1 - match + round) % (teams.size() - 1);
            if (match == 0) {
                away = teams.size() - 1;
            }
            Match* m1 = new Match(teams[home], teams[away]);
            Match* m2 = new Match(teams[away], teams[home]);
            season1_rounds.push_back(m1);
            season2_rounds.push_back(m2);
        }
        season1_matchs.push_back(season1_rounds);
        season2_matchs.push_back(season2_rounds);
    }

    RandomMatch();
    SetAllMatchIdThenSeasons();
}

void RandomMatch(){

    for (int i = 0; i < season1_matchs.size(); i++) {
        int r = i + rand() % (season1_matchs.size() - i);
        swap(season1_matchs[i], season1_matchs[r]);
    }

    for (int round = 0; round < totalRounds; round++) {
        vector<Match*> rounds;
        for (int match = 0; match < matchesPerRound; match++) {
            rounds.push_back(season1_matchs[round][match]);
        }
        matchs.push_back(rounds);
    }

    for (int i = 0; i < season2_matchs.size(); i++) {
        int r = i + rand() % (season2_matchs.size() - i);
        swap(season2_matchs[i], season2_matchs[r]);
    }

    for (int round = 0; round < totalRounds; round++) {
        vector<Match*> rounds;
        for (int match = 0; match < matchesPerRound; match++) {
            rounds.push_back(season2_matchs[round][match]);
        }
        matchs.push_back(rounds);
    }  
}

void SetAllMatchIdThenSeasons(){
    int id = 1;
    for (int round = 0; round < totalRounds*2; round++) {
        for (int match = 0; match < matchesPerRound; match++) {
            Match* m = matchs[round][match];
            m->SetMatchId(id);
            id++;
        }
    }
}

void StartFixture(const int& s){
    if (s == 0){
        CalcMatchResultWithSeason(season1_matchs);
        season++;
    }
    else if (s == 1){
        CalcMatchResultWithSeason(season2_matchs);
        season++;
    }
}

void CalcMatchResultWithSeason(vector<vector<Match*>> array){
    for (int round = 0; round < totalRounds; round++){
        for (int match = 0; match < matchesPerRound; match++) {
            Match* m = array[round][match];
            Team* home = m->GetMatchHomeTeam();
            Team* away = m->GetMatchAwayTeam();
            m->CalcMatchResult(home, away);
        }
    }
}

Team* SelectTeam(){
    GetTeamsName();
    cout << "0. Menüye Dön" << endl;
    cout << endl;
    cout << "Lütfen işlem yapmak istediğiniz takım numarasını giriniz: ";
    int teamIndex = WrongValue(0, teams.size(), "Hatalı takım numarası girdiniz.", "Lütfen tekrar giriniz: ");
    if (teamIndex == 0)
        Menu();
    Team* t = teams[teamIndex-1];
    return t;
}

Player* SelectPlayer(Team* t, const int& s){
    t->GetPlayersName();
    cout << "0. Geri Dön" << endl;
    cout << endl;
    cout << "Lütfen işlem yapmak istediğiniz oyuncu numarasını giriniz: ";
    int playerIndex = WrongValue(0, 11, "Hatalı oyuncu numarası girdiniz.", "Lütfen tekrar giriniz: ");
    if (playerIndex == 0)
        MenuProcess(s);
    cout << endl;
    return t->GetPlayer(playerIndex-1);
}

void GetTeamsName(){
    cout << endl;
    for (int i = 0; i < teams.size(); i++){
        string teamName = StringLeftAlignment(teams[i]->GetTeamName(), 16, 3);
        cout << setw(2) << i+1 << ". " << teamName << " | " << teams[i]->GetShortName() << endl;
    }
    cout << endl;
}

void GetMatchWithTeam(Team* t){
    int totalRounds = (teams.size() - 1) * (season == 0 ? 1 : season);
    int matchesPerRound = teams.size() / 2;
    for (int round = 0; round < totalRounds; round++) {
        for (int match = 0; match < matchesPerRound; match++) {
            if((matchs[round][match]->GetMatchHomeTeam() == t) || (matchs[round][match]->GetMatchAwayTeam() == t)){
                matchs[round][match]->GetMatchInfo(round, match);
            }
        }
    }
    cout << endl;
}

void GetAllMatch(){
    int totalRounds = (teams.size() - 1) * (season == 0 ? 1 : season);
    int matchesPerRound = teams.size() / 2;
    for (int round = 0; round < totalRounds; round++) {
        for (int match = 0; match < matchesPerRound; match++) {
            matchs[round][match]->GetMatchInfo(round, match);
        }
    }
    cout << endl;
    cout << "0. Geri Dön" << endl;
    cout << endl;
    cout << "Lütfen görmek istediğiniz karşılaşmanın Maç ID'sini giriniz veya geri dönebilirsiniz: ";
    int id = WrongValue(0, totalRounds * matchesPerRound, "Hatalı Maç ID'si girdiniz.", "Lütfen tekrar giriniz: ");
    if (id == 0)
        Menu();
    cout << endl;
    GetMatchInfoWithID(id);
}

void GetMatchInfoWithID(const int& id){
    int totalRounds = (teams.size() - 1) * (season == 0 ? 1 : season);
    int matchesPerRound = teams.size() / 2;
    for (int round = 0; round < totalRounds; round++) {
        for (int match = 0; match < matchesPerRound; match++) {
            if(matchs[round][match]->GetMatchID() == id){
                Team* home = matchs[round][match]->GetMatchHomeTeam();
                Team* away = matchs[round][match]->GetMatchAwayTeam();
                int HomeAveragePerformance = 0;
                int AwayAveragePerformance = 0;
                stringstream ss0, ss1;
                ss0 << home->GetTeamAveragePerformance();
                ss0 >> HomeAveragePerformance;
                ss1 << away->GetTeamAveragePerformance();
                ss1 >> AwayAveragePerformance;
                int totalAverage = home->GetTeamAveragePerformance() + away->GetTeamAveragePerformance();
                int homeWin = (home->GetTeamAveragePerformance() * 100) / totalAverage;
                int awayWin = (away->GetTeamAveragePerformance() * 100) / totalAverage;
                cout << setw(20) << underline << "     " << home->GetTeamName() << " | " << home->GetShortName() << " | " << home->GetTeamAveragePerformance() << " | %" << homeWin << "     " << ununderline << setw(22) <<  underline << "     "  << away->GetTeamName() << " | " << away->GetShortName() << " | " << away->GetTeamAveragePerformance() << " | " << "%" << awayWin << "     " << ununderline << endl;
                cout << endl;
                for (int i = 0; i < teamPlayer; i++){
                    Player* hP = home->GetPlayer(i);
                    Player* aP = away->GetPlayer(i);
                    string homeTeamPlayerName = hP->GetPlayerName();
                    string awayTeamPlayerName = aP->GetPlayerName();
                    char homeTeamPlayerPosition = hP->GetPlayerPosition();
                    char awayTeamPlayerPosition = aP->GetPlayerPosition();
                    int homeTeamPlayerPerformance  = hP->GetPlayerPerformance();
                    int awayTeamPlayerPerformance  = aP->GetPlayerPerformance();
                    string empty = "";
                    if (i < 9){
                        empty = " ";
                    }
                    cout << empty << i+1 <<  ".  " << setw(30) << homeTeamPlayerName << " | " << Position(homeTeamPlayerPosition) << " | " << homeTeamPlayerPerformance << setw(44) << awayTeamPlayerName << " | " << Position(awayTeamPlayerPosition) << " | " <<  awayTeamPlayerPerformance << endl;
                }
                
                if (matchs[round][match]->GetPlayed()){
                    cout << "--------------------------------------------------------------------------------------------------------------" << endl;
                    cout << setw(43) << "Atılan Gol: " << matchs[round][match]->GetMatchHomeGoal() << setw(52) << "Atılan Gol: " << matchs[round][match]->GetMatchAwayGoal() << endl;
                } 
                else
                    cout << endl;
            }
        }
    }
}

void Sort(const string& t){
    for (int i = 0; i < teams.size()-1; i++){
        Team* temp;
        for (int j = 0; j < teams.size()-1; j++){
            bool state;
            if (t == "Point"){
                state = teams[j]->GetTeamPoint() < teams[j+1]->GetTeamPoint();
            }
            else if (t == "Average"){
                state = teams[j]->GetTeamPoint() == teams[j+1]->GetTeamPoint() && teams[j]->GetTeamGoalDifference() < teams[j+1]->GetTeamGoalDifference();
            }
            else if (t == "MostGoal"){
                state = teams[j]->GetTeamPoint() == teams[j+1]->GetTeamPoint() && teams[j]->GetTeamGoalDifference() == teams[j+1]->GetTeamGoalDifference() && teams[j]->GetTeamGoal() < teams[j+1]->GetTeamGoal();
            }
            else{
                state = teams[j]->GetTeamName() > teams[j+1]->GetTeamName();
            }
            if(state){
                temp = teams[j];
                teams[j] = teams[j+1];
                teams[j+1] = temp;
            }
	    }
    }
}

void Scoreboard(){
    cout << endl;

    if (season == 0){
        Sort("Alphabetical");
    }
    
    Sort("Point");
    Sort("Average");
    Sort("MostGoal");

    cout << underline << " Sıra No " << ununderline << "   " << underline << "    Takım Adı    " << ununderline << "   " << underline << " Oynadığı Maç " << ununderline << "   " << underline << " Galibiyet Sayısı " << ununderline << "   " << underline " Beraberlik Sayısı " << ununderline << "   " << underline << " Mağlubiyet Sayısı " << ununderline << "   " << underline << " Atılan Gol " << ununderline << "   " << underline << " Yenilen Gol " << ununderline << "   " << underline " Averaj " << ununderline << "   " << underline " Puan " << ununderline << endl;
    for (int i = 0; i < teams.size(); i++){ 
        Team* t = teams[i];
        string teamName = t->GetTeamName();
        int showMaximumCharacterInTeamName = 16;
        int pointNumber = 3;
        if (teamName.size() < showMaximumCharacterInTeamName){
            for (int j = teamName.size(); j < showMaximumCharacterInTeamName - 1; j++){
                teamName += ' ';
            }
        }
        else{
            for (int j = showMaximumCharacterInTeamName - pointNumber - 1; j < showMaximumCharacterInTeamName - 1; j++){
                teamName[j] = '.';
                for (int k = showMaximumCharacterInTeamName - 1; k < teamName.size(); k++){
                    teamName[k] = '\0';
                }
            }
        }
        cout << "   " << setw(2) << i+1 << "        " << teamName << "          " << setw(2) << t->GetTeamPlayed() << "                  " << setw(2) << t->GetTeamWon() << "                  " << setw(2) << t->GetTeamDraw() << "                    " << setw(2) << t->GetTeamLost() << "                " << setw(3) << t->GetTeamGoal() << "             " << setw(3) << t->GetTeamAgainst() << "          " << setw(3) << t->GetTeamGoalDifference() << "       " << setw(3) << t->GetTeamPoint() << endl;
	}
    
}

void MenuProcess(const int& s){
    switch (s){
        case 1: {
            Team* t = SelectTeam();
            t->GetTeamInfo(s);
            break;
        }
        case 2: {
            GetMatchWithTeam(SelectTeam());
            Back(s);
            break;
        }
        case 3: {
            GetAllMatch();
            Back(s);
            break;
        }
        case 4: {
            StartFixture(season);
            Menu();
        }
        case 0: {
            exit(s);
            break;
        }
    }
}

void Back(const int& s){
    cout << "0. Geri Dön: ";
    int back = WrongValue(0, 0, "Hatalı işlem numarası girdiniz.", "Lütfen tekrar giriniz: ");
    if (back == 0){
        MenuProcess(s);
    }
}

void Menu(){
    Title("Sanal Lig - Puan Durumu");
    Scoreboard();
    cout << endl;
    cout << "1. Takım Bilgisini Göster" << endl;
    cout << "2. Takımın Haftalık Maçlarını Göster" << endl;
    cout << "3. Maç ID'si İle Detaylı Karşılaşma Bilgisini Göster" << endl;
    if (season == 0){
        cout << "4. İlk Sezonu Oynat" << endl;
    }
    else if (season == 1){
        cout << "4. İkinci Sezonu Oynat" << endl;
    }
    cout << endl;
    cout << "0. Çıkış" << endl;
    cout << endl;
    cout << "Lütfen yapmak istediğiniz işlem numarasını giriniz: ";
    int state = WrongValue(0, 4, "Hatalı işlem numarası girdiniz.", "Lütfen tekrar giriniz: ");
    MenuProcess(state);
}

int RandomNumber(const int& min, const int& max){
    return rand() % (max - min + 1) + min;
}

void Repeat(const char& c, const int& r){
    for (int i = 0; i < r; i++){
        cout << c;
    }
}

void Title(const string& t){
    cout << endl;
    Repeat('-', terminalWidth);
    cout << endl;
    Repeat(' ', (terminalWidth - t.size()) / 2);
    cout << t << endl;
    Repeat('-', terminalWidth);
    cout << endl;
}

char Position(const char& position){
    char p;
    switch (position){
        case 'G':
            p = 'K';
            break;
        case 'D':
            p = 'D';
            break;
        case 'M':
            p = 'O';
            break;
        case 'S':
            p = 'F';
            break;
        }
    return p;
}

int DecreaseNumber(int n){
    if (n > 0)
        n--;
    return n;
}

int WrongValue(const int& min, const int& max, const string& w, const string& ta){
    int no;
    cin >> no;
    while (!(no >= min && no <= max)){
        cout << endl;
        cout << w << endl; 
        cout << ta;
        cin >> no;
    }
    return no;
}

string StringLeftAlignment(string s, const int& mC, const int& pN){
    if (s.size() < mC){
        for (int j = s.size(); j < mC - 1; j++){
            s += ' ';
        }
    }
    else{
        if (pN > 0) {
            for (int j = mC - pN - 1; j < mC - 1; j++){
                s[j] = '.';
                for (int k = mC - 1; k < s.size(); k++){
                    s[k] = '\0';
                }
            }
        }
    }
    return s;
}

// -------------------------------------------

int main(int argc, char *argv[]){
    setlocale(LC_ALL, "Turkish");
    srand(time(0));
    LoadPlayerInfo("firstnames.txt", playerFirstNames);
    LoadPlayerInfo("lastnames.txt", playerLastNames);
    LoadTeamInfo("teams.txt");
    RandomFixture();
    Menu();
}
