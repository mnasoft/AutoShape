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

#ifndef STRINGS_H
#define STRINGS_H

#ifndef BACKCOLOR
#define BACKCOLOR 1
#endif

#ifndef COLOR
#define COLOR 14
#endif

#ifndef COLOR_
#define COLOR_ 12
#endif

#include <QString>

extern void string_to_string(void);///<Преобразует строку из буфера buffer в сторку str_shape

extern char int_to_char(int);	///<Преобразует int a в диапазоне [-128;127] в символ и возвращает его. В случае выхда за границы диапазона возвращает 0.

extern char l_to_char(int);///<Преобразует int a в диапазоне [-128;256] в символ и возвращает его.

extern int  char_to_int(char);///<Преобразует char [0,255] в int в диапазоне [-128;127].

extern int string_to_int(char *);///<Интерпретирует строку как целое число диапазоне [-128;127]и возвращает его.

extern int string_to_l(char *);///<Интерпретирует строку как целое число и возвращает его.

extern QString scan_from_display(void);///<Читает с экрана строку и помещает ее в буфер buf_str[80]

///Выводит строку str на экран в графическом режиме.
/**
- x,y -координаты левого верхнего угла;
- color -цвет литер;
- b_color -цвет фона;
- b_liter -литера фона;
*/


//extern void string_to_display(char *str,int x=150,int y=15, int color=14, int b_color=1, char b_liter='█');
extern void string_to_display(QString str);


/** Читает из buf_string символы и помещает их в str_rez длинной до get_lenth
символов. При встрече символа из str_devides чтение прерывается и этот
символ в стринг str_rez не переносится. Указатель на этот символ или
на NULL (если он достигнут при чтении) передается через tail.
*/
/**Возвращает 0, если buf_string указывает на 0, иначе возвращает 1.
Если first=1, то первый символ (если он является разделителем (входящим
в строку str_devides)) будет проигнорирован, а чтение будет производиться
со следующего символа.
*/
extern int devide_string(char *buf_string,char * & tail,char *str_rez, char *str_devides, int first=0,int get_lenth=0);

extern QString devide_string(QString str, QChar devider, int lenth);


/**Выбирает из buf_string только символы которые отсутствуют (this_is = 0)
присутствуют (this_is != 0)в str_devides
и записывает их (символы) в str_rez.
*/
extern int select_string_from_string(char *buf_string,char *str_rez, char *str_devides,int this_is=1);

//@todo extern int devide_file(FILE *in,char *str_rez, char *str_devides, int first=0,int get_lenth=0);

/**Читает из in символы и помещает их в str_rez длинной до get_lenth
символов. При встрече символа из str_devides чтение прерывается и этот
символ в стринг str_rez не переносится. Указатель на этот символ или
на NULL (если он достигнут при чтении) передается через tail.
*/
/**Возвращает 0, если buf_string указывает на 0, иначе возвращает 1.
Если first=1, то первый символ (если он является разделителем (входящим
в строку str_devides)) будет проигнорирован, а чтение будет производиться
со следующего символа.
*/


///Преобразует x к циклическому диапазону с началом в baza и шагом delta( [baza, baza+delta)
extern qreal cicl(double baza,double delta,double  x);

/**Округляет x в зависимости от mode
- mode=-1 ближайшему меньшему Z
- mode= 1  ближайшему большему Z
- mode= 0  ближайшему Z
из ряда Z=baza+delta*n , где n-целое число.
с началом в baza и шагом delta( [baza, baza+delta)
*/

extern qreal round(double baza,double delta,int mode, double  x);

#endif
