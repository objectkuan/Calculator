#include "stdafx.h"
#ifndef __EXPRESSIONTOKEN_HJQ__
#include "ExpressionToken.h"
#endif

ExpressionToken::ExpressionToken() {
	token="";
	type=UNKNOWN;
}

ExpressionToken::ExpressionToken(CString t) {
	token=t;
	type=tokenTypeOf(token);
}

CString ExpressionToken::getToken() {
	return token;
}

ExpressionTokenType ExpressionToken::getExpressionTokenType() {
	return type;
}

ExpressionTokenType ExpressionToken::tokenTypeOf(CString t) {
	if(t.GetAt(0)=='#' && t.GetLength()==1) {
		return EDGE;
	}else if((t.GetAt(0)>='0' && t.GetAt(0)<='9') && (isNumber(t))) {
		return NUM;
	}else if((t.GetAt(0)=='~' || t.GetAt(0)=='`') && t.GetLength()==1) {
		return UNARY_OPERATOR;
	}else if((t.GetAt(0)=='^') && t.GetLength()==1) {
		return BINARY_OPERATOR_3;
	}else if((t.GetAt(0)=='*' || t.GetAt(0)=='/' || t.GetAt(0)=='%') && t.GetLength()==1){
		return BINARY_OPERATOR_2;
	}else if((t.GetAt(0)=='+' || t.GetAt(0)=='-') && t.GetLength()==1) {
		return BINARY_OPERATOR_1;
	}else if(t.GetAt(0)=='(' && t.GetLength()==1) {
		return LEFT_PARENTHESES;
	}else if(t.GetAt(0)==')' && t.GetLength()==1){
		return RIGHT_PARENTHESES;
	}else if((t.GetAt(0)>='a' && t.GetAt(0)<='z') || (t.GetAt(0)>='A' && t.GetAt(0)<='Z')){
		return FUNCTION;
	}
	return UNKNOWN;
}

bool ExpressionToken::isNumber(CString n) {
	bool point=false;
	for(int i=0;i<n.GetLength();i++) {
		wchar_t c= n.GetAt(i);
		if(c=='.') {
			if(point)
				return false;
			point=true;
		} else 
		if(c>'9' || c<'0')
			return false;
	}
	return true;
}
