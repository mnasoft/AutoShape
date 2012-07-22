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

#ifndef DIALOG_SCALE_EDIT_H
#define DIALOG_SCALE_EDIT_H

#include "ui_dialog_scale_edit.h"
#include "shape_34.h"

///Диалог, предназначенный для редактирования подформ shape_34.
class DialogScaleEdit : public QDialog
{
		Q_OBJECT

	public:
		DialogScaleEdit ( QWidget *parent = 0 );

		void		set_scaleUp ( bool theValue );
		bool		get_scaleUp ( void );

		void		set_scaleFactor ( int theValue );
		int			get_scaleFactor ( void );

		shape_34*	get_shape ( void );
		void			set_shape ( shape_34* );

	public slots:
		void accept ();
		void scaleFactorChanged(int);
		void scaleDownClicked(bool);
		void scaleUpClicked(bool);

	signals:
		void scaleChanged ( void );

	private:
		Ui::DialogScaleEdit ui;
		
		bool		m_scaleUp;
		int			m_scaleFactor;

		shape_34 * m_shape;
};

#endif
