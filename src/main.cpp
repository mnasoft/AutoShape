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

#include <QApplication>
#include <QTextStream>
#include <QGraphicsPathItem>

#include "main_form.h"

#include "menu.h"
#include "edit_menu.h"
#include "draw_var.h"
#include "forma_l.h"
#include "font.h"

#include "shape_.h"
#include "shape_12.h"
#include "shape_34.h"
#include "shape_56.h"
#include "shape_7.h"
#include "shape_89.h"
#include "shape_a.h"
#include "shape_b.h"
#include "shape_cd.h"
#include "shape_e.h"

#include "strings.h"

#include "dialog_arc_digit_edit.h"
#include "dialog_arc_octant_edit.h"
#include "dialog_draw_vars.h"
#include "dialog_font_header.h"
#include "dialog_forms_find.h"
#include "dialog_line_edit.h"
#include "dialog_multi_line_edit.h"
#include "dialog_pen_edit.h"
#include "dialog_scale_edit.h"
#include "dialog_stack_edit.h"

QTextStream std_out ( stdout );
QTextStream std_in ( stdin );

Main_Form *theMainForm = 0;

extern void menu_create ( void );

int test_shape_ ( void );

int test_1_shape_ ( Main_Form *b );

int test_shape_12 ( void );
int test_shape_34 ( void );
int test_shape_56 ( void );
int test_shape_7 ( void );
int test_shape_89 ( void );
int test_shape_a ( void );
int test_shape_b ( void );
int test_shape_cd ( void );
int test_shape_e ( void );

int test_font ( void );

int test_forma ( void );

int main ( int argc, char *argv[] )
{
//  Q_INIT_RESOURCE ( application );
    QApplication app ( argc, argv );

    Main_Form *a = new Main_Form;
    theMainForm = a;
    a->show();

    app.exec();
    return 0;
}

int test_1_shape_ ( Main_Form *b )
{

    QTextStream std_out ( stdout );
    QTextStream std_in ( stdin );

    QTransform transform
    ( 1, 0, 0,
      0, -1, 0,
      0, 0, 1
    );
    transform.scale ( 0.5, 0.5 );


    QGraphicsView* grView = b->graphicsView;
    grView->setAlignment ( 0 ); //Qt::AlignLeft | Qt::AlignTop

    grView->setTransform ( transform );


    QGraphicsScene *grScene = new QGraphicsScene;
    grView->setScene ( grScene );
    grView->setTransform ( transform );

    grView->setRenderHints ( QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform  | QPainter::HighQualityAntialiasing );


    int i = 1000;

    forma_l * a = new forma_l;
    forma *form = a->get_m_forma();
    QList<shapes*>* sh_list = form->get_m_shapes();

    sh_list->clear();

    shape_e* she_0 =  new shape_e();
    sh_list->append ( she_0 );

    shape_7* sh7_0 =  new shape_7 ( 450 );
    sh_list->append ( sh7_0 );

    shape_56* sh56_0 =  new shape_56 ( true );
    sh_list->append ( sh56_0 );

    shape_b* shb_0 =  new shape_b ( 220, -30, -120, -1 );
    sh_list->append ( shb_0 );

    shape_* sh_0 =  new shape_;
    sh_0->set_length ( 14 );
    sh_0->set_sixtant ( 0 );
    sh_list->append ( sh_0 );

    shape_34* sh34_0 =  new shape_34;
    sh34_0->set_scale_up  ( true );
    sh34_0->set_scale_factor ( 4 );
    sh_list->append ( sh34_0 );

    shape_12* sh12_0 =  new shape_12 ( false );
    sh_list->append ( sh12_0 );

    shape_* sh_1 =  new shape_;
    sh_1->set_length ( 14 );
    sh_1->set_sixtant ( 4 );
    sh_list->append ( sh_1 );

    shape_12* sh12_1 =  new shape_12 ( true );
    sh_list->append ( sh12_1 );

    shape_89* sh89_0 =  new shape_89;
    sh89_0->set_xy ( 0, 20, 20 );
    sh89_0->append ( -20, 20 );
    sh89_0->append ( -20, -20 );
    sh89_0->append ( 20, -20 );
    sh_list->append ( sh89_0 );

    shape_56* sh56_1 =  new shape_56 ( false );
    sh_list->append ( sh56_1 );

    shape_a* sha_0 =  new shape_a;
    sha_0->set_radius ( 120 );
    sha_0->set_start ( 0 );
    sha_0->set_number ( -1 );
    sh_list->append ( sha_0 );

    shape_cd* shcd_0 =  new shape_cd;
    shcd_0->set_xy_c ( 0, 20, 20, 127 );
    shcd_0->append ( -20, 20, 127 );
    shcd_0->append ( -20, -20, 127 );
    shcd_0->append ( 20, -20, 127 );
    sh_list->append ( shcd_0 );

    draw_vars dr;
    stack st;
    a->draw ( dr, st, *grScene );

    {
        draw_point p_center ( 0.0, 0.0 );
        draw_point p_radius ( 3.5, 3.5 );
        grScene->addEllipse ( p_center.x - p_radius.x / 2., p_center.y - p_radius.y / 2., p_radius.x, p_radius.y, QPen ( Qt::red ) );
    }

    std_out << a->out() << endl;
    forma_l *bb = new forma_l;
    *bb = *a;

    std_out << endl;
    std_out << endl;
    std_out << bb->out() << endl;
    delete bb;

}

int test_shape_ ( void )
{

    QTextStream std_out ( stdout );
    QTextStream std_in ( stdin );

    std_out << "**** Test condition start *****************************************************************" << endl;
    std_out
    << "shape_* sh_0 =  new shape_;" << endl
    << "std_out << sh_0->out_comment() << endl;" << endl
    << "sh_0->print();" << endl << endl;
    std_out << "*******************************************************************************************" << endl;
    shape_* sh_0 =  new shape_;
    draw_vars dr;
    stack st;
    sh_0->edit();
    std_out << sh_0->out_comment() << endl;
    sh_0->print();
    std_out << "**** Test condition end *******************************************************************" << endl;

    std_out << "**** Test condition start *****************************************************************" << endl;
    std_out
    << "for ( int ir = 0;ir < 16 ;ir++ )" << endl
    << "{" << endl
    << "  for ( int io = 0;ir < 16;io++ )" << endl
    << "  {" << endl
    << "    shape_* sh_1 = new shape_ ( ir*16 + io );" << endl
    << "    std_out << sh_1->out_comment() << endl;" << endl
    << "    sh_1->print();" << endl
    << "    delete sh_1;" << endl
    << "  }" << endl
    << "}" << endl << endl;
    std_out << "*******************************************************************************************" << endl;

    for ( int ir = 0; ir < 16 ;ir++ )
    {
        for ( int io = 0; io < 16;io++ )
        {
            shape_* sh_1 = new shape_ ( ir*16 + io );
            std_out << sh_1->out_comment() << endl;
            sh_1->print();
            delete sh_1;
        }
    }

    std_out << "**** Test condition end *******************************************************************" << endl;

    std_out << "**** Test condition start *****************************************************************" << endl;
    std_out
    << "for ( int ir = 0;ir < 16 ;ir++ )" << endl
    << "{  for ( int io = 0; io < 16;io++ )" << endl
    << "  {" << endl
    << "    shape_*sh_2 = new shape_ ( ir, io );" << endl
    << "    std_out << sh_2->out_comment() << endl;" << endl
    << "    sh_2->print();" << endl
    << "    delete sh_2;" << endl
    << "  }" << endl
    << "}" << endl << endl;
    std_out << "*******************************************************************************************" << endl;

    for ( int ir = 0; ir < 16 ; ir++ )
    {
        for ( int io = 0; io < 16; io++ )
        {
            shape_*sh_2 = new shape_ ( ir, io );
            std_out << sh_2->out_comment() << endl;
            sh_2->print();
            delete sh_2;
        }
    }

    std_out << "**** Test condition end *******************************************************************" << endl;

    std_out << "**** Test condition start *****************************************************************" << endl;

    std_out
    << "for ( int ir = 0;ir < 16;ir++ )" << endl
    << "{"
    << "  sh_0->set_radius ( ir );"
    << "  for ( int io = 0;io < 16;io++ )" << endl
    << "  {" << endl
    << "    std_out << \"ir=\" << ir << \" io=\" << io << endl;" << endl
    << "    sh_0->set_sixtant ( io );" << endl
    << "    std_out << \"radius=\" << sh_0->get_radius() << \" octant=\" << sh_0->get_octant()" << endl
    << "    << \"byte=\" << sh_0->get_byte() << endl;" << endl
    << "    sh_0->print();" << endl
    << "  }" << endl
    << "}" << endl << endl;

    std_out << "*******************************************************************************************" << endl;

    for ( int ir = -20;ir < 20;ir++ )
    {
        sh_0->set_length ( ir );

        for ( int io = -20;io < 20;io++ )
        {
            std_out << "ir=" << ir << " io=" << io << endl;
            sh_0->set_sixtant ( io );
            std_out << "radius=" << sh_0->get_length() << " octant=" << sh_0->get_sixtant()
            << "byte=" << sh_0->get_byte() << endl;
            sh_0->print();
        }
    }

    std_out << "**** Test condition end *******************************************************************" << endl;

    std_out << "**** Test condition start *****************************************************************" << endl;

    std_out
    << "for ( int ir = 0;ir < 16;ir++ )" << endl
    << "{"
    << "  sh_0->set_radius ( ir );"
    << "  for ( int io = 0;io < 16;io++ )" << endl
    << "  {" << endl
    << "    std_out << \"ir=\" << ir << \" io=\" << io << endl;" << endl
    << "    sh_0->set_sixtant ( io );" << endl
    << "    std_out << \"radius=\" << sh_0->get_radius() << \" octant=\" << sh_0->get_octant()" << endl
    << "    << \" byte=\" << sh_0->get_byte() << endl;" << endl
    << "    sh_0->print();" << endl
    << "  }" << endl
    << "}" << endl << endl;

    std_out << "*******************************************************************************************" << endl;

    for ( int ibyte = -20; ibyte < 300 ; ibyte++ )
    {
        sh_0->set_byte ( ibyte );
        std_out << "ibyte=" << ibyte << endl;
        std_out << "radius=" << sh_0->get_length() << " octant=" << sh_0->get_sixtant()
        << " byte=" << sh_0->get_byte() << endl;
        sh_0->print();
    }

    std_out << "**** Test condition end *******************************************************************" << endl;

    {
        draw_vars dv;
        stack st;
        sh_0->edit ( );
    }

    delete sh_0;
    return 0;
}

int test_shape_12 ( void )
{
    QTextStream std_out ( stdout );
    QTextStream std_in ( stdin );

    std_out << "shape_12 test" << endl;
    std_out << "************************************************************" << endl;
    std_out << "shape_12* sh_12_0 =  new shape_12;" << endl;
    shape_12* sh_12_0 =  new shape_12;
    std_out << "sh_12_0->print();" << endl;
    sh_12_0->print();

    std_out << "shape_12* sh_12_1 =  new shape_12 ( 1 );" << endl;
    shape_12* sh_12_1 =  new shape_12 ( 1 );
    std_out << "sh_12_1->print();" << endl;
    sh_12_1->print();

    std_out << "shape_12* sh_12_2 =  new shape_12 ( 0 );" << endl;
    shape_12* sh_12_2 =  new shape_12 ( 0 );
    std_out << "sh_12_2->print();" << endl;
    sh_12_2->print();

    std_out << "************************************************************" << endl;

    std_out << "sh_12_0->set_pen_down();" << endl;
    sh_12_0->set_pen_down ( );
    std_out << "sh_12_0->print();" << endl;
    sh_12_0->print();

    std_out << "sh_12_0->set_pen_down ( true );" << endl;
    sh_12_0->set_pen_down ( true );
    std_out << "sh_12_0->print();" << endl;
    sh_12_0->print();

    std_out << "sh_12_0->set_pen_down ( false );" << endl;
    sh_12_0->set_pen_down ( false );
    std_out << "sh_12_0->print();" << endl;
    sh_12_0->print();

    std_out << "************************************************************" << endl;

    std_out << "sh_12_0->set_pen_up();" << endl;
    sh_12_0->set_pen_up ( );
    std_out << "sh_12_0->print();" << endl;
    sh_12_0->print();
    std_out << "sh_12_0->is_pen_down()=" << sh_12_0->is_pen_down() << endl;
    std_out << "sh_12_0->is_pen_up()  =" << sh_12_0->is_pen_up() << endl;

    std_out << "sh_12_0->set_pen_up( true );" << endl;
    sh_12_0->set_pen_up ( true );
    std_out << "sh_12_0->print();" << endl;
    sh_12_0->print();
    std_out << "sh_12_0->is_pen_down()=" << sh_12_0->is_pen_down() << endl;
    std_out << "sh_12_0->is_pen_up()  =" << sh_12_0->is_pen_up() << endl;

    std_out << "sh_12_0->set_pen_up( false );" << endl;
    sh_12_0->set_pen_up ( false );
    std_out << "sh_12_0->print();" << endl;
    sh_12_0->print();
    std_out << "sh_12_0->is_pen_down()=" << sh_12_0->is_pen_down() << endl;
    std_out << "sh_12_0->is_pen_up()  =" << sh_12_0->is_pen_up() << endl;

    std_out << "************************************************************" << endl;

    std_out << "sh_12_0->get_lenth()=" << sh_12_0->get_lenth() << endl;

    std_out << "************************************************************" << endl;

    sh_12_0->set_pen_down();
    shape_12* sh_12_3 = dynamic_cast <shape_12 *> ( sh_12_0->copy() );

    if ( sh_12_3 )
    {
        std_out << "sh_12_0->set_pen_down();" << "\n" <<
        "shape_12* sh_12_3 = dynamic_cast <shape_12 *> ( sh_12_0->copy() );" << "\n" <<
        "sh_12_3->print();" << endl;
        sh_12_3->print();
    }

    sh_12_1->set_pen_up();

    shape_12* sh_12_4 = dynamic_cast <shape_12 *> ( sh_12_1->copy() );

    if ( sh_12_4 )
    {
        std_out << "sh_12_1->set_pen_up();" << "\n" <<
        "shape_12* sh_12_4 = dynamic_cast <shape_12 *> ( sh_12_1->copy() );" << "\n" <<
        "sh_12_4->print();" << endl;
        sh_12_4->print();
    }

    {
        draw_vars dw;
        stack st;
        sh_12_0->edit ( );
    }

    /*    draw_vars   draw ( draw_vars & dr,
                                   stack &,
                                   int color,
                                   int color_,
                                   int priznak );
        QString     out ( void );
        void        out_file  ( FILE* );
        void        edit ( draw_vars &,
                                stack &,
                                int ,
                                int );
        void        clear ( void );
    */
    delete sh_12_0;

    delete sh_12_1;

    delete sh_12_2;

    delete sh_12_3;

    delete sh_12_4;

    return 0;
}

int test_shape_34 ( void )
{
    QTextStream std_out ( stdout );
    QTextStream std_in ( stdin );

    std_out << "**** shape_34 test ********************************************************" << endl;
    std_out << "shape_34* sh_34_0 =  new shape_34;" << endl;
    shape_34* sh_34_0 =  new shape_34;
    std_out << "sh_34_0->print();" << endl;
    sh_34_0->print();
    std_out << "sh_34_0->get_lenth()=" << sh_34_0->get_lenth() << endl;

    sh_34_0->set_scale_up ( true );
    std_out << "sh_34_0->set_scale_up ( true );" << endl;
    std_out << "sh_34_0->out_comment()\n" << sh_34_0->out_comment () << endl;

    sh_34_0->set_scale_factor ( 5 );
    std_out << "set_scale_factor ( 5 );" << endl;
    std_out << "sh_34_0->out_comment()\n" << sh_34_0->out_comment () << endl;

    sh_34_0->set ( false , 250 );
    std_out << "sh_34_0->set( false , 250 );" << endl;
    std_out << "sh_34_0->out_comment()\n" << sh_34_0->out_comment () << endl;

    shapes* sh_34_cp = sh_34_0->copy  ( );
    std_out << "sh_34_cp->out_comment()\n" << sh_34_cp->out_comment () << endl;
    delete sh_34_cp;
    {
        {
            shape_34* sh_34_1 =  new shape_34 ( true, -384 );
            std_out << "shape_34* sh_34_1 =  new shape_34 ( true, -384 );" << endl;
            std_out << "sh_34_1->print();" << endl;
            sh_34_1->print();
            std_out << "sh_34_1->get_scale_up()=" << sh_34_1->get_scale_up() << endl;
            std_out << "sh_34_1->get_scale_factor()=" << sh_34_1->get_scale_factor() << endl;
            std_out << "sh_34_1->get_scale()=" << sh_34_1->get_scale() << endl;
            std_out << "sh_34_1->out()=" << sh_34_1->out() << endl;
            std_out << "sh_34_1->out_comment()\n" << sh_34_1->out_comment () << endl;
            delete sh_34_1;
        }

        {
            shape_34* sh_34_1 =  new shape_34 ( false, -256 );
            std_out << "shape_34* sh_34_1 =  new shape_34 ( false, -256 );" << endl;
            std_out << "sh_34_1->print();" << endl;
            sh_34_1->print();
            std_out << "sh_34_1->get_scale_up()=" << sh_34_1->get_scale_up() << endl;
            std_out << "sh_34_1->get_scale_factor()=" << sh_34_1->get_scale_factor() << endl;
            std_out << "sh_34_1->get_scale()=" << sh_34_1->get_scale() << endl;
            std_out << "sh_34_1->out()=" << sh_34_1->out() << endl;
            std_out << "sh_34_1->out_comment()\n" << sh_34_1->out_comment () << endl;
            delete sh_34_1;
        }

        {
            shape_34* sh_34_1 =  new shape_34 ( true, -128 );
            std_out << "shape_34* sh_34_1 =  new shape_34 ( true, -128 );" << endl;
            std_out << "sh_34_1->print();" << endl;
            sh_34_1->print();
            std_out << "sh_34_1->get_scale_up()=" << sh_34_1->get_scale_up() << endl;
            std_out << "sh_34_1->get_scale_factor()=" << sh_34_1->get_scale_factor() << endl;
            std_out << "sh_34_1->get_scale()=" << sh_34_1->get_scale() << endl;
            std_out << "sh_34_1->out()=" << sh_34_1->out() << endl;
            std_out << "sh_34_1->out_comment()\n" << sh_34_1->out_comment () << endl;
            delete sh_34_1;
        }

        {
            shape_34* sh_34_1 =  new shape_34 ( false, -1 );
            std_out << "shape_34* sh_34_1 =  new shape_34 ( false, -1 );" << endl;
            std_out << "sh_34_1->print();" << endl;
            sh_34_1->print();
            std_out << "sh_34_1->get_scale_up()=" << sh_34_1->get_scale_up() << endl;
            std_out << "sh_34_1->get_scale_factor()=" << sh_34_1->get_scale_factor() << endl;
            std_out << "sh_34_1->get_scale()=" << sh_34_1->get_scale() << endl;
            std_out << "sh_34_1->out()=" << sh_34_1->out() << endl;
            std_out << "sh_34_1->out_comment()\n" << sh_34_1->out_comment () << endl;
            delete sh_34_1;
        }

        {
            shape_34* sh_34_1 =  new shape_34 ( true, 0 );
            std_out << "shape_34* sh_34_1 =  new shape_34 ( true, 0 );" << endl;
            std_out << "sh_34_1->print();" << endl;
            sh_34_1->print();
            std_out << "sh_34_1->get_scale_up()=" << sh_34_1->get_scale_up() << endl;
            std_out << "sh_34_1->get_scale_factor()=" << sh_34_1->get_scale_factor() << endl;
            std_out << "sh_34_1->get_scale()=" << sh_34_1->get_scale() << endl;
            std_out << "sh_34_1->out()=" << sh_34_1->out() << endl;
            std_out << "sh_34_1->out_comment()\n" << sh_34_1->out_comment () << endl;
            delete sh_34_1;
        }

        {
            shape_34* sh_34_1 =  new shape_34 ( false, 1 );
            std_out << "shape_34* sh_34_1 =  new shape_34 ( false, 1 );" << endl;
            std_out << "sh_34_1->print();" << endl;
            sh_34_1->print();
            std_out << "sh_34_1->get_scale_up()=" << sh_34_1->get_scale_up() << endl;
            std_out << "sh_34_1->get_scale_factor()=" << sh_34_1->get_scale_factor() << endl;
            std_out << "sh_34_1->get_scale()=" << sh_34_1->get_scale() << endl;
            std_out << "sh_34_1->out()=" << sh_34_1->out() << endl;
            std_out << "sh_34_1->out_comment()\n" << sh_34_1->out_comment () << endl;
            delete sh_34_1;
        }

        {
            shape_34* sh_34_1 =  new shape_34 ( true, 128 );
            std_out << "shape_34* sh_34_1 =  new shape_34 ( true, 128 );" << endl;
            std_out << "sh_34_1->print();" << endl;
            sh_34_1->print();
            std_out << "sh_34_1->get_scale_up()=" << sh_34_1->get_scale_up() << endl;
            std_out << "sh_34_1->get_scale_factor()=" << sh_34_1->get_scale_factor() << endl;
            std_out << "sh_34_1->get_scale()=" << sh_34_1->get_scale() << endl;
            std_out << "sh_34_1->out()=" << sh_34_1->out() << endl;
            std_out << "sh_34_1->out_comment()\n" << sh_34_1->out_comment () << endl;
            delete sh_34_1;
        }

        {
            shape_34* sh_34_1 =  new shape_34 ( false, 256 );
            std_out << "shape_34* sh_34_1 =  new shape_34 ( false, 256 );" << endl;
            std_out << "sh_34_1->print();" << endl;
            sh_34_1->print();
            std_out << "sh_34_1->get_scale_up()=" << sh_34_1->get_scale_up() << endl;
            std_out << "sh_34_1->get_scale_factor()=" << sh_34_1->get_scale_factor() << endl;
            std_out << "sh_34_1->get_scale()=" << sh_34_1->get_scale() << endl;
            std_out << "sh_34_1->out()=" << sh_34_1->out() << endl;
            std_out << "sh_34_1->out_comment()\n" << sh_34_1->out_comment () << endl;
            delete sh_34_1;
        }

        {
            shape_34* sh_34_1 =  new shape_34 ( true, 384 );
            std_out << "shape_34* sh_34_1 =  new shape_34 ( true, 384 );" << endl;
            std_out << "sh_34_1->print();" << endl;
            sh_34_1->print();
            std_out << "sh_34_1->get_scale_up()=" << sh_34_1->get_scale_up() << endl;
            std_out << "sh_34_1->get_scale_factor()=" << sh_34_1->get_scale_factor() << endl;
            std_out << "sh_34_1->get_scale()=" << sh_34_1->get_scale() << endl;
            std_out << "sh_34_1->out()=" << sh_34_1->out() << endl;
            std_out << "sh_34_1->out_comment()\n" << sh_34_1->out_comment () << endl;
            delete sh_34_1;
        }
    }

    /*
      virtual draw_vars   draw ( draw_vars & dr,
                                stack &,
                                int color,
                                int color_,
                                int priznak );        ///<Рисовать форму
    */
    {
        draw_vars dw;
        stack st;
        sh_34_0->edit ( );
    }

    delete sh_34_0;
    return 0;
}

int test_shape_56 ( void )
{
    QTextStream std_out ( stdout );
    QTextStream std_in ( stdin );

    std_out << "**** shape_56 test ********************************************************" << endl;
    std_out << "shape_56* sh_56_0 =  new shape_56;" << endl;
    shape_56* sh_56_0 =  new shape_56;
    std_out << "sh_56_0->print();" << endl;
    sh_56_0->print();
    std_out << "sh_56_0->get_lenth()=" << sh_56_0->get_lenth() << endl;
    std_out << sh_56_0->out_comment() << endl;

    sh_56_0->set_push ( true );
    std_out << "sh_56_0->set_push(true);" << "\n" << "sh_56_0->get_push()" << sh_56_0->get_push() << endl;
    std_out << sh_56_0->out_comment() << endl;

    sh_56_0->set_push ( false );
    std_out << "sh_56_0->set_push(false);" << "\n" << "sh_56_0->get_push()" << sh_56_0->get_push() << endl;
    std_out << sh_56_0->out_comment() << endl;

    {
        shape_56* sh_56_1 =  new shape_56 ( true );
        std_out << sh_56_1->out_comment() << endl;
        delete sh_56_1;
    }

    {
        shape_56* sh_56_1 =  new shape_56 ( false );
        std_out << sh_56_1->out_comment() << endl;
        delete sh_56_1;
    }

    /*  draw_vars   draw ( draw_vars & dr,
                                stack &,
                                int color,
                                int color_,
                                int priznak );  ///<Рисовать форму
    */
    {
        draw_vars dw;
        stack st;
        sh_56_0->edit ( );
    }

    {
        shapes* sh_0 = sh_56_0->copy();
        sh_0->out_comment();
        delete sh_0;
    }

    delete sh_56_0;

    return 0;
}

int test_shape_7 ( void )
{
    QTextStream std_out ( stdout );
    QTextStream std_in ( stdin );

    std_out << "**** shape_7 test ********************************************************" << endl;
    std_out << "shape_7* sh_7_0 =  new shape_7;" << endl;
    shape_7* sh_7_0 =  new shape_7;
    std_out << "sh_7_0->print();" << endl;
    sh_7_0->print();
    std_out << "sh_7_0->get_lenth()=" << sh_7_0->get_lenth() << endl;
    std_out << sh_7_0->out_comment() << endl;

    sh_7_0->set_ref_number ( 300 );
    std_out << "sh_7_0->set_ref_number ( 300 );" << endl;
    std_out << "sh_7_0->get_ref_number ( )=" <<  sh_7_0->get_ref_number ( ) << endl;

    {
        shape_7* sh_7_1 = new shape_7 ( 150 );
        std_out << "shape_7* sh_7_1 = new shape_7 ( 150 );" << endl;
        std_out << "sh_7_1->out_comment()" << sh_7_1->out_comment() << endl;
        delete sh_7_1 ;
    }

    {
        shape_7* sh_7_1 = new shape_7 ( -150 );
        std_out << "shape_7* sh_7_1 = new shape_7 ( -150 );" << endl;
        std_out << "sh_7_1->out_comment()" << sh_7_1->out_comment() << endl;
        delete sh_7_1 ;
    }

    shapes* sh_cp = sh_7_0->copy( );
    std_out << "sh_cp ->out_comment()" << sh_cp ->out_comment() << endl;

    /*
    virtual draw_vars   draw ( draw_vars & dr,
                              stack &,
                              int color,
                              int color_,
                              int priznak );  ///<Рисовать форму
    */
    {
        draw_vars dw;
        stack st;
        sh_7_0->edit ( );
    }

    delete sh_7_0;
    return 0;
}

int test_shape_89 ( void )
{
    QTextStream std_out ( stdout );
    QTextStream std_in ( stdin );

    std_out << "**** shape_89 test ********************************************************" << endl;
    std_out << "shape_89* sh_89_0 =  new shape_89;" << endl;
    shape_89* sh_89_0 =  new shape_89;
    std_out << "sh_89_0->get_lenth()=" << sh_89_0->get_lenth() << endl;
    std_out << "sh_89_0->print();" << endl;
    sh_89_0->print();
    std_out << "sh_89_0->out_comment()" << endl << sh_89_0->out_comment() << endl;

    {
        sh_89_0->set_x ( 0, 50 ) ;
        sh_89_0->set_y ( 0, 60 ) ;
        std_out << "sh_89_0->set_x(0, 50) ;" << endl;
        std_out << "sh_89_0->set_y(0, 60) ;" << endl;
        std_out << "sh_89_0->out_comment()" << endl << sh_89_0->out_comment() << endl;
    }

    {
        sh_89_0->set_xy ( 0, 125, -127 ) ;
        std_out << "sh_89_0->set_xy(0, 125,-127) ;" << endl;
        std_out << "sh_89_0->out_comment()" << endl << sh_89_0->out_comment() << endl;
    }

    {
        sh_89_0->insert ( 1, 10, 10 ) ;
        std_out << "sh_89_0->out_comment()" << endl << sh_89_0->out_comment() << endl;
        std_out << "sh_89_0->is_index_good(-10)=" << sh_89_0->is_index_good ( -10 )  << endl;
        std_out << "sh_89_0->is_index_good(-1)=" << sh_89_0->is_index_good ( -1 )  << endl;
        std_out << "sh_89_0->is_index_good(0)=" << sh_89_0->is_index_good ( 0 )  << endl;
        std_out << "sh_89_0->is_index_good(1)=" << sh_89_0->is_index_good ( 1 )  << endl;
        std_out << "sh_89_0->is_index_good(2)=" << sh_89_0->is_index_good ( 2 )  << endl;
        std_out << "sh_89_0->is_index_good(3)=" << sh_89_0->is_index_good ( 3 )  << endl;
        std_out << "sh_89_0->is_index_good(4)=" << sh_89_0->is_index_good ( 4 )  << endl;

        std_out << "sh_89_0->out_i(-1)" << endl << sh_89_0->out_i ( -1 ) << endl;
        std_out << "sh_89_0->print_i ( 0 );" << endl;
        sh_89_0->print_i ( 0 );
        std_out << endl;
        std_out << "sh_89_0->out_i(1)" << endl << sh_89_0->out_i ( 1 ) << endl;
    }

    {
        QList<int> Dxy;
        Dxy << 101 << 102 << 103 << 104 << 105 << 106;
        sh_89_0->insert ( sh_89_0->get_n_segment() - 1, Dxy );
        sh_89_0->insert ( 1, Dxy );
        sh_89_0->print ( );
    }

    {
        sh_89_0->removeAt ( sh_89_0->get_n_segment() - 1 );
        sh_89_0->print ( );
        sh_89_0->removeAt ( sh_89_0->get_n_segment() );
        sh_89_0->print ( );
        sh_89_0->removeAt ( 0 );
        sh_89_0->print ( );
    }

    {
        draw_vars dw;
        stack st;
        sh_89_0->edit ( );
    }
    {
        QList<int> Dxy;
        Dxy << 11 << 12 << 21<< 22 << 31 << 32 << 41 << 42;
        sh_89_0->replace(Dxy);
        sh_89_0->edit ( );
    }
    shapes * sh_cp = sh_89_0->copy();
    std_out << sh_cp->out_comment() << endl;

    {
        DialogMultiLineEdit *a = new DialogMultiLineEdit;
        a->show();
        a->set_shape ( sh_89_0 );
    }
    return 0;
}

int test_shape_a ( void )
{
    QTextStream std_out ( stdout );
    QTextStream std_in ( stdin );

    std_out << "**** shape_a test ********************************************************" << endl;
    std_out << "shape_a* sh_a_0 =  new shape_a;" << endl;

    shape_a* sh_a_0 =  new shape_a;
    std_out << "sh_a_0->get_lenth()=" << sh_a_0->get_lenth() << endl;
    std_out << "sh_a_0->print();" << endl;
    sh_a_0->print();
    std_out << "sh_a_0->out_comment()" << endl << sh_a_0->out_comment() << endl;

    {
        shape_a* sh_a_1 =  new shape_a ( 200, 0, 6 );
        std_out
        << "shape_a* sh_a_1 =  new shape_a (200,0,6);"  << endl
        << "sh_a_1->out_comment()"  << endl
        << sh_a_1->out_comment() << endl;
        delete sh_a_1;
    }

    {
        int i = ( 4 << 4 ) + 5;
        i = -1 * ( ( 3 << 4 ) + 5 );
        shape_a* sh_a_1 =  new shape_a ( 200, i );
        std_out
        << "shape_a* sh_a_1 =  new shape_a (200,4<<4+5);"   << endl
        << "sh_a_1->out_comment()"  << endl
        << sh_a_1->out_comment() << endl;
        delete sh_a_1;
    }

    {
        draw_vars dw;
        stack st;
        sh_a_0->edit ( );
    }

    /*    virtual draw_vars   draw ( draw_vars & dr,
                                  stack &,
                                  int color,
                                  int color_,
                                  int priznak );        ///<Рисовать форму

        virtual shapes*     copy  ( void );             ///<Копирует подформу.
    */

    return 0;
}

int test_shape_b ( void )
{
    QTextStream std_out ( stdout );
    QTextStream std_in ( stdin );

    std_out << "**** shape_b test ********************************************************" << endl;
    std_out << "shape_b* sh_b_0 =  new shape_b;" << endl;

    shape_b* sh_b_0 =  new shape_b;
    std_out << "sh_b_0->get_lenth()=" << sh_b_0->get_lenth() << endl;
    std_out << "sh_b_0->print();" << endl;
    sh_b_0->print();
    std_out << "sh_b_0->out_comment()" << endl << sh_b_0->out_comment() << endl;

    {
        shape_b* sh_b_1 = new shape_b ( 260, 30, 200, 1 );
        std_out << "sh_b_1->out_comment()" << endl << sh_b_1->out_comment() << endl;
        sh_b_1->print();
        delete sh_b_1;
    }

    {
        draw_vars dw;
        stack st;
        sh_b_0->edit ( );
    }

    return 0;
}

int test_shape_cd ( void )
{
    shape_cd* sh_cd_0 = new shape_cd;
    {
        draw_vars dw;
        stack st;
        sh_cd_0->edit ( );
    }

    return 0;
}

int test_shape_e ( void )
{
    return 0;
}

int test_font ( void )
{
    QTextStream std_out ( stdout );
    QTextStream std_in ( stdin );

    std_out << "int test_font ( void )" << endl;
    font fnt;

    QList<forma_l*> * llist = fnt.get_m_forma_l_list();
    int sss = llist->size();


    fnt.set_file_name ( QString ( "/home/namatv/workspace/u2/shp/my_test.shp" ) );
    fnt.font_load();

    sss = llist->size();

    for ( int i = 0; i < llist->size(); ++i )
    {
        forma_l * mmm = ( *llist ) [i];

        for ( int j;j < mmm->get_List_bites().size() ;++j )
        {
//      std_out<<mmm->m_bites[j]<<" ";
        }

        std_out << endl;
    }

    std_out << "int test_font ( void )============================================" << endl;

    return 0;
}

int test_forma ( void )
{
    /*
      QList<shapes*> sh_lst=form->get_m_shapes();
      shape_12* sh_12_0 = new shape_12;
      sh_lst.append(sh_12_0);
      shapes* sh_0 = sh_lst.at(0);
      sh_0->print();
    */
    forma* form = new forma;
    {
        draw_vars dr;
        stack st;
//    form->edit ( dr, st );
    }

    return 0;
}
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
