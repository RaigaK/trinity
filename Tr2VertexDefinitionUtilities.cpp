////////////////////////////////////////////////////////////
//
//    Created:   July 2013
//    Copyright: CCP 2013
//

#include "StdAfx.h"
#include "Tr2VertexDefinitionUtilities.h"

// --------------------------------------------------------------------------------------
// Description:
//   Converts Granny data type definition to Trinity vertex type.  
// Arguments:
//   src - Granny data type definition
// Return Value:
//   Trinity vertex type corresponding to input Granny type
// --------------------------------------------------------------------------------------
Tr2VertexDefinition::DataType ConvertGrannyTypeToDataType( const granny_data_type_definition& src )
{
	const unsigned width = std::max( src.ArrayWidth, 1 );

	unsigned type = 0;

	switch (src.Type)
	{
	case GrannyInt8Member:
		type = Tr2VertexDefinition::DT_INT8;
		break;
	case GrannyUInt8Member:
		type = Tr2VertexDefinition::DT_INT8 | Tr2VertexDefinition::DT_UNSIGNED_BIT;
		break;
	case GrannyInt16Member:
		type = Tr2VertexDefinition::DT_INT16;
		break;
	case GrannyUInt16Member:
		type = Tr2VertexDefinition::DT_INT16 | Tr2VertexDefinition::DT_UNSIGNED_BIT;
		break;
	case GrannyInt32Member:
		type = Tr2VertexDefinition::DT_INT32;
		break;
	case GrannyUInt32Member:
		type = Tr2VertexDefinition::DT_INT32 | Tr2VertexDefinition::DT_UNSIGNED_BIT;
		break;
	case GrannyReal16Member:
		type = Tr2VertexDefinition::DT_FLOAT16;
		break;
	case GrannyNormalUInt8Member:
		type = Tr2VertexDefinition::DT_INT8 | Tr2VertexDefinition::DT_UNSIGNED_BIT | Tr2VertexDefinition::DT_NORMALIZED_BIT;
		break;
	case GrannyNormalUInt16Member:
		type = Tr2VertexDefinition::DT_INT16 | Tr2VertexDefinition::DT_UNSIGNED_BIT | Tr2VertexDefinition::DT_NORMALIZED_BIT;
		break;
	case GrannyReal32Member:
		type = Tr2VertexDefinition::DT_FLOAT32;
		break;
	default:
		return Tr2VertexDefinition::DT_UNKNOWN_TYPE;
	}

	unsigned size = std::max( 1, src.ArrayWidth ) - 1;
	type |= size << Tr2VertexDefinition::DT_SIZE_OFFSET;

	return static_cast<Tr2VertexDefinition::DataType>(type);
}

// --------------------------------------------------------------------------------------
// Description:
//   Converts Granny vertex definition to Trinity vertex definition.  
// Arguments:
//   grannyVertexDecl - Granny vertex definition
// Return Value:
//   Trinity vertex definition corresponding to input Granny vertex definition
// --------------------------------------------------------------------------------------
Tr2VertexDefinition BuildFromGrannyVertexDecl( const granny_data_type_definition* grannyVertexDecl )
{
	Tr2VertexDefinition vd;

	while( grannyVertexDecl->Type != GrannyEndMember )
	{
		const granny_data_type_definition& src = *grannyVertexDecl++;

		Tr2VertexDefinition::Item item;

		item.m_stream = 0;
		item.m_offset = vd.m_nextOffset[0];
		item.m_dataType = ConvertGrannyTypeToDataType(src);
		item.m_usageIndex = 0;

		vd.m_nextOffset[0] += vd.GetDataTypeSizeInBytes(item.m_dataType);

		if( !strncmp( src.Name, GrannyVertexPositionName, strlen( GrannyVertexPositionName ) ) )
		{
			item.m_usage = vd.POSITION;
			char C = src.Name[ strlen( GrannyVertexPositionName ) ];
			item.m_usageIndex = C ? unsigned( C - '0' ) : 0;
		}
		else if( !strncmp( src.Name, GrannyVertexDiffuseColorName, strlen( GrannyVertexDiffuseColorName ) ) )
		{
			item.m_usage = vd.COLOR;
			char C = src.Name[ strlen( GrannyVertexDiffuseColorName ) ];
			item.m_usageIndex = C ? unsigned( C - '0' ) : 0;
		}
		else if( !strncmp( src.Name, GrannyVertexNormalName, strlen( GrannyVertexNormalName ) ) )
		{
			item.m_usage = vd.NORMAL;
			char C = src.Name[ strlen( GrannyVertexNormalName ) ];
			item.m_usageIndex = C ? unsigned( C - '0' ) : 0;
		}		
		else if( !strcmp( src.Name, GrannyVertexTangentName ) )
		{
			item.m_usage = vd.TANGENT;
		}
		else if( !strcmp( src.Name, GrannyVertexBinormalName ) )
		{
			item.m_usage = vd.BITANGENT;
		}
		else if( !strncmp( src.Name, GrannyVertexTextureCoordinatesName, strlen( GrannyVertexTextureCoordinatesName ) ) )
		{
			item.m_usage = vd.TEXCOORD;
			char C = src.Name[ strlen( GrannyVertexTextureCoordinatesName ) ];
			item.m_usageIndex = C ? unsigned( C - '0' ) : 0;
		}		
		else if( !strcmp( src.Name, GrannyVertexBoneIndicesName ) )
		{
			item.m_usage = vd.BLENDINDICES;
		}
		else if( !strcmp( src.Name, GrannyVertexBoneWeightsName ) )
		{
			item.m_usage = vd.BLENDWEIGHTS;
		}

		vd.m_items.push_back( item );
	}

	return vd;
}

// --------------------------------------------------------------------------------------
// Description:
//   Convert Trinity vertex definition back to a granny layout.  
// Arguments:
//   vd - input definition
//   grannyVertexDecl - pointer to at least maxSize elements
//   maxSize - size of grannyVertexDecl array
// Return Value:
//   true - If successful
//   false - On error
// --------------------------------------------------------------------------------------
bool ConvertVertexDeclToGranny( Tr2VertexDefinition vd, granny_data_type_definition* grannyVertexDecl, unsigned maxSize )
{
	// Note: This function assumes the D3D vertex layout is described in increasing offset order
	// ... so make sure.
	std::sort(	begin( vd.m_items ), end( vd.m_items ) );

	// shorten the namespace...
	typedef Tr2VertexDefinition tvd;

	for( size_t i = 0; i != std::min( maxSize, (unsigned int)vd.m_items.size() ); ++i )
	{
		const auto& src = vd.m_items[i];
	
		granny_data_type_definition& dst = grannyVertexDecl[i];

		dst.ArrayWidth				= ( ( src.m_dataType & tvd::DT_SIZE_MASK ) >> tvd::DT_SIZE_OFFSET ) + 1;
		const bool isUnsigned		= ( src.m_dataType & tvd::DT_UNSIGNED_BIT ) != 0;
		const bool isNormalized		= ( src.m_dataType & tvd::DT_NORMALIZED_BIT ) != 0;

		switch( src.m_dataType & tvd::DT_TYPE_MASK )
		{
			case tvd::DT_INT8:
				dst.Type = isUnsigned	?	isNormalized ? GrannyNormalUInt8Member	: GrannyUInt8Member
										:	/*isNormalized ? GrannyNormalInt8Member	:*/ GrannyInt8Member;
				break;

			case tvd::DT_INT16:
				dst.Type = isUnsigned	?	isNormalized ? GrannyNormalUInt16Member	: GrannyUInt16Member
										:	/*isNormalized ? GrannyNormalInt8Member	:*/ GrannyInt16Member;
				break;

			case tvd::DT_INT32:
				dst.Type = isUnsigned	?	GrannyUInt32Member : GrannyInt16Member;
				break;
		
			case tvd::DT_FLOAT16:
				dst.Type = GrannyReal16Member;
				break;
		
			case tvd::DT_FLOAT32:
				dst.Type = GrannyReal32Member;
				break;
		
			default:
				CCP_ASSERT( false && "Missing datatype support in granny conversion" );
				return false;
		}

		static const char * grannyTexcoordNames[8]=
		{
			GrannyVertexTextureCoordinatesName "0",
			GrannyVertexTextureCoordinatesName "1",
			GrannyVertexTextureCoordinatesName "2",
			GrannyVertexTextureCoordinatesName "3",
			GrannyVertexTextureCoordinatesName "4",
			GrannyVertexTextureCoordinatesName "5",
			GrannyVertexTextureCoordinatesName "6",
			GrannyVertexTextureCoordinatesName "7",
		};

		static const char * grannyPositionNames[4]=
		{
			GrannyVertexPositionName,
			GrannyVertexPositionName "1",
			GrannyVertexPositionName "2",
			GrannyVertexPositionName "3",
		};

		static const char * grannyNormalNames[4]=
		{
			GrannyVertexNormalName,
			GrannyVertexNormalName "1",
			GrannyVertexNormalName "2",
			GrannyVertexNormalName "3",
		};

		switch( src.m_usage )
		{
		case tvd::POSITION:
			CCP_ASSERT( src.m_usageIndex < 4 );
			dst.Name = grannyPositionNames[ src.m_usageIndex ];
			break;
		case tvd::NORMAL:
			CCP_ASSERT( src.m_usageIndex < 4 );
			dst.Name = grannyNormalNames[ src.m_usageIndex ];
			break;
		case tvd::TANGENT:
			dst.Name = GrannyVertexTangentName;
			break;
		case tvd::BITANGENT:
			dst.Name = GrannyVertexBinormalName;
			break;
		case tvd::TEXCOORD:
			CCP_ASSERT( src.m_usageIndex < 8 );
			dst.Name = grannyTexcoordNames[ src.m_usageIndex ]; //GrannyVertexTextureCoordinatesName;
			break;
		case tvd::BLENDINDICES:
			dst.Name = GrannyVertexBoneIndicesName;
			break;
		case tvd::BLENDWEIGHTS:
			dst.Name = GrannyVertexBoneWeightsName;
			break;
		default:
			CCP_ASSERT( false && "Missing usage support in granny conversion" );
			return false;
		}

		dst.ReferenceType = 0;
	}

	grannyVertexDecl[std::min( maxSize, (unsigned int)vd.m_items.size() )].Type = GrannyEndMember;

	return true;
}


#if APEX_ENABLED
Tr2VertexDefinition BuildFromApex( const physx::apex::NxRenderDataFormat::Enum* src, int* offsets, int* sizes )
{
	Tr2VertexDefinition vd;

	CCP_ASSERT( src );
	CCP_ASSERT( offsets );
	CCP_ASSERT( sizes );
	// pVertexSize is optional

	if( !src || !offsets || !sizes )
	{
		return vd;
	}


	typedef Tr2VertexDefinition tvd;

	// Mapping from physx::apex::NxRenderVertexSemantic to Usage
	static const Tr2VertexDefinition::UsageCode ApexSemanticToUsage[] =
	{
		tvd::POSITION,		//POSITION = 0,
		tvd::NORMAL,		//NORMAL,
		tvd::TANGENT,		//TANGENT,
		tvd::BITANGENT,		//BINORMAL,
		tvd::COLOR,			//COLOR,
		tvd::TEXCOORD,		//TEXCOORD0,
		tvd::TEXCOORD,		//TEXCOORD1,
		tvd::TEXCOORD,		//TEXCOORD2,
		tvd::TEXCOORD,		//TEXCOORD3,
		tvd::BLENDINDICES,	//BONE_INDEX,
		tvd::BLENDWEIGHTS	//BONE_WEIGHT,
	};

	// Mapping from physx::apex::NxRenderDataFormat to DataType
	static const Tr2VertexDefinition::DataType ApexTypeToDataType[] =
	{
		tvd::DT_UNKNOWN_TYPE,		//UNSPECIFIED = 0,

		tvd::UBYTE_1,		//UBYTE1,
		tvd::UBYTE_2,		//UBYTE2,
		tvd::UBYTE_3,		//UBYTE3,
		tvd::UBYTE_4,		//UBYTE4,

		tvd::USHORT_1,		//USHORT1,
		tvd::USHORT_2,		//USHORT2,
		tvd::USHORT_3,		//USHORT3,
		tvd::USHORT_4,		//USHORT4,

		tvd::SHORT_1,		//SHORT1,
		tvd::SHORT_2,		//SHORT2,
		tvd::SHORT_3,		//SHORT3,
		tvd::SHORT_4,		//SHORT4,

		tvd::UINT32_1,		//UINT1,
		tvd::UINT32_2,		//UINT2,
		tvd::UINT32_3,		//UINT3,
		tvd::UINT32_4,		//UINT4,

		tvd::UBYTE_4,		//R8G8B8A8
		tvd::UBYTE_4,		//B8G8R8A8
		tvd::FLOAT32_4,		//R32G32B32A32_FLOAT,
		tvd::FLOAT32_4,		//B32G32R32A32_FLOAT,

		Tr2VertexDefinition::DataType(tvd::UBYTE_1 | tvd::DT_NORMALIZED_BIT),		//BYTE_UNORM1,
		Tr2VertexDefinition::DataType(tvd::UBYTE_2 | tvd::DT_NORMALIZED_BIT),		//BYTE_UNORM2,
		Tr2VertexDefinition::DataType(tvd::UBYTE_3 | tvd::DT_NORMALIZED_BIT),		//BYTE_UNORM3,
		Tr2VertexDefinition::DataType(tvd::UBYTE_4 | tvd::DT_NORMALIZED_BIT),	//BYTE_UNORM4,

		Tr2VertexDefinition::DataType(tvd::USHORT_1 | tvd::DT_NORMALIZED_BIT),		//SHORT_UNORM1,
		Tr2VertexDefinition::DataType(tvd::USHORT_2 | tvd::DT_NORMALIZED_BIT),		//SHORT_UNORM2,
		Tr2VertexDefinition::DataType(tvd::USHORT_3 | tvd::DT_NORMALIZED_BIT),		//SHORT_UNORM3,
		Tr2VertexDefinition::DataType(tvd::USHORT_4 | tvd::DT_NORMALIZED_BIT),	//SHORT_UNORM4,

		Tr2VertexDefinition::DataType(tvd::BYTE_1 | tvd::DT_NORMALIZED_BIT),		//BYTE_SNORM1,
		Tr2VertexDefinition::DataType(tvd::BYTE_2 | tvd::DT_NORMALIZED_BIT),		//BYTE_SNORM2,
		Tr2VertexDefinition::DataType(tvd::BYTE_3 | tvd::DT_NORMALIZED_BIT),		//BYTE_SNORM3,
		Tr2VertexDefinition::DataType(tvd::BYTE_4 | tvd::DT_NORMALIZED_BIT),	//BYTE_SNORM4,

		Tr2VertexDefinition::DataType(tvd::SHORT_1 | tvd::DT_NORMALIZED_BIT),		//SHORT_SNORM1,
		Tr2VertexDefinition::DataType(tvd::SHORT_2 | tvd::DT_NORMALIZED_BIT),		//SHORT_SNORM2,
		Tr2VertexDefinition::DataType(tvd::SHORT_3 | tvd::DT_NORMALIZED_BIT),		//SHORT_SNORM3,
		Tr2VertexDefinition::DataType(tvd::SHORT_4 | tvd::DT_NORMALIZED_BIT),	//SHORT_SNORM4,

		tvd::FLOAT16_1,		//HALF1,
		tvd::FLOAT16_2,		//HALF2,
		tvd::FLOAT16_3,		//HALF3,
		tvd::FLOAT16_4,		//HALF4,

		tvd::FLOAT32_1,		//FLOAT1,
		tvd::FLOAT32_2,		//FLOAT2,
		tvd::FLOAT32_3,		//FLOAT3,
		tvd::FLOAT32_4,		//FLOAT4,

		tvd::DT_UNKNOWN_TYPE,	//FLOAT3x4,
		tvd::DT_UNKNOWN_TYPE,	//FLOAT3x3,

		tvd::DT_UNKNOWN_TYPE,	//FLOAT4_QUAT,
		tvd::DT_UNKNOWN_TYPE,	//BYTE_SNORM4_QUATXYZW,
		tvd::DT_UNKNOWN_TYPE		//SHORT_SNORM4_QUATXYZW,
	};

	
	static const unsigned ApexSemanticIndexToUsageIndex[] =
	{
		0,	//POSITION = 0,
		0,	//NORMAL,
		0,	//TANGENT,
		0,	//BINORMAL,
		0,	//COLOR,
		0,	//TEXCOORD0,
		1,	//TEXCOORD1,
		2,	//TEXCOORD2,
		3,	//TEXCOORD3,
		0,	//BONE_INDEX,
		0	//BONE_WEIGHT,
	};

	for( unsigned i = 0; i != physx::apex::NxRenderVertexSemantic::NUM_SEMANTICS; ++i )
	{
		if( src[i] != physx::apex::NxRenderDataFormat::UNSPECIFIED )
		{
			offsets[i] = vd.m_nextOffset[0];

			vd.Add( ApexTypeToDataType[ src[i] ], ApexSemanticToUsage[i], ApexSemanticIndexToUsageIndex[i] );
						
			sizes[i] = vd.GetDataTypeSizeInBytes( vd.m_items.back().m_dataType );
		}
		else
		{
			offsets[i] = -1;
			sizes[i] = 0;
		}
	}

	return vd;
}
#endif // ?APEX_ENABLED
