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

#include "dialog_pen_edit.h"
#include "dialog_pen_edit.moc"

DialogPenEdit::DialogPenEdit ( QWidget *parent )
		: QDialog ( parent )
		, m_shape ( 0 )
{
	ui.setupUi ( this );
}

void DialogPenEdit ::accept ()
{
	m_pen = ui.rButton_PenDown->isChecked();

	done ( QDialog::Accepted );
}

shape_12* DialogPenEdit::get_shape ( void )
{
	return m_shape;
}

void DialogPenEdit::set_shape ( shape_12* theValue )
{
	m_shape = theValue;
}

void DialogPenEdit::penUpChecked ( bool theValue )
{
	if ( m_shape )
		m_shape->set_pen_up ( theValue );

	emit penChanged();
}

void DialogPenEdit::penDownChecked ( bool theValue )
{
	if ( m_shape )
		m_shape->set_pen_down ( theValue );

	emit penChanged();
}

void DialogPenEdit::set_pen ( bool theValue )
{
	ui.rButton_PenDown->setChecked ( theValue );
	ui.rButton_PenUp->setChecked ( !theValue );
	m_pen = ui.rButton_PenDown->isChecked();
}

bool DialogPenEdit::get_pen ( void )
{
	return m_pen;
}
