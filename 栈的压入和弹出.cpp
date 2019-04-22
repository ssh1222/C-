class Solution {
public:
	bool IsPopOrder(vector<int> pushV, vector<int> popV)
	{
		if (pushV.size() != popV.size())
			return false;
		stack<int> st;
		int pushidx = 0;
		int popidx = 0;
		while (popidx < popV.size()){
			while (st.empty() || st.top() != popV[popidx]){
				if (pushidx < pushV.size())
					st.push(pushV[pushidx++]);
				else
					return false;
			}
			st.pop();
			popidx++;
		}
		return st.empty();
	}
};