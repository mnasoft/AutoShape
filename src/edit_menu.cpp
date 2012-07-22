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

#include "edit_menu.h"
#include "font.h"

edit_menu::edit_menu ( QWidget * parent ) :
		m_font ( 0 ),
		s_menu_color ( 0 ),
		s_menu_shape_12_pen ( 0 ),
		s_menu_font_main ( 0 ),
		s_menu_font_forms ( 0 ),
		s_menu_font_yes_no ( 0 ),
		s_menu_font_find_form ( 0 ),
		s_menu_draw_vars_font_main_direction ( 0 ),
//		s_menu_draw_vars_edit_main ( 0 ),
		s_menu_forma_l_header ( 0 ),
		s_menu_form ( 0 ),
		s_menu_form_insert_shapes ( 0 ),
		s_menu_samy ( 0 )
{
	m_font = new font;
	init_menu ( parent );
}

edit_menu::~edit_menu ( void )
{
	delete m_font;
	uninit_menu();
}

void edit_menu::init_menu ( QWidget *parent )
{
	/**********     shape_12     ************************************************************************************/
	if ( s_menu_shape_12_pen == 0 )
	{
		s_menu_shape_12_pen = new menu;
		{
			s_menu_shape_12_pen->setWindowTitle ( QString ( "PEN" ) );
			s_menu_shape_12_pen->addItem ( "&Up" );
			s_menu_shape_12_pen->addItem ( "&Down" );
			s_menu_shape_12_pen->setParent ( parent );
		}
	}

	/**********     font     ************************************************************************************/

	if ( s_menu_font_main  == 0 )
	{
		s_menu_font_main = new menu;
		{
			s_menu_font_main->setWindowTitle ( QString ( "Font" ) );

			s_menu_font_main->addItem ( "&Open" );

//			s_menu_font_main->addItem ( "&New" );

			s_menu_font_main->addItem ( "&Save" );
			s_menu_font_main->addItem ( "Save &as" );

			s_menu_font_main->addItem ( "Edit &header" );
			s_menu_font_main->addItem ( "Edit &forms" );

			s_menu_font_main->addItem ( "&Draw vars" );

			s_menu_font_main->addItem ( "&Close" );
			s_menu_font_main->addItem ( "E&xit" );
			s_menu_font_main->setParent ( parent );
		}
	}

// 	if ( s_menu_font_parametr  == 0 )
// 	{
// 		s_menu_font_parametr = new menu;
// 		{
// 			s_menu_font_parametr->setWindowTitle ( QString ( "Parametr" ) );
// 			s_menu_font_parametr->addItem ( "&Above" );
// 			s_menu_font_parametr->addItem ( "&Below" );
// 			s_menu_font_parametr->addItem ( "&Modes" );
// 			s_menu_font_parametr->addItem ( "Attrib&ute" );
// 			s_menu_font_parametr->addItem ( "E&xit" );
// 			s_menu_font_parametr->setParent ( parent );
// 		}
// 	}

	if ( s_menu_font_forms == 0 )
	{
		s_menu_font_forms = new menu;
		{
			s_menu_font_forms->setWindowTitle ( QString ( "Forms" ) );
			s_menu_font_forms->addItem ( "&Header..." );
			s_menu_font_forms->addItem ( "Forma &ed..." );
			s_menu_font_forms->addItem ( "&Prev" );
			s_menu_font_forms->addItem ( "&Next" );
			s_menu_font_forms->addItem ( "&Home" );
			s_menu_font_forms->addItem ( "En&d" );
			s_menu_font_forms->addItem ( "&Find..." );
			s_menu_font_forms->addItem ( "Ins pa&st" );
			s_menu_font_forms->addItem ( "&Ins befor" );
			s_menu_font_forms->addItem ( "Delete..." );
			s_menu_font_forms->addItem ( "Backspace..." );
			s_menu_font_forms->addItem ( "E&xit" );
			s_menu_font_forms->setParent ( parent );
		}
	}

	if ( s_menu_font_yes_no == 0 )
	{
		s_menu_font_yes_no = new menu;
		{
			s_menu_font_yes_no->setWindowTitle ( QString ( "Delete ?" ) );
			s_menu_font_yes_no->addItem ( "&No" );
			s_menu_font_yes_no->addItem ( "&Yes" );
			s_menu_font_yes_no->setParent ( parent );
		}
	}

	if ( s_menu_font_find_form == 0 )
	{
		s_menu_font_find_form = new menu;
		{
			s_menu_font_find_form->setWindowTitle ( QString ( "Header" ) );
			s_menu_font_find_form->addItem ( "&Number" );
			s_menu_font_find_form->addItem ( "&ASCII" );
			s_menu_font_find_form->setParent ( parent );
		}
	}

	/**********     Font     ************************************************************************************/

	if ( s_menu_color == 0 )
	{
		s_menu_color = new menu;
		{
			s_menu_color->setWindowTitle ( QString ( "Colors" ) );
			s_menu_color->addItem ( "&Draw" );
			s_menu_color->addItem ( "Move" );
			s_menu_color->addItem ( "&Current" );
			s_menu_color->addItem ( "Pen" );
			s_menu_color->addItem ( "&Stack" );
			s_menu_color->addItem ( "&Reference" );
			s_menu_color->addItem ( "&List curr" );
			s_menu_color->addItem ( "&Verical" );
			s_menu_color->addItem ( "&Size" );
			s_menu_color->setParent ( parent );
		}
	}

	if ( s_menu_draw_vars_font_main_direction == 0 )
	{
		s_menu_draw_vars_font_main_direction = new menu;
		{
			s_menu_draw_vars_font_main_direction->setWindowTitle ( QString ( "Direction" ) );
			s_menu_draw_vars_font_main_direction->addItem ( "&Vertical" );
			s_menu_draw_vars_font_main_direction->addItem ( "&Horisontal" );
			s_menu_draw_vars_font_main_direction->setParent ( parent );
		}
	}

/*	if ( s_menu_draw_vars_edit_main == 0 )
	{
		s_menu_draw_vars_edit_main  = new menu;
		{
			s_menu_draw_vars_edit_main ->setWindowTitle ( QString ( "Draw var" ) );
			s_menu_draw_vars_edit_main ->addItem ( "&Direction..." );
			s_menu_draw_vars_edit_main ->addItem ( "&Scale" );
			s_menu_draw_vars_edit_main ->addItem ( "&Origin" );
			s_menu_draw_vars_edit_main ->addItem ( "&Net" );
			s_menu_draw_vars_edit_main ->addItem ( "&color" );
			s_menu_draw_vars_edit_main ->addItem ( "Net de&vide" );
			s_menu_draw_vars_edit_main ->addItem ( "Marker si&ze" );
			s_menu_draw_vars_edit_main ->addItem ( "Marker co&lor" );
			s_menu_draw_vars_edit_main ->setParent ( parent );
		}
	}
*/

	if ( s_menu_forma_l_header == 0 )
	{
		s_menu_forma_l_header = new menu ();
		{
			s_menu_forma_l_header->setWindowTitle ( QString ( "FORMS HEADER" ) );
			s_menu_forma_l_header->addItem ( "&Number" );
			s_menu_forma_l_header->addItem ( "A&SCII" );
			s_menu_forma_l_header->addItem ( "&Attribute" );
			s_menu_forma_l_header->addItem ( "E&xit" );
		}
	}

	/**********     Forma     ************************************************************************************/

	if ( s_menu_form == 0 )
	{
		s_menu_form = new menu ;
		{
			s_menu_form->setWindowTitle ( QString ( "Forma" ) );
			s_menu_form->addItem ( "&Edit..." ); 		//0
			s_menu_form->addItem ( "&Draw var..." );	//1
			s_menu_form->addItem ( "&Prev" );				//2
			s_menu_form->addItem ( "&Next" );				//3
			s_menu_form->addItem ( "&Home" );				//4
			s_menu_form->addItem ( "En&d" );					//5
			s_menu_form->addItem ( "Ins pa&st" );		//6
			s_menu_form->addItem ( "&Ins befor" );		//7
			s_menu_form->addItem ( "Dele&te" );			//8
			s_menu_form->addItem ( "Backspace" );		//9
			s_menu_form->addItem ( "E&xit" );				//10
		}
	}

	if ( s_menu_form_insert_shapes == 0 )
	{
		s_menu_form_insert_shapes = new menu ();
		{
			s_menu_form_insert_shapes->setWindowTitle ( QString ( "Shapes" ) );
			s_menu_form_insert_shapes->addItem ( "&Line..." ); 			//0
			s_menu_form_insert_shapes->addItem ( "&Pen" );					//1
			s_menu_form_insert_shapes->addItem ( "&Scale" );				//2
			s_menu_form_insert_shapes->addItem ( "Stac&k" );				//3
			s_menu_form_insert_shapes->addItem ( "Reference" );			//4
			s_menu_form_insert_shapes->addItem ( "Line_89" );				//5
			s_menu_form_insert_shapes->addItem ( "Octant_Arc" );		//6
			s_menu_form_insert_shapes->addItem ( "Digit_Arc" );			//7
			s_menu_form_insert_shapes->addItem ( "CurveLine_cd" );	//8
			s_menu_form_insert_shapes->addItem ( "Vertical" );			//9
		}
	}


	if ( s_menu_samy  == 0 )
	{
		s_menu_samy = new menu ();
		{
			s_menu_samy->setWindowTitle ( QString ( "SAVE" ) );
			s_menu_samy->addItem ( "&Yes" );
			s_menu_samy->addItem ( "&No" );
		}
	}




}


void edit_menu::uninit_menu ( void )
{
	delete	 s_menu_font_main;
	s_menu_font_main = 0;

// 	delete	 s_menu_font_parametr;
// 	s_menu_font_parametr = 0;

	delete	 s_menu_font_forms;
	s_menu_font_forms = 0;

	delete	 s_menu_font_yes_no;
	s_menu_font_yes_no = 0;

	delete	 s_menu_font_find_form;
	s_menu_font_find_form = 0;

	delete s_menu_color;
	s_menu_color = 0;

	delete s_menu_draw_vars_font_main_direction;
	s_menu_draw_vars_font_main_direction = 0;

/*	delete s_menu_draw_vars_edit_main;
	s_menu_draw_vars_edit_main	= 0;
*/

	delete	 s_menu_forma_l_header;
	s_menu_forma_l_header = 0;

	delete s_menu_form;
	s_menu_form = 0;

	delete s_menu_form_insert_shapes;
	s_menu_form_insert_shapes = 0;

	delete s_menu_samy;
	s_menu_samy = 0;
}
