#pragma once
#include <math.h>
#include <iostream>
//#define PI 3.14159265358979323846 
#define _USE_MATH_DEFINES 


struct Vector2
{
public:
	double x;
	double y;

	explicit Vector2()
	{									//std construct
		x = 0;
		y = 0;
	}

	explicit Vector2(double xd, double yd)			//direct construct					
	{
		x = xd;
		y = yd;
	}

	Vector2(const Vector2& v)			//copy construct
	{
		x = v.x;
		y = v.y;
	}
	~Vector2() {};			//destruct
	//operators:

	void operator=(const Vector2& v) //=
	{
		x = v.x;
		y = v.y;
	}
	void SetVector(double xd, double yd) //usefull metod, allow me to set Vectors value from inside;
	{
		x = xd;
		y = yd;
	}


	Vector2 operator+(const Vector2& v) const //+
	{
		return Vector2(x + v.x, y + v.y);
	}
	Vector2& operator+=(const Vector2& v) //+=
	{
		x += v.x;
		y += v.y;
		return *this;
	}
	Vector2 operator-(const Vector2& v) const //-
	{
		return Vector2(x - v.x, y - v.y);
	}
	Vector2 operator*(double k) const
	{
		return Vector2(x * k, y * k);
	}


	Vector2 operator/(double c) const  // /
	{
		return Vector2(x / c, y / c);
	}
	Vector2& operator*=(double c) //*=
	{
		x *= c;
		y *= c;
		return *this;
	}
	double operator*(const Vector2& v) const  // Scalar mult
	{
		return x * v.x + y * v.y;
	}
	Vector2 ort()						//perpendicullar vector
	{
		return Vector2(y, -x);
	}
	double length()						//length
	{
		return sqrt(x*x + y * y);
	}
	double distance(const Vector2& v)			//minus
	{
		return Vector2((v.x - x), (v.y - y)).length();
	}

	Vector2 norm()							//normirivka
	{
		*this *= (1 / (*this).length());
		return *this;
	}
	Vector2& rotate(double degr)				//rotate itself clockwise
	{
		double rads, COS, SIN, xr, yr;
		rads = (degr / 180.0)* atan(1) * 4;
		COS = cos(rads);
		SIN = sin(rads);

		xr = (x * COS) - (y * SIN);
		yr = (x * SIN) + (y * COS);

		x = round(1000 * xr) / 1000;
		y = round(1000 * yr) / 1000;
		return *this;
	}
	Vector2 getRotated(double degr) {			//gives a value (vector is const) clockwise
		double rads, COS, SIN;
		rads = (degr / 180.0)* atan(1) * 4;
		COS = cos(rads);
		SIN = sin(rads);

		return Vector2(round(1000 * ((x * COS) - (y * SIN))) / 1000, round(1000 * (x * SIN) + (y * COS)) / 1000);
	}
	Vector2 operator -() const						// reversing vector
	{
		return (*this)*(-1);
	}
	double operator^(const Vector2& v) const	 //vector multipliing (returns skalar)								
	{
		return	x * v.y - y * v.x;
	}



};
Vector2 operator*(double k, const Vector2& v)
{
	return Vector2(k * v.x, k * v.y);
}
std::ostream& operator<<(std::ostream& stream, const Vector2& v) //cout
{
	stream << '(' << v.x << ':' << v.y << ')';
	return stream;
}
std::istream& operator>>(std::istream& stream, Vector2& v)     //cin
{
	stream >> v.x >> v.y;

	return stream;
}
