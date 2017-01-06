#include "Scale.h"
#include "Arduino.h"

Scale::Scale(int sckPin, int dtPin, float calibrationFactor, int smoothingWindow) {
	this->_sckPin = sckPin;
	this->_dtPin = dtPin;
	this->_calibrationFactor = calibrationFactor;
	this->_smoothingWindow = smoothingWindow;
	this->_raw = 0.f;
	this->_smooth = 0.f;
}

void Scale::debug() {
	this->_debug = true;
}

void Scale::init() {
	_scale.begin(_dtPin, _sckPin);
	_scale.set_scale(_calibrationFactor);

	_smoother = AnalogSmooth(_smoothingWindow);

	if(_debug){
		Serial.print("Initialized Scale on _dtPin: ");
		Serial.print(_dtPin);
		Serial.print(", _sckPin: ");
		Serial.print(_sckPin);
		Serial.print(", _calibrationFactor: ");
		Serial.print(_calibrationFactor);
		Serial.print(", _smoothingWindow: ");
		Serial.println(_smoothingWindow);
	}
}

void Scale::read() {
	_raw = _scale.get_units(10);
	_smooth = _smoother.smooth(_raw);
}

void Scale::calibrate() {
	Serial.println("Calibration started");
	_scale.set_scale();
	_scale.tare(25);
	Serial.println("Place object on scale");
	while(_raw < 10000) {
		read();
		delay(100);
	}

	Serial.println("Weighing...");
	float objectWeight = _scale.get_units(100);

	Serial.println(String(objectWeight));
	Serial.println("remove object");
	while(_raw > 100) {
		read();
		delay(100);
	}

	_scale.set_scale(_calibrationFactor);
	Serial.println("Calibration finished");
}

