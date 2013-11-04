/*
  ==============================================================================

    Application.cpp
    Created: 3 Nov 2013 11:12:39pm
    Author:  Karl Pannek

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "Application.h"

//==============================================================================
Application::Application()
    : thread ("audio file preview")
{
    setSize (700, 400);
    
    deviceManager.initialise (0, 2, 0, true);
    formatManager.registerBasicFormats();
    thread.startThread (3);
    
    deviceManager.addAudioCallback (&audioSourcePlayer);
    audioSourcePlayer.setSource (&transportSource);
    
    sampleDisplay = new SampleDisplayComponent(formatManager, transportSource);
    sampleDisplay->setBounds(10, 10, getWidth()-20, 100);
    addAndMakeVisible(sampleDisplay);
    
    File myFile("/Volumes/Hazel/Users/karlp/Arbeit/Samples/Rises/Superdown.wav");
    loadFile(myFile);
    
    transportSource.setPosition (0);
    transportSource.start();
    
}

Application::~Application()
{
    deleteAllChildren();
    transportSource.setSource (nullptr);
    audioSourcePlayer.setSource (nullptr);
    deviceManager.removeAudioCallback (&audioSourcePlayer);
}

void Application::paint (Graphics& g)
{
    g.fillAll (Colour (0xff272727));
}

void Application::resized()
{
}

void Application::loadFile (const File& file)
{
    loadFileIntoTransport (file);
    sampleDisplay->setFile(file);
}

void Application::loadFileIntoTransport (const File& audioFile)
{
    // unload the previous file source and delete it..
    transportSource.stop();
    transportSource.setSource (nullptr);
    currentAudioFileSource = nullptr;
    
    AudioFormatReader* reader = formatManager.createReaderFor (audioFile);
    
    if (reader != nullptr)
    {
        currentAudioFileSource = new AudioFormatReaderSource (reader, true);
        
        // ..and plug it into our transport source
        transportSource.setSource (currentAudioFileSource,
                                   32768, // tells it to buffer this many samples ahead
                                   &thread, // this is the background thread to use for reading-ahead
                                   reader->sampleRate);
    }
}