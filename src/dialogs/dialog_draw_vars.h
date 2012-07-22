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

#ifndef DIALOG_DRAW_VARS_H
#define DIALOG_DRAW_VARS_H

#include "ui_dialog_draw_vars.h"
#include <QColor>
#include <QGraphicsScene>
//#include "edit_menu.h"

///Диалог, предназначенный для назначения цвета и толщины перьев при отображении символов шрифта.
class DialogDrawVars : public QDialog
{
		Q_OBJECT

	public:
		DialogDrawVars ( QWidget *parent = 0 );

		void set_color_pen_down ( QColor );
		QColor get_color_pen_down ( void );

		void set_color_pen_up ( QColor );
		QColor get_color_pen_up ( void );

		void set_color_12 ( QColor );
		QColor get_color_12 ( void );

		void set_color_34 ( QColor );
		QColor get_color_34 ( void );

		void set_color_56 ( QColor );
		QColor get_color_56 ( void );

		void set_color_7 ( QColor );
		QColor get_color_7 ( void );

		void set_color_cur ( QColor );
		QColor get_color_cur ( void );

		void set_color_9d ( QColor );
		QColor get_color_9d ( void );

		void set_color_e ( QColor );
		QColor get_color_e ( void );

		void set_width_pen_down ( int );
		int get_width_pen_down ( void );

		void set_width_pen_up ( int );
		int get_width_pen_up ( void );

		void set_width_12 ( int );
		int get_width_12 ( void );

		void set_width_34 ( int );
		int get_width_34 ( void );

		void set_width_56 ( int );
		int get_width_56 ( void );

		void set_width_7 ( int );
		int get_width_7 ( void );

		void set_width_cur ( int );
		int get_width_cur ( void );

		void set_width_9d ( int );
		int get_width_9d ( void );

		void set_width_e ( int );
		int get_width_e ( void );

	public slots:
		void accept ();

		void pB_Defaults_pressed ( void );
		void pB_Save_pressed ( void );
	
		QColor pB_color_pen_up_pressed ( void );
		QColor pB_color_pen_down_pressed ( void );
		QColor pB_color_12_pressed ( void );
		QColor pB_color_34_pressed ( void );
		QColor pB_color_56_pressed ( void );
		QColor pB_color_7_pressed ( void );
		QColor pB_color_cur_pressed ( void );
		QColor pB_color_9d_pressed ( void );
		QColor pB_color_e_pressed ( void );

		void spB_width_pen_up_changed ( void );
		void spB_width_pen_down_changed ( void );
		void spB_width_12_changed  ( void );
		void spB_width_34_changed  ( void );
		void spB_width_56_changed  ( void );
		void spB_width_7_changed  ( void );
		void spB_width_9d_changed  ( void );
		void spB_width_cur_changed  ( void );
		void spB_width_e_changed  ( void );

private:
		QColor color_pen_down;
		QColor color_pen_up;
		QColor color_12;
		QColor color_34;
		QColor color_56;
		QColor color_7;
		QColor color_cur;
		QColor color_9d;
		QColor color_e;

		QGraphicsScene scene_pen_down;
		QGraphicsScene scene_pen_up;
		QGraphicsScene scene_12;
		QGraphicsScene scene_34;
		QGraphicsScene scene_56;
		QGraphicsScene scene_7;
		QGraphicsScene scene_cur;
		QGraphicsScene scene_9d;
		QGraphicsScene scene_e;

	private:
		void redrawScanes(void);
		void loadDefaults(void);
		void save();

	private:
		Ui::DialogDrawVars ui;
// 		edit_menu *m_edit_menu;
};

#endif // FONT_HEADER_H
