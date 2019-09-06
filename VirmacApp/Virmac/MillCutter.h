// MillCutter.h: interface for the CMillCutter class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_MILLCUTTER_H__83FE0025_0DF6_44C7_AF54_1D1AEC9BE5D9__INCLUDED_)
#define AFX_MILLCUTTER_H__83FE0025_0DF6_44C7_AF54_1D1AEC9BE5D9__INCLUDED_

#include <VGLObject.h>
#include <Point3D.h>
#include <ListOfTriangle.h>
#include <Surface.h>

enum MillCutterType { MILL_BALL_NOSE, MILL_SPHERICAL, MILL_TOROIDAL, MILL_CYLINDRICAL };
enum ModelResolution { MODEL_LOW = 9, MODEL_MEDIUM = 18, MODEL_HIGH = 36 , MODEL_VERYHIGH = 72};

class MillingCutter : public VGLObject
{
    public:
    MillingCutter(const MillCutterType& typ	=   MILL_BALL_NOSE,
		const double& HolderDia	=   65,
		const double& HolderLen	=   80,
		const double& ShankDia	=   32,
		const double& ShankLen	=   30,
		const double& TaperDiaA	=   25,
		const double& TaperDiaB	=   32,
		const double& TaperLen	=   60,	
		const double& BodyDia	=   25,
		const double& BodyLen	=   25,
		const double& BallRad	=   12.5,
		const bool&	    tip		=   true
		);
    virtual ~MillingCutter();
	virtual VGLObject* Copy() const;
	virtual void DefineDisplay();
	virtual void Display(const GLDisplayMode& dMode = GLWIREFRAME);
	virtual void Hilight(const GLDisplayMode& dMode);

	void SetCutterType  (const MillCutterType& typ);
	void SetHolderDia   (const double& val);
	void SetHolderLen   (const double& val);
	void SetShankDia    (const double& val);
	void SetShankLen    (const double& val);
	void SetTaperDiaA   (const double& val);
	void SetTaperDiaB   (const double& val);
	void SetTaperLen    (const double& val);
	void SetBodyDia	    (const double& val);
	void SetBodyLen	    (const double& val);
	void SetBallRad	    (const double& val);

	virtual void SetColor(const GLubyte&, const GLubyte&, const GLubyte&);

	void SetResolution( const ModelResolution& res);

	MillCutterType GetCutterType() const { return itsType; }
	double GetHolderDia()	const { return	itsHolderDia;	}
	double GetHolderLen()	const { return	itsHolderLen;	}
	double GetShankDia()	const { return  itsShankDia;	}
	double GetShankLen()	const { return  itsShankLen;	}
	double GetTaperDiaA()	const { return  itsTaperDiaA;	}
	double GetTaperDiaB()	const { return  itsTaperDiaB;	}
	double GetTaperLen()	const { return  itsTaperLen;	}
	double GetBodyDia()	const { return  itsBodyDia;	}
	double GetBodyLen()	const { return  itsBodyLen;	}
	double GetBallRad()	const { return  itsBallRad;	}

	void MoveTo(const Point3D& P);
	void Rotate(double A, double B, double C);
	void SetTranslation(double X, double Y, double Z);
	void SetScale(double X, double Y, double Z);
	void SetRotation(double CX, double CY, double CZ, double RX, double RY, double RZ);
	void GetTranslation(double& X, double& Y, double& Z);
	void GetScale(double& X, double& Y, double& Z);
	void GetRotation(double& CX, double& CY, double& CZ, double& RX, double& RY, double& RZ);
	int NumTriangles() const { return numTriangles; }
	void ComputeBoundLimits();
	void RebuildDisplayLists();
    bool operator == (MillingCutter) const;
	double m_dOX;
	double m_dOY;
	double m_dOZ;
	ListOfTriangle* myTriangleList;
    private:
	void DrawWiredTool();
	void DrawShadedTool();
	void DrawHilitTool();
	void DoRotation();	
	void DrawTool();
	void InitDisplayLists();
	void BuildCollisionModel(const double& chordalError);
	void AddSurfaceTriangles(Surface* pSurf, const double& uParts, const double& vParts);
    private:
	GLint cutterList;

	MillCutterType itsType;
	ModelResolution itsResolution;

	double itsHolderDia;
	double itsHolderLen;
	double itsShankDia;
	double itsShankLen;
	double itsTaperDiaA;
	double itsTaperDiaB;
	double itsTaperLen;
	double itsBodyDia;
	double itsBodyLen;
	double itsBallRad;

	int numTriangles;

	bool	bTip;

	GLUquadricObj* ToolObj;

	double m_dTransX;
	double m_dTransY;
	double m_dTransZ;

	double m_dScaleX;
	double m_dScaleY;
	double m_dScaleZ;

	double m_dRotCX;
	double m_dRotCY;
	double m_dRotCZ;

	double m_dRotRX;
	double m_dRotRY;
	double m_dRotRZ;

	double m_dRotA;
	double m_dRotB;
	double m_dRotC;
};


#endif // !defined(AFX_MILLCUTTER_H__83FE0025_0DF6_44C7_AF54_1D1AEC9BE5D9__INCLUDED_)
