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

#ifndef DRAW_POINT_H
#define DRAW_POINT_H

#include <QtGlobal>

///Класс пердставляющий вещественную точку.
/**Класс пердставляющий вещественную точку.\n
 Досуп коордиинатам осуществляется через
- x - Координата x.
- y - Координата y.
Для элементов класса определены операции сложения (+), вычитания (+), +=, -=.
*/

class draw_point
{

public:
    ///Координата x.
    qreal x ;
    ///Координата y.
    qreal y;
public:
    draw_point ( void );
    draw_point ( qreal x, qreal y );
    draw_point ( const draw_point &p );

    draw_point & set(qreal X, qreal Y);

    qreal dist_sc(const draw_point & pt) const;				///<Возвращает квадрат расстояния между двумя кочками.
    qreal dist(const draw_point & pt) const;					///<Возвращает расстояние между двумя кочками.
    qreal agnle(const draw_point & pt) const;					///<Возвращает угол в радианах под которым точка pt видна из точки *this.
    draw_point polar (qreal ang, qreal dist) const;		///<Возвращает точку смещенную относительно *this на расстояние dist в направлении угла ang.

    draw_point& operator= ( const draw_point &p );		///<Операция присваивания.

    draw_point& operator+= ( const draw_point &p ) ;	///<Перемещает точку на вектор p.
    draw_point& operator-= ( const draw_point &p ) ;	///<Перемещает точку на вектор -p.

    draw_point operator+ ( const draw_point &p ) const;		///<Возвращает результат перемещения точки на вектор p.
    draw_point operator- ( const draw_point &p ) const;		///<Возвращает результат перемещения точки на вектор -p.

    draw_point operator* ( qreal scale ) const;						///<Умножает вектор this в scale раз.
    draw_point operator/ ( qreal scale ) const;						///<Делит вектор this в scale раз.

    static qreal dtr(qreal digit);												///<Возвращает результат перевода из градусов в радианы.
    static qreal rtd(qreal radian);												///<Возвращает результат перевода из радиан в градусы.
};

#endif
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
