#pragma once

class Heartbeat {
public:
	enum Mode {
		Normal=0,
		Quick,
		Slow,
		Slower
	};

    // Call from setup()
	Heartbeat(int pin);
	~Heartbeat();

    void begin();

    Mode mode();
	void setMode(Mode mode);
	void update();

private:
    void updatePin(bool state);

	Mode _mode;
	int _pin;
	bool _pinState;
	unsigned long _lastStateFlip;
	unsigned int _onTime;
	unsigned int _offTime;

};

