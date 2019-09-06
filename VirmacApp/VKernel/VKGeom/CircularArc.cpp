// Arc.cpp: implementation of the CArc class.
////////////////////////////////////////////////////////////////////////


#include "CircularArc.h"
#include "MMath.h"
//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////
CircularArc::CircularArc(int plane, const Point3D& P1, const Point3D& P2, const Point3D& Cen, double step, bool clock)
{
    double tot_ang = 0.0, ang = 0.0 ;
    double a[4] , b[4], nfsec=0,temp=0,temp_1=0,temp_2=0 ;
    int nsec = 0 , i=0;	double ac=0,cb=0;
    double prevx=0,prevy=0,prevz=0;	double compang = 0.0 ;
    double xi, yi, zi, xj, yj, zj, I, J, K, px=0, py=0, pz=0;
    ArcPoints = new ListOfPoint3D;
    xi = P1.GetX();    yi = P1.GetY();    zi = P1.GetZ();
    xj = P2.GetX();    yj = P2.GetY();    zj = P2.GetZ();
    I = Cen.GetX();	J = Cen.GetY();	K = Cen.GetZ();
    a[0] = xi - I ;	a[1] = yi - J ;	a[2] = zi - K ;	a[3] = sqrt( pow(a[0],2) + pow(a[1],2) + pow(a[2],2));
    b[0] = xj - I ;	b[1] = yj - J ;	b[2] = zj - K ;	b[3] = sqrt( pow(b[0],2) + pow(b[1],2) + pow(b[2],2) );
    temp_1 = a[0]*b[0] + a[1]*b[1] + a[2]*b[2] ;
    temp_2 = a[3]*b[3] ;
    tot_ang = acos(temp_1/temp_2);
    step =  2 * ( acos ( ( a[3] - step ) / a[3] ) );
    nfsec = tot_ang/step ;    nsec = (int)(tot_ang/step) ;
    temp = 1-(nfsec - nsec) ;    nsec = nsec + 1 ;
    if  ( temp != 0.0 )
    {
        compang = temp * (step);
        step = -((step) - ( compang / nsec ));
    }
    if(plane == 3)
	clock = !clock;
    if( clock == false)
        step = -step;
    ang = step ;
    //XOY plane
    if(plane == 1)
    {
        ArcPoints->Clear();
        do{
            px = xi*cos(ang) - yi*sin(ang) - I*(cos(ang)-1)+ J*sin(ang) ;
            py = xi*sin(ang) + yi*cos(ang) - I*sin(ang) - J*(cos(ang) - 1 );
            pz = zi ;
            Point3D aPnt;
            aPnt.SetParam(px, py, pz);
            ArcPoints->Append(aPnt);
            ang = ang + step;
            if(i == 0)
            {
                ac = sqrt( pow((xi-px),2) + pow((yi-py),2) + pow((zi-pz),2));
                cb = sqrt( pow((xj-px),2) + pow((yj-py),2) + pow((zj-pz),2));
            }
            else
            {
                ac = sqrt( pow((px-prevx),2) + pow((py-prevy),2) + pow((pz-prevz),2));
                cb = sqrt( pow((xj-px),2) + pow((yj-py),2) + pow((zj-pz),2));
            }
            if(ac == 0 || tot_ang < 0.001)
                break;
            prevx = px;
            prevy = py;
            prevz = pz;
            ++i;
        }while (cb >= ac);
    }
}

CircularArc::~CircularArc()
{
    if(ArcPoints)
    {
        ArcPoints->Clear();
        delete ArcPoints;
    }
}
