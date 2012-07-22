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

#include "shape_.h"
#include "dialog_line_edit.h"
#include "main_form.h"

extern QTextStream std_out;
extern QTextStream std_in;
extern Main_Form  *theMainForm;

shape_::shape_ ( void )
{
    m_bites<<0x10;
    byte_to();
}

shape_::shape_ ( int Bite )
{
    m_bites<< Bite;
    byte_to();
}

shape_::shape_ ( int Radius, int Octant )
{
    m_bites<<0x10;
    set_length ( Radius );
    set_sixtant ( Octant );
}

shape_::~shape_()
{
}

void shape_::set_byte ( int a )
{
    m_bites[0] = a;
    byte_to();
}

void shape_::byte_to ( void )
{
    int octant = m_bites.at ( 0 ) & 0x0f ;
    int radius = ( m_bites.at ( 0 ) & 0xf0 ) >> 4 ;

    if ( radius == 0 )
    {
        //радиус должен принимать значение от 1 до 15
        m_bites[0] = ( 1 << 4 ) + octant;
    }
}

QString shape_::out ( void )
//Добавление символьного представления формы к стрингу
{
    QString rez;
    rez += QString ( "0" ) + QString::number ( get_length(), 16 ) + QString::number ( get_sixtant(), 16 ) + QString ( "," );
    return rez;
}

QString shape_::out_comment ( void )
{
    QString rez;
    rez += QString ( "shape_" ) + QString ( " " );
    rez += QString ( "radius" ) + QString ( "=" ) + QString::number ( get_length() ) + QString ( " " );
    rez += QString ( "octant" ) + QString ( "=" ) + QString::number ( get_sixtant() );
    return rez;
}

int shape_::get_byte ( void ) const
{
    return m_bites.at ( 0 );
}

int shape_::get_length ( void ) const
{
    int radius = ( m_bites.at ( 0 ) & 0xf0 ) >> 4 ;
    return radius;
}

int shape_::get_sixtant ( void ) const
{
    int octant = m_bites.at ( 0 ) & 0x0f ;
    return octant;
}

int shape_::get_lenth ( void )
//Возвращает длину подформы в байтах
{
    return 1;
}

void shape_::set_length ( int Radius )
{
    int octant = m_bites.at ( 0 ) & 0x0f ;
    int radius = ( m_bites.at ( 0 ) & 0xf0 ) >> 4 ;

    if ( Radius <= 15 && 1 <= Radius ) radius = Radius;
    else if ( Radius >= -15 && -1 >= Radius ) radius = -Radius;
    else if ( Radius == 0 ) radius = 1;
    else radius = 15;

    m_bites[0] = ( radius << 4 ) + octant;
}

void shape_::set_sixtant ( int Octant )
{
    int octant = m_bites.at ( 0 ) & 0x0f ;
    int radius = ( m_bites.at ( 0 ) & 0xf0 ) >> 4 ;

    Octant = cicle_range ( Octant, 0, 16 );
    octant = Octant;

    m_bites[0] = ( radius << 4 ) + octant;
}

shapes* shape_::copy ( void )
{
    shape_ * VVV = new shape_;
    *VVV = *this;
    return VVV;
}

QString shape_ ::type ( void ) const
{
  return QString ("shape_");
}

void shape_::draw ( draw_vars &dr, stack &b, QGraphicsScene & sc)
// Рисовать форму
{
    shapes* prev = get_prev();
    if(prev && prev->type()== QString("shape_e") && dr.drawAsHorisontal())
    {
      return;
    }
    if ( is_current() ) dr.draw_marker ( sc );
    draw_point p_start = dr.get_p_otn();
    draw_point delta_p = get_delta_p() * dr.get_masht();
    dr.move_coords ( delta_p );
    draw_point p_end = dr.get_p_otn();

    if (dr.drawWhisOutPenUpMovement() && !dr.get_pero())
        return;

    if ( is_current() )
    {
        QPen pen ( QBrush
                   ( QColor ( draw_vars::s_color_cur ), Qt::SolidPattern ),
                   qreal ( draw_vars::s_width_cur ) ,
                   Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );

        pen.setCosmetic ( true );
        sc.addLine ( p_start.x, p_start.y, p_end.x, p_end.y, pen );
    }
    else if ( dr.get_pero() )
    {
        QPen pen ( QBrush
                   ( QColor ( draw_vars::s_color_pen_down ), Qt::SolidPattern ),
                   qreal ( draw_vars::s_width_pen_down ) ,
                   Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );

        pen.setCosmetic ( true );
        sc.addLine ( p_start.x, p_start.y, p_end.x, p_end.y, pen );
    }
    else
    {
        QPen pen ( QBrush
                   ( QColor ( draw_vars::s_color_pen_up ), Qt::SolidPattern ),
                   qreal ( draw_vars::s_width_pen_up ) ,
                   Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );
        pen.setCosmetic ( true );
        sc.addLine ( p_start.x, p_start.y, p_end.x, p_end.y, pen );
    }
    return ;
}

/**
//Редактирование формы.
*/
void shape_::edit ( void )
{
    int radius = get_length();
    int octant = get_sixtant();

    DialogLineEdit dlgLineEdit;
    dlgLineEdit.set_shape ( this );

    QRect the_main_window_geom = theMainForm->frameGeometry ();
    int top=the_main_window_geom.top();
    int right=the_main_window_geom.right();

    dlgLineEdit.move ( QPoint ( right,top ) );

    QObject::connect ( &dlgLineEdit, SIGNAL ( lineChanged() ), theMainForm, SLOT ( reDrawSlot() ) );

    dlgLineEdit.set_radius ( radius );
    dlgLineEdit.set_sixtant ( octant );

    dlgLineEdit.exec();
    QObject::disconnect ( &dlgLineEdit, SIGNAL ( lineChanged() ), theMainForm, SLOT ( reDrawSlot() ) );

    set_length ( dlgLineEdit.get_radius() );
    set_sixtant ( dlgLineEdit.get_sixtant() );

    theMainForm->reDrawSlot();
}

draw_point shape_::get_delta_p ( void ) const
{
    draw_point dp;
    qreal radius = get_length ( );
    int octant = get_sixtant( );

    switch ( octant )
    {

    case 0:
        dp.x = radius;
        dp.y = 0.;
        break;

    case 1:
        dp.x = radius;
        dp.y = radius / 2.;
        break;

    case 2:
        dp.x = radius;
        dp.y = radius;
        break;

    case 3:
        dp.x = radius / 2.;
        dp.y = radius;
        break;

    case 4:
        dp.x = 0.;
        dp.y = radius;
        break;

    case 5:
        dp.x = -radius / 2.;
        dp.y = radius ;
        break;

    case 6:
        dp.x = -radius;
        dp.y = radius ;
        break;

    case 7:
        dp.x = -radius;
        dp.y = radius / 2. ;
        break;

    case 8:
        dp.x = -radius;
        dp.y = 0. ;
        break;

    case 9:
        dp.x = -radius;
        dp.y = -radius / 2. ;
        break;

    case 10:
        dp.x = -radius;
        dp.y = -radius ;
        break;

    case 11:
        dp.x = -radius / 2.;
        dp.y = -radius ;
        break;

    case 12:
        dp.x = 0.;
        dp.y = -radius ;
        break;

    case 13:
        dp.x = radius / 2.;
        dp.y = -radius ;
        break;

    case 14:
        dp.x = radius;
        dp.y = -radius ;
        break;

    case 15:
        dp.x = radius;
        dp.y = -radius / 2. ;
        break;
    }

    return dp;
}
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
