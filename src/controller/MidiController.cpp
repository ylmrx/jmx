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

#include <controller/MidiController.h>

//==============================================================================

namespace mbctrl {
namespace controller {

//==============================================================================

static const std::map<common::ParameterId, int> sParameterCcMapper =
    {
        {common::ParameterId::idKickTune, 100},
        {common::ParameterId::idKickPitch, 101},
        {common::ParameterId::idKickDecay, 102},
        {common::ParameterId::idKickHarmonics, 103},
        {common::ParameterId::idKickPulse, 104},
        {common::ParameterId::idKickNoise, 105},
        {common::ParameterId::idKickAttack, 106},
        {common::ParameterId::idKickEq, 107},
        {common::ParameterId::idKickLevel, 117},

        {common::ParameterId::idSnareTune, 108},
        {common::ParameterId::idSnareSnappy, 109},
        {common::ParameterId::idSnareDecay, 110},
        {common::ParameterId::idSnareDetune, 111},
        {common::ParameterId::idSnareNoise, 112},
        {common::ParameterId::idSnareLevel, 118},

        {common::ParameterId::idTomLowTune, 12},
        {common::ParameterId::idTomLowDecay, 13},
        {common::ParameterId::idTomLowLevel, 14},
        {common::ParameterId::idTomHighTune, 15},
        {common::ParameterId::idTomHighDecay, 16},
        {common::ParameterId::idTomHighLevel, 17},

        {common::ParameterId::idHatSource, 62},
        {common::ParameterId::idHatTune, 18},
        {common::ParameterId::idHatClosedAttack, 19},
        {common::ParameterId::idHatClosedPeaktime, 20},
        {common::ParameterId::idHatClosedDecay, 21},
        {common::ParameterId::idHatOpenedAttack, 22},
        {common::ParameterId::idHatOpenedPeaktime, 23},
        {common::ParameterId::idHatOpenedDecay, 24},
        {common::ParameterId::idHatHPCutoff, 59},
        {common::ParameterId::idHatLPCutoff, 60},
        {common::ParameterId::idHatResonance, 61},
        {common::ParameterId::idHatLevel, 25},

        {common::ParameterId::idClapTune, 26},
        {common::ParameterId::idClapAttack, 27},
        {common::ParameterId::idClapPeaktime, 28},
        {common::ParameterId::idClapDecay, 29},
        {common::ParameterId::idClapLevel, 30},

        {common::ParameterId::idRimshotTune, 44},
        {common::ParameterId::idRimshotAttack, 45},
        {common::ParameterId::idRimshotPeaktime, 46},
        {common::ParameterId::idRimshotDecay, 47},
        {common::ParameterId::idRimshotLevel, 48},

        {common::ParameterId::idCrashTune, 49},
        {common::ParameterId::idCrashAttack, 50},
        {common::ParameterId::idCrashPeaktime, 51},
        {common::ParameterId::idCrashDecay, 52},
        {common::ParameterId::idCrashLevel, 53},

        {common::ParameterId::idRideTune, 54},
        {common::ParameterId::idRideAttack, 55},
        {common::ParameterId::idRidePeaktime, 56},
        {common::ParameterId::idRideDecay, 57},
        {common::ParameterId::idRideLevel, 58},

        {common::ParameterId::idHatSample, 62},
        {common::ParameterId::idClapSample, 62},
        {common::ParameterId::idRideSample, 62},
        {common::ParameterId::idRimshotSample, 62},
        {common::ParameterId::idCrashSample, 62},
        
        {common::ParameterId::idHatReverse, 62},
        {common::ParameterId::idClapReverse, 62},
        {common::ParameterId::idRideReverse, 62},
        {common::ParameterId::idRimshotReverse, 62},
        {common::ParameterId::idCrashReverse, 62},

        {common::ParameterId::idLFO1Shape, 75},
        {common::ParameterId::idLFO1Destination, 76},
        {common::ParameterId::idLFO1Amplitude, 77},
        {common::ParameterId::idLFO1Frequency, 78},

        {common::ParameterId::idLFO2Shape, 79},
        {common::ParameterId::idLFO2Destination, 80},
        {common::ParameterId::idLFO2Amplitude, 81},
        {common::ParameterId::idLFO2Frequency, 82},
};

//==============================================================================

static juce::MidiMessage createParameterControl (common::ParameterId paramId,
                                                 float value,
                                                 int channel)
{
    jassert (channel > 0);

    const auto param = common::sParameters.at (paramId);
    const auto ccType = sParameterCcMapper.at (paramId);
    float add_sample_cc = 0.0f;
    if (ccType == 75 || ccType == 79) {
        if (value > 3.0f) add_sample_cc = 4.0f;
    }
    if (ccType == 62) {
        if(param.id == "rimshot-sample")
            add_sample_cc = 4.0f;
        if(param.id == "clap-sample")
            add_sample_cc = 8.0f;
        if(param.id == "crash-sample")
            add_sample_cc = 12.0f;
        if(param.id == "ride-sample")
            add_sample_cc = 16.0f;

        if(param.id == "hat-reverse")
            add_sample_cc = 20.0f;
        if(param.id == "rimshot-reverse")
            add_sample_cc = 22.0f;
        if(param.id == "clap-reverse")
            add_sample_cc = 24.0f;
        if(param.id == "crash-reverse")
            add_sample_cc = 26.0f;
        if(param.id == "ride-reverse")
            add_sample_cc = 28.0f;
        if(param.id == "hat-source")
            add_sample_cc = 32.0f;
    }
    return juce::MidiMessage::controllerEvent (channel, ccType, static_cast<int>(value + add_sample_cc));
}

//==============================================================================

MidiController::MidiController (grape::parameters::ParameterManager& parameterManager,
                                grape::settings::SettingManager& settingManager,
                                bool useMidiDevice)
    : mUseExternalMidi (useMidiDevice)
    , mMidiOutputDevices()
    , mMidiOutput (nullptr)
    , mMidiChannel (1)
    , mParameterManager (parameterManager)
    , mSettingManager (settingManager)
{
    for (const auto& p : sParameterCcMapper)
    {
        const auto paramId  = p.first;
        const auto param    = common::sParameters.at (paramId);

        mParametersValues[paramId] = param.defaultValue;
        mParameterManager.addParameterListener (param.id, this);
    }

    mSettingManager.addListener (this);
    setUseExternalMidi (mUseExternalMidi);

    updateSettingsValues();
    updateParametersValues();
}

MidiController::~MidiController()
{
    for (const auto& p : sParameterCcMapper)
    {
        const auto paramId = p.first;
        const auto param = common::sParameters.at (paramId);

        mParameterManager.removeParameterListener (param.id, this);
    }

    mSettingManager.removeListener (this);
}

//==============================================================================

void MidiController::setUseExternalMidi (bool useExternalMidi)
{
    const auto useExternalMidiSetting = common::sSettings.at (common::SettingId::idUseExternalMidi);

    updateUseExternalMidi (useExternalMidi);
    mSettingManager.setSetting (useExternalMidiSetting.id, juce::var (mUseExternalMidi));
}

juce::StringArray MidiController::getMidiOutputDevices() const
{
    return mMidiOutputDevices;
}

void MidiController::updateMidiOutputDevices()
{
    mMidiOutputDevices = juce::MidiOutput::getDevices();
}

bool MidiController::selectDefaultMidiOutputDevice()
{
    return selectMidiOutputDevice (juce::MidiOutput::getDefaultDeviceIndex());
}

bool MidiController::selectMidiOutputDevice (int index)
{
    updateMidiOutputDevice (index);

    if (mMidiOutput.get() != nullptr)
    {
        const auto midiDeviceSetting    = common::sSettings.at (common::SettingId::idMidiDevice);
        const auto midiDeviceName       = mMidiOutput->getName();

        mSettingManager.setSetting (
            midiDeviceSetting.id,
            juce::var (midiDeviceName)
        );

        return true;
    }

    return false;
}

juce::String MidiController::getSelectedMidiOutputDevice() const
{
    if (mMidiOutput == nullptr)
        return juce::String();

    return mMidiOutput->getName();
}

void MidiController::setMidiChannel (int channel)
{
    const auto midiChannelSetting = common::sSettings.at (common::SettingId::idMidiChannel);

    updateMidiChannel (channel);
    mSettingManager.setSetting (midiChannelSetting.id, juce::var (mMidiChannel));
}

void MidiController::synchronize()
{
    for (const auto& p : sParameterCcMapper)
    {
        const auto paramId  = p.first;
        const auto param    = common::sParameters.at (paramId);
        const auto newValue = *mParameterManager.getRawParameterValue (param.id);

        mParametersValues[paramId] = newValue;
        addMidiMessageToBuffer (paramId, newValue);
    }

    sendMidiBuffer();
}

juce::MidiBuffer MidiController::extractMidiBuffer()
{
    const auto midiBuffer (mMidiBuffer);
    mMidiBuffer.clear();

    return midiBuffer;
}

//==============================================================================

void MidiController::sendMidiBuffer()
{
    if (!mUseExternalMidi || mMidiOutput == nullptr)
        return;

    mMidiOutput->sendBlockOfMessagesNow (extractMidiBuffer());
}

void MidiController::updateParametersValues()
{
    for (const auto& p : sParameterCcMapper)
    {
        const auto paramId = p.first;
        const auto param = common::sParameters.at (paramId);

        const auto currentValue = mParametersValues[paramId];
        const auto newValue = *mParameterManager.getRawParameterValue (param.id);

        if (newValue != currentValue)
        {
            mParametersValues[paramId] = newValue;
            addMidiMessageToBuffer (paramId, newValue);
        }
    }

    sendMidiBuffer();
}

void MidiController::updateSettingsValues()
{
    {
        const auto useExternalMidiSetting   = common::sSettings.at (common::SettingId::idUseExternalMidi);
        const auto useExternalMidi          = mSettingManager.getSetting (useExternalMidiSetting.id);
        updateUseExternalMidi (bool (useExternalMidi));
    }

    {
        const auto midiDeviceSetting    = common::sSettings.at (common::SettingId::idMidiDevice);
        const auto midiDevice           = mSettingManager.getSetting (midiDeviceSetting.id);
        updateMidiOutputDeviceByName (midiDevice.toString());
    }

    {
        const auto midiChannelSetting   = common::sSettings.at (common::SettingId::idMidiChannel);
        const auto midiChannel          = mSettingManager.getSetting (midiChannelSetting.id);
        updateMidiChannel (int (midiChannel));
    }
}

void MidiController::updateUseExternalMidi (bool useExternalMidi)
{
    mUseExternalMidi = useExternalMidi;
}

void MidiController::updateMidiOutputDevice (int deviceIndex)
{
    if (!mUseExternalMidi)
    {
        mMidiOutput.reset();
        return;
    }

    const auto device = juce::MidiOutput::openDevice (deviceIndex);
    if (device != nullptr)
    {
        mMidiOutput.reset (device);
    }
}

void MidiController::updateMidiOutputDeviceByName (const juce::String& deviceName)
{
    updateMidiOutputDevices();

    for (int i = 0; i < mMidiOutputDevices.size(); ++i)
    {
        const auto d = mMidiOutputDevices[i];
        if (d == deviceName)
        {
            updateMidiOutputDevice (i);
        }
    }
}

void MidiController::updateMidiChannel (int channel)
{
    jassert (channel > 0 && channel <= 16);

    mMidiChannel = channel;
}

void MidiController::addMidiMessageToBuffer (common::ParameterId paramId, float newValue)
{
    const auto midiMessage = createParameterControl (
        paramId, newValue, mMidiChannel
    );

    mMidiBuffer.addEvent (midiMessage, 0);
}

//==============================================================================

void MidiController::parameterChanged (const juce::String& paramId, float paramValue)
{
    updateParametersValues();
}

//==============================================================================

void MidiController::settingChanged (const juce::String& setting, const juce::var& value)
{
    updateSettingsValues();
}

//==============================================================================

} // namespace controller
} // namespace mbctrl
