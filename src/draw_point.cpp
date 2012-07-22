/***************************************************************************
 *   Copyright (C) 2008 by Николай Матвеев                                 *
 *   mnasoft@gmail.com                                                     *
 *                                                                         *
 *   This program is free software; you can redistribute it and/or modify  *
 *   it under the terms of the GNU General Public License as published by  *
 *   the Free Software Foundation; either version 3 of the License, or     *
 *   (at your option) any later version.                                   *
 *                                                                         *
 *   This program is distributed in the hope that it will be useful,       *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of        *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the         *
 *   GNU General Public License for more details.                          *
 *                                                                         *
 *   You should have received a copy of the GNU General Public License     *
 *   along with this program; if not, write to the                         *
 *   Free Software Foundation, Inc.,                                       *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.             *
 ***************************************************************************/

#include "draw_point.h"
#include <math.h>

draw_point::draw_point ( void )
		: x ( 0 )
		, y ( 0 )
{
}

draw_point::draw_point ( qreal x, qreal y )
		: x ( x )
		, y ( y )
{
}

draw_point::draw_point ( const draw_point &p )
		: x ( p.x )
		, y ( p.y )
{
}

draw_point& draw_point::operator= ( const draw_point & p )
{
	x = p.x;
	y = p.y;
	return *this;
}

draw_point& draw_point::operator+= ( const draw_point & p )
{
	x += p.x;
	y += p.y;
	return *this;
}

draw_point& draw_point::operator-= ( const draw_point & p )
{
	x -= p.x;
	y -= p.y;
	return *this;
}

draw_point draw_point::operator+ ( const draw_point &dp ) const
{
	draw_point rez;
	rez.x = x + dp.x ;
	rez.y = y + dp.y ;
	return rez;
}

draw_point draw_point::operator- ( const draw_point &dp ) const
{
	draw_point rez;
	rez.x = x - dp.x ;
	rez.y = y - dp.y ;
	return rez;
}

draw_point draw_point::operator* ( qreal sc ) const
{
	draw_point rez;
	rez.x = x * sc ;
	rez.y = y * sc ;
	return rez;
}

draw_point draw_point::operator/ ( qreal sc ) const
{
	draw_point rez;
	rez.x = x / sc ;
	rez.y = y / sc ;
	return rez;
}

qreal draw_point::dist_sc ( const draw_point & pt ) const
{
	qreal rez;
	qreal dx = x - pt.x;
	qreal dy = y - pt.y;
	rez = dx * dx + dy * dy;
	return rez;
}

qreal draw_point::dist ( const draw_point & pt ) const
{
	return sqrt ( dist_sc ( pt ) );
}

qreal draw_point::agnle ( const draw_point & pt ) const
{
	qreal rez;
	draw_point delta = pt - ( *this );
	rez = atan2 ( delta.y, delta.x );
	return rez;
}

draw_point & draw_point::set ( qreal X, qreal Y )
{
	x = X;
	y = Y;
	return *this;
}

draw_point draw_point::polar ( qreal ang, qreal dist ) const
{
	draw_point rez ( dist*cos ( ang ), dist*sin ( ang ) );
	rez += *this;
	return rez;
}

qreal draw_point::dtr ( qreal digit )
{
	return M_PI*digit / qreal ( 180 );
}

qreal draw_point::rtd ( qreal radian )
{
	return qreal ( 180 ) *radian / M_PI;
}
