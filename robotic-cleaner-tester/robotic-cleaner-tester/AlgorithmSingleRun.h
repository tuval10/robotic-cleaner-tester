#ifndef AlgorithmSingleRun_h__
#define AlgorithmSingleRun_h__

#include "Battery.h"
#include "Direction.h"
#include "AbstractAlgorithm.h"
#include "House.h"
#include "Point.h"
#include "Encoder.h"

using namespace std;

class AlgorithmSingleRun
{
	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Members ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
	const map<string, int> & _configs;
	AbstractAlgorithm * _currentAlgorithm;
	Battery * _robotBattery;
	House * _currentHouse;
	Point * _currentPosition;
	int _numberOfStepsCommited;
	AbstractSensor * _algorithmSensor;
	bool _canStillRun; // boolean which is false after made illegal move, when battery is empty, or when members are uninitiallized
	bool _hitWall;  //boolean which is true iff algo hit a wall
	int _dirtCollected;
	int _actual_position_in_copmetition; // see http://moodle.tau.ac.il/mod/page/view.php?id=374508. 
	int _sumOfDirtBeforeCleaning;
	bool _videoEnabled;
	
	string _algorithmFileName;
	Direction _lastDirection;  //added because signature of step() changed.  keeps the direction of the lastStep actually performed by the simulation
	
	bool debug_AlgorithmSingleRun = false;  //for debugging

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ctor/Dtor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
	AlgorithmSingleRun (
		const map<string, int> & configs, 
		AbstractAlgorithm * currentAlgorithmPointer, 
		const Battery & robotBattery, 
		House * currentHouse,
		AbstractSensor * algoSensor, 
		Point * startingPoint, string algorithmFileName);	
	~AlgorithmSingleRun(void);
	void initialize();

	// ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Getters/Setters ~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
	int GetSumOfDirtBeforeCleaning() const { return _sumOfDirtBeforeCleaning; }
	int GetActualPosition() const { return _actual_position_in_copmetition; }
	void SetActualPosition(int val) { _actual_position_in_copmetition = val; }
	House * GetCurrentHouse() const { return _currentHouse; }
	int GetDirtCollected() const { return _dirtCollected; }
	int GetNumberOfStepsCommited() const { return _numberOfStepsCommited; }
	string GetAlgorithmFileName() { return _algorithmFileName; }
	Direction GetLastDirection() { return _lastDirection; }
	AbstractAlgorithm * GetCurrentAlgorithm() { return _currentAlgorithm; }
	string GetAlgoHouseString() const;
	void SetVideoEnabled(bool videoEnabled) {_videoEnabled = videoEnabled;}
	bool GetVideoEnabled()const {return _videoEnabled;}

	//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
	Direction DoStep(Direction lastStep);
	bool CanDoStep() const;
	bool IsHouseCleaned() const;
	bool IsBackInDocking() const;
	bool HasWon() const;
	bool HasMadeIllegalStep() const;
	bool IsAlgorithmBatteryEmpty() const;
	void MakeVideo(); //finalize the video and delete the image folder
};

#endif // AlgorithmSingleRun_h__

