VERSION 5.00
Object = "{3B7C8863-D78F-101B-B9B5-04021C009402}#1.2#0"; "RICHTX32.OCX"
Object = "{0D452EE1-E08F-101A-852E-02608C4D0BB4}#2.0#0"; "FM20.DLL"
Begin VB.Form Form1 
   Caption         =   "PEBL Launcher"
   ClientHeight    =   9015
   ClientLeft      =   17805
   ClientTop       =   975
   ClientWidth     =   11325
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   0
   ScaleWidth      =   0
   Begin VB.ComboBox Combo2 
      Height          =   315
      ItemData        =   "Form1.frx":08CA
      Left            =   1920
      List            =   "Form1.frx":08DA
      Style           =   2  'Dropdown List
      TabIndex        =   9
      Top             =   1440
      Width           =   2175
   End
   Begin VB.ComboBox Combo1 
      Height          =   315
      ItemData        =   "Form1.frx":08FE
      Left            =   1920
      List            =   "Form1.frx":0917
      Style           =   2  'Dropdown List
      TabIndex        =   8
      Top             =   960
      Width           =   2175
   End
   Begin VB.CheckBox Check1 
      Caption         =   "Fullscreen"
      Height          =   255
      Left            =   360
      TabIndex        =   7
      Top             =   960
      Value           =   1  'Checked
      Width           =   1215
   End
   Begin VB.TextBox Text1 
      Height          =   375
      Index           =   0
      Left            =   2040
      TabIndex        =   5
      Text            =   "Text1"
      Top             =   2040
      Visible         =   0   'False
      Width           =   2055
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Quit"
      Height          =   735
      Left            =   1920
      TabIndex        =   4
      Top             =   120
      Width           =   1695
   End
   Begin VB.DirListBox Dir1 
      Height          =   2790
      Left            =   4200
      TabIndex        =   3
      Top             =   840
      Width           =   3255
   End
   Begin VB.DriveListBox Drive1 
      Height          =   315
      Left            =   4200
      TabIndex        =   2
      Top             =   360
      Width           =   3255
   End
   Begin VB.FileListBox File1 
      Archive         =   0   'False
      Height          =   3210
      Left            =   7680
      MultiSelect     =   2  'Extended
      Pattern         =   "*.pbl"
      TabIndex        =   1
      Top             =   360
      Width           =   3255
   End
   Begin VB.CommandButton Command1 
      Caption         =   "Run PEBL Script"
      Height          =   735
      Left            =   240
      TabIndex        =   0
      Top             =   120
      Width           =   1455
   End
   Begin RichTextLib.RichTextBox RichTextBox1 
      Height          =   4455
      Index           =   1
      Left            =   600
      TabIndex        =   11
      Top             =   4200
      Visible         =   0   'False
      Width           =   10215
      _ExtentX        =   18018
      _ExtentY        =   7858
      _Version        =   393217
      Enabled         =   -1  'True
      ScrollBars      =   3
      TextRTF         =   $"Form1.frx":095E
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Lucida Console"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin RichTextLib.RichTextBox RichTextBox1 
      Height          =   4455
      Index           =   0
      Left            =   600
      TabIndex        =   10
      Top             =   4200
      Visible         =   0   'False
      Width           =   10215
      _ExtentX        =   18018
      _ExtentY        =   7858
      _Version        =   393217
      ScrollBars      =   3
      TextRTF         =   $"Form1.frx":09EA
      BeginProperty Font {0BE35203-8F91-11CE-9DE3-00AA004BB851} 
         Name            =   "Lucida Console"
         Size            =   8.25
         Charset         =   0
         Weight          =   400
         Underline       =   0   'False
         Italic          =   0   'False
         Strikethrough   =   0   'False
      EndProperty
   End
   Begin VB.Label Label2 
      Caption         =   "Launcher for PEBL 0.06"
      Height          =   255
      Left            =   9120
      TabIndex        =   13
      Top             =   0
      Width           =   2055
   End
   Begin MSForms.TabStrip TabStrip1 
      Height          =   5175
      Left            =   240
      TabIndex        =   12
      Top             =   3720
      Width           =   10815
      ListIndex       =   0
      Size            =   "19076;9128"
      Items           =   "Tab1;Tab2;"
      TipStrings      =   ";;"
      Names           =   "Tab1;Tab2;"
      NewVersion      =   -1  'True
      TabsAllocated   =   2
      Tags            =   ";;"
      TabData         =   2
      Accelerator     =   ";;"
      FontHeight      =   165
      FontCharSet     =   0
      FontPitchAndFamily=   2
      TabState        =   "3;3"
   End
   Begin VB.Label Label1 
      Caption         =   "Label1"
      Height          =   375
      Index           =   0
      Left            =   240
      TabIndex        =   6
      Top             =   2040
      Visible         =   0   'False
      Width           =   1695
   End
End
Attribute VB_Name = "Form1"
Attribute VB_GlobalNameSpace = False
Attribute VB_Creatable = False
Attribute VB_PredeclaredId = True
Attribute VB_Exposed = False
Dim myPathname
Dim PEBL_Executable
Dim MyFilenames
Dim NUMBER
Private SelectedTab As Integer

Private Sub Command1_Click()

 Execute = """" + PEBL_Executable + """"
 
 'add any command-line arguments
  For i = 1 To NUMBER
    If Text1(i) <> "" Then
      Execute = Execute + " -v " + Text1(i)
    End If
   Next i
   
'add any filenames
For j = 0 To File1.ListCount - 1
   
   If File1.Selected(j) Then
    Execute = Execute + " " + """" + File1.Path + "\" + File1.List(j) + """"
   End If
   
Next j
Debug.Print Check1

'add fullscreen mode
If Check1 Then
 Execute = Execute + " --fullscreen "
Else
 Execute = Execute + " --windowed "
End If

'add display size
Execute = Execute + " --display "
Select Case Combo1.ListIndex
Case 1:
 Execute = Execute + " 512x384 "
Case 2:
 Execute = Execute + " 640x480 "
Case 3:
 Execute = Execute + " 800x600 "

Case 4:
 Execute = Execute + " 960x720 "
Case 5:
 Execute = Execute + " 1024x786 "
Case 6:
 Execute = Execute + " 1152x864 "
Case 7:
 Execute = Execute + " 1280x1024 "

Case Else:
Execute = Execute + " 800x600 "
End Select

'add color depth
Execute = Execute + " --depth "
Select Case Combo2.ListIndex
Case 1:
 Execute = Execute + " 15 "
Case 2:
 Execute = Execute + " 16 "
Case 3:
 Execute = Execute + " 24 "

Case 4:
 Execute = Execute + " 32 "

Case Else:
Execute = Execute + " 16 "
End Select


 
 'execute the command in a separate process, waiting for it to return.
 ExecCmd (Execute)
 
 reload
 
End Sub
Private Sub reload()

 Set fs = CreateObject("Scripting.FileSystemObject")
 
 If fs.fileexists(File1.Path & "\stdout.txt") Then
   RichTextBox1(0).LoadFile File1.Path & "\stdout.txt"
  Else
   RichTextBox1(0).Text = "Failed to load [" & File1.Path & "\stdout.txt]."
 End If
 
 If fs.fileexists(File1.Path & "\stderr.txt") Then
   RichTextBox1(1).LoadFile File1.Path & "\stderr.txt"
  Else
   RichTextBox1(1).Text = "Failed to load " & File1.Path & "\stderr.txt]."
 End If
End Sub

Private Sub Command2_Click()
 End
End Sub

Private Sub Dir1_Change()
File1.Path = Dir1.Path
End Sub

Private Sub Drive1_Change()
Dir1.Path = Drive1.Drive
End Sub

Private Sub Form_Load()

Combo1.ListIndex = 2
Combo2.ListIndex = 2
'Try to find the file pebl-init.txt.  If it doesn't exist,
'no worries
If Len(Dir$("pebl-init.txt")) = 0 Then
  MsgBox ("Unable to find file pebl-init.txt in current directory.")
  End
Else
 Open "pebl-init.txt" For Input As #1
 'The first line is the executable location
 Input #1, PEBL_Executable
 'Debug.Print ("PEBL Executable: [" + PEBL_Executable + "]")

 Input #1, myPathname
 'Debug.Print ("Pathname: [" + myPathname + "]")

 Line Input #1, myfilenamelist
 'Debug.Print ("filename: [" + myfilenamelist + "]")
End If


MyFilenames = Split(myfilenamelist)
'myfilenames is now an array, each containing a filename.
 For j = 0 To UBound(MyFilenames)
   MyFilenames(j) = Mid$(MyFilenames(j), 2, Len(MyFilenames(j)) - 2)
   'Debug.Print MyFilenames(j)
   
 Next j
 

'Set the directory & file selector
 Dir1.Path = myPathname
 
'Now, go through the file1 selector list, selecting
'any entries listed.
For i = 0 To File1.ListCount
   
   found = False
   For j = 0 To UBound(MyFilenames)
         Debug.Print File1.List(i) + "  " + MyFilenames(j)
         If File1.List(i) = MyFilenames(j) Then
           File1.Selected(i) = True
         End If
   Next j
Next i

NUMBER = 0
toplabel = 1800
While Not EOF(1)

 NUMBER = NUMBER + 1
 
 'Resize the control array:
 Load Label1(NUMBER)
 Load Text1(NUMBER)
 
 
 'Get the label and initial value
 Input #1, namevalue
 namevaluearray = Split(namevalue, "|")
 
 Label1(NUMBER).Top = toplabel
 Text1(NUMBER).Top = toplabel
 
 toplabel = toplabel + 600
 
  Label1(NUMBER).Visible = True
  Text1(NUMBER).Visible = True
  
  Label1(NUMBER).Caption = namevaluearray(0)
  Text1(NUMBER).Text = namevaluearray(1)
 
 
 Debug.Print "Stuff: [" + namevalue + "]"
 Debug.Print namevaluearray(0)
 Debug.Print namevaluearray(1)
 
Wend
TabStrip1.Tabs.Clear
TabStrip1.Tabs.Add "User Output", "User Output (stdout.txt)"
TabStrip1.Tabs.Add "Warnings and Errors", "Warnings and Errors (stderr.txt)"


RichTextBox1(0).Text = ""
RichTextBox1(1).Text = ""
RichTextBox1(0).Visible = True
SelectedTab = 0

End Sub


Private Sub TabStrip1_Change()

clicked = TabStrip1.SelectedItem.Index
If (clicked = SelectedTab) Then Exit Sub

RichTextBox1(clicked).Visible = True
RichTextBox1(1 - clicked).Visible = False
SelectedTab = clicked

End Sub

