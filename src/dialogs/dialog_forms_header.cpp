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

#include "dialog_forms_header.h"
#include "dialog_forms_header.moc"

#include "QTextCodec"

DialogFormsHeader::DialogFormsHeader ( QWidget *parent ) : QDialog ( parent )
{
	ui.setupUi ( this );
	QList<QByteArray> codecs= QTextCodec::availableCodecs ();
	QStringList Codecs;
	for(int i=0;i<codecs.size();++i)
	{
		Codecs<<QString(codecs[i]);
	}
	Codecs.sort();
	ui.cBox_CodePage-> addItems ( Codecs );
}

void DialogFormsHeader::set_m_mainform ( Main_Form *mform )
{
	m_main_form = mform;

	QList<forma_l*> *flist = m_main_form->m_edit_menu->m_font->get_m_forma_l_list();

	forma_l	*a = (*flist)[m_main_form->get_m_current_forma_l()];
	int Number=a->get_number();
	QString Comment = a->get_attribute();
	ui.lEdit_Number->setText(QString::number(Number));
	ui.lEdit_Comment->setText(Comment);
}

void DialogFormsHeader::accept ()
{
	QList<forma_l*> *flist = m_main_form->m_edit_menu->m_font->get_m_forma_l_list();
	forma_l	*a = (*flist)[m_main_form->get_m_current_forma_l()];

	QString Number = ui.lEdit_Number->text();
	QString Comment = ui.lEdit_Comment->text();
	
	a->set_number(Number.toInt ( ));
	a->set_attribute(Comment);

	done ( QDialog::Accepted );
}
