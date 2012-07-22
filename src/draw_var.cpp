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

#include "draw_var.h"

#include <QStringList>
#include <QTextStream>
#include <QFile>

#include "menu.h"


QColor draw_vars::s_color_pen_down = Qt::cyan;
QColor draw_vars::s_color_pen_up = Qt::red;
QColor draw_vars::s_color_12 = Qt::blue;
QColor draw_vars::s_color_34 = Qt::blue;
QColor draw_vars::s_color_56 = Qt::blue;
QColor draw_vars::s_color_7 = Qt::black;
QColor draw_vars::s_color_cur = Qt::magenta;
QColor draw_vars::s_color_9d = Qt::blue;
QColor draw_vars::s_color_e = Qt::black;

int draw_vars::s_width_pen_down = 4;
int draw_vars::s_width_pen_up = 2;
int draw_vars::s_width_12 = 2;
int draw_vars::s_width_34 = 2;
int draw_vars::s_width_56 = 2;
int draw_vars::s_width_7 = 2;
int draw_vars::s_width_cur = 4;
int draw_vars::s_width_9d = 2;
int draw_vars::s_width_e = 2;

QRect draw_vars::net_hor(-30,-10,60,15);
QRect draw_vars::net_ver(-30,-10,60,15);

bool draw_vars::s_drawHorisontal = false;
bool draw_vars::s_drawAll = true;
bool draw_vars::s_drawNet = true;


void menu_create ( void )
{

}

void draw_vars::print ( void )
{
    /*
      set_viewport ( mes_scr );
      string_to_display ( "*** DROW_VAR***", 5, 205 );
      sprintf ( msg, "  x   = %8.2f", x );
      string_to_display ( msg, 5, 215 );
      sprintf ( msg, "  y   = %8.2f", y );
      string_to_display ( msg, 5, 225 );
      sprintf ( msg, "masht = %8.2f", masht );
      string_to_display ( msg, 5, 235 );

      if ( pero == draw_vars::s_color_pen_down )  string_to_display ( "Pen up:", 5, 245 );

      if ( pero == draw_vars::s_color_pen_down ) string_to_display ( "Pen down:", 5, 245 );

      if ( flag ) string_to_display ( "Vertical", 5, 255 );
      else string_to_display ( "Horizontal", 5, 255 );

      sprintf ( msg, "dist  = %8d", dist );

      string_to_display ( msg, 5, 265 );
    */
}

draw_vars::draw_vars ( void )
{
    set_initial();
}

draw_vars & draw_vars::operator=( const draw_vars & a )
{
    p = a.p;
    p0 = a.p0;

    marker_size = a.marker_size;

    p0v = a.p0v;
    p0h = a.p0h;

    pero = a.pero;
    masht = a.masht;

    drawAsVerticalFlag = a.drawAsVerticalFlag;
    drawWhisOutPenUpMovementFlag = a.drawWhisOutPenUpMovementFlag;

    above = a.above;
    dist = a.dist;
    cur = a.cur;
    return *this;
}

void draw_vars::set_initial( void )
{
    p0v.x = 200.;
    p0v.y = 100.;//Точка начала для вертикального расположения шрифта.
    p0h.x = 150.;
    p0h.y = 300.;//Точка начала для горизонтального расположения шрифта.

    p0 = p0v;

    p.x = 0;
    p.y = 0;

    pero = true;
    masht = 1.0;

    marker_size = 5;
    drawAsVerticalFlag = true;
    drawWhisOutPenUpMovementFlag = false;
    above = 1;
    dist = 1;
    cur = 0;
}

draw_vars::draw_vars ( const draw_vars  & a )
{
    p = a.p;
    p0 = a.p0;

    marker_size = a.marker_size;

    p0v = a.p0v;
    p0h = a.p0h;

    pero = a.pero;
    masht = a.masht;

    drawAsVerticalFlag = a.drawAsVerticalFlag;
    drawWhisOutPenUpMovementFlag=a.drawWhisOutPenUpMovementFlag;

    above = a.above;
    dist = a.dist;
    cur = a.cur;
}

//draw_point draw_vars::otn_to_abs ( void )
draw_point draw_vars::otn_to_abs ( draw_point p_otn )
{
    draw_point p_abs;
    p_abs.x = p0.x + p_otn.x ;
    p_abs.y = p0.y - p_otn.y ;
    return p_abs;
    /*
      x_a = x0 + x * coeff;
      y_a = y0 - y * coeff;
    */
}

draw_point draw_vars::abs_to_otn ( draw_point p_abs )
//void draw_vars::abs_to_otn(qreal  x_a,  qreal  y_a )
{
    draw_point p_otn;
    p_otn.x = ( p_abs.x - p0.x ) ;
    p_otn.y = - ( p_abs.y - p0.y ) ;
    return p_otn;
}

//Работа с пером
void draw_vars::pero_down ( void )
{
    pero = true; //s_color_pen_down;
}

void draw_vars::pero_up ( void )
{
    pero = false; // s_color_pen_up;
}

bool  draw_vars::get_pero ( void )
{
    return pero;
}

/**Перо перемещается в координаты [X,Y].*/
void draw_vars::set_coords ( draw_point p_otn_new )
{
    p = p_otn_new;
}


void draw_vars::set_abs_coords ( draw_point p_abs )
{
    draw_point p_otv = abs_to_otn ( p_abs );;
    set_coords ( p_otv );
}

void draw_vars::move_coords ( draw_point dp_otn )
{
    p += dp_otn ;
}


void draw_vars::set_otn_coords ( draw_point p_otn )
{
    p = p_otn ;
}

draw_point draw_vars::get_p_abs ( void )
{
    draw_point p_abs;
    p_abs = otn_to_abs ( p );
    return p_abs;
}



/*
qreal draw_vars::get_x_abs ( void )
{
  draw_point p_abs;
  p_abs=otn_to_abs(p);
  return p_abs.x;
}

qreal draw_vars::get_y_abs ( void )
{
  draw_point p_abs;
  p_abs=otn_to_abs(p);
  return p_abs.y;
}
*/

draw_point draw_vars::get_p_otn ( void )
{
    return p;
}

/*
qreal draw_vars::get_x_otn ( void )
{
  return p.x;
}

qreal draw_vars::get_y_otn ( void )
{
  return p.y;
}
*/

//Работа с цветом, для отрисовки формы-предка.



void draw_vars::set_dist ( int a )
{
    if ( a == 0 ) dist = 1;

    if ( a >= 1 ) dist = a;
    else if ( above >= 1 ) dist = above;
}

/**<При flag=1-текст вертикальный;\n
при flag=0-текст горизонтальный).
*/
/*
void draw_vars::set_flag ( int a )
{
  if ( a )
  {
    flag = 1;
    p0 = p0v;
  }

  else
  {
    flag = 0;
    p0 = p0h;
  }

}
*/

bool draw_vars::drawAsVertical(void)
{
  return !s_drawHorisontal;
}

bool draw_vars::drawAsHorisontal(void)
{
  return s_drawHorisontal;
}

void draw_vars::set_drawAsVertical(bool a_vertical)
{
    drawAsVerticalFlag=a_vertical;
    return;
}

void draw_vars::set_drawAsHorisontal(bool a_horisontal)
{
    drawAsVerticalFlag=!a_horisontal;
    return;
}

bool draw_vars::drawWhisOutPenUpMovement(void)
{
    return drawWhisOutPenUpMovementFlag;
}

void draw_vars::set_drawWhisOutPenUpMovement(bool flag)
{
    drawWhisOutPenUpMovementFlag=flag;
    return ;
}

void draw_vars::draw_marker ( QGraphicsScene & sc )
{
    draw_point p_start = get_p_otn();         //Начальная точка дуги.
    draw_point p_delta(0.5,0.5);
    QRectF rect( 0.0, 0.0, p_delta.x, p_delta.y );
    rect.moveCenter ( QPointF(p_start.x, p_start.y));


    QPen pen ( QBrush
               ( QColor ( draw_vars::s_color_7 ), Qt::SolidPattern ),
               qreal ( draw_vars::s_width_7 ) ,
               Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );

    pen.setCosmetic ( true );
    sc.addEllipse ( rect,  pen);
}

void draw_vars::read ( const QString & name, const QString &  marker )
{

    QFile file ( name );
    bool rez_open_file  = file.open ( QIODevice::ReadWrite );
    QString header;

    if ( rez_open_file )
    {
        QTextStream in_file ( &file );

        while ( !in_file.atEnd () )
        {
            header = "";
            in_file >> header;

            if ( header == marker )
            {
                in_file >> p0.x >> p0.y; //<Начало относительных координат
                in_file >> p0v.x >> p0v.y;//<Начало относительных координат для вертикального шрифта
                in_file >> p0h.x >> p0h.y;//<Начало относительных координат для горизонтального шрифта
                in_file >> dist ;//<Расстояние между линиями сетки.
                in_file >> marker_size ;//<Размер маркера.
                int a_drawasverticalflag;
                in_file >> a_drawasverticalflag ;
                drawAsVerticalFlag= bool(a_drawasverticalflag);

                int a_drawwhisoutpenupmovementflag;
                in_file >> a_drawwhisoutpenupmovementflag;
                drawWhisOutPenUpMovementFlag=bool(a_drawwhisoutpenupmovementflag);

//        in_file >> color;//Цвет.
//        in_file >> color_marker;//<Цвет маркера.
                return;
            }
        }

        file.close ();
    }
}

void draw_vars::write ( const QString & name, const QString &  marker )
{
    QFile file ( name );
    bool rez_open_file = file.open ( QIODevice::WriteOnly | QIODevice::Append );

    if ( rez_open_file )
    {
        QTextStream out_file ( &file );
        {
            out_file << "\n" << marker << "\n";
            out_file << p0.x << " " << p0.y << "\n" ;//Начало относительных координат
            out_file << p0v.x << " " << p0v.y << "\n";//Начало относительных координат для вертикального шрифта
            out_file << p0h.x << " " << p0h.y << "\n";//Начало относительных координат для горизонтального шрифта
            out_file << dist << "\n";//Расстояние между линиями сетки.
            out_file << marker_size << "\n";//Размер маркера.
            out_file <<  int(drawAsVerticalFlag) << "\n";
            out_file <<  int(drawWhisOutPenUpMovementFlag) << "\n";
//      out_file << color << "\n";//Цвет.
//      out_file <<  color_marker << "\n";//Цвет маркера.
            file.close ();
        }
    }
}


void draw_vars::set_horver_coords ( draw_point p_abs )
{
    p0 = p_abs;

    if ( drawAsVerticalFlag )   p0v = p0;
    else    p0h = p0;
}

//Работа с масштабом
void draw_vars::multipli_masht ( qreal a )
{
    masht *= a;
}

void draw_vars::devided_masht ( qreal a )
{
    masht /= a;
}

void draw_vars::set_masht ( qreal a )
{
    masht = a;
}

qreal  draw_vars::get_masht ( void )

{
    return masht ;
}

///Задает габариты сетки.
void draw_vars::set_above ( int  a )
{
    above = a;
}

void draw_vars::set_dist ( int );///<Задает расстояния между линиями сетки.


void draw_vars::draw ( QGraphicsScene & sc )
{
    draw_point p_start = get_p_otn();         //Начальная точка дуги.
    int x1, y1, x2, y2;
    net_hor.getCoords(&x1, &y1, &x2, &y2);
    QPen pen ( QBrush
               ( QColor ( draw_vars::s_color_7 ), Qt::SolidPattern ),
               qreal ( 1 ) ,
               Qt::SolidLine, Qt::RoundCap, Qt::RoundJoin );

    pen.setCosmetic ( true );
    if (draw_vars::s_drawNet == true)
    {
        for (int i=y1;i<=y2;++i)
            sc.addLine ( p_start.x+x1, p_start.y+i, p_start.x+x2, p_start.y+i, pen);

        for (int i=x1;i<=x2;++i)
            sc.addLine ( p_start.x+i, p_start.y+y1, p_start.x+i, p_start.y+y2, pen);

    }
}
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
