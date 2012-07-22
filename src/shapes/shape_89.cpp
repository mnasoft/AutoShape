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

#include "shape_89.h"
//#include "dialog_scale_edit.h"
#include "main_form.h"
#include "dialog_multi_line_edit.h"

extern QTextStream std_out;
extern QTextStream std_in;

shape_89::shape_89 ( void )
        :m_current(0)
{
//           code   dx   dy
    m_bites << 8 << 1 << 0;
}

shape_89::~shape_89()
{
}

void shape_89::draw ( draw_vars& dr, stack&, QGraphicsScene& sc)
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
        draw_point p_start = dr.get_p_otn();
        draw_point delta_p = get_delta_p ( i ) * dr.get_masht() ;
        dr.move_coords ( delta_p );
        draw_point p_end = dr.get_p_otn();

        if (dr.drawWhisOutPenUpMovement() && !dr.get_pero()) ;
        else if ( is_current() )
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
    }
}

draw_point shape_89::get_delta_p ( int i ) const
{
    draw_point rez ( qreal ( get_x ( i ) ), qreal ( get_y ( i ) ) );
    return rez;
}

QString shape_89::out ( void )
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


QString shape_89::out_comment ( void )
{
    QString rez;
    rez = QString ( "shape_89" ) + QString ( ": " );

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
  fprintf ( du, "\n 11\n%d", ( ( shape_89* ) link )->shape_8::get_dx() );
  fprintf ( du, "\n 21\n%d", ( ( shape_89* ) link )->shape_8::get_dy() );
  fprintf ( du, "\n 98\nend_shape_8" );
  stap_to_tail ( link );
 }

 while ( link->get_succ ( link ) );

 if ( link->get_pred ( link ) )
 {
//  ((shape_89*)link)->shape_8::out_file(du);
  fprintf ( du, "\n 98\nshape_8" );
  fprintf ( du, "\n 11\n%d", ( ( shape_89* ) link )->shape_8::get_dx() );
  fprintf ( du, "\n 21\n%d", ( ( shape_89* ) link )->shape_8::get_dy() );
  fprintf ( du, "\n 98\nend_shape_8" );
 }

 fprintf ( du, "\n  8\nend_shape_9" );
*/

int shape_89::get_lenth ( void )
//Возвращает длину подформы в байтах
{
    return m_bites.size();
}

void shape_89::edit ( void )
//Метод редактирования
{
    DialogMultiLineEdit a;
    a.set_shape ( this );
    a.exec();
}

shapes* shape_89::copy ( void )
{
    /*
     d_link* a = this;
     shape_89 *VVV, *COp;
     d_link * OU = NULL;
     d_link * out;
     a->rewind_to_head ( a );

     do
     {
      if ( OU == 0 ) OU = new shape_89;
      else OU->insert_past ( NULL, OU );

      VVV = ( shape_89* ) OU;

      COp = ( shape_89* ) a;

      VVV->dx = COp->dx;

      VVV->dy = COp->dy;

      out = a;

      a->stap_to_tail ( a );
     }

     while ( out->get_succ ( out ) );

     return VVV;
    */
}

QString shape_89::type ( void ) const
{
  return QString ("shape_89");
}

int shape_89::get_n_segment ( void ) const
{
    int size, n_segment;
    size = m_bites.size ();
    n_segment = size / 2;

    if ( 1 < n_segment )
        --n_segment;

    return n_segment;
}

/**
ref_pos может принимать значения от 0 (вставка перед первым элементом) до n_segment (вставка поле последнего элемента.
Если значение ref_pos выходит за допустимые возвращается код ошибки (Значение большее 0) иначе возвращается 0.
*/
int shape_89::insert ( int ref_pos, int dx, int dy )
{
    if ( !is_multi_form() )
    {
        //Добавляем байты обозначающие окончание формы.
        m_bites.append ( 0 );  //dx
        m_bites.append ( 0 );  //dy
        m_bites[0] = 9;     //Это ломаная с более чем одним сегментом.
    }

    m_bites.insert ( 2*ref_pos + 1, dy );

    m_bites.insert ( 2*ref_pos + 1, dx );
    return 0;
}

int shape_89::append ( int dx, int dy )
{
    insert ( get_n_segment(), dx, dy );
}

/**
  ref_pos может принимать значения от 0 (вставка перед первым элементом) до n_segment (вставка поле последнего элемента.
  Если значение ref_pos выходит за допустимые возвращается код ошибки (Значение большее 0) иначе возвращается 0.
  Аргумент Dxy содержит список, состоящий из целых чисел.
*/
int shape_89::insert ( int ref_pos, QList<int> & Dxy )
{
    if ( ! ( ref_pos >= 0 && ref_pos < get_n_segment() + 1 ) )
        return 1;

    int Dxy_size = Dxy.size();

    int Dxy_length = Dxy_size / 2;


    if ( Dxy_length <= 0 )
        return 2;

    if ( !is_multi_form() )
    {
        //Добавляем байты обозначающие окончание формы.
        m_bites.append ( 0 ); //dx
        m_bites.append ( 0 ); //dy
        m_bites[0] = 9;//Это ломаная более чем одним сегментом.
    }

    for ( int i = Dxy_length - 1; i >= 0;--i )
    {
        m_bites.insert ( 2*ref_pos + 1, Dxy.at ( 2*i + 1 ) );
        m_bites.insert ( 2*ref_pos + 1, Dxy.at ( 2*i ) );
    }

    return 0;
}

int shape_89::replace ( QList<int> & Dxy )
{
    int length = Dxy.length() / 2;

    if ( 0 >= length )
    {
        return 0;
    }
    else if ( 1 == length )
    {
        this->m_bites.clear();
        m_bites << 8 << Dxy[0] << Dxy[1];
        return 3;
    }

    this->m_bites.clear();

    m_bites << 9;

    for ( int i = 0; i < length;++i )
    {
        m_bites << Dxy[2*i] << Dxy[2*i+1];
    }

    m_bites << 0 << 0;

    Validate();
}

int shape_89::get_x ( int i ) const
{
    if ( !is_index_good ( i ) )
        return 0;

    return m_bites.at ( 2*i + 1 );
}

int shape_89::get_y ( int i ) const
{
    if ( !is_index_good ( i ) )
        return 0;

    return m_bites.at ( 2*i + 2 );
}

bool shape_89::is_multi_form() const
{
    int size;
    size = m_bites.size ();

    if ( 3 < size )
        return true;
    else
        return false;
}

void shape_89::set_x ( int i, int dx )
{
    if ( i < 0 || i > get_n_segment() )
        return;

    m_bites[2*i+1] = dx;
}

void shape_89::set_y ( int i, int dy )
{
    if ( i < 0 || i > get_n_segment() )
        return;

    m_bites[2*i+2] = dy;
}

void shape_89::set_xy ( int i, int dx, int dy )
{
    if ( i < 0 || i > get_n_segment() )
        return;

    m_bites[2*i+1] = dx;

    m_bites[2*i+2] = dy;
}

void shape_89::set_current ( int i )
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

int shape_89::get_current ( void )
{
    return m_current;
}

QString shape_89::out_i ( int i )
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

void shape_89::print_i ( int i )
{
    std_out << out_i ( i );
}

bool shape_89::is_index_good ( int i ) const
{
    return ( i >= 0 && i < get_n_segment() );
}

int shape_89::removeAt ( int ref_pos )
{
    if ( !is_multi_form() )
        return 1;

    if ( !is_index_good ( ref_pos ) )
        return 2;

    m_bites.removeAt ( 2*ref_pos + 1 );

    m_bites.removeAt ( 2*ref_pos + 1 );

    if ( m_bites.size() == 5 )
    {
        m_bites.removeLast();
        m_bites.removeLast();
        m_bites[0] = 8;
    }

    return 0;
}

bool shape_89::is_validate() const
{
    return is_index_good(m_current);
}

void shape_89::Validate()
{
    set_current(m_current);
}

// kate: indent-mode cstyle; space-indent on; indent-width 0; 
