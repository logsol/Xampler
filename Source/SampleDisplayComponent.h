/*
  ==============================================================================

    SampleDisplayComponent.h
    Created: 3 Nov 2013 9:40:47pm
    Author:  Karl Pannek

  ==============================================================================
*/

#ifndef SAMPLEDISPLAYCOMPONENT_H_INCLUDED
#define SAMPLEDISPLAYCOMPONENT_H_INCLUDED

#include "../JuceLibraryCode/JuceHeader.h"

//==============================================================================
/*
*/
class SampleDisplayComponent : public Component,
                               public ChangeListener,
                               public SliderListener,
                               public FileDragAndDropTarget,
                               private Timer
{
public:
    SampleDisplayComponent (AudioFormatManager& formatManager,
                            AudioTransportSource& transportSource_);
    ~SampleDisplayComponent();

    void paint (Graphics&);
    void resized();
    
    void sliderValueChanged (Slider* slider);
    void setFile (const File& file);
    void setZoomFactor (double amount);
    void mouseWheelMove (const MouseEvent&, const MouseWheelDetails& wheel);
    void changeListenerCallback (ChangeBroadcaster*);
    bool isInterestedInFileDrag (const StringArray& /*files*/);
    void filesDropped (const StringArray& files, int /*x*/, int /*y*/);
    void mouseDown (const MouseEvent& e);
    void mouseDrag (const MouseEvent& e);
    void mouseUp (const MouseEvent&);
    void timerCallback();
    

private:
    
    AudioTransportSource& transportSource;
    AudioThumbnailCache thumbnailCache;
    AudioThumbnail thumbnail;
    double startTime, endTime;
    
    Slider* zoomSlider;
    
    DrawableRectangle* currentPositionMarker;
    
    float timeToX (const double time) const
    {
        return getWidth() * (float) ((time - startTime) / (endTime - startTime));
    }
    
    double xToTime (const float x) const
    {
        return (x / getWidth()) * (endTime - startTime) + startTime;
    }
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleDisplayComponent)
};


#endif  // SAMPLEDISPLAYCOMPONENT_H_INCLUDED
