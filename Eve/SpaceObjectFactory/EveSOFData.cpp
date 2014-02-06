////////////////////////////////////////////////////////////
//
//    Created:   August 2013
//    Copyright: CCP 2013
//
#include "StdAfx.h"
#include "EveSOFData.h"

// --------------------------------------------------------------------------------
// Description:
//   x
// --------------------------------------------------------------------------------

EveSOFData::EveSOFData( IRoot* lockobj ) :
	PARENTLOCK( m_hull ),
	PARENTLOCK( m_faction ),
	PARENTLOCK( m_race )
{}
EveSOFData::~EveSOFData()
{}


EveSOFDataFactionParameter::EveSOFDataFactionParameter( IRoot* lockobj )
{}


EveSOFDataFactionHullArea::EveSOFDataFactionHullArea( IRoot* lockobj ) :
	PARENTLOCK( m_parameters )
{}


EveSOFDataTexture::EveSOFDataTexture( IRoot* lockobj )
{}


EveSOFDataFaction::EveSOFDataFaction( IRoot* lockobj ) :
	PARENTLOCK( m_textureResPathInsert ),
	PARENTLOCK( m_hullAreas ),
	PARENTLOCK( m_spriteSets )
{}


EveSOFDataBooster::EveSOFDataBooster( IRoot* lockobj ) :
	m_color( 0.f, 0.f, 0.f, 0.f ),
	m_scale( 1.f, 1.f, 1.f, 1.f ),
	m_glowScale( 1.f ),
	m_glowColor( 0.f, 0.f, 0.f, 0.f ),
	m_haloColor( 0.f, 0.f, 0.f, 0.f ),
	m_haloScaleX( 1.f ),
	m_haloScaleY( 1.f ),
	m_symHaloScale( 1.f ),
	m_trailColor( 0.f, 0.f, 0.f, 0.f ),
	m_trailSize( 0.f, 0.f, 0.f, 0.f )
{}


EveSOFDataFactionTexture::EveSOFDataFactionTexture( IRoot* lockobj )
{}


EveSOFDataHull::EveSOFDataHull( IRoot* lockobj ) :
	PARENTLOCK( m_spriteSets ),
	PARENTLOCK( m_spotlightSets ),
	PARENTLOCK( m_planeSets ),
	PARENTLOCK( m_opaqueAreas ),
	m_boundingSphere( 0.f, 0.f, 0.f, 0.f )
{}


EveSOFDataRace::EveSOFDataRace( IRoot* lockobj )
{}


EveSOFDataHullArea::EveSOFDataHullArea( IRoot* lockobj ) :
	PARENTLOCK( m_textures )
{}


EveSOFDataHullSpotlightSet::EveSOFDataHullSpotlightSet( IRoot* lockobj ) :
	PARENTLOCK( m_items ),
	m_skinned( false )
{}


EveSOFDataHullSpotlightSetItem::EveSOFDataHullSpotlightSetItem( IRoot* lockobj ) :
	m_boneIndex( 0 ), m_groupIndex( -1 ),
	m_boosterGainInfluence( false ),
	m_spriteScale( 1.f, 1.f, 1.f )
{
	D3DXMatrixIdentity( &m_transform );
}


EveSOFDataHullPlaneSet::EveSOFDataHullPlaneSet( IRoot* lockobj ) :
	PARENTLOCK( m_items ),
	m_skinned( false ),
	m_planeData( 1.f, 0.f, 0.f, 0.f )
{}


EveSOFDataHullPlaneSetItem::EveSOFDataHullPlaneSetItem( IRoot* lockobj ) :
	m_position( 0.f, 0.f, 0.f ),
	m_rotation( 0.f, 0.f, 0.f, 1.f ),
	m_scaling( 1.f, 1.f, 1.f ),
	m_layer1Transform( 0.f, 0.f, 0.f, 0.f ),
	m_layer2Transform( 0.f, 0.f, 0.f, 0.f ),
	m_layer1Scroll( 0.f, 0.f, 0.f, 0.f ),
	m_layer2Scroll( 0.f, 0.f, 0.f, 0.f )
{
}


EveSOFDataHullSpriteSet::EveSOFDataHullSpriteSet( IRoot* lockobj ) :
	PARENTLOCK( m_items ),
	m_skinned( false )
{}


EveSOFDataHullSpriteSetItem::EveSOFDataHullSpriteSetItem( IRoot* lockobj ) :
	m_position( 0.f, 0.f, 0.f ),
	m_blinkRate( 0.1f ), m_blinkPhase( 0.0f ), m_minScale( 1.f ), m_maxScale( 10.f ), m_falloff( 1.f ),
	m_boneIndex( 0 ), m_groupIndex( -1 )
{}


EveSOFDataFactionSpriteSet::EveSOFDataFactionSpriteSet( IRoot* lockobj ) :
	m_groupIndex( -1 ),
	m_color( 0.f, 0.f, 0.f, 0.f )
{}

EveSOFDataHullBooster::EveSOFDataHullBooster( IRoot* lockobj ) :
	PARENTLOCK( m_items ),
	m_alwaysOn( false ),
	m_hasTrails( true )
{}


EveSOFDataHullBoosterItem::EveSOFDataHullBoosterItem( IRoot* lockobj ) :
	m_functionality( 0.f, 0.f, 0.f, 0.f )
{
	D3DXMatrixIdentity( &m_transform );
}


