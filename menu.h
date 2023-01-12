#ifndef __MENU_H__
#define __MENU_H__

#include <string_view>

class Menuitem
{
  public:
    Menuitem();
    ~Menuitem();
    void AddParent(Menuitem* a_menuitem);
    void AddChild(Menuitem* a_menuitem);
    void AddNextItem(Menuitem* a_menuitem);
    void DeleteItem(Menuitem* a_menuitem);
    Menuitem* GetParent();
    Menuitem* GetChild();
    Menuitem* GetNext();
    Menuitem* GetPrev();
  private:
    Menuitem* parent;
    Menuitem* child;
    Menuitem* next;
    Menuitem* prev; 
    std::string_view data;
  protected:
};

class Menu
{
  public:
    Menu();
    Menu(Menuitem* ap_menuitem);
    ~Menu();
    void AddMenuItem(Menuitem* ap_menuitem);
    void SelectParentItem();
    void SelectChildItem();
    void SelectNextItem();
    void SelectPreviousItem();
    void DisplayMenu();
  private:
    Menuitem* menuitem;
  protected:
};

#endif //__MENU_H__