#if !defined(EDITOR2)

#ifndef __EDITOR_HPP__
#define __EDITOR_HPP__
/*
editor.hpp

�������

*/

/* Revision: 1.05 21.07.2000 $ */

/*
Modify:
  21.07.2000 tran
    - �� ����� ��⮤�  - Bug22
  21.07.2000 tran
    ! GotoLine �⠫� ��� ࠭�� void � ���������� GoToPosition
  17.07.2000 OT
    + ���⮫���� ���� ��� ࠧࠡ��� "�����" ।����
  14.07.2000 tran
    ! �㭪�� GetRowCol ᤥ��� ��⮤�� �����
  05.07.2000 tran
    ! ������� ⨯ ������ � GoToLine() � 'void ' �� 'int'
      �����頥��� ���祭�� - �� �������, ��������� ���짮��⥫��
      �ᯮ������ ⮫쪮 � ����� ���� - � ��ࠡ�⪥ Alt-F8
  25.06.2000 SVS
    ! �����⮢�� Master Copy
    ! �뤥����� � ����⢥ ᠬ����⥫쭮�� �����
*/

class Editor:public ScreenObject
{
  private:
    void DisplayObject();
    void ShowEditor(int CurLineOnly);
    void ShowStatus();
    void DeleteString(struct EditList *DelPtr,int DeleteLast,int UndoLine);
    void InsertString();
    void Up();
    void Down();
    void ScrollDown();
    void ScrollUp();
    void Search(int Next);
    /* $ 05.07.2000 tran
       ! ������� ⨯ ������ � GoToLine() � 'void ' �� 'int'
       �����頥��� ���祭�� - �� �������, ��������� ���짮��⥫��
       �ᯮ������ ⮫쪮 � ����� ���� - � ��ࠡ�⪥ Alt-F8
    */
    /* $ 21.07.2000 tran
       GotoLine �⠫� ��� ࠭�� void
       � ���������� GoToPosition
       */

    void GoToLine(int Line);
    void GoToPosition();
    /* tran 21.07.2000 $ */

    /* tran 05.07.2000 $ */
    int  CalcDistance(struct EditList *From,struct EditList *To,int MaxDist);
    void Paste();
    void Copy(int Append);
    void DeleteBlock();
    void UnmarkBlock();
    void ChangeEditKeyBar();
    void AddUndoData(char *Str,int StrNum,int StrPos,int Type);
    void Undo();
    void SelectAll();
    void SetStringsTable();
    void BlockLeft();
    void BlockRight();
    void DeleteVBlock();
    void VCopy(int Append);
    void VPaste(char *ClipText);
    void VBlockShift(int Left);
    struct EditList * GetStringByNumber(int DestLine);

    KeyBar *EditKeyBar;
    struct EditList *TopList,*EndList,*TopScreen,*CurLine;
    struct EditorUndoData UndoData[64];
    int UndoDataPos;
    int UndoOverflow;
    int UndoSavePos;
    int LastChangeStrPos;
    char FileName[NM];
    int NumLastLine,NumLine;
    int Modified;
    int WasChanged;
    int Overtype;
    int DisableOut;
    int Pasting;
    int MarkingBlock;
    char GlobalEOL[10];
    struct EditList *BlockStart;
    int BlockStartLine;

    struct EditList *VBlockStart;
    int VBlockX;
    int VBlockSizeX;
    int VBlockY;
    int VBlockSizeY;
    int MarkingVBlock;

    int DisableUndo;
    int NewUndo;
    int LockMode;
    int BlockUndo;

    int MaxRightPos;

    unsigned char LastSearchStr[256];
    int LastSearchCase,LastSearchReverse;

    struct CharTableSet TableSet;
    int UseDecodeTable,TableNum,AnsiText;
    int StartLine,StartChar;

    int TableChangedByUser;

    char Title[512];
    char PluginData[NM*2];

    char PluginTitle[512];

    long SavePosLine[10];
    long SavePosCursor[10];
    long SavePosScreenLine[10];
    long SavePosLeftPos[10];

    int EditorID;
    bool OpenFailed;

    FileEditor *HostFileEditor;
  public:
    Editor();
    ~Editor();
    int ReadFile(char *Name,int &UserBreak);
    int SaveFile(char *Name,int Ask,int TextFormat);
    int ProcessKey(int Key);
    int ProcessMouse(MOUSE_EVENT_RECORD *MouseEvent);
    void SetEditKeyBar(KeyBar *EditKeyBar);
    void KeepInitParameters();
    void SetStartPos(int LineNum,int CharNum);
    int IsFileModified();
    int IsFileChanged();
    void SetTitle(char *Title);
    long GetCurPos();
    void SetPluginData(char *PluginData);
    int EditorControl(int Command,void *Param);
    int ProcessEditorInput(INPUT_RECORD *Rec);
    void SetHostFileEditor(FileEditor *Editor) {HostFileEditor=Editor;};
    static int IsShiftKey(int Key);
    static void SetReplaceMode(int Mode);

    /* $ tran 14.07.2000
      + goto to percent support */
    void GetRowCol(char *argv,int *row,int *col);
    /* tran 14.07.2000 $ */

    /* $ 21.07.2000 tran
       �� ����� ��⮤�*/
    int  GetLineCurPos();
    void BeginVBlockMarking();
    void AdjustVBlock(int PrevX);
    /* tran 21.07.2000 $ */
};

struct EditList
{
  struct EditList *Prev;
  struct EditList *Next;
  Edit EditLine;
};

#endif // __EDITOR_HPP__
#endif //defined(EDITOR2)
