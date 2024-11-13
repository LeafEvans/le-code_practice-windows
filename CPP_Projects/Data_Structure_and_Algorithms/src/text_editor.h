#ifndef _TEXT_EDITOR_H_  // 防止重复包含头文件的宏定义
#define _TEXT_EDITOR_H_

#include "char_string.h"  // 包含字符字符串处理的头文件
#include "db_lk_list.h"   // 包含双向链表处理的头文件

#ifdef _WIN32
#pragma warning(disable : 4996)
#include <conio.h>    // Windows下控制台输入输出的头文件
#include <windows.h>  // Windows API的头文件
#elif defined(__gnu_linux__)
#include <fcntl.h>      // 提供文件控制选项
#include <sys/ioctl.h>  // 用于I/O控制操作
#include <termios.h>    // 提供终端I/O接口
#include <unistd.h>     // 提供POSIX操作系统API

#endif  // _WIN32

#include <algorithm>  // 提供STL算法库
#include <cstdio>     // 提供C标准输入输出库
#include <cstdlib>    // 提供C标准库函数
#include <cstring>    // 提供C字符串处理函数

typedef struct tagWinSize {
  int nRows;  // 窗口的行数
  int nCols;  // 窗口的列数
} WinSize;

inline WinSize GetWinSize() {
  WinSize wsWinSize;
  wsWinSize.nCols = 80;  // 默认列数
  wsWinSize.nRows = 30;  // 默认行数

#ifdef _WIN32
  // 获取Windows控制台的屏幕缓冲区信息
  CONSOLE_SCREEN_BUFFER_INFO csbiConsoleInfo;
  if (GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE),
                                 &csbiConsoleInfo)) {
    wsWinSize.nRows = csbiConsoleInfo.srWindow.Bottom -
                      csbiConsoleInfo.srWindow.Top + 1;  // 计算行数
    wsWinSize.nCols = csbiConsoleInfo.srWindow.Right -
                      csbiConsoleInfo.srWindow.Left + 1;  // 计算列数
  }
#elif defined(__gnu_linux__)
  // 打开终端设备文件以获取窗口大小
  struct winsize wsTermSize;
  int nFileDesc = open("/dev/tty", O_RDONLY);

  if (nFileDesc >= 0) {
    // 使用ioctl获取终端窗口大小
    if (ioctl(nFileDesc, TIOCGWINSZ, &wsTermSize) >= 0) {
      wsWinSize.nRows = wsTermSize.ws_row;  // 设置行数
      wsWinSize.nCols = wsTermSize.ws_col;  // 设置列数
    }
    close(nFileDesc);  // 关闭文件描述符以释放资源
  }
#endif  // _WIN32

  return wsWinSize;  // 返回计算得到的窗口大小
}

class TextEditor : public DbLkList<CharString*> {
 public:
  TextEditor();
  ~TextEditor();
  void Run(const CharString& csFileName);   // 启动文本编辑器
  bool Load(const CharString& csFileName);  // 加载文件

 private:
  void Clear();   // 清空内容
  void Edit();    // 进入编辑模式
  bool GetCmd();  // 获取用户输入的命令
  // 处理编辑命令，如光标移动
  bool OnEditCmd(char chCtrl, CharString* pcsCurLn);
  bool Save(const CharString& csFileName);  // 保存到文件
  unsigned short GetStdCh(char& chCtrl);    // 获取一个字符且不回显
  void Help(const CharString& csCmd);       // 显示帮助信息
  void ShowMsg(const CharString& csMsg, int nBgColor = 41);  // 显示提示信息
  void PrintStrs(bool bClearAll = false);            // 打印所有字符串
  void PrintLn(CharString* pcsCurLn, int nYCurPos);  // 打印单行
                                                     // 移动光标位置
  void MoveCur(int nYCurPos, int nXCurPos, bool bPrintLnNum = true);
  void CheckZhCur(CharString* pcsCurLn);  // 检查光标在汉字中的位置
  bool MoveYCur(int nOffset, int nWinRows);  // 垂直移动光标
  // 查找字符串模式
  bool FindPatStr(const CharString& csPat, int nRow, int nCol);
  bool GotoLn(const CharString& csTarLn);     // 跳转到指定行
  int GetTopLn(int nWinRows, bool& bRedraw);  // 获取当前窗口顶行行号

  int m_nXCurPos;  // 当前光标的X坐标
  int m_nYCurPos;  // 当前光标的Y坐标
  int m_nTopLn;    // 当前显示的顶行行号
  bool m_bReplaceMode;  // 是否处于替换模式：false-插入模式, true-替换模式
  bool m_bEditMode;  // 是否处于编辑模式：false-命令模式, true-编辑模式
  CharString m_csFileName;  // 当前编辑的文件名
  CharString m_csPat;       // 当前查找的模式字符串
};

inline TextEditor::TextEditor() {
  m_nXCurPos = 0;
  m_nYCurPos = 0;
  m_nTopLn = 0;
  m_bReplaceMode = false;
  m_bEditMode = false;
}

inline void TextEditor::Run(const CharString& csFileName) {}

inline bool TextEditor::Load(const CharString& csFileName) {
  if (csFileName.IsEmpty()) {
    ShowMsg(
        "Usage: l <filename> - The 'load' command requires a valid filename.");
    return false;
  }

  FILE* pFile = fopen(csFileName.ToCStr(), "rb");

  if (pFile == NULL) {
    CharString csMsg;
    csMsg.Format("File \"%s\" not found.", csFileName.ToCStr());
    ShowMsg(csMsg);
    return false;
  }

  fseek(pFile, 0, SEEK_END);
  int nFileLen = ftell(pFile);
  fseek(pFile, 0, SEEK_SET);

  char* pszBuffer = new char[nFileLen + 1];
  fread(pszBuffer, 1, nFileLen, pFile);
  fclose(pFile);

  pszBuffer[nFileLen] = '\0';

  char* pTailCh = strchr(pszBuffer, '\0');

  if (pTailCh - pszBuffer + 1 < nFileLen) {
    CharString csMsg;
    csMsg.Format("File \"%s\" is not a text file", csFileName.ToCStr());
    ShowMsg(csMsg);
    return false;
  }

  Clear();
  const char* pszCurLn = pszBuffer;
  char* pCurCh = pszBuffer;

  while (*pCurCh != '\0') {
    if (*pCurCh == '\n') {
      *pCurCh = '\0';
      AddTail(new CharString(pszCurLn));
      pszCurLn = pCurCh + 1;
    }
    ++pCurCh;
  }

  if (pCurCh < pszBuffer + nFileLen) {
    AddTail(new CharString(pszCurLn));
  }
  m_csFileName = csFileName;

  return true;
}

inline TextEditor::~TextEditor() {
  while (Length() > 0) {
    CharString* pcsDelStr;  // 指向待删除字符串的指针
    if (Delete(0, pcsDelStr)) {
      delete pcsDelStr;  // 释放字符串内存
    }
  }
  m_nYCurPos = 0;     // 重置Y坐标
  m_nXCurPos = 0;     // 重置X坐标
  m_nTopLn = 0;       // 重置顶行行号
  m_csFileName = "";  // 清空文件名
  m_csPat = "";       // 清空查找模式字符串
}

inline void TextEditor::Clear() {
  if (Length() > 0) {
    CharString* pcsDelStr;
    if (Delete(0, pcsDelStr)) {
      delete pcsDelStr;
    }
  }
  m_nYCurPos = 0;
  m_nXCurPos = 0;
  m_nTopLn = 0;
  m_csFileName = "";
  m_csPat = "";
}

inline void TextEditor::Edit() {
  int nTotalLns = Length();
  printf("\033[2J");
  PrintStrs();

  if (nTotalLns == 0) {
    Insert(0, new CharString());
    m_nYCurPos = 0;
    m_nXCurPos = 0;
  }

  char chCtrl;
  unsigned short chInput;

  do {
    CharString* pcsCurLn = NULL;
    if (!GetElem(m_nYCurPos, pcsCurLn) || pcsCurLn == NULL) {
      break;
    }

    chInput = GetStdCh(chCtrl);
    const char* pszCurLn = pcsCurLn->ToCStr();

    if (chCtrl > 0) {
      if (!OnEditCmd(chCtrl, pcsCurLn)) {
        break;
      }
    } else if ()
  } while (chInput != 27);
}

/* inline void TextEditor::Edit() {
  int nTotalLns = Length();  // 获取当前文本的总行数
  printf("\033[2J");         // 清屏
  PrintStrs();               // 打印当前文本内容

  if (nTotalLns == 0) {           // 如果文本为空
    Insert(0, new CharString());  // 插入一个新的空行
    m_nXCurPos = 0;               // 重置光标的X坐标
    m_nYCurPos = 0;               // 重置光标的Y坐标
  }

  char chCtrl;             // 用于存储控制字符
  unsigned short chInput;  // 用于存储输入的字符

  do {
    CharString* pcsCurLn = NULL;  // 当前行的指针初始化为空
    if (!GetElem(m_nYCurPos, pcsCurLn) ||
        !pcsCurLn)  // 获取当前行失败或当前行为空
      break;        // 退出编辑循环

    chInput = GetStdCh(chCtrl);  // 获取用户输入的字符和控制字符
    const char* pszCurLn = pcsCurLn->ToCStr();  // 获取当前行的字符串指针

    if (chCtrl > 0) {                    // 如果有控制字符输入
      if (!OnEditCmd(chCtrl, pcsCurLn))  // 执行控制命令
        break;  // 如果命令执行失败，退出编辑循环
                // 如果输入的是可打印字符或制表符
    } else if (chInput >= ' ' || chInput == '\t') {
      if (chInput & 0xff00) {        // 如果输入的是多字节字符
        char chHi = chInput >> 8;    // 高字节
        char chLo = chInput & 0xff;  // 低字节
        if (m_bReplaceMode) {        // 如果是替换模式
          unsigned char chCur = static_cast<unsigned char>(
              pszCurLn[m_nXCurPos]);  // 获取当前光标位置的字符
          if (chCur >= 0xa0) {        // 如果是多字节字符
            pcsCurLn->SetElem(m_nXCurPos++, chHi);  // 替换高字节
            pcsCurLn->SetElem(m_nXCurPos++, chLo);  // 替换低字节
          } else {
            pcsCurLn->SetElem(m_nXCurPos++, chHi);  // 替换高字节
            pcsCurLn->Insert(m_nXCurPos++, chLo);   // 插入低字节
          }
        } else {                                 // 如果是插入模式
          pcsCurLn->Insert(m_nXCurPos++, chHi);  // 插入高字节
          pcsCurLn->Insert(m_nXCurPos++, chLo);  // 插入低字节
        }
      } else {                 // 如果输入的是单字节字符
        if (m_bReplaceMode) {  // 如果是替换模式
                               // 获取当前光标位置的字符
          unsigned char chCur =
              static_cast<unsigned char>(pszCurLn[m_nXCurPos]);
          if (chCur >= 0xa0) {                       // 如果是多字节字符
            pcsCurLn->SetElem(m_nXCurPos, chInput);  // 替换字符
            char chNext;
            pcsCurLn->Delete(m_nXCurPos + 1, chNext);  // 删除多余的字节
          } else {
            pcsCurLn->SetElem(m_nXCurPos, chInput);  // 替换字符
          }
        } else {                                  // 如果是插入模式
          pcsCurLn->Insert(m_nXCurPos, chInput);  // 插入字符
        }
        m_nXCurPos++;  // 移动光标到下一个位置
      }
      PrintLn(pcsCurLn, m_nYCurPos);  // 打印当前行
    }
  } while (chInput != 27);  // 循环直到用户按下ESC键

  WinSize stWinSize = GetWinSize();  // 获取窗口大小
  MoveCur(stWinSize.nRows - 1, 0);   // 将光标移动到最后一行
  printf(
      "\033[K--Command mode, please enter your command--");  //
提示用户进入命令模式
} */

inline bool TextEditor::GetCmd() {
  printf("\033[?25l");

  WinSize stWinSize = GetWinSize();
  MoveCur(stWinSize.nRows - 2, 0);

  printf("\033[32m%s\033[37m>>\033[?25h\033[K", m_csFileName.ToCStr());

  char szBuffer[256] = {'\0'};
  scanf("%255[^\n]", szBuffer);
  getchar();

  char* pCmd = szBuffer;
  while (*pCmd <= ' ' && *pCmd != '\0') ++pCmd;

  char* pParam = pCmd;
  while (*pParam > ' ' && *pParam != '\0') ++pCmd;
  *pParam = '\0';
  while ((*pParam <= ' ' || *pParam == '=') && *pParam != '\0') ++pParam;

  CharString csCmd = pCmd;
  CharString csParam = pParam;
  bool bRunning = true;

  if (csCmd == "e" || csCmd == "edit") {
    m_bEditMode = true;
  } else if (csCmd == "?" || csCmd == "h" || csCmd == "help") {
    Help(csParam);
  } else if (csCmd == "l" || csCmd == "load") {
    m_bEditMode = Load(csParam);
  } else if (csCmd == "q" || csCmd == "quit") {
    bRunning = false;
  } else if (csCmd == "s" || csCmd == "save") {
    m_bEditMode = Save(csParam);
  } else if (csCmd == "f" || csCmd == "find") {
    m_bEditMode = FindPatStr(csParam, m_nXCurPos, 0);
  } else if (csCmd == "g" || csCmd == "go") {
    m_bEditMode = GotoLn(csParam);
  } else {
    CharString csMsg;
    csMsg.Format("Not an editor command: %s", csCmd.ToCStr());
    ShowMsg(csMsg);
  }

  return bRunning;
}

inline bool TextEditor::OnEditCmd(char chCtrl, CharString* pcsCurLn) {
  WinSize stWinSize = GetWinSize();
  bool bSuccessed = true;
  int nTotalLns = Length();

  switch (chCtrl) {
    case 27:
      m_bEditMode = false;
      break;
    case 'R':
      m_bReplaceMode = true;
      PrintStrs();
      break;
    case 'G':
      m_nXCurPos = 0;
      m_nYCurPos = 0;
      m_nTopLn = 0;
      PrintStrs();
      break;
    case 'O':
      if (GetElem(nTotalLns - 1, pcsCurLn)) {
        m_nYCurPos = m_nTopLn;
        m_nXCurPos = pcsCurLn->Length();
        PrintStrs();
      }
      break;
    case 'H':
      if (m_nYCurPos > 0) {
        bSuccessed = MoveYCur(-1, stWinSize.nRows);
      }
      break;
    case 'P':
      if (m_nYCurPos < Length() - 1) {
        bSuccessed = MoveYCur(1, stWinSize.nRows);
      }
      break;
    case 'I':
      if (m_nYCurPos > 0) {
        bSuccessed = MoveYCur(-(stWinSize.nRows), stWinSize.nRows);
      }
      break;
    case 'Q':
      if (m_nYCurPos + stWinSize.nRows - 2 < nTotalLns) {
        bSuccessed = MoveYCur(stWinSize.nRows - 2, stWinSize.nRows);
      } else {
        MoveCur(nTotalLns - 1, 0);
      }
      break;
    case 'K':
      if (pcsCurLn != NULL && m_nXCurPos > 0) {
        const unsigned char* pszCurLn =
            reinterpret_cast<const unsigned char*>(pcsCurLn->ToCStr());
        m_nXCurPos -= (pszCurLn[m_nXCurPos - 1] >= 0xa0) ? 2 : 1;
        MoveCur(m_nYCurPos, m_nXCurPos);
      }
      break;
    case 'M':
      if (pcsCurLn != NULL) {
        int nCurMaxLen =
            pcsCurLn->Length() + (m_bReplaceMode && m_nXCurPos > 0 ? 0 : 1);
        if (m_nXCurPos + 1 < nCurMaxLen) {
          const unsigned char* pszCurLn =
              reinterpret_cast<const unsigned char*>(pcsCurLn->ToCStr());
          m_nXCurPos += (pszCurLn[m_nXCurPos] >= 0xa0) ? 2 : 1;
          MoveCur(m_nYCurPos, m_nXCurPos);
        }
      }
      break;
    case '=':
      if (!m_csPat.IsEmpty() &&
          FindPatStr(m_csPat, m_nYCurPos, m_nXCurPos + 1)) {
        PrintStrs();
      }
      break;
    case '\b':
      if (m_nXCurPos == 0) {
        CharString* pcsPreLn = NULL;
        if (GetElem(m_nYCurPos - 1, pcsPreLn) && Delete(m_nYCurPos, pcsCurLn)) {
          *pcsPreLn += *pcsCurLn;
          delete pcsCurLn;
          pcsCurLn = pcsPreLn;
          m_nXCurPos = pcsCurLn->Length();
          printf("\033[?25l");
          PrintStrs();
          printf("\033[?25h");
        }
      } else {
        char chDel;
        pcsCurLn->Delete(m_nXCurPos - 1, chDel);
        --m_nXCurPos;
        if (static_cast<unsigned char>(chDel) >= 0xa0) {
          pcsCurLn->Delete(m_nXCurPos - 1, chDel);
          --m_nXCurPos;
        }
        PrintLn(pcsCurLn, m_nYCurPos);
      }
      break;
    case 'S':
      if (m_nXCurPos >= pcsCurLn->Length()) {
        CharString* pcsNextLn = NULL;
        if (Delete(m_nYCurPos + 1, pcsNextLn)) {
          *pcsCurLn += *pcsNextLn;
          delete pcsNextLn;
          PrintStrs();
        }
      } else {
        char chDel;
        pcsCurLn->Delete(m_nXCurPos, chDel);
        if (static_cast<unsigned char>(chDel) >= 0xa0) {
          pcsCurLn->Delete(m_nXCurPos, chDel);
        }
        PrintLn(pcsCurLn, m_nYCurPos);
      }
      break;
    case '\r':
      if (m_bReplaceMode) {
        if (m_nYCurPos < nTotalLns - 1) {
          ++m_nYCurPos;
          m_nXCurPos = 0;
          MoveCur(m_nYCurPos, m_nXCurPos);
        }
      } else {
        CharString* pcsNewLn = new CharString();
        while (m_nXCurPos < pcsCurLn->Length()) {
          char chDel;
          if (!pcsCurLn->Delete(m_nXCurPos, chDel)) {
            break;
          }
          pcsNewLn->AddTail(chDel);
        }
        Insert(m_nYCurPos + 1, pcsNewLn);
        ++m_nYCurPos;
        m_nXCurPos = 0;
        printf("\033[?25l");
        PrintStrs();
        printf("\033[?25h");
      }
      break;
    default:
      break;
  }

  return bSuccessed;
}

inline bool TextEditor::Save(const CharString& csFileName) {
  if (csFileName.IsEmpty() && m_csFileName.IsEmpty()) {
    ShowMsg("Usage: save <filename> - The save command requires a file name.");
    return false;
  }

  CharString csFinalFileName = csFileName.IsEmpty() ? m_csFileName : csFileName;

  FILE* pFile = fopen(csFinalFileName.ToCStr(), "wb");

  if (pFile == NULL) {
    CharString csMsg;
    csMsg.Format("Failed to open file \"%s\".", csFinalFileName.ToCStr());
    ShowMsg(csMsg);
    return false;
  }

  CharString* pcsCurLn;
  Head();
  int nCurLn = 0;

  while (Next(pcsCurLn)) {
    if (pcsCurLn->Length() > 0) {
      fwrite(pcsCurLn->ToCStr(), pcsCurLn->Length(), 1, pFile);
    }

    if (nCurLn < Length() - 1) {
      fwrite("\n", 1, 1, pFile);
    }
    ++nCurLn;
  }

  fclose(pFile);
  m_csFileName = csFileName;

  return true;
}

inline unsigned short TextEditor::GetStdCh(char& chCtrl) {
  unsigned char uchFirstCh = getch();  // 获取第一个字符
  unsigned short usCh = uchFirstCh;    // 初始化返回值为第一个字符
  chCtrl = 0;                          // 初始化控制字符为0

  if (uchFirstCh == 0xe0 || uchFirstCh == 0) {
    // 特殊控制字符，需读取下一个字符
    chCtrl = getch();
  } else if (uchFirstCh < ' ' && uchFirstCh != '\t') {
    // ASCII控制字符
    chCtrl = uchFirstCh;
  } else if (uchFirstCh > 0xa0) {
    // 处理汉字字符，需读取第二个字节
    unsigned char uchSecondCh = getch();
    // 将两个字节组合成一个完整的汉字
    usCh = (uchFirstCh << 8) | uchSecondCh;
  }

  return usCh;  // 返回完整字符或控制字符
}

inline void TextEditor::Help(const CharString& csCmd) {}

inline void TextEditor::ShowMsg(const CharString& csMsg, int nBgColor) {
  if (m_bEditMode) {
    return;  // 如果处于编辑模式，则直接返回
  }

  printf("\033[?25l");               // 隐藏光标
  WinSize stWinSize = GetWinSize();  // 获取窗口大小
  MoveCur(stWinSize.nRows - 1, 0);   // 将光标移动到窗口底部
  // 清除当前行并设置背景颜色，然后打印消息
  printf("\033[K\033[%dm%s", nBgColor, csMsg.ToCStr());
  MoveCur(stWinSize.nRows - 2, 0);  // 将光标移动到倒数第二行
  printf("\033[40m\033[K>>\033[?25h");  // 恢复默认背景颜色并显示提示符
}

inline void TextEditor::PrintStrs(bool bClearAll) {
  printf("\033[?25l\033[0;0H");
  CharString* pcsCurLn;
  int nCurLn = 0;
  WinSize stWinSize = GetWinSize();

  bool bRedraw;
  int nTopLn = GetTopLn(stWinSize.nRows, bRedraw);
  Head();

  while (Next(pcsCurLn) && pcsCurLn != NULL) {
    if (nCurLn < nTopLn) {
      ++nCurLn;
      continue;
    }

    if (nCurLn - nTopLn >= stWinSize.nRows - 2) {
      break;
    }

    MoveCur(nCurLn, 0);
    printf("\033[K%s\n", pcsCurLn->ToCStr());
    ++nCurLn;
  }

  if (bClearAll) {
    while (nCurLn - nTopLn <= stWinSize.nRows - 3) {
      MoveCur(nCurLn, 0, false);
      printf("\033[K");
    }
  }
}

/* inline void TextEditor::PrintStrs(bool bClearAll) {
  printf("\033[?25l\033[0;0H");
  CharString* pcsCurLn;
  int nCurLn = 0;
  WinSize stWinSize = GetWinSize();

  bool bRedraw;
  int nTopLn = GetTopLn(stWinSize.nRows, bRedraw);
  Head();

  while (Next(pcsCurLn) && pcsCurLn != NULL) {
    if (nCurLn < nTopLn) {
      ++nCurLn;
      continue;
    }

    if (nCurLn - nTopLn > stWinSize.nRows - 3) {
      break;
    }

    MoveCur(nCurLn, 0);
    printf("\033[K%s\n", pcsCurLn->ToCStr());
    ++nCurLn;
  }

  if (bClearAll) {
    while (nCurLn - nTopLn <= stWinSize.nRows - 3) {
      MoveCur(nCurLn, 0, false);
      printf("\033[K");
      ++nCurLn;
    }
  } else {
    MoveCur(nCurLn, 0);
  }

  const char* pszModeMsg =
      m_bReplaceMode ? "--Replace, Presss 'ESC' to return command mode--"
                     : "--Insert, Press 'ESC' to return command mode--";

  printf("\033[%d;%dH\033[K%s", stWinSize.nRows, 0, pszModeMsg);
  MoveCur(m_nYCurPos, m_nXCurPos);
  printf("\033[?25h");
} */

inline void TextEditor::PrintLn(CharString* pcsCurLn, int nYCurPos) {
  if (pcsCurLn == NULL) {
    return;  // 如果目标行指针为空，则返回
  }

  printf("\033[?25l");   // 隐藏光标
  MoveCur(nYCurPos, 0);  // 移动光标到目标行的起始位置
  printf("\033[K%s", pcsCurLn->ToCStr());  // 打印目标行的字符串
  MoveCur(m_nYCurPos, m_nXCurPos);  // 移动光标回到当前光标位置
  printf("\033[?25h");              // 显示光标
}

inline void TextEditor::MoveCur(int nYCurPos, int nXCurPos, bool bPrintLnNum) {
  int nTopLn = m_nTopLn;  // 存储顶行行号

  if (!m_bEditMode) {
    // 不在编辑模式则直接到指定坐标
    printf("\033[%d;%dH", nYCurPos + 1, nXCurPos + 1);
  }

  char szLnHdr[32] = {'\0'};  // 行号数组

  if (bPrintLnNum) {       // 打印字符
    CharString* pcsCurLn;  // 当前行号

    sprintf(szLnHdr, "%-3d", nYCurPos + 1);  // 将行号存入字符数组
    int nLnHdrLen = strlen(szLnHdr);
    if (GetElem(nYCurPos, pcsCurLn)) {
      const char* pszCurLn = pcsCurLn->ToCStr();
      int nXPos = nLnHdrLen;
      for (int i = 0; i < nXCurPos; ++i) {
        nXPos += pszCurLn[i] == '\t' ? 8 - nXPos % 8 : 1;
      }
      nXCurPos = nXPos;

      printf("\033[?25l\033[%d;%dH\033[46m%s\033[?25h\033[40m",
             nYCurPos + 1 - nTopLn, 1, szLnHdr);
    }
  }

  printf("\033[%d;%dH", nYCurPos + 1 - nTopLn, nXCurPos + 1);
}

inline void TextEditor::CheckZhCur(CharString* pcsCurLn) {
  if (m_nXCurPos < 0) return;

  int nCurLen = pcsCurLn->Length();
  int nCurMaxLen = nCurLen - (m_bReplaceMode && nCurLen > 0 ? 1 : 0);
  m_nXCurPos = (std::min)(m_nXCurPos, nCurMaxLen);

  const unsigned char* pszCurLn =
      reinterpret_cast<const unsigned char*>(pcsCurLn->ToCStr());
  const unsigned char* pStartPos = pszCurLn + m_nXCurPos;
  const unsigned char* pEndPos = pszCurLn + nCurLen;
  const unsigned char* pCurPos = pStartPos;

  while (pCurPos < pEndPos && *pCurPos >= 0xa0) {
    ++pCurPos;
  }

  if ((pCurPos - pStartPos) % 2 == 1) {
    --m_nXCurPos;
  }
}

inline bool TextEditor::MoveYCur(int nOffset, int nWinRows) {
  CharString* pcsCurLn;
  bool bPage = (nOffset < -1 || nOffset > 1);

  if (bPage) {
    int nMaxOffset = Length() - 1 - m_nYCurPos;
    int nMinOffset = -m_nYCurPos;
    int nOffset = (std::max)(nMinOffset, (std::min)(nOffset, nMaxOffset));
  }

  if (GetElem(m_nYCurPos + nOffset, pcsCurLn) && pcsCurLn) {
    m_nYCurPos += nOffset;
    CheckZhCur(pcsCurLn);

    bool bRedraw = bPage;

    if (!bPage) {
      GetTopLn(nWinRows, bRedraw);
    } else {
      m_nTopLn += nOffset;
      if (m_nTopLn) m_nTopLn = 0;
    }

    if (bRedraw) {
      PrintStrs();
    } else {
      MoveCur(m_nXCurPos, m_nYCurPos);
    }

    return true;
  }

  return false;
}

inline bool TextEditor::FindPatStr(const CharString& csPat, int nRow,
                                   int nCol) {
  // 检查模式字符串是否为空
  if (csPat.IsEmpty()) {
    // 如果为空，显示错误信息并返回未找到
    ShowMsg(
        "Usage: f <pattern string> - The 'find' command requires a valid "
        "pattern string.");
    return false;
  }

  // 初始化变量
  bool bFound = false;   // 标记是否找到模式
  CharString* pcsCurLn;  // 当前行指针
  int nCurLn = 0;        // 当前行

  Head();  // 将链表指针移到头部

  // 遍历链表中的每一行
  while (Next(pcsCurLn)) {
    // 如果当前行号小于起始行号，继续下一行
    if (nCurLn < nRow) {
      ++nCurLn;
      continue;
    }

    // 确定搜索起始位置
    int nXPos = (nCurLn == nRow) ? nCol : 0;
    // 使用KMP算法查找模式字符串
    int nIdx = pcsCurLn->KMPIndex(csPat, nXPos);

    // 如果找到匹配
    if (nIdx >= 0) {
      bFound = true;        // 标记为找到
      m_csPat = csPat;      // 保存当前模式
      m_nXCurPos = nIdx;    // 更新光标X位置
      m_nYCurPos = nCurLn;  // 更新光标Y位置
      break;                // 退出循环
    }
    ++nCurLn;  // 增加当前行号
  }

  // 如果未找到且不在编辑模式，显示未找到信息
  if (!bFound && !m_bEditMode) {
    CharString csMsg;
    csMsg.Format("Pattern not found: %s", csPat.ToCStr());
    ShowMsg(csMsg);
  } else if (bFound && !m_bEditMode) {
    // 如果找到且不在编辑模式，显示找到信息并等待用户输入

    CharString csMsg;
    csMsg.Format(
        "Pattern '%s' found. Press F3 to find the next occurrence or any key "
        "to return to edit mode.",
        csPat.ToCStr());
    ShowMsg(csMsg, 40);
    getchar();  // 等待用户按键
  }

  return bFound;  // 返回是否找到模式
}

inline bool TextEditor::GotoLn(const CharString& csTarLn) {
  if (csTarLn.IsEmpty()) {  // 检查目标行字符串是否为空
    ShowMsg(
        "Usage: g <Line number> - The 'go' command requires a valid line "
        "number.");
    return false;
  }

  char* pEnd;
  int nTarLn = strtol(csTarLn.ToCStr(), &pEnd, 10);
  if (nTarLn < 1 || nTarLn > Length()) {  // 检查行号是否在有效范围内
    ShowMsg("Invalid line number. Please enter a valid number.");
    return false;
  }

  // 更新光标位置到目标行的起始位置
  m_nYCurPos = nTarLn - 1;
  m_nXCurPos = 0;
  return true;  // 成功跳转到目标行
}

inline int TextEditor::GetTopLn(int nWinRows, bool& bRedraw) {
  bRedraw = false;

  if (m_nYCurPos - m_nTopLn >= nWinRows - 3) {
    m_nTopLn = m_nTopLn + 3 - nWinRows;
    bRedraw = true;
  } else if (m_nYCurPos - m_nTopLn < 0 && m_nTopLn > 0) {
    --m_nTopLn;
    bRedraw = true;
  }
  return m_nTopLn;
}

#endif  // _TEXT_EDITOR_H_