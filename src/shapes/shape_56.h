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

#ifndef SHAPE_56_H
#define SHAPE_56_H

#include "shapes.h"

///Подформа записи-извлечения из стека положения пера.
/**
Подформа записи-извлечения из стека положения пера.
При
- var = 5 осуществляется запись текущего положения пера в стек;
- var = 6 осуществляется перемещение пера в предварительно записанное положение.

Code 5 pushes (saves) and code 6 pops (restores) the current coordinate position while drawing a shape so that you can return to it from a later point in the shape. You must pop everything you push. The position stack is only four locations deep. If the stack overflows because of too many pushes or too many missing pops, the following message is displayed when the shape is drawn.

Position stack overflow in shape nnn

Similarly, if you try to pop more locations than have been pushed onto the stack, the following message is displayed when the shape is drawn.

Position stack underflow in shape nnn
*/

class shape_56: public shapes
{

	public:
		/*******************  К О Н С Т Р У К Т О Р Ы **************************/
		shape_56();																		///<Конструктор.
		shape_56 ( bool push ); 											///<Конструктор. Создает подформу проталкивающую положение в стек
		~shape_56();																	///<Деструктор.
		/************************* Функции доступа *************************/
		void set_push ( bool push );
		bool get_push ( void );
		/*********************************** Виртуальные функции класса shapes ***********************************/
		virtual void				draw ( draw_vars & dr, stack &, QGraphicsScene & sc);///<Рисовать форму
		virtual QString			out	( void );							///<Вывод символьного представления формы в QString.
		virtual QString			out_comment ( void );			///<Вывод содержимого формы в удобном для восприятия формате QString.
		virtual void 				edit ( void );						///<Редактирование формы.
		virtual int					get_lenth	( void );				///<Длина подформы.
		virtual shapes*			copy	( void );						///<Копирует подформу.
    virtual QString     type ( void ) const;      ///<Возвращает тип подформы.
};
#endif
