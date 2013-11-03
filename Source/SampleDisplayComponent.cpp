/*
  ==============================================================================

    SampleDisplayComponent.cpp
    Created: 3 Nov 2013 9:40:47pm
    Author:  Karl Pannek

  ==============================================================================
*/

#include "../JuceLibraryCode/JuceHeader.h"
#include "SampleDisplayComponent.h"

//==============================================================================

SampleDisplayComponent::SampleDisplayComponent()
{


}

SampleDisplayComponent::~SampleDisplayComponent()
{
    deleteAllChildren();
}

void SampleDisplayComponent::paint (Graphics& g)
{
    g.fillAll (Colour (0xff111111));

    g.setColour (Colours::grey);
    g.drawRect (getLocalBounds(), 1);   // draw an outline around the component
    g.setColour (Colours::yellow);
}

void SampleDisplayComponent::resized()
{
    // This method is where you should set the bounds of any child
    // components that your component contains..

}
