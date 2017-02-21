#ifndef Scale_h
#define Scale_h

#include "HX711.h"
#include "AnalogSmooth.h"

class Scale
{
	public:
		Scale(int dtPin, int sckPin, byte tareMeasurements, int smoothingWindow);
		void init(float calibrationFactor);
		float read();
		float readRaw();
		void tare();
		float getOffset();
		HX711 getHX711();

	private:
		int _sckPin, _dtPin, _smoothingWindow;
		byte _tareMeasurements;
		long int _initialOffset = 0;
		float _calibrationFactor = 0.f;
		float _raw, _smooth;
		HX711 _scale;
		AnalogSmooth _smoother;
		void _read();
};
#endif
