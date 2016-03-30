#ifndef RandomRobotAlgorithm_h__
#define RandomRobotAlgorithm_h__

#include "AbstractAlgorithm.h"
#include "Sensor.h"

namespace ns_robotic_cleaner_simulator
{


class RandomRobotAlgorithm : public AbstractAlgorithm
{
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Members ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
private:
	//const AbstractSensor robotSensor;  //compiler says error
	AbstractSensor & robotSensor;   //the sensor is passed to the algorithm by
	//the simulator when the algorithm is initialized
	map<string,int> configs;

//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Ctor/Dtor ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
public:
	RandomRobotAlgorithm(AbstractSensor& sensor, map<string, int> config);
	~RandomRobotAlgorithm(void){}

public:
//~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~ Functions ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
	Direction step();

	void setSensor(const AbstractSensor& sensor) override
	{
		robotSensor = sensor;
	}

	void setConfiguration(map<string, int> config) override
	{
		configs = map<string,int>(config);
	}

	void aboutToFinish(int stepsTillFinishing) override{}

};


} // end of namespace ns_robotic_cleaner_simulator



#endif //RandomRobotAlgorithm