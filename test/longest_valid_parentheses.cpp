/**
 REF http://discuss.leetcode.com/questions/212/longest-valid-parentheses
 
 Given a string containing just the characters '(' and ')', find the length of the longest valid (well-formed) parentheses substring.
 
 For "(()", the longest valid parentheses substring is "()", which has length = 2.
 
 Another example is ")()())", where the longest valid parentheses substring is "()()", which has length = 4.
**/


#include <iostream>
#include <stack>
#include <cassert>
using namespace std;

/**
 @param str - the input str
 @return -  longest parenthese substr
 **/
string solution(const string &str) {
    int max = 0, begin = -1, end = -1;
    int N = (int)str.length();
    
    stack<char> stk;
    int curLen = 0;
    for(int i=0;i<N;i++){
        if(str[i]=='('){   //additional pair
            //curLen += 1;
            stk.push('(');
        }
        else if(str[i]==')'){  //complement
            
            if(!stk.empty() && stk.top()=='('){
                stk.pop();
                curLen += 2;
                if(curLen > max){
                    max = curLen;
                    end = i;
                    begin = i - curLen + 1;
                }
            }
            else{  //end of valid sub
                //reset
                while(!stk.empty()) stk.pop();
                curLen = 0;
            }
            
        }
    }
    
    
    
    string ret = str.substr(begin,max);
    cout << "ret = " << ret << endl;
    return ret;
}


int main(int argc, char** argv)
{
    assert(solution("(()")=="()");
    assert(solution(")()())")=="()()");
    
    return 0;
}
