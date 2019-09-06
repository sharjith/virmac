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
 *            Conic.h
 *
 *  Thu Jun 29 22:12:19 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _CONIC_H
#define _CONIC_H

#include "VKGeom.h"

#include "Curve.h"
#include "AxisSystem.h"

class Point3D;

//Abstract Base Class  For Circle, Ellipse, Parabola and Hyperbola
class VKGEOMSHARED_EXPORT Conic : public Curve
{
public:
	Conic();
	virtual ~Conic();
	virtual void Reverse();
	void SetLocation(const AxisSystem& ax);
	virtual Point3D PointAtPara(const double& para) = 0;
	virtual double FirstParameter() const = 0;
	virtual double LastParameter() const = 0;
	virtual double Eccentricity() const = 0;
	virtual bool IsClosed() const = 0;
    virtual Curve* Copy() const = 0;
protected:
	AxisSystem itsLocation;
};

#endif /* _CONIC_H */
