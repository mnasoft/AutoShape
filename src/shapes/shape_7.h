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

#ifndef SHAPE_7_H
#define SHAPE_7_H

#include "shapes.h"

///Подформа вставки в отрисовываемую другой формы.
/**
Подформа вставки в отрисовываемую другой формы.\n
Переменная  var содержит номер вставляемой формы.

Code 7 draws the subshape number given by the next byte. For a non-Unicode font the specification byte following code 7 is a shape number from 1 to 255. For a Unicode font, code 7 is followed by a Unicode shape number from 1 to 65535. Unicode shape numbers should be counted as two bytes (for specific information about the differences between Unicode and non-Unicode fonts, see Unicode Font Descriptions). The shape with that number (in the same shape file) is drawn at this time. Draw mode is not reset for the new shape. When the subshape is complete, drawing the current shape resumes.
*/

class shape_7: public shapes
{

	public:
		/*******************  К О Н С Т Р У К Т О Р Ы **************************/
		shape_7 ( void );																///<Контруктор.
		shape_7 ( int ref_number );											///<Контруктор.
		~shape_7();																			///<Деструктор.
		/************************* Функции доступа *************************/
		void set_ref_number ( int ref_number );					///<Задает номер ссылочного символа
		int get_ref_number ( void );										///<Возвращает номер ссылочного символа
		/*********************************** Виртуальные функции класса shapes ***********************************/
		virtual void				draw ( draw_vars & dr,
		                       stack &,
		                       QGraphicsScene & sc,
		                       int color,
		                       int color_,
		                       int priznak );						///<Рисовать форму
		virtual QString			out	( void );								///<Вывод символьного представления формы в QString.
		virtual QString			out_comment ( void );				///<Вывод содержимого формы в удобном для восприятия формате QString.
		virtual void 				edit ( void );							///<Редактирование формы.
		virtual int					get_lenth	( void );					///<Длина подформы.
		virtual shapes*			copy	( void );							///<Копирует подформу.
    virtual QString     type ( void ) const;        ///<Возвращает тип подформы.
};
#endif
