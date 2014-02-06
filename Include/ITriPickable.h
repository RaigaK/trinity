#ifndef ITRIPICKABLE_H
#define ITRIPICKABLE_H

BLUE_INTERFACE(ITriPickable) : public IRoot
{
	// Returns true if ray starting at 's' with direction 'd' intersects object, otherwise false.
	// If 'pos' is non-null, position of intersection is returned in 'pos'.
	// If 'data' is non-null, extra data (such as area within object) is returned in 'data'.
	virtual bool RayIntersects( Vector3* pos, ITriRenderObject** data, const Vector3 &s, const Vector3 &d ) = 0;
	
	// Render the object into a colorbuffer. Use the top 16 bits from the given id - if object contains areas, use bottom 16 bits to
	// identify areas. 
	virtual bool RenderForPicking( int id, bool separateAreas ) = 0;

	virtual unsigned int GetAreaCount() = 0;
	virtual IRoot* GetArea( unsigned int ix );
};

#endif