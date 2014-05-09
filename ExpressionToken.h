#ifndef __EXPRESSIONTOKEN_HJQ__
#define __EXPRESSIONTOKEN_HJQ__

typedef enum{
	UNKNOWN=0,
	NUM,
	EDGE,
	LEFT_PARENTHESES,
	RIGHT_PARENTHESES,
	BINARY_OPERATOR_1,
	BINARY_OPERATOR_2,
	BINARY_OPERATOR_3,
	UNARY_OPERATOR,
	FUNCTION
} ExpressionTokenType;

class ExpressionToken {
public:
	ExpressionToken();
	ExpressionToken(CString t);
	CString getToken();
	ExpressionTokenType getExpressionTokenType();
private:
	CString token;
	ExpressionTokenType type;
	bool isNumber(CString n);
	ExpressionTokenType tokenTypeOf(CString t);
};

#endif
