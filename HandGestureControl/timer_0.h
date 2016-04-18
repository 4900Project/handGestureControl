#pragma once
class timer_0
{
public:
	timer_0();
	~timer_0();

	void start_0();
	void stop_0();

	void reset_0();
	double getStop_0();

private:
	double startTime_0;
	double stopTime_0;
	double holdTime;
	double value_0;

};

