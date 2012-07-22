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

#ifndef DIALOG_FONT_HEADER_H
#define DIALOG_FONT_HEADER_H

#include "ui_dialog_font_header.h"
#include "edit_menu.h"
#include "main_form.h"

///Диалог, предназначенный для редактирования атрибутов шрифта (класс font).
class DialogFontHeader : public QDialog
{
		Q_OBJECT

	public:
		DialogFontHeader ( QWidget *parent = 0 );
	
		void set_above ( int a );
		int get_above ( void ) const;

		void set_below ( int new_below );
		int get_below ( void ) const;

		void set_modes ( int new_modes );
		int get_modes ( void ) const;

		void set_attribute ( const QString & new_attribute );
		QString get_attribute ( void ) const;

		void set_m_edit_menu(edit_menu *);

	public slots:
	void accept ();

	private:
		Ui::DialogFontHeader ui;
		edit_menu *m_edit_menu;
};

#endif // FONT_HEADER_H
