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

#ifndef STACK_H
#define STACK_H

#include "draw_var.h"

///Стек положений пера при отрисовке шрифта.

/**Стек положений пера при отрисовке шрифта.*/

class stack
{
private:
	draw_point *p;																		///<Координаты текущего положения (относительные)
	int size;																					///<Глубина стека
	int count;																				///<Указатель на текущее положение
public:
	stack(int Size);																	///<Конструктор.
	stack(void);																			///<Конструктор.
	~stack(void);																			///<Деструктор.
	void pop(draw_point &);														///<Проталкивание положения пера в стек.
	void push(const draw_point &);										///<Выталкивание положения пера из стека.
	void clear(void);																	///<Очистка всего стека.
	void print(void);																	///<Вывод содержимого стека на печать.
};

#endif
