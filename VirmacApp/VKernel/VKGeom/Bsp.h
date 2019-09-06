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
 *            Bsp.h
 *
 *  Thu Jun 29 22:08:13 2006
 *  Copyright  2006  N. Sharjith
 *  sharjith@gmail.com
 ****************************************************************************/


#ifndef _BSP_H
#define _BSP_H

#include "VKGeom.h"

struct point
{
  double x;
  double y;
  double z;
};

VKGEOMSHARED_EXPORT  void compute_intervals(int *u, int n, int t);
VKGEOMSHARED_EXPORT  double blend(int k, int t, int *u, double v);
VKGEOMSHARED_EXPORT  void compute_point(int *u, int n, int t, double v, point *control,
		   point *output);
VKGEOMSHARED_EXPORT  void bspline(int n, int t, point *control, point *output, int num_output);

#endif /* _BSP_H */
