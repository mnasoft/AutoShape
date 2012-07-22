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

#include "menu.h"
#include "draw_var.h"
#include "font.h"
#include "stack.h"
#include "strings.h"
#include "shapes.h"
#include "main_form.h"

extern QTextStream std_out;
extern QTextStream std_in;

extern Main_Form	*theMainForm;

int shapes::s_size							=	7;
int long shapes::s_shapes_count	= 0;

shapes::shapes ( void )
        : m_parent ( 0 )
{
    ++s_shapes_count;
}

shapes::~shapes ( void )
{
    --s_shapes_count;
    m_bites.clear();
}

/**
Печатает подформу в символьном представлении.
*/
void shapes::print ( void )

{
    std_out << out() << endl;
}

/**
			Рисовать форму
*/
void shapes::draw ( draw_vars & dr, stack &, QGraphicsScene & sc)
{
    return ;
}

bool shapes::is_current ( void ) const
{
    if ( !theMainForm )
        return false;
    shapes* test=theMainForm->get_p_current_shape();
    if (test==this)
        return true;
    else
        return false;
}

bool shapes::is_type_equal ( const QString & a_Type)
{
  return (type() == a_Type);
}


/**Если у подформы нет родителя или у родителя отсутствует предыдущий элемент возвращает 0.
 * Если у подформы есть родитель и у родителя присутствует предыдущий элемент возвращает указатель на его.
 */
shapes* shapes::get_prev(void)
{
  forma* f_par=get_parent();
  if(f_par == 0)
    return 0;
  QList<shapes*>* sh_list=f_par->get_m_shapes();
  int idx = sh_list->indexOf(this);
  
  --idx;
  
  if(0<=idx && idx<sh_list->size())
    return sh_list->at(idx);
  return 0;
}

/**Если у подформы нет родителя или у родителя отсутствует последующий элемент возвращает 0.
 * Если у подформы есть родитель и у родителя присутствует последующий элемент возвращает указатель на его.
 */
shapes* shapes::get_next(void)
{
  forma* f_par=get_parent();
  if(f_par == 0)
    return 0;
  QList<shapes*>* sh_list=f_par->get_m_shapes();
  int idx = sh_list->indexOf(this);
  
  ++idx;
  
  if(0<=idx && idx<sh_list->size())
    return sh_list->at(idx);
  return 0;
}


shapes* shapes::copy ( void )
{
    shapes * val = new shapes;
    *val = *this;
    return val;
}

/**Вероятно, желательно сделать эту функцию чисто виртуальной*/
QString shapes::type ( void ) const
{
  return QString ("shapes");
}


QString shapes::out	( )
{
    return QString ( "" );
}

QString shapes::out_comment ( void )
{
    QString rez;
    rez = QString ( "shapes" ) + QString ( "\n" );
    return rez;
}

void shapes::edit	( void )
{
}

int shapes::get_lenth	( void )
{
    return 0;
}

int shapes::cicle_range ( int value, int base, int delta )
{
    int n = ( value - base ) / delta;
    int rez = value - n * delta;
    int test = ( rez - base ) * delta / abs ( delta );

    if ( test < 0 )
        rez = rez + delta;

    return rez;
}

double shapes::cicle_range ( double value, double base, double delta )
{
    int n = int ( ( value - base ) / delta );
    double rez = value - n * delta;
    double test = ( rez - base ) * delta / abs ( delta );

    if ( test < 0 )
        rez = rez + delta;

    return rez;
}

void shapes::set_parent ( forma* parent )
{
    m_parent = parent;
}

forma*	shapes::get_parent ( void ) const
{
    return m_parent;
}

QList<int>    shapes::get_m_bites() const
{
    QList<int> rez = m_bites;
    return rez;
}
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
