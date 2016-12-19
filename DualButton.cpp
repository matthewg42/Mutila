#include "DualButton.h"

DualButton::DualButton(DebouncedButton* b1, DebouncedButton* b2)
{
    _b1 = b1; 
    _b2 = b2;
}

void DualButton::begin(uint8_t threshold, uint8_t delay)
{
    _b1->begin(threshold, delay); 
    _b2->begin(threshold, delay);
}

void DualButton::update() 
{ 
    _b1->update(); 
    _b2->update(); 
}

bool DualButton::on() 
{ 
    return _b1->on() || _b2->on(); 
}

bool DualButton::pushed()
{
    return _b1->pushed() || _b2->pushed(); 
}

bool DualButton::tapped() 
{ 
    return _b1->tapped() || _b2->tapped(); 
}

bool DualButton::held(uint16_t ms)
{
    return _b1->held(ms) || _b2->held(ms);
}

bool DualButton::repeat(uint16_t initialMs, uint16_t repeatMs)
{
    return _b1->repeat(initialMs, repeatMs) || _b2->repeat(initialMs, repeatMs);
}



