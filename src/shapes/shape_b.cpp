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

#include "shape_b.h"
#include <math.h>
#include <QGraphicsPathItem>

#include "dialog_arc_digit_edit.h"
#include "main_form.h"

extern QTextStream std_out;
extern QTextStream std_in;
extern Main_Form	*theMainForm;

shape_b::shape_b ( void )
{
	m_bites.append ( 11 ); //Октантная дуга со смещением начала и конца
	m_bites.append ( 0 ); //start_offset 0-255
	m_bites.append ( 0 ); //end_offset 0-255
	m_bites.append ( 0 ); //hight_radius 0-255
	m_bites.append ( 1 ); //radius 0-255
	m_bites.append ( 0x00 );//(-)0SC: S 0-7 начальный октант. C количество октантов.
}

shape_b::shape_b ( int B1, int B2, int B3, int B4, int B5 )
{
	m_bites.append ( 11 ); //Октантная дуга со смещением начала и конца
	m_bites.append ( B1 );
	m_bites.append ( B2 );
	m_bites.append ( B3 );
	m_bites.append ( B4 );
	m_bites.append ( B5 );
}

shape_b::shape_b ( int Radius, int Start_angle, int End_angle , int Dir )
{
	m_bites.append ( 11 ); //Октантная дуга со смещением начала и конца
	m_bites.append ( 0 ); //start_offset 0-255
	m_bites.append ( 0 ); //end_offset 0-255
	m_bites.append ( 0 ); //hight_radius 0-255
	m_bites.append ( 1 ); //radius 0-255
	m_bites.append ( 0x00 );//(-)0SC: S 0-7 начальный октант. C количество октантов.
	set ( Radius, Start_angle, End_angle, Dir );
}

shape_b::~shape_b()
{
}


void shape_b::set_radius ( int Radius )
{
	if ( Radius < 0 )
		Radius = 1;

	Radius = cicle_range ( Radius, 1 , 256 * 256 );

	m_bites[3] = ( Radius >> 8 );

	m_bites[4] = Radius - m_bites[3] * 256;
}

int shape_b::get_radius ( void ) const
{
	return m_bites.at ( 3 ) *256 + m_bites.at ( 4 );
}

void shape_b::set_start ( int start_ang, int dir )
{
	int end_ang = get_end();
	int radius = get_radius();
	set ( radius , start_ang, end_ang, dir );
}

void shape_b::set_end ( int end_ang, int dir )
{
	int start_ang = get_start();
	int radius = get_radius();
	set ( radius , start_ang, end_ang, dir );
}

int shape_b::get_dir ( void ) const
{
	int Dir, SO;
	SO = m_bites.at ( 5 );

	if ( SO >= 0 )
		Dir = 1;
	else
		Dir = -1;

	return Dir;
}

void shape_b::draw ( draw_vars& dr, stack&, QGraphicsScene& sc)
{
  shapes* prev = get_prev();
  if(prev && prev->type()== QString("shape_e") && dr.drawAsHorisontal())
  {
    return;
  }
  
	if ( is_current() ) dr.draw_marker ( sc );

	draw_point p_start = dr.get_p_otn();    //Начальная точка дуги.
	draw_point p_delta;                  //Припащение до центра дуги.
	draw_point p_center;                  //Центр дуги.

	int ang_start = get_start();
	int ang_end = get_end();

	int ang_number = get_delta();

	int radius = get_radius();

	p_delta.x = -radius * cos ( M_PI * ang_start  / qreal ( 180 ) );
	p_delta.y = -radius * sin ( M_PI * ang_start  / qreal ( 180 ) );

	p_center = p_start + p_delta;

	p_delta.x = radius * cos ( M_PI * ang_end  / qreal ( 180 ) );
	p_delta.y = radius * sin ( M_PI * ang_end  / qreal ( 180 ) );

	dr.set_otn_coords ( p_center + p_delta );

	draw_point p_radius ( radius, radius );
	if (dr.drawWhisOutPenUpMovement() && !dr.get_pero()) ;
	else if ( is_current() )
	{
		QPen pen ( QBrush
		           ( QColor ( draw_vars::s_color_cur ), Qt::SolidPattern ),
		           qreal ( draw_vars::s_width_cur ) ,
		           Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );


		pen.setCosmetic ( true );
	{
			QPainterPath path;

			path.arcMoveTo ( p_center.x - p_radius.x , p_center.y - p_radius.y , p_radius.x * 2, p_radius.y * 2,  -ang_start );
			path.arcTo ( p_center.x - p_radius.x , p_center.y - p_radius.y , p_radius.x * 2, p_radius.y * 2,  -ang_start , -ang_number );

			QGraphicsPathItem *pathItem = new QGraphicsPathItem ( path );
			pathItem->setPen ( pen );
			sc.addItem ( pathItem );
		}
	}
	else if ( dr.get_pero() )
	{
		QPen pen ( QBrush
		           ( QColor ( draw_vars::s_color_pen_down ), Qt::SolidPattern ),
		           qreal ( draw_vars::s_width_pen_down ) ,
		           Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );

		pen.setCosmetic ( true );

		{
			QPainterPath path;

			path.arcMoveTo ( p_center.x - p_radius.x , p_center.y - p_radius.y , p_radius.x * 2, p_radius.y * 2,  -ang_start );
			path.arcTo ( p_center.x - p_radius.x , p_center.y - p_radius.y , p_radius.x * 2, p_radius.y * 2,  -ang_start , -ang_number );

			QGraphicsPathItem *pathItem = new QGraphicsPathItem ( path );
			pathItem->setPen ( pen );
			sc.addItem ( pathItem );
		}
	}
	else
	{
		QPen pen ( QBrush
		           ( QColor ( draw_vars::s_color_pen_up ), Qt::SolidPattern ),
		           qreal ( draw_vars::s_width_pen_up ) ,
		           Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );

		pen.setCosmetic ( true );

		{
			QPainterPath path;

			path.arcMoveTo ( p_center.x - p_radius.x , p_center.y - p_radius.y , p_radius.x * 2, p_radius.y * 2,  -ang_start );
			path.arcTo ( p_center.x - p_radius.x , p_center.y - p_radius.y , p_radius.x * 2, p_radius.y * 2,  -ang_start , -ang_number );

			QGraphicsPathItem *pathItem = new QGraphicsPathItem ( path );
			pathItem->setPen ( pen );
			sc.addItem ( pathItem );
		}
	}
}

QString shape_b::out ( void )
//Добавление символьного представления формы к стрингу
{
	QString rez;
	rez =
	    QString ( "(0" )
	    + QString::number ( m_bites.at ( 0 ), 16 ) + QString ( "," )
	    + QString::number ( m_bites.at ( 1 ) ) + QString ( "," )
	    + QString::number ( m_bites.at ( 2 ) ) + QString ( "," )
	    + QString::number ( m_bites.at ( 3 ) ) + QString ( "," )
	    + QString::number ( m_bites.at ( 4 ) ) + QString ( "," );

	if ( get_dir() == -1 )
	{
		rez += QString ( "-" );
	}

	rez += QString ( "0" );

	rez += QString::number ( abs ( m_bites.at ( 5 ) ), 16 ) + QString ( ")," );

	return rez;
}


QString shape_b::out_comment ( void )
{
	QString rez;
	rez = QString ( "shape_b" ) + QString ( ": " );
	rez += QString ( "radius" ) + QString ( "=" ) + QString::number ( get_radius() ) + QString ( "; " );
	rez += QString ( "start" ) + QString ( "=" ) + QString::number ( get_start() ) + QString ( "; " );
	rez += QString ( "end" ) + QString ( "=" ) + QString::number ( get_end() ) + QString ( "; " );
	rez += QString ( "direction" ) + QString ( "=" ) + QString::number ( get_dir() ) + QString ( "" );
	return rez;
}

int shape_b::get_lenth ( void )
//Возвращает длину подформы в байтах
{
	return 6;
}

void shape_b::edit ( void )
//Метод редактирования
{
	int radius = get_radius();
	int startDig = get_start();
	int endDig = get_end();
	int dir = get_dir();

	DialogArcDigitEdit dlgArcDigitEdit;
	dlgArcDigitEdit.set_shape ( this );

	QRect the_main_window_geom = theMainForm->frameGeometry ();
	int top = the_main_window_geom.top();
	int right = the_main_window_geom.right();

	dlgArcDigitEdit.move ( QPoint ( right, top ) );

	QObject::connect ( &dlgArcDigitEdit, SIGNAL ( arcDigitChanged() ), theMainForm, SLOT ( reDrawSlot() ) );	

	dlgArcDigitEdit.set_radius ( radius );
	dlgArcDigitEdit.set_startDigit ( startDig );
	dlgArcDigitEdit.set_endDigit ( endDig );

	if ( dir==1 )
		dlgArcDigitEdit.set_dirCounterClockwise ( true );
	else
		dlgArcDigitEdit.set_dirCounterClockwise ( false );


	dlgArcDigitEdit.exec();

	if(dlgArcDigitEdit.get_dirCounterClockwise(  ))
		dir=1;
	else
		dir=-1;

	QObject::disconnect ( &dlgArcDigitEdit, SIGNAL ( arcDigitChanged() ), theMainForm, SLOT ( reDrawSlot() ) );	
	
	set_radius ( dlgArcDigitEdit.get_radius() );
	set_start ( dlgArcDigitEdit.get_startDigit(), dir );
	set_end ( dlgArcDigitEdit.get_endDigit(), dir );
}

shapes* shape_b::copy ( void )
{
	shape_b * VVV = new shape_b;
	*VVV = *this;
	return VVV;
}


QString shape_b::type ( void ) const
{
  return QString ("shape_b");
}

void shape_b::set ( int r, int s, int e, int d )
{
	int r_big, r_small, s_oct, s_off, e_oct, e_off, o_oct;

	r_big = r / 256;
	r_small = r - r_big * 256;
	s_oct = cicle_range ( ( s + d * 360 ) / 45, 0, 8 );
	e_oct = cicle_range ( ( e - d * 360 ) / 45, 0, 8 );
	s_off = int ( cicle_range ( d * ( s - s_oct * 45 ), 0, 45 ) * 256. / 45. );
	e_off = int ( cicle_range ( d * ( e - e_oct * 45 ), 0, 45 ) * 256. / 45. );
	o_oct = cicle_range ( d * ( e_oct - s_oct ) , 0, 8 );

	m_bites[1] = s_off;
	m_bites[2] = e_off;
	m_bites[3] = r_big;
	m_bites[4] = r_small;
	m_bites[5] = d * ( s_oct * 16 + o_oct );
}

int shape_b::get_start ( void ) const
{
	int S_oct, O_oct, S_off, O_off, SO, dir;
	int start_ang;
	dir = get_dir();
	SO = m_bites.at ( 5 );
	S_off = m_bites.at ( 1 );
	O_off = m_bites.at ( 2 );
	S_oct = ( abs ( SO ) >> 4 ) & 0x7;
	O_oct = ( abs ( SO ) ) & 0x7;
	start_ang = int ( S_oct * 45 + dir * S_off * 45.0 / 256.0 + 0.5 );
	return start_ang;
}

int shape_b::get_end ( void ) const
{
	int S_oct, O_oct, S_off, O_off, SO, dir, E_off_ang;
	int E_oct, end_ang;
	dir = get_dir();
	SO = m_bites.at ( 5 );
	S_off = m_bites.at ( 1 );
	O_off = m_bites.at ( 2 );
	S_oct = ( abs ( SO ) >> 4 ) & 0x7;
	O_oct = ( abs ( SO ) ) & 0x7;
	E_off_ang = int ( O_off / 256.0 * 45.0 + 0.5 );
	if ( E_off_ang == 0 )
		E_oct = S_oct + O_oct * dir;
	else
		E_oct = S_oct + ( O_oct - 1 ) * dir;
	end_ang = cicle_range ( E_oct * 45 + dir * E_off_ang , 0 , 360 );
	return end_ang ;
}

int shape_b::get_delta ( void ) const
{
	int rez;
	int start = get_start();
	int end = get_end();
	int dir = get_dir();

	if ( dir > 0 )
	{
		if ( start == end )
		{
			rez = 360;
			return rez;
		}
		else if ( start < end )
		{
			rez = end - start;
			return rez;
		}
		else if ( start > end )
		{
			rez = 360 + end - start;
			return rez;
		}
	}

	if ( dir < 0 )
	{
		if ( start == end )
		{
			rez = 360;
			return rez;
		}
		else if ( start > end )
		{
			rez = end - start;
			return rez;
		}
		else if ( start < end )
		{
			rez = end - start - 360 ;
			return rez;
		}
	}
}

void shape_b::set_dir(int Dir)
{
	int radius=get_radius();
	int start=get_start();
	int end=get_end();
	if(Dir>=0)
		Dir=1;
	else
		Dir=-1;
	set(radius,start,end,Dir);	
}
