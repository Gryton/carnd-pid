#include <cmath>
#include "PID.h"

using namespace std;

/*
* TODO: Complete the PID class.
*/

PID::PID() {}

PID::~PID() {}

void PID::Init(double Kp, double Ki, double Kd) {
	this->Kp = Kp;
	this->Ki = Ki;
	this->Kd = Kd;
	this->initialized = false;
}

void PID::UpdateError(double cte) {
	if (!this->initialized)
	{
		this->p_error = cte;
		this->i_error = 0;
		this->initialized = true;
	}
	this->d_error = cte - this->p_error;
	this->p_error = cte;
	this->i_error += cte;
	this->total_cte += abs(cte);
}

double PID::TotalError() {
	return -Kp * p_error - Kd * d_error - Ki * i_error;
}

