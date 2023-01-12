
#include "menu.h"

Menuitem::Menuitem():
  parent{nullptr},
  child{nullptr},
  next{nullptr},
  prev{nullptr}
  //data
{
  
}

Menuitem::~Menuitem()
{

}

void Menuitem::AddParent(Menuitem* a_menuitem)
{
  a_menuitem->child = this;
  this->parent = a_menuitem;
}

void Menuitem::AddChild(Menuitem* a_menuitem)
{
  this->child = a_menuitem;
  a_menuitem->parent = this;
}

void Menuitem::AddNextItem(Menuitem* a_menuitem)
{
  this->next = a_menuitem;
  a_menuitem->prev = this;
}

void Menuitem::DeleteItem(Menuitem* a_menuitem)
{
  #if 0
      if(this->next!=nullptr)
      {
        this->parent->child = this->next;
        this->next->parent = this->parent;
      }
      else if (this->prev !=nullptr)
      {
        this->parent->child = this->prev;
        this->prev->parent = this->parent;
      }
      else
      {
        this->parent->child = this->child;
        this->child->parent = this->parent;
      }
  #endif //0
  
  this->next->prev = this->prev;
  this->prev->next = this->next;
  //this->~Menuitem();??
}

Menuitem* Menuitem::GetParent()
{
  return this->parent;
}

Menuitem* Menuitem::GetChild()
{
  return this->child;
}

Menuitem* Menuitem::GetNext()
{
  return this->next;
}

Menuitem* Menuitem::GetPrev()
{
  return this->prev;
}

Menu::Menu():
  menuitem{nullptr}
{

}

Menu::Menu(Menuitem* ap_menuitem):
  menuitem{ap_menuitem}
{
}

Menu::~Menu()
{

}

void AddMenuItem(Menuitem* ap_menuitem)
{
//  this->menuitem = ap_menuitem; ???
}

void Menu::SelectParentItem()
{
  this->menuitem = menuitem->GetParent();
}
void Menu::SelectChildItem()
{
  this->menuitem = menuitem->GetChild();
}

void Menu::SelectNextItem()
{
  this->menuitem = menuitem->GetNext();
}

void Menu::SelectPreviousItem()
{
  this->menuitem = menuitem->GetPrev();
}

void Menu::DisplayMenu()
{
  //implementation defined!!
}
