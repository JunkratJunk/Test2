#ifndef RECT_H
#define RECT_H

template<class T>
struct Rect
{
	T left;
	T top;
	T width;
	T height;
	Rect(T left, T top, T width, T height)
		: left(left)
		, top(top)
		, width(width)
		, height(height)
	{

	}
};

#endif // RECT_H
