// NCBlock.h: interface for the CNCBlock class.
//
//////////////////////////////////////////////////////////////////////

#if !defined(AFX_NCBLOCK_H__932786D2_D796_45EA_93FA_5EC34884725A__INCLUDED_)
#define AFX_NCBLOCK_H__932786D2_D796_45EA_93FA_5EC34884725A__INCLUDED_

enum ARC_MODE {ARC_CCW, ARC_CW, ARC_STR};
enum G02_G03_Plane { G02_03_XOY=1, G02_03_YOZ, G02_03_ZOX };
enum DIM_Type { DIM_ABS, DIM_INC }; //Absolute Or Incremental G90/91
enum UNIT_Type { UNIT_INCH, UNIT_METRIC };
enum G02_G03_Type { IJK_TYPE, RAD_TYPE };
enum IJK_Type { CENTER_ABS, CENTER_START, CENTER_END };
enum SPINDLE { SPDL_CW, SPDL_CCW, SPDL_STOP };

class NCBlock  
{
public:
	NCBlock();
	virtual ~NCBlock();
public:
	float A;
	float B;
	float C;
	float D;
	float E;
	unsigned F;
	unsigned G;
	unsigned H;
	float I;
	float J;
	float K;
	float L;
	unsigned M;
	unsigned long N;
	unsigned O;
	float P;
	float Q;
	float R;
	unsigned S;
	unsigned T;
	float U;
	float V;
	float W;
	float X;
	float Y;
	float Z;
	float DX;
	float DY;
	float DZ;

	ARC_MODE myArcMode;
	DIM_Type myDimType;
	UNIT_Type myUnitType;
	G02_G03_Type myCircType;
	IJK_Type myIJKType;
	SPINDLE mySpindleCondition;
};

#endif // !defined(AFX_NCBLOCK_H__932786D2_D796_45EA_93FA_5EC34884725A__INCLUDED_)
