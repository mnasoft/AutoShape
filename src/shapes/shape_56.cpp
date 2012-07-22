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

#include "shape_56.h"
#include "dialog_stack_edit.h"
#include "main_form.h"

extern QTextStream std_out;
extern QTextStream std_in;
extern Main_Form	*theMainForm;


/**
Создает подформу, проталкивающую положение в стек
*/
shape_56::shape_56()
{
    m_bites.append ( 5 ); //Протолнуть в стек
}


shape_56::shape_56 ( bool push )
{
    if ( push == true )
        m_bites.append ( 5 ); //Протолнуть в стек
    else
        m_bites.append ( 6 ); //Вытолкнуть из стека
}


shape_56::~shape_56()
{
}

void shape_56::draw ( draw_vars &dr, stack &b, QGraphicsScene & sc)
{
  shapes* prev = get_prev();
  if(prev && prev->type()== QString("shape_e") && dr.drawAsHorisontal())
  {
    return;
  }
    if ( is_current() ) dr.draw_marker ( sc );

    draw_point pnt;
    if ( get_push() )
    {
        pnt=dr.get_p_otn();
        b.push ( pnt );
    }
    else
    {
        b.pop ( pnt );
        dr.set_otn_coords ( pnt );
    }

    qreal size = 1.;
    draw_point p = dr.get_p_otn();

    if (!dr.drawWhisOutPenUpMovement() )
        if ( is_current() )
        {
            QPen pen ( QBrush
                       ( QColor ( draw_vars::s_color_56 ), Qt::SolidPattern ),
                       qreal ( draw_vars::s_width_56 ) ,
                       Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );

            pen.setCosmetic ( true );

            if ( get_push() )
            {
                sc.addLine ( p.x - size, p.y - size, p.x + size, p.y + size, pen );
                sc.addLine ( p.x + size, p.y - size, p.x - size, p.y + size, pen );

                sc.addLine ( p.x - size, p.y - size, p.x + size, p.y - size, pen );
                sc.addLine ( p.x + size, p.y - size, p.x + size, p.y + size, pen );
                sc.addLine ( p.x + size, p.y + size, p.x - size, p.y + size, pen );
                sc.addLine ( p.x - size, p.y + size, p.x - size, p.y - size,  pen );
            }
            else
            {
                sc.addLine ( p.x - size, p.y - size, p.x + size, p.y - size, pen );
                sc.addLine ( p.x + size, p.y - size, p.x + size, p.y + size, pen );
                sc.addLine ( p.x + size, p.y + size, p.x - size, p.y + size, pen );
                sc.addLine ( p.x - size, p.y + size, p.x - size, p.y - size,  pen );
            }
        }


}

int shape_56::get_lenth ( void )
//Возвращает длину подформы в байтах
{
    return 1;
}

QString shape_56::out ( void )
//Добавление символьного представления формы к стрингу
{
    QString rez;
    rez = QString ( "0" ) + QString::number ( m_bites.at ( 0 ), 16 ) + QString ( "," );
    return rez;
}

QString shape_56::out_comment ( void )
{
    QString rez;
    rez = QString ( "shape_56" ) + QString ( ": " ) ;

    if ( get_push ( ) ) rez += QString ( "stack=" ) + QString ( "push" ) ;
    else rez += QString ( "stack=" ) + QString ( "pop" ) ;

    return rez;
}



/*
	if ( var == 5 )
	{
		fprintf ( du, "\n  8\nshape_5" );
		fprintf ( du, "\n  8\nend_shape_5" );
	}

	if ( var == 6 )
	{
		fprintf ( du, "\n  8\nshape_6" );
		fprintf ( du, "\n  8\nend_shape_6" );
	}
*/

/**
Метод редактирования
*/
void shape_56::edit ( void )
{
    bool stackPush = get_push();
    DialogStackEdit dlgStackEdit;
    dlgStackEdit.set_shape ( this );

    QRect the_main_window_geom = theMainForm->frameGeometry ();
    int top=the_main_window_geom.top();
    int right=the_main_window_geom.right();

    dlgStackEdit.move ( QPoint ( right,top ) );

    QObject::connect ( &dlgStackEdit, SIGNAL ( stackChanged() ), theMainForm, SLOT ( reDrawSlot() ) );

    dlgStackEdit.set_stack_push ( stackPush );
    dlgStackEdit.exec();

    QObject::disconnect ( &dlgStackEdit, SIGNAL ( stackChanged() ), theMainForm, SLOT ( reDrawSlot() ) );

    set_push ( dlgStackEdit.get_stack_push() );

    theMainForm->reDrawSlot();
}

void shape_56::set_push ( bool push )
{
    if ( push )
        m_bites[0] = 5;
    else
        m_bites[0] = 6;
}

bool shape_56::get_push ( void )
{
    if ( m_bites[0] == 5 )
        return true;
    else
        return false;
}

shapes* shape_56::copy ( void )
{
    shape_56 * VVV = new shape_56;
    *VVV = *this;
    return VVV;
}

QString shape_56::type ( void ) const
{
  return QString ("shape_56");
}

// kate: indent-mode cstyle; space-indent on; indent-width 0; 
