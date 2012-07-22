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

#ifndef MAIN_FORM_H
#define MAIN_FORM_H

#include "edit_menu.h"

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QWidget>

///Виджет, представляющий главное окно приложения.
/**
Класс Main_Form.\n
Main_Form - главное окно приложения.
*/

class Main_Form : public QWidget
{
    Q_OBJECT

public:
    draw_vars dr;

    edit_menu *m_edit_menu;                       ///<Содержит элементы редактирования шрифта и экземпляр редактируемого шрифта.

    QHBoxLayout *horizontalLayout;                ///<horizontalLayout
    QGraphicsView *graphicsView;                  ///<Виджет для отрисовки символов шрифта.

public:
    Main_Form ( QWidget * parent = 0 );           ///<Конструктор.
    void connect_setup();                         ///<Настройка сигналов и слотов.

    void reDrawCurrentFormInFoma_l(void);         ///<Перерисовка текущей формы шрифта.

    int get_m_current_forma_l(void);              ///<Возвращает номер текущего символа в шрифте.
    void set_m_current_forma_l(int);              ///<Устанавливает номер текущего символа в шрифте.

    forma_l* get_p_current_forma_l(void) const;   ///<Возвращает указатель на текущий символ шрифта.
    QList<shapes*>* get_p_shapeList(void) const;  ///<Возвращает указатель на список форм, составляющих символ.
    shapes* get_p_current_shape();                ///<Возвращает указатель на текущую форму.

public slots:
    void fontMainOpen();                          ///<font.main Открыть шрифт.
    void fontMainSave();                          ///<font.main Сохранить шрифт.
    void fontMainSaveAs();                        ///<font.main Сохранить шрифт как.

    void fontMainEditHeader();                    ///<font.main Редактирование заголовка шрифта.
    void fontMainEditForms();                     ///<font.main Редактирование форм шрифта.

    void fontMainDrawVars();                      ///<font.main Установка параметров отображения шрифта.

    void fontMainClose();                         ///<font.main Закрыть шрифт с сохранением.
    void fontMainExit();                          ///<font.main Выход из программы.

    void formsHeader();                           ///<forma_l.
    void formsFormaEdit();                        ///<forma_l.
    void formsPrev();                             ///<forma_l.
    void formsNext();                             ///<forma_l.
    void formsHome();                             ///<forma_l.
    void formsEnd();                              ///<forma_l.
    void formsFind();                             ///<forma_l.
    void formsInsertPast();                       ///<forma_l.
    void formsInsertBefor();                      ///<forma_l.
    void formsDelete();                           ///<forma_l.
    void formsBackspace();                        ///<forma_l.
    void formsExit();                             ///<forma_l.

    /**************************************************************************************/

    void formaEdit();                             ///<forma.
    void formaDrawVars();                         ///<forma.
    void formaPrev();                             ///<forma.
    void formaNext();                             ///<forma.
    void formaHome();                             ///<forma.
    void formaEnd();                              ///<forma.
    void formaInsert_Past();                      ///<forma.
    void formaInsert_Before();                    ///<forma.
    void formaDelete();                           ///<forma.
    void formaBackspace();                        ///<forma.
    void formaExit();                             ///<forma.
    /**************************************************************************************/

    void formaInsertLine();         //"&Line..."
    void formaInsertPen();          //"&Pen"
    void formaInsertScale();        //"&Scale"
    void formaInsertStack();        //"Stac&k"
    void formaInsertReference();    //"Reference"
    void formaInsertLine89();       //"Line_89"
    void formaInsertOctantArc();    //"Octant_Arc"
    void formaInsertDigitArc();     //"Digit_Arc"
    void formaInsertCurveLineCD();  //"CurveLine_cd"
    void formaInsertVertical();     //"Vertical"

    /**************************************************************************************/

    void wheelEvent(QWheelEvent *e);

    void reDrawSlot(void);                        ///<Обрабатывает реакцию на событие требующее перерисовки формы.

private:
    ///Номер текущего символа в шрифте.
    /**Текущий символ в настоящий момент времени отображается и редактируется.*/
    int m_current_forma_l;
    ///Номер текущей формы в символе шрифта.
    /**Текущая форма в настоящий момент времени подлежит редактированию.*/
    int m_current_shape;
    ///Номер текущей подформы в сложной форме (shape_89, shape cd).
    /**Текущая подформа в настоящий момент времени подлежит редактированию.*/
    int m_current_sub_shape;

    void check_and_validate_m_current_forma_l(void);
    bool is_m_current_forma_l_valid(void) const;

    void check_and_validate_m_current_shape(void);
    bool is_m_current_shape_valid(void) const;

    void setTitle(void);
    ///Выполняет запуск диалога установок рисования.
    /** */
    void exec_Draw_Vars_Dialog(void);
};

#endif

// kate: indent-mode cstyle; space-indent on; indent-width 0; 
