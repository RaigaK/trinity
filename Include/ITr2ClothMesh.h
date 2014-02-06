#ifndef ITr2ClothMesh_H
#define ITr2ClothMesh_H

BLUE_INTERFACE( ITr2ClothMesh ) : IRoot
{
	virtual bool Initialize( const class hclBufferDefinition* def, const class hclClothData* clothData, const class hkxMesh* mesh, int section ) = 0;
	virtual void* LockBuffer() = 0;
	virtual void UnlockBuffer() = 0;
};

#endif
