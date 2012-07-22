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

#include "menu.h"

#include <QVBoxLayout>
#include <QPushButton>

#include <QTextStream>

#include "menu.moc" //new

QTextStream out ( stdout );
/**Создает пустое меню.*/
menu::menu ( QWidget *parent ) :
		QDialog ( parent ),
		run_rez ( -1 ),
		run_object ( 0 )
{
	layout = new QVBoxLayout ( this );
	QSpacerItem *verticalSpacer;
	verticalSpacer = new QSpacerItem(40, 0, QSizePolicy::Minimum, QSizePolicy::Expanding);
	layout->addItem(verticalSpacer);
	setWindowTitle ( QString::fromUtf8 ( "Чисто меню" ) );
}

/**Деструктор.*/
menu::~menu ( void )
{
}

inline int color ( int h, int b )
{
	return ( h ^ b ) | 0x80;
}

void menu::show ( )
{
	setVisible ( true );
}

void menu::hide ( )
{
	setVisible ( false );
}

void menu::addItem ( const QString & aItem )
{
	QPushButton *button = new QPushButton ( aItem );
	layout->addWidget ( button );

//	connect ( button, SIGNAL ( pressed() ), this, SLOT ( select() ) );
}

void menu::addItems ( const QStringList & aItems )
{
	for ( int i = 0; i < aItems.size(); ++i )
		addItem ( aItems.at ( i ) );
}

void menu::run()
{
	run_rez = -1;
	exec();
	QPoint pos_pnt = pos ();
	move ( pos_pnt );
}

void menu::select()
{
	QList<QPushButton *> allPButtons = this->findChildren<QPushButton *>();

	for ( int i = 0; i < allPButtons.size(); ++i )
	{
		QString name = allPButtons.at ( i )->text();
		bool down = allPButtons.at ( i )->isDown ();

		if ( down )
		{
			run_rez = i;
			run_object = allPButtons.at ( i );
			out << name << " " << down  << " " << i << " " << endl;
		}
	}

	hide();
}

int menu::get_run_rez ( void )
{
	return 	run_rez;
}

QObject * menu::get_run_object ( void )
{
	return run_object;
}

QPushButton * menu::findByText ( QString str )
{
	QList<QPushButton *> allPButtons = this->findChildren<QPushButton *>();

	for ( int i = 0; i < allPButtons.size(); ++i )
	{
		QString text = allPButtons.at ( i )->text();

		if ( str == text )
		{
			return allPButtons.at ( i );
		}
	}

	return 0;
}
