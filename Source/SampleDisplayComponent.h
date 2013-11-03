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
class SampleDisplayComponent    : public Component
{
public:
    SampleDisplayComponent();
    ~SampleDisplayComponent();

    void paint (Graphics&);
    void resized();

private:
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (SampleDisplayComponent)
};


#endif  // SAMPLEDISPLAYCOMPONENT_H_INCLUDED
