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

#ifndef SHAPE_89_H
#define SHAPE_89_H

#include "shapes.h"

///Подформа перемещения пера по ломаной.
/**
Состоит из списка подформ shape_89.
Каждый элемент может находиться в диапазоне [-128,+127].


Normal vector specification bytes draw only in the 16 predefined directions, and the longest length is 15. These restrictions help make shape definitions efficient but are sometimes limiting. With codes 8 and 9 you can draw nonstandard vectors using X-Y displacements. Code 8 specifies the X-Y displacement given by the next two bytes. Code 8 must be followed by two specification bytes in the format:

8,X-displacement,Y-displacement
The X-Y displacements can range from -128 to +127. A leading + is optional, and you can use parentheses to improve readability. The following example results in a vector that draws (or moves) 10 units to the left and three units up.

8,(-10,3)
Following the two displacement specification bytes, the shape returns to Normal Vector mode.

You can use code 9 to draw a sequence of nonstandard vectors. Code 9 specifies any number of X-Y displacement pairs. The code sequence is terminated by a (0,0) pair. The following example draws three nonstandard vectors and returns to Normal Vector mode.

9,(3,1),(3,2),(2,-3),(0,0)
You must terminate the sequence of X-Y displacement pairs with a (0,0) pair in order for AutoCAD to recognize any Normal Vectors or special codes that follow.
*/

class shape_89: public shapes
{

  private:
    int m_current;                                    ///<Текущий элемент ломаной.
    /**<0 - первый элемент; 1 - второй элемент; и т.д.*/

  public:
    /*******************  К О Н С Т Р У К Т О Р Ы **************************/
    shape_89 ( void );                              ///<Конструктор.
    /**<Создает форму перемещения пера по ломаной у которой ломаня состоит из одного сегмента.*/
    ~shape_89();                                    ///<Деструктор.
    /************************* Функции доступа *************************/
    int get_n_segment ( void ) const;               ///<Возвращает количество сегментов ломаной.

    int insert ( int ref_pos, int dx, int dy );     ///<Добавляет сегмент (dx,dy) перед ref_pos-овым сегментом ломаной.
    int append ( int dx, int dy );                  ///<Добавляет сегмент (dx,dy) в конец ломаной.
    int insert ( int ref_pos, QList<int> & Dxy );   ///<Добавляет несколько сегментов (dx,dy) перед ref_pos-овым сегментом ломаной.
    int replace ( QList<int> & Dxy );               ///<Заменяет ломаную на ломаную, содержащуюся в списке Dxy.

    int removeAt ( int ref_pos );                   ///<Удаляет ссылочный сегмент из ломаной.

    bool is_validate() const;                       ///<Выполняет проверку данных ломаных на правильность.
    void Validate();                                ///<Выполняет проверку данных ломаных на правильность и устраняет ошибки.

    bool is_index_good ( int i ) const;

    int get_x ( int i ) const;                      ///<Возвращает перемещение пера по оси х для i-того элемента ломаной.
    int get_y ( int i ) const;                      ///<Возвращает перемещение пера по оси y для i-того элемента ломаной.
    draw_point get_delta_p ( int i ) const;         ///<Возвращает точку с координатами соответствующими приращению к месту положения пера после отрисовки формы.

    void set_x ( int i, int dx ) ;                  ///<Устанавливает перемещение пера по оси х для i-того элемента ломаной.
    void set_y ( int i, int dy ) ;                  ///<Устанавливает перемещение пера по оси y для i-того элемента ломаной.
    void set_xy ( int i, int dx, int dy );          ///<Устанавливает перемещение пера по осям х и y для i-того элемента ломаной.

    void set_current (int i);                       ///<Устанавливает текущим i-товый сегмент ломаной.
    int get_current (void);                         ///<Возвращает текущий элемент формы.
    
    bool is_multi_form() const;                     ///<Проверяет содержит-ли ломаная более одного сегмента

    QString out_i ( int i );                        ///<Выводит в строку представление i-тового сегмента ломаной.
    void  print_i ( int i );                        ///<Выводит в консоль представление i-тового сегмента ломаной.
    /*********************************** Виртуальные функции класса shapes ***********************************/
    virtual void        draw ( draw_vars & dr, stack &, QGraphicsScene & sc);///<Рисовать форму
    virtual QString     out ( void );               ///<Вывод символьного представления формы в QString.
    virtual QString     out_comment ( void );       ///<Вывод содержимого формы в удобном для восприятия формате QString.
    virtual void        edit ( void );              ///<Редактирование формы.
    virtual int         get_lenth ( void );         ///<Длина подформы.
    virtual shapes*     copy  ( void );             ///<Копирует подформу.
    virtual QString     type ( void ) const;        ///<Возвращает тип подформы.
};

#endif
// kate: indent-mode cstyle; space-indent on; indent-width 2; 

