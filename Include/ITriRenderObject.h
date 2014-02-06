/* 
	*************************************************************************

	ITriRenderObject.h

	Author:    Hilmar Veigar Pétursson
	Created:   Nov. 2000
	OS:        Win32
	Project:   Trinity

	Description:   

		Hemm...


	Dependencies:

		None, whatsoever!

	(c) CCP 2000

	*************************************************************************
*/


#ifndef _ITRIRENDEROBJECT_H_
#define _ITRIRENDEROBJECT_H_

struct ITriDevice;


BLUE_INTERFACE(ITriRenderObject) : public IRoot
{
	// called the owner of the object 
	virtual void ReloadResources() = 0;
	virtual void RebuildCachedData() = 0;

	// used so that calculations for the object
	// state can be kept seperate from the rendering
	virtual void Update(		
		Be::Time time
		) = 0;

	// called to render the object
	virtual bool Render(
		long param1,
		long param2
		) = 0;

	

};

BLUE_INTERFACE(ITriRenderObjectList) : public ITriRenderObject
{
	virtual ITriRenderObject* FindObject(
		const wchar_t* name, 
		bool recursive
		) = 0;
};


#endif

/*

	The IRenderObject Interface is based on a "design pattern" level on stuff seem in 
	various examples from NVIDIA and Microsoft. Microsoft has the most comples "interface"
	where they have two init calls InitDeviceObjects and RestoreDeviceObjects where Trinity
	uses only Prepare (Render handles some of the tasks that are done in RestoreDeviceObjects)
	Trinity then uses only a single shutdown call Invalidate() to clean house D3D uses
	InvalidateDeviceObjects and DeleteDeviceObjects where resources of different cost are
	deleted in each call. Due to Trinity being more devided into classes it only uses 
	a signle call Invalidate()


  	// Initializing and destroying device-dependent objects
	// Desc: Initializes device-dependent objects, including the vertex buffer used
    //       for rendering text and the texture map which stores the font image.
	// Desc: This creates all device-dependent managed objects, such as managed
    //       textures and managed vertex buffers.
	// Desc: Initialize scene objects.
    HRESULT InitDeviceObjects( LPDIRECT3DDEVICE8 pd3dDevice ); //prepare


	// Desc: Restore device-memory objects and state after a device is created or
	//       resized.
	// Desc: Initialize scene objects.
    HRESULT RestoreDeviceObjects();
	// stateblocks vertexbuffers
	// basically device state, as it seams, not objects well state blocks etc. but not 
	// textures

	
	//-----------------------------------------------------------------------------
	// Desc: Destroys all device-dependent objects
	// Desc: Called when the device-dependent objects are about to be lost.
	//-----------------------------------------------------------------------------
    HRESULT InvalidateDeviceObjects();
	// stateblocks vertex buffers, etc. Seams to be all procedurally created data.
	// a more general rule would be all data which is not in D3DPOOL_MANAGED 	

	//-----------------------------------------------------------------------------
	
	// Desc: Destroys all device-dependent objects
	// Desc: Called when the app is exiting, or the device is being changed,
	//       this function deletes any device dependent objects.
	//-----------------------------------------------------------------------------
    HRESULT DeleteDeviceObjects();
	// textures the device it self, etc.
	// everything is released in a way where it has to be read in from a file to be
	// recreated.



*/