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

#include "main_form.h"
#include "main_form.moc"

#include <QFileDialog>
#include <QPushButton>
#include <QWheelEvent>

#include "dialog_font_header.h"
#include "dialog_draw_vars.h"
#include "dialog_forms_find.h"
#include "dialog_forms_header.h"

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

extern QTextStream std_out;
extern QTextStream std_in;

Main_Form::Main_Form ( QWidget * parent )
        : QWidget ( parent )
        , m_edit_menu ( 0 )
        , m_current_forma_l ( 0 )
        , m_current_shape ( 0 )
        , m_current_sub_shape ( 0 )
{
    m_edit_menu = new edit_menu;

    this->resize ( 740, 447 );

    horizontalLayout = new QHBoxLayout ( this );
    horizontalLayout->setObjectName ( QString::fromUtf8 ( "horizontalLayout" ) );
    graphicsView = new QGraphicsView ( this );

    QGraphicsScene * sc = new QGraphicsScene;
    graphicsView->setScene ( sc );

    QTransform transform ( 1, 0, 0, 0, -1, 0, 0, 0, 1);
    qreal scale = 1.0;
    transform.scale ( scale, scale );
    graphicsView->setTransform ( transform );

    
    graphicsView->setObjectName ( QString::fromUtf8 ( "graphicsView" ) );
    graphicsView->setMinimumSize ( QSize ( 300, 300 ) );
    graphicsView->setMaximumSize ( QSize ( 16777215, 16777215 ) );

    horizontalLayout->addWidget ( graphicsView );

    horizontalLayout->addWidget ( m_edit_menu->s_menu_font_main );


//	horizontalLayout->addWidget ( m_edit_menu->s_menu_font_parametr );
//	m_edit_menu->s_menu_font_parametr->hide();

    horizontalLayout->addWidget ( m_edit_menu->s_menu_font_forms );
    m_edit_menu->s_menu_font_forms->hide();

    horizontalLayout->addWidget ( m_edit_menu->s_menu_font_forms );
    m_edit_menu->s_menu_font_forms->hide();


    horizontalLayout->addWidget ( m_edit_menu->s_menu_draw_vars_font_main_direction );
    m_edit_menu->s_menu_draw_vars_font_main_direction->hide();


    /*	horizontalLayout->addWidget ( m_edit_menu->s_menu_draw_vars_edit_main );
    	m_edit_menu->s_menu_draw_vars_edit_main->hide();
    */

    horizontalLayout->addWidget ( m_edit_menu->s_menu_color );
    m_edit_menu->s_menu_color->hide();


    horizontalLayout->addWidget ( m_edit_menu->s_menu_font_find_form );
    m_edit_menu->s_menu_font_find_form->hide();

    horizontalLayout->addWidget ( m_edit_menu->s_menu_shape_12_pen );
    m_edit_menu->s_menu_shape_12_pen->hide();

    horizontalLayout->addWidget ( m_edit_menu->s_menu_font_yes_no );
    m_edit_menu->s_menu_font_yes_no->hide();

    /********************************************************************************************/

    horizontalLayout->addWidget ( m_edit_menu->s_menu_form );
    m_edit_menu->s_menu_form->hide();

    horizontalLayout->addWidget ( m_edit_menu->s_menu_form_insert_shapes );
    m_edit_menu->s_menu_form_insert_shapes->hide();

    connect_setup();

}

void Main_Form::connect_setup()
{
    QPushButton *bPush;

    bPush = m_edit_menu->s_menu_font_main->findByText ( QString ( "&Open" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontMainOpen() ) );

//	bPush = m_edit_menu->s_menu_font_main->findByText ( QString ( "&New" ) );
//	connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontMainNew() ) );


    bPush = m_edit_menu->s_menu_font_main->findByText ( QString ( "&Save" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontMainSave() ) );

    bPush = m_edit_menu->s_menu_font_main->findByText ( QString ( "Save &as" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontMainSaveAs() ) );

    bPush = m_edit_menu->s_menu_font_main->findByText ( QString ( "Edit &header" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontMainEditHeader() ) );

    bPush = m_edit_menu->s_menu_font_main->findByText ( QString ( "Edit &forms" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontMainEditForms() ) );

    bPush = m_edit_menu->s_menu_font_main->findByText ( QString ( "&Draw vars" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontMainDrawVars() ) );

    bPush = m_edit_menu->s_menu_font_main->findByText ( QString ( "&Close" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontMainClose() ) );

    bPush = m_edit_menu->s_menu_font_main->findByText ( QString ( "E&xit" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontMainExit() ) );

    /**************************************************************************************/

//	bPush = m_edit_menu->s_menu_font_parametr->findByText ( QString ( "&Above" ) );
//	connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontHeaderAbove() ) );

//	bPush = m_edit_menu->s_menu_font_parametr->findByText ( QString ( "&Below" ) );
//	connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontHeaderBelow() ) );

//	bPush = m_edit_menu->s_menu_font_parametr->findByText ( QString ( "&Modes" ) );
//	connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontHeaderModes() ) );

//	bPush = m_edit_menu->s_menu_font_parametr->findByText ( QString ( "Attrib&ute" ) );
//	connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontHeaderAttribute() ) );

//	bPush = m_edit_menu->s_menu_font_parametr->findByText ( QString ( "E&xit" ) );
//	connect ( bPush, SIGNAL ( released() ), this, SLOT ( fontHeaderExit() ) );

    /**************************************************************************************/

    bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "&Header..." ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsHeader() ) );

    bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "Forma &ed..." ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsFormaEdit() ) );

    bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "&Prev" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsPrev() ) );

    bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "&Next" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsNext() ) );

    bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "&Home" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsHome() ) );

    bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "En&d" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsEnd() ) );

    bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "&Find..." ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsFind() ) );

    bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "Ins pa&st" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsInsertPast() ) );

    bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "&Ins befor" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsInsertBefor() ) );

    bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "Delete..." ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsDelete() ) );

    bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "Backspace..." ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsBackspace() ) );

    bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "E&xit" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsExit() ) );

    /**************************************************************************************/

    bPush = m_edit_menu->s_menu_form->findByText ( QString ( "&Edit..." ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaEdit() ) );

    bPush = m_edit_menu->s_menu_form->findByText ( QString ( "&Draw var..." ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaDrawVars() ) );

    bPush = m_edit_menu->s_menu_form->findByText ( QString ( "&Prev" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaPrev() ) );

    bPush = m_edit_menu->s_menu_form->findByText ( QString ( "&Next" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaNext() ) );

    bPush = m_edit_menu->s_menu_form->findByText ( QString ( "&Home" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaHome() ) );

    bPush = m_edit_menu->s_menu_form->findByText ( QString ( "En&d" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaEnd() ) );

    bPush = m_edit_menu->s_menu_form->findByText ( QString ( "Ins pa&st" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaInsert_Past() ) );

    bPush = m_edit_menu->s_menu_form->findByText ( QString ( "&Ins befor" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaInsert_Before() ) );

    bPush = m_edit_menu->s_menu_form->findByText ( QString ( "Dele&te" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaDelete() ) );

    bPush = m_edit_menu->s_menu_form->findByText ( QString ( "Backspace" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaBackspace() ) );

    bPush = m_edit_menu->s_menu_form->findByText ( QString ( "E&xit" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaExit() ) );

    /**************************************************************************************/

    bPush = m_edit_menu->s_menu_form_insert_shapes->findByText ( QString ( "&Line..." ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaInsertLine() ) );

    bPush = m_edit_menu->s_menu_form_insert_shapes->findByText ( QString ( "&Pen" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaInsertPen() ) );

    bPush = m_edit_menu->s_menu_form_insert_shapes->findByText ( QString ( "&Scale" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaInsertScale() ) );

    bPush = m_edit_menu->s_menu_form_insert_shapes->findByText ( QString ( "Stac&k" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaInsertStack() ) );

    bPush = m_edit_menu->s_menu_form_insert_shapes->findByText ( QString ( "Reference" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaInsertReference() ) );

    bPush = m_edit_menu->s_menu_form_insert_shapes->findByText ( QString ( "Line_89" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaInsertLine89() ) );

    bPush = m_edit_menu->s_menu_form_insert_shapes->findByText ( QString ( "Octant_Arc" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaInsertOctantArc() ) );

    bPush = m_edit_menu->s_menu_form_insert_shapes->findByText ( QString ( "Digit_Arc" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaInsertDigitArc() ) );

    bPush = m_edit_menu->s_menu_form_insert_shapes->findByText ( QString ( "CurveLine_cd" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaInsertCurveLineCD() ) );

    bPush = m_edit_menu->s_menu_form_insert_shapes->findByText ( QString ( "Vertical" ) );
    connect ( bPush, SIGNAL ( released() ), this, SLOT ( formaInsertVertical() ) );

    /*************************************************************************************************/

// 	bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "&Number" ) );
// 	connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsHeaderNumber() ) );

// 	bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "A&SCII" ) );
// 	connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsHeaderAscii() ) );

// 	bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "&Attribute" ) );
// 	connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsHeaderAttribute() ) );

// 	bPush = m_edit_menu->s_menu_font_forms->findByText ( QString ( "E&xit" ) );
// 	connect ( bPush, SIGNAL ( released() ), this, SLOT ( formsHeaderExit() ) );
}

/**/
void Main_Form::fontMainOpen()
{
    QString fileName = QFileDialog::getOpenFileName ( 0, QString ( "Open File" ), QString ( "/home/namatv/workspace/u2/shp" ), QString ( "Shape files (*.shp)" ) );
//				fileName = QString ( "/home/namatv/workspace/u2/shp/es_unicode.shp" );
    std_out << fileName << endl;

    if ( fileName != 0 )
    {
        m_edit_menu->m_font->set_file_name ( fileName );
        m_edit_menu->m_font->font_load();
//		m_edit_menu->m_font->
    }

    m_edit_menu->s_menu_font_main->show();										//Показать меню
}

/*
void Main_Form::fontMainNew()
{
	QString fileName = QFileDialog::getOpenFileName ( 0, QString ( "Open File" ), QString ( "/home/namatv/workspace/u2/shp" ), QString ( "Shape files (*.shp)" ) );

	std_out << fileName << endl;

	if ( fileName != 0 )
	{
		m_edit_menu->m_font->set_file_name ( fileName );
		m_edit_menu->m_font->font_load();
	}

	m_edit_menu->s_menu_font_main->show();										//Показать меню

}
*/
void Main_Form::fontMainSave()
{

    if ( m_edit_menu->m_font->get_file_name() == QString ( "" ) )
    {
        QString fileName = QFileDialog::getSaveFileName
                           ( 0, tr ( "Save File" ),
                             QString ( "~" ),
                             tr ( "Shape files (*.shp)" ) );

        if ( fileName == 0 )
            return;

        m_edit_menu->m_font->set_file_name ( fileName );
    }

    m_edit_menu->m_font->font_save();

    m_edit_menu->s_menu_font_main->show();										//Показать меню
}

void Main_Form::fontMainSaveAs()
{

    QString fileName = QFileDialog::getSaveFileName
                       ( 0, tr ( "Save As File" ),
                         QString ( "~" ),
                         tr ( "Shape files (*.shp)" ) );

    if ( fileName == 0 )
        return;

    m_edit_menu->m_font->set_file_name ( fileName );

    m_edit_menu->m_font->font_save();

    m_edit_menu->s_menu_font_main->show();										//Показать меню
}

void Main_Form::fontMainEditHeader()
{
    DialogFontHeader *b1 = new DialogFontHeader;

    int above = m_edit_menu->m_font->get_above();
    int below = m_edit_menu->m_font->get_below();
    int modes = m_edit_menu->m_font->get_modes();
    QString attribute = m_edit_menu->m_font->get_attribute();

    b1->set_above ( above );
    b1->set_below ( below );
    b1->set_modes ( modes );
    b1->set_attribute ( attribute );
    b1->set_m_edit_menu ( m_edit_menu );

    b1->exec();

    m_edit_menu->s_menu_font_main->show();										//Показать меню
//m_edit_menu->s_menu_font_parametr->show();								//Показать меню
}

void Main_Form::fontMainEditForms()
{
    m_edit_menu->s_menu_font_main->hide();

    QList<forma_l*> * Forma_l = m_edit_menu->m_font->get_m_forma_l_list();
    int size = Forma_l->size();

    if ( size > 0 )
    {
        graphicsView->scene()->clear();

        forma *a = ( *Forma_l ) [0]->get_m_forma();
        dr.set_initial();
        dr.draw(*graphicsView->scene());
        stack st;
        a->draw ( dr, st, *graphicsView->scene() );
        graphicsView->invalidateScene ();
    }

    m_edit_menu->s_menu_font_forms->show();									//Показать меню
}

void Main_Form::fontMainDrawVars()
{
    exec_Draw_Vars_Dialog();
}

void Main_Form::fontMainClose()
{}

void Main_Form::fontMainExit()
{
    this->close();
}

/**
forms. Диалог редактирования заголовка формы
*/
void Main_Form::formsHeader()
{
    QList<forma_l*> *flist = m_edit_menu->m_font->get_m_forma_l_list();

    if ( flist->size() == 0 )
        formsInsertPast();

    DialogFormsHeader diaformsHeader;

    diaformsHeader.set_m_mainform ( this );

    diaformsHeader.exec();

    reDrawCurrentFormInFoma_l();
}

void Main_Form::formsFormaEdit()
{
    m_edit_menu->s_menu_font_forms->hide();
    m_edit_menu->s_menu_form->show();										//Показать меню
}

void Main_Form::formsPrev()
{
    --m_current_forma_l;
    check_and_validate_m_current_forma_l();
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formsNext()
{
    ++m_current_forma_l;
    check_and_validate_m_current_forma_l();
    reDrawCurrentFormInFoma_l();
}

/**
Редактирование списка форм.
Выполняет переход к первой форме в шрифте.
*/
void Main_Form::formsHome()
{
    m_current_forma_l = 0;
    check_and_validate_m_current_forma_l();//Вообще-то можно и убрать.
    reDrawCurrentFormInFoma_l();
}

void Main_Form::setTitle ( void )
{
    QList<forma_l*> *flist = m_edit_menu->m_font->get_m_forma_l_list();

    QString Title;
    Title =
        QString::fromUtf8 ( "forms " ) +
        QString::fromUtf8 ( "=> form[" ) +
        QString::number ( m_current_forma_l ) +
        QString::fromUtf8 ( "]:" )
        ;

    if ( is_m_current_forma_l_valid() )
    {
        Title += QString ( " Number = " );
        Title += QString::number ( flist->at ( m_current_forma_l )->get_number() );
        Title += QString ( " ;" );
        Title += QString ( " Comment = " );
        Title += flist->at ( m_current_forma_l )->get_attribute();
    }

    setWindowTitle ( Title );
}

bool Main_Form::is_m_current_forma_l_valid ( void ) const
{
    QList<forma_l*> *flist = m_edit_menu->m_font->get_m_forma_l_list();

    if ( 0 <= m_current_forma_l && m_current_forma_l < flist->size() )
        return true;

    return false;
}

bool Main_Form::is_m_current_shape_valid ( void ) const
{
    QList<shapes*> * shapesList = get_p_shapeList();

    if ( shapesList && 0 <= m_current_shape && m_current_shape < shapesList->size() )
        return true;

    return false;
}

/**
Редактирование списка форм.
Выполняет переход к последней форме в шрифте.
*/
void Main_Form::formsEnd()
{
    m_current_forma_l = m_edit_menu->m_font->get_m_forma_l_list()->size() - 1;
    check_and_validate_m_current_forma_l();
    reDrawCurrentFormInFoma_l();
}

void Main_Form::reDrawCurrentFormInFoma_l ( void )
{
    QList<forma_l*> *flist = m_edit_menu->m_font->get_m_forma_l_list();

    graphicsView->scene()->clear();

    if ( is_m_current_forma_l_valid() )
    {
        dr.set_initial();
        dr.draw(*graphicsView->scene());
        stack st;
        flist->at ( m_current_forma_l )->draw ( dr, st, *graphicsView->scene() );
        graphicsView->invalidateScene ();
        setTitle();
    }
}

void Main_Form::check_and_validate_m_current_forma_l ( void )
{
    QList<forma_l*> * flist = m_edit_menu->m_font->get_m_forma_l_list();
    int Size = flist->size();

    if ( Size <= 0 || m_current_forma_l <= 0 )
        m_current_forma_l = 0;
    else if ( m_current_forma_l >= Size )
        m_current_forma_l = Size - 1;
}

void Main_Form::check_and_validate_m_current_shape ( void )
{
    QList<shapes*> * shapesList = get_p_shapeList();

    if ( !shapesList )
    {
        m_current_shape = 0;
        return;
    }

    int Size = shapesList->size();

    if ( Size <= 0 || m_current_shape <= 0 )
        m_current_shape = 0;
    else if ( m_current_shape >= Size )
        m_current_shape = Size - 1;
}

/**
Редактирование списка форм.
Выполняет поиск формы по номеру или комментарию.
*/
void Main_Form::formsFind()
{
    DialogFormsFind diaFind;
    diaFind.set_m_mainform ( this );
    diaFind.exec();
    reDrawCurrentFormInFoma_l();
}

/**
Редактирование списка форм.
Вставляет в шрифт новую форму после текущей формы.
После вставки формы текущей формой становится вставленная вновь форма.
*/
void Main_Form::formsInsertPast()
{
    QList<forma_l*> *flist = m_edit_menu->m_font->get_m_forma_l_list();

    forma_l *a_forma_l = new forma_l;

    int index;

    if ( flist->size() == 0 )
        index = 0;
    else
        index = get_m_current_forma_l() + 1;

    flist->insert ( index, a_forma_l );

    index = flist->indexOf ( a_forma_l );

    set_m_current_forma_l ( index );

    reDrawCurrentFormInFoma_l();
}

/**
Редактирование списка форм.
Вставляет в шрифт новую форму перед текущей формы.
После вставки формы текущей формой становится вставленная вновь форма.
*/
void Main_Form::formsInsertBefor()
{
    QList<forma_l*> *flist = m_edit_menu->m_font->get_m_forma_l_list();

    forma_l *a_forma_l = new forma_l;

    int index;

    if ( flist->size() == 0 )
        index = 0;
    else
        index = get_m_current_forma_l();

    flist->insert ( index, a_forma_l );

    index = flist->indexOf ( a_forma_l );

    set_m_current_forma_l ( index );

    reDrawCurrentFormInFoma_l();
}

/**
Редактирование списка форм.
Удаляет текущую форму и устанавливает в текущую позицию форму, следующую за удаляемой
(если таковая имеется).
*/
void Main_Form::formsDelete()
{
    QList<forma_l*> *flist = m_edit_menu->m_font->get_m_forma_l_list();

    if ( flist->size() == 0 )
        return;

    int index = get_m_current_forma_l();

    flist->removeAt ( index );

    check_and_validate_m_current_forma_l();
    reDrawCurrentFormInFoma_l();
}

/**
Редактирование списка форм.
Удаление текущей формы и установка в текущую позицию форму, предыдущую удаляемой
(если таковая имеется).
*/
void Main_Form::formsBackspace()
{
    QList<forma_l*> *flist = m_edit_menu->m_font->get_m_forma_l_list();

    if ( flist->size() == 0 )
        return;

    int index = get_m_current_forma_l();

    flist->removeAt ( index );

    --m_current_forma_l;

    check_and_validate_m_current_forma_l();
    reDrawCurrentFormInFoma_l();
}

/**
Редактирование списка форм. Выход.
*/
void Main_Form::formsExit()
{
    m_edit_menu->s_menu_font_main->show();										//Показать меню
    m_edit_menu->s_menu_font_forms->hide();
}

/**************************************************************************************/

void Main_Form::formaEdit()
{
    shapes* sh = get_p_current_shape();
    sh->edit();
}

void Main_Form::formaDrawVars()
{
    exec_Draw_Vars_Dialog();
}

void Main_Form::formaPrev()
{
    --m_current_shape;
    check_and_validate_m_current_shape();
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaNext()
{
    ++m_current_shape;
    check_and_validate_m_current_shape();
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaHome()
{
    m_current_shape = 0;
    check_and_validate_m_current_shape();
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaEnd()
{
    QList<shapes*> *shapesList = get_p_shapeList();

    if ( shapesList )
        m_current_shape = shapesList->size() - 1;
    else
        m_current_shape = 0;

    check_and_validate_m_current_shape();
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaInsert_Past()
{
    check_and_validate_m_current_shape();
    ++m_current_shape;

    m_edit_menu->s_menu_form->hide();
    m_edit_menu->s_menu_form_insert_shapes->show();	//Показать меню
}

void Main_Form::formaInsert_Before()
{
    check_and_validate_m_current_shape();
    m_edit_menu->s_menu_form->hide();
    m_edit_menu->s_menu_form_insert_shapes->show();	//Показать меню
    /**/
}

void Main_Form::formaDelete()
{
    QList<shapes*> * shapesList = get_p_shapeList();

    if ( shapesList->size() == 0 )
        return;

    int index = m_current_shape;

    shapesList->removeAt ( index );

    check_and_validate_m_current_shape();
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaBackspace()
{
    QList<shapes*> * shapesList = get_p_shapeList();

    if ( shapesList->size() == 0 )
        return;

    int index = --m_current_shape;

    if ( index >= 0 )
        shapesList->removeAt ( index );

    check_and_validate_m_current_shape();
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaExit()
{
    m_edit_menu->s_menu_form->hide();
    m_edit_menu->s_menu_font_forms->show();										//Показать меню
}

/**************************************************************************************/


void Main_Form::formaInsertLine()
{
    QList<shapes*>*	shapeList = get_p_shapeList();
    shapes * sh = new shape_;
    shapeList->insert ( m_current_shape, sh );

    m_edit_menu->s_menu_form_insert_shapes->hide();
    m_edit_menu->s_menu_form->show();										//Показать меню
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaInsertPen()
{
    QList<shapes*>*	shapeList = get_p_shapeList();
    shapes * sh = new shape_12;
    shapeList->insert ( m_current_shape, sh );

    m_edit_menu->s_menu_form_insert_shapes->hide();
    m_edit_menu->s_menu_form->show();										//Показать меню
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaInsertScale()
{
    QList<shapes*>*	shapeList = get_p_shapeList();
    shapes * sh = new shape_34;
    shapeList->insert ( m_current_shape, sh );

    m_edit_menu->s_menu_form_insert_shapes->hide();
    m_edit_menu->s_menu_form->show();										//Показать меню
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaInsertStack()
{
    QList<shapes*>*	shapeList = get_p_shapeList();
    shapes * sh = new shape_56;
    shapeList->insert ( m_current_shape, sh );

    m_edit_menu->s_menu_form_insert_shapes->hide();
    m_edit_menu->s_menu_form->show();										//Показать меню
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaInsertReference()
{
    QList<shapes*>*	shapeList = get_p_shapeList();
    shapes * sh = new shape_7;
    shapeList->insert ( m_current_shape, sh );

    m_edit_menu->s_menu_form_insert_shapes->hide();
    m_edit_menu->s_menu_form->show();										//Показать меню
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaInsertLine89()
{
    QList<shapes*>*	shapeList = get_p_shapeList();
    shapes * sh = new shape_89;
    shapeList->insert ( m_current_shape, sh );

    m_edit_menu->s_menu_form_insert_shapes->hide();
    m_edit_menu->s_menu_form->show();										//Показать меню
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaInsertOctantArc()
{
    QList<shapes*>*	shapeList = get_p_shapeList();
    shapes * sh = new shape_a;
    shapeList->insert ( m_current_shape, sh );

    m_edit_menu->s_menu_form_insert_shapes->hide();
    m_edit_menu->s_menu_form->show();										//Показать меню
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaInsertDigitArc()
{
    QList<shapes*>*	shapeList = get_p_shapeList();
    shapes * sh = new shape_b;
    shapeList->insert ( m_current_shape, sh );

    m_edit_menu->s_menu_form_insert_shapes->hide();
    m_edit_menu->s_menu_form->show();										//Показать меню
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaInsertCurveLineCD()
{
    QList<shapes*>*	shapeList = get_p_shapeList();
    shapes * sh = new shape_cd;
    shapeList->insert ( m_current_shape, sh );

    m_edit_menu->s_menu_form_insert_shapes->hide();
    m_edit_menu->s_menu_form->show();										//Показать меню
    reDrawCurrentFormInFoma_l();
}

void Main_Form::formaInsertVertical()
{
    QList<shapes*>*	shapeList = get_p_shapeList();
    shapes * sh = new shape_e;
    shapeList->insert ( m_current_shape, sh );

    m_edit_menu->s_menu_form_insert_shapes->hide();
    m_edit_menu->s_menu_form->show();										//Показать меню
    reDrawCurrentFormInFoma_l();
}

void Main_Form::wheelEvent ( QWheelEvent *e )
{
    int rez;
    int ev_buttons ;
    int ev_delta;
    qreal scale_factor;
    QPoint ev_globalPos;
    QPoint ev_pos;

    ev_buttons = e->buttons ();
    rez = ev_buttons;

    ev_delta = e->delta ();
    scale_factor = qreal ( ev_delta ) / qreal ( 600 );
    rez = ev_delta;

    ev_globalPos = e->globalPos ();

    ev_pos = e-> pos ();

    if ( ev_delta > 0 )
    {
        QTransform transform
        ( 1. + scale_factor, 0, 0,
          0, 1. + scale_factor, 0,
          0, 0, 1
        );
        this->graphicsView->setTransform ( transform, true );

    }

    if ( ev_delta < 0 )
    {
        QTransform transform
        ( 1. / 1. + scale_factor, 0, 0,
          0, 1. / 1. + scale_factor, 0,
          0, 0, 1
        );
        this->graphicsView->setTransform ( transform, true );
    }
}


int Main_Form::get_m_current_forma_l ( void )
{
    return m_current_forma_l;
}

/**Возвращает указатель на список форм, составляющих символ.
*/
QList<shapes*>*	Main_Form::get_p_shapeList ( void ) const
{
    QList<shapes*>* rez = 0;
    forma_l * aForma_l = get_p_current_forma_l();

    if ( aForma_l )
    {
        forma * aForma = aForma_l->get_m_forma();
        rez = aForma->get_m_shapes();
    }

    return rez;
}

forma_l* Main_Form::get_p_current_forma_l ( void ) const
{
    forma_l* rez = 0;
    QList<forma_l*> *flist = m_edit_menu->m_font->get_m_forma_l_list();

    if ( is_m_current_forma_l_valid() )
        rez = ( *flist ) [ m_current_forma_l];

    return rez;
}

void Main_Form::set_m_current_forma_l ( int newVal )
{
    m_current_forma_l = newVal;
    check_and_validate_m_current_forma_l(); //Проверить правильность.
}

shapes*	Main_Form::get_p_current_shape()
{
    QList<shapes*>* shapesList = get_p_shapeList();
    check_and_validate_m_current_shape();
    shapes* sh = 0;
    if ( shapesList && shapesList->size() > 0 )
        sh = ( *shapesList ) [m_current_shape];
    return sh;
}

/**Действие функции Main_Form::reDrawSlot(void) сводится к вызову функции Main_Form::reDrawCurrentFormInFoma_l().*/
void Main_Form::reDrawSlot ( void )
{
    reDrawCurrentFormInFoma_l();
}

void Main_Form::exec_Draw_Vars_Dialog(void)
{
  DialogDrawVars  *a = new DialogDrawVars ;
  a->exec();
  reDrawCurrentFormInFoma_l();
}
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
