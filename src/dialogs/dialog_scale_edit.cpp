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

#include "dialog_scale_edit.h"
#include "dialog_scale_edit.moc"

DialogScaleEdit::DialogScaleEdit ( QWidget *parent ) 
: QDialog ( parent )
, m_shape(0)
{
	ui.setupUi ( this );
}

void DialogScaleEdit::accept ()
{
	m_scaleUp = ui.rButton_ScaleUp->isChecked();
	m_scaleFactor = ui.spBoxScale->value();

	done ( QDialog::Accepted );
}

void DialogScaleEdit::scaleFactorChanged ( int theValue )
{
	if ( m_shape )
		m_shape->set_scale_factor( theValue );

	emit scaleChanged();
}

void DialogScaleEdit::scaleDownClicked ( bool theValue )
{
	if ( m_shape )
		m_shape->set_scale_up( !theValue );

	emit scaleChanged();
}

void DialogScaleEdit::scaleUpClicked ( bool theValue )
{
	if ( m_shape )
		m_shape->set_scale_up( theValue );

	emit scaleChanged();
}

void		DialogScaleEdit::set_scaleUp ( bool theValue )
{
	ui.rButton_ScaleUp->setChecked ( theValue );
	ui.rButton_ScaleDown->setChecked ( !theValue );
	m_scaleUp = ui.rButton_ScaleUp->isChecked();
}

bool		DialogScaleEdit::get_scaleUp ( void )
{
	return m_scaleUp;
}

void DialogScaleEdit::set_scaleFactor ( int theValue )
{
	ui.spBoxScale->setValue ( theValue );
	m_scaleFactor = ui.spBoxScale->value();
}

int DialogScaleEdit::get_scaleFactor ( void )
{
	return m_scaleFactor;
}

shape_34* DialogScaleEdit::get_shape ( void )
{
	return m_shape;
}

void DialogScaleEdit::set_shape ( shape_34* theValue)
{
	m_shape=theValue;
}
