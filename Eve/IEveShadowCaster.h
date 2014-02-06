#ifndef IEveShadowCaster_h
#define IEveShadowCaster_h



struct ITr2Renderable;
class TriFrustumOrtho;

BLUE_INTERFACE( IEveShadowCaster ) : public IRoot
{
	// Warning: GetRenderablesCastingShadow can be called on different threads, so it needs to be thread-safe.
	virtual bool GetRenderablesCastingShadow( bool isSelf, const TriFrustumOrtho& frustum, std::vector<ITr2Renderable*>& renderables ) = 0;
	virtual bool IsShadowReceiveEnabled() = 0;
};

#endif
