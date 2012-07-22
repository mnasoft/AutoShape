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

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

#include <math.h>
#include "strings.h"

#include <QTextStream>
QTextStream s_out ( stdout );
QTextStream s_in ( stdin );

char buffer[10000];
char buff_2[10000];
char buf_str[80];
char str_shape[2000];
char msg[81];

int string_to_int ( char *a )
{
	int i;

	if ( *a == '0' )
	{
		if ( * ( a + 1 ) != NULL )
		{
			a++;
			sscanf ( a, "%x", &i );

			if ( i >= 127 ) i -= 256;
		}

		else
		{
			sscanf ( a, "%x", &i );

			if ( i >= 127 ) i -= 256;
		}
	}

	else
	{
		sscanf ( a, "%d", &i );
	}

	if ( i < -128 || i > 127 ) i = 0;

	return i;
}

/**
Преобразует строку из буфера buffer в сторку str_shape
*/
void string_to_string ( void )
{
	char a[50];
	char b[50];
	char *buf;
	char *str_sh;
	str_sh = str_shape;
	buf = buffer;
	int i, j;

	for ( i = 0;i < 2000;i++ ) str_shape[i] = NULL;

	i = 0;

	while ( *buf )
	{
		sscanf ( buf, "%[-+()0123456789abcdefABCDEF\n\t\v]", a );
		buf += strlen ( a ) + 1;
		i = 0;
		j = 0;

		while ( a[i] )
			switch ( a[i] )
			{

				case '\n' :
					i++;
					break;

				case '('  :
					i++;
					break;

				case ')'  :
					i++;
					break;

				case '\t' :
					i++;
					break;

				case '\v' :
					i++;
					break;

				default   :
					b[j++] = a[i++];
					break;
			}

		b[j++] = a[i++];

		* ( str_sh++ ) = l_to_char ( string_to_l ( b ) );
	}
}

/**
Преобразует int a в диапазоне [-128;256] в символ и возвращает его.
*/
char l_to_char ( int a )
{
	char s;
	s = 0;
	s = char ( a );
	return s;
}


/**
Преобразует int a в диапазоне [-128;127] в символ и возвращает его.\n
В случае выхда за границы диапазона возвращает 0.
*/
char int_to_char ( int a )
{
	char s;
	s = 0;

	if ( a < 0 )
	{
		a += 256;
		s = a;
	}

	if ( -128 >= a || a <= 127 )
	{
		s = a;
		return s;
	}

	return s;
}

/**
Интерпретирует строку как целое число и возвращает его.
*/
int string_to_l ( char *a )
{
	int i, k;
	i = 0;
	k = 1;

	if ( *a == '-' && * ( a + 1 ) == '0' )
	{
		a++;
		k = -1;
	}

	if ( *a == '0' )
	{
		if ( * ( a + 1 ) != NULL )
		{
			a++;
			sscanf ( a, "%x", &i );
			i *= k;
		}

		else
		{
			sscanf ( a, "%x", &i );
			i *= k;
		}
	}

	else
	{
		sscanf ( a, "%d", &i );
	}

	return i;
}

/**
Преобразует char [0,255] в int в диапазоне [-128;127].
*/
int  char_to_int ( char a )
{
	int i;
	i = a;

	if ( i >= 127 ) i -= 256;

	return i;
}

/**
Читает с экрана строку и помещает ее в в буфер buf_str[80]
*/
QString scan_from_display ( void )
{
	QString 	tmp;
	/*	set_viewport(io_scr);
		char * buf;
		int i;
		char ch;
		char buf_pr[50];
		int col=getcolor();
		sprintf(buf_pr,"████████████████████████████████");
		setcolor(BACKCOLOR);
		outtextxy(1,5,buf_pr);
		setcolor(COLOR);
		sprintf(buf_pr,"      Enter string            ");
		outtextxy(1,5,buf_pr);

		for(i=0;i<80;i++)buf_str[i]=0;
		i=0;
		buf=buf_str;
		while((ch=getch())!='\r'&& i<50)
		{
			if(ch!='\b')
			{
				*buf++=ch;i++;
			}
			else
			{
				if(i>0)
				{
					*(--buf)=0;i--;
				}
				else
				{
					*buf=0;
				}
			}
			sprintf(buf_pr,"██████████████████████████████████████████████████");
			setcolor(BACKCOLOR);
			outtextxy(1,5,buf_pr);
			setcolor(COLOR);
			sprintf(buf_pr,"%s",buf_str);
			outtextxy(1,5,buf_pr);
			setcolor(col);
		}
		return *buf_str;
	*/
	s_in >> tmp;
	return tmp;
}

//void string_to_display(char * str,int x,int y, int color, int b_color, char b_liter)
void string_to_display ( QString str )
// Выводит на экран строку-сообщение
{
	s_out << str << endl;
	/*
		char buf_pr[81];

		if( y<0)y=0;
		if( x<0)x=0;


		buf_pr[0]=0;
		int len=strlen(str);
		int count=0;
		if(len>80)len=getmaxx()/8;
		while(count<len)
		{
			buf_pr[count++]=b_liter;
		}
		buf_pr[count]=0;

		int col=getcolor();
		setcolor(b_color);
		int end_x=x+8*len;

		if( y+8 >= getmaxy() )y=getmaxy()-8;
		if( end_x >= getmaxx() )x=getmaxx()-8*len;

		outtextxy(x,y,buf_pr);

		char * a;
		a=str;
		while(count<len)
		{
			buf_pr[count++]= * a++;
		}

		buf_pr[count]=0;
		setcolor(color);

		outtextxy(x,y,str);
		setcolor(col);
	*/
}

int devide_string ( char *buf_string, char * & tail, char *str_rez,
                    char *str_devides, int first, int get_lenth )
//Читает из buf_string символы и помещает их в str_rez длинной до get_lenth
//символов. При встрече символа из str_devides чтение прерывается и этот
//символ в стринг str_rez не переносится. Указатель на этот символ или
//на NULL (если он достигнут при чтении) передается через tail.
//Возвращает 0, если buf_string указывает на 0, иначе возвращает 1.
//Если first=1, то первый символ (если он является разделителем (входящим
//в строку str_devides)) будет проигнорирован, а чтение будет производиться
//со следующего символа.

{
	char *buf, *rez;
	int ii = strlen ( str_devides );
	int equal;
	buf = buf_string;
	rez = str_rez;
	{
//Игнорирование первого символа если first!=0 и он совпадает с набором из str_devides
		int cur;
		equal = 1;

		for ( cur = 0;cur < ii;cur++ )
		{
			if ( *buf == str_devides[cur] ) equal = 0;
		}

		if ( equal == 0 && first ) buf++;

//Игнорирование первого символа если first!=0 и он совпадает с набором из str_devides
	}

	if ( *buf )
	{
		if ( get_lenth <= 0 )
		{
			do
			{
				int cur;
				equal = 1;

				for ( cur = 0;cur <= ii;cur++ )
				{
					if ( *buf == str_devides[cur] ) equal = 0;
				}

				*rez++ = *buf++;
			}

			while ( equal );

			* ( --rez ) = 0;

			tail = --buf;

			return 1;
		}

		else
		{
			int no = 0;

			do
			{
				int cur;
				equal = 1;

				for ( cur = 0;cur <= ii;cur++ )
				{
					if ( *buf == str_devides[cur] ) equal = 0;
				}

				*rez++ = *buf++;

				no++;
			}

			while ( equal && no <= get_lenth );

			* ( --rez ) = 0;

			tail = --buf;

			return 1;
		}
	}

	else
	{
		*str_rez = 0;
		tail = buf;
		return 0;
	}
}

QString devide_string ( QString str, QChar devider, int lenth )
{
	bool do_while = true;
	int pos = 0;

	do
	{
		pos = pos + lenth;
		pos = str.indexOf ( devider, pos );

		if ( pos <= 0 )
			do_while = false;
		else
		{
			str.insert ( pos + 1, QChar ( '\n' ) );
		}
	}

	while ( do_while );

	return str;
}

/*
QString devide_string(QString str, QChar devider, int lenth)
{
	bool do_while=true;
	int i=1;
	int pos;
	pos=str.indexOf('\n', 0);

	do
	{
		pos=str.indexOf(devider, i*lenth+(i-1));
		if(pos<=0)
			do_while=false;
		else
		{
			str.insert(pos+1,QChar('\n'));
			++i;
		}

	}
	while(do_while);
	return str;
}
*/

int select_string_from_string ( char *buf_string, char *str_rez,
                                char *str_devides, int this_is )
//Выбирает из buf_string только символы которые отсутствуют (this_is = 0)
//присутствуют (this_is != 0)в str_devides
//и записывает их (символы) в str_rez.
{
	char *buf, *rez;
	int ii = strlen ( str_devides );
	int equal;
	buf = buf_string;
	rez = str_rez;

	if ( buf_string[0] == 0 )
	{
		str_rez[0] = 0;
		return 0;
	}

	do
	{
		int cur;
		equal = 1;

		for ( cur = 0;cur < ii;cur++ )
		{
			if ( *buf == str_devides[cur] ) equal = 0;
		}

		if ( this_is )
		{
			//Для символов которые присутствуют
			if ( equal == 0 ) *rez++ = *buf++;
			else buf++;

			//Для символов которые присутствуют
		}

		else
		{
			//Для символов которые отсутствуют
			if ( equal ) *rez++ = *buf++;
			else buf++;

			//Для символов которые отсутствуют
		}
	}

	while ( *buf );

	* ( rez ) = 0;

	return 1;
}

int devide_file ( FILE *in, char *str_rez, char *str_devides,
                  int first, int get_lenth )
//Читает из in символы и помещает их в str_rez длинной до get_lenth
//символов. При встрече символа из str_devides чтение прерывается и этот
//символ в стринг str_rez не переносится. Указатель на этот символ или
//на NULL (если он достигнут при чтении) передается через tail.
//Возвращает 0, если buf_string указывает на 0, иначе возвращает 1.
//Если first=1, то первый символ (если он является разделителем (входящим
//в строку str_devides)) будет проигнорирован, а чтение будет производиться
//со следующего символа.
{
	char ch;
	char *rez;
	int ii = strlen ( str_devides );
	int equal;
	rez = str_rez;
	{
//Игнорирование первого символа если first!=0 и он совпадает с набором из str_devides
		int cur;
		equal = 1;

		if	( ( ch = fgetc ( in ) ) != EOF )
		{
			for ( cur = 0;cur < ii;cur++ )
			{
				if ( ch == str_devides[cur] ) equal = 0;
			}

			if ( equal == 0 && first )
				{}
			else
			{
				ungetc ( ch, in );
			}
		}

		else
		{
			// Если достигнут конец файла
		}

//Игнорирование первого символа если first!=0 и он совпадает с набором из str_devides
	}

	if	( ( ch = fgetc ( in ) ) != EOF )
	{
		ungetc ( ch, in );

		if ( get_lenth <= 0 )
		{
			do
			{
				int cur;
				equal = 1;

				if	( ( ch = fgetc ( in ) ) != EOF )
				{
					for ( cur = 0;cur < ii;cur++ )
					{
						if ( ch == str_devides[cur] ) equal = 0;
					}

					*rez++ = ch;
				}

				else
				{
					//Достигнут конец файла.
					*rez = 0;
					return 0;
				}
			}

			while ( equal );

			//Найден символ разделитель
			*--rez = 0;

			ungetc ( ch, in );

			return 1;
		}

		else
		{
			int no = 0;

			do
			{
				int cur;
				equal = 1;

				if	( ( ch = fgetc ( in ) ) != EOF )
				{
					for ( cur = 0;cur < ii;cur++ )
					{
						if ( ch == str_devides[cur] ) equal = 0;
					}

					*rez++ = ch;

					no++;
				}

				else
				{
					//Достигнут конец файла.
					return 0;
				}
			}

			while ( equal && no <= get_lenth );

			*rez = 0;

			return 1;
		}
	}

	else
	{
		//Если достигнут конец файла на первом символе который дб считан.
		*str_rez = 0;
		return 0;
	}
}

/**
Преобразует x к диапазону 0...360.
*/
extern qreal cicl ( double baza, double delta, double  x )
{
	double left, right, rez;

	if ( delta < 0 )
	{
		left = baza + delta;
		right = baza;
	}

	else
	{
		left = baza;
		right = baza + delta;
	}

	if ( x > left && x < right )
	{
		return x;
	}

	else
		if ( x <= left )
		{
			rez = int ( ( right - x ) / ( right - left ) ) * ( right - left ) + x;
		}

		else
			if ( x >= right )
			{
				rez = x - int ( ( x - left ) / ( right - left ) ) * ( right - left );
			}

	if ( rez == baza + delta )
	{
		return baza;
	}

	return rez;
}

/**
Округляет x в зависимости от mode \n
mode=-1 ближайшему меньшему Z \n
mode= 1  ближайшему большему Z \n
mode= 0  ближайшему Z \n
из ряда Z=baza+delta*n , где n-целое число.
*/
extern qreal round ( double baza, double delta, int mode, double  x )
{
	double left, right;

	if ( delta < 0. ) delta *= -1;

	if ( baza == x ) return x;

	if ( x < baza )
	{
		right = baza - int ( ( baza - x ) / delta ) * delta;
		left = right - delta;
	}

	if ( x > baza )
	{
		left = baza + int ( ( x - baza ) / delta ) * delta;
		right = left + delta;
	}

	if ( mode < 0 ) return left;

	if ( mode > 0 ) return right;

	if ( mode == 0 )
		if ( right - x <= x - left ) return right;

	return left;
}

QString scan_str()
{
	QString tmp;
	s_in >> tmp;
	return tmp;

	/*	x=0;
		y=0;
		handle han;
		char str[80];str[0]=0;
		char tem[80];tem[0]=0;
		int into=1;
		int cur=0;
		int j=0;
		int insert=1;



		while(into)
		{
			j=-1;
			do
			{
				j++;
				if(str[j]!=0)
				{
					if(j==cur)tem[j]='~';
					else tem[j]=' ';
				}
				else tem[j]=0;
			}while(j<80&&str[j]!=0);

			string_to_display(tem,0,10,14,1,'█');
			string_to_display(str,0,0,14,1,'█');




			m_on();// функция 0x0001
			han=event(1,1);
			han.x-=draw_scr.left;
			han.y-=draw_scr.top;
			m_off();// функция 0x0001

			string_to_display(tem,0,10,0,0,'█');
			string_to_display(str,0,0,0,0,'█');

			int len=strlen(str);

			if(han.right){into=0;}
			else
			if(han.middle){into=0;}
			else
			if(han.key==ESC){into=0;}
			else
			if(han.left){into=0;out[0]=0;return han;}
			switch (han.key)
			{
				case HOME:
				{
					if(cur>0)cur--;
				}
				break;
				case END:
				{
					if(len>cur)cur++;
				}
				break;
				case BSPACE:
				{
					j=cur-1;int i=cur;
					if(j>=0)
					{
						do
						{str[j++]=str[i++];}while(str[i-1]);
						cur--;
					}
				}
				break;
				case ENTER:
				{into=0;}
				break;
				case INSERT: insert=!insert;break;
				case DELETE:
				{
					j=cur;int i=cur;
					if(str[i++])
					do{str[j++]=str[i++];}while(str[i-1]);
				}
				break;
				case F2: x++;break;
				case F1: x--;break;
				case F4: y++;break;
				case F3: y--;break;
				default :
				if(han.key<256&&han.key>=32&&len<79)
				{
					if(insert)
					{
						int i;
						i=j=0;
						do
						{
							if(j!=cur)tem[j++]=str[i++];
							else tem[j++]=han.key;
						}while(tem[j-1]);
						cur++;
						strcpy(str,tem);
					}
					else
					{
						if(str[cur])str[cur++]=han.key;
						else {str[cur++]=han.key;str[cur]=0;}
					}
				}
			}
		}
		strcpy(out,str);
		return han;
	*/
}
