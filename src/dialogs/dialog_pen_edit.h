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

#ifndef DIALOG_PEN_EDIT_H
#define DIALOG_PEN_EDIT_H

#include "ui_dialog_pen_edit.h"
#include "shape_12.h"

///Диалог, предназначенный для редактирования подформ shape_12.
class DialogPenEdit : public QDialog
{
		Q_OBJECT

	public:
		DialogPenEdit ( QWidget *parent = 0 );

		void			set_pen ( bool theValue );
		bool			get_pen ( void );

		shape_12*	get_shape ( void );
		void			set_shape ( shape_12* );

	public slots:
		void			accept ();
		void			penUpChecked ( bool );
		void			penDownChecked ( bool );

	signals:
		void penChanged ( void );

	private:
		Ui::DialogPenEdit ui;

		bool m_pen;
		shape_12 * m_shape;
};

#endif
