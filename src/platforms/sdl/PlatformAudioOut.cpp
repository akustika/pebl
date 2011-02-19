//* -*- mode:C++; tab-width:4; c-basic-offset:4; indent-tabs-mode:nil -*- */
/////////////////////////////////////////////////////////////////////////////////
//    Name:       src/platforms/sdl/PlatformAudioOut.cpp
//    Purpose:    Contains platform-specific audio playing routines
//    Author:     Shane T. Mueller, Ph.D.
//    Copyright:  (c) 2003-2011 Shane T. Mueller <smueller@obereed.net>
//    License:    GPL 2
//
//
//
//     This file is part of the PEBL project.
//
//    PEBL is free software; you can redistribute it and/or modify
//    it under the terms of the GNU General Public License as published by
//    the Free Software Foundation; either version 2 of the License, or
//    (at your option) any later version.
//
//    PEBL is distributed in the hope that it will be useful,
//    but WITHOUT ANY WARRANTY; without even the implied warranty of
//    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//    GNU General Public License for more details.
//
//    You should have received a copy of the GNU General Public License
//    along with PEBL; if not, write to the Free Software
//    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
////////////////////////////////////////////////////////////////////////////////

#include "PlatformAudioOut.h"
#include "../../devices/PAudioOut.h"

#include "../../utility/PEBLPath.h"
#include "../../utility/PError.h"
#include "../../base/Evaluator.h"

#include "SDL/SDL.h"
#include "SDL/SDL_audio.h"



void PlayCallBack(void * dummy, Uint8 * stream, int len);

//initiate static data for callback.
extern AudioInfo *gWaveStream=NULL;


using std::string;
using std::cerr;
using std::cout;
using std::endl;

PlatformAudioOut::PlatformAudioOut():
    PEBLObjectBase(CDT_AUDIOOUT)
{
}



PlatformAudioOut::PlatformAudioOut(const string &  soundfilename):
    PEBLObjectBase(CDT_AUDIOOUT)
{

    //Check to see if we can find the sound file; if not, call everything off.
    string mFilename = Evaluator::gPath.FindFile(soundfilename);

    if(mFilename == "")
        PError::SignalFatalError(string("Unable to find sound file [")  + soundfilename + string("]."));

    
    LoadSoundFile(mFilename.c_str());
    Initialize();    
}


PlatformAudioOut::~PlatformAudioOut()
{
    SDL_FreeWAV(mWave.audio);

}


bool PlatformAudioOut::LoadSoundFile(const string & soundfilename)
{
    //Check to see if we can find the sound file; if not, call everything off.
    mFilename = Evaluator::gPath.FindFile(soundfilename);

    if(mFilename == "")
        PError::SignalFatalError(string("Unable to find sound file [")  + soundfilename + string("]."));

 
	/* Load the wave file into memory */
	if ( SDL_LoadWAV(mFilename.c_str(), &mWave.spec, &mWave.audio, &mWave.audiolen) == NULL )
        {
			std::cerr << "Couldn't load " << mFileName << ": " << SDL_GetError() << std::endl;
            return false;
        }

    cerr << "------------------------------------\n";
    cerr << "Loading Sound File.  Specs:\n";
    cerr << "Frequency:   [" << mWave.spec.freq << "]\n";
    cerr << "Format:      [" << mWave.spec.format << "]\n";
    cerr << "Channels:    [" << mWave.spec.channels << "]\n";
    cerr << "Silence:     [" << mWave.spec.silence  << "]\n";
    cerr << "Samples:     [" << mWave.spec.samples  << "]\n";
    cerr << "Size:        [" << mWave.spec.size     << "]\n";
    cerr << "------------------------------------\n";
    mLoaded = true;


    mWave.name = mFilename.c_str();
    mWave.spec.callback = PlayCallBack;
    mWave.spec.userdata = &mWave;

    //Set the global playback wave to the current wave.
    gWaveStream = &mWave;


    return true;

}


//This must be called after the audio is initialized but before it can
//be played.  It actually opens the audio device for playing.
bool PlatformAudioOut::Initialize()
{	
    
    if (mLoaded &&  SDL_OpenAudio(&mWave.spec, NULL) < 0 ) {
		fprintf(stderr, "Couldn't open audio: %s\n", SDL_GetError());
        return false;
	}
    
    //Reset the position to the beginning.
    mWave.audiopos = 0;

    return true;
}

//  This plays the sound using the callback mixer function (in the background)
//
bool PlatformAudioOut::Play()
{

    SDL_LockAudio();
    mWave.audiopos = 0;
    gWaveStream = &mWave;
    SDL_UnlockAudio();

    //    Initialize();

    SDL_PauseAudio(0);
    
    return true;
}


//This will play the file, not returning until it is complete.
//Do not count on immediate return, as the function goes to sleep
bool PlatformAudioOut::PlayForeground()
{

    

    SDL_LockAudio();

    mWave.audiopos = 0;
    gWaveStream = &mWave;

    SDL_UnlockAudio();



    SDL_PauseAudio(0);
    while(SDL_GetAudioStatus() == SDL_AUDIO_PLAYING)
        {
            //Wait at least 10 ms before checking again.
            SDL_Delay(10);
            //cout << "---------- playing    ["<<SDL_GetTicks() << endl;
        }

    SDL_PauseAudio(1);
    return true;

}

bool PlatformAudioOut::Stop()
{
    SDL_PauseAudio(1);
    //Set the audio stream back to the beginning.
    //SDL_CloseAudio();
    mWave.audiopos=0;

    return true;
}



void PlayCallBack(void * udata, Uint8 * stream, int len)
{


    //    cerr << "Callback Called\n" <<endl;
    Uint8 * waveptr;
    int waveleft;

    //Cast udata to a proper form--this is dangerous and nasty.
    AudioInfo * wave = gWaveStream;//(AudioInfo*)(udata);


    //Put pointer at the proper place in the buffer.
    waveptr = wave->audio + wave->audiopos;
    waveleft = wave->audiolen - wave->audiopos;

    //   cerr << "waveleft: " <<  waveleft << "  len:" << len << endl;
    if(waveleft >= len)
        {
            SDL_MixAudio(stream, waveptr, len, SDL_MIX_MAXVOLUME);
            wave->audiopos += len;
            
        }
    else
        {
            //This plays the rest of the file and stops playing.
            SDL_MixAudio(stream, waveptr, waveleft, SDL_MIX_MAXVOLUME);
            wave->audiopos += waveleft;
            SDL_PauseAudio(1);
            wave->audiopos=0;  //Reset it back to the beginning.
            
        }
    
}
