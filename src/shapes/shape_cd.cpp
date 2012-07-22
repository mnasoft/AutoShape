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

#include "shape_cd.h"
#include <math.h>
#include <QGraphicsPathItem>
#include "dialog_multi_arc_edit.h"

extern QTextStream std_out;
extern QTextStream std_in;

/*
char *ld_name=
  "&List dx_dy&~Edit&==========&~Prev<LFT&~Next<RGT&~Home< HM&En~d<END&==========&Ins past<INS&Ins be~for&==========&De~l<DEL&Backspace";
 menu list_dx_dy(65,0,   // X, Y
  14,  1,         // Normal For Back
  12,             // Heat char
  2,  14,         // Choise For Back
  8,              // Shadow
  14,  2,         // Header For Back
  0,              // Frozen For
  2, 1,           // Shadow Displacement dX dY
  1,              // Is mouse present ?
  ld_name);          // Init string
*/
/*******************  К О Н С Т Р У К Т О Р Ы **************************/
shape_cd::shape_cd ( void )
:m_current(0)
{
//           code   dx   dy    bulge
    m_bites << 12 << 1 << 0 << 0 ;
}

shape_cd::~shape_cd()
{
}


/*******************  К О Н С Т Р У К Т О Р Ы **************************/

void shape_cd::draw ( draw_vars& dr, stack&, QGraphicsScene& sc)
{
  shapes* prev = get_prev();
  if(prev && prev->type()== QString("shape_e") && dr.drawAsHorisontal())
  {
    return;
  }
    if ( is_current() ) dr.draw_marker ( sc );

    int nSegments = get_n_segment();

    for ( int i = 0 ; i < nSegments; ++i )
    {
        draw_point p_start = dr.get_p_otn();   //Начальная точка сегмента дуги.
        draw_point delta_p = get_delta_p ( i ) * dr.get_masht() ;
        qreal C = abs ( get_c ( i ) );   //Значение параметра кривизны.
        qreal C_sign = get_c ( i ) / C; //Знак параметра кривизны.
        dr.move_coords ( delta_p );
        draw_point p_end = dr.get_p_otn();    //Конечная точка сегмента дуги.

        if (dr.drawWhisOutPenUpMovement() && !dr.get_pero()) ;
        else if ( get_c ( i ) != 0 )
        {
            qreal D = p_start.dist ( p_end );  //Расстояние между конечными точками сегмента.
            qreal H = C * D / qreal ( 2 ) / qreal ( 127 );   //Высота сегмента.
            qreal R = D * D / ( H * qreal ( 8 ) ) + H / qreal ( 2 ); //Радиус дуги.

            qreal ang = p_start.agnle ( p_end );
            draw_point p_mid_hord = p_start.polar ( ang, D / qreal ( 2 ) );
            draw_point p_center = p_mid_hord.polar ( ang + C_sign * M_PI / qreal ( 2 ), R - H );

            draw_point p_radius ( R, R );
            qreal ang_start = draw_point::rtd ( p_center.agnle ( p_start ) );
            qreal ang_4 = draw_point::rtd ( atan2 ( H, D / qreal ( 2 ) ) );
            qreal ang_number = C_sign * ang_4 * qreal ( 4 );
            if ( is_current() )
            {
                QPen pen( QBrush
                          ( QColor ( draw_vars::s_color_cur ), Qt::SolidPattern ),
                          qreal ( draw_vars::s_width_cur ) ,
                          Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );
                pen.setCosmetic ( true );
                if ( i == get_current())
                    pen.setColor(QColor ( draw_vars::s_color_9d));
                else
                    pen.setColor(QColor ( draw_vars::s_color_cur));
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
        else
        {
            if ( dr.get_pero() )
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
        }
    }
}

QString shape_cd::out ( void )
//Добавление символьного представления формы к стрингу
{
    QString rez = QString ( "(0" ) + QString::number ( m_bites.at ( 0 ), 16 );
    for ( int i = 1;i < m_bites.size();++i )
    {
        rez += QString ( "," ) + QString::number ( m_bites.at ( i ) );
    }
    rez += QString ( ")," ) ;
    return rez;
}


QString shape_cd::out_comment ( void )
{
    QString rez;
    rez = QString ( "shape_cd" ) + QString ( ": " );

    for ( int i = 0;i < m_bites.size();++i )
    {
        rez += QString::number ( m_bites.at ( i ) ) + QString ( " " );
    }

    return rez;
}

/*
 d_link* link = this;
 rewind_to_head ( link );
 fprintf ( du, "\n  8\nshape_9" );

 do
 {
  fprintf ( du, "\n 98\nshape_8" );
  fprintf ( du, "\n 11\n%d", ( ( shape_cd* ) link )->shape_8::get_dx() );
  fprintf ( du, "\n 21\n%d", ( ( shape_cd* ) link )->shape_8::get_dy() );
  fprintf ( du, "\n 98\nend_shape_8" );
  stap_to_tail ( link );
 }

 while ( link->get_succ ( link ) );

 if ( link->get_pred ( link ) )
 {
//  ((shape_cd*)link)->shape_8::out_file(du);
  fprintf ( du, "\n 98\nshape_8" );
  fprintf ( du, "\n 11\n%d", ( ( shape_cd* ) link )->shape_8::get_dx() );
  fprintf ( du, "\n 21\n%d", ( ( shape_cd* ) link )->shape_8::get_dy() );
  fprintf ( du, "\n 98\nend_shape_8" );
 }

 fprintf ( du, "\n  8\nend_shape_9" );
*/

int shape_cd::get_lenth ( void )
//Возвращает длину подформы в байтах
{
    return m_bites.size();
}

void shape_cd::edit ( void )
//Метод редактирования
{

    DialogMultiArcEdit dlg ;
    dlg.set_shape ( this );
    dlg.exec();
}

shapes* shape_cd::copy ( void )
{
    /*
     d_link* a = this;
     shape_cd *VVV, *COp;
     d_link * OU = NULL;
     d_link * out;
     a->rewind_to_head ( a );

     do
     {
      if ( OU == 0 ) OU = new shape_cd;
      else OU->insert_past ( NULL, OU );

      VVV = ( shape_cd* ) OU;

      COp = ( shape_cd* ) a;

      VVV->dx = COp->dx;

      VVV->dy = COp->dy;

      out = a;

      a->stap_to_tail ( a );
     }

     while ( out->get_succ ( out ) );

     return VVV;
    */
}

QString shape_cd::type ( void ) const
{
  return QString ("shape_cd");
}

int shape_cd::get_n_segment ( void ) const
{
    int rez, size, n_segment;
    size = m_bites.size ();
    n_segment = ( size - 1 ) / 3;
    return n_segment;
}

/**
ref_pos может принимать значения от 0 (вставка перед первым элементом) до n_segment (вставка поле последнего элемента.
Если значение ref_pos выходит за допустимые возвращается код ошибки (Значение большее 0) иначе возвращается 0.
*/
int shape_cd::insert ( int ref_pos, int dx, int dy, int c )
{
    if ( !is_multi_form() )
    {
        //Добавляем байты обозначающие окончание формы.
        m_bites.append ( 0 ); //dx
        m_bites.append ( 0 ); //dy
        m_bites[0] = 13;//Это ломаная более чем одним сегментом.
    }

    m_bites.insert ( 3*ref_pos + 1, c );
    m_bites.insert ( 3*ref_pos + 1, dy );
    m_bites.insert ( 3*ref_pos + 1, dx );
    return 0;
}

int shape_cd::append ( int dx, int dy , int c )
{
    insert ( get_n_segment(), dx, dy, c );
}

int shape_cd::replace ( QList<int> & Dxy )
{
    int length = Dxy.length() / 3;

    if ( 0 >= length )
    {
        return 0;
    }
    else if ( 1 == length )
    {
        this->m_bites.clear();
        m_bites << 12 << Dxy[0] << Dxy[1] << Dxy[2];
        return 3;
    }

    this->m_bites.clear();

    m_bites << 13;

    for ( int i = 0; i < length;++i )
    {
        m_bites << Dxy[3*i] << Dxy[3*i+1] << Dxy[3*i+2];
    }

    m_bites << 0 << 0;

    Validate();
}

/**
  ref_pos может принимать значения от 0 (вставка перед первым элементом) до n_segment (вставка поле последнего элемента.
  Если значение ref_pos выходит за допустимые возвращается код ошибки (Значение большее 0) иначе возвращается 0.
  Аргумент Dxy содержит список, состоящий из целых чисел.
*/
int shape_cd::insert ( int ref_pos, QList<int> & Dxy )
{
    if ( ! ( ref_pos >= 0 && ref_pos < get_n_segment() + 1 ) )
        return 1;

    int Dxy_size = Dxy.size();

    int Dxy_length = Dxy_size / 3;


    if ( Dxy_length <= 0 )
        return 2;

    if ( !is_multi_form() )
    {
        m_bites << 13 << 0 << 0;
    }

    for ( int i = Dxy_length - 1; i >= 0;--i )
    {
        m_bites.insert ( 3*ref_pos + 1, Dxy.at ( 3*i + 2 ) );
        m_bites.insert ( 3*ref_pos + 1, Dxy.at ( 3*i + 1 ) );
        m_bites.insert ( 3*ref_pos + 1, Dxy.at ( 3*i ) );
    }

    return 0;
}

int shape_cd::get_x ( int i ) const
{
    if ( !is_index_good ( i ) )
        return 0;

    return m_bites.at ( 3*i + 1 );
}

int shape_cd::get_y ( int i ) const
{
    if ( !is_index_good ( i ) )
        return 0;

    return m_bites.at ( 3*i + 2 );
}

int shape_cd::get_c ( int i ) const
{
    if ( !is_index_good ( i ) )
        return 0;

    return m_bites.at ( 3*i + 3 );
}

bool shape_cd::is_multi_form() const
{
    int size;
    size = m_bites.size ();

    if ( 4 < size )
        return true;
    else
        return false;
}

void shape_cd::set_x ( int i, int dx )
{
    if ( i < 0 || i > get_n_segment() )
        return;

    m_bites[3*i+1] = dx;
}

void shape_cd::set_y ( int i, int dy )
{
    if ( i < 0 || i > get_n_segment() )
        return;

    m_bites[3*i+2] = dy;
}

void shape_cd::set_c ( int i, int c )
{
    if ( i < 0 || i > get_n_segment() )
        return;

    m_bites[3*i+3] = c;
}

void shape_cd::set_xy_c ( int i, int dx, int dy, int c )
{
    if ( i < 0 || i > get_n_segment() )
        return;

    m_bites[3*i+1] = dx;

    m_bites[3*i+2] = dy;

    m_bites[3*i+3] = c;
}

void shape_cd::set_current ( int i )
{
    if ( i < 0 )
    {
        m_current = 0;
        return;
    }
    else if ( i >= get_n_segment() )
    {
        m_current = get_n_segment() - 1;
        return;
    }
    else
    {
        m_current=i;
        return;
    }
}

int shape_cd::get_current ( void )
{
    return m_current;
}


QString shape_cd::out_i ( int i )
{
    QString rez;

    if ( is_index_good ( i ) )
    {
        rez += QString ( "dx(" ) + QString::number ( i ) + QString ( ")=" ) + QString::number ( get_x ( i ) ) + QString ( ", " );
        rez += QString ( "dy(" ) + QString::number ( i ) + QString ( ")=" ) + QString::number ( get_y ( i ) ) ;
    }

    else
        rez = "Bad index";

    return rez;
}

void shape_cd::print_i ( int i )
{
    std_out << out_i ( i );
}

bool shape_cd::is_index_good ( int i ) const
{
    return ( i >= 0 && i < get_n_segment() );
}

int shape_cd::removeAt ( int ref_pos )
{
    if ( !is_multi_form() )
        return 1;

    if ( !is_index_good ( ref_pos ) )
        return 2;

    m_bites.removeAt ( 3*ref_pos + 1 );

    m_bites.removeAt ( 3*ref_pos + 1 );

    m_bites.removeAt ( 3*ref_pos + 1 );

    if ( m_bites.size() == 6 )
    {
        m_bites.removeLast();
        m_bites.removeLast();
        m_bites[0] = 12;
    }

    return 0;
}

bool shape_cd::is_validate() const
{
    return is_index_good(m_current);
}

void shape_cd::Validate()
{
    set_current(m_current);
}

draw_point shape_cd::get_delta_p ( int i ) const
{
    draw_point rez ( qreal ( get_x ( i ) ), qreal ( get_y ( i ) ) );
    return rez;
}
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
