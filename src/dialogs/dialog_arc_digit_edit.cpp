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

#include "dialog_arc_digit_edit.h"
#include "dialog_arc_digit_edit.moc"


DialogArcDigitEdit::DialogArcDigitEdit ( QWidget *parent )
		: QDialog ( parent )
		, m_shape ( 0 )
{
	ui.setupUi ( this );
}

void DialogArcDigitEdit ::accept ()
{
	m_radius = ui.spBox_Radius->value();
	m_startDigit = ui.spBox_StartDigit->value();
	m_endDigit = ui.spBox_EndDigit->value();
	m_dirCounterClockwise = ui.rButton_CounerClockwise->isChecked();

	done ( QDialog::Accepted );
}

void DialogArcDigitEdit::set_radius ( int theValue )
{
	ui.spBox_Radius->setValue ( theValue );
	m_radius = ui.spBox_Radius->value();
}

int DialogArcDigitEdit::get_radius ( void )
{
	return m_radius;
}

void DialogArcDigitEdit::set_startDigit ( int theValue )
{
	ui.spBox_StartDigit->setValue ( theValue );
	m_startDigit = ui.spBox_StartDigit->value();
}

int DialogArcDigitEdit::get_startDigit ( void )
{
	return m_startDigit;
}

void DialogArcDigitEdit::set_endDigit ( int theValue )
{
	ui.spBox_EndDigit->setValue ( theValue );
	m_endDigit = ui.spBox_EndDigit->value();
}

int DialogArcDigitEdit::get_endDigit ( void )
{
	return m_endDigit;
}

void DialogArcDigitEdit::set_dirCounterClockwise ( bool theValue )
{
	ui.rButton_CounerClockwise->setChecked ( theValue );
	ui.rButton_Clockwise->setChecked ( !theValue );
	m_dirCounterClockwise = ui.rButton_CounerClockwise->isChecked();
}

bool DialogArcDigitEdit::get_dirCounterClockwise ( void )
{
	return m_dirCounterClockwise;
}

void DialogArcDigitEdit::arcDigitStartChadged ( int theValue )
{
	m_shape->set_start(theValue, m_shape->get_dir());

	emit arcDigitChanged();
}

void DialogArcDigitEdit::arcDigitEndChadged ( int theValue )
{
	m_shape->set_end(theValue, m_shape->get_dir());

	emit arcDigitChanged();
}

void DialogArcDigitEdit::arcDigitRadiusChadged ( int theValue )
{
	m_shape->set_radius(theValue);

	emit arcDigitChanged();
}

void DialogArcDigitEdit::arcDigitDirectionCounterClockwiseClicked ( bool theValue )
{
	if(theValue)
		m_shape->set_dir(1);

	emit arcDigitChanged();
}

void DialogArcDigitEdit::arcDigitDirectionClockwiseClicked ( bool theValue )
{
	if(theValue)
		m_shape->set_dir(-1);

	emit arcDigitChanged();
}

shape_b* DialogArcDigitEdit::get_shape ( void )
{
	return m_shape;
}

void DialogArcDigitEdit::set_shape ( shape_b* theValue )
{
	m_shape = theValue;
}
