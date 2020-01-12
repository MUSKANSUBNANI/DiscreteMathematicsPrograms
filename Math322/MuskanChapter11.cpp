#include<iostream>
#include<stack>
#include<string>
#include<cctype>
#include<fstream>
#include<cmath>

using namespace std;

double Postfix(string expression);
double Prefix(string expression);
double Operation(char operation, double operand1, double operand2); 
bool IsOperator(char C);
bool IsNumericDigit(char C);


int main(int argc, char* argv[]) {
  if (argc > 1) {   
    ifstream fin;
    fin.open(argv[1]);
	
	string expression; 
	double result=0;
	while(!fin.eof())
	{
    	getline(fin,expression);
			
		 	if (IsOperator(expression[0]))
			{	
				result = Prefix(expression);
				cout<<result<<"\n";
			}
		else if(isdigit(expression[0]))
			{
				
				result = Postfix(expression);
				cout<<result<<"\n";
			}
		
	 }
  }
  return 0;
}

double Postfix(string expression)
{
	stack<double> S;
	double result=0;
	for(unsigned int i = 0;i< expression.length();i++) {
 
		if(expression[i] == ' ' ) 
			continue; 
		else if(IsOperator(expression[i])) {
	 
			double operand2 = S.top();
			S.pop();
			double operand1 = S.top(); 
			S.pop();
			result = Operation(expression[i], operand1, operand2);
			S.push(result);
		}
		else if(IsNumericDigit(expression[i])){
			 
			double operand = 0; 
			while(i<expression.length() && IsNumericDigit(expression[i])) {
				
				operand = (operand*10) + (expression[i] - '0'); 
				i++;
			}
			
			i--; 
			S.push(operand);
		}
		else{
			//do nothing
		}
	}
	return S.top();
}
double Prefix(string expression) 
{ 
	double result=0;
    stack<double> S; 
  
    for (int j = expression.size()-1 ; j >=0; j--) { 
		if(expression[j] == ' ' ) 
			continue; 

        else if (IsNumericDigit(expression[j])) 
		{
			double operand = 0; 
			int i=0;
			while(j>0 && IsNumericDigit(expression[j])) {
			
				operand = operand + (((expression[j] - '0'))*pow(10,i)); 

			
				i++;
				j--; 
			}
			j++;
			
			S.push(operand);
		}
          
        else if(IsOperator(expression[j])) { 
  
			double operand2 = S.top(); 
			S.pop();
			double operand1 = S.top(); 
			S.pop();

			result = Operation(expression[j], operand2, operand1);
			 
			S.push(result);
      
        } 
		else{
			//do nothing
		}
    }
    return S.top();
} 

bool IsOperator(char C)
{
	if(C == '+' || C == '-' || C == '*' || C == '/')
		return true;

	return false;
}

double Operation(char operation, double operand1, double operand2)
{	double result=0;

	if(operation == '+') 
		result= operand1 +operand2;

	else if(operation == '-') 
		result= operand1 - operand2;

	else if(operation == '*') 
		result= operand1 * operand2;

	else if(operation == '/') 
		result= operand1 / operand2;

	return result;
}

bool IsNumericDigit(char C) 
{
	if(C >= '0' && C <= '9') 
		return true;

	return false;
}