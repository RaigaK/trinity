////////////////////////////////////////////////////////////
//
//    Created:   May 2019
//    Copyright: CCP 2019
//

#pragma once


BLUE_INTERFACE( ITr2ControllerOwner ) : public IRoot
{
	// Called when we need to set a controller variable
	virtual void SetControllerVariable( const char* name, float value ) {}
	// Called when we need a value of a controller variable
	virtual bool GetControllerValueByName( const char* name, float& out )
	{
		return false;
	}
	// Called when we need to handle a controller variable
	virtual void HandleControllerEvent( const char* name ) {}
	// Called when we want to start all the controllers
	virtual void StartControllers() {}
	virtual void GetBindingRoots( std::unordered_map<std::string, IRoot*>& variables ) 
	{
		variables["Owner"] = this->GetRootObject();
	};
};

BLUE_DECLARE_IVECTOR( ITr2ControllerOwner );