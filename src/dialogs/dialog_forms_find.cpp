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

#include "dialog_forms_find.h"
#include "dialog_forms_find.moc"

DialogFormsFind::DialogFormsFind ( QWidget *parent ) : QDialog ( parent )
{
	ui.setupUi ( this );
}

void DialogFormsFind::set_m_mainform ( Main_Form *mform )
{
	m_main_form = mform;
}

void DialogFormsFind::accept ()
{
	QList<forma_l*> *flist = m_main_form->m_edit_menu->m_font->get_m_forma_l_list();
	QString str = ui.lineEdit->text();
	int rez = 0;

	if (	ui.rButton_Number->isChecked() ) //Искать по номеру
	{
		int num = str.toInt ();
		for ( int i = 0; i < flist->size();++i )
		{
			int num_test = flist->at ( i )->get_number();
			if ( num_test == num )
			{
				rez = i;
				m_main_form->set_m_current_forma_l ( rez );
			}
		}
	}
	if ( ui.rButton_Comment->isChecked() ) //Искать форму по комментарию
	{
		for ( int i = 0; i < flist->size();++i )
		{
			QString comment_test = flist->at ( i )->get_attribute();
			QRegExp rx ( str );
			rx.setPatternSyntax ( QRegExp::Wildcard );

			if ( rx.exactMatch ( comment_test ) )
			{
				rez = i;
				m_main_form->set_m_current_forma_l ( rez );
			}
		}
	}

	done ( QDialog::Accepted );
}
