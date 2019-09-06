// GeomException.cpp: implementation of the CGeomException class.
//
//////////////////////////////////////////////////////////////////////

#include "GeomException.h"
#include "MMath.h"

//////////////////////////////////////////////////////////////////////
// Construction/Destruction
//////////////////////////////////////////////////////////////////////

GeomException::GeomException()
{

}

GeomException::GeomException(ErrorType type)
{
    switch (static_cast<int>(type))
	{
		case DivideByZero:
			msg = "\nDivide By Zero Raised!\n";
			break;
		case ConstructionFailure:
			msg = "\nConstruction Failure Raised!\n";
			break;
		case MaxDegree:
			msg = "\nDegree Greater Than Maximum Degree Allowed!\n";
				break;
		default:
			break;
	}
}

GeomException::~GeomException()
{
}

std::string GeomException::ErrorMessage() const
{
	return msg;
}

