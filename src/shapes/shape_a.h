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

#ifndef SHAPE_A_H
#define SHAPE_A_H

#include "shapes.h"

///Подформа, перемещающая перо по октантной дуге.
/**
Подформа характеризуется следующими атрибутами:
- radius - радиус дуги. Может принимать значение от 1 до 255;
- start - целое число от 0 до 7 представляющее направление вектора, идущего из центра дуги в ее начало;
- number - целое число от -7 до 7 пердставляющее количество октантов дуги.


Special code 00A (or 10) uses the next two specification bytes to define an arc. This is called an octant arc because it spans one or more 45-degree octants, starting and ending on an octant boundary. Octants are numbered counterclockwise from the 3 o'clock position, as shown in the following illustration.

The arc specification is

10,radius,(-)0SC
The radius can be any value from 1 through 255. The second specification byte indicates the direction of the arc (counterclockwise if positive, and clockwise if negative), its starting octant (s, a value from 0 through 7), and the number of octants it spans (c, a value from 0 through 7, in which 0 equals eight octants, or a full circle). You can use parentheses to improve readability. For example, consider the following fragment of a shape definition:

...012,10,(1,-032),01E,...
This code draws a one-unit vector up and to the right, a clockwise arc from octant 3 (with a radius of one unit for two octants), and then a one-unit vector down and to the right, as shown in the following illustration.
*/

class shape_a: public shapes
{

	public:
		/*******************  К О Н С Т Р У К Т О Р Ы **************************/
		shape_a ( void );																///<Конструктор.
		shape_a ( int R, int S, int N );								///<Конструктор.
		shape_a ( int Byte_1, int Byte_2 );							///<Конструктор.
		~shape_a();                   									///<Деструктор.

		/************************* Функции доступа *************************/
		void set_radius ( int );                				///<Устанавлвиает значение радиуса.
		void set_start ( int );													///<Устанавливает значение начального октанта.
		void set_number ( int );												///<Устанавливает значение количества октантов.

		int get_radius ( void ) const;									///<Возвращает значение радиуса.
		int get_octant_start ( void ) const;						///<Возвращает значение начального октанта.
		int get_octant_number ( void ) const;						///<Возвращает значение количества октантов.
		int get_octant_end ( void ) const;							///<Возвращает значение количества октантов.

		/*********************************** Виртуальные функции класса shapes ***********************************/
		virtual void    draw ( draw_vars & dr, stack &, QGraphicsScene & sc); ///<Рисовать форму
		virtual QString   out ( void );       					///<Вывод символьного представления формы в QString.
		virtual QString   out_comment ( void );					///<Вывод содержимого формы в удобном для восприятия формате QString.
		virtual void     edit ( void );									///<Редактирование формы.
		virtual int     get_lenth ( void );							///<Длина подформы.
		virtual shapes*   copy ( void );								///<Копирует подформу.
    virtual QString     type ( void ) const;        ///<Возвращает тип подформы.
};

#endif
