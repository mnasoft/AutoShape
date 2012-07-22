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

#include "forma_l.h"
#include "menu.h"

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

extern QTextStream std_out;
extern QTextStream std_in;

long  forma_l::s_forma_l_count = 0;

void forma_l::menu_init ( void )
{
}

void forma_l::menu_delete ( void )
{
}

void forma_l::set_Initial()
{
    m_comment = QString ( "Nothing" );
    m_number = -1;
    m_changed = 0;
//	m_forma->set_parent ( this );
}

/**
Конструктор.
*/
forma_l::forma_l ( void ) :
        m_forma ( 0 ),
        m_parent ( 0 )
{
    ++s_forma_l_count;
    menu_init();

    m_forma = new forma;
    set_Initial();
}

/**
Конструктор копирования.
*/
forma_l::forma_l ( forma_l  const  & new_forma_l ) :
        m_forma ( 0 ),
        m_parent ( 0 )
{
    ++s_forma_l_count;
    menu_init();
    set_Initial();

    m_comment = new_forma_l.m_comment;
    m_number = new_forma_l.m_number;
    m_changed = new_forma_l.m_changed;

    m_forma = new forma;
    QList<int> Bites = new_forma_l.get_List_bites();
    load_List_bites ( Bites );
}

forma_l & forma_l::operator= ( forma_l const  & new_forma_l )
{
    set_Initial();
    m_comment = new_forma_l.m_comment;
    m_number = new_forma_l.m_number;
    m_changed = new_forma_l.m_changed;

// m_parent = new_forma_l.m_parent;

    QList<int> Bites = new_forma_l.get_List_bites();
    load_List_bites ( Bites );
    return *this;
}

forma_l::~forma_l ( void )
{
    --s_forma_l_count;

    delete m_forma;

    menu_delete();
}

/**
Вычисляет и возвращает количество байтов в символе.
*/
int forma_l::get_num_bites ( void )
{
    int rez ;
    rez = m_forma->get_lenth ( );

    return rez;
}

int forma_l::is_changed ( void )
//Возвращает 0, еcли форма не изменялать.
{
    return m_changed;
}


void forma_l::load_List_bites ( const QList<int> & m_bites )
{
    int i = 0;
    shapes* shs;
    shape_89 * sh_89;
    shape_cd * sh_cd;
    int dx;
    int dy;
    int dxy_c;

    QList<shapes*> * sh_lst = m_forma->get_m_shapes();

    clear_m_forma(); //Очистка содержимого байтов формы

    bool while_do;

    while ( i < m_bites.size() )
    {
        switch ( m_bites[i] )
        {

        case 0: // 000 End of shape definition
            std_out << "case 0" << endl;
            break;

        case 1: // 001 Activate Draw mode (pen down)
            std_out << "case 1" << endl;
            shs = new shape_12 ( true );
            sh_lst->append ( shs );
            shs->set_parent ( m_forma );
            break;

        case 2: // 002 Deactivate Draw mode (pen up)
            std_out << "case 2" << endl;
            shs = new shape_12 ( false );
            sh_lst->append ( shs );
            shs->set_parent ( m_forma );
            break;

        case 3: // 003 Divide vector lengths by next byte
            std_out << "case 3" << endl;
            shs = new shape_34 ( false, m_bites[++i] );
            sh_lst->append ( shs );
            shs->set_parent ( m_forma );
            break;

        case 4: // 004 Multiply vector lengths by next byte
            std_out << "case 4" << endl;
            shs = new shape_34 ( true, m_bites[++i] );
            sh_lst->append ( shs );
            shs->set_parent ( m_forma );
            break;

        case 5: // 005 Push current location onto stack
            std_out << "case 5" << endl;
            shs = new shape_56 ( true );
            sh_lst->append ( shs );
            shs->set_parent ( m_forma );
            break;

        case 6: // 006 Pop current location from stack
            std_out << "case 6" << endl;
            shs = new shape_56 ( false );
            sh_lst->append ( shs );
            shs->set_parent ( m_forma );
            break;

        case 7: // 007 Draw subshape number given by next byte
            std_out << "case 7" << endl;
            shs = new shape_7 ( m_bites[++i] );
            sh_lst->append ( shs );
            shs->set_parent ( m_forma );
            break;

        case 8: // 008 X-Y displacement given by next two bytes
            std_out << "case 8" << endl;
            shs = new shape_89;
            sh_lst->append ( shs );
            sh_89 = dynamic_cast <shape_89 *> ( shs ) ;
            sh_89->set_x ( 0, m_bites[++i] );
            sh_89->set_y ( 0, m_bites[++i] );
            shs->set_parent ( m_forma );
            break;

        case 9: // 009 Multiple X-Y displacements, terminated (0,0)
            std_out << "case 9" << endl;
            shs = new shape_89;
            sh_lst->append ( shs );
            sh_89 = dynamic_cast <shape_89 *> ( shs ) ;
            sh_89->set_x ( 0, m_bites[++i] );
            sh_89->set_y ( 0, m_bites[++i] );

            do
            {
                dx = m_bites[++i];
                dy = m_bites[++i];

                if ( dx == 0 & dy == 0 )
                    while_do = false;
                else
                {
                    while_do = true;
                    sh_89->append ( dx, dy );
                }
            }
            while ( while_do );

            shs->set_parent ( m_forma );

            break;

        case 10:// 00A Octant arc defined by next two bytes
            std_out << "case 10" << endl;

            shs = new shape_a ( m_bites[++i], m_bites[++i] ) ;

            sh_lst->append ( shs );

            shs->set_parent ( m_forma );

            break;

        case 11:// 00B Fractional arc defined by next five bytes
            std_out << "case 11" << endl;

            shs = new shape_b ( m_bites[++i], m_bites[++i], m_bites[++i], m_bites[++i], m_bites[++i] ) ;

            sh_lst->append ( shs );

            shs->set_parent ( m_forma );

            break;

        case 12:// 00C Arc defined by X-Y displacement and bulge
            std_out << "case 12" << endl;

            shs = new shape_cd;

            sh_lst->append ( shs );

            sh_cd = dynamic_cast <shape_cd *> ( shs ) ;

            sh_cd->set_x ( 0, m_bites[++i] );

            sh_cd->set_y ( 0, m_bites[++i] );

            sh_cd->set_c ( 0, m_bites[++i] );

            shs->set_parent ( m_forma );

            break;

        case 13:// 00D Multiple bulge-specified arcs
            std_out << "case 13" << endl;

            shs = new shape_cd;

            sh_lst->append ( shs );

            sh_cd = dynamic_cast <shape_cd *> ( shs ) ;

            sh_cd->set_x ( 0, m_bites[++i] );

            sh_cd->set_y ( 0, m_bites[++i] );

            sh_cd->set_c ( 0, m_bites[++i] );

            do
            {
                dx = m_bites[++i];
                dy = m_bites[++i];

                if ( dx == 0 & dy == 0 )
                    while_do = false;
                else
                {
                    while_do = true;
                    dxy_c = m_bites[++i];
                    sh_cd->append ( dx, dy, dxy_c );
                }
            }

            while ( while_do );

            shs->set_parent ( m_forma );

            break;

        case 14:// 00E Process next command only if vertical text
            std_out << "case 14" << endl;

            shs = new shape_e ;

            sh_lst->append ( shs );

            shs->set_parent ( m_forma );

            break;

        case 15: // 002 Deactivate Draw mode (pen up)
            std_out << "case 15" << endl;

        default :
            shs = new shape_ ( m_bites[i] ) ;

            sh_lst->append ( shs );

            shs->set_parent ( m_forma );

            break;
        } //switch ( m_bites[i] )

        ++i;
    }  //while ( i < m_bites.size() )

}

/**
Возврвщает байтовое представление формы.
*/
QList<int>	forma_l::get_List_bites ( void ) const
{
    QList<int> rez;
    QList<shapes*> * shList = m_forma->get_m_shapes();

    for ( int i = 0;i < shList->size();++i )
    {
        rez << shList->at ( i )->get_m_bites();
    }

    rez << 0;

    return rez;
}


/**
Выводит содержимое формы в стринг в символьном представлении.
*/
QString forma_l::out ( void )
{
    QString rez = out_header();
    rez += QString ( "\n" );
    rez += out_shapes();
    return rez;
}

QString forma_l::out_header ( void )
{
    QString rez;
    rez = QString ( "*" );
    rez += QString::number ( get_number() );
    rez += QString ( "," );
    rez += QString::number ( get_num_bites() );
    rez += QString ( "," );
    rez += get_attribute();
    return rez;
}

QString forma_l::out_shapes ( void )
{
    QString rez;
    rez = m_forma->out();
    rez = devide_string ( rez, QChar ( ',' ), 70 );
    return rez;
}

int forma_l::in ( char* )
//Производит заполнение стринга строкой символов для данной формы
{
    return 0;
}

/*
void forma_l::out_file(font* fon,FILE*write)
//Печатать байты.
{
 d_link *a=this;
 FILE * du1=fon->get_dub1();
 a->rewind_to_head(a);
 while(a->get_succ(a))
 {
  if(a->get(a))
  {}
  else
  {
   ( (forma_l*) a)->load(du1);
  }
  fprintf(write,"  0\nSTART\n");
  fprintf(write,"  6\nHEADER\n");
  fprintf(write,"  2\n%d\n",((forma_l*)a)->get_number());
  fprintf(write,"  5\n%d\n",((forma_l*)a)->get_num_bites());
  fprintf(write," 10\n%s\n",((forma_l*)a)->get_attribute());
  fprintf(write,"  6\nEND_HEADER\n");
  fprintf(write,"  6\nRECORD");
  ( (forma*) (a->get(a) ))->out_file(write);
  fprintf(write,"\n  8\nshape_0");
  fprintf(write,"\n  8\nend_shape_0");
  fprintf(write,"\n  6\nEND_RECORD\n");
  fprintf(write,"  0\nEND\n");

  ( (forma_l*) a)->clear_somthing(a);
  a->stap_to_tail(a);
 }
 if(a->get(a))
 {}
 else
 {
  ( (forma_l*) a)->load(du1);
 }
 fprintf(write,"  0\nSTART\n");
 fprintf(write,"  6\nHEADER\n");
 fprintf(write,"  2\n%d\n",((forma_l*)a)->get_number());
 fprintf(write,"  5\n%d\n",((forma_l*)a)->get_num_bites());
 fprintf(write," 10\n%s\n",((forma_l*)a)->get_attribute());
 fprintf(write,"  6\nEND_HEADER\n");
 fprintf(write,"  6\nRECORD");
 ( (forma*) (a->get(a) ))->out_file(write);
 fprintf(write,"\n  8\nshape_0");
 fprintf(write,"\n  8\nend_shape_0");
 fprintf(write,"\n  6\nEND_RECORD\n");
 fprintf(write,"  0\nEND\n");
 fprintf(write,"  0\nEOF\n");
 ( (forma_l*) a)->clear_somthing(a);
}
*/

//long forma_l::get_file_position ( void )
//Получить адать смещение с которого начинаются байты формы, записанные в du1.
// {
//  return m_file_position;
// }



/*
void forma_l::clear_somthing(d_link * &a)
//Удалить элемент.
{
 d_link* that;
 that=(d_link*)a->get(a);
 if(that)
 {
  that->clear_all(that);
  a->define(NULL,a);
 }
}
*/

/*
d_link* forma_l::create(d_link * &)
//Выделить память под элемент списка.
{
 return new forma_l;
}
*/

int forma_l::find ( int nom )
{
    /*
     d_link * grend=this;
     a=this;
     a->rewind_to_head(a);
     do
     {
      int no=((forma_l*)a)->get_number();
      if( nom == no)return no;
      a->stap_to_tail(a);
     }while(a->get_succ(a));
     int no=((forma_l*)a)->get_number();
     if( nom == no)return nom;
     a=grend;
     return 0;
    */
    return 0;
}

void forma_l::edit_header ( void )
{
    int rez  = 0;
    QString  str;
    int   rez_number;
    ushort  rez_ushort;
    bool   ok;

    do
    {
        print_bites ( std_out );
//  s_menu_font_forms->run();
//  rez = s_menu_font_forms->get_run_rez();


        switch ( rez )
        {

        case 0: //Number
            std_out << "Enter Number:";
            std_out.flush();

            std_in >> str;
            rez_number = str.toInt ( &ok );

            if ( ok )
                m_number = rez_number;

            break;

        case 1: //ASCII
            std_out << "ASCII:";

            std_out.flush();

            std_in >> str;

            if ( str.length() >=  1 )
            {
                rez_ushort = str[0].unicode () ;
                m_number = rez_ushort;
            }

            break;

        case 2: //Attribute
            std_out << "Enter Attribute:";

            std_out.flush();

            std_in >> str;

            m_comment = str;

            break;

        case 3: //Restore
            m_comment = QString ( "Nothing" );
            m_number = -1;
            break;

        default :
            break;
        }

        std_out << rez << endl;
    }

    while ( rez != -1 );
}

void forma_l::edit_record ( draw_vars &dr, stack &st )
//Редактировать байты.
{
    /*
     d_link *for_l=this;
     d_link *form_;
     FILE *du1=((font*)fon)->get_dub1();
     if(for_l->get(for_l))
     {
      form_=(d_link*)for_l->get(for_l);
      ((forma*)form_)->edit(form_,dr,st,fon);
     }
     else
     {
      ((forma_l*)for_l)->load(du1);
      form_=(d_link*)for_l->get(for_l);
      ((forma*)form_)->edit(form_,dr,st,fon);
     }
     if(form_)
     {
      int len=((forma*)form_)->get_lenth();
      ((forma_l*)for_l)->set_num_bites(len);
     }
     for_l->define(form_,for_l);
    */
}

void forma_l::print ( void )
//Печатать номер и заголовок.
{
    print_bites ( std_out );
}

void forma_l::draw ( draw_vars &dr, stack &st, QGraphicsScene & sc )
//Рисовать.
{
    forma * a = get_m_forma();
    QList<shapes*> * sh_list = a->get_m_shapes();

    dr.set_drawWhisOutPenUpMovement(!draw_vars::s_drawAll);

    if (dr.drawWhisOutPenUpMovement() && !dr.get_pero())
        return;

    for ( int i = 0;i < sh_list->size(); ++i )
    {
        sh_list->at ( i )->draw ( dr, st, sc);
    }
}

void forma_l::print_bites ( QTextStream & stream )
{
    stream << "attribute     = " << m_comment   << endl;
    stream << "number        = " << m_number    << endl;
    stream << "changed       = " << m_changed    << endl;

    stream << QString::fromUtf8 ( "Байты формы:" ) << endl;

    QList<int> Bites = get_List_bites();

    for ( int i = 0; i < Bites.size(); ++i )
    {
        int tmp = Bites.at ( i );
        stream << tmp << " ";
    }

    stream << endl;
}

void forma_l::print_shapes ( QTextStream & stream )
{
//Вывод заголовка формы.
    stream << out() << QString ( "\n" );
}


int forma_l::read_int_byte ( const QString& str )
{
    //1 - исключить символы скобок
    QString rez_str;
    int rez = 0;

    for ( int i = 0; i < str.size(); ++i )
    {
        if ( str.at ( i ) == QChar ( '(' ) || str.at ( i ) == QChar ( ')' ) )
            ;
        else
            rez_str += str.at ( i );
    }

    //2 - если первый символ "0" - читать шестнадцатеричное, иначе десятичное.
    bool ok;

    if ( rez_str.at ( 0 ) == QChar ( '0' ) )
        rez = rez_str.toInt ( &ok, 16 );
    else if ( rez_str.size() >= 2 && rez_str.at ( 0 ) == QChar ( '-' ) && rez_str.at ( 1 ) == QChar ( '0' ) )
    {
        rez = rez_str.toInt ( &ok, 16 );
    }
    else
        rez = rez_str.toInt ( &ok, 10 );

    return rez;
}


QString forma_l::get_attribute ( void ) const
{
    return m_comment;
}


void forma_l::set_attribute ( const QString & new_attribute )
{
    m_comment = new_attribute;
}

/**
Возвращает номер формы.
*/
int forma_l::get_number ( void ) const
{
    return m_number;
}


void forma_l::set_number ( int new_number )
{
    m_number = new_number;
}


void  forma_l::set_parent ( font* new_parent )
{
    m_parent = new_parent;
}

font* forma_l::get_parent ( void ) const
{
    return m_parent;
}


forma * forma_l::get_m_forma()
{
    return m_forma;
}

void forma_l::clear_m_forma()
{
    m_forma->clear_m_shapes();
}
// kate: indent-mode cstyle; space-indent on; indent-width 0; 
