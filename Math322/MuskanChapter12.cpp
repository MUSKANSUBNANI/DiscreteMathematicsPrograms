#include<iostream>
#include<queue>
#include<string>
#include<cctype>
#include<fstream>

using namespace std;
void showq(queue <string> gq) 
{ 
    queue <string> g = gq; 
    while (!g.empty()) 
    { 
        cout  << g.front(); 
        g.pop(); 
    } 
    cout << '\n'; 
} 

int main(int argc, char* argv[]) {
  if (argc > 1) {   
    ifstream fin;
    fin.open(argv[1]);
	queue <string> inputqueue;
    queue<string> outputqueue;

	string readline;
    getline(fin,readline);
    char input1= readline[0];
    char input2=readline[2];
    string x(1,input1);
    string negsign="-";
    string notx=negsign+x;
    string y(1,input2);
    string noty=negsign+y;

    while(!fin.eof())
    {
        getline(fin,readline);
        //cout<<readline[0]<<" "<<readline[2]<<" "<<readline[4]<<"\n";
        if(readline[4]=='0')
        {
            if(readline[0]=='1')
            { 
                inputqueue.push(notx);
            }
            else
            {
                
                inputqueue.push(x);
            }
            inputqueue.push("+");
            if(readline[2]=='1')
            {
                
                inputqueue.push(noty);
            }
            else
            {
                
                inputqueue.push(y);

            }
            
            string a=inputqueue.front();
            inputqueue.pop();
            if(!outputqueue.empty())
            {
                outputqueue.push(".");
            }
            outputqueue.push("-");
            outputqueue.push("(");
            if(a==x)
            {
                outputqueue.push(notx);
            }
            else{
                outputqueue.push(x);

            }
            //string or=inputqueue.front();
            inputqueue.pop();
            outputqueue.push(".");

            string b=inputqueue.front();
            inputqueue.pop();

            if(b==y)
            {
                outputqueue.push(noty);
            }
            else{
                outputqueue.push(y);

            }
            outputqueue.push(")");
      
        }
    }

	showq(outputqueue);
  }
}
