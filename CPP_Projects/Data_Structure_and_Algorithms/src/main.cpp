#include "text_editor.h"

int main(int argc, char **argv) {
  CharString csFileName;

  if (argc > 1) {
    csFileName = argv[1];
  }

  TextEditor teEditor;
  teEditor.Run(csFileName);

  return 0;
}