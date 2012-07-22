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

#include "strings.h"
#include "stack.h"

///<Создает стек размером в Size элементов.
stack::stack ( int sz )
{
	size = sz;
	p = new draw_point[size];

	if ( p == NULL )
	{
//		printf ( "\nOut of memory" );
		exit ( 1 );
	}
	else
		count = 0;
}

///<Создает пустой стек элементов.
stack::stack ( void ) : p ( 0 )
{
	size = 0;
	count = 0;
}

stack::~stack ( void )
{
	delete []p;
}

void stack::push ( const draw_point & p_new )
{
	if ( count < size )
	{
		p[count] = p_new;
		count++;
	}
}

void stack::pop ( draw_point & p_rez )
{
	if ( count == 0 )
	{
		;
	}
	else
	{
		count--;
		p_rez = p[count];
	}
}

void stack::print ( void )
{
	char str[40];
	int s = 0;
	int x_, y_;
	x_ = 0;
	y_ = 100;

	if ( count == 0 )
	{
		string_to_display ( "Stack is empty " );
		return;
	}

	for ( s; s < count; s++ )
	{
//		sprintf ( str, "%f  %f", p[s].x, p[s].y );
		string_to_display ( str );
		y_ += 10;
	}

	if ( count == size )
	{
		string_to_display ( "Stack is full " );
	}
}

void stack::clear ( void )
{
	count = 0;
}
