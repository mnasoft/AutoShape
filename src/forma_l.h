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

#ifndef FORMA_L_H
#define FORMA_L_H

#include "forma.h"

#include <QList>
#include <QTextStream>

class font;

///Символы шрифта.
/**
Символы шрифта.\n
*/

class forma_l
{
	public:

		forma_l ( void ); 																			///<Конструктор.
		forma_l ( forma_l  const  & new_forma_l );							///<Конструктор копирования.

		forma_l & operator= ( forma_l const  & new_forma_l );		///<Оператор присваивания
		~forma_l ( void );																			///<Деструктор

		void 		set_Initial ( void );														///<Очистка содержимого формы.

		QString get_attribute ( void ) const;										///<Возвращает значение поля attribute
		void 		set_attribute ( const QString & new_attribute );///<Устанавливает новое значение для поля attribute

		int			get_number ( void ) const;											///<Возвращает номер формы.
		void		set_number ( int new_number );									///<Устанавливает новое значение для поля number.

		forma*	get_m_forma();																	///<Возвращает указатель на элемент содержащий список подформ. (shapes).

		void		set_parent ( font* new_parent );								///<Устанавливает указатель на родительский объект.
		font*		get_parent ( void ) const;											///<Возвращает указатель на родительский объект.

		int			get_num_bites ( void ) ;												///<Возвращает количество байтов в символе.
		int			is_changed ( void );														///<Возвращает 0, еcли форма не изменялать.

		void				load_List_bites (const QList<int> & );			///<Загружает форму из байтового представления.
		QList<int>	get_List_bites (void) const;								///<Возврвщает байтовое представление формы.

		QString out ( void );																		///<Выводит содержимое формы в стринг в символьном представлении.

		QString out_header ( void );														///<Выводит содержимое заголовка формы в стринг в символьном представлении.

		QString out_shapes ( void );														///<Выводит подформы формы в стринг в символьном представлении.

		int 		in ( char* );																		///<Производит заполнение стринга строкой символов для данной формы
		int 		find ( int no );																///<Ищет в списке forma_l элемент с номером no.
		/**<Возвращает 0 если такого не нашлось, и его номер в протвном случае.*/

		void 		edit_header ( void );														///<Редактировать заголовок.
		void 		edit_record ( draw_vars &, stack & );						///<Редактировать байты.
		void 		print ( void );																	///<Печатать байты.

		void 		draw ( draw_vars &,
		              stack &,
		              QGraphicsScene & sc );										///<Метод рисования.
		void 		print_bites ( QTextStream & stream ) ;					///<Вывод содержимого байтов формы на консоль.
		void 		print_shapes ( QTextStream & stream ) ;					///<Вывод содержимого подформ на консоль.

		static int read_int_byte ( const QString& str );

	public:

		void clear_m_forma();
//		QList<int>			m_bites;																///<Байты формы


	private:
		static long			s_forma_l_count;

		QString					m_comment;															///<Символьная строка длиной до 32 символов
		long						m_number;																///<Номер формы в шрифте.
		int 						m_changed;															///<Признак того, была-ли форма изменена в процессе редактирования или нет.
		font *					m_parent;																///<Указатель на родителя
		forma *			 		m_forma;																///<Элемент, содержащий список подформ шрифта
		/**<Через этот элемент осуществляется: добавление; удаление; редактирование подформ символов шрифта*/

		static void			menu_init ( void );											///<Инициализация меню
		static void			menu_delete ( void );										///<Очистка меню

};
#endif
