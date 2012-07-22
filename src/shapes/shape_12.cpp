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

#include "shape_12.h"
#include "dialog_pen_edit.h"
#include "main_form.h"

extern QTextStream std_out;
extern QTextStream std_in;
extern Main_Form  *theMainForm;

/**Создает подформу, задающую положения пера.\n
После выполнения конструктора перо опущено (при перемещении пера производится рисование).
*/
shape_12::shape_12 ( void )
{
    m_bites << 1 ; //Перо опущено
}

/**
  Создает подформу, задающее положения пера.\n
- Если pen_down == true - перо опущено (при перемещении пера производится рисование).
- Если pen_down == false - перо поднято (при перемещении пера рисование не производится).
*/
shape_12::shape_12 ( bool pen_down )
{
    if ( pen_down )
        m_bites << 1 ; //Перо опущено
    else
        m_bites << 2 ;//Перо поднято
}

shape_12::~shape_12()
{
}

void shape_12::set_pen_up ( bool pen_up )
{
    if ( !pen_up )
        m_bites[0] = 1 ; //Перо опущено
    else
        m_bites[0] = 2 ; //Перо поднято
}

void shape_12::set_pen_down ( bool pen_down )
{
    if ( pen_down )
        m_bites[0] = 1 ; //Перо опущено
    else
        m_bites[0] = 2 ; //Перо поднято
}

/**
- возвращает true если перо поднято;
- возвращает false если перо опущено.
*/
bool shape_12::is_pen_up ( void )
{
    return !is_pen_down();
}

/**
- возвращает false если перо поднято;
- возвращает true если перо опущено.
*/
bool shape_12::is_pen_down ( void )
{
    if ( m_bites[0] == 1 )
        return true;

    return false;
}

/**Рисовать форму shape_12.

*/
void shape_12::draw ( draw_vars &dr, stack &b, QGraphicsScene & sc)
{
  shapes* prev = get_prev();
  if(prev && prev->type()== QString("shape_e") && dr.drawAsHorisontal())
  {
    return;
  }
    if ( is_current() ) dr.draw_marker ( sc );
    qreal size = 1.;
    draw_point p = dr.get_p_otn();

    if (!dr.drawWhisOutPenUpMovement() )
        if ( is_current() )
        {
            QPen pen ( QBrush
                       ( QColor ( draw_vars::s_color_12 ), Qt::SolidPattern ),
                       qreal ( draw_vars::s_width_12 ) ,
                       Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );

            pen.setCosmetic ( true );

            if ( is_pen_down() )
            {
                sc.addLine ( p.x + size, p.y + size, p.x - size, p.y + size, pen );
                sc.addLine ( p.x + size, p.y + size, p.x, p.y - size*2, pen );
                sc.addLine ( p.x - size, p.y + size, p.x, p.y - size*2, pen );
            }

            if ( is_pen_up() )
            {
                sc.addLine ( p.x - size, p.y - size, p.x + size, p.y - size, pen );
                sc.addLine ( p.x - size, p.y - size, p.x, p.y + size*2, pen );
                sc.addLine ( p.x + size, p.y - size, p.x, p.y + size*2, pen );
            }
        }

    if ( is_pen_up ( ) )
        dr.pero_up();
    else
        dr.pero_down();

    return ;
}

int shape_12::get_lenth ( void )
//Возвращает длину подформы в байтах
{
    return 1;
}

/**
Добавление символьного представления формы к стрингу.
*/
QString shape_12::out ( void )
{
    QString rez = "";
    rez = QString::number ( m_bites.at ( 0 ) ) + QString ( "," );
    return rez;
}

QString shape_12::out_comment ( void )
{
    QString rez = "";
    rez = QString ( "shape_12" ) + QString ( ": " );

    if ( is_pen_up() ) rez += QString ( "pen" ) + QString ( "=" ) + QString ( "up" ) ;
    else  rez += QString ( "pen" ) + QString ( "=" ) + QString ( "down" ) ;

    return rez;
}

/**
Метод редактирования
*/
void shape_12::edit ( void )
{
    bool Pen_Down = is_pen_down();
    DialogPenEdit dlgPenEdit;
    dlgPenEdit.set_shape ( this );

    QRect the_main_window_geom = theMainForm->frameGeometry ();
    int top=the_main_window_geom.top();
    int right=the_main_window_geom.right();

    dlgPenEdit.move(QPoint(right,top));

    QObject::connect ( &dlgPenEdit, SIGNAL ( penChanged() ), theMainForm, SLOT ( reDrawSlot() ) );

    dlgPenEdit.set_pen ( Pen_Down );
    dlgPenEdit.exec();
    QPoint assa = dlgPenEdit.pos();

    QObject::disconnect ( &dlgPenEdit, SIGNAL ( penChanged() ), theMainForm, SLOT ( reDrawSlot() ) );

    set_pen_down ( dlgPenEdit.get_pen() );
    theMainForm->reDrawSlot();
}

shapes* shape_12::copy ( void )
{
    shape_12 * VVV = new shape_12;
    *VVV = *this;
    return VVV;
}

QString shape_12::type(void ) const
{
  return QString ("shape_12");
}


// kate: indent-mode cstyle; space-indent on; indent-width 0; 
