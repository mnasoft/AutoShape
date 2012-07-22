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

#ifndef MENU_H
#define MENU_H

#include <QString>
#include <QStringList>
#include <QDialog>

#include <QVBoxLayout>

///Класс, меню.
/**
Класс, меню.\n
Меню представляет из себя QWidget, наполненный кнопками QPushButton.\n
Добавить кнопки к меню можно используя функции:
- void addItem ( const QString & aItem )
- void addItems ( const QStringList & aItems ).\n
Для задания заголовка окна используйте функцию QWidget::setWindowTitle(QString) :
@code setWindowTitle (QString::fromUtf8("Заголовок меню")); @endcode

Для изменения положения меню используйте функцию базового класса QWidget::move ( int x, int y );
@code
	menu * menu_a = new menu ( );
	menu_a->move(120,50);
@endcode

@code
	menu * menu_a = new menu ( );
	menu_a->addItem ( "&File" );
	menu_a->addItem ( "&Open" );
	menu_a->addItem ( "C&lose" );
	menu_a->run();
@endcode
Знак "&" перед символом в строке, обозначающей имя кнопки, задает быструю клавишу для выбора этой кнопки (
Alt+символ).
*/

class menu: public QDialog
{
		Q_OBJECT
	public:
		QVBoxLayout * layout;													///<Менеджер размещения кнопок меню.
	private:
		int run_rez;																	///<Поле, содержащее последний выбор пользователя.
		/**<По умолчанию run_rez=-1.\n
		Если пользователь выбрал первый элемент меню - run_rez==0, \n если второй - run_rez==1, и т.д.
		*/
		QObject * run_object;													///<Поле,  содержащее последний выбор пользователя.
	private slots:
		void select();																///< Слот функция. Обрабатывает нажатие на кнопку меню. Возвращает
	public:
		menu ( QWidget *parent = 0 );									///< Конструктор по умолчанию.
		~menu ( void );																///< Деструктор.
		void show();																	///<Показывает меню.
		void hide();																	///<Скрывает меню.
		void run();																		///<Отображает меню. Сбрасывает значение поля run_rez=-1.
		/**<
		При выполнении пользовательского ввода поле run_rez принимает значение от 0 до n-1,
		где n - количество кнопок QPushButton в окне меню.
		*/
		void addItem ( const QString & aItem ); 			///< Добавляет элемент к списку меню.
		/**<
		@code
		menu * menu_a = new menu ( );
		menu_a->addItem ( "&File" );
		Знак "&" перед символом в строке, обозначающей имя кнопки, задает быструю клавишу для выбора этой кнопки.
		Добавленный элемент в примере выше можно выбрать при помощи комбинации  Alt+F.
		@endcode
		*/
		void addItems ( const QStringList & aItems );	///< Добавляет элементы к списку меню.
		/**<
		@code
		menu * menu_a = new menu ( );
		QStringList menu_str_lst;
		menu_str_lst << "&File" << "&Open" << "C&lose";
		menu_a->addItems ( menu_str_lst);
		@endcode
		*/
		int get_run_rez ( void ); 										///< Возвращает номер выбранного пользователем элемента меню.
		/**< Первый элемент имеет номер 0.*/
		QObject * get_run_object(void) ;							///< Возвращает указатель выбранного пользователем элемента меню.
		QPushButton * findByText(QString);						///< Возвращает указатель на объект указанным текстом.
};
#endif
