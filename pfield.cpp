// Programmer: Richa Phulwani
// Due date: Feb 25th 2020
// This program takes a robot's six sensor readings 
// and computes the direction and magnitude of the robot's
// next move if it has to get away from what it's sensing.

#include <iostream>
#include <fstream>
#include <math.h>

using namespace std;

// angles of where the sensors are placed
const double IS1ang = 45;
const double IS2ang = 30;
const double IS3ang = -30;
const double IS4ang = -45;
const double IS5ang = -130;
const double IS6ang = 130;

// sensor readings
int IS1,IS2,IS3,IS4,IS5,IS6;

// function to turn degrees to radians
double deg2rad(int x) {
  double y = double((double(x)*(M_PI)))/double(180);
  return y;
}

// function to compute the X vectors of the sensor readings
double xcomp(double reading, double angleInRad) {
  double y = reading*double(cos(angleInRad));
  return y;
}

// function to compute the Y vectors of the sensor readings
double ycomp(double reading, double angleInRad) {
  double y = reading*double(sin(angleInRad));
  return y;
}

// function to compute vector magnitudes of sensor readings
// if it is linear magnitude profile
double magnitude(int reading) {
  double magnitude;
  if (reading < 10) {
    magnitude = double((10 - reading))/double(10);
  }
  else if (reading >= 10){
    magnitude = 0;
  }
  return magnitude;
}

// function to compute directions of sensor readings
// if pfield is repulsive
double direction(int reading, double degree) {
  double direction;
  if (reading < 10) {
    direction = degree + M_PI;
  }
  else if (reading >= 10){
    direction = 0;
  }
  return direction;
}


int main(){
  fstream file;
  file.open("readings.dat");
  if (file.is_open()) {

    // reads sensor inputs
    while(file >> IS1 >> IS2 >> IS3 >> IS4 >> IS5 >> IS6) {

    // computes X and Y vectors
        double X1 = xcomp(magnitude(IS1), direction(IS1,deg2rad(IS1ang)));
        double Y1 = ycomp(magnitude(IS1), direction(IS1, deg2rad(IS1ang)));
        double X2 = xcomp(magnitude(IS2), direction(IS2,deg2rad(IS2ang)));
        double Y2 = ycomp(magnitude(IS2), direction(IS2,deg2rad(IS2ang)));
        double X3 = xcomp(magnitude(IS3), direction(IS3,deg2rad(IS3ang)));
        double Y3 = ycomp(magnitude(IS3), direction(IS3,deg2rad(IS3ang)));
        double X4 = xcomp(magnitude(IS4), direction(IS4,deg2rad(IS4ang)));
        double Y4 = ycomp(magnitude(IS4), direction(IS4, deg2rad(IS4ang)));
        double X5 = xcomp(magnitude(IS5), direction(IS5, deg2rad(IS5ang)));
        double Y5 = ycomp(magnitude(IS5), direction(IS5, deg2rad(IS5ang)));
        double X6 = xcomp(magnitude(IS6), direction(IS6, deg2rad(IS6ang)));
        double Y6 = ycomp(magnitude(IS6), direction(IS6, deg2rad(IS6ang)));

        
       
       double xsumSquared = pow((X1 + X2 + X3 + X4 + X5 + X6),2.0);
       double ysumSquared = pow((Y1 + Y2 + Y3 + Y4 + Y5 + Y6),2.0);
       double xysum = xsumSquared + ysumSquared;
       double magnitude = sqrt(xysum);

       double a = X1 + X2 + X3 + X4 + X5 + X6;
       double b = Y1 + Y2 + Y3 + Y4 + Y5 + Y6;

       double angDiv = b / a;

       double angle2 = ((atan2(b,a))*180) / M_PI;

       cout << "The robot should turn " <<  angle2 << " with a magnitude of " << magnitude << "\n";
    }
  }
  else {
    cout << "readings file not found";
  }
}