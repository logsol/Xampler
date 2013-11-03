/*
  ==============================================================================

    Application.h
    Created: 3 Nov 2013 11:12:39pm
    Author:  Karl Pannek

  ==============================================================================
*/

#ifndef APPLICATION_H_INCLUDED
#define APPLICATION_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"
#include "SampleDisplayComponent.h"

//==============================================================================
/*
*/
class Application    : public Component
{
public:
    Application();
    ~Application();

    void paint (Graphics&);
    void resized();
    void loadFile(const File& file);
    void loadFileIntoTransport (const File& audioFile);
    
private:
    AudioDeviceManager deviceManager;
    AudioFormatManager formatManager;
    
    TimeSliceThread thread;
    
    AudioSourcePlayer audioSourcePlayer;
    AudioTransportSource transportSource;
    ScopedPointer<AudioFormatReaderSource> currentAudioFileSource;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Application)
};


#endif  // APPLICATION_H_INCLUDED
