#include "StdAfx.h"
#include "Tr2ScalarExprCurve.h"
#include "include/TriMath.h"

static float perlin_wrap( float x, float a, float b, float n )
{
	return (float)((PerlinNoise1D( x, a, b, (int)n)+1.0)*0.5);
}

static float perlin_wrap_simple( float x )
{
	return (float)((PerlinNoise1D( x, 1.1, 2.0, (int)3)+1.0)*0.5);
}

static float frandom( float a, float b )
{
	return ((b-a)*((float)rand()/RAND_MAX))+a;
}

Tr2ScalarExprCurve::Tr2ScalarExprCurve( IRoot* lockobj ):
	Tr2ScalarCurve( lockobj )
{
	m_expression = "";
	m_updateDistance = false;
	m_sourcePositionA = Vector3(0.0f, 0.0f, 0.0f);
	m_sourcePositionB = Vector3(0.0f, 0.0f, 0.0f);
	m_scalarValue = 0.0f;
	m_inputVar1 = 0.0f;
	m_inputVar2 = 0.0f;
	m_inputVar3 = 0.0f;
	m_inputVar4 = 0.0f;
	m_sourceDistance = 0.0f;
	m_randomMin = 0.0f;
	m_randomMax = 1.0f;
	m_expressionParser.DefineFun( "perlin_simple", perlin_wrap_simple, false );
	m_expressionParser.DefineFun( "perlin", perlin_wrap, false );
	m_expressionParser.DefineFun( "random", frandom, false );
	m_expressionParser.DefineVar( "value", &m_scalarValue );
	m_expressionParser.DefineVar( "time", &m_localTime );
	m_expressionParser.DefineVar( "length", &m_length );
	m_expressionParser.DefineVar( "input1", &m_inputVar1 );
	m_expressionParser.DefineVar( "input2", &m_inputVar2 );
	m_expressionParser.DefineVar( "input3", &m_inputVar3 );
	m_expressionParser.DefineVar( "input4", &m_inputVar4 );
	m_expressionParser.DefineVar( "sourceDistance", &m_sourceDistance );
	m_expressionParser.DefineVar( "randomConstant", &m_randomConstant );
	m_expressionParser.DefineConst( "pi", 3.1415926f );
	m_expressionParser.DefineConst( "pi2", 2.0f*3.1415926f );
}

void Tr2ScalarExprCurve::RegenRandomConstant()
{
	m_randomConstant = frandom( m_randomMin, m_randomMax );
}

bool Tr2ScalarExprCurve::Initialize()
{
	RegenRandomConstant();
	if ( m_expression.size() )
	{
		SetExpression( m_expression );
	}
	Tr2ScalarCurve::Initialize();
	return true;
}

std::string Tr2ScalarExprCurve::GetExpression(  )
{
	return m_expression;
}

void Tr2ScalarExprCurve::SetExpression( std::string expr )
{
	m_expression = expr;
	m_expressionParser.SetExpr(m_expression);
	try
	{
		// Generate the bytecode
		m_expressionParser.Eval();
	}
	catch (mu::Parser::exception_type e)
	{
		if ( m_expression.size() )
		{
			CCP_LOGERR("SetExpression: %s",e.GetMsg().c_str());
			m_expression = "";
			m_expressionParser.SetExpr(m_expression);
		}		
	}
}

float* Tr2ScalarExprCurve::Interpolate( float* out, Tr2ScalarKey* startKey, Tr2ScalarKey* endKey )
{
	Vector3 temp;
	if( m_updateDistance )
	{
		m_sourceDistance = XMVectorGetX( XMVector3Length( XMVectorSubtract( m_sourcePositionA, m_sourcePositionB ) ) );
	}

	Tr2ScalarCurve::Interpolate( out, startKey, endKey	);
	m_scalarValue = *out;

	if ( m_expression.size() )
	{
		*out = m_expressionParser.Eval();
	}
	return out;
}

