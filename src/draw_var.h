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

#ifndef DRAW_VAR_H
#define DRAW_VAR_H

#include <QString>
#include <QColor>

#include <QtGui/QGraphicsView>

#include "draw_point.h"

///Класс, содержащий переменные рисования.
/**Класс, содержащий переменные рисования.*/

class draw_vars
{

public:
    draw_vars ( void );                           ///<Конструктор по умолчанию.
    draw_vars ( const draw_vars & a );            ///<Конструктор копирования.

    draw_vars & operator=( const draw_vars & a ); ///<Оператор копирования.

private:
    ///Координаты текущего положения (относительные).
    draw_point p;
    
    ///Начало относительных координат, выраженноое в абсолютных координатах окна.
    draw_point p0;
    
    ///Начало относительных координат для вертикального шрифта, выраженноое в абсолютных координатах.
    draw_point p0v;
    
    ///Начало относительных координат для горизонтального шрифта, выраженноое в абсолютных координатах.
    draw_point p0h;
    
    ///Состояние пера (pero==true - перо опущено, рисует; pero==false - перо поднято, перемещается.)
    bool pero;
    
    ///Текущий масштабный множитель для подформ.
    /**Масштабный множитель изменяется при пмощи подформ 3 и 4.*/
    qreal masht;
    
    ///Разрежение линий вспомогательной сетки.
    /**При dist = 1 рисуются все линии сетки; dist = 2 - рисуются каждая вторая линия; и т.д.*/
    int dist;
    
    ///Размер маркера. Какого маркера?
    int marker_size;
    
    ///Флаг, управляющий отрисовкой текста.
    /**
     При drawAsVertical=true символ шрифта отрисовывается как вертикальный (производится отрисовка форм следующих за spape_e).
     При drawAsVertical=false символ шрифта отрисовывается как горизонтальный (отрисовка форм следующих за spape_e игнорируется).
     */
    bool drawAsVerticalFlag;
    
    ///Флаг, управляющий отрисовкой текста.
    /**
     При drawWhisOutPenUpMovement=true символ шрифта отрисовывается без показа перемещения поднятого пера.
     При drawWhisOutPenUpMovement=false символ шрифта отрисовывается с показом перемещения поднятого пера.
     */
    bool drawWhisOutPenUpMovementFlag;
    
    ///Количество горизонтальных линий на вспомогательной сетке.???
    int above;

public:
    //Цвет для подформ.
    static QColor s_color_pen_down;     ///<Цвет для форм, отрисовываемых при опущенном пере.
    static QColor s_color_pen_up;       ///<Цвет для форм, отрисовываемых при попднятом пере.
    static QColor s_color_12;           ///<Цвет значков "Опустить перо" и "Поднять перо".
    static QColor s_color_34;           ///<Цвет значка "Изменить масштаб".
    static QColor s_color_56;           ///<Цвет для значков "Протолкнуть в стек" и "Вытолкнуть из стека".
    static QColor s_color_7;            ///<Цвет для вставки подформы.
    static QColor s_color_cur;          ///<Цвет для текущей формы.
    static QColor s_color_9d;           ///
    static QColor s_color_e;            ///<Цвет для значка "Следующая форма отрисовывается только если шрифт имеет вертикальное направление вычерчивания".
    //Толщина линий для подформ.
    static int  s_width_pen_down;       ///<Толщина пера для форм, отрисовываемых при опущенном пере.
    static int  s_width_pen_up;         ///<Толщина пера для форм, отрисовываемых при попднятом пере.
    static int  s_width_12;             ///<Толщина пера значков "Опустить перо" и "Поднять перо".
    static int  s_width_34;             ///<Толщина пера значка "Изменить масштаб".
    static int  s_width_56;             ///<Толщина пера для значков "Протолкнуть в стек" и "Вытолкнуть из стека".
    static int  s_width_7;              ///<Толщина пера для вставки подформы.
    static int  s_width_cur;            ///<Толщина пера для текущей формы.
    static int  s_width_9d;             ///<Толщина пера для текущей подформы форм shape_89  и shape_cd.
    static int  s_width_e;              ///<Толщина пера для значка "Следующая форма отрисовывается только если шрифт имеет вертикальное направление вычерчивания".
    
    static QRect net_hor;               ///<Прямоугольник, определяющий границы вспомогательной сетки для горизонтального шрифта.
    static QRect net_ver;               ///<Прямоугольник, определяющий границы вспомогательной сетки для горизонтального шрифта.

    static bool s_drawHorisontal;       ///<Рисовать текст как горизонтальный.
    static bool s_drawAll;              ///<Рисовать все элементы.
    static bool s_drawNet;              ///<Рисовать вспомогательную сетку.
    
    int cur;
    //Преобразования координат.
    draw_point  otn_to_abs ( draw_point p_otn );        ///<Преобразование координат из относительных в абсолютные.
    draw_point  abs_to_otn ( draw_point p_a );          ///<Преобразование координат из абсолютных в относительные.

    //Работа с пером
    void        pero_down ( void );                     ///<Опустить перо.
    void        pero_up ( void );                       ///<Поднять перо.
    bool        get_pero ( void );                      ///Возвращает состояние пера (true - опущено; false - поднято).
    //Работа с пером

    void        set_coords ( draw_point p_otn_new );    ///<Выполняет перенос пера в относительных координатах.

    void        set_abs_coords ( draw_point p_abs );
    void        set_otn_coords ( draw_point p_otn );    ///<Устанавливает новую абсциссу текущего положения пера в относительных координатах.

    void        set_horver_coords ( draw_point p_abs );

    void        move_coords ( draw_point dp_otn );

    draw_point  get_p_abs ( void );
    draw_point  get_p_otn ( void );                     ///<Возврвщвет положение пера в относительных координатах.

    //Работа с масштабом
    void        multipli_masht ( qreal a );             ///<Выполняет умножение маштабного множителя masht на число a.
    void        devided_masht ( qreal a );              ///<Выполняет деление маштабного множителя masht на число a.

    void        set_masht ( qreal a );                  ///<Устанавливает значение маштабного множителя masht равным числу a.
    qreal       get_masht ( void );                     ///<Возвращает значение маштабного множителя masht.
    //Работа с масштабом

    qreal       get_scale ( void );

    void        set_above ( int  a );                   ///<Задает габариты сетки.
    void        set_dist ( int );                       ///<Задает расстояния между линиями сетки.


    bool        drawAsVertical(void);                   ///<Возвращает true при вертикальной отрисовке символов шрифта.
    bool        drawAsHorisontal(void);                 ///<Возвращает true при горизонтальной отрисовке символов шрифта.
    void        set_drawAsVertical(bool a_vertical);    ///<Возвращает true при вертикальной отрисовке символов шрифта.
    void        set_drawAsHorisontal(bool a_horisontal);///<Возвращает true при горизонтальной отрисовке символов шрифта.

    bool        drawWhisOutPenUpMovement(void);
    void        set_drawWhisOutPenUpMovement(bool flag);
    
    //Печать
    void draw ( QGraphicsScene & sc );                  ///<Отрисовка вспомогательной сетки.

    void draw_marker ( QGraphicsScene & sc );           ///<Отрисовка маркера текущего положения.
//@todo print
    void print ( void );
    //Вывод в файл и считывание из файла.
    void read ( const QString & file_name, const QString &  marker );
    void write ( const QString & file_name, const QString &  marker );

public:
    void        set_initial( void );                   ///<Устанавливает атрибуты draw_vars к значениям по-умолчанию.
};

#endif
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
