/*
  ==============================================================================

    Pro-Parameters.cpp
    Created: 27 Jan 2024 8:01:08pm
    Author:  Eemil Ahonen

  ==============================================================================
*/

#include "../PluginProcessor.h"
#include "../Globals/Globals.h"
#include "../Keisari-Modules/Helper-Functions/HelperFunctions.h"

//==============================================================================

void DeepFryerAudioProcessor::addParameterListeners()
{
    // UI code in processor, not good
    for (auto& sliderComponent : _parameters.getSliderComponents())
    {
        _treeState.addParameterListener(sliderComponent->_id, this);
    }
}

juce::AudioProcessorValueTreeState::ParameterLayout DeepFryerAudioProcessor::createParameterLayout()
{
    return { _parameters.getAudioParameters().begin(), _parameters.getAudioParameters().end() };
}

void DeepFryerAudioProcessor::parameterChanged(const juce::String &parameterId, float newValue)
{
    // There has to be a better way to do this
    if (parameterId == inputVolumeID)
    {
        // Set input volume target value (smoothed)
        _inputVolumeValue.setTargetValue(*_treeState.getRawParameterValue(inputVolumeID));
    }
    else if (parameterId == inputVolumeID)
    {
        // Set output volume target value (smoothed)
        _outputVolumeValue.setTargetValue(*_treeState.getRawParameterValue(outputVolumeID));
    }
    else if (parameterId == inputVolumeID)
    {
        // Scale the drive parameter from 0-100 to 0-1
        _driveValue.setTargetValue(*_treeState.getRawParameterValue(driveID) / 100);
    }
    else if (parameterId == inputVolumeID)
    {
        // Amount of tone from -maximumTone to maximumTone
        _toneValue = juce::Decibels::decibelsToGain(*_treeState.getRawParameterValue(toneID) / 100 * _maximumTone);
    }
    else if (parameterId == inputVolumeID)
    {
        // Scale the clarity parameter from 0 to 100 to a cutoff frequency from 20 to maximumClarity
        _clarityValue.setTargetValue(max(*_treeState.getRawParameterValue(clarityID), 20.0f));
        _clarityModule.setCutoffFrequency(_clarityValue.getNextValue() * _maximumClarity / 10);
    }
    else if (parameterId == mixID)
    {
        // Scale the mix parameter from 0-100 to 0-1
        _mixValue = *_treeState.getRawParameterValue(mixID) / 100;
    }
    else
    {
        // Set input volume target value (smoothed)
        _inputVolumeValue.setTargetValue(*_treeState.getRawParameterValue(inputVolumeID));
        
        // Set output volume target value (smoothed)
        _outputVolumeValue.setTargetValue(*_treeState.getRawParameterValue(outputVolumeID));
        
        // Scale the drive parameter from 0-100 to 0-1
        _driveValue.setTargetValue(*_treeState.getRawParameterValue(driveID) / 100);
        
        // Amount of tone from -maximumTone to maximumTone
        _toneValue = juce::Decibels::decibelsToGain(*_treeState.getRawParameterValue(toneID) / 100 * _maximumTone);
        
        // Scale the clarity parameter from 0 to 100 to a cutoff frequency from 20 to maximumClarity
        _clarityValue.setTargetValue(max(*_treeState.getRawParameterValue(clarityID), 20.0f));
        _clarityModule.setCutoffFrequency(_clarityValue.getNextValue() * _maximumClarity / 10);
        
        // Scale the mix parameter from 0-100 to 0-1
        _mixValue = *_treeState.getRawParameterValue(mixID) / 100;
    }
}
