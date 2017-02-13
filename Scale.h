#ifndef Scale_h
#define Scale_h

#include "HX711.h"
#include "AnalogSmooth.h"

class Scale
{
	public:
		Scale(int dtPin, int sckPin, float calibrationFactor, int smoothingWindow);
		void init();
		float read();
		float readRaw();
		void tare(int times);
		void setCalibrationFactor(float calibrationFactor);
		HX711 getHX711();

	private:
		int _sckPin, _dtPin, _smoothingWindow;
		float _calibrationFactor, _raw, _smooth;
		HX711 _scale;
		AnalogSmooth _smoother;
		void _read();
};
#endif
