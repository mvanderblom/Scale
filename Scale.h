#ifndef Scale_h
#define Scale_h

#include "HX711.h"
#include "AnalogSmooth.h"

class Scale
{
	public:
		Scale(int sckPin, int dtPin, float calibrationFactor, int smoothingWindow);
		void debug();
		void init();
		void read();
		void calibrate();

	private:
		bool _debug = false;
		int _sckPin, _dtPin, _smoothingWindow;
		float _calibrationFactor, _raw, _smooth;
		HX711 _scale;
		AnalogSmooth _smoother;
};
#endif
