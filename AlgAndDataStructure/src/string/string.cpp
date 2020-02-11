#include <string>
#include <algorithm>
using namespace std;

bool isStringPalindrome(string s) {
	string str = s;
	//reverse(s.begin(), s.end());
	//return str == s;
	int i = 0, j = 0;
	j = s.length() - 1;

	while (i <= j) {
		if (s[i] != s[j])
		{
			return false;
		}
		else {
			i++;
			j--;
		}
	}
	return true;
}


string longestPalindrome(string s) {
	int pos = 0, idx = 0; //用于记录从字符串中开始搜索的位置
	int len = 0; //用于记录回文串的长度
	int maxlen = 0; //用于记录最大的回文串长度
	string tmpstr;//用于记录当前测试的子串
	string strPal;

	if (s.length() == 0 || s.length() == 1) {
		return s;
	}

	len = 1;
	//maxlen = 2;

	//每一个位置都尝试一下
	for (idx = 0; (string::size_type)idx + len <= s.length(); idx++, len = max(maxlen, 1)) {
		for (pos = idx; (string::size_type)pos + len <= s.length();) {
			//从当前位置获取一个子串
			tmpstr = s.substr(pos, len);

			//当前子串是回文串，更新最大子串长度，
			//基于当前的子串，增加子串的长度，继续尝试
			if (isStringPalindrome(tmpstr)) {
				if (len > maxlen) {
					maxlen = len;
					strPal = tmpstr;
				}
				len++;
			}
			else {
				//如果当前子串不是回文串，继续增加子串长度尝试
				len++;
			}
		}
	}
	return strPal;
}