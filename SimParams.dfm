object FSimParams: TFSimParams
  Left = 342
  Top = 162
  Width = 647
  Height = 437
  BorderIcons = [biSystemMenu, biMinimize]
  Caption = 'Simulationsparameter'
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  OnClose = FormClose
  OnDestroy = FormDestroy
  OnShow = FormShow
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 328
    Top = 24
    Width = 68
    Height = 13
    Caption = 'Beschreibung:'
  end
  object Label2: TLabel
    Left = 355
    Top = 56
    Width = 246
    Height = 57
    AutoSize = False
    WordWrap = True
  end
  object Label3: TLabel
    Left = 336
    Top = 176
    Width = 26
    Height = 13
    Caption = 'Wert:'
  end
  object OK: TButton
    Left = 400
    Top = 336
    Width = 75
    Height = 25
    Caption = 'OK'
    TabOrder = 0
    OnClick = OKClick
  end
  object Button1: TButton
    Left = 496
    Top = 336
    Width = 75
    Height = 25
    Caption = 'Abbrechen'
    TabOrder = 1
    OnClick = Button1Click
  end
  object ListBox1: TListBox
    Left = 16
    Top = 16
    Width = 281
    Height = 369
    ItemHeight = 13
    TabOrder = 2
    OnClick = ListBox1Click
  end
  object Edit1: TEdit
    Left = 360
    Top = 208
    Width = 249
    Height = 21
    TabOrder = 3
    OnChange = Edit1Change
  end
end
