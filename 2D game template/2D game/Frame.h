#ifndef FRAME_H
#define FRAME_H

#include "Point.h"

struct Frame
{
	Frame() = delete;
	Frame(const ipoint& position, const ipoint& size) : position(position), size(size) {}

	const ipoint position;
	const ipoint size;
};

#endif
