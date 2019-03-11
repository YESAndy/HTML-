//括号匹配
//S  =  S0 + "(" + S1 + ")" + S2 + S3 
//其中S0和S3不含括号，且S1中左右括号数目相等，则S匹配当且仅当S1和S2均匹配。 
//按照这一理解，可采用分治策略设计算法如下：将表达式划分为子表达式S0、S1和S2，分别递归地判断S1和S2是否匹配。

void trim(const char exp[], int& lo, int& hi) {//删除表达式exp【lo，hi】不含括号的最长前缀、后缀
	while ((lo <= hi) && (exp[lo] != '(') && (exp[lo] != ')')) lo++;//查找第一个括号
	while ((lo <= hi) && (exp[hi] != '(') && (exp[hi] != ')')) hi--;//和最后一个括号
}

int divide(const char exp[], int lo, int hi) {//切分表达式exp【lo，hi】，使exp匹配仅当他们匹配
	int mi = lo; int crc = 1;//crc为【lo，mi】范围内左右括号数目之差
	while ((0 < crc) && (++mi < hi))//逐个检查各字符，直到左右括号数目相等，或者越界
	{
		if (exp[mi] == ')') crc--;//左右括号分别计数
		if (exp[mi] == '(') crc++;//合法的情况必须是前缀的‘（’数不小于‘）’数
	}
	return mi;//若mi《=hi则为合法切分点；否则，意味着局部不可能匹配
}

bool paren(const char exp[], int lo, int hi) {//检查表达式中exp【lo，hi】是否括号匹配
	trim(exp, lo, hi); if (lo > hi) return true;//清除不含括号的前缀、后缀
	if (exp[lo] != '(') return false;//首字符非左括号则不匹配
	if (exp[hi] != ')') return false;//末字符非右括号则不匹配
	int mi = divide(exp, lo, hi);//确定适合的切分点
	if (mi > hi) return false;//切分点不合法，意味着局部以至整体不匹配
	return paren(exp, lo + 1, mi - 1) && paren(exp, mi + 1, hi);//分别检查左右子表达式
}

bool paren_d(const string exp[], int lo, int hi) {//检查表达式中exp【lo，hi】html标识符是否匹配，迭代版
	Stack<string> S;
	for (int i = lo; i<hi; i++){//逐个检查
		if ((exp[i] == "<mytag>") || (exp[i] == "<body>") || (exp[i] == "<font>") || (exp[i] == "<h1>") || (exp[i] == "<left>") || (exp[i] == "<p>"))
		{ S.push(exp[i]); break; }
		else if ((exp[i] == "</mytag>") && ((S.empty()) || ("<mytag>" != S.pop()))) { return false; break; }
		else if ((exp[i] == "</body>") && ((S.empty()) || ("<body>" != S.pop()))) { return false; break; }
		else if ((exp[i] == "</font>") && ((S.empty()) || ("<font>" != S.pop()))) { return false; break; }
		else if ((exp[i] == "</h1>") && ((S.empty()) || ("<h1>" != S.pop()))) { return false; break; }
		else if ((exp[i] == "</left>") && ((S.empty()) || ("<left>" != S.pop()))) { return false; break; }
		else if ((exp[i] == "</p>") && ((S.empty()) || ("<p>" != S.pop()))) { return false; break; }
		}
	return S.empty();
}
