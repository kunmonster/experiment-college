#include<iostream>
#include<iomanip>
using namespace std;

int flag[23]={0};   //标记各个特征的状态
int IsAnimal(const int a);
int Inference();
void Input();
void Menu();

string animal[]  = {"企鹅","海燕","鸵鸟","斑马","长颈鹿","虎","金钱豹"};
string feature [] ={"有毛","产奶","有羽毛","会飞","会下蛋","吃肉","有犬齿","有爪","眼睛盯前方","有蹄","反刍","黄褐色","有斑点","有黑色条纹","长脖","长腿","不会飞","会游泳","黑白两色","善飞","哺乳类","鸟类","肉食类","蹄类", "企鹅","海燕","鸵鸟","斑马","长颈鹿","虎","金钱豹"};

typedef struct {
  int relation[5];
  int name;
}Rule;

Rule rule[15] = {
  {{0,-1},20},
{{1,-1},20},
{{2,-1},21},
{{3,4,-1},21},
{{20,5,-1},22},
{{6,7,8,-1},22},
{{20,8,-1},23},
{{20,9,-1},23},
{{22,11,12,-1},30},
{{22,11,13,-1},29},
{{23,14,15,12,-1},28},
{{23,13,-1},27},
{{21,14,15,16,-1},26},
{{21,19,-1},25},
{{21,17,18,16,-1},24}
};

void Menu(){
 int i = 0;
 for(i = 0;i<24;i++){
   if(i%4==0&&i!=0){
     cout<<endl;
   }
  
   cout<<setw(3)<<left<<i<<"."<<setw(15)<<left<<feature[i];
 }
}

void Input(){
  int ti = 0;
  for(int i=0;i<24;i++){
    flag[i]=0;
  }
  while (ti!=-1){
    /* code */
    cout<<"\n输入选择(-1结束):";
    cin>>ti;
    if(ti>=0&&ti<=23) flag[ti]=1;
    else if(ti != -1){
      cout<<"输入错误!请输入0~23之间的数字!"<<endl;
      cin.clear();  //清除流错误
      cin.sync(); //清空输入缓冲
    }
  }
}

int IsAnimal(const int a){
  return a>=24 && a<=30 ? 1 : 0;
}

int Inference(){
  //正向推理
  int ti,i,j,tres;
  cout<<endl;
  for(i=0;i<15;i++){
    j=0;
    ti=rule[i].relation[j];
    while(ti!=-1){
      //-1作为结束标志
      if(flag[ti] == 0 ){
        break;
      }
      j++;
      ti = rule[i].relation[j];    
    }
    if(ti==-1){
      //规则满足
      tres = rule[i].name;
      flag[tres] = 1;
      cout<<"运用了规则:"<<i<<endl;
      j=0;
      while(rule[i].relation[j]!=-1){
        cout<<feature[rule[i].relation[j]]<<" ";
        j++;
      }
      cout<<"====>"<<feature[tres]<<endl;
      if(IsAnimal(tres)) return 1;

    }
  }
if(i == 15){
  cout<<"没有这种动物";
}
return -1;
}

int main(int argv,char ** args){
  char q;
  while (q!='n'){
    /* code */
    Menu();
    Input();
    Inference();
    cout<<"\n继续?(Y/N)"<<endl;
    cin>>q;
  }
  return 0;
}