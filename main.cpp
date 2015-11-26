//
// main.cpp
//


#include <windows.h>
#include <math.h>
#include <stdio.h>

#include "resource.h"

#include "..\..\systemNNN\nyanLib\include\commonmacro.h"

#include "..\..\systemNNN\nnnUtilLib\commongameVersion.h"

#include "..\..\systemNNN\nnnLib\mainControl.h"
#include "..\..\systemNNN\nnnLib\gameCallBack.h"

#include "..\..\systemNNN\nnnUtilLib\currentDirControl.h"

#include "game.h"
#include "main.h"


#include "..\..\systemNNN\nyanlib\include\libinclude.h"

#if !defined _DEBUG
#pragma comment(lib,"d:\\libpng\\lib\\zlib.lib")

#pragma comment(lib,"d:\\libpng\\lib\\libpng.lib")
#else
#pragma comment(lib,"d:\\libpng\\lib\\zlibD.lib")
#pragma comment(lib,"d:\\libpng\\lib\\libpngD.lib")
#endif


//#pragma comment(lib,"thinkgear.lib")

//#include "thinkgear.h"

//#define __DEMO_VERSION__

/*
void
wait() {
//    printf( "\n" );
    //printf( "Press the ENTER key...\n" );
    //fflush( stdout );
    //getc( stdin );
	MessageBox(NULL,"wait","wait",MB_OK);
}
*/


int WINAPI WinMain(  HINSTANCE hInstance,   HINSTANCE hPrevInstance,  LPSTR lpCmdLine,  int nCmdShow)
{
/*


    char *comPortName = NULL;
    int   dllVersion = 0;
    int   connectionId = 0;
    int   packetsRead = 0;
    int   errCode = 0;

	OutputDebugString("main()...\n");

    // Print driver version number 
	OutputDebugString("GetVersion...\n");
    dllVersion = TG_GetDriverVersion();
    printf( "ThinkGear DLL version: %d\n", dllVersion );

	OutputDebugString("connect start...\n");

    // Get a connection ID handle to ThinkGear 
    connectionId = TG_GetNewConnectionId();
    if( connectionId < 0 ) {
        fprintf( stderr, "ERROR: TG_GetNewConnectionId() returned %d.\n", 
                 connectionId );
        wait();
        exit( EXIT_FAILURE );
    }

	OutputDebugString("log1...\n");
    // Set/open stream (raw bytes) log file for connection 
    errCode = TG_SetStreamLog( connectionId, "streamLog.txt" );
    if( errCode < 0 ) {
		MessageBox(NULL,"err1","err1",MB_OK);
//        fprintf( stderr, "ERROR: TG_SetStreamLog() returned %d.\n", errCode );
  //      wait();
        exit( EXIT_FAILURE );
    }

    // Set/open data (ThinkGear values) log file for connection 
	OutputDebugString("log2...\n");
    errCode = TG_SetDataLog( connectionId, "dataLog.txt" );
    if( errCode < 0 ) {
		MessageBox(NULL,"err2","err2",MB_OK);
//        fprintf( stderr, "ERROR: TG_SetDataLog() returned %d.\n", errCode );
        //wait();
        exit( EXIT_FAILURE );
    }

	OutputDebugString("open handle...\n");
    // Attempt to connect the connection ID handle to serial port "COM5" 
    comPortName = "\\\\.\\COM2";
    errCode = TG_Connect( connectionId, 
                          comPortName, 
                          TG_BAUD_9600, 
                          TG_STREAM_PACKETS );
    if( errCode < 0 ) {
//        fprintf( stderr, "ERROR: TG_Connect() returned %d.\n", errCode );
  //      wait();
		MessageBox(NULL,"err3","err3",MB_OK);

        exit( EXIT_FAILURE );
    }

	OutputDebugString("start...\n");

    packetsRead = 0;
    while( packetsRead < 10 ) {

        // Attempt to read a Packet of data from the connection 
        errCode = TG_ReadPackets( connectionId, 1 );

        // If TG_ReadPackets() was able to read a complete Packet of data...
        if( errCode == 1 ) {
            packetsRead++;

			OutputDebugString("packet read \n");
            // If attention value has been updated by TG_ReadPackets()... 
            if( TG_GetValueStatus(connectionId, TG_DATA_ATTENTION) != 0 ) {

                // Get and print out the updated attention value 
//                fprintf( stdout, "New attention value: %d\n",
  //                       TG_GetValue(connectionId, TG_DATA_ATTENTION) );

    //            fflush( stdout );


				float f = TG_GetValue(connectionId, TG_DATA_ATTENTION) ;
				char mes[256];
				sprintf_s(mes,256,"value=%f\n",f);
				OutputDebugString(mes);

            } // end "If attention value has been updated..." 

        } // end "If a Packet of data was read..." 
	

    } // end "Read 10 Packets of data from connection..." 

    // Clean up 
    TG_FreeConnection( connectionId );





	return 0;
*/

/*

	for (int i=0;i<1000;i++)
	{
		int r = rand();
		r++;
	}

	for (int i=0;i<30;i++)
	{
		float th = (float)(i + 4);
		th /= 36;
		th *= 3.14159f*2.0f;
		float dr = (float)(i);
		dr /= 6;
		dr *= 3.14159f*2.0f;

		float ml = 250.0f + sin(dr) * 40.0f;
		int y = (int)(cos(th) * ml) + 300 - 20;
		int x = (int)(sin(th) * ml) + 400 - 20;

		char mes[256];
//		x = (rand() %  700) + 50;
//		y = (rand() % 500) + 50;
//		while ((x>=330) && (x<470) && (y>=230) && (y<370))
//		{
//			x = (rand() %  700) + 50;
//			y = (rand() % 500) + 50;
//		}

//		int r = (rand() % 2) + 2;

		int r = 1;
		sprintf_s(mes,"%d,%d,35,35,%d,0\n",x,y,r);
		OutputDebugString(mes);
	}
*/



//return 0;

//

	/*
	int a0 = 155;
	int b0 = 3741;

	int a = a0;
	int b = b0;

	while (a & b)
	{
		int c = a & b;
		a &= ~c;
		b &= ~c;
		a |= b;
		b = c<<1;

		char mes[256];
		sprintf_s(mes,256,"\n%d %d : %d+ %d = %d",a0,b0,a,b,a | b);
		OutputDebugString(mes);
	}


	return 0;
*/



	CCurrentDirControl::ChangeCurrentToExe();

	//
	// 必要ならここで体験版フラグなどをたてる
	//
//	CCommonGameVersion::SetTaikenVersion();
//	CCommonGameVersion::SetLoadOk();
//	CCommonGameVersion::SetSaveOk();

	//
	// 必要ならここで独自のwheelMouse,systemfileを作成する
	//
	m_game = NULL;
//	m_wheelMouse = new CWheelMouse();
//	m_systemFile = new CCommonSystemFile();
//	m_systemFile->Load(TRUE);


	m_mainControl = new CMainControl();	//コンストラクタでwheelMouse,systemfileを指定できる 指定なし、またはNULLだと内部で標準のを作成する

	if (m_mainControl->CheckSystem())
	{
		HICON icon = LoadIcon(hInstance, MAKEINTRESOURCE(IDI_ICON1));
		HWND hWnd = m_mainControl->CreateWindowRoutine(hInstance,icon);//hinstance,icon,proc    proc == NULLだとCMainControl内部の標準callBack

		CCommonSystemFile* lpSystemFile = m_mainControl->GetSystemFile();
		SIZE sz = m_mainControl->GetWindowSize();
		int bpp = m_mainControl->GetBpp();
		m_game = new CGame(hWnd,hInstance,lpSystemFile,sz.cx,sz.cy,bpp);
		m_mainControl->Game(m_game);
	}

	ENDDELETECLASS(m_game);
	ENDDELETECLASS(m_mainControl);

	CCurrentDirControl::RestoreCurrent();

	return 0;
}

/*_*/

