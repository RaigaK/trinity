#pragma once
#ifndef Tr2MayaAnimationEngine_h
#define Tr2MayaAnimationEngine_h

#if BLUE_WITH_PYTHON

enum InfinityType 
{
	INFINITY_CONSTANT = 0,
	INFINITY_LINEAR = 1,
	INFINITY_CYCLE = 3,
	INFINITY_CYCLE_RELATIVE = 4,
	INFINITY_OSCILLATE = 5
};
typedef enum InfinityType InfinityType;

struct Tr2MayaAnimSegment
{
	float		m_time;			// start of segment
	float		m_value;		// value at start of segment
};

struct Tr2MayaAnimHermiteSegment : public Tr2MayaAnimSegment //Hermite
{

	float		m_fCoeff[4];	// Bezier x parameters
	bool		m_isStep;
	bool		m_isStepNext;
};
BLUE_DECLARE_STRUCTURE_LIST( Tr2MayaAnimHermiteSegment );


struct Tr2MayaAnimBezierSegment : public Tr2MayaAnimSegment//Bezier
{
	float		m_fCoeff[4];	// Bezier x parameters
	float		m_fPolyY[4];	// Bezier y parameters
	bool		m_isStep;		// value fixed to start value
	bool		m_isStepNext;	// value fixed to the start value of next segment
	bool		m_isLinear;		// the control points make the polynomial linear
};
BLUE_DECLARE_STRUCTURE_LIST( Tr2MayaAnimBezierSegment );

struct Tr2MayaAnimCurve
{
	int		m_numSegments;
	int		m_segmentOffset;
	float	m_endTime;
	float	m_endValue;
	float	m_inTangent;
	float	m_outTangent;
	char	m_preInfinity;
	char	m_postInfinity;
	bool	m_isWeighted;
};
BLUE_DECLARE_STRUCTURE_LIST( Tr2MayaAnimCurve );

BLUE_CLASS( Tr2MayaAnimationEngine ):
     public IRoot
{
public:
    EXPOSE_TO_BLUE();
    Tr2MayaAnimationEngine( IRoot* lockobj = NULL );
	~Tr2MayaAnimationEngine();
	float evaluate( int curveIndex, float time );
	float getLength( int curveIndex );
	inline size_t getNumberOfCurves( void ) const { return m_curves.size(); }

private:

	PTr2MayaAnimCurveStructureList			m_curves;
	PTr2MayaAnimHermiteSegmentStructureList	m_hermiteSegments;
	PTr2MayaAnimBezierSegmentStructureList	m_bezierSegments;	
	int*									m_evalCache;
	int										m_currentCurveIndex;

	// evaluate curves
	float evaluateHermite( const Tr2MayaAnimHermiteSegment *segment, float time ) const;
	float evaluateBezier( const Tr2MayaAnimBezierSegment *segment, float time, float nextSegmentTime ) const;	

	inline bool find( const Tr2MayaAnimCurve *animCurve, float time, void* firstSegment, size_t segmentSize, int *index ) const;
	float evaluateImp( const Tr2MayaAnimCurve *animCurve, float time, void* firstSegment, size_t segmentSize );

	// evaluate infinities
	float evaluateInfinities( const Tr2MayaAnimCurve *animCurve, void* firstSegment, size_t segmentSize, float time, bool evalPre );

	float evaluateInfinityLinearPre( const Tr2MayaAnimCurve *animCurve, void* firstSegment, size_t segmentSize, float time );
	float evaluateInfinityLinearPost( const Tr2MayaAnimCurve *animCurve, float time );

	inline void evaluateInfinityCycleSetup( const Tr2MayaAnimCurve *animCurve, void* firstSegment, size_t segmentSize, float time, float* firstTime, 
									float* lastTime, float *factoredTime, float *remainder ) const;
	float evaluateInfinityCyclePre( const Tr2MayaAnimCurve *animCurve, void* firstSegment, size_t segmentSize, float time );
	float evaluateInfinityCyclePost( const Tr2MayaAnimCurve *animCurve, void* firstSegment, size_t segmentSize, float time );

	inline void evaluateInfinityCycleRelativeSetup( const Tr2MayaAnimCurve *animCurve, void* firstSegment, size_t segmentSize, float time, float* firstTime, 
											float* lastTime, float *factoredTime, float *remainder, float* valueRange, double *numCycles ) const;
	float evaluateInfinityCycleRelativePre( const Tr2MayaAnimCurve *animCurve, void* firstSegment, size_t segmentSize, float time );
	float evaluateInfinityCycleRelativePost( const Tr2MayaAnimCurve *animCurve, void* firstSegment, size_t segmentSize, float time );

	inline void evaluateInfinityOscillateSetup( const Tr2MayaAnimCurve *animCurve, void* firstSegment, size_t segmentSize, float time, float* firstTime, 
										float* lastTime, float *factoredTime, float *remainder, double *numCycles ) const;
	float evaluateInfinityOscillatePre( const Tr2MayaAnimCurve *animCurve, void* firstSegment, size_t segmentSize, float time );
	float evaluateInfinityOscillatePost( const Tr2MayaAnimCurve *animCurve, void* firstSegment, size_t segmentSize, float time );


};

BLUE_CLASS( Tr2MayaAnimationCurveInfo ):
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	Tr2MayaAnimationCurveInfo( IRoot* lockobj = NULL );
	std::string					m_name;
	std::string					m_type;
	int							m_index;
	bool						m_isStatic;
	float						m_staticValue;
};
BLUE_DECLARE_VECTOR( Tr2MayaAnimationCurveInfo );

BLUE_CLASS( Tr2MayaAnimationEngineInfo ):
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	Tr2MayaAnimationEngineInfo( IRoot* lockobj = NULL );
	std::string							m_name;
	float								m_fps;
	PTr2MayaAnimationCurveInfoVector	m_curves;
};

TYPEDEF_BLUECLASS( Tr2MayaAnimationEngine );
TYPEDEF_BLUECLASS( Tr2MayaAnimationEngineInfo );
TYPEDEF_BLUECLASS( Tr2MayaAnimationCurveInfo );

#endif

#endif //Tr2MayaAnimationEngine_h

