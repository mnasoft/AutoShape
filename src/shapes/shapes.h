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

#ifndef SHAPES_H
#define SHAPES_H

#include "draw_var.h"
#include "stack.h"
#include "menu.h"

#include <QGraphicsScene>
#include <QTextStream>
#include <QString>

class forma;

///Базовый класс для форм.
/**
  Каждый символ шрифта (за исключением специального символа 0) состоит из форм. \n
  Формы, порожденные от базового класса форм, делятся на обыкновенные и специальные. \n

  Обыкновенная форма имеет длину один байт и выполняет перемещение пера на вектор длиной от 1 до 16
в одном из шестнадцати навравлений (от 0 до 15). Конец вектора выравнивается к вершинам или серединам или четвертям сторон сторонам квадрата, центр которого расположен в точке начала вектора, длина стороны которого равна удвоенной длине вектора.

\image html shapes.jpg "Направление векторов" width=10cm

  Специальные формы начинаются с одного обозначающего байта и бывают следующими:

- 000 Конец определения формы; \n
- 001 Активировать режим рисования (опустить перо); \n
- 002 Деактивировать режим рисования (поднять перо); \n
- 003 Разделить длины векторов на значение следующего байта;  \n
- 004 Умножить длины векторов на значение следующего байта;   \n
- 005 Протолкнуть текущее положение в стек; \n
- 006 Вытолкнуть текущее положение из стека; \n
- 007 Нарисовать форму с номером, определяемую следующим байтом; \n
- 008 X-Y перемещение, определяемое двумя следующими байтами; \n
- 009 Множественное X-Y перемещение, оканчивающееся на (0,0);  \n
- 00A Октантная дуга, определяемая двумя байтами; \n
- 00B Дробная дуга, определяемая пятью байтами; \n
- 00C Дуга, определяемая X-Y перемещением и выпуклостью; \n
- 00D Множественные дуги, специфицируемые выпуклостью, оканчивающиеся на (0,0,0); \n
- 00E Выполнять следующую команду только если шрифт вертикальный. \n
*/

class shapes
{
public:
    QList<int>    get_m_bites ( void ) const;         ///<Возвращает содержимое атрибута m_bites (байты формы).
public:
    static int cicle_range ( int value, int base, int delta );
    ///<Приведение аргумента периодической функции к инлервалу [base,base+delta).
    static double cicle_range ( double value, double base, double delta );
    ///<Приведение аргумента периодической функции к инлервалу [base,base+delta).
    virtual ~shapes ( void );                       ///<Деструктор.

    void    set_parent ( forma* );                  ///<Устанавливает родителя подформы.
    forma*  get_parent ( void ) const;              ///<Возвращает родителя подформы.

    bool    is_current ( void ) const;              ///<Возвращает true если форма является текущей и false
    ///Проверяет соответствие типа формы специфицируемому в переменной a_Type типу.
    bool    is_type_equal ( const QString & a_Type);
    ///Возвращает указатель на предыдущую форму.
    shapes* get_prev(void);
    ///Возвращает указатель на последующую форму.
    shapes* get_next(void);

    virtual void        print ( void );             ///<Печатает подформу в символьном представлении.
    virtual void        draw ( draw_vars & dr,
                               stack & st,
                               QGraphicsScene & scene);
                                                    ///<Выполняет отрисовку формы в сцене scene.

    virtual QString     out ( void );               ///<Вывод символьного представления формы в QString.
    virtual QString     out_comment ( void );       ///<Вывод содержимого формы в удобном для восприятия формате QString.
    virtual void        edit ( void );              ///<Редактирование формы.
    virtual int         get_lenth ( void );         ///<Длина подформы.
    virtual shapes*     copy  ( void );             ///<Копирует подформу.
    virtual QString     type ( void ) const;        ///<Возвращает тип подформы.
    /**<Вероятно, желательно сделать эту функцию чисто виртуальной*/

protected:
    static long   s_shapes_count;                   ///<Содержит количество, созданных форм
    static int    s_size;

    forma*        m_parent;                         ///<Указатель на родителя.
    QList<int>    m_bites;                          ///<Байты формы.

    shapes ( void );                                ///<Защищенный конструктор.
};

extern shapes * create_shapes ( void );             ///<Создает новую подформу и возвращает указатель на нее.

#endif
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
