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

#ifndef SHAPE__H
#define SHAPE__H

#include "shapes.h"
#include <QtGlobal>


///Представляет форму перемещения пера по одному из 16 направлений (от 0 до F (15)) на расстояние от 1 до F(15) единиц.

/**
При увеличении номера направления происходит поворот направлений против часовой стрелки.
Направление 0 - вправо E; 2 - вправо вверх NE; 1 - между 1-м и 2-м направлением NE-E; и т.д.

\image html shapes.jpg "Направление векторов" width=10cm
*/

class shape_: public shapes
{

private:
    void byte_to ( void );

public:
    /*******************  К О Н С Т Р У К Т О Р Ы **************************/
    shape_ ( void );                                ///<Конструктор.
    shape_ ( int Bite );                            ///<Конструктор.
    shape_ ( int Radius, int Octant );              ///<Конструктор.
    ~shape_();                                      ///<Деструктор.
    /************************* Функции доступа *************************/
    void set_byte ( int a );
    void set_length ( int );
    void set_sixtant ( int );

    int get_byte ( void ) const;                      ///<Возвращает байт.
    int get_length ( void ) const;                    ///<Возвращает радиус.
    int get_sixtant ( void ) const;                   ///<Возвращает направление.
    draw_point get_delta_p ( void ) const;                ///<Возвращает точку с координатами соответствующими приращению к месту положения пера после отрисовки формы.
    /*********************************** Виртуальные функции класса shapes ***********************************/
    virtual void        draw ( draw_vars & dr, stack &, QGraphicsScene & sc);///<Рисовать форму
    virtual QString     out ( void );               ///<Вывод символьного представления формы в QString.
    virtual QString     out_comment ( void );       ///<Вывод содержимого формы в удобном для восприятия формате QString.
    virtual void        edit ( void );              ///<Редактирование формы.
    virtual int         get_lenth ( void );         ///<Длина подформы в байтах.
    virtual shapes*     copy  ( void );             ///<Копирует подформу.
    virtual QString     type ( void ) const;      ///<Возвращает тип подформы.
};

#endif
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
