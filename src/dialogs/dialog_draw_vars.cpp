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

#include "dialog_draw_vars.h"
#include "dialog_draw_vars.moc"

#include "draw_var.h"
#include <QColorDialog>

DialogDrawVars::DialogDrawVars ( QWidget *parent )
{
    ui.setupUi ( this );

    DialogDrawVars::loadDefaults();

    ui.spBox_net_x_min->setMinimum(-1000);
    ui.spBox_net_x_min->setMaximum(1000);

    ui.spBox_net_y_min->setMinimum(-1000);
    ui.spBox_net_y_min->setMaximum(1000);

    ui.spBox_net_width->setMaximum(1280);
    ui.spBox_net_hight->setMaximum(1024);

    if (draw_vars::s_drawHorisontal )
        ui.chBox_drawHorisontal->setCheckState(Qt::Checked);
    else
        ui.chBox_drawHorisontal->setCheckState(Qt::Unchecked);

    if (draw_vars::s_drawAll )
        ui.chBox_drawAll->setCheckState(Qt::Checked);
    else
        ui.chBox_drawAll->setCheckState(Qt::Unchecked);

    if (draw_vars::s_drawNet )
        ui.chBox_drawNet->setCheckState(Qt::Checked);
    else
        ui.chBox_drawNet->setCheckState(Qt::Unchecked);

    ui.spBox_net_x_min->setValue(draw_vars::net_hor.x());
    ui.spBox_net_y_min->setValue(draw_vars::net_hor.y());
    ui.spBox_net_width->setValue(draw_vars::net_hor.width());
    ui.spBox_net_hight->setValue(draw_vars::net_hor.height());

    redrawScanes();
}

void DialogDrawVars::accept ()
{
    save();
    done ( QDialog::Accepted );
}

void DialogDrawVars::set_color_pen_down ( QColor new_color )
{
    color_pen_down = new_color;
}

QColor DialogDrawVars::get_color_pen_down ( void )
{
    return color_pen_down;
}

void DialogDrawVars::set_color_pen_up ( QColor  new_color )
{
    color_pen_up = new_color;
}

QColor DialogDrawVars::get_color_pen_up ( void )
{
    return color_pen_up;
}

void DialogDrawVars::set_color_12 ( QColor  new_color )
{
    color_12 = new_color;
}

QColor DialogDrawVars::get_color_12 ( void )
{
    return color_12;
}

void DialogDrawVars::set_color_34 ( QColor  new_color )
{
    color_34 = new_color;
}

QColor DialogDrawVars::get_color_34 ( void )
{
    return color_34;
}

void DialogDrawVars::set_color_56 ( QColor  new_color )
{
    color_56 = new_color;
}

QColor DialogDrawVars::get_color_56 ( void )
{
    return color_56;
}

void DialogDrawVars::set_color_7 ( QColor  new_color )
{
    color_7 = new_color;
}

QColor DialogDrawVars::get_color_7 ( void )
{
    return color_7;
}

void DialogDrawVars::set_color_cur ( QColor  new_color )
{
    color_cur = new_color;
}

QColor DialogDrawVars::get_color_cur ( void )
{
    return color_cur;
}

void DialogDrawVars::set_color_9d ( QColor  new_color )
{
    color_9d = new_color;
}

QColor DialogDrawVars::get_color_9d ( void )
{
    return color_9d;
}

void DialogDrawVars::set_color_e ( QColor  new_color )
{
    color_e = new_color;
}

QColor DialogDrawVars::get_color_e ( void )
{
    return color_e;
}

/*
int value () const
void setValue ( int val )

    QGraphicsView *grView_color_pen_up;
    QGraphicsView *grView_color_pen_down;
    QGraphicsView *grView_color_12;
    QGraphicsView *grView_color_34;
    QGraphicsView *grView_color_56;
    QGraphicsView *grView_color_7;
    QGraphicsView *grView_color_cur;
    QGraphicsView *grView_color_9d;
    QGraphicsView *grView_color_e;
*/

void DialogDrawVars::set_width_pen_down ( int val )
{
    this->ui.spBox_width_pen_down->setValue ( val );
}

int DialogDrawVars::get_width_pen_down ( void )
{
    return  this->ui.spBox_width_pen_down->value ( );
}

void DialogDrawVars::set_width_pen_up ( int val )
{
    this->ui.spBox_width_pen_up->setValue ( val );
}

int DialogDrawVars::get_width_pen_up ( void )
{
    return this->ui.spBox_width_pen_up->value ( );
}

void DialogDrawVars::set_width_12 ( int val )
{
    if ( ui.spBox_width_12->value ( ) != val )
        ui.spBox_width_12->setValue ( val );
}

int DialogDrawVars::get_width_12 ( void )
{
    return ui.spBox_width_12->value ( );
}

void DialogDrawVars::set_width_34 ( int val )
{
    if ( ui.spBox_width_34->value ( ) != val )
        ui.spBox_width_34->setValue ( val );
}

int DialogDrawVars::get_width_34 ( void )
{
    return this->ui.spBox_width_34->value ( );
}

void DialogDrawVars::set_width_56 ( int val )
{
    if ( ui.spBox_width_56->value ( ) != val )
        this->ui.spBox_width_56->setValue ( val );
}

int DialogDrawVars::get_width_56 ( void )
{
    return this->ui.spBox_width_56->value ( );
}

void DialogDrawVars::set_width_7 ( int val )
{
    if ( ui.spBox_width_7->value ( ) != val )
        ui.spBox_width_7->setValue ( val );
}

int DialogDrawVars::get_width_7 ( void )
{
    return this->ui.spBox_width_7->value ( );
}

void DialogDrawVars::set_width_cur ( int val )
{
    if ( ui.spBox_width_cur->value ( ) != val )
        ui.spBox_width_cur->setValue ( val );
}

int DialogDrawVars::get_width_cur ( void )
{
    return this->ui.spBox_width_cur->value ( );
}

void DialogDrawVars::set_width_9d ( int val )
{
    if ( ui.spBox_width_9d->value ( ) != val )
        ui.spBox_width_9d->setValue ( val );
}

int DialogDrawVars::get_width_9d ( void )
{
    return this->ui.spBox_width_9d->value ( );
}

void DialogDrawVars::set_width_e ( int val )
{
    if ( ui.spBox_width_e->value ( ) != val )
        ui.spBox_width_e->setValue ( val );
}

int DialogDrawVars::get_width_e ( void )
{
    return this->ui.spBox_width_e->value ( );
}


QColor DialogDrawVars::pB_color_pen_up_pressed ( void )
{
//QColor color = QColorDialog::getColor ( const QColor & initial = Qt::white, QWidget * parent = 0 );
    QColor color_rez;
    color_rez = QColorDialog::getColor ( get_color_pen_up() );
    set_color_pen_up ( color_rez );
    redrawScanes();
    return color_rez;
}

QColor DialogDrawVars::pB_color_pen_down_pressed ( void )
{
    QColor color_rez;
    color_rez = QColorDialog::getColor ( get_color_pen_down() );
    set_color_pen_down ( color_rez );
    redrawScanes();
    return color_rez;
}

QColor DialogDrawVars::pB_color_12_pressed ( void )
{
    QColor color_rez;
    color_rez = QColorDialog::getColor ( get_color_12() );
    set_color_12 ( color_rez );
    redrawScanes();
    return color_rez;
}

QColor DialogDrawVars::pB_color_34_pressed ( void )
{
    QColor color_rez;
    color_rez = QColorDialog::getColor ( get_color_34() );
    set_color_34 ( color_rez );
    redrawScanes();
    return color_rez;
}

QColor DialogDrawVars::pB_color_56_pressed ( void )
{
    QColor color_rez;
    color_rez = QColorDialog::getColor ( get_color_56() );
    set_color_56 ( color_rez );
    redrawScanes();
    return color_rez;
}

QColor DialogDrawVars::pB_color_7_pressed ( void )
{
    QColor color_rez;
    color_rez = QColorDialog::getColor ( get_color_7() );
    set_color_7 ( color_rez );
    redrawScanes();
    return color_rez;
}

QColor DialogDrawVars::pB_color_cur_pressed ( void )
{
    QColor color_rez;
    color_rez = QColorDialog::getColor ( get_color_cur() );
    set_color_cur ( color_rez );
    redrawScanes();
    return color_rez;
}

QColor DialogDrawVars::pB_color_9d_pressed ( void )
{
    QColor color_rez;
    color_rez = QColorDialog::getColor ( get_color_9d() );
    set_color_9d ( color_rez );
    redrawScanes();
    return color_rez;
}

QColor DialogDrawVars::pB_color_e_pressed ( void )
{
    QColor color_rez;
    color_rez = QColorDialog::getColor ( get_color_e() );
    set_color_e ( color_rez );
    redrawScanes();
    return color_rez;
}

void DialogDrawVars::spB_width_pen_up_changed ( void )
{
    redrawScanes();
}

void DialogDrawVars::spB_width_pen_down_changed ( void )
{
    redrawScanes();
}

void DialogDrawVars::spB_width_12_changed ( void )
{
    redrawScanes();
}

void DialogDrawVars::spB_width_34_changed ( void )
{
    redrawScanes();
}

void DialogDrawVars::spB_width_56_changed ( void )
{
    redrawScanes();
}

void DialogDrawVars::spB_width_7_changed ( void )
{
    redrawScanes();
}

void DialogDrawVars::spB_width_9d_changed ( void )
{
    redrawScanes();
}

void DialogDrawVars::spB_width_cur_changed ( void )
{
    redrawScanes();
}

void DialogDrawVars::spB_width_e_changed ( void )
{
    redrawScanes();
}


void DialogDrawVars::redrawScanes ( void )
{
    scene_pen_down.clear();
    scene_pen_up.clear();
    scene_12.clear();
    scene_34.clear();
    scene_56.clear();
    scene_7.clear();
    scene_cur.clear();
    scene_9d.clear();
    scene_e.clear();

    scene_pen_down.addLine ( 5, 12, 75, 12, QPen ( QBrush ( color_pen_down ), this->ui.spBox_width_pen_down->value() ) );
    scene_pen_up.addLine ( 5, 12, 75, 12, QPen ( QBrush ( color_pen_up ), this->ui.spBox_width_pen_up->value() ) );
    scene_12.addLine ( 5, 12, 75, 12, QPen ( QBrush ( color_12 ), this->ui.spBox_width_12->value() ) );
    scene_34.addLine ( 5, 12, 75, 12, QPen ( QBrush ( color_34 ), this->ui.spBox_width_34->value() ) );
    scene_56.addLine ( 5, 12, 75, 12, QPen ( QBrush ( color_56 ), this->ui.spBox_width_56->value() ) );
    scene_7.addLine ( 5, 12, 75, 12, QPen ( QBrush ( color_7 ), this->ui.spBox_width_7->value() ) );
    scene_cur.addLine ( 5, 12, 75, 12, QPen ( QBrush ( color_cur ), this->ui.spBox_width_cur->value() ) );
    scene_9d.addLine ( 5, 12, 75, 12, QPen ( QBrush ( color_9d ), this->ui.spBox_width_9d->value() ) );
    scene_e.addLine ( 5, 12, 75, 12, QPen ( QBrush ( color_e ), this->ui.spBox_width_e->value() ) );

    ui.grView_color_pen_down->setScene ( & scene_pen_down );
    ui.grView_color_pen_up->setScene ( & scene_pen_up );
    ui.grView_color_12->setScene ( & scene_12 );
    ui.grView_color_34->setScene ( & scene_34 );
    ui.grView_color_56->setScene ( & scene_56 );
    ui.grView_color_7->setScene ( & scene_7 );
    ui.grView_color_9d->setScene ( & scene_9d );
    ui.grView_color_cur->setScene ( & scene_cur );
    ui.grView_color_e->setScene ( & scene_e );
}


void DialogDrawVars::pB_Defaults_pressed ( void )
{
    loadDefaults ( );
    redrawScanes ( );
}

void DialogDrawVars::pB_Save_pressed ( void )
{

}

void DialogDrawVars::loadDefaults ( void )
{
    color_pen_down = draw_vars::s_color_pen_down;
    color_pen_up = draw_vars::s_color_pen_up;
    color_12 = draw_vars::s_color_12;
    color_34 = draw_vars::s_color_34;
    color_56 = draw_vars::s_color_56;
    color_7 = draw_vars::s_color_7;
    color_cur = draw_vars::s_color_cur;
    color_9d = draw_vars::s_color_9d;
    color_e = draw_vars::s_color_e;

    set_width_pen_down ( draw_vars::s_width_pen_down );
    set_width_pen_up ( draw_vars::s_width_pen_up );
    set_width_12 ( draw_vars::s_width_12 );
    set_width_34 ( draw_vars::s_width_34 );
    set_width_56 ( draw_vars::s_width_56 );
    set_width_7 ( draw_vars::s_width_7 );
    set_width_cur ( draw_vars::s_width_cur );
    set_width_9d ( draw_vars::s_width_9d );
    set_width_e ( draw_vars::s_width_e );
}

void DialogDrawVars::save()
{
    draw_vars::s_color_pen_down = color_pen_down ;
    draw_vars::s_color_pen_up = color_pen_up;
    draw_vars::s_color_12 = color_12;
    draw_vars::s_color_34 = color_34;
    draw_vars::s_color_56 = color_56;
    draw_vars::s_color_7 = color_7;
    draw_vars::s_color_cur = color_cur;
    draw_vars::s_color_9d = color_9d;
    draw_vars::s_color_e = color_e;

    draw_vars::s_width_pen_down = get_width_pen_down();
    draw_vars::s_width_pen_up = get_width_pen_up();
    draw_vars::s_width_12 = get_width_12( );
    draw_vars::s_width_34 = get_width_34();
    draw_vars::s_width_56 = get_width_56();
    draw_vars::s_width_7 = get_width_7();
    draw_vars::s_width_cur = get_width_cur();
    draw_vars::s_width_9d = get_width_9d();
    draw_vars::s_width_e = get_width_e();

    draw_vars::net_hor.setRect(ui.spBox_net_x_min->value(),
                               ui.spBox_net_y_min->value(),
                               ui.spBox_net_width->value(),
                               ui.spBox_net_hight->value()
                              );

    if (ui.chBox_drawHorisontal->checkState() == Qt::Checked )
        draw_vars::s_drawHorisontal=true;
    else
        draw_vars::s_drawHorisontal=false;

    if (ui.chBox_drawAll->checkState() == Qt::Checked )
        draw_vars::s_drawAll=true;
    else
        draw_vars::s_drawAll=false;

    if (ui.chBox_drawNet->checkState()== Qt::Checked)
        draw_vars::s_drawNet =true;
    else
        draw_vars::s_drawNet =false;
}
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
