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

#ifndef SHAPE_E_H
#define SHAPE_E_H

#include "shapes.h"

///Подформа для придания шрифту вертикального расположения.

/**Подформа для придания шрифту вертикального расположения.*/

class shape_e: public shapes
{

	public:
		/*******************  К О Н С Т Р У К Т О Р Ы **************************/
		shape_e ( void );																///<Конструктор.
		~shape_e();																			///<Деструктор.

		/************************* Функции доступа *************************/

		/*********************************** Виртуальные функции класса shapes ***********************************/
		virtual void				draw ( draw_vars & dr, stack &, QGraphicsScene & sc);///<Рисовать форму
		virtual QString			out	( void );								///<Вывод символьного представления формы в QString.
		virtual QString			out_comment ( void );				///<Вывод содержимого формы в удобном для восприятия формате QString.
		virtual void 				edit ( void );							///<Редактирование формы.
		virtual int					get_lenth	( void );					///<Длина подформы.
		virtual shapes*			copy	( void );							///<Копирует подформу.
    virtual QString     type ( void ) const;        ///<Возвращает тип подформы.
};

#endif
