#pragma once

#ifndef KD_LOG
	#if WITH_EDITOR
		#define KD_LOG 1
	#else
		#define KD_LOG 0
	#endif
#endif


#ifndef KD_GRAPHIC_LOG
	#if KD_LOG
		#define KD_GRAPHIC_LOG 1
	#else
		#define KD_GRAPHIC_LOG 0
	#endif
#endif
