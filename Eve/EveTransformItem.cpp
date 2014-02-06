#include "StdAfx.h"
#include "EveTransformItem.h"
#include "TriValueBinding.h"

EveTransformItem::EveTransformItem( IRoot* lockobj /*= NULL */ ):
	PARENTLOCK( m_children ),
	m_modifer( EVE_TOM_NONE ),
	m_parentArray( nullptr ),
	m_translationBinding( nullptr ),
	m_rotationBinding( nullptr ),
	m_scaleBinding( nullptr )
{

}

EveTransformItem::~EveTransformItem()
{

}

void EveTransformItem::RegisterBinding( TriValueBinding* vb )
{
	const std::string& destinationAttribute = vb->GetDestinationAttributeName();

	if( destinationAttribute.find("translation") == 0 )
	{
		CCP_ASSERT( m_translationBinding == nullptr );
		m_translationBinding = vb;
	}
	else if( destinationAttribute.find("rotation") == 0 )
	{
		CCP_ASSERT( m_rotationBinding == nullptr );
		m_rotationBinding = vb;
	}
	else if( destinationAttribute.find("scale") == 0 )
	{
		CCP_ASSERT( m_scaleBinding == nullptr );
		m_scaleBinding = vb;
	}
}

void EveTransformItem::UnregisterBinding( TriValueBinding* vb )
{
	const std::string& destinationAttribute = vb->GetDestinationAttributeName();

	if( destinationAttribute.find("translation") == 0 )
	{
		m_translationBinding = nullptr;
	}
	else if( destinationAttribute.find("rotation") == 0 )
	{
		m_rotationBinding = nullptr;
	}
	else if( destinationAttribute.find("scale") == 0 )
	{
		m_scaleBinding = nullptr;
	}
}

void EveTransformItem::SetTransformArray( EveTransformArray* parent )
{
	m_parentArray = parent;
	for( auto i = m_children.begin(); i != m_children.end(); ++i )
	{
		(*i)->SetTransformArray( parent );
	}
}

void EveTransformItem::OnListModified( long event, 
												 ssize_t key, 
												 ssize_t key2, 
												 IRoot* value, 
												 const IList* theList )
{

	if( (event & BELIST_LOADING) == 0  )
	{
		switch( event & BELIST_EVENTMASK )
		{
		case BELIST_INSERTED:
			{
				EveTransformItemPtr object( BlueCastPtr( value ) );
				if( object )
				{
					object->SetTransformArray( m_parentArray );
				}
			}
			break;
		case BELIST_REMOVED:
			{
				//	If an entry is being removed from the statics list, ensure that it has its parent system cleared
				EveTransformItemPtr object( BlueCastPtr( value ) );
				if( object )
				{
					object->SetTransformArray( nullptr );
				}
			}
			break;
		case BELIST_SWAPPED:
		case BELIST_MOVED:
			//				rebuildUmbraCell();
			break;
		}
	}
}

bool EveTransformItem::HasBindings() const
{
	return m_translationBinding || m_rotationBinding || m_scaleBinding;
}

void EveTransformItem::SetTranslationBindingDestination( float* destination )
{
	if( m_translationBinding )
	{
		m_translationBinding->RerouteDestination( destination );
	}
}

void EveTransformItem::SetRotationBindingDestination( float* destination )
{
	if( m_rotationBinding )
	{
		m_rotationBinding->RerouteDestination( destination );
	}
}

void EveTransformItem::SetScaleBindingDestination( float* destination )
{
	if( m_scaleBinding )
	{
		m_scaleBinding->RerouteDestination( destination );
	}
}