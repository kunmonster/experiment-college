#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define MAXSIZE 100;  //外存最大容量

enum Status { CLOSE, OPEN };  // CLOSE:关闭 OPEN:打开
enum Type { FIEL, TABLE };    // FILE:文件  TABLE:目录

class FCB {
 private:
  string name;
  Type type = FIEL;  //默认为文件 默认在根目录
  int all_size;
  int use_size;
  Status statu;
  int belong = 0;  //属于哪个用户
  int start;
  vector<FCB *> Child;  //子目录默认为-1,若为其他值，就为该子目录的索引

 public:
  FCB(std::string name, int start, std::string content) {
    this->name = name;
    this->all_size = this->use_size = content.length();
    this->statu = CLOSE;  //默认关闭状态
    this->start = start;
    this->use_size = content.length();
  }
  int getStatus() { return this->statu; }
  void child_Push(FCB *fcb) { this->Child.push_back(fcb); }
  vector<FCB *> getChild() { return this->Child; }
  void changeStatus() { this->statu = Status(this->statu / 1); }
  int getallSize() { return this->all_size; }
  int getuseSize() { return this->use_size; }
  void setName(std::string name) { this->name = name; }
  void setStatu() {
    this->statu == OPEN ? this->statu = CLOSE : this->statu = OPEN;
  }
  void del(int i) { this->Child.erase(Child.begin() + i); }
  string getname() { return this->name; }
  int getStart() { return this->start; }
};

class FIELMANAGE {
 private:
  vector<string> *MEMORY;
  vector<FCB *> *tableOfContents;
  vector<FCB *> *childtable;

 public:
  FIELMANAGE(vector<string> *MEMORY, vector<FCB *> *tableOfContents,
             vector<FCB *> *childtable) {
    this->MEMORY = MEMORY;
    this->tableOfContents = tableOfContents;
    this->childtable = childtable;
  }

  void Creat() {
    //新建文件
    std::string name;
    std::cout << "请输入文件名:" << std::endl;
    std::cin >> name;
    std::string content;
    std::cout << "请输入文件内容:" << std::endl;
    std::cin >> content;
    int currentsize = MEMORY->size();
    if (currentsize < 100) {
      int index = this->MEMORY->end() - this->MEMORY->begin();
      FCB *fcb = new FCB(name, index, content);  //此处将迭代器转为索引
      this->MEMORY->push_back(content);  // 1表示该位置内存被占用
      this->tableOfContents->push_back(fcb);
    }
  }

  void Delete() {
    //根据文件名删除文件
    bool tag = false;
    cout << "请输入文件名" << endl;
    string name;
    cin >> name;
    for (int i = 0; i < tableOfContents->size(); i++) {
      tag = true;
      if ((*tableOfContents)[i]->getname() == name) {
        tableOfContents->erase(tableOfContents->begin() + i);
        MEMORY->erase(MEMORY->begin() + (*tableOfContents)[i]->getStart());
        delete (*tableOfContents)[i];
      } else {
        continue;
      }
    }
    if (!tag) {
      cout << "不存在当前文件!" << endl;
    }
  }
  void OpenFile() {
    bool tag = false;
    cout << "请输入文件名" << endl;
    string name;
    cin >> name;
    for (auto item : *tableOfContents) {
      if (item->getname() == name) {
        //存在当前文件，查看是否为打开状态
        tag = true;
        if (item->getStatus() == OPEN) {
          //打开状态
          std::cout << "当前文件已经打开！" << std::endl;
          exit(0);
        } else {
          //打开成功
          item->setStatu();
          std::cout << "当前文件打开成功" << std::endl;
        }
        break;
      } else {
        continue;
      }
    }
    if (!tag) {
      std::cout << "不存在当前文件" << std::endl;
    }
  }
  void CloseFile() {
    cout << "请输入文件名" << endl;
    string name;
    cin >> name;
    bool tag = false;
    for (auto item : *tableOfContents) {
      tag = true;
      if (item->getname() == name) {
        if (item->getStatus() == OPEN) {
          //文件打开直接关闭
          item->setStatu();
          std::cout << "文件关闭成功!" << std::endl;
        } else {
          std::cout << "文件处于关闭状态!" << std::endl;
        }
      }
    }
  }
  void ListFile() {
    if (tableOfContents->empty()) {
      std::cout << "当前目录为空！";
    } else {
      for (auto item : *tableOfContents) {
        std::cout << item->getname() << std::endl;
        auto temp = item->getChild();
        if (!temp.empty()) {
          for (auto item_child : temp) {
            cout << "chlid:" << item_child->getname() << endl;
          }
        }
      }
    }
  }
  void writeFile() {
    bool have_tag = false;
    cout << "请输入文件名" << endl;
    string name;
    cin >> name;
    for (auto item : *tableOfContents) {
      if (item->getname() == name) {
        if (item->getStatus() == OPEN) {
          //查到该文件
          std::string content;
          std::cout << "请输入内容:" << std::endl;
          std::cin >> content;
          int length = content.length();
          have_tag = true;
          string temp;
          std::cout << "是否覆盖原内容? [1]:是 [2]:否";
          int choice;
          std::cin >> choice;
          switch (choice) {
            case 1:
              // item->setContent(content, 1);  //覆盖模式
              (*MEMORY)[item->getStart()] = content;
              break;
            case 2:
              // item->setContent(content, 0);  //非覆盖模式
              temp = (*MEMORY)[item->getStart()] + content;
              (*MEMORY)[item->getStart()] = temp;
              break;
            default:
              //非覆盖模式
              temp = (*MEMORY)[item->getStart()] + content;
              (*MEMORY)[item->getStart()] = temp;
              break;
          }
        } else {
          std::cout << "文件处于关闭状态";
        }
      }
    }
    if (!have_tag) {
      //不存在当前文件，创建再赋值
      Creat();
    }
  }
  void Read() {
    bool tag = false;
    cout << "请输入文件名" << endl;
    string name;
    cin >> name;
    for (auto item : *tableOfContents) {
      if (item->getname() == name) {
        tag = true;
        //去内存中查找
        //文件表中存在该文件
        if (item->getStatus() == OPEN) {
          cout << (*MEMORY)[item->getStart()];
        } else {
          cout << "文件未打开!" << endl;
        }
      }
    }
    if (!tag) {
      cout << "不存在该文件!" << endl;
    }
  }
  void CreatChild() {
    bool tag = false;
    cout << "请输入父文件名" << endl;
    string name_father;
    cin >> name_father;
    for (auto item : *tableOfContents) {
      if (item->getname() == name_father) {
        tag = true;
        string name_child;
        cout << "请输入子文件名:" << std::endl;
        cin >> name_child;
        string content;
        cout << "请输入子文件内容:" << std::endl;
        cin >> content;
        vector<FCB *> temp = item->getChild();
        int index_mem = this->MEMORY->end() - this->MEMORY->begin();
        FCB *fcb = new FCB(name_child, index_mem, content);
        MEMORY->push_back(content);
        item->child_Push(fcb);
        this->childtable->push_back(fcb);  //插入子目录表中
      }
    }
    if (!tag) {
      cout << "不存在该父文件!" << endl;
    }
  }
  void deltable() {
    bool tag = false;
    cout << "请输入要删除的目录名" << endl;
    string name_table;
    cin >> name_table;
    for (int i = 0; i < tableOfContents->size(); i++) {
      tag = true;
      if ((*tableOfContents)[i]->getname() == name_table) {
        auto child = (*tableOfContents)[i]->getChild();
        if (child.empty()) {
          tableOfContents->erase(tableOfContents->begin() + i);
          MEMORY->erase(MEMORY->begin() + (*tableOfContents)[i]->getStart());
          delete (*tableOfContents)[i];
        } else {
          //还存在子目录
          for (int k = 0; k <= child.size(); k++) {
            for (int j = 0; j <= childtable->size(); j++) {
              if (child[k]->getname() == (*childtable)[j]->getname()) {
                childtable->erase(childtable->begin() + j);
              } else {
                continue;
              }
            }
            (*tableOfContents)[i]->del(k);
          }
        }
      } else {
        continue;
      }
    }
    if (!tag) {
      cout << "不存在当前文件!" << endl;
    }
  }
};

int main() {
  std::vector<string> *MEMORY = new vector<string>();         //模拟外存
  std::vector<FCB *> *tableOfContents = new vector<FCB *>();  //目录
  vector<FCB *> *childtable = new vector<FCB *>();
  FIELMANAGE *f = new FIELMANAGE(MEMORY, tableOfContents, childtable);

sign:
  cout << "请选择操作:" << endl;
  cout << "[1]:创建文件\t[2]:删除文件" << endl;
  cout << "[3]:打开文件\t[4]:关闭文件" << endl;
  cout << "[5]:文件目录\t[6]:写入文件" << endl;
  cout << "[7]:读文件\t  [8]:建子目录" << endl;
  cout << "[9]:删除目录\t[10]:退出程序" << endl;

  int choice;
  cin >> choice;
  switch (choice) {
    case 1:
      f->Creat();
      goto sign;

      break;
    case 2:

      f->Delete();
      goto sign;
      break;
    case 3:

      f->OpenFile();
      goto sign;
      break;
    case 4:

      f->CloseFile();
      goto sign;
      break;
    case 5:
      f->ListFile();
      goto sign;
      break;
    case 6:

      f->writeFile();
      goto sign;
      break;
    case 7:
      f->Read();
      goto sign;
      break;
    case 8:
      f->CreatChild();
      goto sign;
      break;
    case 9:
      f->deltable();
      goto sign;

      break;
    case 10:
      exit(0);
      break;
    default:
      break;
  }

  return 0;
}
