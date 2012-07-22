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

#ifndef FORMA_H
#define FORMA_H

#include <QList>
#include <QString>

#include "menu.h"
#include "shapes.h"

class forma_l;

///Владелец подформ.

class forma
{
	public:
		forma ( void );																			///<Конструктор.
		forma ( forma const & new_forma );									///<Конструктор.
		forma&		operator= ( forma const  & new_forma_l );	///<Оператор присваивания
		~forma ( void );																		///<Деструктор.
		void 			clear_m_shapes();													///<Очистка подформ.

		QString		out ( void ) const;												///<Метод печати.
		void			out_file ( FILE* du );										///<Метод вывода в файл.
		void 			draw ( draw_vars &,
		               stack &,
		               QGraphicsScene & sc );								///<Метод рисования.
//		void			edit ( draw_vars &, stack & );						///<Метод редактирования.
		int				get_lenth ( void ) const;									///<Возвращает длину формы.

//		shapes*		menu_shape_insert();											///<
		void			set_parent ( forma_l* new_parent );				///<Установить владельца.
		forma_l*	get_parent() const;												///<Возвратить владльца.

		QList<shapes*>*	get_m_shapes() ;										///<Возвращает список указателей на подформы.

	private:
		QList<shapes*> m_shapes;														///<Список указателей на подформы.
		forma_l* parent;																		///<Указатель на базовую форму.
		//Статические члены
		static long forma_count;														///<Количество форм.

		void init_forma();
};
#endif
