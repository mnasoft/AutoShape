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

#ifndef DIALOG_ARC_OCTANT_EDIT_H
#define DIALOG_ARC_OCTANT_EDIT_H

#include "ui_dialog_arc_octant_edit.h"
#include "main_form.h"
#include "shape_a.h"

///Диалог, предназначенный для редактирования подформ shape_a.
class DialogArcOctantEdit : public QDialog
{
    Q_OBJECT

  public:
    DialogArcOctantEdit ( QWidget *parent = 0 );

    void   set_radius ( int theValue );
    int    get_radius ( void );
    void   set_startOctant ( int theValue );
    int    get_startOctant ( void );
    void   set_numberOctant ( int theValue );
    int    get_numberOctant ( void );

    shape_a* get_shape ( void );
    void   set_shape ( shape_a* );

  public slots:
    void    accept ();
    void    acrOctantStartChadged ( int );
    void    acrOctantNumberChadged ( int );
    void    acrOctantRadiusChadged ( int );

  signals:
    void    arcOctantChanged ( void );

  private:
    Ui::DialogArcOctantEdit ui;

    int    m_radius;
    int    m_startOctant;
    int    m_numberOctant;

    shape_a* m_shape;
};

#endif
// kate: indent-mode cstyle; space-indent on; indent-width 2; replace-tabs on; 
