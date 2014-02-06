#include "StdAfx.h"


#include "TriConstants.h"

#include "include/ITriConstants.h"

using namespace Tr2RenderContextEnum;

#if BLUE_WITH_PYTHON
void AddTriConstants(PyObject* d)
{
	const Be::VarChooser* const triConstants [] = 
	{	
#if DEPRECATED_ENABLED
		TriPrimitiveType,
		TriShadeMode,
		TriLightChooser,
		TriTextureOp,
		TriTextureTransformFlags,
		TriTextureAddress,
		TriTextureFilterType,
		TriTextureArgFlags,
		TriTexCoordIndex,
		TriCubemapFaces,
		TriImageFileFormat,
		TriFogMode,
		TriDevType,
		TriCreate,
		TriSwapEffect,
		TriPresentFlag,
		TriMultiSampleType,
		TriPresent,
		TriFormat,
		TriFormatZStencil,
		TriZBufferType,
		TriResourceTypeChooser,
		TriPool,
		TriFVF,
		TriUsage,
		TriUsageVertexIndex,
		TriVertexDeclType,
		TriVertexDeclMethod,
		TriVertexDeclUsage,
		TriSetGammaRamp,
		TriPresentMethodFlag,
		TriD3DFormat,
        TriFilterMode,
#endif
		
		TriBlendOp,
		TriBlend,
		TriFillMode,
        TriTextureChooser,
		TriModelChooser,
		TriParticleBirth,
		TriParticleDeath,
		TriParticleAnimation,
		TriParticleCycle,
		TriParticleType,
		TriBoidSwarmType,
		TriExtrapolation,
		TriInterpolation,
		TriOperator,
		TriTextureSource,
		TriMaterialSource,
		TriStageSelection,
		TriTransformBase,
		TriCloudType,
		TriTransformBaseFlags,
		TriLodBy,
		TriCull,
		TriCmpFunc,
		TriClearFlags,
		TriScissorMode,
		TriGR2Chooser,
		TriPoseClipTime,
		TriBipedMovementState,
		TriHACKFORTESTING,
		TriSkeletonType,
		TriD3DRenderState,
	};

	for (int i = 0; i < sizeof triConstants / sizeof triConstants[0]; i++)
	{
		for (const Be::VarChooser* j = triConstants[i]; j->mKey; j++)
		{
			// this obviously assumes that all values are LONG
			// later perhaps call BlueToPython to convert types
			// correctly
			PyObject *value = PyInt_FromLong( j->mValue.mLong );
			PyDict_SetItemString(d, const_cast<char*>( j->mKey ), value );
			Py_DECREF( value );
		}
	}
}
#endif


const char* KeyFromVal(const Be::VarChooser* i, long val)
{
	while (i->mKey)
	{
		if(i->mValue.mLong == val)
			return i->mKey;
		i++;
	}

	return "[-not found-]";
}



////////////////////////////////////////////////////////////////////////////////
// The actual definitions of these constants.
// the rot group ids
const long TRIGRPID_TEXTURE = 8001;
const long TRIGRPID_VERTEXBUFFER = 8002;
const long TRIGRPID_INDEXBUFFER = 8003;
const long TRIGRPID_SURFACE = 8004;
const long TRIGRPID_GR2 = 8005; // granny file
const long TRIGRPID_MORPHEME = 8006; // morpheme bundle

#define VAL(v) BeCast(v)
#define KV( name, doc ) \
{ \
#name, \
	VAL( name ), \
	doc \
}


#define KV_RC( name, doc ) \
{ \
	"D3D" #name, \
	VAL( Tr2RenderContextEnum::name ), \
	doc \
}

#define VAL_RC(v) BeCast(Tr2RenderContextEnum:: v)


const Be::VarChooser TriTextureChooser[] =
{
	{ 
		"SELECT_TEXTURE",     
		VAL(0),     
		"Texture (.dds, .tga, .bmp)|*.dds;*.tga;*.bmp;|All Files (*.*)|*.*" 
	},
	{0}
};

const Be::VarChooser TriModelChooser[] =
{
	{ 
		"SELECT_TRIMODEL",     
		VAL(0),     
		"Blue Object(.blue)|*.blue;|Maya Exported Model (.tri)|*.tri;|All Files (*.*)|*.*" 
	},
	{0}
};

const Be::VarChooser TriGR2Chooser[] =
{
	{ 
		"SELECT_GR2MODEL",     
		VAL(0),     
		"Granny file(.gr2)|*.GR2" 
	},
	{0}
};

const Be::VarChooser TriMorphemeBundleChooser[] =
{
	{ 
		"SELECT_BUNDLEMODEL",     
		VAL(0),     
		"Morpheme Bundle file|*.*" 
	},
	{0}
};

const Be::VarChooser TriParticleBirth[] =
{
	{ 
		"TRTPB_POINT",     
		VAL(TRTPB_POINT),     
		"no comment" 
	},
	{ 
		"TRTPB_FIELD", 
		VAL(TRTPB_FIELD), 
		"no comment" 
	},	
	{0}
};


const Be::VarChooser TriParticleDeath[] =
{
	{ 
		"TRTPD_TIME",     
		VAL(TRTPD_TIME),     
		"no comment" 
	},
	{ 
		"TRTPD_RANGE", 
		VAL(TRTPD_RANGE), 
		"no comment" 
	},
	{ 
		"TRTPD_CAMERADIST", 
		VAL(TRTPD_CAMERADIST), 
		"no comment" 
	},	
	{ 
		"TRTPD_NEEDED", 
		VAL(TRTPD_NEEDED), 
		"no comment" 
	},	
	{0}
};

const Be::VarChooser TriParticleAnimation[] =
{
	{ 
		"TRTPA_NONE",     
		VAL(TRTPA_NONE),     
		"no comment" 
	},
	{ 
		"TRTPA_4", 
		VAL(TRTPA_4), 
		"no comment" 
	},
	{ 
		"TRTPA_16", 
		VAL(TRTPA_16), 
		"no comment" 
	},
	{ 
		"TRTPA_64", 
		VAL(TRTPA_64), 
		"no comment" 
	},	
	{0}
};

const Be::VarChooser TriParticleCycle[] =
{
	{ 
		"TRTPC_NONE",     
		VAL(TRTPC_NONE),     
		"no uv cycling" 
	},
	{ 
		"TRTPC_RANDOM_HOLD", 
		VAL(TRTPC_RANDOM_HOLD), 
		"new particle starts somewhere in uv cycle and will always show that frame.\r\n" 
		"This has the same effect as TRTPC_RANDOM_LOOP with uvFPS == 0.0" 
	},
	{ 
		"TRTPC_RANDOM_LOOP", 
		VAL(TRTPC_RANDOM_LOOP), 
		"new particle starts somewhere in uv cycle, and loops, changes frames as per uvFPS" 
	},
	{ 
		"TRTPC_CONSTANT", 
		VAL(TRTPC_CONSTANT), 
		"new particle starts at frame 1, and plays to the end frame. Depends on uvFPS" 
	},
	{ 
		"TRTPC_LIFETIME", 
		VAL(TRTPC_LIFETIME), 
		"new particle starts at frame 1, and plays to the end frame over it's whole lifetime" 
	},	
	{0}
};

const Be::VarChooser TriParticleType[] =
{
	{ 
		"TRTPT_SIMPLE",     
		VAL(TRTPT_SIMPLE),     
		"no comment" 
	},
	{ 
		"TRTPT_MOVING", 
		VAL(TRTPT_MOVING), 
		"no comment" 
	},	
	{ 
		"TRTPT_RIBBON", 
		VAL(TRTPT_RIBBON), 
		"no comment" 
	},	
	{0}
};


const Be::VarChooser TriBoidSwarmType[] =
{
	{ 
		"TRTBST_WHIP",     
		VAL(TRTBST_WHIP),     
		"Makes the boids behave like a torch" 
	},
	{ 
		"TRTBST_TRAIL", 
		VAL(TRTBST_TRAIL), 
		"Makes the boids behave like smoke" 
	},	
	{0}
};


const Be::VarChooser TriExtrapolation[] =
{
	{ 
		"TRIEXT_NONE",     
		VAL(TRIEXT_NONE),     
		"no comment" 
	},
	{ 
		"TRIEXT_CONSTANT", 
		VAL(TRIEXT_CONSTANT), 
		"no comment" 
	},
	{ 
		"TRIEXT_GRADIENT", 
		VAL(TRIEXT_GRADIENT), 
		"no comment" 
	},
	{ 
		"TRIEXT_CYCLE",    
		VAL(TRIEXT_CYCLE),    
		"no comment" 
	},
	{0}
};


const Be::VarChooser TriInterpolation[] =
{
	{ 
		"TRIINT_NONE",     
		VAL(TRIINT_NONE),     
		"No Interpolation" 
	},
	{ 
		"TRIINT_CONSTANT", 
		VAL(TRIINT_CONSTANT), 
		"Performs a constant interpolation" 
	},
	{ 
		"TRIINT_LINEAR",   
		VAL(TRIINT_LINEAR),   
		"Performs a linear interpolation" 
	},
	{ 
		"TRIINT_HERMITE",  
		VAL(TRIINT_HERMITE),  
		"Performs a Hermite spline interpolation" 
	},
	{ 
		"TRIINT_CATMULLROM",  
		VAL(TRIINT_CATMULLROM),  
		"Performs a Catmull-Rom interpolation" 
	},
	{ 
		"TRIINT_SLERP",  
		VAL(TRIINT_SLERP),  
		"Interpolates between two quaternions, using spherical linear interpolation." 
	},
	{ 
		"TRIINT_SQUAD",  
		VAL(TRIINT_SQUAD),  
		"Interpolates between quaternions, using spherical quadrangle interpolation" 
	},			
	{ 
		"TRIINT_SIGMOID",  
		VAL(TRIINT_SIGMOID),  
		"Only used for scalar curves. Uses the first key's value and the right value" 
	},			
	{0}
};


const Be::VarChooser TriTextureSource[] =
{
	{
		"TRITEXSRC_NONE", 
		VAL(TRITEXSRC_NONE),   
		"The there is no texture to be used."
	},
	{
		"TRITEXSRC_SHADER", 
		VAL(TRITEXSRC_SHADER),   
		"The textures of the shader are used as texture inputs."
	},
	{
		"TRITEXSRC_AREA", 
		VAL(TRITEXSRC_AREA), 
		"The base textures of the model are used as texture inputs."
	},
	{
		"TRITEXSRC_SCENE", 
		VAL(TRITEXSRC_SCENE), 
		"The global textures of the scene are used as texture inputs."
	},

	{0}
};


const Be::VarChooser TriMaterialSource[] =
{
	{
		"TRIMATSRC_NONE", 
		VAL(TRITEXSRC_NONE),   
		"The there is no material to be used."
	},

	{
		"TRIMATSRC_SHADER", 
		VAL(TRIMATSRC_SHADER),   
		"The materials of the shader are used as material inputs."
	},
	{
		"TRIMATSRC_AREA", 
		VAL(TRIMATSRC_AREA), 
		"The base materials of the model are used as material inputs."
	},
	{
		"TRIMATSRC_SCENE", 
		VAL(TRIMATSRC_SCENE), 
		"The global materials of the scene are used as material inputs."
	},
	{
		"TRIMATSRC_VERTEX", 
		VAL(TRIMATSRC_VERTEX), 
		"Uses the color defined in the vertices of the geometry. THE GEOMETRY MUST HAVE COLOR FOR THIS TO WORK!!!!."
	},

	{0}
};


const Be::VarChooser TriStageSelection[] =
{
	{
		"TRISTS_USE2STAGEPASSES", 
		VAL(TRISTS_USE2STAGEPASSES),   
		"On Hardware that has 2 or more stages, use passes that have not more than "
		"2 stages (textureStage0 and textureStage1) enabled. This is the 'passes' "
		"list of passes"
	},

	{
		"TRISTS_USE3STAGEPASSES", 
		VAL(TRISTS_USE3STAGEPASSES),   
		"On Hardware that has 3 or more stages, use passes that have not more than "
		"3 stages (textureStage0, textureStage1 and textureStage2) enabled. This is "
		"the 'passes3Stage' list of passes"
	},
	{
		"TRISTS_USE4STAGEPASSES", 
		VAL(TRISTS_USE4STAGEPASSES), 
		"On Hardware that has 4 or more stages, use passes that have not more than "
		"4 stages (textureStage0, textureStage1, textureStage2, textureStage3) enabled. "
		"This is the 'passes4Stage' list of passes"
	},
	{0}
};


const Be::VarChooser TriTransformBase[] =
{
	{
		"TRITB_OBJECT", 
		VAL(TRITB_OBJECT),   
		"This makes TriTransforms build hierachies as expected, that is a child inherits "
		"its parent transforms.\r\n."
		"For TriTextures this is mosly usefull for projecting textures from objects"
	},
	{
		"TRITB_CAMERA_ROTATION", 
		VAL(TRITB_CAMERA_ROTATION),   
		"This sets the inverted rotation part of the camera matrix as the base for the"
		"transformations be they texture or transforms, good for environment maps and"
		"normal projected cubemaps."
	},
	{
		"TRITB_CAMERA_TRANSLATION", 
		VAL(TRITB_CAMERA_TRANSLATION),   
		"This sets the inverted translation part of the camera matrix as the base for the"
		"transformations be they texture or transforms, good for geometry that is locked,"
		"to the camera, like nebulas and starfields, etc."
	},
	{
		"TRITB_CAMERA", 
		VAL(TRITB_CAMERA),   
		"This sets the inverted camera matrix as the base for the transformations"
		"be they texture or geometry transforms, basically the same, as "
		"TRITB_CAMERA_ROTATION except the translation is taken also"
		""
	},
	{
		"TRITB_CAMERA_ROTATION_ALIGNED", 
		VAL(TRITB_CAMERA_ROTATION_ALIGNED),   
		"Makes the transform face the camera at all times, used for billboarding."
		"The up direction of the billboard is preserved."
	},
	{
		"TRITB_CAMERA_ROTATION_ALIGNED_SYMMETRY", 
		VAL(TRITB_CAMERA_ROTATION_ALIGNED_SYMMETRY),   
		"Makes the transform face the camera at all times, used for billboarding,"
		"the rotation around the axis to the camera is not corrected, hence this"
		"should only be used for rotationally symmetric billboards."
	},
	{
		"TRITB_CAMERA_ROTATION_FALLOFF", 
		VAL(TRITB_CAMERA_ROTATION_FALLOFF),   
		"Same as TRITB_CAMERA_ROTATION_ALIGNED, except the billboard is scaled"
		"by distance. This is useful for lights that are not rotationally symmetric."
	},
	{
		"TRITB_CAMERA_ROTATION_FALLOFF_SYMMETRY", 
		VAL(TRITB_CAMERA_ROTATION_FALLOFF_SYMMETRY),   
		"Same as TRITB_CAMERA_ROTATION_ALIGNED_SYMMETRY, except the billboard is scaled"
		"by distance. This is useful for lights that are rotationally symmetric."
	},
	{
		"TRITB_BOOSTER", 
		VAL(TRITB_BOOSTER),   
		"Makes the sprite behave as if it were an ellipsoid"
	},
	{
		"TRITB_SIMPLE_HALO", 
		VAL(TRITB_SIMPLE_HALO),   
		"Ask Torfi"
	},
	{
		"TRITB_SIMPLE_HALO_FALLOFF", 
		VAL(TRITB_SIMPLE_HALO_FALLOFF),   
		"Ask Torfi"
	},
	{
		"TRITB_SIMPLE_HALO_SYMMETRY", 
		VAL(TRITB_SIMPLE_HALO_SYMMETRY),   
		"Ask Torfi"
	},
	{
		"TRITB_SIMPLE_SPRITE", 
		VAL(TRITB_SIMPLE_SPRITE),   
		"Ask Torfi"
	},
	{
		"TRITB_SIMPLE_SPRITE_FALLOFF", 
		VAL(TRITB_SIMPLE_SPRITE_FALLOFF),   
		"Ask Torfi"
	},
	{
		"TRITB_SIMPLE_SPRITE_CONSTANT", 
		VAL(TRITB_SIMPLE_SPRITE_CONSTANT),   
		"Don't ask Torfi"
	},
	{
		"TRITB_FIXED", 
		VAL(TRITB_FIXED),   
		"This placed traditionally called world-space, the transform is considered to "
		"be in the world cordinate system (object hierarchies are ignored)"
		"This leves the texture space untouched (set to the identity matrix)."
	},
	{
		"TRITB_BOOSTER_FALLOFF",
		VAL(TRITB_BOOSTER_FALLOFF),
		"Makes the sprite behave as if it were an ellipsoid, includes falloff"
	},
	{
		"TRITB_WORLD", 
		VAL(TRITB_WORLD),   
		"Transforms the object relative to the world zero "		
	},
	{0}
};

const Be::VarChooser TriTransformBaseFlags[] =
{
	{
		"TRITBF_SCALING", 
		VAL(TRITBF_SCALING),   
		"Use Scaling"
	},
	{
		"TRITBF_TRANSLATION", 
		VAL(TRITBF_TRANSLATION),   
		"Use translation"
	},
	{
		"TRITBF_ROTATION_FWD", 
		VAL(TRITBF_ROTATION_FWD),   
		"Use rotation forward"
	},	
	{
		"TRITBF_ROTATION_UP", 
		VAL(TRITBF_ROTATION_UP),   
		"Use rotation up"
	},	
	{0}
};

const Be::VarChooser TriPoseClipTime[] =
{
	{
		"TRIPC_WORLD", 
		VAL(TRIPC_WORLD),   
		"World time"
	},
	{
		"TRIPC_LOCAL", 
		VAL(TRIPC_LOCAL),   
		"Local ( birth ) time"
	},
	{
		"TRIPC_OFFSETX", 
		VAL(TRIPC_OFFSETX),   
		"Use local X translation"
	},	
	{
		"TRIPC_OFFSETY", 
		VAL(TRIPC_OFFSETY),   
		"Use local Y translation"
	},	
	{
		"TRIPC_OFFSETZ", 
		VAL(TRIPC_OFFSETZ),   
		"Use local Z translation"
	},	
	{
		"TRIPC_YAW", 
		VAL(TRIPC_YAW),   
		"Use model yaw"
	},	
	{0}
};

const Be::VarChooser TriOperator[] =
{
	{
		"TRIOP_MULTIPLY", 
		VAL(TRIOP_MULTIPLY),   
		"multiply"
	},
	{
		"TRIOP_ADD", 
		VAL(TRIOP_ADD),   
		"add"
	},
	{0}
};

#if DEPRECATED_ENABLED

const Be::VarChooser TriPrimitiveType[] =
{
	{
		"TRIPT_POINTLIST", 
		VAL(D3DPT_POINTLIST),   
		"Renders the vertices as a collection of isolated points."
	},
	{
		"TRIPT_LINELIST", 
		VAL(D3DPT_LINELIST),   
		"Renders the vertices as a list of isolated straight line segments. Calls"
		"using this primitive type fail if the count is less than 2 or is odd."
	},
	{
		"TRIPT_LINESTRIP", 
		VAL(D3DPT_LINESTRIP),   
		"Renders the vertices as a single polyline. Calls using this primitive type"
		"fail if the count is less than 2. "
	},
	{
		"TRIPT_TRIANGLELIST", 
		VAL(D3DPT_TRIANGLELIST),   
		"Renders the specified vertices as a sequence of isolated triangles. Each"
		"group of three vertices defines a separate triangle.\r\n"
		"Backface culling is affected by the current winding-order render state."
	},
	{
		"TRIPT_TRIANGLESTRIP", 
		VAL(D3DPT_TRIANGLESTRIP),   
		"Renders the vertices as a triangle strip. The backface-culling flag is"
		"automatically flipped on even-numbered triangles."
	},
	{
		"TRIPT_TRIANGLEFAN", 
		VAL(D3DPT_TRIANGLEFAN),   
		"Renders the vertices as a triangle fan."
	},
	{
		"TRIPT_FORCE_DWORD", 
		VAL(D3DPT_FORCE_DWORD),   
		"Forces this enumeration to compile to 32 bits in size. This value is not"
		"used."
	},
	{0}
};

#endif

const Be::VarChooser TriCloudType[] =
{
	{
		"TRICT_SPRITE", 
		VAL(TRICT_SPRITE),   
		"Sprite"
	},
	{
		"TRICT_POINT", 
		VAL(TRICT_POINT),   
		"points"
	},
	{
		"TRICT_LINE", 
		VAL(TRICT_LINE),   
		"lines connecting points"
	},
	{0}
};

const Be::VarChooser TriLodBy[] =
{
	{
		"TRILB_NONE", 
		VAL(TRILB_NONE),   
		"No automated switching of LOD levels, use this if you want to control "
		"externaly what LOD level is displayed"
	},
	{
		"TRILB_CAMERA_DISTANCE", 
		VAL(TRILB_CAMERA_DISTANCE),   
		"Use the theshold values as distances from the camera"
	},
	{
		"TRITB_CAMERA_DISTANCE_FOV_HEIGHT", 
		VAL(TRITB_CAMERA_DISTANCE_FOV_HEIGHT),   
		"Use the theshold values as height of the view-volume at the current distance from the camera"
	},
	{0}
};

const Be::VarChooser TriCull[] =
{
	{
		"TRICULL_NONE", 
		VAL(CULLMODE_NONE),
		"Do not cull back faces."
	},
	{
		"TRICULL_CW",   
		VAL(CULLMODE_CW),
		"Cull back faces with clockwise vertices."
	},
	{
		"TRICULL_CCW",  
		VAL(CULLMODE_CCW),
		"Cull back faces with counterclockwise vertices."
	},
	{0}
};


#if DEPRECATED_ENABLED

const Be::VarChooser TriShadeMode[] =
{
	{
		"TRISHADE_FLAT",    
		VAL(D3DSHADE_FLAT),    
		"Flat shading mode. The color and specular component of the first vertex in the "
		"triangle are used to determine the color and specular component of the face. "
		"These colors remain constant across the triangle; that is, they are not "
		"interpolated. The specular alpha is interpolated. See Remarks."
	},
	{
		"TRISHADE_GOURAUD", 
		VAL(D3DSHADE_GOURAUD), 
		"Gouraud shading mode. The color and specular components of the face are "
		"determined by a linear interpolation between all three of the triangle's "
		"vertices."
	},
	{
		"TRISHADE_PHONG",   
		VAL(D3DSHADE_PHONG),   
		"Not supported."
	},
	{0}
};


const Be::VarChooser TriLightChooser[] =
{
	{
		"TRILIGHT_POINT",     
		VAL(D3DLIGHT_POINT),     
		"Light is a point source. The light has a position in space and radiates light in all directions."
	},
	{
		"TRILIGHT_SPOT", 
		VAL(D3DLIGHT_SPOT), 
		"Light is a spotlight source. This light is like a point light, except that the "
		"illumination is limited to a cone. This light type has a direction and several "
		"other parameters that determine the shape of the cone it produces. For information "
		"about these parameters, see the D3DLIGHT8 structure. "
	},
	{
		"TRILIGHT_DIRECTIONAL",     
		VAL(D3DLIGHT_DIRECTIONAL),     
		"Light is a directional source. This is equivalent to using a point light source "
		"at an infinite distance."
	},
	{0}
};

#endif

const Be::VarChooser TriFillMode[] =
{
	{
		"TRIFILL_POINT",     
		VAL(Tr2RenderContextEnum::FM_POINT),     
		"Fill points."
	},
	{
		"TRIFILL_WIREFRAME", 
		VAL(Tr2RenderContextEnum::FM_WIREFRAME), 
		"Fill wireframes. This fill mode currently does not work for clipped "
		"primitives when you use the DrawPrimitive methods."
	},
	{
		"TRIFILL_SOLID",     
		VAL(Tr2RenderContextEnum::FM_SOLID),     
		"Fill solids."
	},
	{0}
};

const Be::VarChooser TriCmpFunc[] =
{
	{
		"TRICMP_NEVER",         
		VAL_RC(CMP_NEVER),         
		"Always fail the test\n" 		
	},
	{
		"TRICMP_LESS",         
		VAL_RC(CMP_LESS),         
		"Accept the new pixel if its value is less than the value of the current pixel.\n"
	},
	{
		"TRICMP_EQUAL",    
		VAL_RC(CMP_EQUAL),    
		"Accept the new pixel if its value equals the value of the current pixel.\n"
	},
	{
		"TRICMP_LESSEQUAL", 
		VAL_RC(CMP_LESSEQUAL ), 
		"Accept the new pixel if its value is less than or equal to the value of the current pixel.\n"
	},
	{
		"TRICMP_GREATER",         
		VAL_RC(CMP_GREATER),         
		"Accept the new pixel if its value is greater than the value of the current pixel.\n"
	},
	{
		"TRICMP_NOTEQUAL",         
		VAL_RC(CMP_NOTEQUAL),         
		"Accept the new pixel if its value does not equal the value of the current pixel.\n"
	},
	{
		"TRICMP_GREATEREQUAL",         
		VAL_RC(CMP_GREATEREQUAL),         
		"Accept the new pixel if its value is greater than or equal to the value of the current pixel.\n"
	},
	{
		"TRICMP_ALWAYS",         
		VAL_RC(CMP_ALWAYS ),         
		"Always pass the test.\n"
	},
	{0}
};

const Be::VarChooser TriBlendOp[] =
{
	{
		"TRIBLENDOP_DISABLE",         
		VAL(Tr2RenderContextEnum::BO_DISABLE),
		"No blending\n" 		
	},
	{
		"TRIBLENDOP_ADD",         
		VAL(Tr2RenderContextEnum::BO_ADD),         
		"The result is the destination added to the source.\n" 
		"Result = Source + Destination"
	},
	{
		"TRIBLENDOP_SUBTRACT",    
		VAL(Tr2RenderContextEnum::BO_SUBTRACT),    
		"The result is the destination subtracted from to the source.\n"
		"Result = Source - Destination"
	},
	{
		"TRIBLENDOP_REVSUBTRACT", 
		VAL(Tr2RenderContextEnum::BO_REVSUBTRACT), 
		"The result is the source subtracted from the destination.\n"
		"Result = Destination - Source"
	},
	{
		"TRIBLENDOP_MIN",         
		VAL(Tr2RenderContextEnum::BO_MIN),         
		"The result is the minimum of the source and destination.\n"
		"Result = MIN(Source, Destination)"
	},
	{
		"TRIBLENDOP_MAX",         
		VAL(Tr2RenderContextEnum::BO_MAX),         
		"The result is the maximum of the source and destination.\n"
		"Result = MAX(Source, Destination)"
	},
	{0}
};

const Be::VarChooser TriBlend[] =
{
	{
		"TRIBLEND_ZERO",            
		VAL(Tr2RenderContextEnum::BM_ZERO),
		"Blend factor is (0, 0, 0, 0)."
	},
	{
		"TRIBLEND_ONE",             
		VAL(Tr2RenderContextEnum::BM_ONE),             
		"Blend factor is (1, 1, 1, 1)."
	},
	{
		"TRIBLEND_SRCCOLOR",        
		VAL(Tr2RenderContextEnum::BM_SRCCOLOR),        
		"Blend factor is (Rs, Gs, Bs, As)."
	},
	{
		"TRIBLEND_INVSRCCOLOR",     
		VAL(Tr2RenderContextEnum::BM_INVSRCCOLOR),     
		"Blend factor is (1-Rs, 1-Gs, 1-Bs, 1-As)."
	},
	{
		"TRIBLEND_SRCALPHA",        
		VAL(Tr2RenderContextEnum::BM_SRCALPHA),        
		"Blend factor is (As, As, As, As)."
	},
	{
		"TRIBLEND_INVSRCALPHA",     
		VAL(Tr2RenderContextEnum::BM_INVSRCALPHA),     
		"Blend factor is (1-As, 1-As, 1-As, 1-As)."
	},
	{
		"TRIBLEND_DESTALPHA",       
		VAL(Tr2RenderContextEnum::BM_DESTALPHA),       
		"Blend factor is (Ad, Ad, Ad, Ad)."
	},
	{
		"TRIBLEND_INVDESTALPHA",    
		VAL(Tr2RenderContextEnum::BM_INVDESTALPHA),    
		"Blend factor is (1-Ad, 1-Ad, 1-Ad, 1-Ad)."
	},
	{
		"TRIBLEND_DESTCOLOR",    
		VAL(Tr2RenderContextEnum::BM_DESTCOLOR),    
		"Blend factor is (Rd, Gd, Bd, Ad)."
	},
	{
		"TRIBLEND_INVDESTCOLOR",    
		VAL(Tr2RenderContextEnum::BM_INVDESTCOLOR),    
		"Blend factor is (1-Rd, 1-Gd, 1-Bd, 1-Ad)."
	},
	{
		"TRIBLEND_SRCALPHASAT",     
		VAL(Tr2RenderContextEnum::BM_SRCALPHASAT),     
		"Blend factor is (f, f, f, 1); f = min(As, 1-Ad)."
	},
	{
		"TRIBLEND_BOTHINVSRCALPHA", 
		VAL(Tr2RenderContextEnum::BM_BOTHINVSRCALPHA), 
		"Source blend factor is (1-As, 1-As, 1-As, 1-As), and destination blend factor is "
		"(As, As, As, As); the destination blend selection is overridden. This blend mode is "
		"supported only for the D3DRS_SRCBLEND render state." 
	},
	{0}
};


#if DEPRECATED_ENABLED

const Be::VarChooser TriTextureOp [] =
{
	{
		"TRITOP_DISABLE",            
		VAL(D3DTOP_DISABLE),            
		"Disables output from this texture stage and all stages with a higher index. "
		"To disable texture mapping, set this as the color operation for the first "
		"texture stage (stage 0). Alpha operations cannot be disabled when color operations "
		"are enabled. Setting the alpha operation to D3DTOP_DISABLE when color blending is "
		"enabled causes undefined behavior."

	},
	{
		"TRITOP_SELECTARG1",            
		VAL(D3DTOP_SELECTARG1),            
		"Use this texture stage's first color or alpha argument, unmodified, as the output. "
		"This operation affects the color argument when used with the D3DTSS_COLOROP "
		"texture-stage state, and the alpha argument when used with D3DTSS_ALPHAOP. \n"
		"Srgba = Arg1"
	},
	{
		"TRITOP_SELECTARG2",            
		VAL(D3DTOP_SELECTARG2),            
		"Use this texture stage's second color or alpha argument, unmodified, as the output. "
		"This operation affects the color argument when used with the D3DTSS_COLOROP texture "
		"stage state, and the alpha argument when used with D3DTSS_ALPHAOP. \n"
		"Srgba = Arg1"
	},
	{
		"TRITOP_MODULATE",            
		VAL(D3DTOP_MODULATE),            
		"Multiply the components of the arguments\n"
		"Srgba = Arg1 * Arg2"
	},
	{
		"TRITOP_MODULATE2X",            
		VAL(D3DTOP_MODULATE2X),            
		"Multiply the components of the arguments, and shift the products to the left 1 bit "
		"(effectively multiplying them by 2) for brightening.\n"
		"Srgba = (Arg1 * Arg2) << 1"
	},
	{
		"TRITOP_MODULATE4X",            
		VAL(D3DTOP_MODULATE4X),            
		"Multiply the components of the arguments, and shift the products to the left 2 bits "
		"(effectively multiplying them by 4) for brightening. \n"
		"Srgba = (Arg1 * Arg2) << 2"
	},
	{
		"TRITOP_ADD",            
		VAL(D3DTOP_ADD),            
		"Add the components of the arguments.\n"
		"Srgba = Arg1 + Arg2"
	},
	{
		"TRITOP_ADDSIGNED",            
		VAL(D3DTOP_ADDSIGNED),            
		"Add the components of the arguments with a -0.5 bias, making the effective range"
		"of values from -0.5 through 0.5. \n"
		"Srgba = Arg1 + Arg2 - 0.5"
	},
	{
		"TRITOP_ADDSIGNED2X",            
		VAL(D3DTOP_ADDSIGNED2X),            
		"Add the components of the arguments with a -0.5 bias, and shift "
		"the products to the left 1 bit. \n"
		"Srgba = (Arg1 + Arg2 - 0.5) << 1"
	},
	{
		"TRITOP_SUBTRACT",            
		VAL(D3DTOP_SUBTRACT),            
		"Subtract the components of the second argument from those of the first argument. \n"
		"Srgba = Arg1 - Arg2"
	},
	{
		"TRITOP_ADDSMOOTH",            
		VAL(D3DTOP_ADDSMOOTH),            
		"Add the first and second arguments; then subtract their product from the sum. \n"
		"Srgba = Arg1 + Arg2 - Arg1 * Arg2 \n"
		"      = Arg1 + Arg2 (1 - Arg1)\n"
	},
	{
		"TRITOP_BLENDDIFFUSEALPHA",            
		VAL(D3DTOP_BLENDDIFFUSEALPHA),            
		"D3DTOP_BLENDDIFFUSEALPHA,D3DTOP_BLENDTEXTUREALPHA, D3DTOP_BLENDFACTORALPHA, "
		"and D3DTOP_BLENDCURRENTALPHA \n"
		"Linearly blend this texture stage, using the interpolated alpha from "
		"each vertex (D3DTOP_BLENDDIFFUSEALPHA), alpha from this stage's texture "
		"(D3DTOP_BLENDTEXTUREALPHA), a scalar alpha (D3DTOP_BLENDFACTORALPHA) set with "
		"the D3DRS_TEXTUREFACTOR render state, or the alpha taken from the previous "
		"texture stage (D3DTOP_BLENDCURRENTALPHA).\n"
		"Srgba = Arg1 * (Alpha) + Arg2 * (1 - Alpha)"
	},
	{
		"TRITOP_BLENDTEXTUREALPHA",            
		VAL(D3DTOP_BLENDTEXTUREALPHA),            
		"D3DTOP_BLENDDIFFUSEALPHA,D3DTOP_BLENDTEXTUREALPHA, D3DTOP_BLENDFACTORALPHA, "
		"and D3DTOP_BLENDCURRENTALPHA \n"
		"Linearly blend this texture stage, using the interpolated alpha from "
		"each vertex (D3DTOP_BLENDDIFFUSEALPHA), alpha from this stage's texture "
		"(D3DTOP_BLENDTEXTUREALPHA), a scalar alpha (D3DTOP_BLENDFACTORALPHA) set with "
		"the D3DRS_TEXTUREFACTOR render state, or the alpha taken from the previous "
		"texture stage (D3DTOP_BLENDCURRENTALPHA).\n"
		"Srgba = Arg1 * (Alpha) + Arg2 * (1 - Alpha)"
	},
	{
		"TRITOP_BLENDFACTORALPHA",            
		VAL(D3DTOP_BLENDFACTORALPHA),            
		"D3DTOP_BLENDDIFFUSEALPHA,D3DTOP_BLENDTEXTUREALPHA, D3DTOP_BLENDFACTORALPHA, "
		"and D3DTOP_BLENDCURRENTALPHA \n"
		"Linearly blend this texture stage, using the interpolated alpha from "
		"each vertex (D3DTOP_BLENDDIFFUSEALPHA), alpha from this stage's texture "
		"(D3DTOP_BLENDTEXTUREALPHA), a scalar alpha (D3DTOP_BLENDFACTORALPHA) set with "
		"the D3DRS_TEXTUREFACTOR render state, or the alpha taken from the previous "
		"texture stage (D3DTOP_BLENDCURRENTALPHA).\n"
		"Srgba = Arg1 * (Alpha) + Arg2 * (1 - Alpha)"
	},
	{
		"TRITOP_BLENDTEXTUREALPHAPM",            
		VAL(D3DTOP_BLENDTEXTUREALPHAPM),            
		"Linearly blend a texture stage that uses a premultiplied alpha. \n"
		"Srgba = Arg1 + Arg2 * (1 - Alpha)"
	},
	{
		"TRITOP_BLENDCURRENTALPHA",            
		VAL(D3DTOP_BLENDCURRENTALPHA),            
		"D3DTOP_BLENDDIFFUSEALPHA,D3DTOP_BLENDTEXTUREALPHA, D3DTOP_BLENDFACTORALPHA, "
		"and D3DTOP_BLENDCURRENTALPHA \n"
		"Linearly blend this texture stage, using the interpolated alpha from "
		"each vertex (D3DTOP_BLENDDIFFUSEALPHA), alpha from this stage's texture "
		"(D3DTOP_BLENDTEXTUREALPHA), a scalar alpha (D3DTOP_BLENDFACTORALPHA) set with "
		"the D3DRS_TEXTUREFACTOR render state, or the alpha taken from the previous "
		"texture stage (D3DTOP_BLENDCURRENTALPHA).\n"
		"Srgba = Arg1 * (Alpha) + Arg2 * (1 - Alpha)"
	},
	{
		"TRITOP_PREMODULATE",            
		VAL(D3DTOP_PREMODULATE),            
		"Modulate this texture stage with the next texture stage."
	},
	{
		"TRITOP_MODULATEALPHA_ADDCOLOR",            
		VAL(D3DTOP_MODULATEALPHA_ADDCOLOR),            
		"Modulate the color of the second argument, using the alpha of the first "
		"argument; then add the result to argument one. This operation is supported "
		"only for color operations (D3DTSS_COLOROP). \n"
		"Srgba = Arg1rgb + Arg1a * Arg2rgb"
	},
	{
		"TRITOP_MODULATECOLOR_ADDALPHA",            
		VAL(D3DTOP_MODULATECOLOR_ADDALPHA),            
		"Modulate the arguments; then add the alpha of the first argument. "
		"This operation is supported only for color operations (D3DTSS_COLOROP). \n"
		"Srgba = Arg1rgb * Arg2rgb + Arg1a"
	},
	{
		"TRITOP_MODULATEINVALPHA_ADDCOLOR",            
		VAL(D3DTOP_MODULATEINVALPHA_ADDCOLOR),            
		"Similar to D3DTOP_MODULATEALPHA_ADDCOLOR, but use the inverse of the "
		"alpha of the first argument. This operation is supported only for color "
		"operations (D3DTSS_COLOROP). \n"
		"Srgba = (1 - Arg1a) * Arg2rgb + Arg1rgb"
	},
	{
		"TRITOP_MODULATEINVCOLOR_ADDALPHA",            
		VAL(D3DTOP_MODULATEINVCOLOR_ADDALPHA),            
		"Similar to D3DTOP_MODULATECOLOR_ADDALPHA, but use the inverse of the color "
		"of the first argument. This operation is supported only for color operations "
		"(D3DTSS_COLOROP). \n"
		"Srgba = (1 - Arg1rgb) * Arg2rgb + Arg1a"
	},
	{
		"TRITOP_BUMPENVMAP",            
		VAL(D3DTOP_BUMPENVMAP),            
		"Perform per-pixel bump mapping, using the environment map in the next texture "
		"stage, without luminance. This operation is supported only for color operations "
		"(D3DTSS_COLOROP). "
	},
	{
		"D3DTOP_BUMPENVMAPLUMINANCE",            
		VAL(D3DTOP_BUMPENVMAPLUMINANCE ),            
		"Perform per-pixel bump mapping, using the environment map in the next texture "
		"stage, with luminance. This operation is supported only for color operations "
		"(D3DTSS_COLOROP). "
	},
	{
		"TRITOP_DOTPRODUCT3",            
		VAL(D3DTOP_DOTPRODUCT3),            
		"Modulate the components of each argument as signed components, add their "
		"products; then replicate the sum to all color channels, including alpha. This "
		"operation is supported for color and alpha operations. \n\n"
		"Srgba = (Arg1r * Arg2r + Arg1g * Arg2g + Arg1b * Arg2b)\n\n"
		"In DirectX 6.0 and 7.0 multitexture operations the above inputs are all shifted "
		"down by half (y = x - 0.5) before use to simulate signed data, and the scalar "
		"result is automatically clamped to positive values and replicated to all "
		"three output channels. Also, note that as a color operation this does not "
		"updated the alpha it just updates the rgb components. \n\n"
		"However, in DirectX 8.0 shaders you can specify that the output be routed "
		"to the .rgb or the .a components or both (the default). You can also "
		"specify a separate scalar operation on the alpha channel. "
	},
	{
		"TRITOP_MULTIPLYADD",            
		VAL(D3DTOP_MULTIPLYADD),            
		"Performs a multiply-accumulate operation. It takes the last two arguments, "
		"multiplies them together, and adds them to the remaining input/source argument, "
		"and places that into the result. \n"
		"Srgba = Arg1 + Arg2 * Arg3"
	},
	{
		"TRITOP_LERP",            
		VAL(D3DTOP_LERP),            
		"Linearly interpolates between the 2nd and 3rd source arguments by a proportion "
		"specified in the 1st source argument. \n"
		"Srgba = (Arg1) * Arg2 + (1-Arg1) * Arg3"
	},
	{0}
};


const Be::VarChooser TriTextureTransformFlags [] =
{
	{
		"TRITTFF_DISABLE",            
		VAL(D3DTTFF_DISABLE),            
		"Texture coordinates are passed directly to the rasterizer."
	},
	{
		"TRITTFF_COUNT1",            
		VAL(D3DTTFF_COUNT1),            
		"The rasterizer should expect 1-D texture coordinates."
	},
	{
		"TRITTFF_COUNT2",            
		VAL(D3DTTFF_COUNT2),            
		"The rasterizer should expect 2-D texture coordinates."
	},
	{
		"TRITTFF_COUNT3",            
		VAL(D3DTTFF_COUNT3),            
		"The rasterizer should expect 3-D texture coordinates."
	},
	{
		"TRITTFF_COUNT4",            
		VAL(D3DTTFF_COUNT4),            
		"The rasterizer should expect 4-D texture coordinates."
	},
	{
		"TRITTFF_COUNT2_PROJECTED",            
		VAL(D3DTTFF_COUNT2 | D3DTTFF_PROJECTED),            
		"The rasterizer should expect 2-D texture coordinates."
		"The texture coordinates are all divided by the last element "
		"before being passed to the rasterizer. For example, if this flag "
		"is specified with the D3DTTFF_COUNT3 flag, the first and second "
		"texture coordinates is divided by the third coordinate before being passed "
		"to the rasterizer. "
	},
	{
		"TRITTFF_COUNT3_PROJECTED",            
		VAL(D3DTTFF_COUNT3 | D3DTTFF_PROJECTED),            
		"The rasterizer should expect 3-D texture coordinates."
		"The texture coordinates are all divided by the last element "
		"before being passed to the rasterizer. For example, if this flag "
		"is specified with the D3DTTFF_COUNT3 flag, the first and second "
		"texture coordinates is divided by the third coordinate before being passed "
		"to the rasterizer. "
	},
	{
		"TRITTFF_COUNT4_PROJECTED",            
		VAL(D3DTTFF_COUNT4 | D3DTTFF_PROJECTED),            
		"The rasterizer should expect 4-D texture coordinates."
		"The texture coordinates are all divided by the last element "
		"before being passed to the rasterizer. For example, if this flag "
		"is specified with the D3DTTFF_COUNT3 flag, the first and second "
		"texture coordinates is divided by the third coordinate before being passed "
		"to the rasterizer. "
	},
	{0}
};



const Be::VarChooser TriTextureAddress [] =
{
	{
		"TRITADDRESS_WRAP",            
		VAL(D3DTADDRESS_WRAP),            
		"Tile the texture at every integer junction. For example, "
		"for u values between 0 and 3, the texture is repeated three "
		"times; no mirroring is performed. "
	},
	{
		"TRITADDRESS_MIRROR",            
		VAL(D3DTADDRESS_MIRROR),            
		"Similar to D3DTADDRESS_WRAP, except that the texture is flipped at "
		"every integer junction. For u values between 0 and 1, for example, the "
		"texture is addressed normally; between 1 and 2, the texture is flipped "
		"(mirrored); between 2 and 3, the texture is normal again, and so on. "
	},
	{
		"TRITADDRESS_CLAMP",            
		VAL(D3DTADDRESS_CLAMP),            
		"Texture coordinates outside the range [0.0, 1.0] are set to "
		"the texture color at 0.0 or 1.0, respectively. "
	},
	{
		"TRITADDRESS_BORDER",            
		VAL(D3DTADDRESS_BORDER),            
		"Texture coordinates outside the range [0.0, 1.0] are set "
		"to the border color."
	},
	{
		"TRITADDRESS_MIRRORONCE",            
		VAL(D3DTADDRESS_MIRRORONCE),            
		"Similar to D3DTADDRESS_MIRROR and D3DTADDRESS_CLAMP. Takes the "
		"absolute value of the texture coordinate (thus, mirroring around 0), and "
		"then clamps to the maximum value. The most common usage is for volume textures, "
		"where support for the full D3DTADDRESS_MIRRORONCE texture-addressing mode is not "
		"necessary, but the data is symmetric around the one axis. "
	},
	{0}
};


const Be::VarChooser TriTextureFilterType [] =
{
	{
		"TRITEXF_NONE",            
		VAL(D3DTEXF_NONE),            
		"Mipmapping disabled. The rasterizer should use the magnification filter instead."
	},
	{
		"TRITEXF_POINT",            
		VAL(D3DTEXF_POINT),            
		"Point filtering used as a texture magnification or minification filter. The texel "
		"with coordinates nearest to the desired pixel value is used. \n\n"
		"The texture filter to be used between mipmap levels is nearest-point mipmap filtering. "
		"The rasterizer uses the color from the texel of the nearest mipmap texture. "

	},
	{
		"TRITEXF_LINEAR",            
		VAL(D3DTEXF_LINEAR),            
		"Bilinear interpolation filtering used as a texture magnification or minification filter. "
		"A weighted average of a 2×2 area of texels surrounding the desired pixel is used. \n\n"
		"The texture filter to use between mipmap levels is trilinear mipmap interpolation. "
		"The rasterizer linearly interpolates pixel color, using the texels of the two nearest "
		"mipmap textures. "
	},
	{
		"TRITEXF_ANISOTROPIC",            
		VAL(D3DTEXF_ANISOTROPIC),            
		"Anisotropic texture filtering used as a texture magnification or minification "
		"filter. Compensates for distortion caused by the difference in angle between "
		"the texture polygon and the plane of the screen. "
	},
	{
		"TRITEXF_PYRAMIDALQUAD",            
		VAL(D3DTEXF_PYRAMIDALQUAD),            
		"A 4-sample tent filter used as a texture magnification or minification filter."
	},
	{
		"TRITEXF_GAUSSIANQUAD",            
		VAL(D3DTEXF_GAUSSIANQUAD),            
		"A 4-sample Gaussian filter used as a texture magnification or minification filter."
	},
	{0}
};

// TriTextureArgFlags is based on what could be gathered from the DX documentation.
// Basically there are two kind of Texture Argument Flags, there are Argument flags 
// and modifier flags. TRITA_ALPHAREPLICATE and TRITA_COMPLEMENT are modifier flags
// Acording to the documentation there can only be one active Argument flag and
// then that argument flag can be flagged with an modifier flag. It doesn't say
// whether both modifier flags can be used at the same time. 
// To have this making any sense in the Editing tool, the most used 
// Argument flags TRITA_CURRENT, TRITA_DIFFUSE and TRITA_TEXTURE will
// be "pre-flagged" with both modifier flags and presented as a seperate enum option

const Be::VarChooser TriTextureArgFlags [] =
{
	{
		"TRITA_CURRENT",            
		VAL(D3DTA_CURRENT),            
		"The texture argument is the result of the previous blending stage. "
		"In the first texture stage (stage 0), this argument is equivalent to "
		"D3DTA_DIFFUSE. If the previous blending stage uses a bump-map texture "
		"(the D3DTOP_BUMPENVMAP operation), the system chooses the texture from "
		"the stage before the bump-map texture. If s represents the current texture "
		"stage and s - 1 contains a bump-map texture, this argument becomes the result "
		"output by texture stage s - 2. Permissions are read/write. "
	},
	{
		"TRITA_DIFFUSE",            
		VAL(D3DTA_DIFFUSE),            
		"The texture argument is the diffuse color interpolated from vertex components "
		"during Gouraud shading. If the vertex does not contain a diffuse color, the "
		"default color is 0xFFFFFFFF. Permissions are read-only. "
	},
	{
		"TRITA_TEXTURE",            
		VAL(D3DTA_TEXTURE),            
		"The texture argument is the texture color for this texture stage. Permissions "
		"are read-only."
	},
	{
		"TRITA_SPECULAR",            
		VAL(D3DTA_SPECULAR),            
		"The texture argument is the specular color interpolated from vertex components "
		"during Gouraud shading. If the vertex does not contain a specular color, the "
		"default color is 0xFFFFFFFF. Permissions are read only. "
	},
	// the three most used Argument flags, flagged with TRITA_COMPLEMENT modifier flag
	{
		"TRITA_CURRENT_INV",            
		VAL(D3DTA_CURRENT | D3DTA_COMPLEMENT),            
		"Same as TRITA_CURRENT exept the color has been inverted by flagging the "
		"argument with the TRITA_COMPLEMENT modifier flag"
	},
	{
		"TRITA_DIFFUSE_INV",            
		VAL(D3DTA_DIFFUSE | D3DTA_COMPLEMENT),            
		"Same as TRITA_DIFFUSE exept the color has been inverted by flagging the "
		"argument with the TRITA_COMPLEMENT modifier flag"
	},
	{
		"TRITA_TEXTURE_INV",            
		VAL(D3DTA_TEXTURE | D3DTA_COMPLEMENT),            
		"Same as TRITA_TEXTURE exept the color has been inverted by flagging the "
		"argument with the TRITA_COMPLEMENT modifier flag"
	},
	{
		"TRITA_SPECULAR_INV",            
		VAL(D3DTA_SPECULAR | D3DTA_COMPLEMENT),            
		"Same as TRITA_SPECULAR exept the color has been inverted by flagging the "
		"argument with the TRITA_COMPLEMENT modifier flag"
	},
	// the three most used Argument flags, flagged with TRITA_ALPHAREPLICATE 
	// modifier flag
	{
		"TRITA_CURRENT_ALPHAREPLICATE",            
		VAL(D3DTA_CURRENT | D3DTA_ALPHAREPLICATE),            
		"Same as TRITA_CURRENT except the alpha information are replicated  to all "
		"color channels before the operation completes by flagging the argument with "
		"the TRITA_ALPHAREPLICATE modifier flag"
	},
	{
		"TRITA_DIFFUSE_ALPHAREPLICATE",            
		VAL(D3DTA_DIFFUSE | D3DTA_ALPHAREPLICATE),            
		"Same as TRITA_DIFFUSE except the alpha information are replicated  to all "
		"color channels before the operation completes by flagging the argument with "
		"the TRITA_ALPHAREPLICATE modifier flag"
	},
	{
		"TRITA_TEXTURE_ALPHAREPLICATE",            
		VAL(D3DTA_TEXTURE | D3DTA_ALPHAREPLICATE),            
		"Same as TRITA_TEXTURE except the alpha information are replicated  to all "
		"color channels before the operation completes by flagging the argument with "
		"the TRITA_ALPHAREPLICATE modifier flag"
	},
	{
		"TRITA_SPECULAR_ALPHAREPLICATE",            
		VAL(D3DTA_SPECULAR | D3DTA_ALPHAREPLICATE),            
		"Same as TRITA_SPECULAR except the alpha information are replicated  to all "
		"color channels before the operation completes by flagging the argument with "
		"the TRITA_ALPHAREPLICATE modifier flag"
	},
	// the three most used Argument flags, flagged with TRITA_ALPHAREPLICATE 
	// and the modifier flag
	{
		"TRITA_CURRENT_INV_ALPHAREPLICATE",            
		VAL(D3DTA_CURRENT | D3DTA_COMPLEMENT | D3DTA_ALPHAREPLICATE),            
		"Same as TRITA_CURRENT except the color has been inverted by flagging the "
		"argument with the TRITA_COMPLEMENT modifier flag and then the alpha "
		"information are replicated  to all color channels before the operation "
		"completes by flagging the argument with the TRITA_ALPHAREPLICATE modifier flag"
	},
	{
		"TRITA_DIFFUSE_INV_ALPHAREPLICATE",            
		VAL(D3DTA_DIFFUSE | D3DTA_COMPLEMENT | D3DTA_ALPHAREPLICATE),            
		"Same as TRITA_DIFFUSE except the color has been inverted by flagging the "
		"argument with the TRITA_COMPLEMENT modifier flag and then the alpha "
		"information are replicated  to all color channels before the operation "
		"completes by flagging the argument with the TRITA_ALPHAREPLICATE modifier flag"
	},
	{
		"TRITA_TEXTURE_INV_ALPHAREPLICATE",            
		VAL(D3DTA_TEXTURE | D3DTA_COMPLEMENT | D3DTA_ALPHAREPLICATE),            
		"Same as TRITA_TEXTURE except the color has been inverted by flagging the "
		"argument with the TRITA_COMPLEMENT modifier flag and then the alpha "
		"information are replicated  to all color channels before the operation "
		"completes by flagging the argument with the TRITA_ALPHAREPLICATE modifier flag"
	},
	{
		"TRITA_SPECULAR_INV_ALPHAREPLICATE",            
		VAL(D3DTA_SPECULAR | D3DTA_COMPLEMENT | D3DTA_ALPHAREPLICATE),            
		"Same as TRITA_SPECULAR except the color has been inverted by flagging the "
		"argument with the TRITA_COMPLEMENT modifier flag and then the alpha "
		"information are replicated  to all color channels before the operation "
		"completes by flagging the argument with the TRITA_ALPHAREPLICATE modifier flag"
	},

	// here is the rest og the argument flags, they have not been pre-flaged 
	// with the modifier flags as these flags are not that much used.
	// if they need to be come pre-flaged, then it is only a question of
	// doing the flagging here.
	{
		"TRITA_SELECTMASK",            
		VAL(D3DTA_SELECTMASK),            
		"Mask value for all arguments; not used when setting texture arguments. "
	},
	{
		"TRITA_TEMP",            
		VAL(D3DTA_TEMP),            
		"The texture argument is a temporary register color for read or write. "
		"D3DTA_TEMP is supported if the D3DPMISCCAPS_TSSARGTEMP device capability is "
		"present. The default value for the register is (0.0, 0.0, 0.0, 0.0). "
		"Permissions are read/write. "
	},
	{
		"TRITA_TFACTOR",            
		VAL(D3DTA_TFACTOR),            
		"The texture argument is the texture factor set in a previous call to the "
		"TD3DDevice8::SetRenderState with the D3DRS_TEXTUREFACTOR render-state "
		"value. Permissions are read-only. "
	},
	
	// this is a funky texture OP that CCP has added. It uses the direction to 
	// the sun of the scene as color. This is usefull for DOTPRODUCT3 Stuff
	// 

	{
		"TRITA_CUSTOMCOLOR",            
		VAL(D3DTA_CUSTOMCOLOR),            
		"This is really just the D3DTA_TFACTOR. It is specified here as a speciall "
		"agrument as all the special ops below use the TFactor. With this system "
		"of calling it custom color there isn't any danger of confusion with the ones "
		"below."
	},
	{
		"TRITA_VIEWVEC",            
		VAL(D3DTA_VIEWVEC),            
		"The view vector of the camera turned into a color."
	},
	{
		"TRITA_OBJECTVEC",
		VAL(D3DTA_OBJECTVEC),            
		"The vector <0.0, 1.0, 0.0> Transformed by the world matrix (combined "
		"matrices of the object being rendered)."
	},
	{
		"TRITA_CONTRASTVIEW_BYALPHA",
		VAL(D3DTA_CONTRASTVIEW_BYALPHA),
		"na"
	},
	{
		"TRITA_SUNVEC",            
		VAL(D3DTA_SUNVEC),            
		"The direction verctor of the scene's sunLight turned into a color."
	},
	{
		"TRITA_SUNDOTVIEWVEC",            
		VAL(D3DTA_SUNDOTVIEWVEC),            
		"Software DOT3 of the SUNVEC and the VIEWVEC turned into a color."
	},
	{
		"TRITA_VOLUME",
		VAL(D3DTA_VOLUME),
		"na"
	},
	{
		"TRITA_SCENE0",
		VAL(D3DTA_SCENE0),
		"na"
	},
	{
		"TRITA_SCENE1",
		VAL(D3DTA_SCENE1),
		"na"
	},
	{0}
};

const Be::VarChooser TriTexCoordIndex [] = 
{
	{
		"TRITSS_TCI_PASSTHRU",            
		VAL(D3DTSS_TCI_PASSTHRU),            
		"Use the specified texture coordinates contained within the vertex format. "
		"This value resolves to zero. "
	},
	{
		"TRITSS_TCI_CAMERASPACENORMAL",            
		VAL(D3DTSS_TCI_CAMERASPACENORMAL),            
		"Use the vertex normal, transformed to camera space, as the input texture "
		"coordinates for this stage's texture transformation."
	},
	{
		"TRITSS_TCI_CAMERASPACEPOSITION",            
		VAL(D3DTSS_TCI_CAMERASPACEPOSITION),            
		"Use the vertex position, transformed to camera space, as the input texture "
		"coordinates for this stage's texture transformation. "
	},
	{
		"TRITSS_TCI_CAMERASPACEREFLECTIONVECTOR",            
		VAL(D3DTSS_TCI_CAMERASPACEREFLECTIONVECTOR),            
		"Use the reflection vector, transformed to camera space, as the input texture "
		"coordinate for this stage's texture transformation. The reflection vector is "
		"computed from the input vertex position and normal vector. "
	},
	{0}
};


const Be::VarChooser TriCubemapFaces  [] =
{
	{
		"TRICUBEMAP_FACE_POSITIVE_X",            
		VAL(D3DCUBEMAP_FACE_POSITIVE_X),            
		"Positive x-face of the cubemap."
	},
	{
		"TRICUBEMAP_FACE_NEGATIVE_X",            
		VAL(D3DCUBEMAP_FACE_NEGATIVE_X),            
		"Negative x-face of the cubemap."
	},
	{
		"TRICUBEMAP_FACE_POSITIVE_Y",            
		VAL(D3DCUBEMAP_FACE_POSITIVE_Y),            
		"Positive y-face of the cubemap."
	},
	{
		"TRICUBEMAP_FACE_NEGATIVE_Y",            
		VAL(D3DCUBEMAP_FACE_NEGATIVE_Y),            
		"Negative y-face of the cubemap. "
	},
	{
		"TRICUBEMAP_FACE_POSITIVE_Z",            
		VAL(D3DCUBEMAP_FACE_POSITIVE_Z),            
		"Positive z-face of the cubemap."
	},
	{
		"TRICUBEMAP_FACE_NEGATIVE_Z",            
		VAL(D3DCUBEMAP_FACE_NEGATIVE_Z),            
		"Negative z-face of the cubemap."
	},
};


const Be::VarChooser TriImageFileFormat  [] =
{
	{
		"TRIIFF_BMP",            
		VAL(D3DXIFF_BMP),            
		"Microsoft® Windows® bitmap file format."
	},
	{
		"TRIIFF_JPG",            
		VAL(D3DXIFF_JPG),            
		"Microsoft® Windows® bitmap file format."
	},
		{
		"TRIIFF_TGA",            
		VAL(D3DXIFF_TGA),            
		"Microsoft® Windows® bitmap file format."
	},
		{
		"TRIIFF_PNG",            
		VAL(D3DXIFF_PNG),            
		"Microsoft® Windows® bitmap file format."
	},
		{
		"TRIIFF_DDS",            
		VAL(D3DXIFF_DDS),            
		"Microsoft® Windows® bitmap file format."
	},
		{
		"TRIIFF_PPM",            
		VAL(D3DXIFF_PPM),            
		"Microsoft® Windows® bitmap file format."
	},
		{
		"TRIIFF_DIB",            
		VAL(D3DXIFF_DIB),            
		"Microsoft® Windows® bitmap file format."
	},
};


const Be::VarChooser TriFogMode [] = 
{
	{
		"TRIFOG_NONE",            
		VAL(D3DFOG_NONE),            
		"No fog effect."
	},
	{
		"TRIFOG_EXP",            
		VAL(D3DFOG_EXP),            
		"Fog effect intensifies exponentially, according to the following formula.\r\n"
		"f = 1 / pow(e, d * density)"
	},
	{
		"TRIFOG_EXP2",            
		VAL(D3DFOG_EXP2),            
		"Fog effect intensifies exponentially with the square of the distance, "
		"according to the following formula. \r\n"
		"f = 1 / pow(pow(e, d * density), 2) "
	},
	{
		"TRIFOG_LINEAR",            
		VAL(D3DFOG_LINEAR),            
		"Fog effect intensifies linearly between the start and end points, according "
		"to the following formula. \r\n"
		"f = end - d / end - start"
	},
	{0}
};


const Be::VarChooser TriDevType [] = 
{
	{
		"TRIDEVTYPE_HAL",            
		VAL(D3DDEVTYPE_HAL ),            
		"Hardware rasterization and shading with software, hardware, or mixed transform and lighting.\r\n"
	},
	{
		"TRIDEVTYPE_REF",            
		VAL(D3DDEVTYPE_REF ),            
		"Microsoft® Direct3D® features are implemented in software; however, the reference rasterizer "
		"does make use of special CPU instructions whenever it can. \r\n"
	},
	{
		"TRIDEVTYPE_SW",            
		VAL(D3DDEVTYPE_SW),            
		"A pluggable software device that has been registered with Direct3D using IDirect3D8::RegisterSoftwareDevice.\r\n"
	},
	{0}
};


const Be::VarChooser TriCreate [] = 
{
	{
		"TRICREATE_FPU_PRESERVE",            
		VAL(D3DCREATE_FPU_PRESERVE),            
		"The calling application does not want Direct3D to modify the FPU state in ways that are "
		"visible to the application. In this mode, Direct3D saves and restores the FPU state every "
		"time it needs to modify the FPU state. "
	},
	{
		"TRICREATE_HARDWARE_VERTEXPROCESSING",            
		VAL(D3DCREATE_HARDWARE_VERTEXPROCESSING ),            
		"Specifies hardware vertex processing. "		
	},
	{
		"TRICREATE_MIXED_VERTEXPROCESSING",            
		VAL(D3DCREATE_MIXED_VERTEXPROCESSING),            
		"Specifies mixed (both software and hardware) vertex processing."
	},
	{
		"TRICREATE_MULTITHREADED",            
		VAL(D3DCREATE_MULTITHREADED),            
		"Requests multithread-safe behavior. This causes Direct3D to take the global critical section more frequently."
	},
	{
		"TRICREATE_PUREDEVICE",            
		VAL(D3DCREATE_PUREDEVICE),            
		"Specifies hardware rasterization, transform, lighting, and shading."
	},
	{
		"TRICREATE_SOFTWARE_VERTEXPROCESSING",            
		VAL(D3DCREATE_SOFTWARE_VERTEXPROCESSING),            
		"Specifies software vertex processing."
	},
	{0}
};


const Be::VarChooser TriSwapEffect [] = 
{
	{
		"TRISWAPEFFECT_DISCARD",            
		VAL(D3DSWAPEFFECT_DISCARD ),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRISWAPEFFECT_FLIP",            
		VAL(D3DSWAPEFFECT_FLIP ),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRISWAPEFFECT_COPY",            
		VAL(D3DSWAPEFFECT_COPY ),            
		"See D3D Documentation.\r\n"
	},
	{0}
};

const Be::VarChooser TriPresentFlag [] = 
{
	{
		"TRIPRESENTFLAG_LOCKABLE_BACKBUFFER",            
		VAL(D3DPRESENTFLAG_LOCKABLE_BACKBUFFER  ),            

		"Set this flag if the application requires the ability to lock the "
		"back-buffer directly. Note that back buffers are not lockable unless the "
		"application specifies D3DPRESENTFLAG_LOCKABLE_BACKBUFFER when calling "
		"IDirect3D8::CreateDevice or TD3DDevice8::Reset. Lockable back buffers "
		"incur a performance cost on some graphics hardware configurations."
		"\r\n"
		"Performing a lock operation (or using TD3DDevice8::CopyRects to "
		"read/write) on the lockable back-buffer decreases performance on many cards. "		
		"In this case, consider using textured triangles to move data to the back buffer."		
	},
	{
		"TRIPRESENTFLAG_DISCARD_DEPTHSTENCIL",            
		VAL(D3DPRESENTFLAG_DISCARD_DEPTHSTENCIL),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIPRESENTFLAG_DEVICECLIP",            
		VAL(D3DPRESENTFLAG_DEVICECLIP),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIPRESENTFLAG_VIDEO",            
		VAL(D3DPRESENTFLAG_VIDEO),            
		"See D3D Documentation.\r\n"
	},
	{0}
};


const Be::VarChooser TriMultiSampleType [] = 
{
	{
		"TRIMULTISAMPLE_NONE",            
		VAL(D3DMULTISAMPLE_NONE),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_NONMASKABLE",            
		VAL(D3DMULTISAMPLE_NONMASKABLE),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_2_SAMPLES",            
		VAL(D3DMULTISAMPLE_2_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_3_SAMPLES",            
		VAL(D3DMULTISAMPLE_3_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_4_SAMPLES",            
		VAL(D3DMULTISAMPLE_4_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_5_SAMPLES",            
		VAL(D3DMULTISAMPLE_5_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_6_SAMPLES",            
		VAL(D3DMULTISAMPLE_7_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_7_SAMPLES",            
		VAL(D3DMULTISAMPLE_7_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_8_SAMPLES",            
		VAL(D3DMULTISAMPLE_8_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_9_SAMPLES",            
		VAL(D3DMULTISAMPLE_9_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_10_SAMPLES",            
		VAL(D3DMULTISAMPLE_10_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_11_SAMPLES",            
		VAL(D3DMULTISAMPLE_11_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_12_SAMPLES",            
		VAL(D3DMULTISAMPLE_12_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_13_SAMPLES",            
		VAL(D3DMULTISAMPLE_13_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_14_SAMPLES",            
		VAL(D3DMULTISAMPLE_14_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_15_SAMPLES",            
		VAL(D3DMULTISAMPLE_15_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{
		"TRIMULTISAMPLE_16_SAMPLES",            
		VAL(D3DMULTISAMPLE_16_SAMPLES),            
		"See D3D Documentation.\r\n"
	},
	{0}
};


const Be::VarChooser TriPresent [] = 
{
	{
		"TRIPRESENT_INTERVAL_DEFAULT",            
		VAL(D3DPRESENT_INTERVAL_DEFAULT),            
		""
	},
	{
		"TRIPRESENT_INTERVAL_ONE",            
		VAL(D3DPRESENT_INTERVAL_ONE),            
		""
	},
	{
		"TRIPRESENT_INTERVAL_TWO",            
		VAL(D3DPRESENT_INTERVAL_TWO),            
		""
	},
	{
		"TRIPRESENT_INTERVAL_THREE",            
		VAL(D3DPRESENT_INTERVAL_THREE),            
		""
	},
	{
		"TRIPRESENT_INTERVAL_FOUR",            
		VAL(D3DPRESENT_INTERVAL_FOUR),            
		""
	},
		{
		"TRIPRESENT_INTERVAL_IMMEDIATE",            
		VAL(D3DPRESENT_INTERVAL_IMMEDIATE),            
		""
	},
	{0}
};
#endif
const Be::VarChooser TriClearFlags [] = 
{
	{
		"TRICLEAR_STENCIL",
		VAL(CLEARFLAGS_STENCIL),
		"Clear the stencil buffer to 0.\r\n"
	},
	{
		"TRICLEAR_TARGET",
		VAL(CLEARFLAGS_TARGET),
		"Clear the render target to the scenes bgColor parameter.\r\n"
	},
	{
		"TRICLEAR_ZBUFFER",
		VAL(CLEARFLAGS_ZBUFFER),
		"Clear the depth buffer to 1.0.\r\n"
	},
	{0}
};

#if DEPRECATED_ENABLED


const Be::VarChooser TriFormat [] = 
{
	{
		"TRIFMT_UNKNOWN",
		VAL(D3DFMT_UNKNOWN),
		"Surface format is unknown.\r\n"
	},

	//Unsigned Formats
	{
		"TRIFMT_R8G8B8",
		VAL(D3DFMT_R8G8B8),
		"24-bit RGB pixel format with 8 bits per channel.\r\n"
	},
	{
		"TRIFMT_A8R8G8B8",
		VAL(D3DFMT_A8R8G8B8),
		"32-bit ARGB pixel format with alpha, using 8 bits per channel.\r\n"
	},
	{
		"TRIFMT_X8R8G8B8",
		VAL(D3DFMT_X8R8G8B8),
		"32-bit RGB pixel format, where 8 bits are reserved for each color.\r\n"
	},
	{
		"TRIFMT_R5G6B5",
		VAL(D3DFMT_R5G6B5),
		"16-bit RGB pixel format with 5 bits for red, 6 bits for green, and 5 bits for blue.\r\n"
	},
	{
		"TRIFMT_X1R5G5B5",
		VAL(D3DFMT_X1R5G5B5),
		"16-bit pixel format where 5 bits are reserved for each color.\r\n"
	},
	{
		"TRIFMT_A1R5G5B5",
		VAL(D3DFMT_A1R5G5B5),
		"16-bit pixel format where 5 bits are reserved for each color and 1 bit is "
		"reserved for alpha.\r\n"
	},
	{
		"TRIFMT_A4R4G4B4",
		VAL(D3DFMT_A4R4G4B4),
		"16-bit ARGB pixel format with 4 bits for each channel.\r\n"
	},
	{
		"TRIFMT_R3G3B2",
		VAL(D3DFMT_R3G3B2),
		"8-bit RGB texture format using 3 bits for red, 3 bits for green, and 2 bits for blue.\r\n"
	},
	{
		"TRIFMT_A8",
		VAL(D3DFMT_A8),
		"8-bit alpha only.\r\n"
	},
	{
		"TRIFMT_A8R3G3B2",
		VAL(D3DFMT_A8R3G3B2),
		"16-bit ARGB texture format using 8 bits for alpha, 3 bits each for red and green, and 2 bits for blue.\r\n"
	},
	{
		"TRIFMT_X4R4G4B4",
		VAL(D3DFMT_X4R4G4B4),
		"16-bit RGB pixel format using 4 bits for each color.\r\n"
	},
	{
		"TRIFMT_A2B10G10R10",
		VAL(D3DFMT_A2B10G10R10),
		"32-bit pixel format using 10 bits for each color and 2 bits for alpha.\r\n"
	},
	{
		"TRIFMT_A8B8G8R8",
		VAL(D3DFMT_A8B8G8R8),
		"32-bit ARGB pixel format with alpha, using 8 bits per channel.\r\n"
	},
	{
		"TRIFMT_X8B8G8R8",
		VAL(D3DFMT_X8B8G8R8),
		"32-bit RGB pixel format, where 8 bits are reserved for each color.\r\n"
	},
	{
		"TRIFMT_G16R16",
		VAL(D3DFMT_G16R16),
		"32-bit pixel format using 16 bits each for green and red.\r\n"
	},
	{
		"TRIFMT_A2R10G10B10",
		VAL(D3DFMT_A2R10G10B10),
		"32-bit pixel format using 10 bits each for red, green, and blue, and 2 bits for alpha.\r\n"
	},
	{
		"TRIFMT_A16B16G16R16",
		VAL(D3DFMT_A16B16G16R16),
		"64-bit pixel format using 16 bits for each component.\r\n"
	},
	{
		"TRIFMT_A8P8",
		VAL(D3DFMT_A8P8),
		"8-bit color indexed with 8 bits of alpha.\r\n"
	},
	{
		"TRIFMT_P8",
		VAL(D3DFMT_P8),
		"color indexed.\r\n"
	},
	{
		"TRIFMT_L8",
		VAL(D3DFMT_L8),
		"8-bit luminance only.\r\n"
	},
	{
		"TRIFMT_A8L8",
		VAL(D3DFMT_A8L8),
		"using 8 bits each for alpha and luminance.\r\n"
	},
	{
		"TRIFMT_A4L4",
		VAL(D3DFMT_A4L4),
		"using 4 bits each for alpha and luminance.\r\n"
	},
	// Signed Formats
	{
		"TRIFMT_V8U8",
		VAL(D3DFMT_V8U8),
		"16-bit bump-map format using 8 bits each for u and v data.\r\n"
	},
	{
		"TRIFMT_Q8W8V8U8",
		VAL(D3DFMT_Q8W8V8U8),
		"32-bit bump-map format using 8 bits for each channel.\r\n"
	},
	{
		"TRIFMT_V16U16",
		VAL(D3DFMT_V16U16 ),
		"32-bit bump-map format using 16 bits for each channel.\r\n"
	},
	{
		"TRIFMT_Q16W16V16U16",
		VAL(D3DFMT_Q16W16V16U16 ),
		"64-bit bump-map format using 16 bits for each component.\r\n"
	},
	{
		"TRIFMT_CxV8U8",
		VAL(D3DFMT_CxV8U8 ),
		"16-bit normal compression format. The texture sampler computes the C channel from: C = sqrt(1 - U2 - V2).\r\n"
	},

	//Mixed Formats
	{
		"TRIFMT_L6V5U5",
		VAL(D3DFMT_L6V5U5 ),
		"16-bit bump-map format with luminance using 6 bits for luminance, and 5 bits each for v and u.\r\n"
	},

	{
		"TRIFMT_X8L8V8U8",
		VAL(D3DFMT_X8L8V8U8 ),
		"32-bit bump-map format with luminance using 8 bits for each channel.\r\n"
	},
	{
		"TRIFMT_A2W10V10U10",
		VAL(D3DFMT_A2W10V10U10 ),
		"32-bit bump-map format using 2 bits for alpha and 10 bits each for w, v, and u.\r\n"
	},
	// FOURCC Formats
	{
		"TRIFMT_MULTI2_ARGB8",
		VAL(D3DFMT_MULTI2_ARGB8 ),
		"MultiElement texture (not compressed).\r\n"
	},
	{
		"TRIFMT_G8R8_G8B8",
		VAL(D3DFMT_G8R8_G8B8 ),
		"A 16-bit packed RGB format analogous to YUY2 (Y0U0, Y1V0, Y2U2, etc.). It requires a pixel pair in order to properly represent the color value. The first pixel in the pair contains 8 bits of green (in the high 8 bits) and 8 bits of red (in the low 8 bits). The second pixel contains 8 bits of green (in the high 8 bits) and 8 bits of blue (in the low 8 bits). Together, the two pixels share the red and blue components, while each has a unique green component (G0R0, G1B0, G2R2, etc.). The texture sampler does not normalize the colors when looking up into a pixel shader; they remain in the range of 0.0f to 255.0f. This is true for all programmable pixel shader models. For the fixed function pixel shader, the hardware should normalize to the 0.f to 1.f range and essentially treat it as the YUY2 texture. Hardware that exposes this format must have the PixelShader1xMaxValue member of D3DCAPS9 set to a value capable of handling that range.\r\n"
	},
	{
		"TRIFMT_R8G8_B8G8",
		VAL(D3DFMT_R8G8_B8G8 ),
		"A 16-bit packed RGB format analogous to UYVY (U0Y0, V0Y1, U2Y2, etc.). It requires a pixel pair in order to properly represent the color value. The first pixel in the pair contains 8 bits of green (in the low 8 bits) and 8 bits of red (in the high 8 bits). The second pixel contains 8 bits of green (in the low 8 bits) and 8 bits of blue (in the high 8 bits). Together, the two pixels share the red and blue components, while each has a unique green component (R0G0, B0G1, R2G2, etc.). The texture sampler does not normalize the colors when looking up into a pixel shader; they remain in the range of 0.0f to 255.0f. This is true for all programmable pixel shader models. For the fixed function pixel shader, the hardware should normalize to the 0.f to 1.f range and essentially treat it as the YUY2 texture. Hardware that exposes this format must have PixelShader1xMaxValue member of D3DCAPS9 set to a value capable of handling that range.\r\n"
	},
	{
		"TRIFMT_DXT1",
		VAL(D3DFMT_DXT1 ),
		"DXT1 compression texture format.\r\n"
	},
	{
		"TRIFMT_DXT2",
		VAL(D3DFMT_DXT2 ),
		"DXT2 compression texture format.\r\n"
	},
	{
		"TRIFMT_DXT3",
		VAL(D3DFMT_DXT3 ),
		"DXT3 compression texture format.\r\n"
	},
	{
		"TRIFMT_DXT4",
		VAL(D3DFMT_DXT4 ),
		"DXT4 compression texture format.\r\n"
	},
	{
		"TRIFMT_DXT5",
		VAL(D3DFMT_DXT5 ),
		"DXT5 compression texture format.\r\n"
	},
	{
		"TRIFMT_UYVY",
		VAL(D3DFMT_UYVY ),
		"UYVY format (PC98 compliance).\r\n"
	},
	{
		"TRIFMT_YUY2",
		VAL(D3DFMT_YUY2 ),
		"YUY2 format (PC98 compliance).\r\n"
	},

	//Buffer Formats
	{
		"TRIFMT_D16_LOCKABLE",
		VAL(D3DFMT_D16_LOCKABLE ),
		"16-bit z-buffer bit depth. This is an application-lockable surface format.\r\n"
	},
	{
		"TRIFMT_D32",
		VAL(D3DFMT_D32 ),
		"32-bit z-buffer bit depth.\r\n"
	},
	{
		"TRIFMT_D15S1",
		VAL(D3DFMT_D15S1 ),
		"z-buffer bit depth where 15 bits are reserved for the depth channel and 1 bit is reserved for the stencil channel.\r\n"		
	},
	{
		"TRIFMT_D24S8",
		VAL(D3DFMT_D24S8 ),
		"32-bit z-buffer bit depth using 24 bits for the depth channel and 8 bits for the stencil channel."
	},
	{
		"TRIFMT_D24X8",
		VAL(D3DFMT_D24X8 ),
		"z-buffer bit depth using 24 bits for the depth channel."
	},
	{
		"TRIFMT_D24X4S4",
		VAL(D3DFMT_D24X4S4 ),
		"32-bit z-buffer bit depth using 24 bits for the depth channel and 4 bits for the stencil channel."
	},
	{
		"TRIFMT_D32F_LOCKABLE",
		VAL(D3DFMT_D32F_LOCKABLE ),
		"A lockable format where the depth value is represented as a standard IEEE floating-point number."
	},
	{
		"TRIFMT_D24FS8",
		VAL(D3DFMT_D24FS8 ),
		"A non-lockable format that contains 24 bits of depth (in a 24-bit floating point format - 20e4) and 8 bits of stencil."
	},
	{
		"TRIFMT_D16",
		VAL(D3DFMT_D16 ),
		"16-bit z-buffer bit depth.\r\n"
	},
	{
		"TRIFMT_VERTEXDATA",
		VAL(D3DFMT_VERTEXDATA ),
		"Describes a vertex buffer surface.\r\n"
	},
	{
		"TRIFMT_INDEX16",
		VAL(D3DFMT_INDEX16 ),
		"16-bit index buffer bit depth.\r\n"
	},
	{
		"TRIFMT_INDEX32",
		VAL(D3DFMT_INDEX32 ),
		"32-bit index buffer bit depth.\r\n"
	},

	// Floating-Point Formats
	{
		"TRIFMT_R16F",
		VAL(D3DFMT_R16F ),
		"16-bit float format using 16 bits for the red channel.\r\n"
	},
	{
		"TRIFMT_G16R16F",
		VAL(D3DFMT_G16R16F ),
		"32-bit float format using 16 bits for the red channel and 16 bits for the green channel.\r\n"
	},
	{
		"TRIFMT_A16B16G16R16F",
		VAL(D3DFMT_A16B16G16R16F ),
		"64-bit float format using 16 bits for the each channel (alpha, blue, green, red).\r\n"
	},
	// IEEE Formats
	{
		"TRIFMT_R32F",
		VAL(D3DFMT_R32F ),
		"32-bit float format using 32 bits for the red channel.\r\n"
	},
	{
		"TRIFMT_G32R32F",
		VAL(D3DFMT_G32R32F ),
		"64-bit float format using 32 bits for the red channel and 32 bits for the green channel.\r\n"
	},
	{
		"TRIFMT_A32B32G32R32F",
		VAL(D3DFMT_A32B32G32R32F ),
		"128-bit float format using 32 bits for the each channel (alpha, blue, green, red).\r\n"
	},
	{
		"TRIFMT_INTZ",
		VAL( MAKEFOURCC( 'I', 'N', 'T', 'Z' ) ),
		"32-bit format for depth texture (24-bit depth + 8-bit stencil).\r\n"
	},
	{0}
};


const Be::VarChooser TriFormatZStencil [] = 
{
	{
		"TRIFMT_D16_LOCKABLE",
		VAL(D3DFMT_D16_LOCKABLE ),
		"16-bit z-buffer bit depth. This is an application-lockable surface format.\r\n"
	},
	{
		"TRIFMT_D32",
		VAL(D3DFMT_D32 ),
		"32-bit z-buffer bit depth.\r\n"
	},
	{
		"TRIFMT_D15S1",
		VAL(D3DFMT_D15S1 ),
		"z-buffer bit depth where 15 bits are reserved for the depth channel and 1 bit is reserved for the stencil channel.\r\n"		
	},
	{
		"TRIFMT_D24S8",
		VAL(D3DFMT_D24S8 ),
		"32-bit z-buffer bit depth using 24 bits for the depth channel and 8 bits for the stencil channel."
	},
	{
		"TRIFMT_D24X8",
		VAL(D3DFMT_D24X8 ),
		"z-buffer bit depth using 24 bits for the depth channel."
	},
	{
		"TRIFMT_D24X4S4",
		VAL(D3DFMT_D24X4S4 ),
		"32-bit z-buffer bit depth using 24 bits for the depth channel and 4 bits for the stencil channel."
	},
	{
		"TRIFMT_D32F_LOCKABLE",
		VAL(D3DFMT_D32F_LOCKABLE ),
		"A lockable format where the depth value is represented as a standard IEEE floating-point number."
	},
	{
		"TRIFMT_D24FS8",
		VAL(D3DFMT_D24FS8 ),
		"A non-lockable format that contains 24 bits of depth (in a 24-bit floating point format - 20e4) and 8 bits of stencil."
	},
	{
		"TRIFMT_D16",
		VAL(D3DFMT_D16 ),
		"16-bit z-buffer bit depth.\r\n"
	},
	{
		"TRIFMT_VERTEXDATA",
		VAL(D3DFMT_VERTEXDATA ),
		"Describes a vertex buffer surface.\r\n"
	},
	{
		"TRIFMT_INDEX16",
		VAL(D3DFMT_INDEX16 ),
		"16-bit index buffer bit depth.\r\n"
	},
	{
		"TRIFMT_INDEX32",
		VAL(D3DFMT_INDEX32 ),
		"32-bit index buffer bit depth.\r\n"
	},
	{0}
};

const Be::VarChooser TriZBufferType [] = 
{
	{
		"TRIZB_FALSE",
		VAL(D3DZB_FALSE),
		"Disable depth buffering.\r\n"
	},
	{
		"D3DZB_TRUE",
		VAL(D3DZB_TRUE),
		"Enable z-buffering.\r\n"
	},
	{
		"D3DZB_USEW",
		VAL(D3DZB_USEW),
		"Enable w-buffering.\r\n"
	},
	{0}
};
     
const Be::VarChooser TriResourceTypeChooser [] = 
{
	{
		"TRIRTYPE_SURFACE",
		VAL(D3DRTYPE_SURFACE),
		"Surface resource.\r\n"
	},
	{
		"TRIRTYPE_VOLUME",
		VAL(D3DRTYPE_VOLUME),
		"Volume resource.\r\n"
	},
	{
		"TRIRTYPE_TEXTURE",
		VAL(D3DRTYPE_TEXTURE  ),
		"Texture resource.\r\n"
	},
	{
		"TRIRTYPE_VOLUMETEXTURE",
		VAL(D3DRTYPE_VOLUMETEXTURE  ),
		"Volume texture resource.\r\n"
	},
	{
		"TRIRTYPE_CUBETEXTURE",
		VAL(D3DRTYPE_CUBETEXTURE  ),
		"Cube texture resource.\r\n"
	},
	{
		"TRIRTYPE_VERTEXBUFFER",
		VAL(D3DRTYPE_VERTEXBUFFER  ),
		"Vertex buffer resource.\r\n"
	},
	{
		"TRIRTYPE_INDEXBUFFER",
		VAL(D3DRTYPE_INDEXBUFFER  ),
		"Index buffer resource.\r\n"
	},
	{0}
};


const Be::VarChooser TriPool [] = 
{
	{
		"TRIPOOL_DEFAULT",
		VAL(D3DPOOL_DEFAULT),
		"See D3D doc.\r\n"
	},
	{
		"TRIPOOL_MANAGED",
		VAL(D3DPOOL_MANAGED),
		"See D3D doc.\r\n"
	},
	{
		"TRIPOOL_SYSTEMMEM",
		VAL(D3DPOOL_SYSTEMMEM  ),
		"See D3D doc.\r\n"
	},
	{
		"TRIPOOL_SCRATCH",
		VAL(D3DPOOL_SCRATCH),
		"See D3D doc.\r\n"
	},
	{0}
};                                                                                    


const Be::VarChooser TriFVF [] = 
{
	{
		"TRIFVF_DIFFUSE",
		VAL(D3DFVF_DIFFUSE),
		"Vertex format includes a diffuse color component.\r\n"
	},
	{
		"TRIFVF_NORMAL",
		VAL(D3DFVF_NORMAL),
		"Vertex format includes a vertex normal vector. This flag cannot be used with "
		"the D3DFVF_XYZRHW flag.\r\n"
	},
	{
		"TRIFVF_PSIZE",
		VAL(D3DFVF_PSIZE),
		"Vertex format includes a vertex normal vector. This flag cannot be used with "
		"the D3DFVF_XYZRHW flag.\r\n"
	},
	{
		"TRIFVF_SPECULAR",
		VAL(D3DFVF_SPECULAR  ),
		"Vertex format includes a specular color component. \r\n"
	},
	{
		"TRIFVF_XYZ",
		VAL(D3DFVF_XYZ),
		"Vertex format includes the position of an untransformed vertex. This flag "
		"cannot be used with the D3DFVF_XYZRHW flag.\r\n"
	},
	{
		"TRIFVF_XYZRHW",
		VAL(D3DFVF_XYZRHW),
		"Vertex format includes the position of a transformed vertex. This flag "
		"cannot be used with the D3DFVF_XYZ or D3DFVF_NORMAL flags.\r\n"
	},
	{
		"TRIFVF_XYZB1",
		VAL(D3DFVF_XYZB1),
		"Vertex format contains position data, and a corresponding number of "
		"weighting (beta) values to use for multimatrix vertex blending operations. "
		"Currently, Microsoft® Direct3D® can blend with up to three weighting values "
		"and four blending matrices. For more information on using blending matrices, "
		"see Indexed Vertex Blending.\r\n"
	},
	{
		"TRIFVF_XYZB2",
		VAL(D3DFVF_XYZB2),
		"See TRIFVF_XYB1\r\n"
	},
	{
		"TRIFVF_XYZB3",
		VAL(D3DFVF_XYZB3),
		"See TRIFVF_XYB1\r\n"
	},
	{
		"TRIFVF_XYZB4",
		VAL(D3DFVF_XYZB4),
		"See TRIFVF_XYB1\r\n"
	},
	{
		"TRIFVF_XYZB5",
		VAL(D3DFVF_XYZB5),
		"See TRIFVF_XYB1\r\n"
	},
	{
		"TRIFVF_TEX0",
		VAL(D3DFVF_TEX0),
		"Number of texture coordinate sets for this vertex. The actual values "
		"for these flags are not sequential.\r\n"
	},
	{
		"TRIFVF_TEX1",
		VAL(D3DFVF_TEX1),
		"See TRIFVF_TEX0\r\n"
	},
	{
		"TRIFVF_TEX2",
		VAL(D3DFVF_TEX2),
		"See TRIFVF_TEX0\r\n"
	},
	{
		"TRIFVF_TEX3",
		VAL(D3DFVF_TEX3),
		"See TRIFVF_TEX0\r\n"
	},
	{
		"TRIFVF_TEX4",
		VAL(D3DFVF_TEX4),
		"See TRIFVF_TEX0\r\n"
	},
	{
		"TRIFVF_TEX5",
		VAL(D3DFVF_TEX5),
		"See TRIFVF_TEX0\r\n"
	},
	{
		"TRIFVF_TEX6",
		VAL(D3DFVF_TEX6),
		"See TRIFVF_TEX0\r\n"
	},
	{
		"TRIFVF_TEX7",
		VAL(D3DFVF_TEX7),
		"See TRIFVF_TEX0\r\n"
	},
	{
		"TRIFVF_TEX8",
		VAL(D3DFVF_TEX8),
		"See TRIFVF_TEX0\r\n"
	},
/*
	{
		"TRIFVF_TEXTUREFORMAT1",
		VAL(D3DFVF_TEXTUREFORMAT1),
		"Number of values that define a texture coordinate set. The "
		"D3DFVF_TEXTUREFORMAT1 indicates one-dimensional texture coordinates, "
		"D3DFVF_TEXTUREFORMAT2 indicates two-dimensional texture coordinates, and "
		"so on. These flags are rarely used alone; they are used with the "
		"D3DFVF_TEXCOORDSIZEn macros.\r\n"
	},
	{
		"TRIFVF_TEXTUREFORMAT2",
		VAL(D3DFVF_TEXTUREFORMAT2),
		"See D3DFVF_TEXTUREFORMAT1\r\n"
	},

	{
		"TRIFVF_TEXTUREFORMAT3",
		VAL(D3DFVF_TEXTUREFORMAT3),
		"Vertex format includes a diffuse color component.\r\n"
	},
	{
		"TRIFVF_TEXTUREFORMAT4",
		VAL(D3DFVF_TEXTUREFORMAT4),
		"Vertex format includes a diffuse color component.\r\n"
	},
*/
	{
		"D3DFVF_LASTBETA_UBYTE4",
		VAL(D3DFVF_LASTBETA_UBYTE4),
		"When using indexed vertex blending and a fixed function FVF vertex shader, you "
		"must specify this flag for the vertex shader. \r\n"
	},

/* MASK VALUES which cannot be chosen
	{
		"TRIFVF_POSITION_MASK",
		VAL(D3DFVF_POSITION_MASK),
		"Vertex format includes a diffuse color component.\r\n"
	},
	{
		"D3DFVF_RESERVED0",
		VAL(D3DFVF_RESERVED0),
		"Mask values for reserved bits in the flexible vertex format. Do not use.\r\n"
	},
	{
		"D3DFVF_RESERVED0",
		VAL(D3DFVF_RESERVED0),
		"Mask values for reserved bits in the flexible vertex format. Do not use.\r\n"
	},
	{
		"D3DFVF_RESERVED2",
		VAL(D3DFVF_RESERVED2),
		"Mask values for reserved bits in the flexible vertex format. Do not use.\r\n"
	},
	{
		"D3DFVF_TEXCOUNT_MASK",
		VAL(D3DFVF_TEXCOUNT_MASK),
		"Mask value for texture flag bits.\r\n"
	},	
	{
		"D3DFVF_TEXCOUNT_SHIFT",
		VAL(D3DFVF_TEXCOUNT_SHIFT),
		"The number of bits by which to shift an integer value that identifies the "
		"number of a texture coordinates for a vertex. This value might be used as "
		"follows:\r\n"
	},
*/
	{0}
};


const Be::VarChooser TriUsage [] = 
{
	{
		"TRIUSAGE_RENDERTARGET",
		VAL(D3DUSAGE_RENDERTARGET),
		"n/a.\r\n"
	},
	{
		"TRIUSAGE_DEPTHSTENCIL",
		VAL(D3DUSAGE_DEPTHSTENCIL),
		"n/a.\r\n"
	},
	{
		"TRIUSAGE_AUTOGENMIPMAP",
		VAL(D3DUSAGE_AUTOGENMIPMAP),
		"Auto generate mipmaps"
	},
	{0}
};


const Be::VarChooser TriUsageVertexIndex [] = 
{
	{
		"TRIUSAGE_WRITEONLY",
		VAL(D3DUSAGE_WRITEONLY),
		"n/a.\r\n"
	},
	{
		"TRIUSAGE_SOFTWAREPROCESSING",
		VAL(D3DUSAGE_SOFTWAREPROCESSING),
		"n/a.\r\n"
	},
	{
		"TRIUSAGE_DONOTCLIP",
		VAL(D3DUSAGE_DONOTCLIP),
		"n/a.\r\n"
	},
	{
		"TRIUSAGE_POINTS",
		VAL(D3DUSAGE_POINTS),
		"n/a.\r\n"
	},
	{
		"TRIUSAGE_RTPATCHES",
		VAL(D3DUSAGE_RTPATCHES),
		"n/a.\r\n"
	},
	{
		"TRIUSAGE_NPATCHES",
		VAL(D3DUSAGE_NPATCHES),
		"n/a.\r\n"
	},
	{
		"TRIUSAGE_DYNAMIC",
		VAL(D3DUSAGE_DYNAMIC),
		"n/a.\r\n"
	},
	{0}
};


const Be::VarChooser TriVertexDeclType [] = 
{
	{
		"TRIDECLTYPE_FLOAT1",
		VAL(D3DDECLTYPE_FLOAT1),
		"1D float expanded to (value, 0., 0., 1.)\r\n"
	},
	{
		"TRIDECLTYPE_FLOAT2",
		VAL(D3DDECLTYPE_FLOAT2),
		"2D float expanded to (value, value, 0., 1.)\r\n"
	},
	{
		"TRIDECLTYPE_FLOAT3",
		VAL(D3DDECLTYPE_FLOAT3),
		"3D float expanded to (value, value, value, 1.)\r\n"
	},
	{
		"TRIDECLTYPE_FLOAT4",
		VAL(D3DDECLTYPE_FLOAT4),
		"4D float\r\n"
	},
	{
		"TRIDECLTYPE_D3DCOLOR",
		VAL(D3DDECLTYPE_D3DCOLOR),
		"4D packed unsigned bytes mapped to 0. to 1. range. Input is in D3DCOLOR format (ARGB) expanded to (R, G, B, A)\r\n"
	},
	{
		"TRIDECLTYPE_UBYTE4",
		VAL(D3DDECLTYPE_UBYTE4),
		"4D unsigned byte.\r\n"
	},
	{
		"TRIDECLTYPE_SHORT2",
		VAL(D3DDECLTYPE_SHORT2),
		"2D signed short expanded to (value, value, 0., 1.)\r\n"
	},
	{
		"TRIDECLTYPE_SHORT4",
		VAL(D3DDECLTYPE_SHORT4),
		"4D signed short.\r\n"
	},
	// vx shader 2.0 types not added
	{
		"TRIDECLTYPE_UNUSED",
		VAL(D3DDECLTYPE_UNUSED),
		"When the type field in a decl is unused.\r\n"
	},
	{0}
};


const Be::VarChooser TriVertexDeclMethod [] = 
{
	{
		"TRIDECLMETHOD_DEFAULT",
		VAL(D3DDECLMETHOD_DEFAULT),
		"n/a.\r\n"
	},
	{
		"TRIDECLMETHOD_PARTIALU",
		VAL(D3DDECLMETHOD_PARTIALU),
		"n/a.\r\n"
	},
	{
		"TRIDECLMETHOD_PARTIALV",
		VAL(D3DDECLMETHOD_PARTIALV),
		"n/a.\r\n"
	},
	{
		"TRIDECLMETHOD_CROSSUV",
		VAL(D3DDECLMETHOD_CROSSUV),
		"n/a.\r\n"
	},
	{
		"TRIDECLMETHOD_UV",
		VAL(D3DDECLMETHOD_UV),
		"n/a.\r\n"
	},
	{
		"TRIDECLMETHOD_LOOKUP",
		VAL(D3DDECLMETHOD_LOOKUP),
		"n/a.\r\n"
	},
	{
		"TRIDECLMETHOD_LOOKUPPRESAMPLED",
		VAL(D3DDECLMETHOD_LOOKUPPRESAMPLED),
		"n/a.\r\n"
	},
	{0}
};

const Be::VarChooser TriVertexDeclUsage [] = 
{
	{
		"TRIDECLUSAGE_POSITION",
		VAL(D3DDECLUSAGE_POSITION),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_BLENDWEIGHT",
		VAL(D3DDECLUSAGE_BLENDWEIGHT),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_BLENDINDICES",
		VAL(D3DDECLUSAGE_BLENDINDICES),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_NORMAL",
		VAL(D3DDECLUSAGE_NORMAL),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_PSIZE",
		VAL(D3DDECLUSAGE_PSIZE),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_TEXCOORD",
		VAL(D3DDECLUSAGE_TEXCOORD),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_TANGENT",
		VAL(D3DDECLUSAGE_TANGENT),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_BINORMAL",
		VAL(D3DDECLUSAGE_BINORMAL),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_TESSFACTOR",
		VAL(D3DDECLUSAGE_TESSFACTOR),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_POSITIONT",
		VAL(D3DDECLUSAGE_POSITIONT),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_COLOR",
		VAL(D3DDECLUSAGE_COLOR),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_FOG",
		VAL(D3DDECLUSAGE_FOG),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_DEPTH",
		VAL(D3DDECLUSAGE_DEPTH),
		"n/a.\r\n"
	},
	{
		"TRIDECLUSAGE_SAMPLE",
		VAL(D3DDECLUSAGE_SAMPLE),
		"n/a.\r\n"
	},
	{0}
};
        

const Be::VarChooser TriSetGammaRamp [] = 
{
	{
		"TRISGR_CALIBRATE",
		VAL(D3DSGR_CALIBRATE),
		"n/a.\r\n"
	},
	{
		"TRISGR_NO_CALIBRATION",
		VAL(D3DSGR_NO_CALIBRATION),
		"n/a.\r\n"
	},
	{0}
};

#endif

const Be::VarChooser TriHACKFORTESTING [] = 
{
	{
		"TRIVSDE_POSITION",
		VAL(0),
		"n/a.\r\n"
	},
	{
		"TRIVSDE_NORMAL",
		VAL(1),
		"n/a.\r\n"
	},
	{0}
};

#if DEPRECATED_ENABLED

const Be::VarChooser TriPresentMethodFlag [] = 
{
	{
		"D3DPRESENT_DONOTWAIT", 
		VAL(D3DPRESENT_DONOTWAIT),
		"Don't wait for Present"
	},
	{
		"D3DPRESENT_LINEAR_CONTENT", 
		VAL(D3DPRESENT_LINEAR_CONTENT),
		"The content of the back buffer to be presented is in the linear color space"
	},
	{0}
};

#endif

const Be::VarChooser TriScissorMode[] =
{
	{
		"SCISSOR_NONE",
		VAL(SCISSOR_NONE),
		"disable scissoring"
	},
	{
		"SCISSOR_SCISSOR",
		VAL(SCISSOR_SCISSOR),
		"use d3d scissoring"
	},
	{
		"SCISSOR_EMULATE",
		VAL(SCISSOR_EMULATE),
		"emulate d3d scissoring"
	},
	{
		"SCISSOR_CHOOSE",
		VAL(SCISSOR_CHOOSE),
		"choose d3d scissoring"
	},
	{0}
};

const Be::VarChooser TriBipedMovementState[] =
{
	{
		"TRIBPS_IDLE",
		VAL(TRIBPS_IDLE),
		"Idle"
	},
	{
		"TRIBPS_WALKING",
		VAL(TRIBPS_WALKING),
		"Walking"
	},
	{
		"TRIBPS_TURNING",
		VAL(TRIBPS_TURNING),
		"Turning"
	},
	{
		"TRIBPS_RUNNING",
		VAL(TRIBPS_RUNNING),
		"Running"
	},
	{
		"TRIBPS_STRAFING",
		VAL(TRIBPS_STRAFING),
		"Running"
	},
	{0}
};

const Be::VarChooser TriSkeletonType[] =
{
	{
		"TRIST_MAIN",
		VAL(TRIST_MAIN),
		"Main skeleton"
	},
	{
		"TRIST_CLOTH_UPPER",
		VAL(TRIST_CLOTH_UPPER),
		"Upper cloth skeleton"
	},
	{
		"TRIST_CLOTH_LOWER",
		VAL(TRIST_CLOTH_LOWER),
		"Lower cloth skeleton"
	},
	{0}
};

const Be::VarChooser TriD3DRenderState[] =
{
	KV_RC( 
		RS_ZENABLE,
		"Depth-buffering state as one member of the ZBUFFERTYPE enumerated type.\n"
		"Set this state to ZB_TRUE to enable z-buffering, ZB_USEW to enable\n"
		"w-buffering, or ZB_FALSE to disable depth buffering. The default value\n"
		"for this render state is ZB_TRUE if a depth stencil was created along\n"
		"with the swap chain by setting the EnableAutoDepthStencil member of the\n"
		"PRESENT_PARAMETERS structure to TRUE, and ZB_FALSE otherwise."
	),
	KV_RC( 
		RS_FILLMODE, 
		"One or more members of the FILLMODE enumerated type.\n"
		"The default value is FILL_SOLID."
	),
	KV_RC( RS_SHADEMODE, "" ),
	KV_RC( RS_ZWRITEENABLE, "" ),
	KV_RC( RS_ALPHATESTENABLE, "" ),
	KV_RC( RS_LASTPIXEL, "" ),
	KV_RC( RS_SRCBLEND, "" ),
	KV_RC( RS_DESTBLEND, "" ),
	KV_RC( RS_CULLMODE, "" ),
	KV_RC( RS_ZFUNC, "" ),
	KV_RC( RS_ALPHAREF, "" ),
	KV_RC( RS_DITHERENABLE, "" ),
	KV_RC( RS_ALPHABLENDENABLE, "" ),
	KV_RC( RS_ALPHABLENDENABLE, "" ),
	KV_RC( RS_FOGENABLE, "" ),
	KV_RC( RS_SPECULARENABLE, "" ),
	KV_RC( RS_FOGCOLOR, "" ),
	KV_RC( RS_FOGTABLEMODE, "" ),
	KV_RC( RS_FOGSTART, "" ),
	KV_RC( RS_FOGEND, "" ),
	KV_RC( RS_FOGDENSITY, "" ),
	KV_RC( RS_RANGEFOGENABLE, "" ),
	KV_RC( RS_STENCILENABLE, "" ),
	KV_RC( RS_STENCILFAIL, "" ),
	KV_RC( RS_STENCILZFAIL, "" ),
	KV_RC( RS_STENCILPASS, "" ),
	KV_RC( RS_STENCILFUNC, "" ),
	KV_RC( RS_STENCILREF, "" ),
	KV_RC( RS_STENCILMASK, "" ),
	KV_RC( RS_STENCILWRITEMASK, "" ),
	KV_RC( RS_TEXTUREFACTOR, "" ),
	KV_RC( RS_WRAP0, "" ),
	KV_RC( RS_WRAP1, "" ),
	KV_RC( RS_WRAP2, "" ),
	KV_RC( RS_WRAP3, "" ),
	KV_RC( RS_WRAP4, "" ),
	KV_RC( RS_WRAP5, "" ),
	KV_RC( RS_WRAP6, "" ),
	KV_RC( RS_WRAP7, "" ),
	KV_RC( RS_CLIPPING, "" ),
	KV_RC( RS_LIGHTING, "" ),
	KV_RC( RS_AMBIENT, "" ),
	KV_RC( RS_FOGVERTEXMODE, "" ),
	KV_RC( RS_COLORVERTEX, "" ),
	KV_RC( RS_LOCALVIEWER, "" ),
	KV_RC( RS_NORMALIZENORMALS, "" ),
	KV_RC( RS_DIFFUSEMATERIALSOURCE, "" ),
	KV_RC( RS_SPECULARMATERIALSOURCE, "" ),
	KV_RC( RS_AMBIENTMATERIALSOURCE, "" ),
	KV_RC( RS_EMISSIVEMATERIALSOURCE, "" ),
	KV_RC( RS_VERTEXBLEND, "" ),
	KV_RC( RS_CLIPPLANEENABLE, "" ),
	KV_RC( RS_POINTSIZE, "" ),
	KV_RC( RS_POINTSIZE_MIN, "" ),
	KV_RC( RS_POINTSPRITEENABLE, "" ),
	KV_RC( RS_POINTSCALEENABLE, "" ),
	KV_RC( RS_POINTSCALE_A, "" ),
	KV_RC( RS_POINTSCALE_B, "" ),
	KV_RC( RS_POINTSCALE_C, "" ),
	KV_RC( RS_MULTISAMPLEANTIALIAS, "" ),
	KV_RC( RS_MULTISAMPLEMASK, "" ),
	KV_RC( RS_PATCHEDGESTYLE, "" ),
	KV_RC( RS_DEBUGMONITORTOKEN, "" ),
	KV_RC( RS_POINTSIZE_MAX, "" ),
	KV_RC( RS_INDEXEDVERTEXBLENDENABLE, "" ),
	KV_RC( RS_COLORWRITEENABLE, "" ),
	KV_RC( RS_TWEENFACTOR, "" ),
	KV_RC( RS_BLENDOP, "" ),
	KV_RC( RS_POSITIONDEGREE, "" ),
	KV_RC( RS_NORMALDEGREE, "" ),
	KV_RC( RS_SCISSORTESTENABLE, "" ),
	KV_RC( RS_SLOPESCALEDEPTHBIAS, "" ),
	KV_RC( RS_ANTIALIASEDLINEENABLE, "" ),
	KV_RC( RS_MINTESSELLATIONLEVEL, "" ),
	KV_RC( RS_MAXTESSELLATIONLEVEL, "" ),
	KV_RC( RS_ADAPTIVETESS_X, "" ),
	KV_RC( RS_ADAPTIVETESS_Y, "" ),
	KV_RC( RS_ADAPTIVETESS_Z, "" ),
	KV_RC( RS_ADAPTIVETESS_W, "" ),
	KV_RC( RS_ENABLEADAPTIVETESSELLATION, "" ),
	KV_RC( RS_TWOSIDEDSTENCILMODE, "" ),
	KV_RC( RS_CCW_STENCILFAIL, "" ),
	KV_RC( RS_CCW_STENCILZFAIL, "" ),
	KV_RC( RS_CCW_STENCILPASS, "" ),
	KV_RC( RS_CCW_STENCILFUNC, "" ),
	KV_RC( RS_COLORWRITEENABLE1, "" ),
	KV_RC( RS_COLORWRITEENABLE2, "" ),
	KV_RC( RS_COLORWRITEENABLE3, "" ),
	KV_RC( RS_BLENDFACTOR, "" ),
	KV_RC( RS_SRGBWRITEENABLE, "" ),
	KV_RC( RS_DEPTHBIAS, "" ),
	KV_RC( RS_WRAP8, "" ),
	KV_RC( RS_WRAP9, "" ),
	KV_RC( RS_WRAP10, "" ),
	KV_RC( RS_WRAP11, "" ),
	KV_RC( RS_WRAP12, "" ),
	KV_RC( RS_WRAP13, "" ),
	KV_RC( RS_WRAP14, "" ),
	KV_RC( RS_WRAP15, "" ),
	KV_RC( RS_SEPARATEALPHABLENDENABLE, "" ),
	KV_RC( RS_SRCBLENDALPHA, "" ),
	KV_RC( RS_DESTBLENDALPHA, "" ),
	KV_RC( RS_BLENDOPALPHA, "" ),

	{0}
};

#if DEPRECATED_ENABLED

const Be::VarChooser TriD3DFormat [] = 
{
	KV( D3DFMT_UNKNOWN, 	"Surface format is unknown.\r\n" ),

	//Unsigned Formats
	KV( 
		D3DFMT_R8G8B8,
		"24-bit RGB pixel format with 8 bits per channel.\r\n"
	),
	KV( 
		D3DFMT_A8R8G8B8,
		"32-bit ARGB pixel format with alpha, using 8 bits per channel.\r\n"
	),
	KV( 
		D3DFMT_X8R8G8B8,
		"32-bit RGB pixel format, where 8 bits are reserved for each color.\r\n"
	),
	KV( 
		D3DFMT_R5G6B5,
		"16-bit RGB pixel format with 5 bits for red, 6 bits for green, and 5 bits for blue.\r\n"
	),
	KV( 
		D3DFMT_X1R5G5B5,
		"16-bit pixel format where 5 bits are reserved for each color.\r\n"
	),
	KV( 
		D3DFMT_A1R5G5B5,
		"16-bit pixel format where 5 bits are reserved for each color and 1 bit is "
		"reserved for alpha.\r\n"
	),
	KV( 
		D3DFMT_A4R4G4B4,
		"16-bit ARGB pixel format with 4 bits for each channel.\r\n"
	),
	KV( 
		D3DFMT_R3G3B2,
		"8-bit RGB texture format using 3 bits for red, 3 bits for green, and 2 bits for blue.\r\n"
	),
	KV( 
		D3DFMT_A8,
		"8-bit alpha only.\r\n"
	),
	KV( 
		D3DFMT_A8R3G3B2,
		"16-bit ARGB texture format using 8 bits for alpha, 3 bits each for red and green, and 2 bits for blue.\r\n"
	),
	KV( 
		D3DFMT_X4R4G4B4,
		"16-bit RGB pixel format using 4 bits for each color.\r\n"
	),
	KV( 
		D3DFMT_A2B10G10R10,
		"32-bit pixel format using 10 bits for each color and 2 bits for alpha.\r\n"
	),
	KV( 
		D3DFMT_A8B8G8R8,
		"32-bit ARGB pixel format with alpha, using 8 bits per channel.\r\n"
	),
	KV( 
		D3DFMT_X8B8G8R8,
		"32-bit RGB pixel format, where 8 bits are reserved for each color.\r\n"
	),
	KV( 
		D3DFMT_G16R16,
		"32-bit pixel format using 16 bits each for green and red.\r\n"
	),
	KV( 
		D3DFMT_A2R10G10B10,
		"32-bit pixel format using 10 bits each for red, green, and blue, and 2 bits for alpha.\r\n"
	),
	KV( 
		D3DFMT_A16B16G16R16,
		"64-bit pixel format using 16 bits for each component.\r\n"
	),
	KV( 
		D3DFMT_A8P8,
		"8-bit color indexed with 8 bits of alpha.\r\n"
	),
	KV( 
		D3DFMT_P8,
		"color indexed.\r\n"
	),
	KV( 
		D3DFMT_L8,
		"8-bit luminance only.\r\n"
	),
	KV( 
		D3DFMT_A8L8,
		"using 8 bits each for alpha and luminance.\r\n"
	),
	KV( 
		D3DFMT_A4L4,
		"using 4 bits each for alpha and luminance.\r\n"
	),
	// Signed Formats
	KV( 
		D3DFMT_V8U8,
		"16-bit bump-map format using 8 bits each for u and v data.\r\n"
	),
	KV( 
		D3DFMT_Q8W8V8U8,
		"32-bit bump-map format using 8 bits for each channel.\r\n"
	),
	KV( 
		D3DFMT_V16U16 ,
		"32-bit bump-map format using 16 bits for each channel.\r\n"
	),
	KV( 
		D3DFMT_Q16W16V16U16 ,
		"64-bit bump-map format using 16 bits for each component.\r\n"
	),
	KV( 
		D3DFMT_CxV8U8 ,
		"16-bit normal compression format. The texture sampler computes the C channel from: C = sqrt(1 - U2 - V2).\r\n"
	),

	//Mixed Formats
	KV( 
		D3DFMT_L6V5U5 ,
		"16-bit bump-map format with luminance using 6 bits for luminance, and 5 bits each for v and u.\r\n"
	),

	KV( 
		D3DFMT_X8L8V8U8 ,
		"32-bit bump-map format with luminance using 8 bits for each channel.\r\n"
	),
	KV( 
		D3DFMT_A2W10V10U10 ,
		"32-bit bump-map format using 2 bits for alpha and 10 bits each for w, v, and u.\r\n"
	),
	// FOURCC Formats
	KV( 
		D3DFMT_MULTI2_ARGB8 ,
		"MultiElement texture (not compressed).\r\n"
	),
	KV( 
		D3DFMT_G8R8_G8B8 ,
		"A 16-bit packed RGB format analogous to YUY2 (Y0U0, Y1V0, Y2U2, etc.). It requires a pixel pair in order to properly represent the color value. The first pixel in the pair contains 8 bits of green (in the high 8 bits) and 8 bits of red (in the low 8 bits). The second pixel contains 8 bits of green (in the high 8 bits) and 8 bits of blue (in the low 8 bits). Together, the two pixels share the red and blue components, while each has a unique green component (G0R0, G1B0, G2R2, etc.). The texture sampler does not normalize the colors when looking up into a pixel shader; they remain in the range of 0.0f to 255.0f. This is true for all programmable pixel shader models. For the fixed function pixel shader, the hardware should normalize to the 0.f to 1.f range and essentially treat it as the YUY2 texture. Hardware that exposes this format must have the PixelShader1xMaxValue member of D3DCAPS9 set to a value capable of handling that range.\r\n"
	),
	KV( 
		D3DFMT_R8G8_B8G8 ,
		"A 16-bit packed RGB format analogous to UYVY (U0Y0, V0Y1, U2Y2, etc.). It requires a pixel pair in order to properly represent the color value. The first pixel in the pair contains 8 bits of green (in the low 8 bits) and 8 bits of red (in the high 8 bits). The second pixel contains 8 bits of green (in the low 8 bits) and 8 bits of blue (in the high 8 bits). Together, the two pixels share the red and blue components, while each has a unique green component (R0G0, B0G1, R2G2, etc.). The texture sampler does not normalize the colors when looking up into a pixel shader; they remain in the range of 0.0f to 255.0f. This is true for all programmable pixel shader models. For the fixed function pixel shader, the hardware should normalize to the 0.f to 1.f range and essentially treat it as the YUY2 texture. Hardware that exposes this format must have PixelShader1xMaxValue member of D3DCAPS9 set to a value capable of handling that range.\r\n"
	),
	KV( 
		D3DFMT_DXT1 ,
		"DXT1 compression texture format.\r\n"
	),
	KV( 
		D3DFMT_DXT2 ,
		"DXT2 compression texture format.\r\n"
	),
	KV( 
		D3DFMT_DXT3 ,
		"DXT3 compression texture format.\r\n"
	),
	KV( 
		D3DFMT_DXT4 ,
		"DXT4 compression texture format.\r\n"
	),
	KV( 
		D3DFMT_DXT5 ,
		"DXT5 compression texture format.\r\n"
	),
	KV( 
		D3DFMT_UYVY ,
		"UYVY format (PC98 compliance).\r\n"
	),
	KV( 
		D3DFMT_YUY2 ,
		"YUY2 format (PC98 compliance).\r\n"
	),

	//Buffer Formats
	KV( 
		D3DFMT_D16_LOCKABLE ,
		"16-bit z-buffer bit depth. This is an application-lockable surface format.\r\n"
	),
	KV( 
		D3DFMT_D32 ,
		"32-bit z-buffer bit depth.\r\n"
	),
	KV( 
		D3DFMT_D15S1 ,
		"z-buffer bit depth where 15 bits are reserved for the depth channel and 1 bit is reserved for the stencil channel.\r\n"		
	),
	KV( 
		D3DFMT_D24S8 ,
		"32-bit z-buffer bit depth using 24 bits for the depth channel and 8 bits for the stencil channel."
	),
	KV( 
		D3DFMT_D24X8 ,
		"z-buffer bit depth using 24 bits for the depth channel."
	),
	KV( 
		D3DFMT_D24X4S4 ,
		"32-bit z-buffer bit depth using 24 bits for the depth channel and 4 bits for the stencil channel."
	),
	KV( 
		D3DFMT_D32F_LOCKABLE ,
		"A lockable format where the depth value is represented as a standard IEEE floating-point number."
	),
	KV( 
		D3DFMT_D24FS8 ,
		"A non-lockable format that contains 24 bits of depth (in a 24-bit floating point format - 20e4) and 8 bits of stencil."
	),
	KV( 
		D3DFMT_D16 ,
		"16-bit z-buffer bit depth.\r\n"
	),
	KV( 
		D3DFMT_VERTEXDATA ,
		"Describes a vertex buffer surface.\r\n"
	),
	KV( 
		D3DFMT_INDEX16 ,
		"16-bit index buffer bit depth.\r\n"
	),
	KV( 
		D3DFMT_INDEX32 ,
		"32-bit index buffer bit depth.\r\n"
	),

	// Floating-Point Formats
	KV( 
		D3DFMT_R16F ,
		"16-bit float format using 16 bits for the red channel.\r\n"
	),
	KV( 
		D3DFMT_G16R16F ,
		"32-bit float format using 16 bits for the red channel and 16 bits for the green channel.\r\n"
	),
	KV( 
		D3DFMT_A16B16G16R16F ,
		"64-bit float format using 16 bits for the each channel (alpha, blue, green, red).\r\n"
	),
	// IEEE Formats
	KV( 
		D3DFMT_R32F ,
		"32-bit float format using 32 bits for the red channel.\r\n"
	),
	KV( 
		D3DFMT_G32R32F ,
		"64-bit float format using 32 bits for the red channel and 32 bits for the green channel.\r\n"
	),
	KV( 
		D3DFMT_A32B32G32R32F ,
		"128-bit float format using 32 bits for the each channel (alpha, blue, green, red).\r\n"
	),
	{ 0 }
};

const Be::VarChooser TriFilterMode[] =
{
    {
        "TRIFILTER_NONE",
        VAL(D3DX_FILTER_NONE),
        "No scaling or filtering will take place. Pixels outside the bounds of the source image are assumed to be transparent black."
    },
    {
        "TRIFILTER_POINT",
        VAL(D3DX_FILTER_POINT),
        "Each destination pixel is computed by sampling the nearest pixel from the source image."
    },
    {
        "TRIFILTER_LINEAR",
        VAL(D3DX_FILTER_LINEAR),
        "Each destination pixel is computed by sampling the four nearest pixels from the source image. This filter works best when the scale on both axes is less than two."
    },
    {
        "TRIFILTER_TRIANGLE",
        VAL(D3DX_FILTER_TRIANGLE),
        "Every pixel in the source image contributes equally to the destination image. This is the slowest of the filters."
    },
    {
        "TRIFILTER_BOX",
        VAL(D3DX_FILTER_BOX),
        "Each pixel is computed by averaging a 2x2(x2) box of pixels from the source image. This filter works only when the dimensions of the destination are half those of the source, as is the case with mipmaps."
    },
    {
        "TRIFILTER_MIRROR_U",
        VAL(D3DX_FILTER_MIRROR_U),
        "Pixels off the edge of the texture on the u-axis should be mirrored, not wrapped."
    },
    {
        "TRIFILTER_MIRROR_V",
        VAL(D3DX_FILTER_MIRROR_V),
        "Pixels off the edge of the texture on the v-axis should be mirrored, not wrapped."
    },
    {
        "TRIFILTER_MIRROR_W",
        VAL(D3DX_FILTER_MIRROR_W),
        "Pixels off the edge of the texture on the w-axis should be mirrored, not wrapped."
    },
    {
        "TRIFILTER_MIRROR",
        VAL(D3DX_FILTER_MIRROR),
        "Specifying this flag is the same as specifying the D3DX_FILTER_MIRROR_U, D3DX_FILTER_MIRROR_V, and D3DX_FILTER_MIRROR_W flags."
    },
    {
        "TRIFILTER_DITHER",
        VAL(D3DX_FILTER_DITHER),
        "The resulting image must be dithered using a 4x4 ordered dither algorithm."
    },
    {
        "TRIFILTER_SRGB_IN",
        VAL(D3DX_FILTER_SRGB_IN),
        "Input data is in sRGB (gamma 2.2) color space."
    },
    {
        "TRIFILTER_SRGB_OUT",
        VAL(D3DX_FILTER_SRGB_OUT),
        "The output data is in sRGB (gamma 2.2) color space."
    },
    {
        "TRIFILTER_SRGB",
        VAL(D3DX_FILTER_SRGB),
        "Same as specifying D3DX_FILTER_SRGB_IN | D3DX_FILTER_SRGB_OUT."
    },
    {0}
};

#endif
