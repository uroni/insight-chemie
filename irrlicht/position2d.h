// Copyright (C) 2002-2005 Nikolaus Gebhardt
// This file is part of the "Irrlicht Engine".
// For conditions of distribution and use, see copyright notice in Irrlicht.h

#ifndef __IRR_POSITION_H_INCLUDED__
#define __IRR_POSITION_H_INCLUDED__

#include "irrTypes.h"

namespace irr
{
namespace core
{

	//! Simple class for holding 2d coordinates.
	/** Not supposed for doing geometric calculations.
	use vector2d instead for things like that. 
	*/
	template <class T>
	class position2d
	{
		public:
			position2d(T x, T y)
				: X(x), Y(y) {};


			position2d()
				: X(0), Y(0) {};


			position2d(const position2d<T>& other)
				: X(other.X), Y(other.Y) {};


			bool operator == (const position2d<T>& other) const
			{
				return X == other.X && Y == other.Y;
			}


			bool operator != (const position2d<T>& other) const
			{
				return X != other.X || Y != other.Y;
			}

			const position2d<T>& operator+=(const position2d<T>& other)
			{
				X += other.X;
				Y += other.Y;
				return *this;
			}

			const position2d<T>& operator-=(const position2d<T>& other)
			{
				X -= other.X;
				Y -= other.Y;
				return *this;
			}

			position2d<T> operator-(const position2d<T>& other) const
			{
				return position2d<T>(X-other.X, Y-other.Y);
			}

			position2d<T> operator+(const position2d<T>& other) const
			{
				return position2d<T>(X+other.X, Y+other.Y);
			}

			const position2d<T>& operator=(const position2d<T>& other) 
			{
				X = other.X;
				Y = other.Y;
				return *this;
			}

			T X, Y;
	};

} // end namespace core
} // end namespace irr

#endif

