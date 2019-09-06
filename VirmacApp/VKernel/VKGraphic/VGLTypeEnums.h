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
 *            GLTypeEnums.h
 *
 *  Thu Jun 29 23:01:46 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _GLTYPEENUMS_H
#define _GLTYPEENUMS_H

typedef enum  { GLTOPVIEW, GLBOTTOMVIEW, GLFRONTVIEW, GLBACKVIEW,
    GLLEFTVIEW, GLRIGHTVIEW, GLAXONVIEW, GLUNDEFINEDVIEW} GLViewType;

//Every CGLObject created in the context must have a unique id;
typedef enum { GLCURVE = 123456, GLFONT = 234561, 
    GLPLANE = 345612, GLPOINT = 456123, 
    GLSURFACE = 561234, GLTRIHEDRON = 612345, 
    GLAXIS = 876543, GLONEAXIS = 765432, GLCUTTER = 876543, GLSIRUS = 987654} GLObjectType;

//Somehow I dont like the GL_POINTS primitive of OpenGL
//So creating some markers for point display
typedef enum { MARKER_POINT, MARKER_PLUS, MARKER_CROSS, MARKER_STAR, MARKER_CIRCLE } GLPointMarker;

typedef enum { LINE_SOLID, LINE_DOTTED, LINE_DASHED, LINE_DASHDOTTED } GLLineStyle;

typedef enum { GLSHADED, GLWIREFRAME, GLHLREMOVED } GLDisplayMode;

// Some Standard Materials
// P_ prefix denotes Polished
typedef enum {ALUMINIUM, BRASS, BRONZE, P_BRONZE, CHROME, COPPER, P_COPPER, GOLD, P_GOLD,
    PEWTER, SILVER, P_SILVER, STEEL, EMERALD, JADE, OBSIDIAN, PEARL, RUBY, TURQUOISE, PLASTIC, 
    RUBBER, BLACK_PLASTIC, BLACK_RUBBER, DEFAULT} GLMaterialName;

#endif /* _GLTYPEENUMS_H */
