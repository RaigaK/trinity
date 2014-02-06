//////////////////////////////////////////////////////////////////////////
//
// Created: December 2010
// Copyright CCP 2010
//

#include "StdAfx.h"

#if BINK_ENABLED

#include "Tr2Sprite2dBinkTexture.h"
#include "Tr2AtlasTexture.h"
#include "BinkOutputStream.h"

BLUE_DEFINE( Tr2Sprite2dBinkTexture );

const Be::ClassInfo* Tr2Sprite2dBinkTexture::ExposeToBlue()
{
    EXPOSURE_BEGIN( Tr2Sprite2dBinkTexture, "" )
        MAP_INTERFACE( ITr2Sprite2dTexture )
		MAP_INTERFACE( Tr2Sprite2dBinkTexture )
		MAP_INTERFACE( ITr2Updateable )

		MAP_ATTRIBUTE
		(
			"name", 
			m_name, 
			"Name of this object", 
			Be::READWRITE
		)

		MAP_PROPERTY
		(
			"resPath",
			GetResPath,
			SetResPath,
			"Resource path for Bink video"
		)

		MAP_ATTRIBUTE( "resPath_", m_resPath, "", Be::PERSISTONLY	)
		MAP_ATTRIBUTE( "outputChannel",  m_outputChannel,  "", Be::READWRITE )

		MAP_PROPERTY_READONLY
		(
			"duration",
			GetDuration,
			"Duration of video, in seconds"
		)
		
		MAP_ATTRIBUTE
		(
			"srcX", 
			m_srcX, 
			"X-coordinate of top-left of source rectangle for this texture", 
			Be::READWRITE | Be::NOTIFY
		)

		MAP_ATTRIBUTE
		(
			"srcY", 
			m_srcY, 
			"Y-coordinate of top-left of source rectangle for this texture", 
			Be::READWRITE | Be::NOTIFY
		)
		MAP_ATTRIBUTE
		(
			"srcWidth", 
			m_srcWidth, 
			"Width of source rectangle for this texture", 
			Be::READWRITE | Be::NOTIFY
		)

		MAP_ATTRIBUTE
		(
			"srcHeight", 
			m_srcHeight, 
			"Height of source rectangle for this texture", 
			Be::READWRITE | Be::NOTIFY
		)

		MAP_ATTRIBUTE
		(
			"loop",
			m_loop,
			"If true, the video plays in a loop until stopped.",
			Be::READWRITE | Be::NOTIFY
		)

		MAP_PROPERTY_READONLY
		(
			"atlasTexture",
			GetAtlasTexture,
			"Atlas texture held by this texture object"
		)

		MAP_ATTRIBUTE
		(
			"isMuted",
			m_isMuted,
			"Flag indicating whether or not the movie is muted.",
			Be::READ
		)

		MAP_ATTRIBUTE
		(
			"isPaused",
			m_isPaused,
			"Flag indicating whether or not the movie is paused.",
			Be::READ
		)
		
		MAP_ATTRIBUTE
		(
			"videoFps",
			m_videoFps,
			"The fps of the loaded video.",
			Be::READ
		)
		
		MAP_ATTRIBUTE
		(
			"currentFrame",
			m_currentFrame,
			"The frame number of the video. Could be used to play subtites.",
			Be::READ 
		)
		
		MAP_ATTRIBUTE
		(
			"isFinished",
			m_isFinished,
			"Flag indicating whether or not the movie is finished.",
			Be::READ
		)

		MAP_METHOD_AND_WRAP
		( 
			"Play", 
			Play, 
			"Starts the video from paused."
		)
		
		MAP_METHOD_AND_WRAP
		( 
			"Pause", 
			Pause, 
			"Pauses the video."
		)

		MAP_METHOD_AND_WRAP
		( 
			"Rewind", 
			Rewind, 
			"Rewinds the video."
		)

		MAP_METHOD_AND_WRAP
		( 
			"MuteAudio", 
			MuteAudio, 
			"Mutes the audio track 0 of the video"
		)

		MAP_METHOD_AND_WRAP
		( 
			"UnmuteAudio", 
			UnmuteAudio, 
			"Unmutes the audio track 0 of the video"
		)

	EXPOSURE_END()
}

#if BLUE_WITH_PYTHON
static PyObject* PySetDirectSoundPtr( PyObject* module, PyObject* args )
{
	static bool hasSoundBeenSet = false;

	if ( !hasSoundBeenSet )
	{
		//local declarations and arg parsing
		PyObject* pyLong;
		if ( !PyArg_ParseTuple( args, "O", &pyLong ) )
		{
			return NULL;
		}

		void* directSoundPtr = PyLong_AsVoidPtr(pyLong);

		BinkSetSoundSystem( BinkOpenCustomStream, (UINTa) directSoundPtr );
		hasSoundBeenSet = true;
	}

	Py_RETURN_NONE;
}

MAP_FUNCTION( "SetDirectSoundPtr", PySetDirectSoundPtr, "Pass the direct sound pointer from audio2 to trinity before playing any bink audio." );

#endif

#endif
