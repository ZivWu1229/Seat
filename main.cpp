#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <fstream>
#include <vector>
#include <cstring>

using namespace std;

int main()
{
    //load group
    ifstream file("group.txt");
    string text;
    int line{0};
    getline(file,text);
    int group_count=atoi(text.c_str());
    int group[group_count][2];//group [start,end]
    while (getline(file,text)){
        int temp{0};
        for (int i=0;i<text.length();i++){
            if (text[i]=='-'){
                group[line][0]=temp;
                temp=0;
            }
            else{
                temp=temp*10+text[i]-48;
            }
        }
        group[line][1]=temp;
        line++;
    }
        
    file.close();

    //generate number
    srand(time(NULL));
    vector<int> number[group_count];
    for (int g=0;g<group_count;g++){
        int start{group[g][0]};
        int end{group[g][1]};
        int len {end-start+1};
        int output[len]={};
        for (int i=start;i<=end;i++){
            int pos{};
            do{
                pos=rand()%len+start;
            }while (output[pos-start]!=0);
            output[pos-start]=i;
        }
        number[g]=vector<int>(output,output+sizeof(output)/sizeof(output[0]));
    }
    //output
    cout<<number[0][24]<<" "<<number[1][29]<<endl;
    file=ifstream("layout.txt");
    while (getline(file,text)){
        cout<<endl;
        for (int i=0;i<text.length();i++){
            int index;
            if (text[i]==' '){cout<<"   ";continue;}
            //else if(text[i]=='*') index=rand()%(sizeof(number)/sizeof(number[0]));
            else index=int(text[i])-97;
            if (log10(number[index][0])<1)cout<<" ";
            cout<<number[index][0]<<" ";
            number[index].erase(number[index].begin());
            
        }
    }
    file.close();
    return 0;
}

