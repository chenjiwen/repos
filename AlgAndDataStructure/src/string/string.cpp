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
	int pos = 0, idx = 0; //���ڼ�¼���ַ����п�ʼ������λ��
	int len = 0; //���ڼ�¼���Ĵ��ĳ���
	int maxlen = 0; //���ڼ�¼���Ļ��Ĵ�����
	string tmpstr;//���ڼ�¼��ǰ���Ե��Ӵ�
	string strPal;

	if (s.length() == 0 || s.length() == 1) {
		return s;
	}

	len = 1;
	//maxlen = 2;

	//ÿһ��λ�ö�����һ��
	for (idx = 0; (string::size_type)idx + len <= s.length(); idx++, len = max(maxlen, 1)) {
		for (pos = idx; (string::size_type)pos + len <= s.length();) {
			//�ӵ�ǰλ�û�ȡһ���Ӵ�
			tmpstr = s.substr(pos, len);

			//��ǰ�Ӵ��ǻ��Ĵ�����������Ӵ����ȣ�
			//���ڵ�ǰ���Ӵ��������Ӵ��ĳ��ȣ���������
			if (isStringPalindrome(tmpstr)) {
				if (len > maxlen) {
					maxlen = len;
					strPal = tmpstr;
				}
				len++;
			}
			else {
				//�����ǰ�Ӵ����ǻ��Ĵ������������Ӵ����ȳ���
				len++;
			}
		}
	}
	return strPal;
}