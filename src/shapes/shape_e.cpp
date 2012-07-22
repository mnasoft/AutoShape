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

#include "shape_e.h"

extern QTextStream std_out;
extern QTextStream std_in;

shape_e::shape_e ( void )
{
    m_bites.append ( 14 );
}

shape_e::~shape_e()
{
}

void shape_e::draw (draw_vars & dr, stack &, QGraphicsScene & sc)
{
    /**todo: Переопределить в зависивости от типа отрисовки символа (горизонтальный или вертикальный) */
    if (dr.drawWhisOutPenUpMovement() ) ;
    else if ( is_current() )
        dr.draw_marker ( sc );
}

int shape_e::get_lenth ( void )
//Возвращает длину подформы в байтах
{
    return 1;
}

QString shape_e::out ( void )
//Добавление символьного представления формы к стрингу
{
    return QString ("0e,");
}

void shape_e::edit ( void)
{
}

QString shape_e::out_comment ( void )
{
    QString rez;
    rez = QString ( "shape_e" ) + QString ( "\n" );
    return rez;
}

shapes* shape_e::copy ( void )
{
    shape_e * VVV = new shape_e;
    *VVV = *this;
    return VVV;
}

QString shape_e::type ( void ) const
{
  return QString ("shape_e");
}

// kate: indent-mode cstyle; space-indent on; indent-width 0; 
