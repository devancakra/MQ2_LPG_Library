// Library: Gas MQ2-LPG
// By: Devan Cakra M.W

#include <MQ2_LPG.h>
#include <Arduino.h>

void MQ2Sensor::begin(int pin) {
  _pin = pin;
}

void MQ2Sensor::RL(float RL_Value){
  _RL = RL_Value;
}

void MQ2Sensor::Ro(float Ro_Value){
  _Ro = Ro_Value;
}

void MQ2Sensor::Volt(float Voltage_Value){
  _Voltage = Voltage_Value;
}

void MQ2Sensor::BitADC(float bitADC_Value){
  _bitADC = bitADC_Value;
}

void MQ2Sensor::VRL(){
  _VRL = analogRead(_pin)*(_Voltage/(_bitADC));
}

float MQ2Sensor::roCheck(){
  VRL();
  _Rs = (((_Voltage/(_VRL))-1)*(_RL));
  return _Reverseosmosis = _Rs/9.6;
}

float MQ2Sensor::ratioCheck(){
  VRL();
  _Rs = ((_Voltage*(_RL))/(_VRL))-(_RL);
  return _ratio = ((_Rs)/(_Ro));
}

double MQ2Sensor::mCurve(double x1, double x2, double y1, double y2){
  return _m = (log(y2) - log(y1)) / (log(x2) - log(x1));
}

double MQ2Sensor::bCurve(double x, double y){
  return _b = log(y) - (_m) * log(x);
}

void MQ2Sensor::getDataCalibration(){
  _getDataRo = MQ2Sensor::roCheck();
  _getDataRatio = MQ2Sensor::ratioCheck();
}

void MQ2Sensor::viewDataCalibration(){
  Serial.println("Ro Value: "+String(_getDataRo)); // Prints the Ro value.
  Serial.println("Rs/Ro Value: "+String(_getDataRatio)); // Prints the Rs/Ro value.
  Serial.println("m Value: "+String(_m)); // Prints the m value.
  Serial.println("b Value: "+String(_b)); // Prints the b value.
}

float MQ2Sensor::readGas(){
  return _ppm = (pow(10, ((log10(_getDataRatio)-(_b))/(_m))));
}