#ifndef POINT_H
#define POINT_H

#include <math.h>

template <class data>
struct point
{
	point(){}
	point(const data &all)
	{
		this->x = all;
		this->y = all;
	}
	point(const data &x, const data &y)
	{
		this->x = x;
		this->y = y;
	}
	point(const point &p)
	{
		x = p.x;
		y = p.y;
	}
	~point() {}

	//DATA
	data x;
	data y;
	//UTILITY
	void Zero()
	{
		x = 0;
		y = 0;
	}
	void Negate(const bool x = true, const bool y = true)
	{
		if(x)
			this->x = -this->x;
		if(y)
			this->y = -this->y;
	}
	//EQUALITAZION
	void operator=(const point& p)
	{
		x = p.x;
		y = p.y;
	}
	bool operator==(const point& p) const
	{
		if (x == p.x && y == p.y)
		{
			return true;
		}
		return false;
	}
	//ADDITION
	point operator+(const point& p) const
	{
		point<data> output;

		output.x = x + p.x;
		output.y = y + p.y;

		return output;
	}
	void operator+=(const point& p)
	{
		x = x + p.x;
		y = y + p.y;
	}
	point operator+(const data& p) const
	{
		point<data> output;

		output.x = x + p;
		output.y = y + p;

		return output;
	}
	void operator+=(const data& p)
	{
		x = x + p;
		y = y + p;
	}
	//SUBSTRACTION
	point operator-(const point& p) const
	{
		point<data> output;

		output.x = x - p.x;
		output.y = y - p.y;

		return output;
	}
	void operator-=(const point& p)
	{
		x = x - p.x;
		y = y - p.y;
	}
	point operator-(const data& p) const
	{
		point<data> output;

		output.x = x - p;
		output.y = y - p;

		return output;
	}
	void operator-=(const data& p)
	{
		x = x - p;
		y = y - p;
	}
	//MULTIPLICATION
	point operator*(const point& p) const
	{
		point<data> output;

		output.x = x * p.x;
		output.y = y * p.y;

		return output;
	}
	void operator*=(const point& p)
	{
		x = x * p.x;
		y = y * p.y;
	}
	point operator*(const data& p) const
	{
		point<data> output;

		output.x = x * p;
		output.y = y * p;

		return output;
	}
	void operator*=(const data& p)
	{
		x = x * p;
		y = y * p;
	}
	//DIVISION
	point operator/(const point& p) const
	{
		point<data> output;

		output.x = x / p.x;
		output.y = y / p.y;

		return output;
	}
	void operator/=(const point& p)
	{
		x = x / p.x;
		y = y / p.y;
	}
	point operator/(const data& p) const
	{
		point<data> output;

		output.x = x / p;
		output.y = y / p;

		return output;
	}
	void operator/=(const data& p)
	{
		x = x / p;
		y = y / p;
	}
	//DISTANCES
	data DistanceTo(const point& p) const
	{
		data fx = x - p.x;
		data fy = y - p.y;

		return sqrtf((fx * fx) + (fy * fy));
	}
	data DistanceNoSqrt(const point& p) const
	{
		data fx = x - p.x;
		data fy = y - p.y;

		return (fx * fx) + (fy * fy);
	}
	data DistanceManhattan(const point& p) const
	{
		return abs(p.x - x) + abs(p.y - y);
	}
};

typedef point<int> ipoint;
typedef point<float> fpoint;

#endif
