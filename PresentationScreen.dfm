object FPresentationScreen: TFPresentationScreen
  Left = 809
  Top = 202
  BorderStyle = bsDialog
  Caption = 'Pr'#228'sentationen'
  ClientHeight = 494
  ClientWidth = 174
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  FormStyle = fsStayOnTop
  OldCreateOrder = False
  PixelsPerInch = 96
  TextHeight = 13
  object Label1: TLabel
    Left = 8
    Top = 232
    Width = 33
    Height = 13
    Caption = 'Aktion:'
  end
  object Label2: TLabel
    Left = 8
    Top = 248
    Width = 161
    Height = 49
    AutoSize = False
    WordWrap = True
  end
  object ListBox1: TListBox
    Left = 8
    Top = 8
    Width = 121
    Height = 217
    ItemHeight = 13
    TabOrder = 0
    OnClick = ListBox1Click
  end
  object Button1: TButton
    Left = 32
    Top = 336
    Width = 121
    Height = 25
    Caption = 'Aufzeichnung starten'
    TabOrder = 1
    OnClick = Button1Click
  end
  object Button2: TButton
    Left = 32
    Top = 368
    Width = 121
    Height = 25
    Caption = 'Speichern'
    TabOrder = 2
    OnClick = Button2Click
  end
  object Button3: TButton
    Left = 32
    Top = 400
    Width = 121
    Height = 25
    Caption = 'Laden'
    TabOrder = 3
    OnClick = Button3Click
  end
  object Button4: TButton
    Left = 32
    Top = 464
    Width = 121
    Height = 25
    Caption = 'Abspielen'
    TabOrder = 4
    OnClick = Button4Click
  end
  object Button6: TButton
    Left = 144
    Top = 40
    Width = 25
    Height = 25
    Caption = 'X'
    TabOrder = 5
    OnClick = Button6Click
  end
  object BitBtn1: TBitBtn
    Left = 144
    Top = 8
    Width = 25
    Height = 25
    TabOrder = 6
    OnClick = BitBtn1Click
    Glyph.Data = {
      76010000424D760100000000000036000000280000000A0000000A0000000100
      18000000000040010000120B0000120B00000000000000000000FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
      FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
      FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
      FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFF0000000000FFFFFF
      FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFF0000000000000000000000
      FFFFFFFFFFFF000000000000FFFFFFFFFFFF0000000000000000FFFFFF000000
      000000FFFFFF000000000000FFFFFF000000000000FFFFFF0000FFFFFFFFFFFF
      000000000000000000000000000000000000FFFFFFFFFFFF0000FFFFFFFFFFFF
      FFFFFF000000000000000000000000FFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
      FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFF0000}
  end
  object BitBtn2: TBitBtn
    Left = 144
    Top = 72
    Width = 25
    Height = 25
    TabOrder = 7
    OnClick = BitBtn2Click
    Glyph.Data = {
      76010000424D760100000000000036000000280000000A0000000A0000000100
      18000000000040010000120B0000120B00000000000000000000FFFFFFFFFFFF
      FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
      FFFFFF000000000000000000000000FFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
      000000000000000000000000000000000000FFFFFFFFFFFF0000FFFFFF000000
      000000FFFFFF000000000000FFFFFF000000000000FFFFFF0000000000000000
      FFFFFFFFFFFF000000000000FFFFFFFFFFFF0000000000000000000000FFFFFF
      FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFF0000000000FFFFFFFFFFFF
      FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
      FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
      FFFFFFFFFFFF000000000000FFFFFFFFFFFFFFFFFFFFFFFF0000FFFFFFFFFFFF
      FFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFFF0000}
  end
  object Button5: TButton
    Left = 144
    Top = 120
    Width = 25
    Height = 25
    Caption = 'H'
    TabOrder = 8
    OnClick = Button5Click
  end
  object Button7: TButton
    Left = 32
    Top = 432
    Width = 121
    Height = 25
    Caption = 'Neu'
    TabOrder = 9
    OnClick = Button7Click
  end
  object CheckBox1: TCheckBox
    Left = 16
    Top = 312
    Width = 145
    Height = 17
    Caption = 'Positionen sind wichtig'
    Checked = True
    State = cbChecked
    TabOrder = 10
  end
  object SaveDialog1: TSaveDialog
    DefaultExt = '.lua'
    Filter = 'Pr'#228'sentationen|*.lua'
    Options = [ofOverwritePrompt, ofHideReadOnly, ofEnableSizing]
    Top = 360
  end
  object OpenDialog1: TOpenDialog
    Filter = 'Pr'#228'sentationen|*.lua'
    Top = 392
  end
end
