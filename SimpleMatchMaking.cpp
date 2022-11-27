//In our game, each player is assigned a numerical rating which determines their skill level.
//We want to support a 100 vs 100 clan war mode. In this mode, participants from each clan 
//are split into 10 teams of 10, and each team of 10 will battle another team of 10 from the
//opponent clan.Design a matchmaking algorithm to create as even of a match as possible between
//two clans, accounting for edge casesand skill imbalances.

//CASES NOT IMPLEMENTED
//-NOT ENOUGH PLAYERS.

#include <iostream>
#include <vector>
#include <algorithm>
#include <time.h>

using namespace std;

const int NUMBER_OF_PLAYERS = 1000;
const int MAX_SKILL = 500;
const int SKILL_STEP = 5;
const int PLAYERS_IN_MATCH = 200;
const int PLAYER_PER_CLAN = PLAYERS_IN_MATCH / 2;

struct Player {
  Player(int assignedSkill) : skill(assignedSkill) { };
  int skill;
};

int FindPlayersAverageSkill(vector<Player*>& players) {
  int sum = 0;
  for (Player* player : players) {
    sum += player->skill;
  }

  return sum / players.size();
}

void FindPlayersWithSkill(vector<Player*>& waiting, vector<Player*>& queued, int averageSkill, int offset = 0) {
  vector<Player*> remaining = vector<Player*>();

  for (int i = 0; i < waiting.size(); ++i) {
    if (abs(waiting[i]->skill - averageSkill) <= offset) {
      queued.push_back(waiting[i]);
      if (queued.size() == PLAYERS_IN_MATCH) {
        return;
      }
    }
    else {
      remaining.push_back(waiting[i]);
    }
  }
  
  FindPlayersWithSkill(remaining, queued, averageSkill, offset + SKILL_STEP);
}

void SplitByClan(vector<Player*>& playersInGame) {
  sort(playersInGame.begin(), playersInGame.end(), greater<> ());
  vector<Player*>* clanA = new vector<Player*>();
  vector<Player*>* clanB = new vector<Player*>();
  int clanA_Skill = 0;
  int clanB_Skill = 0;
  for (Player* player : playersInGame) {
    if ((clanB->size() < PLAYER_PER_CLAN && clanA_Skill > clanB_Skill) || clanA->size() == PLAYER_PER_CLAN) {
      clanB_Skill += player->skill;
      clanB->push_back(player);
    }
    else {
      clanA_Skill += player->skill;
      clanA->push_back(player);
    }
  }

  cout << "CLAN A " << clanA->size() << ": " << FindPlayersAverageSkill(*clanA) << endl;
  cout << "CLAN B " << clanB->size() << ": " << FindPlayersAverageSkill(*clanB) << endl;

  cout << "A    B" << endl;
  for (int i = 0; i < PLAYER_PER_CLAN; ++i) {
    cout << (*clanA)[i]->skill << "     " << (*clanB)[i]->skill << endl;
  }

  delete clanA;
  delete clanB;
}

int main()
{
  srand((unsigned)time(0));

   //Init players.
  vector<Player*> players = vector<Player*>(NUMBER_OF_PLAYERS);
  for (int i = 0; i < NUMBER_OF_PLAYERS; ++i) {
    players[i] = new Player(rand() % MAX_SKILL);
  }

  //Pick average skill of all players currently looking for a game.
  int average = FindPlayersAverageSkill(players);
  vector<Player*> queued = vector<Player*>();
  FindPlayersWithSkill(players, queued, average);

  cout << "PLAYERS FOUND: " << queued.size() << endl;
  cout << "AVERAGE SKILL: " << FindPlayersAverageSkill(queued) << endl;

  SplitByClan(queued);
  for (Player* player : players) {
    delete player;
  }
  players.clear();
}