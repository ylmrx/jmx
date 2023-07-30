/*
    Meeblip Controller - MIDI controller for the Meeblip Anode synthesizer
    Copyright (c) 2018 Romain Clement

    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with this program. If not, see <https://www.gnu.org/licenses/>.
 */

//==============================================================================

#pragma once

#include <controller/MidiController.h>
#include <ui/components/ControlKnob.h>
#include <ui/components/ControlList.h>
#include <ui/components/ControlToggle.h>
#include <JuceHeader.h>
#include <grape/parameters/ParameterManager.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

class ControlPanelAnode : public juce::Component
{
public:
    ControlPanelAnode (grape::parameters::ParameterManager&,
                       controller::MidiController&);
    ~ControlPanelAnode();

public: // juce::Component
    void resized() override;
    void paint (juce::Graphics&) override;

private:
    controller::MidiController& mMidiController;

    // juce::DrawableImage     mMeeblipLogo;
    // juce::DrawableImage     mAnodeLogo;
    juce::TextButton        mSync;

    juce::GroupComponent    mKickGroup;
    ui::ControlKnob         mKickTune;
    ui::ControlKnob         mKickPitch;
    ui::ControlKnob         mKickDecay;
    ui::ControlKnob         mKickHarmonics;
    ui::ControlKnob         mKickPulse;
    ui::ControlKnob         mKickNoise;

    ui::ControlKnob         mKickAttack;
    ui::ControlKnob         mKickEq;
    ui::ControlKnob         mKickLevel;


    juce::GroupComponent    mSnareGroup;
    ui::ControlKnob         mSnareTune;
    ui::ControlKnob         mSnareSnappy;
    ui::ControlKnob         mSnareDecay;
    ui::ControlKnob         mSnareDetune;
    ui::ControlKnob         mSnareNoise;
    ui::ControlKnob         mSnareLevel;

    juce::GroupComponent    mTomsGroup;
    ui::ControlKnob         mTomLowTune;
    ui::ControlKnob         mTomLowDecay;
    ui::ControlKnob         mTomLowLevel;
    ui::ControlKnob         mTomHighTune;
    ui::ControlKnob         mTomHighDecay;
    ui::ControlKnob         mTomHighLevel;

    juce::GroupComponent    mHatGroup;
    ui::ControlKnob         mHatTune;
    ui::ControlList         mHatSource;
    ui::ControlKnob         mHatClosedAttack;
    ui::ControlKnob         mHatClosedPeaktime;
    ui::ControlKnob         mHatClosedDecay;
    ui::ControlKnob         mHatOpenedAttack;
    ui::ControlKnob         mHatOpenedPeaktime;
    ui::ControlKnob         mHatOpenedDecay;
    ui::ControlKnob         mHatHPCutoff;
    ui::ControlKnob         mHatLPCutoff;
    ui::ControlKnob         mHatResonance;
    ui::ControlKnob         mHatLevel;

    juce::GroupComponent    mClapGroup;
    ui::ControlKnob         mClapTune;
    ui::ControlKnob         mClapAttack;
    ui::ControlKnob         mClapPeaktime;
    ui::ControlKnob         mClapDecay;
    ui::ControlKnob         mClapLevel;

    juce::GroupComponent    mRimshotGroup;
    ui::ControlKnob         mRimshotTune;
    ui::ControlKnob         mRimshotAttack;
    ui::ControlKnob         mRimshotPeaktime;
    ui::ControlKnob         mRimshotDecay;
    ui::ControlKnob         mRimshotLevel;

    juce::GroupComponent    mCrashGroup;
    ui::ControlKnob         mCrashTune;
    ui::ControlKnob         mCrashAttack;
    ui::ControlKnob         mCrashPeaktime;
    ui::ControlKnob         mCrashDecay;
    ui::ControlKnob         mCrashLevel;

    juce::GroupComponent    mRideGroup;
    ui::ControlKnob         mRideTune;
    ui::ControlKnob         mRideAttack;
    ui::ControlKnob         mRidePeaktime;
    ui::ControlKnob         mRideDecay;
    ui::ControlKnob         mRideLevel;
    
    ui::ControlList         mHatSample;
    ui::ControlList         mRimshotSample;
    ui::ControlList         mClapSample;
    ui::ControlList         mCrashSample;
    ui::ControlList         mRideSample;

    ui::ControlToggle         mHatReverse;
    ui::ControlToggle         mRimshotReverse;
    ui::ControlToggle         mClapReverse;
    ui::ControlToggle         mCrashReverse;
    ui::ControlToggle         mRideReverse;

    juce::GroupComponent    mLFOGroup;
    ui::ControlList mLFO1Shape;
    ui::ControlList mLFO1Destination;
    ui::ControlKnob mLFO1Amplitude;
    ui::ControlKnob mLFO1Frequency;

    ui::ControlList mLFO2Shape;
    ui::ControlList mLFO2Destination;
    ui::ControlKnob mLFO2Amplitude;
    ui::ControlKnob mLFO2Frequency;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlPanelAnode)
};

//==============================================================================

} // namespace ui
} // namespace mbctrl

