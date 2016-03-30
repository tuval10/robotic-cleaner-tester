//#include "stdafx.h"
#include "AlgorithmSingleRun.h"


namespace ns_robotic_cleaner_simulator
{
	
	AlgorithmSingleRun::AlgorithmSingleRun(void)
		: _configs(map<string,int>())
	{
		initialize();
	}

	AlgorithmSingleRun::AlgorithmSingleRun(const map<string, int> & configs, AbstractAlgorithm * currentAlgorithmPointer, Battery robotBattery, House * currentHousePointer)
		: _configs(configs)
	{
		initialize();
		_currentAlgorithm = currentAlgorithmPointer;
		_robotBattery = new Battery(robotBattery);
		_currentHouse = new House(*currentHousePointer);
		_currentPosition = _currentHouse->GetDockingStation(); // start at docking points
		_algorithmSensor = new Sensor(_currentHouse,_currentPosition);
		_currentAlgorithm->setSensor(*_algorithmSensor);
		_canStillRun = true;
		_sumOfDirtBeforeCleaning = _currentHouse->SumOfDirtInTheHouse();
	}

	AlgorithmSingleRun::AlgorithmSingleRun(const map<string, int> & configs, AbstractAlgorithm * currentAlgorithmPointer, const Battery & robotBattery, House * currentHouse, AbstractSensor * algoSensor, Point * startingPoint)
		: _configs(configs)
	{
		initialize();
		_currentAlgorithm = currentAlgorithmPointer;
		_robotBattery = new Battery(robotBattery);
		_currentHouse = currentHouse;
		_currentPosition = startingPoint;
		_canStillRun = true;
		_sumOfDirtBeforeCleaning = _currentHouse->SumOfDirtInTheHouse();
	}


	
	AlgorithmSingleRun::~AlgorithmSingleRun(void)
	{
		//no need to check if not null - delete(NULL) = no_op
		delete _currentPosition;
		delete _currentHouse;
		delete _algorithmSensor;
		delete _currentAlgorithm;
		delete _robotBattery;
	}

	void AlgorithmSingleRun::initialize()
	{
		_algorithmSensor = NULL;
		_currentAlgorithm = NULL;
		_currentHouse = NULL;
		_currentPosition = NULL;
		_robotBattery = NULL;
		_canStillRun = false;
		_dirtCollected = 0;
		_numberOfStepsCommited = 0;
		_actual_position_in_copmetition = 0;
		_sumOfDirtBeforeCleaning = 0;
	}

	bool AlgorithmSingleRun::CanDoStep() const
	{
		return (	(_numberOfStepsCommited < _configs.find("MaxSteps")->second) &&
					(_canStillRun) &&
					( ! _currentHouse->IsClean()));
	}

	bool AlgorithmSingleRun::IsHouseCleaned() const
	{
		return _currentHouse->IsClean();
	}

	bool AlgorithmSingleRun::IsBackInDocking() const
	{
		return _currentHouse->IsDockingStation(*_currentPosition);
	} 

	bool AlgorithmSingleRun::HasWon() const
	{
		return IsBackInDocking() && IsHouseCleaned();
	} 

	
	//************************************
	// Brief:		Moves one step and change the status of members according to the move commited
	// Pre:			-
	// Post:		-
	//************************************
	void AlgorithmSingleRun::DoStep()
	{
		// charging and cleaning before the move
		if(_currentHouse->IsDockingStation(*_currentPosition))
			_robotBattery->Recharge();
		else
			_robotBattery->Consume();

		if( _currentHouse->IsDirty(*_currentPosition) ){
			_currentHouse->Clean(*_currentPosition);
			_dirtCollected++;
		}

		//making the move and updating 
		Direction chosenDirection = _currentAlgorithm->step();
		_currentPosition->Move(chosenDirection);
		if(HasMadeIllegalStep())
		{
			cout << _currentHouse->GetShortName() << "\t0\n";
			cout << "algorithm made an illegal move";
			_canStillRun = false;
		}
		if(IsAlgorithmBatteryEmpty())
			_canStillRun = false;
		++_numberOfStepsCommited;
	}

	bool AlgorithmSingleRun::IsAlgorithmBatteryEmpty() const
	{
		return (_robotBattery->IsBatteryEmpty() && ! _currentHouse->IsDockingStation(*_currentPosition));
	}

	bool AlgorithmSingleRun::HasMadeIllegalStep() const
	{
		return (! _currentHouse->IsPositionValid(*_currentPosition));
	}

}
