object FLoadingScreen: TFLoadingScreen
  Left = 379
  Top = 379
  BorderStyle = bsSingle
  Caption = 'GO'
  ClientHeight = 59
  ClientWidth = 545
  Color = clBtnFace
  Font.Charset = DEFAULT_CHARSET
  Font.Color = clWindowText
  Font.Height = -11
  Font.Name = 'MS Sans Serif'
  Font.Style = []
  OldCreateOrder = False
  Position = poScreenCenter
  OnCreate = FormCreate
  OnDestroy = FormDestroy
  PixelsPerInch = 96
  TextHeight = 13
  object ProgressBar1: TProgressBar
    Left = 8
    Top = 8
    Width = 529
    Height = 25
    Min = 0
    Max = 100
    TabOrder = 0
  end
  object StatusBar1: TStatusBar
    Left = 0
    Top = 40
    Width = 545
    Height = 19
    Panels = <>
    SimplePanel = True
  end
  object Timer1: TTimer
    Interval = 100
    OnTimer = Timer1Timer
    Left = 32
    Top = 8
  end
end
