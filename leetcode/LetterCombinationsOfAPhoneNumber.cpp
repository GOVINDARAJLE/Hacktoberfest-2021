//Problem Link - https://leetcode.com/problems/letter-combinations-of-a-phone-number/

//Solution

class Solution {
public:
    void solve(string digits, int i, vector<string> mp, vector<string>& result, string& combi){
        if(i==digits.size()){
            result.push_back(combi);
            return;
        }
        for(auto c:mp[digits[i]-'2']){
            combi.push_back(c);
            solve(digits, i+1, mp, result, combi);
            combi.pop_back();
        }
    }
    
    vector<string> letterCombinations(string digits) {
        //------------------------------RECURSIVE SOLUTION--------------------------------
        if(digits=="")
            return {};
        vector<string> mp = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        vector<string> result;
        string combi="";
        solve(digits, 0, mp, result, combi);
        return result;
        
        
        //-------------------------------ITERATIVE SOLUTION----------------------------
        if(digits=="")
            return {};
        vector<string> mp{"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};
        deque<string> dq;
        dq.push_back("");
        
        for(auto digit:digits){
            int n = dq.size();
            for(int j=0; j<n; j++){
                string old = dq.front();
                dq.pop_front();
                for(auto newChar:mp[digit-'2']){
                    string temp = old+newChar;
                    dq.push_back(temp);
                }
            }
        }
        vector<string> result;
        while(!dq.empty()){
            result.push_back(dq.front());
            dq.pop_front();
        }
        return result;
    }
};
