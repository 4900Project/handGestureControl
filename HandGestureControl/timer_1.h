#pragma once
class timer_1
{
public:
	timer_1();
	~timer_1();

	void start_1();
	void stop_1();

	void reset_1();
	double getStop_1();

private:
	double startTime_1;
	double stopTime_1;

	double value_1;


};

