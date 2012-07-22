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

#ifndef DIALOG_LINE_EDIT_H
#define DIALOG_LINE_EDIT_H

#include "ui_dialog_line_edit.h"

#include "edit_menu.h"
#include "main_form.h"
#include "shape_.h"

///Диалог, предназначенный для редактирования подформ shape_.

class DialogLineEdit : public QDialog
{
  Q_OBJECT

public:
  DialogLineEdit ( QWidget *parent = 0 );
  void        set_radius ( int theValue );
  int         get_radius ( void );
  void        set_sixtant ( int theValue );
  int         get_sixtant ( void );

  shape_*     get_shape ( void );
  void        set_shape ( shape_* );  
public slots:
  void        accept ();
  void        set_ShapeLength ( int );
  void        set_ShapeDirection ( int );
signals:
  void        lineChanged ( void );

private:
    Ui::DialogLineEdit ui;

    int         m_radius;
    int         m_sixtant;
    shape_*     m_shape;
};


#endif
// kate: indent-mode cstyle; space-indent on; indent-width 2; 
