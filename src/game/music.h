/************************************************************************
                        music.h - Copyright zefiris

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

#ifndef MUSIC_H
#define MUSIC_H
#include <string>

/**
 * Class Music
 * A Music contains a music track which can be played through a Mixer.
 */
class Music {
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
    Music ( ) { }
    /**
     * Accessor Methods
     */
    /**
     * Operations
     */
    /**
     * 
     * @param path The file to load the music from.
     */
    static Music load (string path);
        
    
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
#endif //MUSIC_H

