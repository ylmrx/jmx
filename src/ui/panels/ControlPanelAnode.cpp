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

#include <ui/panels/ControlPanelAnode.h>
#include <common/Parameters.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

ControlPanelAnode::ControlPanelAnode (grape::parameters::ParameterManager& parameterManager,
                                      controller::MidiController& midiController)
    : mMidiController (midiController)

    , mKickTune (parameterManager, common::ParameterId::idKickTune, "TUNE")
    , mKickPitch (parameterManager, common::ParameterId::idKickPitch, "PITCH")
    , mKickDecay (parameterManager, common::ParameterId::idKickDecay, "DECAY")
    , mKickHarmonics (parameterManager, common::ParameterId::idKickHarmonics, "HARMS")
    , mKickPulse (parameterManager, common::ParameterId::idKickPulse, "PULSE")
    , mKickNoise (parameterManager, common::ParameterId::idKickNoise, "NOISE")
    , mKickAttack (parameterManager, common::ParameterId::idKickAttack, "ATTCK")
    , mKickEq (parameterManager, common::ParameterId::idKickEq, "EQ")
    , mKickLevel (parameterManager, common::ParameterId::idKickLevel, "LEVEL")

    , mSnareTune (parameterManager, common::ParameterId::idSnareTune, "TUNE")
    , mSnareSnappy (parameterManager, common::ParameterId::idSnareSnappy, "SNAP")
    , mSnareDecay (parameterManager, common::ParameterId::idSnareDecay, "DECAY")
    , mSnareDetune (parameterManager, common::ParameterId::idSnareDetune, "DETUN")
    , mSnareNoise (parameterManager, common::ParameterId::idSnareNoise, "NOISE")
    , mSnareLevel (parameterManager, common::ParameterId::idSnareLevel, "LEVEL")

    , mTomLowTune (parameterManager, common::ParameterId::idTomLowTune, "LTUNE")
    , mTomLowDecay (parameterManager, common::ParameterId::idTomLowDecay, "LDECAY")
    , mTomLowLevel (parameterManager, common::ParameterId::idTomLowLevel, "LLEVEL")
    , mTomHighTune (parameterManager, common::ParameterId::idTomHighTune, "HTUNE")
    , mTomHighDecay (parameterManager, common::ParameterId::idTomHighDecay, "HDECAY")
    , mTomHighLevel (parameterManager, common::ParameterId::idTomHighLevel, "HLEVEL")

    , mHatSource (parameterManager, common::ParameterId::idHatSource)
    , mHatTune (parameterManager, common::ParameterId::idHatTune, "TUNE")
    , mHatClosedAttack (parameterManager, common::ParameterId::idHatClosedAttack, "CATTCK")
    , mHatClosedPeaktime (parameterManager, common::ParameterId::idHatClosedPeaktime, "CPEAK")
    , mHatClosedDecay (parameterManager, common::ParameterId::idHatClosedDecay, "CDECAY")
    , mHatOpenedAttack (parameterManager, common::ParameterId::idHatOpenedAttack, "OATTCK")
    , mHatOpenedPeaktime (parameterManager, common::ParameterId::idHatOpenedPeaktime, "OPEAK")
    , mHatOpenedDecay (parameterManager, common::ParameterId::idHatOpenedDecay, "ODECAY")
    , mHatLevel (parameterManager, common::ParameterId::idHatLevel, "LEVEL")
    , mHatHPCutoff (parameterManager, common::ParameterId::idHatHPCutoff, "HPCUT")
    , mHatLPCutoff (parameterManager, common::ParameterId::idHatLPCutoff, "LPCUT")
    , mHatResonance (parameterManager, common::ParameterId::idHatResonance, "RES")

    , mClapTune (parameterManager, common::ParameterId::idClapTune, "TUNE")
    , mClapAttack (parameterManager, common::ParameterId::idClapAttack, "ATTCK")
    , mClapPeaktime (parameterManager, common::ParameterId::idClapPeaktime, "PEAK")
    , mClapDecay (parameterManager, common::ParameterId::idClapDecay, "DECAY")
    , mClapLevel (parameterManager, common::ParameterId::idClapLevel, "LEVEL")

    , mRimshotTune (parameterManager, common::ParameterId::idRimshotTune, "TUNE")
    , mRimshotAttack (parameterManager, common::ParameterId::idRimshotAttack, "ATTCK")
    , mRimshotPeaktime (parameterManager, common::ParameterId::idRimshotPeaktime, "PEAK")
    , mRimshotDecay (parameterManager, common::ParameterId::idRimshotDecay, "DECAY")
    , mRimshotLevel (parameterManager, common::ParameterId::idRimshotLevel, "LEVEL")
    
    , mCrashTune (parameterManager, common::ParameterId::idCrashTune, "TUNE")
    , mCrashAttack (parameterManager, common::ParameterId::idCrashAttack, "ATTCK")
    , mCrashPeaktime (parameterManager, common::ParameterId::idCrashPeaktime, "PEAK")
    , mCrashDecay (parameterManager, common::ParameterId::idCrashDecay, "DECAY")
    , mCrashLevel (parameterManager, common::ParameterId::idCrashLevel, "LEVEL")

    , mRideTune (parameterManager, common::ParameterId::idRideTune, "TUNE")
    , mRideAttack (parameterManager, common::ParameterId::idRideAttack, "ATTCK")
    , mRidePeaktime (parameterManager, common::ParameterId::idRidePeaktime, "PEAK")
    , mRideDecay (parameterManager, common::ParameterId::idRideDecay, "DECAY")
    , mRideLevel (parameterManager, common::ParameterId::idRideLevel, "LEVEL")
    
    , mHatSample (parameterManager, common::ParameterId::idHatSample)
    , mRimshotSample (parameterManager, common::ParameterId::idRimshotSample)
    , mClapSample (parameterManager, common::ParameterId::idClapSample)
    , mCrashSample (parameterManager, common::ParameterId::idCrashSample)
    , mRideSample (parameterManager, common::ParameterId::idRideSample)

    , mHatReverse (parameterManager, common::ParameterId::idHatReverse)
    , mRimshotReverse (parameterManager, common::ParameterId::idRimshotReverse)
    , mClapReverse (parameterManager, common::ParameterId::idClapReverse)
    , mCrashReverse (parameterManager, common::ParameterId::idCrashReverse)
    , mRideReverse (parameterManager, common::ParameterId::idRideReverse)

    , mLFO1Shape (parameterManager, common::ParameterId::idLFO1Shape)
    , mLFO1Destination (parameterManager, common::ParameterId::idLFO1Destination)
    , mLFO1Amplitude (parameterManager, common::ParameterId::idLFO1Amplitude, "AMP")
    , mLFO1Frequency (parameterManager, common::ParameterId::idLFO1Frequency, "RATE")
    , mLFO2Shape (parameterManager, common::ParameterId::idLFO2Shape)
    , mLFO2Destination (parameterManager, common::ParameterId::idLFO2Destination)
    , mLFO2Amplitude (parameterManager, common::ParameterId::idLFO2Amplitude, "AMP")
    , mLFO2Frequency (parameterManager, common::ParameterId::idLFO2Frequency, "RATE")

{

    mSync.setButtonText ("Synchronize");
    mSync.onClick = [this] { mMidiController.synchronize(); };
    addAndMakeVisible (mSync);

    mKickGroup.setText ("KICK");
    mKickGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mKickGroup);

    addAndMakeVisible (mKickTune);
    addAndMakeVisible (mKickPitch);
    addAndMakeVisible (mKickDecay);
    addAndMakeVisible (mKickHarmonics);
    addAndMakeVisible (mKickPulse);
    addAndMakeVisible (mKickNoise);
    addAndMakeVisible (mKickAttack);
    addAndMakeVisible (mKickEq);
    addAndMakeVisible (mKickLevel);

    mSnareGroup.setText ("SNARE");
    mSnareGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mSnareGroup);

    addAndMakeVisible (mSnareTune);
    addAndMakeVisible (mSnareSnappy);
    addAndMakeVisible (mSnareDecay);
    addAndMakeVisible (mSnareDetune);
    addAndMakeVisible (mSnareNoise);
    addAndMakeVisible (mSnareLevel);

    mTomsGroup.setText ("LOW TOM / HIGH TOM");
    mTomsGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mTomsGroup);

    addAndMakeVisible (mTomLowTune);
    addAndMakeVisible (mTomLowDecay);
    addAndMakeVisible (mTomLowLevel);
    addAndMakeVisible (mTomHighTune);
    addAndMakeVisible (mTomHighDecay);
    addAndMakeVisible (mTomHighLevel);

    mHatGroup.setText ("HATS");
    mHatGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mHatGroup);

    addAndMakeVisible (mHatTune);
    addAndMakeVisible (mHatClosedAttack);
    addAndMakeVisible (mHatClosedPeaktime);
    addAndMakeVisible (mHatClosedDecay);
    addAndMakeVisible (mHatOpenedAttack);
    addAndMakeVisible (mHatOpenedPeaktime);
    addAndMakeVisible (mHatOpenedDecay);
    addAndMakeVisible (mHatLevel);
    addAndMakeVisible (mHatHPCutoff);
    addAndMakeVisible (mHatLPCutoff);
    addAndMakeVisible (mHatResonance);
    addAndMakeVisible (mHatSource);

    mClapGroup.setText ("CLAP");
    mClapGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mClapGroup);
    addAndMakeVisible (mClapTune);
    addAndMakeVisible (mClapAttack);
    addAndMakeVisible (mClapPeaktime);
    addAndMakeVisible (mClapDecay);
    addAndMakeVisible (mClapLevel);

    mRimshotGroup.setText ("RIMSHOT");
    mRimshotGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mRimshotGroup);
    addAndMakeVisible (mRimshotTune);
    addAndMakeVisible (mRimshotAttack);
    addAndMakeVisible (mRimshotPeaktime);
    addAndMakeVisible (mRimshotDecay);
    addAndMakeVisible (mRimshotLevel);
    
    mCrashGroup.setText ("CRASH");
    mCrashGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mCrashGroup);
    addAndMakeVisible (mCrashTune);
    addAndMakeVisible (mCrashAttack);
    addAndMakeVisible (mCrashPeaktime);
    addAndMakeVisible (mCrashDecay);
    addAndMakeVisible (mCrashLevel);
    
    mRideGroup.setText ("RIDE");
    mRideGroup.setTextLabelPosition (juce::Justification::centred);
    addAndMakeVisible (mRideGroup);
    addAndMakeVisible (mRideTune);
    addAndMakeVisible (mRideAttack);
    addAndMakeVisible (mRidePeaktime);
    addAndMakeVisible (mRideDecay);
    addAndMakeVisible (mRideLevel);

    addAndMakeVisible (mHatSample);
    addAndMakeVisible (mRimshotSample);
    addAndMakeVisible (mClapSample);
    addAndMakeVisible (mCrashSample);
    addAndMakeVisible (mRideSample);

    addAndMakeVisible (mHatReverse);
    addAndMakeVisible (mRimshotReverse);
    addAndMakeVisible (mClapReverse);
    addAndMakeVisible (mCrashReverse);
    addAndMakeVisible (mRideReverse);

    mLFOGroup.setText("LFO");
    mLFOGroup.setTextLabelPosition(juce::Justification::centred);
    addAndMakeVisible(mLFOGroup);
    addAndMakeVisible(mLFO1Shape);
    addAndMakeVisible(mLFO1Destination);
    addAndMakeVisible(mLFO1Amplitude);
    addAndMakeVisible(mLFO1Frequency);

    addAndMakeVisible(mLFO2Shape);
    addAndMakeVisible(mLFO2Destination);
    addAndMakeVisible(mLFO2Amplitude);
    addAndMakeVisible(mLFO2Frequency);
}

ControlPanelAnode::~ControlPanelAnode()
{
}

//==============================================================================

void ControlPanelAnode::resized()
{
    static const auto sHorizontalMargin = 20;
    static const auto sVerticalMargin   = 20;
    static const auto sKnobWidth        = 70;
    static const auto sKnobHeight       = 80;
    static const auto sToggleWidth      = 70;
    static const auto sToggleHeight     = 80;
    static const auto sListWidth        = 70;
    static const auto sListHeight       = 80;
    static const auto sMeeblipWidth     = 100;
    static const auto sMeeblipHeight    = 25;
    static const auto sAnodeWidth       = 56;
    static const auto sAnodeHeight      = 25;
    static const auto sSyncWidth        = 100;
    static const auto sSyncHeight       = 20;

    const auto bounds       = getLocalBounds();
    const auto usableWidth = bounds.getWidth(); // -sHorizontalMargin * 2;
    // const auto leftWidth    = 3 * usableWidth / 5;
    const auto leftWidth    = usableWidth / 2;
    const auto rightWidth = leftWidth;

    {
    }

    mSync.setBounds (
        (sHorizontalMargin * 2 + leftWidth + (rightWidth / 2)) - (sSyncWidth / 2),
        20,
        sSyncWidth,
        sSyncHeight
    );

    mKickGroup.setBounds (
        0,
        mSync.getY() + sSyncHeight + sVerticalMargin,
        usableWidth,
        sSyncHeight
    );

        mKickTune.setBounds (
            mKickGroup.getX(),
            mKickGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mKickPitch.setBounds (
            mKickGroup.getX() + 1 * sKnobWidth,
            mKickGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mKickDecay.setBounds (
            mKickGroup.getX() + 2 * sKnobWidth,
            mKickGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mKickHarmonics.setBounds (
            mKickGroup.getX() + 3 * sKnobWidth,
            mKickGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mKickPulse.setBounds (
            mKickGroup.getX() + 4 * sKnobWidth,
            mKickGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mKickNoise.setBounds (
            mKickGroup.getX() + 5 * sKnobWidth,
            mKickGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );


        mKickAttack.setBounds (
            mKickGroup.getX(),
            mKickNoise.getY() + sKnobHeight,
            sKnobWidth,
            sKnobHeight
        );

        mKickEq.setBounds (
            mKickGroup.getX() + sKnobWidth,
            mKickAttack.getY(),
            sKnobWidth,
            sKnobHeight
        );

        mKickLevel.setBounds (
            mKickGroup.getX() + 5 * sKnobWidth,
            mKickAttack.getY(),
            sKnobWidth,
            sKnobHeight
        );

    mSnareGroup.setBounds (
        0,
        mKickAttack.getY() + sKnobHeight + 2 * sVerticalMargin,
        usableWidth,
        mKickGroup.getHeight()
    );

        mSnareTune.setBounds (
            mSnareGroup.getX(),
            mSnareGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mSnareSnappy.setBounds (
            mSnareGroup.getX() + sKnobWidth,
            mSnareGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mSnareDecay.setBounds (
            mSnareGroup.getX() + 2 * sKnobWidth,
            mSnareGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mSnareDetune.setBounds (
            mSnareGroup.getX() + 3 * sKnobWidth,
            mSnareGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mSnareNoise.setBounds (
            mSnareGroup.getX() + 4 * sKnobWidth,
            mSnareGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mSnareLevel.setBounds (
            mSnareGroup.getX() + 5 * sKnobWidth,
            mSnareGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

    mTomsGroup.setBounds (
        0,
        mSnareGroup.getY() + sKnobHeight + 2 * sVerticalMargin,
        usableWidth,
        mKickGroup.getHeight()
    );

        mTomLowTune.setBounds (
            mTomsGroup.getX(),
            mTomsGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mTomLowDecay.setBounds (
            mTomsGroup.getX() + sKnobWidth,
            mTomsGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mTomLowLevel.setBounds (
            mTomsGroup.getX() + 2 * sKnobWidth,
            mTomsGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mTomHighTune.setBounds (
            mTomsGroup.getX() + 3 * sKnobWidth,
            mTomsGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mTomHighDecay.setBounds (
            mTomsGroup.getX() + 4 * sKnobWidth,
            mTomsGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mTomHighLevel.setBounds (
            mTomsGroup.getX() + 5 * sKnobWidth,
            mTomsGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

    mHatGroup.setBounds (
        0,
        mTomsGroup.getY() + sKnobHeight + 2 * sVerticalMargin,
        usableWidth,
        mKickGroup.getHeight()
    );

        mHatSource.setBounds (
            mSync.getX(),
            mHatGroup.getY(),
            sSyncWidth,
            mHatGroup.getHeight()
        );
        mHatClosedAttack.setBounds (
            mHatGroup.getX(),
            mHatGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mHatClosedPeaktime.setBounds (
            mHatGroup.getX() + sKnobWidth,
            mHatGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mHatClosedDecay.setBounds (
            mHatGroup.getX() + 2 * sKnobWidth,
            mHatGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mHatOpenedAttack.setBounds (
            mHatGroup.getX() + 3 * sKnobWidth,
            mHatGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mHatOpenedPeaktime.setBounds (
            mHatGroup.getX() + 4 * sKnobWidth,
            mHatGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mHatOpenedDecay.setBounds (
            mHatGroup.getX() + 5 * sKnobWidth,
            mHatGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );

        mHatTune.setBounds (
            mHatGroup.getX(),
            mHatClosedAttack.getY() + sKnobHeight,
            sKnobWidth,
            sKnobHeight
        );
        mHatHPCutoff.setBounds (
            mHatGroup.getX() + 1 * sKnobWidth,
            mHatClosedAttack.getY() + sKnobHeight,
            sKnobWidth,
            sKnobHeight
        );
        mHatLPCutoff.setBounds (
            mHatGroup.getX() + 2 * sKnobWidth,
            mHatClosedAttack.getY() + sKnobHeight,
            sKnobWidth,
            sKnobHeight
        );
        mHatResonance.setBounds (
            mHatGroup.getX() + 3 * sKnobWidth,
            mHatClosedAttack.getY() + sKnobHeight,
            sKnobWidth,
            sKnobHeight
        );
        mHatLevel.setBounds (
            mHatGroup.getX() + 5 * sKnobWidth,
            mHatClosedAttack.getY() + sKnobHeight,
            sKnobWidth,
            sKnobHeight
        );
        mHatSample.setBounds (
            mHatResonance.getX() + sKnobWidth,
            mHatClosedAttack.getY() + sKnobHeight,
            sKnobWidth,
            sKnobHeight / 3
        );
        mHatReverse.setBounds (
            mHatResonance.getX() + sKnobWidth,
            mHatClosedAttack.getY() + sKnobHeight + sKnobHeight/3,
            sKnobWidth,
            sKnobHeight
        );

    mClapGroup.setBounds (
        0,
        mHatGroup.getY() + 2* sKnobHeight + 2 * sVerticalMargin,
        usableWidth,
        mKickGroup.getHeight()
    );
        mClapTune.setBounds (
            mClapGroup.getX(),
            mClapGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mClapAttack.setBounds (
            mClapGroup.getX() + sKnobWidth,
            mClapGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mClapPeaktime.setBounds (
            mClapGroup.getX() + 2 * sKnobWidth,
            mClapGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mClapDecay.setBounds (
            mClapGroup.getX() + 3 * sKnobWidth,
            mClapGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mClapSample.setBounds (
            mClapGroup.getX() + 4* sKnobWidth,
            mClapGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight / 3
        );
        mClapReverse.setBounds (
            mClapGroup.getX() + 4* sKnobWidth,
            mClapGroup.getY() + sVerticalMargin + sKnobHeight/3,
            sKnobWidth,
            sKnobHeight
        );
        mClapLevel.setBounds (
            mClapGroup.getX() + 5 * sKnobWidth,
            mClapGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
    mRimshotGroup.setBounds (
        0,
        mClapGroup.getY() + sKnobHeight + 2 * sVerticalMargin,
        usableWidth,
        mKickGroup.getHeight()
    );
        mRimshotTune.setBounds (
            mRimshotGroup.getX(),
            mRimshotGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mRimshotAttack.setBounds (
            mRimshotGroup.getX() + sKnobWidth,
            mRimshotGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mRimshotPeaktime.setBounds (
            mRimshotGroup.getX() + 2 * sKnobWidth,
            mRimshotGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mRimshotDecay.setBounds (
            mRimshotGroup.getX() + 3 * sKnobWidth,
            mRimshotGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mRimshotSample.setBounds (
            mRimshotGroup.getX() + 4* sKnobWidth,
            mRimshotGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight / 3
        );
        mRimshotReverse.setBounds (
            mRimshotGroup.getX() + 4* sKnobWidth,
            mRimshotGroup.getY() + sVerticalMargin + sKnobHeight/3,
            sKnobWidth,
            sKnobHeight
        );
        mRimshotLevel.setBounds (
            mRimshotGroup.getX() + 5 * sKnobWidth,
            mRimshotGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
    mCrashGroup.setBounds (
        0,
        mRimshotGroup.getY() + sKnobHeight + 2*sVerticalMargin,
        usableWidth,
        mKickGroup.getHeight()
    );
        mCrashTune.setBounds (
            mCrashGroup.getX(),
            mCrashGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mCrashAttack.setBounds (
            mCrashGroup.getX() + sKnobWidth,
            mCrashGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mCrashPeaktime.setBounds (
            mCrashGroup.getX() + 2 * sKnobWidth,
            mCrashGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mCrashDecay.setBounds (
            mCrashGroup.getX() + 3 * sKnobWidth,
            mCrashGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mCrashSample.setBounds (
            mCrashGroup.getX() + 4* sKnobWidth,
            mCrashGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight / 3
        );
        mCrashReverse.setBounds (
            mCrashGroup.getX() + 4* sKnobWidth,
            mCrashGroup.getY() + sVerticalMargin + sKnobHeight/3,
            sKnobWidth,
            sKnobHeight
        );
        mCrashLevel.setBounds (
            mCrashGroup.getX() + 5 * sKnobWidth,
            mCrashGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
    mRideGroup.setBounds (
        0,
        mCrashGroup.getY() + sKnobHeight + 2*sVerticalMargin,
        usableWidth,
        mKickGroup.getHeight()
    );
        mRideTune.setBounds (
            mRideGroup.getX(),
            mRideGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mRideAttack.setBounds (
            mRideGroup.getX() + sKnobWidth,
            mRideGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mRidePeaktime.setBounds (
            mRideGroup.getX() + 2 * sKnobWidth,
            mRideGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mRideDecay.setBounds (
            mRideGroup.getX() + 3 * sKnobWidth,
            mRideGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mRideSample.setBounds (
            mRideGroup.getX() + 4* sKnobWidth,
            mRideGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight / 3
        );
        mRideReverse.setBounds (
            mRideGroup.getX() + 4* sKnobWidth,
            mRideGroup.getY() + sVerticalMargin + sKnobHeight/3,
            sKnobWidth,
            sKnobHeight
        );
        mRideLevel.setBounds (
            mRideGroup.getX() + 5 * sKnobWidth,
            mRideGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
    mLFOGroup.setBounds(
        0,
        mRideGroup.getY() + sKnobHeight + 2 * sVerticalMargin,
        usableWidth,
        mKickGroup.getHeight()
    );
        mLFO1Shape.setBounds(
            mLFOGroup.getX(),
            mLFOGroup.getY() + sVerticalMargin,
            sKnobWidth * 2 - 10,
            sKnobHeight
        );
        mLFO1Destination.setBounds(
            mLFOGroup.getX() + sKnobWidth * 2,
            mLFOGroup.getY() + sVerticalMargin,
            sKnobWidth * 2,
            sKnobHeight
        );
        mLFO1Amplitude.setBounds(
            mLFOGroup.getX() + 4 * sKnobWidth,
            mLFOGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mLFO1Frequency.setBounds(
            mLFOGroup.getX() + 5 * sKnobWidth,
            mLFOGroup.getY() + sVerticalMargin,
            sKnobWidth,
            sKnobHeight
        );
        mLFO2Shape.setBounds(
            mLFOGroup.getX(),
            mLFOGroup.getY() + sVerticalMargin + sKnobHeight, 
            sKnobWidth * 2 - 10,
            sKnobHeight
        );
        mLFO2Destination.setBounds(
            mLFOGroup.getX() + sKnobWidth * 2,
            mLFOGroup.getY() + sVerticalMargin + sKnobHeight,
            sKnobWidth * 2,
            sKnobHeight
        );
        mLFO2Amplitude.setBounds(
            mLFOGroup.getX() + 4 * sKnobWidth,
            mLFOGroup.getY() + sVerticalMargin + sKnobHeight,
            sKnobWidth,
            sKnobHeight
        );
        mLFO2Frequency.setBounds(
            mLFOGroup.getX() + 5 * sKnobWidth,
            mLFOGroup.getY() + sVerticalMargin + sKnobHeight,
            sKnobWidth,
            sKnobHeight
        );
}

void ControlPanelAnode::paint (juce::Graphics&)
{

}

//==============================================================================

} // namespace ui
} // namespace mbctrl

