////////////////////////////////////////////////////////////
//
//    Created:   August 2013
//    Copyright: CCP 2013
//
#pragma once
#ifndef EveSOFData_H
#define EveSOFData_H

// --------------------------------------------------------------------------------
// All data storage classes for per-hull data
// --------------------------------------------------------------------------------

BLUE_CLASS( EveSOFDataHullSpotlightSetItem ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataHullSpotlightSetItem( IRoot* lockobj = NULL );
	~EveSOFDataHullSpotlightSetItem() {}

	// per-hull data of a spotlightset
	Matrix m_transform;
	int m_boneIndex, m_groupIndex;
	bool m_boosterGainInfluence;
	Vector3 m_spriteScale;
};
TYPEDEF_BLUECLASS( EveSOFDataHullSpotlightSetItem );
BLUE_DECLARE_VECTOR( EveSOFDataHullSpotlightSetItem );


BLUE_CLASS( EveSOFDataHullSpotlightSet ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataHullSpotlightSet( IRoot* lockobj = NULL );
	~EveSOFDataHullSpotlightSet() {}

	// data
	bool m_skinned;
	float m_zOffset;
	std::string m_glowTextureResPath;
	std::string m_coneTextureResPath;
	// items
	PEveSOFDataHullSpotlightSetItemVector m_items;
};
TYPEDEF_BLUECLASS( EveSOFDataHullSpotlightSet );
BLUE_DECLARE_VECTOR( EveSOFDataHullSpotlightSet );


BLUE_CLASS( EveSOFDataHullPlaneSetItem ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataHullPlaneSetItem( IRoot* lockobj = NULL );
	~EveSOFDataHullPlaneSetItem() {}

	// per-hull data of a planeset
	Vector3 m_position;
	Vector3 m_scaling;
	Quaternion m_rotation;
	Vector4 m_layer1Transform, m_layer2Transform, m_layer1Scroll, m_layer2Scroll;
	int m_boneIndex;
};
TYPEDEF_BLUECLASS( EveSOFDataHullPlaneSetItem );
BLUE_DECLARE_VECTOR( EveSOFDataHullPlaneSetItem );


BLUE_CLASS( EveSOFDataHullPlaneSet ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataHullPlaneSet( IRoot* lockobj = NULL );
	~EveSOFDataHullPlaneSet() {}

	// data
	bool m_skinned;
	std::string m_layer1MapResPath;
	std::string m_layer2MapResPath;
	std::string m_maskMapResPath;
	Vector4 m_planeData;
	// items
	PEveSOFDataHullPlaneSetItemVector m_items;
};
TYPEDEF_BLUECLASS( EveSOFDataHullPlaneSet );
BLUE_DECLARE_VECTOR( EveSOFDataHullPlaneSet );


BLUE_CLASS( EveSOFDataHullSpriteSetItem ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataHullSpriteSetItem( IRoot* lockobj = NULL );
	~EveSOFDataHullSpriteSetItem() {}

	// per-hull data of a spriteset
	Vector3 m_position;
	float m_blinkRate, m_blinkPhase, m_minScale, m_maxScale, m_falloff;
	int m_boneIndex, m_groupIndex;
};
TYPEDEF_BLUECLASS( EveSOFDataHullSpriteSetItem );
BLUE_DECLARE_VECTOR( EveSOFDataHullSpriteSetItem );


BLUE_CLASS( EveSOFDataHullSpriteSet ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataHullSpriteSet( IRoot* lockobj = NULL );
	~EveSOFDataHullSpriteSet() {}

	// animated?
	bool m_skinned;
	// items
	PEveSOFDataHullSpriteSetItemVector m_items;
};
TYPEDEF_BLUECLASS( EveSOFDataHullSpriteSet );
BLUE_DECLARE_VECTOR( EveSOFDataHullSpriteSet );


BLUE_CLASS( EveSOFDataHullBoosterItem ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataHullBoosterItem( IRoot* lockobj = NULL );
	~EveSOFDataHullBoosterItem() {}

	// per-hull data of a booster
	Matrix m_transform;
	Vector4 m_functionality;
};
TYPEDEF_BLUECLASS( EveSOFDataHullBoosterItem );
BLUE_DECLARE_VECTOR( EveSOFDataHullBoosterItem );


BLUE_CLASS( EveSOFDataHullBooster ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataHullBooster( IRoot* lockobj = NULL );
	~EveSOFDataHullBooster() {}

	// per-hull data of a booster
	bool m_alwaysOn, m_hasTrails;
	std::string m_soundName;
	PEveSOFDataHullBoosterItemVector m_items;
};
TYPEDEF_BLUECLASS( EveSOFDataHullBooster );
BLUE_DECLARE_VECTOR( EveSOFDataHullBooster );


BLUE_CLASS( EveSOFDataTexture ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataTexture( IRoot* lockobj = NULL );
	~EveSOFDataTexture() {}

	// data
	std::string m_resFilePath;
	std::string m_name;
};
TYPEDEF_BLUECLASS( EveSOFDataTexture );
BLUE_DECLARE_VECTOR( EveSOFDataTexture );


BLUE_CLASS( EveSOFDataHullArea ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataHullArea( IRoot* lockobj = NULL );
	~EveSOFDataHullArea() {}

	// data
	unsigned int m_index;
	std::string m_name;
	std::string m_shaderPath;
	PEveSOFDataTextureVector m_textures;
};
TYPEDEF_BLUECLASS( EveSOFDataHullArea );
BLUE_DECLARE_VECTOR( EveSOFDataHullArea );


BLUE_CLASS( EveSOFDataHull ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataHull( IRoot* lockobj = NULL );
	~EveSOFDataHull() {}

	// hull name
	std::string m_name;

	// geometry
	std::string m_geometryResFilePath;
	Vector4 m_boundingSphere;

	// materials
	PEveSOFDataHullAreaVector m_opaqueAreas;

	// effects on ship
	PEveSOFDataHullSpriteSetVector m_spriteSets;
	PEveSOFDataHullSpotlightSetVector m_spotlightSets;
	PEveSOFDataHullPlaneSetVector m_planeSets;

	// boosters
	EveSOFDataHullBoosterPtr m_booster;
};
TYPEDEF_BLUECLASS( EveSOFDataHull );
BLUE_DECLARE_VECTOR( EveSOFDataHull );




// --------------------------------------------------------------------------------
// All data storage classes for per-faction data
// --------------------------------------------------------------------------------

BLUE_CLASS( EveSOFDataFactionTexture ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataFactionTexture( IRoot* lockobj = NULL );
	~EveSOFDataFactionTexture() {}

	// data
	std::string m_name;
	std::string m_resPathInsert;
};
TYPEDEF_BLUECLASS( EveSOFDataFactionTexture );
BLUE_DECLARE_VECTOR( EveSOFDataFactionTexture );


BLUE_CLASS( EveSOFDataFactionSpriteSet ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataFactionSpriteSet( IRoot* lockobj = NULL );
	~EveSOFDataFactionSpriteSet() {}

	// per-faction data of a spriteset
	int m_groupIndex;
	Color m_color;
};
TYPEDEF_BLUECLASS( EveSOFDataFactionSpriteSet );
BLUE_DECLARE_VECTOR( EveSOFDataFactionSpriteSet );


BLUE_CLASS( EveSOFDataFactionParameter ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataFactionParameter( IRoot* lockobj = NULL );
	~EveSOFDataFactionParameter() {}

	// simple shader parameter
	std::string m_name;
	Vector4 m_value;
};
TYPEDEF_BLUECLASS( EveSOFDataFactionParameter );
BLUE_DECLARE_VECTOR( EveSOFDataFactionParameter );


BLUE_CLASS( EveSOFDataFactionHullArea ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataFactionHullArea( IRoot* lockobj = NULL );
	~EveSOFDataFactionHullArea() {}

	// designation
	std::string m_name;
	// list of params
	PEveSOFDataFactionParameterVector m_parameters;
};
TYPEDEF_BLUECLASS( EveSOFDataFactionHullArea );
BLUE_DECLARE_VECTOR( EveSOFDataFactionHullArea );


BLUE_CLASS( EveSOFDataBooster ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataBooster( IRoot* lockobj = NULL );
	~EveSOFDataBooster() {}

	// data
	float m_glowScale, m_symHaloScale, m_haloScaleX, m_haloScaleY;
	Color m_color, m_glowColor, m_haloColor, m_trailColor;
	std::string m_textureResPath;
	Vector4 m_trailSize, m_scale;
	std::string m_soundName;
};
TYPEDEF_BLUECLASS( EveSOFDataBooster );


BLUE_CLASS( EveSOFDataFaction ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataFaction( IRoot* lockobj = NULL );
	~EveSOFDataFaction() {}

	// hull name
	std::string m_name;

	// data
	PEveSOFDataFactionTextureVector m_textureResPathInsert;
	PEveSOFDataFactionHullAreaVector m_hullAreas;
	PEveSOFDataFactionSpriteSetVector m_spriteSets;
};
TYPEDEF_BLUECLASS( EveSOFDataFaction );
BLUE_DECLARE_VECTOR( EveSOFDataFaction );


BLUE_CLASS( EveSOFDataRace ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFDataRace( IRoot* lockobj = NULL );
	~EveSOFDataRace() {}

	// race name
	std::string m_name;

	// data
	EveSOFDataBoosterPtr m_booster;
};
TYPEDEF_BLUECLASS( EveSOFDataRace );
BLUE_DECLARE_VECTOR( EveSOFDataRace );


BLUE_CLASS( EveSOFData ) :
	public IRoot
{
public:
	EXPOSE_TO_BLUE();
	EveSOFData( IRoot* lockobj = NULL );
	~EveSOFData();

	// hull data
	PEveSOFDataHullVector m_hull;
	// faction data
	PEveSOFDataFactionVector m_faction;
	// race data
	PEveSOFDataRaceVector m_race;
};
TYPEDEF_BLUECLASS( EveSOFData );



#endif // EveSOFData_H