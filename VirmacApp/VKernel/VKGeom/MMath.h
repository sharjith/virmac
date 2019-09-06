/*
 *  This program is free software; you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation; either version 2 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program; if not, write to the Free Software
 *  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA 02111-1307, USA.
 */
 
/***************************************************************************
 *            MMath.h
 *
 *  Thu Jun 29 22:25:05 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _MMATH_H
#define _MMATH_H

#include "VKGeom.h"

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

//Some Useful Math Routines and definitions
//Some Are Directly From Graphics Gems

#ifndef PI
#define PI (double)3.1415926535897932384626433832795
#endif

#ifndef INFINITY
#define INFINITY (double)999999.999f
#endif

#ifndef EPSILON
#define EPSILON (double)0.000001f
#endif

#ifndef MAX
#define MAX(X, Y) (X) > (Y) ? (X) : (Y)
#endif				

#ifndef vsin
#define vsin(x) ((1.0) - (double)(cos(x))) //versine theta (1 - cos theta)
#endif	
				     
VKGEOMSHARED_EXPORT  double degToRad(double ang);

VKGEOMSHARED_EXPORT  double radToDeg(double ang);

VKGEOMSHARED_EXPORT  double sround(const double& );

struct Matrix4 /* 4-by-4 matrix */
{	
	double element[4][4];
};


VKGEOMSHARED_EXPORT  void inverse( Matrix4* in, Matrix4* out );
VKGEOMSHARED_EXPORT  void adjoint(Matrix4 *in, Matrix4 *out);
VKGEOMSHARED_EXPORT  double det2x2( double a, double b, double c, double d);
VKGEOMSHARED_EXPORT  double det3x3( double a1, double a2, double a3, double b1, double b2, double b3, double c1, double c2, double c3 );
VKGEOMSHARED_EXPORT  double det4x4( Matrix4 *m );

#endif /* _MMATH_H */
