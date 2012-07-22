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

#include "dialog_arc_octant_edit.h"
#include "dialog_arc_octant_edit.moc"

DialogArcOctantEdit::DialogArcOctantEdit ( QWidget *parent ) 
: QDialog ( parent )
, m_shape(0)
{
	ui.setupUi ( this );
}

void DialogArcOctantEdit ::accept ()
{
  m_radius=ui.spBox_Radius->value();
  m_startOctant=ui.spBox_StartOctant->value();
  m_numberOctant=ui.spBox_NumberOctant->value();

	done ( QDialog::Accepted );
}

void DialogArcOctantEdit::set_radius ( int theValue )
{
  ui.spBox_Radius->setValue(theValue);
  m_radius=ui.spBox_Radius->value();
}

int DialogArcOctantEdit::get_radius ( void )
{
  return m_radius;
}

void DialogArcOctantEdit::set_startOctant ( int theValue )
{
  ui.spBox_StartOctant->setValue(theValue);
  m_startOctant=ui.spBox_StartOctant->value();
}

int DialogArcOctantEdit::get_startOctant ( void )
{
    return m_startOctant;
}

void DialogArcOctantEdit::set_numberOctant ( int theValue )
{
  ui.spBox_NumberOctant->setValue(theValue);
  m_numberOctant=ui.spBox_NumberOctant->value();
}

int DialogArcOctantEdit::get_numberOctant ( void )
{
  return m_numberOctant;
}

shape_a* DialogArcOctantEdit::get_shape(void)
{
	return m_shape;
}

void DialogArcOctantEdit::set_shape(shape_a* theValue)
{
	m_shape=theValue;
}

void DialogArcOctantEdit::acrOctantStartChadged(int theValue)
{
	m_shape->set_start(theValue);

	emit arcOctantChanged ();
}

void DialogArcOctantEdit::acrOctantNumberChadged(int theValue)
{
	m_shape->set_number(theValue);

	emit arcOctantChanged ();
}

void DialogArcOctantEdit::acrOctantRadiusChadged(int theValue)
{
	m_shape->set_radius(theValue);

	emit arcOctantChanged ();
}
