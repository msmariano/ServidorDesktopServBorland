//---------------------------------------------------------------------------
#ifndef ContrRemPortdH
#define ContrRemPortdH
//---------------------------------------------------------------------------
#include <SysUtils.hpp>
#include <Classes.hpp>
#include <SvcMgr.hpp>
#include <vcl.h>
#include <ScktComp.hpp>
//---------------------------------------------------------------------------
class TServerContrRemPort : public TService
{
__published:    // IDE-managed Components
        TServerSocket *ServerSocket1;
        void __fastcall ServerSocket1ClientRead(TObject *Sender,
          TCustomWinSocket *Socket);
        void __fastcall ServiceExecute(TService *Sender);
private:        // User declarations
public:         // User declarations
	__fastcall TServerContrRemPort(TComponent* Owner);
	TServiceController __fastcall GetServiceController(void);

	friend void __stdcall ServiceController(unsigned CtrlCode);
};
//---------------------------------------------------------------------------
extern PACKAGE TServerContrRemPort *ServerContrRemPort;
//---------------------------------------------------------------------------
#endif
