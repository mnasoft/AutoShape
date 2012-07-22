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

#include "dialog_line_edit.h"
#include "dialog_line_edit.moc"

extern Main_Form	*theMainForm;

DialogLineEdit::DialogLineEdit ( QWidget *parent )
        : QDialog ( parent )
        , m_shape ( 0 )
{
    ui.setupUi ( this );
}

void DialogLineEdit::accept ()
{
    m_radius = ui.spBoxLength->value();
    m_sixtant = ui.spBox_Direction->value();
//	emit lineChanged();

    done ( QDialog::Accepted );
}

void DialogLineEdit::set_radius ( int theValue )
{
    ui.spBoxLength->setValue ( theValue );
    m_radius = ui.spBoxLength->value();
}

int DialogLineEdit::get_radius ( void )
{
    return m_radius;
}

void DialogLineEdit::set_sixtant ( int theValue )
{
    ui.spBox_Direction->setValue ( theValue );
    m_sixtant = ui.spBox_Direction->value();
}

int DialogLineEdit::get_sixtant ( void )
{
    return m_sixtant;
}

shape_*	DialogLineEdit::get_shape ( void )
{
    return m_shape;
}

void DialogLineEdit::set_shape ( shape_* theValue )
{
    m_shape = theValue;
}

void DialogLineEdit::set_ShapeLength ( int theValue )
{
    shape_ *sh = get_shape();
    if ( sh )
        sh->set_length ( theValue );

    emit lineChanged();
// 	if ( m_main_form )
// 		m_main_form->reDrawCurrentFormInFoma_l();
}

void DialogLineEdit::set_ShapeDirection ( int theValue )
{
    shape_ *sh = get_shape();
    if ( sh )
        sh->set_sixtant ( theValue );

    emit lineChanged();
// 	if ( m_main_form )
// 		m_main_form->reDrawCurrentFormInFoma_l();
}
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
