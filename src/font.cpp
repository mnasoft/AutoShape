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

#include "font.h"

#include <QFileDialog>

extern QTextStream std_out;
extern QTextStream std_in;

long font::s_font_main_count = 0;

font::font ( void ) :
		m_forma_l_list ( 0 )
{
	m_comment	= QString("");
	m_forma_l_list = new QList<forma_l *>;

	set_above ( 10 );
	set_below ( 5 );
	set_modes ( 2 );

	++s_font_main_count;
}

font::~font ( void )
{
	m_forma_l_list->clear();
	--s_font_main_count;
}

/**
Загрузить список форм.
*/
//todo Доработать определение данной функции для Большого-шрифта и Unicode-шрифта
void font::font_load ( void )
{
	QString str;													//Буфер чтения строк из файла.
	QStringList str_lst;									//Подстроки элементов шрифта.
	bool zv_was_red = false; 							//Символ "*" был прочтен.
	int Number = -1;											//Номер, счтиываемой формы шрифта.
	int numBites = -1;										//Количество байт в форме шрифта, участия в вычислениях не принимает. Введено для справки.
	QString Attribute;										//Комментарий формы.
	QList<int> Bites;											//Буфер байтов формы.

	m_forma_l_list->clear();							//Очищаем шрифт от содержащихся в нем форм.

	if ( !m_file.exists() )								//Проверка сущетсвования файла.
	{
		std_out << QString::fromUtf8 ( "Файл не существует: " ) << m_file.fileName() << endl;
		return;
	}

	if ( !m_file.open ( QIODevice::ReadOnly | QIODevice::Text ) ) //Попытка открытия файла.
		//QIODevice::ReadWrite | QIODevice::Text
	{
		std_out << QString::fromUtf8 ( "Не удалось открыть файл: " ) << m_file.fileName() << endl;
		return;
	}

	m_stream.setDevice ( &m_file );

	while ( !m_stream.atEnd() )
	{
		str = m_stream.readLine ();																	//Считываем строку из файла.

		if ( str[0] == QChar ( '*' ) )
		{
			if ( zv_was_red ) //Добавление в конец списка уже прочитанной формы. Для форм с первой по предпоследнюю.
			{
				if ( Number != 0 )
				{
					//Добавление формы к шрифту.
					forma_l * shape = 0;							//Указатель на форму для добавления к формы к шрифту.
					shape = new forma_l;
					shape->set_number ( Number );
					shape->set_attribute ( Attribute );
					shape->load_List_bites ( Bites );
					m_forma_l_list->push_back ( shape );
				}
				else	//Запись заголовка шрифта.
				{
					m_above = Bites.at ( 0 );
					m_below = Bites.at ( 1 );
					m_modes = Bites.at ( 2 );
					m_comment = Attribute;
				}

				Bites.clear();			//Не удалять.

				//Сброс буферов (для отладки, после отладки можно удалить).
				Number = -1;
				Attribute = QString();
				str_lst.clear();
				numBites = -1;
			}

			//Разбор и сохранение в буферах заголовка формы.
			zv_was_red = true;

			QString str_0, str_1, str_2;

			str_0 = str.section ( QChar ( ',' ), 0, 0 );

			str_1 = str.section ( QChar ( ',' ), 1, 1 );

			str_2 = str.section ( QChar ( ',' ), 2 );

			str_0 = str_0.section ( QChar ( '*' ), 1, 1 ); //Исключение первой звёздочки

			if ( str_0 == QString ( "Diameter_Symbol" ) )
				Number = -1000 ;
			else if ( str_0 == QString ( "Degree_Sign" ) )
				Number = -1001 ;
			else if ( str_0 == QString ( "Plus_Or_Minus_Sign" ) )
				Number = -1002 ;
			else if ( str_0 == QString ( "UNIFONT" ) )
				Number = -1003 ;
			else
				Number = forma_l::read_int_byte ( str_0 ) ;

			Attribute = str_2 ;
		}

		else if ( str.length() == 0 || str[0] == QChar ( ';' ) || str[0] == QChar ( ' ' ) )
		{
			;
		}

		else
		{
			str_lst = str.split ( QChar ( ',' ), QString::SkipEmptyParts );

			for ( int i = 0; i < str_lst.size(); ++i )
			{
				int Bite = forma_l::read_int_byte ( str_lst.at ( i ) );
				Bites.insert ( Bites.end(), Bite );
//				std_out << str_lst.at ( i ) << endl;
			}
		}
	}

	if ( zv_was_red ) //Добавление в конец списка уже прочитанной формы. Для последней формы.
	{
		if ( Number != 0 )
		{
			//Добавление формы к шрифту.
			forma_l * shape = 0;							//Указатель на форму для добавления к формы к шрифту.
			shape = new forma_l;
			shape->set_number ( Number );
			shape->set_attribute ( Attribute );
			shape->load_List_bites ( Bites );
			m_forma_l_list->push_back ( shape );
		}
		else	//Запись заголовка шрифта.
		{
			m_above = Bites.at ( 0 );
			m_below = Bites.at ( 1 );
			m_modes = Bites.at ( 2 );
		}
	}

	m_file.close();
}


/*void font::forma_du1_to_du2 ( void )
{
  d_link *a = this;

  if ( ! open )
  {
   return;
  }

  if ( ( dublicat_2 = fopen ( str_dubl_2, "wt" ) ) == NULL )
  {
   exit ( 2 );
  }

  d_link *b = ( d_link* ) a->get ( a );

  if ( b )
  {
   ( ( forma_l * ) b )->out_file ( ( font* ) a, dublicat_2 );
  }

  else
  {
   return;
  }

 // ((forma_l*)get(a);
  fclose ( dublicat_2 );
}
*/

/*
void font::du2_to_du1 ( void )
//Удалить du1 и переименовать du2 в du1.
{
  if ( ! open )
  {
   return;
  }

  if ( access ( str_dubl_2, 0 ) == 0 )
  {
   fclose ( dublicat_1 );
   unlink ( str_dubl_1 );
   rename ( str_dubl_2, str_dubl_1 );

   if ( ( dublicat_1 = fopen ( str_dubl_1, "r" ) ) == NULL ) exit ( 1 );
  }
}
*/

void font::font_forms ( draw_vars &dr, stack &st )
//Редактировать формы шрифта.
{
	/*
	 qreal sum;
	 a = this;

	 if ( ! open )
	 {
	  return;
	 }

	 char ch;

	 int m;

	 if ( ! open )
	 {
	  return;
	 }

	 draw_vars &dr_const = dr;

	 d_link *formoch;
	 formoch = ( d_link* ) a->get ( a );
	 set_viewport ( zoom_scr );

	 do
	 {
	  char stroka[30];
	  set_viewport ( mes_scr );
	  unsigned long memo = 0;

	  if ( !formoch )
	  {
	   formoch = new forma_l;
	   ( ( forma_l* ) formoch )->edit_header();
	  }

	  set_viewport ( zoom_scr );

	  clearviewport();
	  a->define ( formoch, a );
	  ( ( forma_l* ) formoch )->print();//Печатать заголовок формы.
	  dr = dr_const;
	  dr.set_coords ( 0., 0. );
	  dr.draw();
	  ( ( forma_l* ) formoch )->draw ( a, dr, st );//Рисовать.
	  dr.print();
	  dr.set_coords ( 0., 0. );
	  set_viewport ( mes_scr );
	  memo = farcoreleft();
	  sprintf ( stroka, "MEM=%10.0f", qreal ( memo ) );
	  string_to_display ( stroka, 0, 40 );
	  forms.show();
	  m_on();
	  ch = forms.run();
	  m_off();
	  forms.hide();

	  switch ( ch )
	  {

	   case 6:
	   {
	    formoch->rewind_to_head ( formoch );
	   }

	   break;

	   case 4:
	    formoch->stap_to_head ( formoch );
	    break;

	   case 5:
	    formoch->stap_to_tail ( formoch );
	    break;

	   case 14:
	    shuar.show();
	    m_on();

	    if ( shuar.run() == 2 ) formoch->backspace ( formoch );

	    m_off();

	    shuar.hide();

	    break;

	   case 13:
	    shuar.show();

	    m_on();

	    if ( shuar.run() == 2 ) formoch->del ( formoch );

	    m_off();

	    shuar.hide();

	    break;

	   case 7:
	   {
	    formoch->rewind_to_tail ( formoch );
	   }

	   break;

	   case 1:
	    ( ( forma_l* ) formoch )->edit_header();//Редактировать заголовок.
	    break;

	   case 2:
	    ( ( forma_l* ) formoch )->edit_record ( a, dr, st );//Редактировать байты.
	    break;

	   case 8:
	   {
	    int m = ( ( forma_l* ) formoch )->get_octant_number();
	    char stroka[81];
	    char chus;
	    stroka[0] = 0;

	    do
	    {
	     set_viewport ( zoom_scr );
	     clearviewport();
	     ascii.show();
	     m_on();
	     chus = ascii.run();
	     m_off();
	     ascii.hide();
	     set_viewport ( io_scr );
	     clearviewport();

	     switch ( chus )
	     {

	      case 1:
	       sprintf ( stroka, "Eter new namber of shape <%d>:", ( ( forma_l* ) formoch )->get_octant_number() );
	       string_to_display ( stroka, 0, 20 );

	       if ( scan_from_display ( buf_str ) )
	       {
	        char *tail, *buf, mn[81];
	        mn[0] = 0;
	        buf = buf_str;
	        devide_string ( buf, tail, mn, ",", 0 );
	        devide_string ( mn, buf, mn, ".", 0 );
	        select_string_from_string ( mn, mn, "0123456789", 1 );

	        if ( mn[0] )
	        {
	         sscanf ( mn, "%d", &m );
	        }

	        ( ( forma_l* ) formoch )->find ( formoch, m );
	       }

	       break;

	      case 2:
	       sprintf ( stroka, "Perss key to enter ASCII code:" );
	       string_to_display ( stroka, 0, 20 );
	       m = getch();
	       ( ( forma_l* ) formoch )->find ( formoch, m );
	       break;

	      default:
	       break;
	     }
	    }

	    while ( chus );
	   }

	   break;

	   case 11:
	   {
	    shape_12 *p = new shape_12 ( 2 );
	    d_link *pforma = new forma;
	    pforma->define ( p, pforma );
	    formoch->insert_befor ( pforma, formoch );
	   }

	   break;

	   case 10:
	   {
	    shape_12 *p = new shape_12 ( 2 );
	    d_link *pforma = new forma;
	    pforma->define ( p, pforma );
	    formoch->insert_past ( pforma, formoch );
	   }

	   break;

	   default:
	    break;
	  }
	 }

	 while ( ch != 0 );
	*/
}

void font::font_save ( void )
{
//  if ( m_file.exists() )
//  {
//   if ( m_file.open ( QIODevice::WriteOnly | QIODevice::Text ) )
//    m_stream.setDevice ( &m_file );
//  }
//  else
//  {
//   std_out<<QString::fromUtf8("Файл не существует: ")<< m_file.fileName() <<endl;
//  }
	if ( m_file.open ( QIODevice::WriteOnly | QIODevice::Text ) )
		m_stream.setDevice ( &m_file );
	else
	{
		std_out << QString::fromUtf8 ( "Не могу открыть файт: " ) << m_file.fileName() << endl;
		return;
	}

//************************************************************
	m_stream << "*0," << "4," << get_attribute() << endl;

	std_out << "*0," << "4," << get_attribute() << endl;

	m_stream
	<< get_above() << ","
	<< get_below() << "," << get_modes() << ","
	<< "0" << endl;

	for ( int i = 0; i < m_forma_l_list->size(); ++i )
	{
		( *m_forma_l_list ) [ i ]->print_shapes ( m_stream );
	}

	m_file.close();
}

void font::font_close ( void )
//Закрыть шрифт.
{
	/*
	 char ch;

	 if ( ! open )
	 {
	  return;
	 }

	 do
	 {
	  set_viewport ( zoom_scr );
	  clearviewport();
	  set_viewport ( io_scr );

	  string_to_display ( name, 0, 20, 11, 4 );
	  string_to_display ( "Save font? <y||n>:", 0, 0, 10, 4 );
	  ch = getch();
	 }

	 while ( ! ( ch == 'y' || ch == 'Y' || ch == 10 || ch == 'n' || ch == 'N' ) );

	 if ( ch == 'y' || ch == 'Y' || ch == 10 )
	 {
	  font_save();
	  return;
	 }

	 if ( ( ch = access ( str_dubl_1, 0 ) ) == 0 )
	 {
	  if ( unlink ( str_dubl_1 ) != 0 )
	  {
	   exit ( 5 );
	  }
	 }

	 if ( ( ch = access ( str_dubl_2, 0 ) ) == 0 )
	 {
	  if ( unlink ( str_dubl_2 ) != 0 )
	  {
	   exit ( 5 );
	  }
	 }

	 d_link *a = this;

	 clear_somthing ( a );
	 open = 0;
	*/
}




void font::print ( void )
{
	print_to_console ( std_out );
}

void font::menu_Font ( void )
{
	int rez  = 0;
	QString  str;
	QString   fileName;

	do
	{
		print();
//  edit_menu::s_menu_font_main->run();
//  rez = edit_menu::s_menu_font_main->get_run_rez();

		switch ( rez )
		{

			case 0: //Open
				fileName = QFileDialog::getOpenFileName ( 0, QString ( "Open File" ), QString ( "/home/namatv/workspace/u2/shp" ), QString ( "Shape files (*.shp)" ) );
//    fileName = QString ( "/home/namatv/workspace/u2/shp/es_unicode.shp" );
				std_out << fileName << endl;

				if ( fileName != 0 )
				{
					set_file_name ( fileName );
				}

				font_load();

				break;

			case 1: //Save
				font_save();
				break;

			case 2: //Save as
				break;

			case 3: //Edit header
				menu_Parametr();
				break;

			case 4: //Edit forms
				menu_Forms();
				break;

			case 5: //Draw vars
				break;

			case 6: //Close
				break;

			case 7: //Exit
				break;


			default :
				break;
		}
	}

	while ( rez >= 0 && rez < 7 );
}

void font::print_to_console ( QTextStream & stream )
{
	stream << QString::fromUtf8 ( "Содержит количество, созданных объектов font = " ) << s_font_main_count << endl;
	stream << QString::fromUtf8 ( "Имя файла оригинала                          = " ) << get_file_name() << endl;
	stream << QString::fromUtf8 ( "attribute                                    = " ) << get_attribute() << endl;
	stream << QString::fromUtf8 ( "Значение above                               = " ) << get_above() << endl;
	stream << QString::fromUtf8 ( "Значение below                               = " ) << get_below() << endl;
	stream << QString::fromUtf8 ( "Значение modes                               = " ) << get_modes() << endl;
	stream << QString::fromUtf8 ( "Количество символов в шрифте                 = " ) << m_forma_l_list->size() << endl;

	/*
	 stream << QString::fromUtf8 ( "Символы шрифта:" ) << endl;

	 for ( int i = 0; i < m_forma_l_list.size(); ++i )
	 {
	  stream << QString::fromUtf8 ( "Номер формы                                i = " ) << i << endl;
	  m_forma_l_list.at ( i ).print_to_console ( stream );
	 }
	*/
}

void font::set_file_name ( const QString & new_name )
{
	if ( new_name != 0 )
	{
		m_file.setFileName ( new_name );
		/*
		  if ( m_file.exists() )
		  {
		   if ( m_file.open ( QIODevice::ReadWrite | QIODevice::Text ) )
		    m_stream.setDevice ( &m_file );
		  }
		*/
	}
}

QString font::get_file_name ( void )
{
	return m_file.fileName();
}

void font::set_above ( int new_above )
{
	m_above = new_above;
}

int font::get_above ( void ) const
{
	return m_above;
}

void font::set_below ( int new_below )
{
	m_below = new_below;
}

int font::get_below ( void ) const
{
	return m_below;
}

void font::set_modes ( int new_modes )
{
	if ( new_modes ) m_modes = 2;
	else m_modes = 0;
}

int font::get_modes ( void ) const
{
	return m_modes;
}

void font::set_attribute ( const QString & new_attribute )
{
	if ( 0 < m_forma_l_list->size() )
		( *m_forma_l_list ) [0]->set_attribute ( new_attribute );
}

QString font::get_attribute ( void ) const
{
	QString rez;

	if ( 0 < m_forma_l_list->size() )
		rez = ( *m_forma_l_list ) [0]->get_attribute();

	return rez;

	/*
	 return m_comment;
	*/
}

bool font::is_font_main_opend ( void ) const
{
	return m_file.isOpen ();
}

/**
Редактировать атрибуты шрифта.
*/
void font::menu_Parametr ( void )
{
	int rez  = 0;
	int above = 0;
	int below = 0;
	int modes = 0;

	QString  attribute;

	do
	{
		print();
//  edit_menu::s_menu_font_parametr->run();
//  rez = edit_menu::s_menu_font_parametr->get_run_rez();

		switch ( rez )
		{

			case 0: //Above
				std_out << "Above (n>=1) <" << get_above () << "> =";
				std_out.flush();
				std_in >> above ;
				set_above ( above );
				break;

			case 1: //Below
				std_out << "Below (n>=1) <" << get_below() << "> =";
				std_out.flush();
				std_in >> below;
				set_below ( below );
				break;

			case 2: //Modes
				std_out << "Modes (0|2) <" << get_modes() << "> =";
				std_out.flush();
				std_in >> modes;
				set_modes ( modes );
				break;

			case 3: //Attribute
				std_out << "Attribute <" << get_attribute() << "> =";
				std_out.flush();
				attribute = std_in.readLine();
//    std_in >> attribute;
				set_attribute ( attribute );
				break;

			case 4: //Exit
				break;

			default:
				rez = 4;
				break;
		}
	}

	while ( rez >= 0 && rez < 4 );
}

void font::menu_Forms ( void )
{
}

void font::menu_Shuar ( void )
{
}

void font::menu_Ascii ( void )
{
	int rez  = 0;
	QString  str;
	ushort  rez_ushort;
	QString   fileName;

	do
	{
		switch ( rez )
		{

			case 1: //ASCII
				std_out << "ASCII:";
				std_out.flush();
				std_in >> str;

				if ( str.length() >=  1 )
				{
					rez_ushort = str[0].unicode () ;
//     number = rez_ushort;
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
//    number = -1;
				break;

			default:
				break;
		}
	}

	while ( rez >= 0 );
}

QList<forma_l*>* font::get_m_forma_l_list ( void )
{
	return m_forma_l_list;
}
