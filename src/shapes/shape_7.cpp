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

#include "shape_7.h"

extern QTextStream std_out;
extern QTextStream std_in;

/*
	char *ref_name="&Reference&~Number&~ASCII";
	menu ref(65,0,		 // X, Y
		14,  1,         // Normal For Back
		12,             // Heat char
		2,  14,         // Choise For Back
		8,              // Shadow
		14,  2,         // Header For Back
		0,              // Frozen For
		2, 1,           // Shadow Displacement dX dY
		1,              // Is mouse present ?
		ref_name);          // Init string
*/

shape_7::shape_7 ( void )
{
    m_bites.append ( 7 );  //Перо опущено
    m_bites.append ( 10 ); //Перо опущено
}

shape_7::shape_7 ( int ref_number )
{
    m_bites.append ( 7 );  //Перо опущено
    m_bites.append ( ref_number ); //Перо опущено
}

shape_7::~shape_7()
{
}

void shape_7::set_ref_number ( int ref_number )
{
    m_bites[1] = ref_number;
}

int shape_7::get_ref_number ( void )
{
    return m_bites[1];
}

void shape_7::draw ( draw_vars & dr, stack &, QGraphicsScene & sc, int , int, int )
// Рисовать форму
{
  shapes* prev = get_prev();
  if(prev && prev->type()== QString("shape_e") && dr.drawAsHorisontal())
  {
    return;
  }
  //@todo ;lkasf;l 
    if ( is_current() ) dr.draw_marker ( sc );
    /*
    	d_link *non = 0;
    	shapes::draw ( a, st, 0, 0, 0, non, non );
    	draw_vars draw = a;
    	d_link* _forma_l = ( d_link* ) ( fon->get ( fon ) );

    	if ( ( ( forma_l* ) _forma_l )->find ( _forma_l, var ) )
    	{
    		( ( forma_l* ) _forma_l )->draw ( fon, a, st );
    	}

    	return draw;
    */
}

///Возвращает длину подформы в байтах
int shape_7::get_lenth ( void )
{
    return 2;
// todo: Переопределить возвтащаемое значение функции в зависимости от типа шрифта.
}

QString shape_7::out ( void )
//Добавление символьного представления формы к стрингу
{
    QString rez;
    rez = QString ("(0")+QString::number ( m_bites.at ( 0 ), 16 ) + QString ( "," ) + QString::number ( m_bites.at ( 1 ), 10 ) + QString ( ")," );
    return rez;
}

QString shape_7::out_comment ( void )
{
    QString rez;
    rez = QString ( "shape_7" ) + QString ( ": " );

    rez += QString ( "number" ) + QString ( "=" ) + QString::number ( get_ref_number () ) + QString ( "" );

    return rez;
}

void shape_7::edit ( void )
//Метод редактирования
{
    int do_while;
    int menu;
    int ref_number = get_ref_number();
    int value;

    do
    {
        std_out << endl << endl << out_comment() << endl;
        std_out
        << "shape_7 menu:" << "\n"
        << "0     - save & exit" << "\n"
        << "1     - set shape number" << "\n"
        << "9     - cancel  & exit" <<  "\n"
        << "Enter value:";
        std_out.flush();
        std_in >> menu;

        switch ( menu )
        {

        case 0:
            do_while = 0;
            break;

        case 1:
            do_while = 1;
            std_out
            << "Enter reference number (from 1 to 256):";
            std_out.flush();
            std_in >> value;
            set_ref_number ( value );
            break;

        case 9:
            do_while = 0;
            set_ref_number ( ref_number );
            break;

        default:
            do_while = 0;
            break;
        }
    }

    while ( do_while );

    std_out << out_comment() << endl;
}

shapes* shape_7::copy ( void )
{
    shape_7 * VVV = new shape_7;
    *VVV = *this;
    return VVV;
}

QString shape_7::type ( void ) const
{
  return QString ("shape_7");
}

// kate: indent-mode cstyle; space-indent on; indent-width 0; 
