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

#ifndef MNAS_FONT_H
#define MNAS_FONT_H

#include "forma_l.h"

#include <QTextStream>
#include <QString>
#include <QFile>

///Класс font.

/**
Класс font.\n
Text Font Descriptions

Text fonts must include a special shape number 0 that conveys information about the font itself.

AutoCAD is packaged with numerous text fonts. You can use the STYLE command to apply expansion, compression, or
obliquing to any of these fonts, thereby tailoring the characters to your needs. You can draw text of any height, at
any baseline angle, and with either horizontal or vertical orientation using these fonts.

AutoCAD text fonts are files of shape definitions with shape numbers corresponding to the ASCII code for each
character. Codes 1 through 31 are for control characters, only one of which is used in AutoCAD text fonts:

10 (LF)
The line feed (LF) must drop down one line without drawing. This is used for repeated TEXT commands, to place
succeeding lines below the first one.

*10,5,lf

2,8,(0,-10),0

You can modify the spacing of lines by adjusting the downward movement specified by the LF shape definition.

Text fonts must include a special shape number 0 that conveys information about the font itself. The format has the following syntax:

*0,4,font-name

above,below,modes,0 

The above value specifies the number of vector lengths above the baseline that the uppercase letters extend, and below indicates how far the lowercase letters descend below the baseline. The baseline is similar in concept to the lines on writing paper. These values define the basic character size and are used as scale factors for the height specified in the TEXT command.

The modes byte should be 0 for a horizontally oriented font and 2 for a dual-orientation (horizontal or vertical) font. The special 00E (14) command code is honored only when modes is set to 2.

The standard fonts supplied with AutoCAD include a few additional characters required for the AutoCAD dimensioning feature.

%%%d Degree symbol (°)

%%%p Plus/minus tolerance symbol (±)

%%%c Circle diameter dimensioning symbol 

You can use these and the %%nnn control sequences, as described under TEXT in the Command Reference.

NoteAutoCAD draws text characters by their ASCII codes (shape numbers) and not by name. To save memory, specify the shape name portion of each text shape definition in lowercase as shown in the following example. (Lowercase names are not saved in memory.)
*65,11,uca
024,043,04d,02c,2,047,1,040,2,02e,0
Because the shape name uca contains lowercase letters, AutoCAD doesn't save the name in memory. However, you can use the name for reference when editing the font definition file. In this example, uca stands for uppercase A.

---------------------------------------------------------------------------------------------------------------------

Big Font Descriptions

To reduce the size of composite Kanji characters, you can define an extended Big Font file. Extended big fonts use the subshape code, followed immediately by a 0. 

The first line of an extended Big Font file is the same as the regular Big Font file. This is the format for the remaining lines of the file:

*0,5,font-name 
character-height, 0, modes, character-width,0


*shape-number,defbytes,shape-name

code,0,primitive#,basepoint-x,basepoint-y,width,height, 

code,0,primitive#,basepoint-x,basepoint-y,width,height, 

terminator
The following list describes the fields of a Big Font definition file:

character height
Used along with character width to indicate the number of units that define the font characters.

character width
Used along with character height to indicate the number of units that define the font characters. The character-height and character-width values are used to scale the primitives of the font. In this context, primitives are the points, lines, polygons, or character strings of the font geometrically oriented in two-dimensional space. A Kanji character consists of several primitives used repeatedly in different scales and combinations.

modes
The modes byte should be 0 for a horizontally oriented font and 2 for a dual-orientation (horizontal or vertical) font. The special 00E (14) command code is honored only when modes is set to 2. 

shape-number
Character code.

defbytes
Byte size. It is always 2 bytes, consisting of a hexadecimal or a combination of decimal and hexadecimal codes.

shape-name
Character name.

code
Shape description special code. It is always 7 so that it can use the subshape feature. 

primitive#
Reference to the subshape number. It is always 2.

basepoint-x
X origin of the primitive.

basepoint-y
Y origin of the primitive.

width
Scale of the width of the primitive.

height 
Scale of the height of the primitive.

terminator
End-of-file indicator for the shape definition. It is always 0.

To arrive at the scale factor, AutoCAD scales down the primitive to a square unit and then multiplies it by the height and width to get the shape of the character. Character codes (shape numbers) in the Big Font shape definition file can have values up to 65535. The following table describes the fields of the extended Big Font file.

   
Variable
 Value
 Byte size
 Description
 
shape-number
 xxxx
 2 bytes
 Character code
 
code
 7,0
 2 bytes
 Extended font definition
 
primitive#
 xxxx
 2 bytes
 Refer to subshape number
 
basepoint-x
   
 1 byte
 Primitive X origin
 
basepoint-y
   
 1 byte
 Primitive Y origin
 
width
   
 1 byte
 Scale of primitive width
 
height
   
 1 byte
 Scale of primitive height
 
terminator
 0
 1 byte
 End of shape definition
 

The following figure is an example of a 16 x 16 dot matrix that you could use to design an extended Big Font, such as a Kanji character. In the example, the distance between each dot is one unit. The callout points to a square unit.



The following figure shows examples of Kanji characters. Each character occupies an M×N matrix (matrices don't have to be square), similar to the one shown in the previous figure. The numbers above each figure are the associated shape numbers.



The following figure shows Kanji primitives.



NoteNot all fonts are defined in a square matrix; some are defined in rectangular matrices.


---------------------------------------------------------------------------------------------------------------------

Define a Big Font

Special codes in the first line of a Big Font file specify how to read two-byte hexidecimal codes.

A font with hundreds or thousands of characters must be handled differently from a font containing the ASCII set of up to 256 characters. In addition to using more complicated techniques for searching the file, AutoCAD needs a way to represent characters with two-byte codes as well as one-byte codes. Both situations are addressed by the use of special codes at the beginning of a Big Font file.

The first line of a Big Font shape definition file must be as follows:

*BIGFONT nchars,nranges,b1,e1,b2,e2,...

where nchars is the approximate number of character definitions in this set; if it is off by more than about 10 percent, either speed or file size suffers. You can use the rest of the line to name special character codes (escape codes) that signify the start of a two-byte code. For example, on Japanese computers, Kanji characters start with hexadecimal codes in the range 90-AF or E0-FF. When the operating system sees one of these codes, it reads the next byte and combines the two bytes into a code for one Kanji character. In the *BIGFONT line, nranges tells how many contiguous ranges of numbers are used as escape codes; b1, e1, b2, e2, and so on, define the beginning and ending codes in each range. Therefore, the header for a Japanese Big Font file might look like this:

*BIGFONT 4000,2,090,0AF,0E0,0FF
After the *BIGFONT line, the font definition is just like a regular AutoCAD text font, except that character codes (shape numbers) can have values up to 65535.


---------------------------------------------------------------------------------------------------------------------

Unicode Font Descriptions

A single Unicode font, due to its large character set, is capable of supporting all languages and platforms. Unicode shape definition files are virtually identical in format and syntax to regular AutoCAD shape definition files.

The main difference is in the syntax of the font header as shown in the following code:

*UNIFONT,6,font-name
above,below,modes,encoding,type,0
The font-name, above, below, and modes parameters are the same as in regular fonts. The remaining two parameters are defined as follows:

encoding
Font encoding. Uses one of the following integer values.

0 Unicode
1 Packed multibyte 1
2 Shape file

Font embedding information. Specifies whether the font is licensed. Licensed fonts must not be modified or exchanged. Bitcoded values can be added.

0 Font can be embedded
1 Font cannot be embedded
2 Embedding is read-only

Another important difference is the handling of the code 7 subshape reference. If a shape description includes a code 7 subshape reference, the data following the code 7 is interpreted as a two-byte value. This affects the total number of data bytes (defbytes) in the shape description header. For example, the following shape description is found in the romans.shp file:

*00080,4,keuroRef
7,020AC,0
The second field in the header represents the total number of bytes in the shape description. If you are not used to working with Unicode font descriptions, you may be inclined to use three bytes rather than four, but this would cause an error during the compiling of the SHP file. This is true even if the shape number you are referencing is not in the two-byte range (below 255); the compiler always uses two bytes for this value, so you must account for that in the header.

The only other difference between Unifont shape definitions and regular shape definitions is the shape numbers. The Unifont shape definitions that AutoCAD provides use hexadecimal shape numbers as opposed to decimal values. Although hexadecimal numbers are not required, their use makes it easier to cross-reference the shape numbers with the \\U+ control character values. 
*/


class font
{

	public:
		font ( void );																					///<Конструктор.
		~font ( void );																					///<Деструктор.

		void set_file_name ( const QString & new_name );				///<Установить имя шрифта.
		QString	get_file_name ( void );													///<Возвращает имя файла шрифта.

		void set_above ( int a );																///<Устанавливает количество единичных векторов на которое поднимаются над базовой линией символы верхнего регистра.
		int get_above ( void ) const;														///<Возвращает значение атрибута above.

		void set_below ( int new_below );												///<Устанавливает количество единичных векторов на которое ниже базовой линии располагаются символы нижнего регистра.
		int get_below ( void ) const;														///<Возвращает значение атрибута below.

		void set_modes ( int new_modes );												///< Байт modes должен быть равным 0 для стандартного (горизонтального) шрифта и равным 2 для шрифта двойной ориентации (горизонтальной и вертикальной). Специальный командный код 00E (14) используется только тогда, когда байт modes имет значение 2.
		int get_modes ( void ) const;														///<Возвращает значение атрибута modes.

		void set_attribute ( const QString & new_attribute );		///<Устанавливает значение атрибута attribute.
		QString get_attribute ( void ) const;										///<Возвращает значение атрибута attribute.
		void menu_Font ( void );																///<Запускает на выполнение главное меню редактирования шрифта.
		void menu_Parametr( void );															///<Запускает на выполнение меню редактирования параметров шрифта.
		void menu_Forms( void );																///<Запускает на выполнение меню редактирования форм шрифта.
		void menu_Shuar( void );																///<Меню Вы уверены? Да|Нет
		void menu_Ascii( void );																///<

		void font_load ( void );																///<Загрузить список форм.
		void font_save ( void );																///<Сохранить шрифт.
		void font_close ( void );																///<Закрыть шрифт.
		void font_forms ( draw_vars &, stack & );
		void print ( void );																		///<Метод печати.
		bool is_font_main_opend ( void ) const;									///<Если шрифт открыт возвращает true.

		void print_to_console ( QTextStream & stream );					///<Вывод содержимого на консоль.

		QList<forma_l*>* get_m_forma_l_list(void);							///<Возвращает m_forma_l_list

	private:
		static long s_font_main_count;													///<Содержит количество, созданных объектов font
		QList<forma_l *> *m_forma_l_list;												///<Символы шрифта

	private:
		QTextStream m_stream;																		///<Поток файла описания шрифта
		QFile m_file;																						///<Файл описания шрифта


		int m_above;																						///<above.
		int m_below;																						///<below.
		int m_modes;																						///<modes.
		QString m_comment;																			///<Атрибут шрифта.
};

#endif
