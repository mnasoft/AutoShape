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

#ifndef SHAPE_CD_H
#define SHAPE_CD_H

#include "shapes.h"

///Подформа перемещения пера по ломаной.
/**
Подформа перемещения пера по ломаной.<br />

Специальные коды 00C и 00D (12 и 13) обеспечивают иной механизм для включения сегментов дуг в описание формы. Они аналогичны кодам 8 и 9 в том, что вы можете использовать смещения X-Y. Однако, коды 00C и 00D рисуют дуги за счет применения фактора выпуклости к вектору перемещения. Код 00C рисует один сегмент дуги, а код 00D рисует несколько сегментов дуг (polyarcs) которые заканчиваются смещением (0,0).<br />
За кодом 00C должны следовать три байта, описывающие дугу:<br />
0C,X-перемещение,Y-перемещение,Выпуклость<br />

Все значения смещения по X и Y и выпуклость, которая определяет кривизну дуги, должны нахоиться в диапазоне от -127 до +127. If the line segment specified by the displacement has length D, and the perpendicular distance from the midpoint of that segment has height H, the magnitude of the bulge is ((2* H / D) * 127). The sign is negative if the arc from the current location to the new location is clockwise.

A semicircle has bulge 127 (or -127) and is the greatest arc that can be represented as a single-arc segment using these codes (use two consecutive arc segments for larger arcs). A bulge specification of 0 is valid and represents a straight-line segment. Note, however, that using code 8 for a straight-line segment saves a byte in the shape description.

The polyarc code (00D, or 13) is followed by 0 or by more arc segment triples, and is terminated by a (0,0) displacement. Note that no bulge is specified after the final displacement. For example, the letter S might be defined by the following sequence:

13,(0,5,127),(0,5,-127),(0,0)
Zero bulge segments are useful within polyarcs to represent straight segments; they are more efficient than terminating the polyarc, inserting one straight segment, and then starting another polyarc.

The number -128 cannot be used in arc segment and polyarc definitions.
*/

class shape_cd: public shapes
{

private:
        int m_current;                                      ///<Текущий элемент ломаной.
        /**<0 - первый элемент; 1 - второй элемент; и т.д.*/

public:
        /*******************  К О Н С Т Р У К Т О Р Ы **************************/
        shape_cd ( void );                                  ///<Конструктор.
        /**<Создает форму перемещения пера по ломаной у которой ломаня состоит из одного сегмента.*/
        ~shape_cd();                                        ///<Деструктор.
        /************************* Функции доступа *************************/
        int get_n_segment ( void ) const;                   ///<Возвращает количество сегментов ломаной.

        int insert ( int ref_pos, int dx, int dy , int c ); ///<Добавляет сегмент (dx,dy) перед ref_pos-овым сегментом ломаной.
        int insert ( int ref_pos, QList<int> & Dxy );       ///<Добавляет несколько сегментов (dx,dy) перед ref_pos-овым сегментом ломаной.
        int append ( int dx, int dy , int c );              ///<Добавляет сегмент (dx,dy) перед ref_pos-овым сегментом ломаной.
        int replace ( QList<int> & Dxy );                   ///<Заменяет ломаную на ломаную, содержащуюся в списке Dxy.

        int removeAt ( int ref_pos );                       ///<Удаляет ссылочный сегмент из ломаной.

        bool is_validate() const;                           ///<Выполняет проверку данных ломаных на правильность.
        void Validate();                                    ///<Выполняет проверку данных ломаных на правильность и устраняет ошибки.

        bool is_index_good ( int i ) const;

        int get_x ( int i ) const;                      ///<Возвращает перемещение пера по оси х для i-того элемента ломаной.
        int get_y ( int i ) const;                      ///<Возвращает перемещение пера по оси y для i-того элемента ломаной.
        int get_c ( int i ) const;                      ///<Возвращает кривизну дуги i-того элемента ломаной.
        draw_point get_delta_p ( int i ) const;

        void set_x ( int i, int dx ) ;                  ///<Устанавливает перемещение пера по оси х для i-того элемента ломаной.
        void set_y ( int i, int dy ) ;                  ///<Устанавливает перемещение пера по оси y для i-того элемента ломаной.
        void set_xy_c ( int i, int x, int y, int c );   ///<Устанавливает перемещение пера по осям х и y для i-того элемента ломаной.
        void set_c ( int i, int c );                    ///<Устанавливает кривизну i-того элемента ломаной.

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
// kate: indent-mode cstyle; space-indent on; indent-width 8; 
