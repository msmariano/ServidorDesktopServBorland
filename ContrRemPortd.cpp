//---------------------------------------------------------------------------
#include "ContrRemPortd.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"

TServerContrRemPort *ServerContrRemPort;
//---------------------------------------------------------------------------
__fastcall TServerContrRemPort::TServerContrRemPort(TComponent* Owner)
	: TService(Owner)
{
}

TServiceController __fastcall TServerContrRemPort::GetServiceController(void)
{
	return (TServiceController) ServiceController;
}

void __stdcall ServiceController(unsigned CtrlCode)
{
	ServerContrRemPort->Controller(CtrlCode);
}
//---------------------------------------------------------------------------





////////////////////////

//---------------------------------------------------------------------------

#include <vcl.h>
#pragma hdrstop

#include "Unit1.h"
//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
        : TForm(Owner)
{
}
//---------------------------------------------------------------------------


//---------------------------------------------------------------------------

void __fastcall TServerContrRemPort::ServerSocket1ClientRead(
      TObject *Sender, TCustomWinSocket *Socket)
{

        String S;
        S = Socket->ReceiveText();



        if( S.Pos("Referer: http://localhost:8080/?act=On") > 1   )
        {
                nRetBytesWritten = 0;
  WriteFile(
                hSerial,
                "Act",
                sizeof("Act"),
                &nRetBytesWritten,
                NULL );

                WriteFile(
                hSerial,
                "\n",
                1,
                &nRetBytesWritten,
                NULL );
        }



        Memo1->Lines->Add(S);

        Socket->SendText("Teste\n\n");
        Memo1->Lines->SaveToFile("res.txt");
        //Memo1->Lines->Clear();
        Socket->Close();

}
//---------------------------------------------------------------------------


/*

#include "ColetorSerial.h"

void TColetorSerial::funIniciar()
{
    String parametros;
    DCB dcb = {0};

    parametros.sprintf("baud=%s parity=%s data=%s stop=%s", config.baudRate, config.parity, config.byteSize, config.stopBits);
    dcb.DCBlength = sizeof(dcb);

    if((hSerial = CreateFile(config.porta.c_str(), GENERIC_READ | GENERIC_WRITE,
			       0,0,OPEN_EXISTING,NULL,0)) == INVALID_HANDLE_VALUE)
    {
        portaAberta = false;
        return;
    }

    if(!GetCommState(hSerial,&dcb))
	{
		portaAberta = false;
        return;
	}

    if(!BuildCommDCB(parametros.c_str(),&dcb))
	{
        portaAberta = false;
		return;
	}

    if(!SetCommState(hSerial,&dcb))
	{
        portaAberta = false;
		return;
	}

    portaAberta = true;
}

void TColetorSerial::funParar()
{
    CloseHandle(hSerial);
    portaAberta = false;
}

void TColetorSerial::Executar()
{
    String textoRec;
    String bilhete;
    while(portaAberta)
    {
        char dados[1024];
        DWORD nRead;

        memset(dados,0,sizeof(dados));
        if(!ReadFile(hSerial,dados,sizeof(dados)-1,&nRead,0))
        {
            portaAberta = false;
        }

        textoRec += dados;

        try
        {
            while((textoRec.Pos(config.lineEnd)) > 0)
            {
                bilhete = textoRec.SubString(1,textoRec.Pos(config.lineEnd)-config.lineEnd.Length());
                textoRec = textoRec.SubString(textoRec.Pos(config.lineEnd)+1, textoRec.Length());
                TratarBilhete(bilhete);
            }
        }
        catch(Exception&e)
        {
        }
    }
}

void TColetorSerial::SetConfig(TConfigSerial conf)
{
    config = conf;
}

TColetorSerial::TColetorSerial()
{
    portaAberta = false;
}

TColetorSerial::~TColetorSerial()
{
}
*/
void __fastcall TForm1::Button1Click(TObject *Sender)
{
String parametros;
    memset(&dcb,0,sizeof(dcb));

    parametros = "baud=9600 parity=N data=8 stop=2";
    dcb.DCBlength = sizeof(dcb);

    if((hSerial = CreateFile("COM3", GENERIC_READ | GENERIC_WRITE,
			       0,0,OPEN_EXISTING,NULL,0)) == INVALID_HANDLE_VALUE)
    {
        ShowMessage("Falhou ao Iniciar COM3!");
        
    }
     if(!GetCommState(hSerial,&dcb))
	{
		ShowMessage("Falhou ao Iniciar COM3!(GetCommState)");
	}

    if(!BuildCommDCB(parametros.c_str(),&dcb))
	{
        ShowMessage("Falhou ao Iniciar COM3!(BuildCommDCB)");
	}

    if(!SetCommState(hSerial,&dcb))
	{
         ShowMessage("Falhou ao Iniciar COM3!SetCommState");
	}


        bConnected = true;


}
//---------------------------------------------------------------------------
void __fastcall TForm1::Button2Click(TObject *Sender)
{


      nRetBytesWritten = 0;
  WriteFile(
                hSerial,
                Edit1->Text.c_str(),
                Edit1->Text.Length(),
                &nRetBytesWritten,
                NULL );

                WriteFile(
                hSerial,
                "\n",
                1,
                &nRetBytesWritten,
                NULL );



}
//---------------------------------------------------------------------------
void __fastcall TForm1::ServerSocket1ClientRead(TObject *Sender,
      TCustomWinSocket *Socket)
{

/*



*/



        String S;

        S = Socket->ReceiveText();



        if( S.Pos("Referer: http://localhost:8080/?act=On") > 1   )
        {
                nRetBytesWritten = 0;
  WriteFile(
                hSerial,
                "Act",
                sizeof("Act"),
                &nRetBytesWritten,
                NULL );

                WriteFile(
                hSerial,
                "\n",
                1,
                &nRetBytesWritten,
                NULL );
        }



        Memo1->Lines->Add(S);

        Socket->SendText("Teste\n\n");
        Memo1->Lines->SaveToFile("res.txt");
        //Memo1->Lines->Clear();
        Socket->Close();
}
//---------------------------------------------------------------------------

void __fastcall TForm1::FormCreate(TObject *Sender)
{
  bConnected = false;
}
//---------------------------------------------------------------------------

void __fastcall TForm1::Timer1Timer(TObject *Sender)
{
        if(bConnected)
        {

         String S;
         S =  "Hour"+TimeToStr(Now());


          nRetBytesWritten = 0;
  WriteFile(
                hSerial,
                S.c_str(),
                S.Length(),
                &nRetBytesWritten,
                NULL );

                WriteFile(
                hSerial,
                "\n",
                1,
                &nRetBytesWritten,
                NULL );


        }
}
//---------------------------------------------------------------------------



void __fastcall TServerContrRemPort::ServiceExecute(TService *Sender)
{
        String parametros;
    memset(&dcb,0,sizeof(dcb));

    parametros = "baud=9600 parity=N data=8 stop=2";
    dcb.DCBlength = sizeof(dcb);

    if((hSerial = CreateFile("COM3", GENERIC_READ | GENERIC_WRITE,
			       0,0,OPEN_EXISTING,NULL,0)) == INVALID_HANDLE_VALUE)
    {
        ShowMessage("Falhou ao Iniciar COM3!");
        
    }
     if(!GetCommState(hSerial,&dcb))
	{
		ShowMessage("Falhou ao Iniciar COM3!(GetCommState)");
	}

    if(!BuildCommDCB(parametros.c_str(),&dcb))
	{
        ShowMessage("Falhou ao Iniciar COM3!(BuildCommDCB)");
	}

    if(!SetCommState(hSerial,&dcb))
	{
         ShowMessage("Falhou ao Iniciar COM3!SetCommState");
	}


        bConnected = true;        
}
//---------------------------------------------------------------------------

