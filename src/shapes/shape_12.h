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

#ifndef SHAPE_12_H
#define SHAPE_12_H

#include "shapes.h"

///Подформа управления положением пера.

/**
Подформа управления положением пера.\n
Перо может занимать два положения:
- перо опущено (поледующие формы, вызывающие перемещение пера будут отрисовываться);
- перо поднято (поледующие формы, вызывающие перемещение пера не будут отрисовываться).\n
В представлении формы шрифта Acad:
- 1, - опустить перо;
- 2, - поднять пера.

Code 0 marks the end of the shape definition.

Codes 1 and 2 control Draw mode. Draw is activated at the start of each shape. When Draw mode is turned on (code 1), the vectors cause lines to be drawn. When Draw mode is turned off (code 2), the vectors move to a new location without drawing.

*/

class shape_12: public shapes
{

	private:

	public:
		/*******************  К О Н С Т Р У К Т О Р Ы **************************/
		shape_12 ( void );															///<Конструктор.
		shape_12 ( bool pen_down );											///<Конструктор.
		~shape_12();																		///<Деструктор.
		/************************* Функции доступа *************************/
//		static void menu_init ( void );									///<Инициализация меню.

		void set_pen_up ( bool pen_up = true );					///<Метод задания положения пера.
		void set_pen_down ( bool pen_down = true );			///<Метод задания положения пера.

		bool is_pen_up ( void );												///<Производит проверку положения пера.
		bool is_pen_down ( void );											///<Производит проверку положения пера.
		/*********************************** Виртуальные функции класса shapes ***********************************/
		virtual 	void			draw ( draw_vars & dr, stack &, QGraphicsScene & sc);///<Рисовать форму
		virtual QString			out	( void );								///<Вывод символьного представления формы в QString.
		virtual QString			out_comment ( void );				///<Вывод содержимого формы в удобном для восприятия формате QString.
		virtual void 				edit ( void );							///<Редактирование формы.
		virtual int					get_lenth	( void );					///<Длина подформы в байтах.
		virtual shapes*			copy	( void );							///<Копирует подформу.
    virtual QString     type ( void ) const;        ///<Возвращает тип подформы.
};

#endif
