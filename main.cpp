#include <pthread.h>
#include <iostream>
 #include<fstream>
 #include <vector>
#include <cmath>

using namespace std;


void *code(void *array){
    string *ptr= (string *)array;
    for(int i=0; i<30; i++){
        if(i==0){
            (*ptr)="0";
            ptr++;
        }
        if(i>0){
            int num= i;
            string buffer;
            for(int j=0; num>0;j++){
                int temp=num%2;
                buffer=to_string(temp)+buffer;
                num=num/2;
            }
            (*ptr)=buffer;
            ptr++;
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
  
    string text, test;
    int count=0;
    
    ifstream read;
    read.open(argv[1]);
    if (read.is_open()) {
        while(getline(read,test)){
        count++;
        }
    }
    read.close();
    string myArray[count];
    read.open(argv[1]);
    
    if (read.is_open()) {
        for(int i=0; i<count;i++){
            getline(read,text);
            myArray[i]=text;
        }
    }
    
    read.close();
    
    for(int i=1; i<count;i++){
        myArray[0]= myArray[0]+ myArray[i];
    }
 
        test=myArray[0];
        for(int j=0; j<test.length();j++){
            for(int k=0; k<test.length()-j-1;k++){
                if(test.at(k)>test.at(k+1)){
                    char temp=test.at(k);
                    test.at(k)=test.at(k+1);
                    test.at(k+1)=temp;
                }
            }
        }
        myArray[0]=test;
        
    text=myArray[0];
    vector<char> unique;
    vector<int> num;
    for(int i=0; i<text.length(); i++){
        if(unique.empty()){
            unique.push_back(text.at(0));
            num.push_back(1);
        }
        if(text.at(i)==unique.back()){
            int temp= num.back();
            num.back()=temp+1;
        }
        else{
            unique.push_back(text.at(i));
            num.push_back(1);
            
        }
    }

    for(int i=0; i<unique.size();i++){
         for(int j=0; j<unique.size()-i-1;j++){
             if(num.at(j)<num.at(j+1)){
                 char let= unique.at(j);
                int temp=num.at(j);
                 unique.at(j)=unique.at(j+1);
                num.at(j)=num.at(j+1);
                num.at(j+1)=temp;
                 unique.at(j+1)=let;
              }
          }
      }
    

    int soc= ceil(log2(unique.size()));
    
    pthread_t tid[30];
    static string arr[30];
    
    for(int i=0; i<30;i++){
        pthread_create(&tid[i], NULL, code, &arr );
        pthread_join(tid[i],NULL);
    }
    
   for(int i=0; i<30;i++){
       string temp=arr[i];
       while(temp.length()!=soc){
           temp="0"+temp;
       }
       arr[i]=temp;
   }
    for(int i=0; i<unique.size();i++){
        cout<<"Symbol: "<< unique.at(i)<<", Frequency: "<< num.at(i)<<", Code: "<< arr[i]<<endl;
    }
    
    return 0;
}

