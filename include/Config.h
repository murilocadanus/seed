#ifndef __CONFIG_H__
#define __CONFIG_H__

#if defined(SEED_BUILD)
	#if !defined(SEED_USE_COMMERCIAL)
		#define SEED_BUILD_LGPL
		#define SEED_LICENSE "LGPL"
	#else
		#define SEED_LICENSE "Commercial"
	#endif // SEED_BUILD
#else
	#if !defined(SEED_USE_COMMERCIAL)
		#define SEED_USE_LGPL 1
		#define SEED_LICENSE "LGPL"
	#else
		#define SEED_LICENSE "Commercial"
	#endif
#endif

#define DANNY	"Danny Angelo Carminati Grein"
#define PATUTI	"Everton Fernando Patitucci da Silva"
#define RAPTOR	"Rafael Eduardo Gonchor"

#define SEED_TAG					"[Seed] "
#define SEED_VERSION_MINOR			1			// Developer version (features, fixes)
#define SEED_VERSION_MIDDLE			1			// Client version
#define SEED_VERSION_MAJOR			0			// Release version (final trunk)
#define SEED_VERSION_STRING			"%d.%d.%d"	//"0.1.1"
#define SEED_NAME					"Seed SDK"
#define SEED_COPYRIGHT				"Copyright (c) 2008-2009 Danny Angelo Carminati Grein\nCopyright (c) 2009 TechFront Studios"
#define SEED_AUTHORS				"Authors:\n\t" DANNY "\n\t" PATUTI "\n\t" RAPTOR

#define SEED_MESSAGE		SEED_NAME " " SEED_VERSION_STRING " [" SEED_PLATFORM_NAME " " SEED_TYPE " " SEED_LICENSE "]\n" SEED_COPYRIGHT "\n" SEED_AUTHORS

#if defined(DEBUG)
	#define SEED_TYPE "Debug"
#else
	#define SEED_TYPE "Release"
#endif // DEBUG

#if defined(BUILD_IOS)
	#define SEED_PLATFORM_NAME "iPhone"
#elif defined(BUILD_SDL)
	#define SEED_PLATFORM_NAME "SDL"
#elif defined(BUILD_QT)
	#define SEED_PLATFORM_NAME "Qt"
#endif // BUILD_IOS

//================================================================================
// FEATURES CAPPING
//================================================================================
#define SEED_USE_JSON						1
#define SEED_USE_THEORA						0
#define SEED_ENABLE_DEPTH_TEST				0

/*
Transformable objects have only one pivot for calculating the object position, scale and rotation.
By enabling this, the rotation and scale will be separated from the position pivot but not configurable (defaults to the center of the frame).
*/
#define SEED_USE_ROTATION_PIVOT				0

/*
Transformables objects give you the freedom to change the pivot used for calculating the object position, scale and rotation.
This option, if enabled, will force the pivot to the center of the object (default, but you are free to change)
If this option is disabled, you'll have the default pivot in the upper-left corner of the image, causing objects to rotate in a unexpected way.
Disabling this and enabling SEED_USE_ROTATION_PIVOT will let you use the upper-left corner as position pivot while using the object center as
scale and rotation pivot.
*/
#define SEED_DEFAULT_PIVOT_CENTERED			1

/*
The size of the music buffer for streaming from hard disk on platforms that support it (SDL).
*/
#define SEED_MUSIC_STREAMING_BUFFER_SIZE	(1024 * 40)

/*
Toggle between instancing Singleton classes in the (0) Stack or in the (1) Heap
*/
#define SEED_SINGLETON_HEAP					0

/*
*/
#define SEED_MAX_PRIORITY					1000000

/*
Maximum size of a folder name string
*/
#define SEED_MAX_FOLDER_SIZE				4096

/*
Use wide char paths
*/
#if defined(WIN32)
#define SEED_PATH_WIDE						1 // For windows this is required
#else
#define SEED_PATH_WIDE						0
#endif


//================================================================================
// FEATURES SPECIFIC SETTINGS
//================================================================================


//================================================================================
// DEBUGGING DEFINES
//================================================================================
#if defined(DEBUG)
	#define SEED_LOG_RESOURCEMANAGER		1
#endif // DEBUG

#endif // __CONFIG_H__
