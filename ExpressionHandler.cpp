#include "stdafx.h"
#include "Queue.h"

#ifndef __EXPRESSIONHANDLER_HJQ__
#include "ExpressionHandler.h"
#endif

ExpressionHandler::ExpressionHandler(){ExpressionHandler(L"0");}

ExpressionHandler::ExpressionHandler(CString exp) {
	exp1=exp;
}

CString ExpressionHandler::convertToFormalExpression(CString exp) {
	CString res=exp;
	wchar_t c;
	res.Remove(' ');
	res.Remove('	');
	for(int i=res.GetLength()-1;i>0;i--) {
		c=res.GetAt(i);
		if(c=='+') {
			if(isInOperandBefore(res.GetAt(i-1)))
				res.SetAt(i,'~');
		}else if(c=='-') {
			if(isInOperandBefore(res.GetAt(i-1)))
				res.SetAt(i,'`');
		}else if(c=='(') {
			if(isAtTheEndOfOperand(res.GetAt(i-1)))
				res.Insert(i,'*');
		}
	}
	if(res.GetAt(0)=='+') res.SetAt(0,'~');
	if(res.GetAt(0)=='-') res.SetAt(0,'`');
	return res;
}

Queue<CString> ExpressionHandler::convertToQueue(CString exp) {
	Queue<CString> res;
	ExpressionTokenType preType=UNKNOWN;
	CString exp2=convertToFormalExpression(exp);
	for(int i=0,j=1;i<exp2.GetLength();) {
		preType=belongingOf(exp2.GetAt(i));
		if(preType!=LEFT_PARENTHESES && preType!=RIGHT_PARENTHESES && preType!=UNARY_OPERATOR) {
			while(j<exp2.GetLength() && preType==belongingOf(exp2.GetAt(j)))
				j++;
		}
		res.insertToTail(exp2.Mid(i,j-i));
		i=j;
		j=i+1;
	}
	return res;
}

bool ExpressionHandler::isInOperandBefore(wchar_t c) {
	return c=='+' || c=='-' || c=='*' || c=='/' || c=='^' || c=='%' || c=='(';
}

bool ExpressionHandler::isAtTheEndOfOperand(wchar_t c) {
	return (c>='0' && c<='9') || c==')';
}

ExpressionTokenType ExpressionHandler::belongingOf(wchar_t c) {
	if(c=='#') {
		return EDGE;
	}else if((c>='0' && c<='9') && c=='.') {
		return NUM;
	}else if(c=='~' || c=='`') {
		return UNARY_OPERATOR;
	}else if(c=='^') {
		return BINARY_OPERATOR_3;
	}else if(c=='%' || c=='*' || c=='/') {
		return BINARY_OPERATOR_2;
	}else if(c=='+' || c=='-') {
		return BINARY_OPERATOR_1;
	}else if(c=='('){
		return LEFT_PARENTHESES;
	}else if(c==')') {
		return RIGHT_PARENTHESES;
	}else if((c>='a' && c<='z') || (c>='A' && c<='Z')) {
		return FUNCTION;
	}
	return UNKNOWN;
}


Queue<ExpressionToken> ExpressionHandler::convertToInversed(Queue<CString> l) throw(StackEmptyException,ParenthesesException){
	Queue<ExpressionToken> res;
	Stack s;
	QueueNode<CString>* cur=l.h;
	ExpressionToken* t;
	while(cur!=NULL) {
		CString token=cur->v;
		t = new ExpressionToken(token);
		//UNKNOWN=0,NUM,EDGE,BINARY_OPERATOR,UNARY_OPERATOR,PARENTHESES,FUNCTION
		switch(t->getExpressionTokenType()) {
			case UNKNOWN:
				throw TokenException();
				break;
			case NUM:
				res.insertToTail(*t);
				break;
			case EDGE:

				break;
			case BINARY_OPERATOR_1:
			case BINARY_OPERATOR_2:
			case BINARY_OPERATOR_3:
				if(s.isEmpty()) {
					s.push(*t);
				} else {
					while((!s.isEmpty()) && (s.peak().getExpressionTokenType()>=t->getExpressionTokenType())) {
						res.insertToTail(s.pop());
					}
					s.push(*t);
				}
				break;
			case UNARY_OPERATOR:
				s.push(*t);
				break;
			case LEFT_PARENTHESES:
				s.push(*t);
				break;
			case RIGHT_PARENTHESES:
				while((!s.isEmpty()) && (s.peak().getExpressionTokenType()!=LEFT_PARENTHESES)) {
					if(s.isEmpty())
						throw ParenthesesException();
					res.insertToTail(s.pop());
				}
				s.pop();
				if((!s.isEmpty()) && (s.peak().getExpressionTokenType()==FUNCTION))
					res.insertToTail(s.pop());
				break;
			case FUNCTION:
				s.push(*t);
				break;
			default:
				break;
		}
		cur=cur->n;
	}
	while(!s.isEmpty())
	{
		if(s.peak().getExpressionTokenType()==LEFT_PARENTHESES) 
			throw ParenthesesException();
		res.insertToTail(s.pop());
	}
	return res;
}

bool ExpressionHandler::isInteger(double n) {
	return (abs(n-(int)n)<1e-8);	
}

CString ExpressionHandler::calculate(CString _exp) throw(ArithmeticException,StackEmptyException,TokenException){
	CString res;
	Queue<ExpressionToken> inversedExpression = convertToInversed(convertToQueue(_exp));
	QueueNode<ExpressionToken>* ptr = inversedExpression.h;
	Stack s;

	while(ptr!=NULL) {
		ExpressionTokenType type=ptr->v.getExpressionTokenType();
		switch(type) {
			case UNKNOWN:
				throw TokenException();
				break; 
			case NUM:
				s.push(ptr->v);
				break;
			case EDGE:
				break;
			case BINARY_OPERATOR_1:
			case BINARY_OPERATOR_2:
			case BINARY_OPERATOR_3:
				{
					CString newN;
					CString et2=s.pop().getToken();
					CString et1=s.pop().getToken();
					CString token=ptr->v.getToken();
					if(token=="+") {
						double n1,n2;
						n1=_tstof(et1);
						n2=_tstof(et2);
						newN.Format(L"%lf",n1+n2);
					} else if(token=="-") {
						double n1,n2;
						n1=_tstof(et1);
						n2=_tstof(et2);
						newN.Format(L"%lf",n1-n2);
					} else if(token=="*") {
						double n1,n2;
						n1=_tstof(et1);
						n2=_tstof(et2);
						newN.Format(L"%lf",n1*n2);
					} else if(token=="/") {
						double n1,n2;
						n1=_tstof(et1);
						n2=_tstof(et2);
						if(n2==0)
							throw ArithmeticException();
						newN.Format(L"%lf",n1/n2);
					} else if(token=="%") {
						if(et1.Find('.')>=0 || et2.Find('.')>=0)
							throw TokenException();
						else{
							long n1,n2;
							n1=_tstol(et1);
							n2=_tstol(et2);
							if(n2==0)
								throw ArithmeticException();
							newN.Format(L"%ld",n1%n2);
						}
					} else if(token=="^") {
						double n1,n2;
						n1=_tstof(et1);
						n2=_tstof(et2);
						if(n1==0 && n2==0)
							throw ArithmeticException();
						newN.Format(L"%lf",pow(n1,n2));
					}
					s.push(*(new ExpressionToken(newN)));
					break;
				}
			case UNARY_OPERATOR:
				{
					CString et=s.pop().getToken();
					CString token=ptr->v.getToken();
					if(token=="~") {
						s.push(*(new ExpressionToken(et)));
					} else if (token=="`") {
						if(et.GetAt(0)=='-') {
							et = et.Mid(1);
						} else {
							et.Insert(0,'-');
						}
						s.push(*(new ExpressionToken(et)));
					}
					break;
				}
			case LEFT_PARENTHESES:
				break;
			case RIGHT_PARENTHESES:
				break;
			case FUNCTION:
				{
					CString token=ptr->v.getToken();
					if(token=="sin") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						et.Format(L"%lf",sin(net));
						s.push(*(new ExpressionToken(et)));
					} else if(token=="cos") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						et.Format(L"%lf",cos(net));
						s.push(*(new ExpressionToken(et)));
					} else if(token=="tan") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						if(isInteger((net-M_PI_2)/M_PI))
							throw ArithmeticException();
						et.Format(L"%lf",tan(net));
						s.push(*(new ExpressionToken(et)));
					} else if(token=="cot") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						if(isInteger(net/M_PI))
							throw ArithmeticException();
						et.Format(L"%lf",cos(net)/sin(net));
						s.push(*(new ExpressionToken(et)));
					} else if(token=="sec") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						if(isInteger((net-M_PI_2)/M_PI))
							throw ArithmeticException();
						et.Format(L"%lf",1/cos(net));
						s.push(*(new ExpressionToken(et)));
					} else if(token=="csc") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						if(isInteger(net/M_PI))
							throw ArithmeticException();
						et.Format(L"%lf",1/sin(net));
						s.push(*(new ExpressionToken(et)));
					} else if(token=="arcsin") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						if(abs(net)>1)
							throw ArithmeticException();
						et.Format(L"%lf",asin(net));
						s.push(*(new ExpressionToken(et)));
					} else if(token=="arccos") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						if(abs(net)>1)
							throw ArithmeticException();
						et.Format(L"%lf",acos(net));
						s.push(*(new ExpressionToken(et)));
					} else if(token=="arctan") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						et.Format(L"%lf",atan(net));
						s.push(*(new ExpressionToken(et)));
					}else if(token=="RND") {
						double rnd;
						CString rnds;
						rnd=(double)rand()/RAND_MAX;
						rnds.Format(L"%lf",rnd);
						s.push(*(new ExpressionToken(rnds)));
					}else if(token=="sinh") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						et.Format(L"%lf",sinh(net));
						s.push(*(new ExpressionToken(et)));
					}else if(token=="cosh") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						et.Format(L"%lf",cosh(net));
						s.push(*(new ExpressionToken(et)));
					}else if(token=="tanh") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						et.Format(L"%lf",tanh(net));
						s.push(*(new ExpressionToken(et)));
					}else if(token=="coth") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						if(net==0)
							throw ArithmeticException();
						et.Format(L"%lf",1/tanh(net));
						s.push(*(new ExpressionToken(et)));
					}else if(token=="sech") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						et.Format(L"%lf",1/cosh(net));
						s.push(*(new ExpressionToken(et)));
					}else if(token=="csch") {
						CString et=s.pop().getToken();
						double net=_tstof(et);
						if(net==0)
							throw ArithmeticException();
						et.Format(L"%lf",1/sinh(net));
						s.push(*(new ExpressionToken(et)));
					} else {
						throw TokenException();
					}
				}
				break;
			default:
				break;
		}
		ptr=ptr->n;
	}
	res=s.pop().getToken();
	return res;
}
