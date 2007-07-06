/* Copyright (C) 2005-2007, Thorvald Natvig <thorvald@natvig.com>

   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions
   are met:

   - Redistributions of source code must retain the above copyright notice,
     this list of conditions and the following disclaimer.
   - Redistributions in binary form must reproduce the above copyright notice,
     this list of conditions and the following disclaimer in the documentation
     and/or other materials provided with the distribution.
   - Neither the name of the Mumble Developers nor the names of its
     contributors may be used to endorse or promote products derived from this
     software without specific prior written permission.

   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
   ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
   LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
   A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE FOUNDATION OR
   CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
   EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
   PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
   PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
   LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
   NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
   SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

#ifndef _DXAUDIOOUTPUT_H
#define _DXAUDIOOUTPUT_H

#include "AudioOutput.h"
#include <dsound.h>

class DXAudioOutput;

class DXAudioOutputPlayer {
	friend class DXAudioOutput;
	protected:
		LPDIRECTSOUNDBUFFER       pDSBOutput;
		LPDIRECTSOUNDNOTIFY8       pDSNotify;
		HANDLE               hNotificationEvent;
		LPDIRECTSOUND3DBUFFER8     pDS3dBuffer;

		DWORD	dwBufferSize;
		DWORD	dwLastWritePos;
		DWORD	dwLastPlayPos;
		DWORD	dwTotalPlayPos;
		int iLastwriteblock;

		DXAudioOutput *dxAudio;
		AudioOutputPlayer *aop;

		bool bPlaying;

		unsigned int iByteSize;
		int iMissingFrames;
		void setupAudioDevice();
	public:
		DXAudioOutputPlayer(DXAudioOutput *, AudioOutputPlayer *);
		~DXAudioOutputPlayer();
		bool playFrames();
};


class DXAudioOutput : public AudioOutput {
	friend class DXAudioOutputPlayer;
	Q_OBJECT
	protected:
		LPDIRECTSOUND8             pDS;
		LPDIRECTSOUNDBUFFER       pDSBPrimary;
		LPDIRECTSOUND3DLISTENER8   p3DListener;
		HANDLE               hNotificationEvent;

		QHash<AudioOutputPlayer *, DXAudioOutputPlayer *> qhPlayers;

		virtual void newPlayer(AudioOutputPlayer *);
		virtual void removeBuffer(AudioOutputPlayer *);
		void updateListener();

		bool bRebuild;
		bool bOk;
	public:
		DXAudioOutput();
		~DXAudioOutput();
		void run();
};

#else
class DXAudioOutput;
#endif
