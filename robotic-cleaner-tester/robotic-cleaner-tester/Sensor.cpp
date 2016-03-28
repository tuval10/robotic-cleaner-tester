#include "stdafx.h"
#include "Sensor.h"
#include <array>
namespace ns_robotic_cleaner_simulator
{




	Sensor::Sensor(void)
		: _currentHouse(NULL), _currentPosition(NULL){ }

	Sensor::Sensor(const House * housePtr, const Point * pointPtr)
		: _currentHouse(housePtr), _currentPosition(pointPtr){ }

	// Brief: returns SensorInformation about the current location of the robot
	SensorInformation Sensor::sense() const
	{
		assert(_currentPosition != NULL && _currentHouse != NULL); 
		array<Direction, 4> Directions = {Direction(0),Direction(1), Direction(2), Direction(3)};
		SensorInformation returnedInfo;
		returnedInfo.dirtLevel = _currentHouse->GetDirtLevel(*_currentPosition);
		for(unsigned int i=0; i< Directions.size(); i++)
		{
			Point neighborPoint = Point(*_currentPosition);
			if( (neighborPoint.Move(Directions.at(i))) && (_currentHouse->IsPositionValid(neighborPoint)))
				returnedInfo.isWall[i] = _currentHouse->IsWall(neighborPoint);
			else
				returnedInfo.isWall[i] = true;
		}
		return returnedInfo;
	}


	unsigned int Sensor::GetCurrentRow()
	{
		unsigned int currentRow =  _currentPosition->GetRow();
		return currentRow;
	}

	unsigned int Sensor::GetCurrrentCol()
	{
		unsigned int currentCol =  _currentPosition->GetCol();
		return currentCol;
	}

}