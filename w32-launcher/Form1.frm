VERSION 5.00
Begin VB.Form Form1 
   Caption         =   "PEBL Launcher"
   ClientHeight    =   7485
   ClientLeft      =   1695
   ClientTop       =   2370
   ClientWidth     =   8370
   Icon            =   "Form1.frx":0000
   LinkTopic       =   "Form1"
   ScaleHeight     =   7485
   ScaleWidth      =   8370
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
      Height          =   495
      Index           =   0
      Left            =   2040
      TabIndex        =   5
      Text            =   "Text1"
      Top             =   2040
      Visible         =   0   'False
      Width           =   2055
   End
   Begin VB.CommandButton Command2 
      Caption         =   "Cancel"
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
      Height          =   3600
      Left            =   4200
      MultiSelect     =   2  'Extended
      Pattern         =   "*.pbl"
      TabIndex        =   1
      Top             =   3720
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

Private Sub Command1_Click()

 execute = """" + PEBL_Executable + """"
 
 'add any command-line arguments
  For i = 1 To NUMBER
    If Text1(i) <> "" Then
      execute = execute + " -v " + Text1(i)
    End If
   Next i
   
'add any filenames
For j = 0 To File1.ListCount - 1
   
   If File1.Selected(j) Then
    execute = execute + " " + """" + File1.Path + "\" + File1.List(j) + """"
   End If
   
Next j
Debug.Print Check1

'add fullscreen mode
If Check1 Then
 execute = execute + " --fullscreen "
Else
 execute = execute + " --windowed "
End If

'add display size
execute = execute + " --display "
Select Case Combo1.ListIndex
Case 1:
 execute = execute + " 512x384 "
Case 2:
 execute = execute + " 640x480 "
Case 3:
 execute = execute + " 800x600 "

Case 4:
 execute = execute + " 960x720 "
Case 5:
 execute = execute + " 1024x786 "
Case 6:
 execute = execute + " 1152x864 "
Case 7:
 execute = execute + " 1280x1024 "

Case Else:
execute = execute + " 800x600 "
End Select

'add color depth
execute = execute + " --depth "
Select Case Combo2.ListIndex
Case 1:
 execute = execute + " 15 "
Case 2:
 execute = execute + " 16 "
Case 3:
 execute = execute + " 24 "

Case 4:
 execute = execute + " 32 "

Case Else:
execute = execute + " 16 "
End Select

Debug.Print execute

 
 
 Shell (execute)
 End
 
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
Open "pebl-init.txt" For Input As #1



'The first line is the executable location
Input #1, PEBL_Executable
Debug.Print ("PEBL Executable: [" + PEBL_Executable + "]")

Input #1, myPathname
Debug.Print ("Pathname: [" + myPathname + "]")

Line Input #1, myfilenamelist
Debug.Print ("filename: [" + myfilenamelist + "]")

MyFilenames = Split(myfilenamelist)
'myfilenames is now an array, each containing a filename.
 For j = 0 To UBound(MyFilenames)
   MyFilenames(j) = Mid$(MyFilenames(j), 2, Len(MyFilenames(j)) - 2)
   Debug.Print MyFilenames(j)
   
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
 
 toplabel = toplabel + 800
 
  Label1(NUMBER).Visible = True
  Text1(NUMBER).Visible = True
  
  Label1(NUMBER).Caption = namevaluearray(0)
  Text1(NUMBER).Text = namevaluearray(1)
 
 
 Debug.Print "Stuff: [" + namevalue + "]"
 Debug.Print namevaluearray(0)
 Debug.Print namevaluearray(1)
 
Wend

End Sub
