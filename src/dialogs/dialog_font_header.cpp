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

#include "dialog_font_header.h"
#include "dialog_font_header.moc"

DialogFontHeader::DialogFontHeader ( QWidget *parent ) :
QDialog(parent)
{
	ui.setupUi ( this );
}

void DialogFontHeader::accept ()
{
	int above = get_above();
	int below = get_below();
	int modes = get_modes();
	QString attribute = get_attribute();

	m_edit_menu->m_font->set_above(above);
	m_edit_menu->m_font->set_below(below);
	m_edit_menu->m_font->set_modes(modes);
	m_edit_menu->m_font->set_attribute(attribute);

	done ( QDialog::Accepted );
}

void DialogFontHeader::set_above ( int new_above )
{
	QString str = QString::number ( new_above );
	this->ui.lineEditAbove-> setText ( str );
}

int DialogFontHeader::get_above ( void ) const
{
	QString str = this->ui.lineEditAbove-> text();
	bool ok;
	int rez = str.toInt ( & ok );

	if ( ok )
		return rez;
	else
		return 10;
}

void DialogFontHeader::set_below ( int new_below )
{
	QString str = QString::number ( new_below );
	this->ui.lineEditBelow-> setText ( str );
}

int DialogFontHeader::get_below ( void ) const
{
	QString str = this->ui.lineEditBelow->text();
	bool ok;
	int rez = str.toInt ( & ok );

	if ( ok )
		return rez;
	else
		return 10;
}

void DialogFontHeader::set_modes ( int new_modes )
{
	if (new_modes == 0)
		this->ui.checkBoxModes->setChecked ( false );
	else
		this->ui.checkBoxModes->setChecked ( true );

//QCheckBox *checkBoxModes
}

int DialogFontHeader::get_modes ( void ) const
{
	bool checked = this->ui.checkBoxModes->isChecked ( );
	if (checked)
		return 2;
	else
		return 0;
}

void DialogFontHeader::set_attribute ( const QString & new_attribute )
{
	QString str ( new_attribute );
	this->ui.lineEditAttribute-> setText ( str );
}

QString DialogFontHeader::get_attribute ( void ) const
{
	QString rez = this->ui.lineEditAttribute-> text ();
	return rez;
}

void DialogFontHeader::set_m_edit_menu(edit_menu * emenu)
{
	m_edit_menu=emenu;
}
