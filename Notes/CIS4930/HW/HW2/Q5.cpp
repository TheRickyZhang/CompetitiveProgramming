class Solution {
public:
    bool isValid(string s) {
        std::unordered_map<char, char> bracketMap = {{')', '('}, {'}', '{'}, {']', '['}};
        std::stack<char> stack;
        for(int i = 0; i < s.size(); ++i) {
            if(s[i] == '(' || s[i] == '{' || s[i] == '['){
                stack.push(s[i]);
            }
            else if(s[i] == ')' || s[i] == '}' || s[i] == ']') {
                if(stack.empty() || stack.top() != bracketMap[s[i]]){
                    return false;
                }
                stack.pop();
            }
        }
        if(stack.size() != 0) {
            return false;
        }
        return true;
    }
};