object ServerContrRemPort: TServerContrRemPort
  OldCreateOrder = False
  DisplayName = 'ServerContrRemPort'
  OnExecute = ServiceExecute
  Left = 801
  Top = 338
  Height = 150
  Width = 215
  object ServerSocket1: TServerSocket
    Active = True
    Port = 8080
    ServerType = stNonBlocking
    OnClientRead = ServerSocket1ClientRead
    Left = 32
    Top = 16
  end
end
