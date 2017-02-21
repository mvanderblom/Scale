#include <HX711.h>
#include <Scale.h>
#include <Arduino.h>
#include <AnalogSmooth.h>

Scale::Scale(int dtPin, int sckPin, byte tareMeasurements,
		int smoothingWindow) {
	this->_dtPin = dtPin;
	this->_sckPin = sckPin;
	this->_tareMeasurements = tareMeasurements;
	this->_smoothingWindow = smoothingWindow;
	this->_raw = 0.f;
	this->_smooth = 0.f;
}

void Scale::init(float calibrationFactor) {
	_calibrationFactor = calibrationFactor;

	_scale.begin(_dtPin, _sckPin);
	_scale.set_scale(calibrationFactor);
	_scale.tare(_tareMeasurements * 2);
	_initialOffset = _scale.get_offset();
	_smoother = AnalogSmooth(_smoothingWindow);

//	Serial.print("Initialized Scale on _dtPin: ");
//	Serial.print(_dtPin);
//	Serial.print(", _sckPin: ");
//	Serial.print(_sckPin);
//	Serial.print(", _calibrationFactor: ");
//	Serial.print(_calibrationFactor);
//	Serial.print(", _smoothingWindow: ");
//	Serial.println(_smoothingWindow);
}

void Scale::_read() {
	_raw = _scale.get_units(1);
	_smooth = _smoother.smooth(_raw);

//	Serial.print("raw: ");
//	Serial.print(_raw);
//	Serial.print(", \t smooth: ");
//	Serial.print(_smooth);
//	Serial.println();
}

float Scale::read() {
	_read();
	return _smooth;
}

float Scale::readRaw() {
	_read();
	return _raw;
}

void Scale::tare() {
	_scale.tare(_tareMeasurements);

	// Warmup the smoother
	for(int i = 0; i < _smoothingWindow; i++) {
		_read();
	}
}

float Scale::getOffset() {
	long int offset = _scale.get_offset();
	return (offset - _initialOffset) / _calibrationFactor;
}

HX711 Scale::getHX711() {
	return _scale;
}
