////////////////////////////////////////////////////////////
//
//    Created:   June 2010
//    Copyright: CCP 2010
//
#pragma once
#ifndef Tr2ShaderParameterDescription_H
#define Tr2ShaderParameterDescription_H

// Blue forward declarations
BLUE_DECLARE( Tr2ShaderParameterDescription );
BLUE_DECLARE( Tr2ShaderFloat4Desc );
BLUE_DECLARE( Tr2ShaderFloat3Desc );
BLUE_DECLARE( Tr2ShaderFloat2Desc );
BLUE_DECLARE( Tr2ShaderFloatDesc );
BLUE_DECLARE( Tr2ShaderTexDesc );
BLUE_DECLARE( Tr2ShaderMaterialParameter);

// Forward declarations
struct ITriEffectParameter;

// --------------------------------------------------------------------------------------
// Description:
//   Tr2ShaderParameterDescription is virtual class for describing a material parameter 
//   for better UI.  Tr2HighLevelShader has a list of these.
//   Other classes such as Tr2ShaderFloat4Desc implement this class.
// SeeAlso:
//   Tr2HighLevelShader, Tr2ShaderFloat4Desc, Tr2ShaderFloat3Desc, Tr2ShaderFloat2Desc, 
//   Tr2ShaderFloatDesc, Tr2ShaderTexDesc
// --------------------------------------------------------------------------------------

BLUE_CLASS( Tr2ShaderParameterDescription ): public IInitialize
{
public:
	Tr2ShaderParameterDescription( IRoot* lockobj = NULL );
	virtual ~Tr2ShaderParameterDescription() {}

	EXPOSE_TO_BLUE();

	/////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	virtual bool Initialize();

	const std::string& GetShaderParameterName() const;
	const std::string& GetArtistFriendlyName() const;
	const std::string& GetHelpText() const;

	bool IsPermutationTag() const;

	const std::string& GetPermutationDefine() const;
	unsigned int GetPermuteTagHash() const;

	virtual ITriEffectParameter* CreateDefaultParameter( void ) const { return NULL; }

protected:
	// The name used by the shader/engine for data binding, not exposed to the artist.
	std::string m_parameterName;

private:
	// The name shown in the UI for this parameter.
	std::string m_artistName;
	// A description of what this parameter does in plain, artist-friendly English.
	std::string m_helpText;
	// The 'section' used for grouping parameters together (for example, all params that 
	// affect specular could be in one spot in the UI)
	std::string m_sectionName;

	// The permute flag emitted if this value is non-zero.  If this is empty, then there 
	// are no permutations associated with this parameter.
	std::string m_permuteDefineName;
	// This is the FNV1 hash of the parameterName field.
	unsigned int m_permuteTagHash; 
};
TYPEDEF_BLUECLASS(Tr2ShaderParameterDescription);

// --------------------------------------------------------------------------------------
// Description:
//   Tr2ShaderFloat4Desc implements Tr2ShaderParameterDescription.
//   This class holds the defaults and ranges for a float4 parameter.
// SeeAlso:
//   Tr2HighLevelShader, Tr2ShaderParameterDescription
// --------------------------------------------------------------------------------------
class Tr2ShaderFloat4Desc : public Tr2ShaderParameterDescription
{
public:
	Tr2ShaderFloat4Desc( IRoot* lockobj = NULL );

	EXPOSE_TO_BLUE();

	/////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	virtual bool Initialize();

	virtual ITriEffectParameter* CreateDefaultParameter( void ) const;

private:
	Vector4 m_defaultValue;
	Vector4 m_minimumValue;
	Vector4 m_maximumValue;

	std::string m_thumbnailResPath;
	std::string m_valueToNameMethod;
	std::string m_nameToValueMethod;

	bool m_isColor;
	bool m_normalize;
};
TYPEDEF_BLUECLASS(Tr2ShaderFloat4Desc);

// --------------------------------------------------------------------------------------
// Description:
//   Tr2ShaderFloat3Desc implements Tr2ShaderParameterDescription.   
//   This class holds the defaults and ranges for a float3 parameter.
// SeeAlso:
//   Tr2HighLevelShader, Tr2ShaderParameterDescription
// --------------------------------------------------------------------------------------
class Tr2ShaderFloat3Desc : public Tr2ShaderParameterDescription
{
public:
	Tr2ShaderFloat3Desc( IRoot* lockobj = NULL );

	EXPOSE_TO_BLUE();

	/////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	virtual bool Initialize();

	virtual ITriEffectParameter* CreateDefaultParameter( void ) const;

private:
	Vector3 m_defaultValue;
	Vector3 m_minimumValue;
	Vector3 m_maximumValue;

	std::string m_thumbnailResPath;
	std::string m_valueToNameMethod;
	std::string m_nameToValueMethod;

	bool m_isColor;
	bool m_normalize;
};
TYPEDEF_BLUECLASS(Tr2ShaderFloat3Desc);

// --------------------------------------------------------------------------------------
// Description:
//   Tr2ShaderFloat2Desc implements Tr2ShaderParameterDescription.   
//   This class holds the defaults and ranges for a float2 parameter.
// SeeAlso:
//   Tr2HighLevelShader, Tr2ShaderParameterDescription
// --------------------------------------------------------------------------------------
class Tr2ShaderFloat2Desc : public Tr2ShaderParameterDescription
{
public:
	Tr2ShaderFloat2Desc( IRoot* lockobj = NULL );

	EXPOSE_TO_BLUE();

	/////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	virtual bool Initialize();

	virtual ITriEffectParameter* CreateDefaultParameter( void ) const;

private:
	Vector2 m_defaultValue;
	Vector2 m_minimumValue;
	Vector2 m_maximumValue;

	std::string m_thumbnailResPath;
	std::string m_valueToNameMethod;
	std::string m_nameToValueMethod;

	bool m_normalize;
};
TYPEDEF_BLUECLASS(Tr2ShaderFloat2Desc);

// --------------------------------------------------------------------------------------
// Description:
//   Tr2ShaderFloatDesc implements Tr2ShaderParameterDescription.   
//   This class holds the defaults and ranges for a float parameter.
// SeeAlso:
//   Tr2HighLevelShader, Tr2ShaderParameterDescription
// --------------------------------------------------------------------------------------
class Tr2ShaderFloatDesc : public Tr2ShaderParameterDescription
{
public:
	Tr2ShaderFloatDesc(IRoot* lockobj = NULL);

	EXPOSE_TO_BLUE();

	/////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	virtual bool Initialize();

	virtual ITriEffectParameter* CreateDefaultParameter( void ) const;

private:
	float m_defaultValue;
	float m_minimumValue;
	float m_maximumValue;

	std::string m_thumbnailResPath;
	std::string m_valueToNameMethod;
	std::string m_nameToValueMethod;

	bool m_normalize;
};
TYPEDEF_BLUECLASS(Tr2ShaderFloatDesc);

// --------------------------------------------------------------------------------------
// Description:
//   Tr2ShaderTexDesc is implements the Tr2ShaderParameterDescription.
//   
//   This class holds the defaults and ranges for a texture parameter.
// SeeAlso:
//   Tr2HighLevelShader, Tr2ShaderParameterDescription
// --------------------------------------------------------------------------------------
class Tr2ShaderTexDesc : public Tr2ShaderParameterDescription
{
public:
	Tr2ShaderTexDesc(IRoot* lockobj = NULL);

	EXPOSE_TO_BLUE();

	/////////////////////////////////////////////////////////////////////////////////////
	// IInitialize
	virtual bool Initialize();

	virtual ITriEffectParameter* CreateDefaultParameter( void ) const;

private:
	std::string m_defaultValue;
};
TYPEDEF_BLUECLASS(Tr2ShaderTexDesc);

#endif
