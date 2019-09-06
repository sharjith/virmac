// Helix.h: interface for the CHelix class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_HELIX_H__8195CAF2_E922_4631_8E35_AD84A07EE6A1__INCLUDED_)
#define AFX_HELIX_H__8195CAF2_E922_4631_8E35_AD84A07EE6A1__INCLUDED_

#if _MSC_VER > 1000
#pragma once
#endif // _MSC_VER > 1000

#include "VKGeom.h"

#include "Circle3D.h"
#include "AxisSystem.h"

class VKGEOMSHARED_EXPORT Helix : public Circle3D
{
public:
    Helix(const AxisSystem& Ax, const double& radius, const double& start, const double& end, const double lead);
    virtual ~Helix();
	virtual void Reverse();
	virtual Point3D PointAtPara(const double& para);
	virtual double FirstParameter() const;
	virtual double LastParameter() const;
	virtual bool IsClosed() const;
	CurveType Type() const;
	bool IsOfType(const CurveType&) const;
	virtual Curve* Copy() const;
	virtual void Translate(double dx, double dy, double dz);
	virtual void Translate(const Vector3D&);
	virtual void Translate(const Point3D&, const Point3D&);
    virtual void Rotate(const OneAxis&, double);
	virtual void Scale(const Point3D&, double);
	virtual void Mirror(const Point3D&);
    virtual void Mirror(const OneAxis&);
    virtual void Mirror(const Plane&);
	double Lead() const { return itsLead;}
private:
	//CAxisSystem itsLocation;
	//double itsRadius;
	double itsFirstParameter;
	double itsLastParameter;
	double itsLead;
};

#endif // !defined(AFX_HELIX_H__8195CAF2_E922_4631_8E35_AD84A07EE6A1__INCLUDED_)
