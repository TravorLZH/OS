/* 
* TravorOS: A simple OS running on Intel x86 Architecture
* Copyright (C) 2017  Travor Liu
*
* This program is free software: you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation, either version 3 of the License, or
* any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program.  If not, see <https://www.gnu.org/licenses/>.
*/
/* ctypes.c: Implementations of functions about character categories */
#include <def.h>
#include <ctypes.h>

char* alpha="abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ";
char* digit="0123456789";
char* punct="!\"#$%&'()*+,-./:;<=>@[\\]^_`{|}~";
char* space="\t\n\r\v\a ";

int isalpha(int c)
{
	if(strchr(alpha,c)){
		return 1;
	}
	return 0;
}

int isdigit(int c)
{
	if(strchr(digit,c)){
		return 1;
	}
	return 0;
}

int isspace(int c)
{
	if(strchr(space,c)){
		return 1;
	}
	return 0;
}

int ispunct(int c)
{
	if(strchr(punct,c)){
		return 1;
	}
	return 0;
}

int islower(int c)
{
	if(c>='a' && c<='z'){
		return 1;
	}
}

int isupper(int c)
{
	if(c>='A' && c<='Z'){
		return 1;
	}
	return 0;
}

/* Conversions between cases */
int tolower(int c)
{
	if(isupper(c)){
		return c-'A'+'a';
	}
	return c;
}

int toupper(int c)
{
	if(islower(c)){
		return c-'a'+'A';
	}
	return c;
}
