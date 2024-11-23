#include "text_editor.h"

int main() {
  CharString csFileName = "C:\\Code\\Code_Practice\\CPP_Projects\\TextEditor\\data\\test.txt";

  TextEditor teEditor;
  teEditor.Run(csFileName);

  return 0;
}