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

#include "forma.h"
#include "menu.h"

#include "shape_.h"
#include "shape_12.h"
#include "shape_34.h"
#include "shape_56.h"
#include "shape_7.h"
#include "shape_89.h"
#include "shape_a.h"
#include "shape_b.h"
#include "shape_cd.h"
#include "shape_e.h"

extern QTextStream std_out;
extern QTextStream std_in;

long  forma::forma_count = 0;

void forma::init_forma()
{
	++forma_count;
}

forma::forma ( void ) : parent ( 0 )
{
	init_forma();
}

forma::forma ( forma const & new_forma )
{
	init_forma();
	m_shapes.clear();
	m_shapes = new_forma.m_shapes;
	parent = new_forma.parent;
}

forma & forma::operator= ( forma const  & new_forma )
{
	init_forma();
	m_shapes.clear();
	m_shapes = new_forma.m_shapes;
	parent = new_forma.parent;
	return *this;
}

/**
Деструктор
*/
forma::~forma ( void )
{
	clear_m_shapes();
	--forma_count;
}

void forma::clear_m_shapes()
{
	for ( int i = 0;i < m_shapes.size();++i )
	{
		delete m_shapes.at ( i );
		m_shapes[i] = 0;
	}

	m_shapes.clear();
}

void forma::draw ( draw_vars &dr, stack & b, QGraphicsScene & sc )
{
	for ( int i = 0; i < m_shapes.size(); ++i )
	{
		m_shapes.at ( i ) -> draw ( dr, b, sc);
	}

	return ;
}

/**
Метод печати
*/
QString forma::out ( void ) const
{
	QString rez = QString ( "" );
	QString tmp = QString ( "" );

	for ( int i = 0; i < m_shapes.size(); ++i )
	{
		tmp = m_shapes.at ( i )->out ();
		rez += tmp;
	}

	rez += QString ( "0" );

	return rez;
}

/**
Возвращает длину формы.
*/
int forma::get_lenth ( void ) const
{
	int len;
	int rez = 1;

	for ( int i = 0; i < m_shapes.size(); ++i )
	{
		len = m_shapes.at ( i )-> get_lenth( );
		rez += len;
	}

	return  rez;
}

/**
Метод печати
*/
void forma::out_file ( FILE* du )
{
	/*	d_link *a = this;
		a->rewind_to_head ( a );

		while ( a->get_succ ( a ) )
		{
			if ( a->get ( a ) )
				( ( ( forma* ) a )->get ( a ) )->out_file ( du );

			a->stap_to_tail ( a );
		}

		if ( ( ( forma* ) a )->get ( a ) )
			( ( ( forma* ) a )->get ( a ) )->out_file ( du );
	*/
}

/*
void forma::edit ( draw_vars & dr, stack & st )
//Метод редактирования
{
	int rez 	=	0;
	int curr = 0; 					//Редактируемая подформа
	int tmp_size;
	shapes * sh ;

	do
	{
		std_out << "Position = " << curr << endl;
		std_out << out() << endl;
//		s_menu_form->run();
//		rez = s_menu_form->get_run_rez();

		switch ( rez )
		{

			case 0: //Edit
				m_shapes.at ( curr )->edit ( );
				break;

			case 1: //Draw var
				break;

			case 2: //Prev
				--curr;

				if ( curr < 0 )
					curr = 0;

				break;

			case 3: //Next
				tmp_size = m_shapes.size() - 1;

				if ( curr < tmp_size )
					++curr;

				break;

			case 4: //Home
				curr = 0;

				break;

			case 5: //En&d
				curr = m_shapes.size() - 1;

				if ( curr < 0 )
					curr = 0;

				break;

			case 6: //Ins pa&st
				sh = menu_shape_insert();

				if ( curr <= m_shapes.size() - 1 )
				{
					m_shapes.insert ( ++curr, sh );
				}

				else
				{
					curr = m_shapes.size();
					m_shapes.insert ( curr, sh );
				}

				sh->edit ( );

				break;

			case 7: //Ins befor
				sh = menu_shape_insert();

				m_shapes.insert ( curr, sh );

				sh->edit ( );

				break;

			case 8: //Dele&te
				break;

			case 9: //Backspace
				break;

			case 10://E&xit
				break;

			default :
				break;
		}
	}

	while ( rez != 10 );
}
*/


/*d_link* forma::create ( d_link * & )
//Выделить память под элемент списка.
{
	return ( d_link* ) new forma;
}
*/

/*
d_link* forma::copy ( d_link * &a )
//Скопировать подформу.
{
	a = this;
	shapes *sh = NULL;
	d_link * outl = NULL;
	d_link * out;
	a->rewind_to_head ( a );

	do
	{
		if ( ( ( forma* ) a )->get ( a ) )
		{
			if ( outl == 0 )
			{
				outl = new forma;
				sh = ( ( ( forma* ) a )->get ( a ) )->copy();
				outl->define ( sh, outl );
			}

			else
			{
				sh = ( ( ( forma* ) a )->get ( a ) )->copy();
				outl->insert_past ( sh, outl );
			}
		}

		out = a;

		a->stap_to_tail ( a );
	}

	while ( out->get_succ ( out ) );

	a = this;

	return outl;
}
*/

void forma::set_parent ( forma_l* new_parent )
{
	parent = new_parent;
}

forma_l*	forma::get_parent() const
{
	return parent;
}

//QList<shapes*>	forma::get_m_shapes() const
QList<shapes*>*	forma::get_m_shapes()
{
	return &m_shapes;
}

/*
shapes* forma::menu_shape_insert()
{

	int rez 	=	0;
	int curr = 0;
	shapes* new_shape = 0;

	do
	{
		std_out << out() << endl;
		switch ( rez )
		{

			case 0://Line
				new_shape = new shape_;
				break;

			case 1://Pen
				new_shape = new shape_12;

				break;

			case 2://Scale
				new_shape = new shape_34;
				break;

			case 3://Stack
				new_shape = new shape_56;
				break;

			case 4://Reference
				new_shape = new shape_7;
				break;

			case 5://Line_89
				new_shape = new shape_89;
				break;

			case 6://Octant_Arc
				new_shape = new shape_a;
				break;

			case 7://Arc
				new_shape = new shape_b;
				break;

			case 8://CurveLine_cd
				new_shape = new shape_cd;
				break;

			case 9://Vertical
				new_shape = new shape_e;
				break;

			default :
				break;
		}
	}

	while ( rez < 0 || rez > 9 );

	return new_shape;
}
*/
