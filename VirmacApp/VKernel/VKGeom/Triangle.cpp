



#include "Triangle.h"
#include "MMath.h"

Triangle::Triangle()
{
    vArray[0] = Point3D(-1, -0.5, 0);
    vArray[1] = Point3D(1, -0.5, 0);
    vArray[2] = Point3D(0, 0.5, 0);
    geomType = CPOLYGON;
}

///Make a triqangle from three vertices
Triangle::Triangle(const Point3D& v1, const Point3D& v2, const Point3D& v3)
{
    vArray[0] = v1;
    vArray[1] = v2;
    vArray[2] = v3;
    geomType = CPOLYGON;
}

Triangle::Triangle(const Triangle& other) : Geometry()
{
    vArray[0] = other.vArray[0];
    vArray[1] = other.vArray[1];
    vArray[2] = other.vArray[2];
    geomType = CPOLYGON;
}

Triangle::~Triangle()
{
}

///Set Vertex --- Index >=1 <=3
void Triangle::SetVertex(const int& index, const Point3D& v)
{
    if(index < 1 || index > 3)
    {
	cout << "From CTriangle::SetVertex ---- Invalid Index\n";
	return;
    }
    vArray[index-1] = v;    
}

///Get Vertex --- Index >=1 <=3
Point3D Triangle::GetVertex(const int& index) const
{
    if(index < 1 || index > 3)
    {
	cout << "From CTriangle::GetVertex ---- Invalid Index....\nReturning First Vertex\n";
	return vArray[0];
    }
    else
	return vArray[index-1];
}

///Calculate the Normal Vector
Vector3D Triangle::Normal() const
{
    Vector3D V1(vArray[1], vArray[0]);
    Vector3D V2(vArray[1], vArray[2]);
    return V1.Crossed(V2);
}

/*
bool CTriangle::Intersect(const CTriangle& tri)
{
    CPoint3D st,en;
    double P1[3] = {vArray[0].GetX(), vArray[0].GetY(), vArray[0].GetZ()};
    double P2[3] = {vArray[1].GetX(), vArray[1].GetY(), vArray[1].GetZ()};
    double P3[3] = {vArray[2].GetX(), vArray[2].GetY(), vArray[2].GetZ()};

    double Q1[3] = {tri.GetVertex(1).GetX(), tri.GetVertex(1).GetY(), tri.GetVertex(1).GetZ()};
    double Q2[3] = {tri.GetVertex(2).GetX(), tri.GetVertex(2).GetY(), tri.GetVertex(2).GetZ()};
    double Q3[3] = {tri.GetVertex(3).GetX(), tri.GetVertex(3).GetY(), tri.GetVertex(3).GetZ()};

    double S[3] = {0,0,0}, E[3] = {0,0,0};
    int coplanar = 0;
    int res = tri_tri_intersection_test_3d(P1, P2, P3, Q1, Q2, Q3, &coplanar, S, E);
    st.SetParam(S[0], S[1], S[2]);
    en.SetParam(E[0], E[1], E[2]);   
    
    if(!res)
	return false;
    double d = st.Distance(en);
    if(d == 0)
	return false;
    return true;
}
*/

bool Triangle::operator == (const Triangle& p) const
{
    bool b = false;
    b = (vArray[0] == p.vArray[0] &&
	 vArray[1] == p.vArray[1] && 
	 vArray[2] == p.vArray[2]);
    return b;
}


///Translate this Triangle By Amount dx, dy ,dz
void Triangle::Translate(double dx, double dy, double dz)
{
    vArray[0].Translate(dx,dy,dz);
    vArray[1].Translate(dx,dy,dz);
    vArray[2].Translate(dx,dy,dz);
}

///Translate this Triangle Along Vector dir
void Triangle::Translate(const Vector3D& dir)
{
    vArray[0].Translate(dir);
    vArray[1].Translate(dir);
    vArray[2].Translate(dir);
}

///Translate this Triangle Along Vector Formed By O And D
void Triangle::Translate(const Point3D& O, const Point3D& D)
{
    vArray[0].Translate(O, D);
    vArray[1].Translate(O, D);
    vArray[2].Translate(O, D);
}

///Rotate this Triangle @ Ax By Angle ang(radians)
void Triangle::Rotate(const OneAxis& Ax, double ang)
{
    vArray[0].Rotate(Ax, ang);
    vArray[1].Rotate(Ax, ang);
    vArray[2].Rotate(Ax, ang);
}

///Scale this Triangle @ Point P By Factor fact
void Triangle::Scale(const Point3D& P, double fact)
{
    vArray[0].Scale(P, fact);
    vArray[1].Scale(P, fact);
    vArray[2].Scale(P, fact);
}

///Mirror this Triangle @ Point P
void Triangle::Mirror(const Point3D& P)
{
    vArray[0].Mirror(P);
    vArray[1].Mirror(P);
    vArray[2].Mirror(P);
}

///Mirror this Triangle @ Axis Ax
void Triangle::Mirror(const OneAxis& Ax)
{
    vArray[0].Mirror(Ax);
    vArray[1].Mirror(Ax);
    vArray[2].Mirror(Ax);
}

///Mirror this Triangle @ Plane P
void Triangle::Mirror(const Plane& P)
{
    vArray[0].Mirror(P);
    vArray[1].Mirror(P);
    vArray[2].Mirror(P);
}

