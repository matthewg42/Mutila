#include <stdlib.h>
#include "MutilaDebug.h"
#include "MultiThrowSwitch.h"

MultiThrowSwitch::MultiThrowSwitch(uint8_t throws, const uint8_t pins[], bool sticky, bool pullup) : 
	_throws(throws),
	_sticky(sticky),
	_pos(0)
{
	// First allocate space for pointers to button objects
	_buttons = new DebouncedButton*[throws];

	// Now create the button objects
	for (int i=0; i<_throws; i++) {
		_buttons[i] = new DebouncedButton(pins[i], pullup);
	}
}

MultiThrowSwitch::~MultiThrowSwitch()
{
	// Protect from double delete
	if (_buttons == NULL) {
		return;
	}

	// Delete the button objects
	for (int i=0; i<_throws; i++) {
		if (_buttons[i]) {
			delete _buttons[i];
			_buttons[i] = NULL;
		}
	}
	
	// Finally delete the array of pointers to them
	delete _buttons;
	_buttons = NULL;

}

void MultiThrowSwitch::begin(int startPosition, uint8_t threshold, uint8_t delay)
{
	if (_buttons != NULL) {
		for (int i=0; i<_throws && _buttons[i] != NULL; i++) {
			_buttons[i]->begin(threshold, delay);
		}
	}
	if (startPosition >= 1 && startPosition <= _throws) {
		_pos = startPosition;
	}
	update();
}

void MultiThrowSwitch::update()
{
	if (_buttons == NULL) {
		return;
	}

	for (int i=0; i<_throws && _buttons[i] != NULL; i++) {
		_buttons[i]->update();
	}

	if (_buttons != NULL) {
		for (int i=0; i<_throws && _buttons[i] != NULL; i++) {
			if (_buttons[i]->on()) {
				_pos = i + 1;
				return;
			}
		}
		if (!_sticky) {
			_pos = 0;
		}
	}
}

uint8_t MultiThrowSwitch::position()
{
	return _pos;
}


