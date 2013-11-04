/*
  ==============================================================================

    SampleDisplayComponent.cpp
    Created: 3 Nov 2013 9:40:47pm
    Author:  Karl Pannek

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SampleDisplayComponent.h"
#include "Application.h"

//==============================================================================



SampleDisplayComponent::SampleDisplayComponent (AudioFormatManager& formatManager,
                                                AudioTransportSource& transportSource_)
    : transportSource (transportSource_),
      thumbnailCache (5),
      thumbnail (512, formatManager, thumbnailCache)
{
    startTime = endTime = 0;
    thumbnail.addChangeListener (this);
    
    currentPositionMarker = new DrawableRectangle();
    currentPositionMarker->setFill (Colours::purple.withAlpha (0.7f));
    addAndMakeVisible (currentPositionMarker);

    zoomSlider = new Slider (String::empty);
    zoomSlider->setRange (0, 1, 0);
    zoomSlider->setSliderStyle (Slider::LinearHorizontal);
    zoomSlider->setTextBoxStyle (Slider::NoTextBox, false, 80, 20);
    zoomSlider->addListener (this);
    zoomSlider->setSkewFactor (2);
    addAndMakeVisible (zoomSlider);
}

SampleDisplayComponent::~SampleDisplayComponent()
{
    deleteAllChildren();
    thumbnail.removeChangeListener (this);
}

void SampleDisplayComponent::sliderValueChanged (Slider* slider){
    SampleDisplayComponent::setZoomFactor (zoomSlider->getValue());
}

void SampleDisplayComponent::setFile (const File& file)
{
    if (! file.isDirectory())
    {
        zoomSlider->setValue(0);
        thumbnail.setSource (new FileInputSource (file));
        startTime = 0;
        endTime = thumbnail.getTotalLength();
        startTimer (1000 / 40);
    }
}

void SampleDisplayComponent::setZoomFactor (double amount)
{
    if (thumbnail.getTotalLength() > 0)
    {
        const double newScale = jmax (0.001, thumbnail.getTotalLength() * (1.0 - jlimit (0.0, 0.99, amount)));
        const double timeAtCentre = xToTime (getWidth() / 2.0f);
        startTime = timeAtCentre - newScale * 0.5;
        endTime = timeAtCentre + newScale * 0.5;
        repaint();
    }
}

void SampleDisplayComponent::mouseWheelMove (const MouseEvent&, const MouseWheelDetails& wheel)
{
    if (thumbnail.getTotalLength() > 0)
    {
        double newStart = startTime - wheel.deltaX * (endTime - startTime) / 10.0;
        newStart = jlimit (0.0, jmax (0.0, thumbnail.getTotalLength() - (endTime - startTime)), newStart);
        endTime = newStart + (endTime - startTime);
        startTime = newStart;
        
        if (wheel.deltaY != 0)
            zoomSlider->setValue (zoomSlider->getValue() - wheel.deltaY);
        
        repaint();
    }
}

void SampleDisplayComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff202020));
    g.setColour (Colours::yellow);
    
    if (thumbnail.getTotalLength() > 0)
    {
        thumbnail.drawChannels (g, getLocalBounds().reduced (2),
                                startTime, endTime, 1.0f);
    }
    else
    {
        g.setFont (14.0f);
        g.drawFittedText ("(No audio file selected)", getLocalBounds(), Justification::centred, 2);
    }
}

void SampleDisplayComponent::resized()
{
}

void SampleDisplayComponent::changeListenerCallback (ChangeBroadcaster*) 
{
    // this method is called by the thumbnail when it has changed, so we should repaint it..
    repaint();
}

bool SampleDisplayComponent::isInterestedInFileDrag (const StringArray& /*files*/)
{
    return true;
}

void SampleDisplayComponent::filesDropped (const StringArray& files, int /*x*/, int /*y*/)
{
    Application* application;
    application = findParentComponentOfClass<Application>();
    application->loadFile (File (files[0]));
}

void SampleDisplayComponent::mouseDown (const MouseEvent& e) 
{
    mouseDrag (e);
}

void SampleDisplayComponent::mouseDrag (const MouseEvent& e) 
{
    transportSource.setPosition (jmax (0.0, xToTime ((float) e.x)));
}

void SampleDisplayComponent::mouseUp (const MouseEvent&) 
{
    transportSource.start();
}

void SampleDisplayComponent::timerCallback()
{
    currentPositionMarker->setVisible (transportSource.isPlaying() || isMouseButtonDown());
    
    double currentPlayPosition = transportSource.getCurrentPosition();
    
    currentPositionMarker->setRectangle (Rectangle<float> (timeToX (currentPlayPosition) - 0.75f, 0,
                                                          1.5f, (float) getHeight()));
}
