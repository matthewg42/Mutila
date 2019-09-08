#pragma once

template <class T> 
class NumericRange {
public:
	NumericRange(T start, T end) : _start(start), _end(end) {}
	bool contains(T value) { return value >= _start && value < _end; }

private:
	T _start;
	T _end;

};

