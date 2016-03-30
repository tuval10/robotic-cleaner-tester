#ifndef Simulator_h__
#define Simulator_h__

#include <fstream>
#include "AlgorithmSingleRun.h"

namespace ns_robotic_cleaner_simulator
{

class Simulator
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Members ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
	vector<House *> _houses;
	map<string, int> _configs;
	vector< AlgorithmSingleRun *> _runs;
	Battery * _defaultBattery;
	bool _winnerAlgorithmExist;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ctor/Dtor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
	Simulator(void);
	Simulator(char * configFilePath);
	~Simulator(void);

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
	void RunAll(void);
	void ReadConfigFromFile(char * configFilePath);
	int LoadHouses( char * houseFolder);
	int LoadAlgorithmsAndRuns();
	void printScores(int winner_num_steps);
private:
	void MoveAllOneStep(int & currentRankAlgorithmsCompetingOn);
};

} // end of namespace ns_robotic_cleaner_simulator

#endif // Simulator_h__