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

#include "dialog_multi_arc_edit.h"
#include "dialog_multi_arc_edit.moc"

extern Main_Form  *theMainForm;

DialogMultiArcEdit::DialogMultiArcEdit ( QWidget *parent )
        : QDialog ( parent )
        , m_shape ( 0 )
{
    ui.setupUi ( this );
}

shape_cd* DialogMultiArcEdit::get_shape ( void )
{
    return m_shape;
}

void DialogMultiArcEdit::set_shape ( shape_cd* theValue )
{
    QTextStream std_out ( stdout );
    QTextStream std_in ( stdin );

    m_shape = theValue;
    int length = m_shape->get_lenth();
    int n_segment = m_shape->get_n_segment();
    int current = m_shape->get_current();

    std_out << endl << "void DialogMultiArcEdit::set_shape ( shape_cd* theValue )" << endl;
    std_out << "length = " << length << endl;
    std_out << "n_segment = " << n_segment << endl;
    ui.tableWidget->setRowCount ( n_segment );


    for ( int i = 0; i < n_segment;++i )
    {
        int x = m_shape->get_x ( i );
        int y = m_shape->get_y ( i );
        int c = m_shape->get_c ( i );
        QTableWidgetItem *x_Item = new QTableWidgetItem ( tr ( "%1" ).arg ( x ) );
        ui.tableWidget->setItem ( i, 0, x_Item );
        QTableWidgetItem *y_Item = new QTableWidgetItem ( tr ( "%1" ).arg ( y ) );
        ui.tableWidget->setItem ( i, 1, y_Item );
        QTableWidgetItem *c_Item = new QTableWidgetItem ( tr ( "%1" ).arg ( c ) );
        ui.tableWidget->setItem ( i, 2, c_Item );
    }
    ui.tableWidget->setCurrentCell(current,0);
}

void DialogMultiArcEdit::accept ()
{
    QTextStream std_out ( stdout );
    QTextStream std_in ( stdin );

    std_out << "void DialogMultiArcEdit::accept ()" << endl;

    QList<int> Dxy;
    int row_number = ui.tableWidget->rowCount();
    int col_number =  ui.tableWidget->columnCount();
    int row_current = ui.tableWidget->currentRow();
    if (col_number != 3)
        return;
    for (int i = 0; i < row_number; i++)
    {
        QTableWidgetItem* i_x = ui.tableWidget->item(i,0);
        QTableWidgetItem* i_y = ui.tableWidget->item(i,1);
        QTableWidgetItem* i_c = ui.tableWidget->item(i,2);

        int dx=i_x->text().toInt();
        int dy=i_y->text().toInt();
        int c=i_c->text().toInt();
        Dxy << dx << dy << c;
    }
    m_shape->replace(Dxy);
    m_shape->set_current(row_current);
    
    done ( QDialog::Accepted );
}

void DialogMultiArcEdit::insert_before_pushed()
{
    int row = ui.tableWidget->currentRow();
    ui.tableWidget->insertRow(row);

    QTableWidgetItem *x_Item = new QTableWidgetItem ( tr ( "%1" ).arg ( 1 ) );
    ui.tableWidget->setItem ( row, 0, x_Item );

    QTableWidgetItem *y_Item = new QTableWidgetItem ( tr ( "%1" ).arg ( 0 ) );
    ui.tableWidget->setItem ( row, 1, y_Item );

    QTableWidgetItem *c_Item = new QTableWidgetItem ( tr ( "%1" ).arg ( 0 ) );
    ui.tableWidget->setItem ( row, 2, c_Item );
}

void DialogMultiArcEdit::insert_next_pushed()
{
    int row = ui.tableWidget->currentRow();
    ui.tableWidget->insertRow(row+1);

    QTableWidgetItem *x_Item = new QTableWidgetItem ( tr ( "%1" ).arg ( 1 ) );
    ui.tableWidget->setItem ( row+1, 0, x_Item );

    QTableWidgetItem *y_Item = new QTableWidgetItem ( tr ( "%1" ).arg ( 0 ) );
    ui.tableWidget->setItem ( row+1, 1, y_Item );

    QTableWidgetItem *c_Item = new QTableWidgetItem ( tr ( "%1" ).arg ( 0 ) );
    ui.tableWidget->setItem ( row+1, 2, c_Item );
    
}

void DialogMultiArcEdit::delete_pushed()
{
    int row = ui.tableWidget->currentRow();
    int rows=ui.tableWidget->rowCount();
    if (1<rows)
        ui.tableWidget->removeRow(row);
}

void DialogMultiArcEdit::cell_was_changed(int c_row,int c_col,int p_row,int p_col)
{
  QList<int> Dxy;
  int row_number = ui.tableWidget->rowCount();
  int col_number =  ui.tableWidget->columnCount();
  int row_current = ui.tableWidget->currentRow();
  if (col_number != 3)
    return;
  for (int i = 0; i < row_number; i++)
  {
    QTableWidgetItem* i_x = ui.tableWidget->item(i,0);
    QTableWidgetItem* i_y = ui.tableWidget->item(i,1);
    QTableWidgetItem* i_c = ui.tableWidget->item(i,2);
    
    int dx=i_x->text().toInt();
    int dy=i_y->text().toInt();
    int c=i_c->text().toInt();
    Dxy << dx << dy << c;
  }
  m_shape->replace(Dxy);
  m_shape->set_current(row_current);
  
  
  if ( theMainForm )
    theMainForm->reDrawCurrentFormInFoma_l();
  
}

// kate: indent-mode cstyle; space-indent on; indent-width 0; 
