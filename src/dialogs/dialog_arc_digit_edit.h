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

#ifndef DIALOG_ARC_DIGIT_EDIT_H
#define DIALOG_ARC_DIGIT_EDIT_H

#include "ui_dialog_arc_digit_edit.h"
#include "main_form.h"
#include "shape_b.h"

///Диалог, предназначенный для редактирования подформ shape_b.
class DialogArcDigitEdit : public QDialog
{
    Q_OBJECT

  public:
    DialogArcDigitEdit ( QWidget *parent = 0 );

    void        set_radius ( int theValue );
    int         get_radius ( void );
    void        set_startDigit ( int theValue );
    int         get_startDigit ( void );
    void        set_endDigit ( int theValue );
    int         get_endDigit ( void );

    void        set_dirCounterClockwise ( bool theValue );
    bool        get_dirCounterClockwise ( void );

    shape_b*    get_shape ( void );
    void        set_shape ( shape_b* );

  public slots:
    void        accept ();
    void        arcDigitStartChadged ( int );
    void        arcDigitEndChadged ( int );
    void        arcDigitRadiusChadged ( int );
    void        arcDigitDirectionCounterClockwiseClicked ( bool );
    void        arcDigitDirectionClockwiseClicked ( bool );

  signals:
    void        arcDigitChanged ( void );

  private:
    Ui::DialogArcDigitEdit ui;

    int         m_radius;
    int         m_startDigit;
    int         m_endDigit;
    bool        m_dirCounterClockwise;

    shape_b*    m_shape;
};

#endif
// kate: indent-mode cstyle; space-indent on; indent-width 2; replace-tabs on; 
