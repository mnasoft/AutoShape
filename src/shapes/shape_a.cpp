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

#include "shape_a.h"
#include <math.h>
#include <QGraphicsPathItem>

#include "dialog_arc_octant_edit.h"
#include "main_form.h"

extern QTextStream std_out;
extern QTextStream std_in;
extern Main_Form	*theMainForm;

shape_a::shape_a ( void )
{
	m_bites.append ( 10 ); //Октантная дуга
	m_bites.append ( 1 ); //Радиус октантной дуги
	m_bites.append ( 0x00 );
//Старший байт - начальный октант[0,7],
//младший байт количество октантов [0,7], 0 соответствует полной окружности
// знак определяет направление отрисовки:
// "+" - против часовой
// "-" - по часовой.
}

shape_a::shape_a ( int R, int S, int N )
{
	m_bites.append ( 10 ); //Октантная дуга
	m_bites.append ( 1 ); //Радиус октантной дуги
	m_bites.append ( 0x00 ); //Начало и направление

	set_radius ( R );
	set_start ( S );
	set_number ( N );
}

shape_a::shape_a ( int Bite_1, int Bite_2 )
{
	m_bites.append ( 10 ); //Октантная дуга
	m_bites.append ( Bite_1 ); //Радиус октантной дуги
	m_bites.append ( Bite_2 ); //Начало и направление
}

shape_a::~shape_a()
{
}

void shape_a::set_radius
( int Radius/**- содержит новое значение радиуса. Может принимать значение в диапазоне от 1 до 255*/
)
{
	if ( Radius < 0 )
		m_bites[1] = -Radius;
	else
		m_bites[1] = Radius;

	if ( m_bites[1] > 255 )
		m_bites[1] = 255;

	if ( m_bites[1] == 0 )
		m_bites[1] = 1;
}

int shape_a::get_radius ( void ) const
{
	return m_bites[1];
}

void shape_a::set_start 
( 
int Start /**- содержит новое значение начального октанта. Может принимать значение от 0 до 7*/
)
{
	Start = cicle_range ( Start, 0, 8 );

	int bite = m_bites[2];

	int direction;

	int start_octant;

	int num_octant;

	if ( bite > 0 )
	{
		direction = 1;
		bite = bite;
	}

	else
	{
		direction = -1;
		bite = -bite;
	}

	start_octant = bite >> 4;

	num_octant = bite - ( start_octant << 4 );

	bite = direction * ( ( Start << 4 ) + num_octant );

	m_bites[2] = bite ;
}

int shape_a::get_octant_start ( void ) const
{
	int bite = m_bites[2];
	int direction;
	int start_octant;
	int num_octant;

	if ( bite > 0 )
	{
		direction = 1;
		bite = bite;
	}

	else
	{
		direction = -1;
		bite = -bite;
	}

	start_octant = bite >> 4;

	num_octant = bite - ( start_octant << 4 );
	num_octant = num_octant * direction;
	return start_octant;
}

void shape_a::set_number 
( int Number /**- содержит новое значение количества октантов. Может принимать значение от -7 до 7*/
)
{
	int bite ;
	int direction;
	int start_octant;


	if ( Number <= -8 )
		Number = 0;

	if ( Number >= 8 )
		Number = 0;

	if ( Number > 0 )
	{
		direction = 1;
		Number = Number;
	}

	else
	{
		direction = -1;
		Number = -Number;
	}

	bite = m_bites[2];

	if ( bite > 0 )
		bite = bite;
	else
		bite = -bite;

	start_octant = bite >> 4;

	bite = direction * ( ( start_octant << 4 ) + Number );

	m_bites[2] = bite ;
}

int shape_a::get_octant_number ( void ) const
{
	int bite = m_bites[2];
	int direction;
	int start_octant;
	int num_octant;

	if ( bite > 0 )
	{
		direction = 1;
		bite = bite;
	}

	else
	{
		direction = -1;
		bite = -bite;
	}

	start_octant = bite >> 4;

	num_octant = bite - ( start_octant << 4 );
	num_octant = num_octant * direction;
	return num_octant;
}

int shape_a::get_octant_end ( void ) const
{
	int rez = get_octant_start() + get_octant_number();

	if ( rez >= 8 )
		rez -= 8;

	if ( rez < 0 )
		rez += 8;

	return rez;
}

void shape_a::draw ( draw_vars& dr, stack&, QGraphicsScene& sc )
{
  shapes* prev = get_prev();
  if(prev && prev->type()== QString("shape_e") && dr.drawAsHorisontal())
  {
    return;
  }
  
	if ( is_current() ) dr.draw_marker ( sc );

	draw_point p_start = dr.get_p_otn(); 			//Начальная точка дуги.
	draw_point p_delta;             					//Приращение до центра дуги.
	draw_point p_center;             					//Центр дуги.

	int oct_start = get_octant_start();
	int oct_end = get_octant_end();

	int oct_number = get_octant_number();

	if ( oct_number == 0 ) oct_number = 8;

	int radius = get_radius();

	p_delta.x = -radius * cos ( M_PI * oct_start * qreal ( 45 ) / qreal ( 180 ) );

	p_delta.y = -radius * sin ( M_PI * oct_start * qreal ( 45 ) / qreal ( 180 ) );

	p_center = p_start + p_delta;

	p_delta.x = radius * cos ( M_PI * oct_end * qreal ( 45 ) / qreal ( 180 ) );

	p_delta.y = radius * sin ( M_PI * oct_end * qreal ( 45 ) / qreal ( 180 ) );

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

			path.arcMoveTo ( p_center.x - p_radius.x , p_center.y - p_radius.y , p_radius.x * 2, p_radius.y * 2,  -oct_start*qreal ( 45 ) );
			path.arcTo ( p_center.x - p_radius.x , p_center.y - p_radius.y , p_radius.x * 2, p_radius.y * 2,  -oct_start*qreal ( 45 ), -oct_number*qreal ( 45 ) );

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

			path.arcMoveTo ( p_center.x - p_radius.x , p_center.y - p_radius.y , p_radius.x * 2, p_radius.y * 2,  -oct_start*qreal ( 45 ) );
			path.arcTo ( p_center.x - p_radius.x , p_center.y - p_radius.y , p_radius.x * 2, p_radius.y * 2,  -oct_start*qreal ( 45 ), -oct_number*qreal ( 45 ) );

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

			path.arcMoveTo ( p_center.x - p_radius.x , p_center.y - p_radius.y , p_radius.x * 2, p_radius.y * 2,  -oct_start*qreal ( 45 ) );
			path.arcTo ( p_center.x - p_radius.x , p_center.y - p_radius.y , p_radius.x * 2, p_radius.y * 2,  -oct_start*qreal ( 45 ), -oct_number*qreal ( 45 ) );

			QGraphicsPathItem *pathItem = new QGraphicsPathItem ( path );

			pathItem->setPen ( pen );
			sc.addItem ( pathItem );
		}
	}



}

QString shape_a::out ( void )
//Добавление символьного представления формы к стрингу
{
	QString rez;

	int bite_0 =  m_bites.at ( 0 );
	int bite_1 =  m_bites.at ( 1 );
	int bite_2 =  m_bites.at ( 2 );

	int radius = get_radius();
	int start = get_octant_start();
	int number = get_octant_number();
	int direction;

	if ( get_octant_number() < 0 )
		direction = -1;
	else
		direction = 1;

	if ( bite_2 >= 0 )
		rez = QString ( "(0" )
		      + QString::number ( m_bites.at ( 0 ), 16 )
		      + QString ( "," )
		      + QString::number ( m_bites.at ( 1 ), 10 )
		      + QString ( "," )
		      + QString ( "0" )
		      + QString::number ( bite_2, 16 )
		      + QString ( ")," );
	else
		rez = QString ( "(0" )
		      + QString::number ( m_bites.at ( 0 ), 16 )
		      + QString ( "," )
		      + QString::number ( m_bites.at ( 1 ), 10 )
		      + QString ( "," )
		      + QString ( "-0" )
		      + QString::number ( -bite_2, 16 )
		      + QString ( ")," );

	return rez;
}

int shape_a::get_lenth ( void )
//Возвращает длину подформы в байтах
{
	return 3;
}

QString shape_a::out_comment ( void )
{
	QString rez;
	rez = QString ( "shape_a" ) + QString ( ": " );
	rez += QString ( "radius" ) + QString ( "=" ) + QString::number ( get_radius() ) + QString ( "; " );
	rez += QString ( "start" ) + QString ( "=" ) + QString::number ( get_octant_start() ) + QString ( "; " );
	rez += QString ( "number" ) + QString ( "=" ) + QString::number ( get_octant_number() ) + QString ( "" );
	return rez;
}

void shape_a::edit ( void )
//Метод редактирования
{
	int radius = get_radius();
	int startOct = get_octant_start();
	int numberOct = get_octant_number();

	DialogArcOctantEdit dlgArcOctantEdit;
	dlgArcOctantEdit.set_shape ( this );

	QRect the_main_window_geom = theMainForm->frameGeometry ();
	int top = the_main_window_geom.top();
	int right = the_main_window_geom.right();

	dlgArcOctantEdit.move ( QPoint ( right, top ) );

	QObject::connect ( &dlgArcOctantEdit, SIGNAL ( arcOctantChanged() ), theMainForm, SLOT ( reDrawSlot() ) );

	dlgArcOctantEdit.set_radius ( radius );
	dlgArcOctantEdit.set_startOctant ( startOct );
	dlgArcOctantEdit.set_numberOctant ( numberOct );
	dlgArcOctantEdit.exec();

	QObject::disconnect ( &dlgArcOctantEdit, SIGNAL ( arcOctantChanged() ), theMainForm, SLOT ( reDrawSlot() ) );

	set_radius ( dlgArcOctantEdit.get_radius() );
	set_start ( dlgArcOctantEdit.get_startOctant() );
	set_number ( dlgArcOctantEdit.get_numberOctant() );
}

shapes* shape_a::copy ( void )
{
	shape_a * VVV = new shape_a;
	*VVV = *this;
	return VVV;
}

QString shape_a::type ( void ) const
{
  return QString ("shape_a");
}
