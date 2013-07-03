/************************************************************************
                        mixer.h - Copyright zefiris

Here you can write a license for your code, some comments or any other
information you want to have in your generated code. To to this simply
configure the "headings" directory in uml to point to a directory
where you have your heading files.

or you can just replace the contents of this file with your own.
If you want to do this, this file is located at

/usr/kde/3.5/share/apps/umbrello/headings/heading.h

-->Code Generators searches for heading files based on the file extension
   i.e. it will look for a file name ending in ".h" to include in C++ header
   files, and for a file name ending in ".java" to include in all generated
   java code.
   If you name the file "heading.<extension>", Code Generator will always
   choose this file even if there are other files with the same extension in the
   directory. If you name the file something else, it must be the only one with that
   extension in the directory to guarantee that Code Generator will choose it.

you can use variables in your heading files which are replaced at generation
time. possible variables are : author, date, time, filename and filepath.
just write %variable_name%

This file was generated on Fri Aug 25 2006 at 03:36:12
The original location of this file is 
**************************************************************************/

#ifndef MIXER_H
#define MIXER_H
#include <string>
#include "sound.h"
#include "music.h"

/**
 * Class Mixer
 * The Mixer is used to mix several different sources of sound (from Sound and Music objects) and play them through the soundcard.
 */
class Mixer {
/**
 * Public stuff
 */
public:
    /**
     * Fields
     */
    /**
     * 
     */
    /**
     * Constructors
     */
    /**
     * Empty Constructor
     */
    Mixer ( ) { }
    /**
     * Accessor Methods
     */
    /**
     * Operations
     */
    /**
     * 
     * @param sound A sound to play.
     */
    void playSound (Sound sound);
        
    
    /**
     * Push a music track onto the end of the queue.
     */
    void pushMusic (Music music);
        
    
    /**
     * Clear the music queue.
     */
    void clearQueue ();
        
    
    /**
     * Fast-forward to the next music track in the queue.
     */
    void nextTrack ();
        
    
/**
 * Protected stuff
 */
protected:
    /**
     * Fields
     */
    /**
     * 
     */
    /**
     * Constructors
     */
    /**
     * Accessor Methods
     */
    /**
     * Operations
     */
/**
 * Private stuff
 */
private:
    /**
     * Fields
     */
    /**
     * 
     */
    /**
     * Constructors
     */
    /**
     * Accessor Methods
     */
    /**
     * Operations
     */
};
#endif //MIXER_H

