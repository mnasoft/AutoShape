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

#ifndef SHAPE_34_H
#define SHAPE_34_H

#include "shapes.h"

///Подформа управляющая масштабом.
/**
Подформа управляющая масштабом.
При
- var = 3 масштаб увеличивается на monz;
- var = 4 масштаб уменьшается на monz.

Коды 3 и 4 управляют относительным масштабом каждого вектора. The height specified with the SHAPE command is initially considered the length of a single orthogonal vector (direction 0, 4, 8, or C). Код 3 делит длины векторов на следующий байт. Код 4 умножает длины векторов на последующий байт. За кодами 3 и 4 следует спецификационный байт, содержащий целочисленный масштабный фактор (от 1 до  255). If you want the shape height to specify the size of the entire shape, and you use 10 vector lengths to draw it, you can use 3,10 to scale the height specification. The scale factor is cumulative within a shape; that is, multiplying by 2 and again by 6 results in a scale factor of 12. Usually, you should reverse the effect of your scale factors at the end of the shape, especially for subshapes and text font shapes. AutoCAD does not reset the scale factor for you.
*/

class shape_34: public shapes
{

	public:
		/*******************  К О Н С Т Р У К Т О Р Ы **************************/
		shape_34 ( void );															///<Конструктор.
		shape_34 ( bool scale_up, int scale_factor );		///<Конструктор.
		~shape_34();																		///<Деструктор.
		/************************* Функции доступа *************************/
		void set_scale_up	( bool scale_up ); 						///<Задание направления масштабирования
		void set_scale_factor ( int scale_factor );			///<Задание масштаба

		void set ( bool scale_up, int scale_factor );

		bool get_scale_up	( void );											///<Возврашает направление масштабирования 
		int get_scale_factor	( void );									///<Возврашает масштаб scale=1..255

		double get_scale ( void );											///<Возврашает масштаб
		/*********************************** Виртуальные функции класса shapes ***********************************/
		virtual 	void			draw ( draw_vars & dr, stack &, QGraphicsScene & sc);///<Рисовать форму
		virtual QString			out	( void );								///<Вывод символьного представления формы в QString.
		virtual QString			out_comment ( void );				///<Вывод содержимого формы в удобном для восприятия формате QString.
		virtual void 				edit ( void );							///<Редактирование формы.
		virtual int					get_lenth	( void );					///<Возвращает длину подформы в байтах.
		virtual shapes*			copy	( void );							///<Копирует подформу.
    virtual QString     type ( void ) const;        ///<Возвращает тип подформы.
};

#endif
