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

#ifndef SHAPE_B_H
#define SHAPE_B_H

#include "shapes.h"

///Подформа, перемещающая перо по дуге, определяемой радиусом, начальным и конечным  углами, направлением отрисовки дуги.
/**
Подформа характеризуется следующими атрибутами:
	- radius - радиус дуги (от 1 до 255*256+255);
	- start_angle - начальный угол дуги (от 0 359);
	- end_angle - конечный угол дуги (от 0 359);
	- direction - направление отрисовки дуги (-1, 1).

Special code 00B (11) draws an arc that doesn't necessarily start and end on an octant boundary. The definition uses five specification bytes.\n

11,start_offset,end_offset,high_radius,radius,(-)0SC
The start_offset and end_offset represent how far from an octant boundary the arc begins or ends. The high_radius represents the most significant eight bits of the radius; the high radius will be 0 unless the radius is greater than 255 units. Multiply the high_radius value by 256 and add that value to the radius value to generate an arc radius greater than 255. The radius and ending specification byte are the same as for the octant arc specification (code 00A, described previously).

You determine the startoffset by calculating the difference in degrees between the starting octant's boundary (a multiple of 45 degrees) and the start of the arc. Then, you multiply this difference by 256 and divide by 45. If the arc starts on an octant boundary, its start offset is 0.

The end offset is calculated in a similar fashion, but you use the number of degrees from the last octant boundary crossed to the end of the arc. If the arc ends on an octant boundary, its end offset is 0.

For example, a fractional arc from 55 degrees to 95 degrees with a 3 unit radius would be coded as follows:

11,(56,28,0,3,012)
Here is the explanation:

start_offset     = 56 because ((55 - 45) * 256 / 45) = 56
end_offset       = 28 because ((95 - 90) * 256 / 45) = 28
high_radius      = 0  because (radius < 255)
radius           = 3
starting octant  = 1  because
arc starts in the 45 degree octant
ending octant    = 2  because
arc ends in the 90 degree octant
*/

class shape_b: public shapes
{

	public:
		/*******************  К О Н С Т Р У К Т О Р Ы **************************/
		shape_b ( void );																		///<Конструктор.
		shape_b ( int R, int S, int E, int Dir );						///<Конструктор.
		shape_b ( int B1, int B2, int B3, int B4, int B5 );	///<Конструктор.
		~shape_b();																					///<Деструктор.
		/************************* Функции доступа *************************/
		void set_radius ( int Radius );											///<Устанавлвиает значение радиуса.

		void set_start ( int Start_direction, int Dir );		///<Устанавливает значение начального угла дуги.
		void set_end ( int End, int Dir );									///<Устанавливает значение конечного угла дуги.
		void set ( int Radius, int Start_angle, int End_angle, int Dir );
		void set_dir(int Dir);															///<Устанавливает значение направления отрисовки дуги.

		int  get_radius ( void ) const;											///Возвращает радиус дуги (1..256*255+255).

		int get_start ( void ) const;												///<Возвращает начальный угол дуги (0..359).
		int get_end ( void ) const;													///<Возвращает конечный угол дуги (0..359).
		int get_delta ( void ) const;												///<Возвращает центральный угол дуги (1..360).
		int get_dir ( void ) const;													///<Возвращает направление отрисовки формы (-1,1).
		/*********************************** Виртуальные функции класса shapes ***********************************/
		virtual void				draw ( draw_vars & dr, stack &, QGraphicsScene & sc); ///<Рисовать форму
		virtual QString			out	( void );										///<Вывод символьного представления формы в QString.
		virtual QString			out_comment ( void );						///<Вывод содержимого формы в удобном для восприятия формате QString.
		virtual void 				edit ( void );									///<Редактирование формы.
		virtual int					get_lenth	( void );							///<Длина подформы.
		virtual shapes*			copy	( void );									///<Копирует подформу.
    virtual QString     type ( void ) const;        ///<Возвращает тип подформы.
};

#endif
