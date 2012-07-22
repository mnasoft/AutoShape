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

#include "shape_34.h"
#include "dialog_scale_edit.h"
#include "main_form.h"

extern QTextStream std_out;
extern QTextStream std_in;
extern Main_Form	*theMainForm;

shape_34::shape_34 ( void )
{
    m_bites << 3 << 1 ; //Увеличить масштаб в 1 раз.
}


shape_34::shape_34 ( bool scale_up, int scale_factor )
{
    m_bites << 3 << 1 ; //Увеличить масштаб в 1 раз.
    set ( scale_up, scale_factor ); //Назначить новый масштаб.
}

shape_34::~shape_34()
{
}

int shape_34::get_lenth ( void )
{
    return 2;
}

QString shape_34::out ( void )
//Добавление символьного представления формы к стрингу
{
    QString rez;
    rez = QString("(0")
          + QString::number ( m_bites.at ( 0 ), 16 )
          + QString ( "," )
          + QString::number ( m_bites.at ( 1 ), 10 )
          + QString ( ")," );
    return rez;
}

QString shape_34::out_comment ( void )
{
    QString rez;
    rez = QString ( "shape_34" ) + QString ( ": " );

    if ( get_scale_up() ) rez += QString ( "get_scale_up()" ) + QString ( "=" ) + QString ( "up" ) + QString ( "; " );
    else  rez += QString ( "get_scale_up()" ) + QString ( "=" ) + QString ( "down" ) + QString ( "; " );

    rez += QString ( "get_scale_factor()=" ) + QString ::number ( get_scale_factor() ) + QString ( "; " );

    rez += QString ( "get_scale()=" ) + QString::number ( get_scale() ) + QString ( "" );

    return rez;
}

void shape_34::set ( bool scale_up, int scale_factor )
{
    set_scale_up ( scale_up );
    set_scale_factor ( scale_factor );
}

/**
Если эта функция возвращает true масштаб последующих подформ будет увеличен в  get_scale_factor( ) раз. \n
Если эта функция возвращает false масштаб последующих подформ будет уменьшен в  get_scale_factor( ) раз.
*/
bool shape_34::get_scale_up ( void )
{
    if ( m_bites[0] == 4 )
        return true;
    else
        return false;
}

int shape_34::get_scale_factor ( void )
{
    return m_bites[1];
}

/**
При
- scale_up=true - масштаб увеличивается
- scale_up=false - масштаб уменьшается
*/
void shape_34::set_scale_up ( bool scale_up )
{
    if ( scale_up )
        m_bites[0] = 4; //Увеличить масштаб
    else
        m_bites[0] = 3; //Уменьшить масштаб
}

;
void shape_34::set_scale_factor ( int scale_factor )
{
    if ( scale_factor <= 0 )
        m_bites[1] = 1 ;
    else if ( scale_factor <= 256 )
        m_bites[1] = scale_factor;
    else
        m_bites[1] = 256 ;
}

double shape_34::get_scale ( void )
{
    double rez;

    if ( get_scale_up ( ) )
        rez = get_scale_factor( ) ;
    else
        rez = 1.0 / get_scale_factor( ) ;

    return rez;
}

shapes* shape_34::copy ( void )
{
    shape_34 * VVV = new shape_34;
    *VVV = *this;
    return VVV;
}

QString shape_34::type ( void ) const
{
  return QString ("shape_34");
}

void shape_34::draw ( draw_vars &dr, stack &b, QGraphicsScene & sc)
{
  shapes* prev = get_prev();
  if(prev && prev->type()== QString("shape_e") && dr.drawAsHorisontal())
  {
    return;
  }
    if ( is_current() ) dr.draw_marker ( sc );

    if ( get_scale_up() )
    {
        dr.multipli_masht ( qreal ( get_scale_factor() ) );
    }
    else
        dr.multipli_masht ( 1. / qreal ( get_scale_factor() ) );

    qreal size = 1.;
    draw_point p = dr.get_p_otn();

    if (!dr.drawWhisOutPenUpMovement() )
        if ( is_current() )
        {
            QPen pen ( QBrush
                       ( QColor ( draw_vars::s_color_34 ), Qt::SolidPattern ),
                       qreal ( draw_vars::s_width_34 ) ,
                       Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );

            pen.setCosmetic ( true );

            if ( get_scale_up() )
            {
                sc.addLine ( p.x - size, p.y - size*0.5, p.x + size, p.y - size*1.5, pen );
                sc.addLine ( p.x - size, p.y + size*0.5, p.x + size, p.y + size*1.5, pen );

                sc.addLine ( p.x - size, p.y - size*0.5, p.x - size, p.y + size*0.5, pen );
                sc.addLine ( p.x + size, p.y - size*1.5, p.x + size, p.y + size*1.5, pen );
            }
            else
            {
                sc.addLine ( p.x + size, p.y - size*0.5, p.x - size, p.y - size*1.5, pen );
                sc.addLine ( p.x + size, p.y + size*0.5, p.x - size, p.y + size*1.5, pen );

                sc.addLine ( p.x + size, p.y - size*0.5, p.x + size, p.y + size*0.5, pen );
                sc.addLine ( p.x - size, p.y - size*1.5, p.x - size, p.y + size*1.5, pen );
            }
        }

}

void shape_34::edit ( void )
//Метод редактирования
{
    int scaleFactor = get_scale_factor();
    bool scaleUp = get_scale_up();

    DialogScaleEdit dlgScaleEdit;
    dlgScaleEdit.set_shape ( this );

    QRect the_main_window_geom = theMainForm->frameGeometry ();
    int top=the_main_window_geom.top();
    int right=the_main_window_geom.right();

    dlgScaleEdit.move(QPoint(right,top));
    QObject::connect ( &dlgScaleEdit, SIGNAL ( scaleChanged() ), theMainForm, SLOT ( reDrawSlot() ) );

    dlgScaleEdit.set_scaleUp(scaleUp);
    dlgScaleEdit.set_scaleFactor(scaleFactor);
    dlgScaleEdit.exec();

    QObject::disconnect ( &dlgScaleEdit, SIGNAL ( scaleChanged() ), theMainForm, SLOT ( reDrawSlot() ) );
    set_scale_up(dlgScaleEdit.get_scaleUp());
    set_scale_factor(dlgScaleEdit.get_scaleFactor());

    theMainForm->reDrawSlot();
}
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
