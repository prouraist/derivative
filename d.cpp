#include<bits/stdc++.h>
using namespace std;

void deleteSpaces(string &s)
{
	int k;
	while((k = s.find(' '))!=-1)
		s.erase(s.begin()+k);
}


string d(string s)
{
	int bracket=0;

	for(int i = s.size()-1; i>=0; i--)
	{
		if (s[i]=='(')
			bracket++;
		else if (s[i]==')')
			bracket--;
		else if (!bracket)
		{
			if (s[i]=='+')
				return "((" + d(s.substr(0,i)) + ")+(" + d(s.substr(i+1)) + "))";
			if (s[i]=='-')
				return "((" + d(s.substr(0,i)) + ")-(" + d(s.substr(i+1)) + "))";
		}
	}

	bracket=0;

	for(int i = s.size()-1; i>=0; i--)
	{
		if (s[i]=='(')
			bracket++;
		else if (s[i]==')')
			bracket--;
		else if (!bracket)
		{
			if (s[i]=='*' && (s[i - 1] != '*') && (s[i + 1] != '*')){
				return "((" + d(s.substr(0, i)) + ")*(" + s.substr(i+1) + ")+(" +
				   	   s.substr(0, i) + ")*(" + d(s.substr(i+1)) + "))";
			}
			if (s[i]=='/')
				return "(((" + d(s.substr(0, i)) + ")*(" + s.substr(i + 1) + ")-(" +
					   s.substr(0, i) + ")*(" + d(s.substr(i + 1)) + "))/((" + s.substr(i + 1) + ")**2))";
		}
	}

	bracket = 0;

	for (unsigned i = 0; i < s.size(); ++i)
	{
		if (s[i]=='(')
			bracket++;
		else if (s[i]==')')
			bracket--;
		else if (!bracket && s[i] == '*' && s[i + 1] == '*'){
            string st = s.substr(i+2);
            string x = s.substr(0, i);

            bool o1 = false;
            bool o2 = false;
            for(int u=0; u<st.size(); u++)
                if (st[u]=='x') o1 = true;
            for(int u=0; u<x.size(); u++)
                if (x[u]=='x') o2 = true;

            if (!o1)
                return "(" + st + ")*((" + x + ")**(" + st + "-1))*(" + d(x) + ")";
            else
                return "(" + s + ")*(" + d(s.substr(i + 2) + "*ln(" + s.substr(0, i) + ")") + ")";

		}
	}

	if (s[0] == '(' && s[s.size() - 1] == ')')
		return d(s.substr(1, s.size() - 2));

	if ((int)s.find("ln")==0)
		return "(1/" + s.substr(2) + "*(" + d(s.substr(2)) + "))";

	if ((int)s.find("arctg")==0)
		return "(1/(1+" + s.substr(5) + "**2)*("+ d(s.substr(5)) + "))";

	if ((int)s.find("arcctg")==0)
		return "((-1)/(1+" + s.substr(6) + "**2)*(" + d(s.substr(6)) + "))";

	if ((int)s.find("arcsin")==0)
		return "(1/((1-" + s.substr(6) + "**2)**0.5)*(" + d(s.substr(6)) + "))";

	if ((int)s.find("arccos")==0)
		return "((-1)/((1-" + s.substr(6) + "**2)**0.5)*(" + d(s.substr(6)) + "))";

	if ((int)s.find("sin")==0)
		return "(cos" + s.substr(3) + "*(" + d(s.substr(3)) + "))";

	if ((int)s.find("cos")==0)
		return "((-sin" + s.substr(3) + ")*(" + d(s.substr(3)) + "))";

	if ((int)s.find("ctg")==0)
		return "((-1)/(sin" + s.substr(3) + "**2)*(" + d(s.substr(3)) + "))"
			;
	if ((int)s.find("tg")==0)
		return "(1/(cos" + s.substr(2) + "**2)*(" + d(s.substr(2)) + "))";


	if (s == "x")
		return "(1)";

	return "(0)";
}


int main()
{
	freopen("deriv.in", "r", stdin);
	freopen("deriv.out", "w", stdout);

	string s;

	while(getline(cin, s))
	{
		deleteSpaces(s);

		cout << d(s) << endl;
	}

	return 0;
}
