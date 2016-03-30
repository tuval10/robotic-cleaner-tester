//#include "stdafx.h"
#include "Sensor.h"

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
		array<Point,4> pointsAfterMoving = {*_currentPosition, *_currentPosition, *_currentPosition, *_currentPosition};
		SensorInformation returnedInfo;
		returnedInfo.dirtLevel = _currentHouse->GetDirtLevel(*_currentPosition);
		for(unsigned int i=0; i< pointsAfterMoving.size(); i++)
		{
			bool canMove = pointsAfterMoving[i].Move(Direction(i));
			if( ! canMove)
			{
				returnedInfo.isWall[i] = true;
				continue;
			}
			bool isInsideTheHouse = _currentHouse->IsPositionValid(pointsAfterMoving[i]);
			if(! isInsideTheHouse)
			{
				returnedInfo.isWall[i] = true;
				continue;
			}
			returnedInfo.isWall[i] = _currentHouse->IsWall(pointsAfterMoving[i]);
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