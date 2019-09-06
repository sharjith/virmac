/***************************************************************************
  GLMaterials.cpp  -  description
  -------------------
begin                : Sun Mar 6 2005
copyright            : (C) 2005 by Sharjith
email                : sharjith_ssn@hotmail.com
 ***************************************************************************/

/***************************************************************************
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 2 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 ***************************************************************************/

#include "VGLMaterial.h"

VGLMaterial::VGLMaterial()
{
    Init(ALUMINIUM);
}

VGLMaterial::VGLMaterial(const GLMaterialName& mat)
{
    Init(mat);
}

void VGLMaterial::SetName(const GLMaterialName& mat)
{
    Init(mat);
}

void VGLMaterial::SetAmbient(const VGLColor& aCol)
{
    myAmbient = aCol;
}

void VGLMaterial::SetDiffuse(const VGLColor& aCol)
{
    myDiffuse = aCol;
}

void VGLMaterial::SetSpecular(const VGLColor& aCol)
{
    mySpecular = aCol;
}

void VGLMaterial::SetAmbientCoeff(const float& aVal)
{
    myAmbientCoeff = aVal;
}

void VGLMaterial::SetDiffuseCoeff(const float& aVal)
{
    myDiffuseCoeff = aVal;
}

void VGLMaterial::SetSpecularCoeff(const float& aVal)
{
    mySpecularCoeff = aVal;
}

void VGLMaterial::SetShininessCoeff(const float& aVal)
{
    myShininessCoeff = aVal;
}


VGLColor VGLMaterial::GetAmbient()	    const
{
    return myAmbient;
}

VGLColor VGLMaterial::GetDiffuse()	    const
{
    return myDiffuse;
}

VGLColor VGLMaterial::GetSpecular()	    const
{
    return mySpecular;
}

float	 VGLMaterial::GetAmbientCoeff()	    const
{
    return myAmbientCoeff;
}

float	 VGLMaterial::GetDiffuseCoeff()	    const
{
    return myDiffuseCoeff;
}

float	 VGLMaterial::GetSpecularCoeff()    const
{
    return mySpecularCoeff;
}

float	 VGLMaterial::GetShininessCoeff()   const
{
    return myShininessCoeff;
}

void VGLMaterial::Init(const GLMaterialName& mat)
{
    switch(mat)
    {
	//Non Metals
	case EMERALD:
	    myMaterialName = EMERALD;
	    myAmbient.SetValues(0.021500f, 0.174500f, 0.021500f);
	    myDiffuse.SetValues(0.075680f, 0.614240f, 0.075680f);
	    mySpecular.SetValues(0.633000f, 0.727811f, 0.633000f);
	    myAmbientCoeff =	0.550000f;
	    myDiffuseCoeff =	0.550000f;
	    mySpecularCoeff =	0.550000f;
	    myShininessCoeff =	76.800003f;
	    break;
	case JADE:
	    myMaterialName = JADE;
	    myAmbient.SetValues(0.135000f, 0.222500f, 0.157500f);
	    myDiffuse.SetValues(0.540000f, 0.890000f, 0.630000f);
	    mySpecular.SetValues(0.316228f, 0.316228f, 0.316228f);
	    myAmbientCoeff =	0.950000f;
	    myDiffuseCoeff =	0.950000f;
	    mySpecularCoeff =	0.950000f;
	    myShininessCoeff =	12.800000f;
	    break;
	case OBSIDIAN:
	    myMaterialName = OBSIDIAN;
	    myAmbient.SetValues(0.053750f, 0.050000f, 0.066250f);
	    myDiffuse.SetValues(0.182750f, 0.170000f, 0.225250f);
	    mySpecular.SetValues(0.332741f, 0.328634f, 0.346435f);
	    myAmbientCoeff =	0.820000f;
	    myDiffuseCoeff =	0.820000f;
	    mySpecularCoeff =	0.820000f;
	    myShininessCoeff =	38.400002f;
	    break;
	case PEARL:
	    myMaterialName = PEARL;
	    myAmbient.SetValues(0.250000f, 0.207250f, 0.207250f);
	    myDiffuse.SetValues(1.000000f, 0.829000f, 0.829000f);
	    mySpecular.SetValues(0.296648f, 0.296648f, 0.296648f);
	    myAmbientCoeff =	0.922000f;
	    myDiffuseCoeff =	0.922000f;
	    mySpecularCoeff =	0.922000f;
	    myShininessCoeff =	11.264000f;
	    break;
	case PEWTER:
	    myMaterialName = PEWTER;
	    myAmbient.SetValues(0.105882f, 0.058824f, 0.113725f);
	    myDiffuse.SetValues(0.427451f, 0.470588f, 0.541176f);
	    mySpecular.SetValues(0.333333f, 0.333333f, 0.521569f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	9.846150f;
	    break;
	case RUBY:
	    myMaterialName = RUBY;
	    myAmbient.SetValues(0.174500f, 0.011750f, 0.011750f);
	    myDiffuse.SetValues(0.614240f, 0.041360f, 0.041360f);
	    mySpecular.SetValues(0.727811f, 0.626959f, 0.626959f);
	    myAmbientCoeff =	0.550000f;
	    myDiffuseCoeff =	0.550000f;
	    mySpecularCoeff =	0.550000f;
	    myShininessCoeff =	76.800003f;
	    break;
	case TURQUOISE:
	    myMaterialName = TURQUOISE;
	    myAmbient.SetValues(0.100000f, 0.187250f, 0.174500f);
	    myDiffuse.SetValues(0.396000f, 0.741510f, 0.691020f);
	    mySpecular.SetValues(0.297254f, 0.308290f, 0.306678f);
	    myAmbientCoeff =	0.800000f;
	    myDiffuseCoeff =	0.800000f;
	    mySpecularCoeff =	0.800000f;
	    myShininessCoeff =	12.800000f;
	    break;
	case PLASTIC:
	    myMaterialName = PLASTIC;
	    myAmbient.SetValues(0.5000000f, 0.5000000f, 0.5000000f);
	    myDiffuse.SetValues(0.25000f, 0.25000f, 0.25000f);
	    mySpecular.SetValues(0.00000f, 0.00000f, 0.00000f);
	    myAmbientCoeff =	0.500000f;
	    myDiffuseCoeff =	0.240000f;
	    mySpecularCoeff =	0.060000f;
	    myShininessCoeff =	125.0f;
	    break;
	case RUBBER:
	    myMaterialName = RUBBER;
	    myAmbient.SetValues(0.020000f, 0.020000f, 0.020000f);
	    myDiffuse.SetValues(0.010000f, 0.010000f, 0.010000f);
	    mySpecular.SetValues(0.400000f, 0.400000f, 0.400000f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	10.000000f;
	    break;
	    //Metals
	case ALUMINIUM:
	    myMaterialName = ALUMINIUM;
	    myAmbient.SetValues(0.300000f, 0.300000f, 0.300000f);
	    myDiffuse.SetValues(0.300000f, 0.300000f, 0.300000f);
	    mySpecular.SetValues(0.700000f, 0.700000f, 0.800000f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	11.520000f;
	    break;
	case BRASS:
	    myMaterialName = BRASS;
	    myAmbient.SetValues(1.000000f, 0.76862745f, 0.31764706f);
	    myDiffuse.SetValues(1.000000f, 0.69000000f, 0.00000000f);
	    mySpecular.SetValues(1.000000f, 0.98000000f, 0.78000000f);
	    myAmbientCoeff =	0.300000f;
	    myDiffuseCoeff =	1.400000f;
	    mySpecularCoeff =	1.900000f;
	    myShininessCoeff =	8.0000000f;
	    break;
	case BRONZE:
	    myMaterialName = BRONZE;
	    myAmbient.SetValues(0.212500f, 0.127500f, 0.054000f);
	    myDiffuse.SetValues(0.714000f, 0.428400f, 0.181440f);
	    mySpecular.SetValues(0.393548f, 0.271906f, 0.166721f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	25.600000f;
	    break;
	case P_BRONZE:
	    myMaterialName = P_BRONZE;
	    myAmbient.SetValues(0.250000f, 0.148000f, 0.064750f);
	    myDiffuse.SetValues(0.400000f, 0.236800f, 0.103600f);
	    mySpecular.SetValues(0.774597f, 0.458561f, 0.200621f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	76.800003f;
	    break;
	case CHROME:
	    myMaterialName = CHROME;
	    myAmbient.SetValues(0.350000f, 0.350000f, 0.350000f);
	    myDiffuse.SetValues(0.400000f, 0.400000f, 0.400000f);
	    mySpecular.SetValues(0.974597f, 0.974597f, 0.974597f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	12.800000f;
	    break;
	case COPPER:
	    myMaterialName = COPPER;
	    myAmbient.SetValues(0.330000f, 0.260000f, 0.230000f);
	    myDiffuse.SetValues(0.500000f, 0.110000f, 0.000000f);
	    mySpecular.SetValues(0.950000f, 0.730000f, 0.000000f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	119.04000f;
	    break;
	case P_COPPER:
	    myMaterialName = P_COPPER;
	    myAmbient.SetValues(0.229500f, 0.088250f, 0.027500f);
	    myDiffuse.SetValues(0.550800f, 0.211800f, 0.066000f);
	    mySpecular.SetValues(0.580594f, 0.223257f, 0.069570f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	52.200001f;
	    break;
	case GOLD:
	    myMaterialName = GOLD;
	    myAmbient.SetValues(0.329412f, 0.223529f, 0.027451f);
	    myDiffuse.SetValues(0.780392f, 0.568627f, 0.113725f);
	    mySpecular.SetValues(0.992157f, 0.941176f, 0.807843f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	27.897400f;
	    break;
	case P_GOLD:
	    myMaterialName = P_GOLD;
	    myAmbient.SetValues(0.247250f, 0.224500f, 0.064500f);
	    myDiffuse.SetValues(0.346150f, 0.314300f, 0.090300f);
	    mySpecular.SetValues(0.797357f, 0.723991f, 0.208006f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	83.199997f;
	    break;
	case SILVER:
	    myMaterialName = SILVER;
	    myAmbient.SetValues(0.19225f, 0.19225f, 0.19225f);
	    myDiffuse.SetValues(0.50754f, 0.50754f, 0.50754f);
	    mySpecular.SetValues(0.508273f, 0.508273f, 0.508273f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	25.600000f;
	    break;
	case P_SILVER:
	    myMaterialName = P_SILVER;
	    myAmbient.SetValues(0.231250f, 0.231250f, 0.231250f);
	    myDiffuse.SetValues(0.277500f, 0.277500f, 0.277500f);
	    mySpecular.SetValues(0.773911f, 0.773911f, 0.773911f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	89.599998f;
	    break;
	case STEEL:
	    myMaterialName = STEEL;
	    myAmbient.SetValues(0.200000f, 0.200000f, 0.200000f);
	    myDiffuse.SetValues(0.000000f, 0.000000f, 0.000000f);
	    mySpecular.SetValues(1.000000f, 1.000000f, 1.000000f);
	    myAmbientCoeff =	0.010000f;
	    myDiffuseCoeff =	0.020000f;
	    mySpecularCoeff =	0.980000f;
	    myShininessCoeff =	7.6800000f;
	    break;
	default:
	    myMaterialName = DEFAULT;
	    myAmbient.SetValues(0.500000f, 0.500000f, 0.500000f);
	    myDiffuse.SetValues(0.300000f, 0.300000f, 0.300000f);
	    mySpecular.SetValues(0.700000f, 0.700000f, 0.700000f);
	    myAmbientCoeff =	1.000000f;
	    myDiffuseCoeff =	1.000000f;
	    mySpecularCoeff =	1.000000f;
	    myShininessCoeff =	128.00000f;
	    break;
    }
}

