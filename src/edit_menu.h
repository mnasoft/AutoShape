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

#ifndef EDIT_MENU_H
#define EDIT_MENU_H


#include "font.h"
#include "menu.h"

///Класс edit_menu.
/**
Класс edit_menu.\n
Содержит меню для всех элементов управления.
*/

class edit_menu
{

public:
    font  *m_font;                                      ///<Экземпляр шрифта.

    menu  *s_menu_color;                                ///<shapes. Меню выбора цветов отображения.

    menu  *s_menu_shape_12_pen;                         ///<shape_12. Меню переключчения положения пера.

    menu  *s_menu_font_main;                            ///<font. Главное меню.
//    menu  *s_menu_font_parametr;                        ///<font. Редактирование параметров шрифта.
    menu  *s_menu_font_forms;                           ///<font. Навигация по формам шрифта.
    menu  *s_menu_font_yes_no;                          ///<font. Подтверждение перезаписи файла.
    menu  *s_menu_font_find_form;                       ///<font. Поиск формы.

    menu  *s_menu_draw_vars_font_main_direction;        ///<draw_vars.
//    menu  *s_menu_draw_vars_edit_main;                  ///<draw_vars.

    menu  *s_menu_forma_l_header;                       ///<forma_l. Редактирование заголовка формы.

    menu  *s_menu_form;                                 ///<forma. Меню редактирование формы.
    menu  *s_menu_form_insert_shapes;                   ///<forma. Меню для вставки новой подформы.
    menu  *s_menu_samy;                                 ///<forma.


    edit_menu ( QWidget * parent = 0 );                 ///<Конструктор.
    ~edit_menu ( void );                                ///<Деструктор.

public:
    void init_menu ( QWidget * parent = 0 );
    void uninit_menu ( void );
};

#endif
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
