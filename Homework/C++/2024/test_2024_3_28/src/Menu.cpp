#include "../include/Menu.h"

#include "../include/ContactsManagement.h"

void Menu::show_menu() {
  int choice;
  ContactsManagement contacts_management;

  do {
    cout << "===== 联系人管理系统菜单 =====" << endl;
    cout << "1. 显示所有联系人" << endl;
    cout << "2. 添加新联系人" << endl;
    cout << "3. 查找联系人" << endl;
    cout << "4. 退出系统" << endl;
    cout << "请选择操作：" << endl;

    cin >> choice;

    switch (choice) {
      case 1:
        contacts_management.show_all_contacts();
        break;
      case 2:
        contacts_management.add_new_contact();
        break;
      case 3:
        contacts_management.search_contact();
        break;
      case 4:
        cout << "感谢使用，再见！" << endl;
        break;
      default:
        cout << "无效选项，请重新选择。" << endl;
    }
  } while (choice != 4);
}