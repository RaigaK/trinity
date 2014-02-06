#pragma once
#ifndef Tr2ScalarExprCurve_h
#define Tr2ScalarExprCurve_h

#include "Tr2ScalarCurve.h"
#include <muParser.h>

BLUE_CLASS( Tr2ScalarExprCurve ):
     public Tr2ScalarCurve
{
public:
    EXPOSE_TO_BLUE();

	mu::Parser m_expressionParser;
	std::string m_expression;
	float m_scalarValue;
	float m_inputVar1;
	float m_inputVar2;
	float m_inputVar3;
	float m_inputVar4;

	// Random
	float m_randomConstant;
	float m_randomMin;
	float m_randomMax;

	void RegenRandomConstant();
	// For influencing the expression by 3d locations
	Vector3 m_sourcePositionA;
	Vector3 m_sourcePositionB;
	float	m_sourceDistance;
	bool	m_updateDistance;

	bool Initialize();
	
	std::string GetExpression();
	void SetExpression( std::string expr );

    Tr2ScalarExprCurve( IRoot* lockobj = NULL );
	float* Interpolate( float* out, Tr2ScalarKey* startKey, Tr2ScalarKey* endKey );
};

TYPEDEF_BLUECLASS( Tr2ScalarExprCurve );
#endif //Tr2ScalarExprCurve_h
