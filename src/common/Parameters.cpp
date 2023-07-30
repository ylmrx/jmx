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

#include <common/Parameters.h>
#include <grape/helpers/Helpers.h>

//==============================================================================

namespace mbctrl {
namespace common {

//==============================================================================
static const int sSampleSwitches = 4;
const std::array<juce::String, sSampleSwitches> sSampleLabels = {{
    "909",
    "808",
    "CR78",
    "JMX",
}};

static const int sReverseSwitches = 2;
const std::array<juce::String, sReverseSwitches> sReverseLabels = {{
    "OFF",
    "ON",
}};

static const int sHatSourceSwitches = 3;
const std::array<juce::String, sHatSourceSwitches> sHatSourceLabels = {{
    "Normal",
    "Filter",
    "Noise"
}};

static const int sLFOShapesSwitches = 8;
const std::array<juce::String, sLFOShapesSwitches> sLFOShapesLabels = {{
    "Saw Up",
    "Saw Down",
    "Triangle",
    "Rectangle",
    "Sync Saw Up",
    "Sync Saw Down",
    "Sync Triangle",
    "Sync Rectangle"
}};

static const int sLFO1DestinationSwitches = 10;
const std::array<juce::String, sLFO1DestinationSwitches> sLFO1DestinationLabels = {{
    "BD Tune",
    "SD Tune",
    "LT Tune",
    "HT Tune",
    "HH Tune",
    "FLT Cutoff",
    "CP Tune",
    "RM Tune",
    "CR Tune",
    "RD Tune"
}};
static const int sLFO2DestinationSwitches = 4;
const std::array<juce::String, sLFO2DestinationSwitches> sLFO2DestinationLabels = {{
    "BD Tune",
    "SD Tune",
    "LT Tune",
    "HT Tune"
}};

const std::map<ParameterId, grape::parameters::Parameter> sParameters =
{
    { ParameterId::idKickTune, {
            "kick-tune",
            "Kick Tune",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idKickPitch, {
            "kick-pitch",
            "Kick Pitch",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            8.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idKickDecay, {
            "kick-decay",
            "Kick Decay",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 2.0f, 1.0f),
            127.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idKickHarmonics, {
            "kick-harmonics",
            "Kick Harmonics",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 2.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idKickPulse, {
            "kick-pulse",
            "Kick Pulse",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 8.0f, 1.0f),
            8.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idKickNoise, {
            "kick-noise",
            "Kick Noise",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 8.0f, 1.0f),
            8.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idKickAttack, {
            "kick-attack",
            "Kick Attack",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 8.0f, 1.0f),
            32.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idKickEq, {
            "kick-eq",
            "Kick EQ",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 16.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idKickLevel, {
            "kick-level",
            "Kick Level",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            127.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },

    { ParameterId::idSnareTune, {
            "snare-tune",
            "Snare Tune",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idSnareSnappy, {
            "snare-snappy",
            "Snare Snappy",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 2.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idSnareDecay, {
            "snare-decay",
            "Snare Decay",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 2.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idSnareDetune, {
            "snare-detune",
            "Snare Detune",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 8.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idSnareNoise, {
            "snare-noise",
            "Snare Noise",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 2.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idSnareLevel, {
            "snare-level",
            "Snare Level",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            127.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },

    { ParameterId::idTomLowTune, {
            "tom-low-tune",
            "LowTom Tune",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idTomLowDecay, {
            "tom-low-decay",
            "LowTom Decay",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 2.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idTomLowLevel, {
            "tom-low-level",
            "LowTom Level",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            127.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idTomHighTune, {
            "tom-high-tune",
            "HighTom Tune",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idTomHighDecay, {
            "tom-high-decay",
            "HighTom Decay",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 2.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idTomHighLevel, {
            "tom-high-level",
            "HighTom Level",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            127.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },

    { ParameterId::idHatSource, {
            "hat-source",
            "Hat Source",
            "",
            juce::NormalisableRange<float> (0.0, sHatSourceSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sHatSourceSwitches, sHatSourceLabels>,
            grape::helpers::choiceLabelToIndex<sHatSourceSwitches, sHatSourceLabels>,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idHatTune, {
            "hat-tune",
            "Hat Tune",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idHatClosedAttack, {
            "hat-closed-attack",
            "Closed-Hat Attack",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idHatClosedPeaktime, {
            "hat-closed-peaktime",
            "Closed-Hat Peaktime",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idHatClosedDecay, {
            "hat-closed-decay",
            "Closed-Hat Decay",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idHatOpenedAttack, {
            "hat-opened-attack",
            "Opened-Hat Attack",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idHatOpenedPeaktime, {
            "hat-opened-peaktime",
            "Opened-Hat Peaktime",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idHatOpenedDecay, {
            "hat-opened-decay",
            "Opened-Hat Decay",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idHatHPCutoff, {
            "hat-highpass-cutoff",
            "Hat Highpass Cutoff",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idHatLPCutoff, {
            "hat-lowpass-cutoff",
            "Hat Lowpass Cutoff",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            127.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idHatResonance, {
         "hat-resonance",
            "Hat Resonance",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idHatLevel, {
            "hat-level",
            "Hat Level",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            127.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },

    { ParameterId::idClapTune, {
            "clap-tune",
            "Clap Tune",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idClapAttack, {
            "clap-attack",
            "Clap Attack",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idClapPeaktime, {
            "clap-peaktime",
            "Clap Peaktime",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idClapDecay, {
            "clap-decay",
            "Clap Decay",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idClapLevel, {
            "clap-level",
            "Clap Level",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            127.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },

    { ParameterId::idRimshotTune, {
            "rimshot-tune",
            "Rimshot Tune",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idRimshotAttack, {
            "rimshot-attack",
            "Rimshot Attack",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idRimshotPeaktime, {
            "rimshot-peaktime",
            "Rimshot Peaktime",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idRimshotDecay, {
            "rimshot-decay",
            "Rimshot Decay",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idRimshotLevel, {
            "rimshot-level",
            "Rimshot Level",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            127.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },

    { ParameterId::idCrashTune, {
            "crash-tune",
            "Crash Tune",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idCrashAttack, {
            "crash-attack",
            "Crash Attack",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idCrashPeaktime, {
            "crash-peaktime",
            "Crash Peaktime",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idCrashDecay, {
            "crash-decay",
            "Crash Decay",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idCrashLevel, {
            "crash-level",
            "Crash Level",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            127.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },

    { ParameterId::idRideTune, {
            "ride-tune",
            "Ride Tune",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idRideAttack, {
            "ride-attack",
            "Ride Attack",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idRidePeaktime, {
            "ride-peaktime",
            "Ride Peaktime",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idRideDecay, {
            "ride-decay",
            "Ride Decay",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            64.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idRideLevel, {
            "ride-level",
            "Ride Level",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            127.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },

    { ParameterId::idHatSample, {
            "hat-sample",
            "Hat Sample",
            "",
            juce::NormalisableRange<float> (0.0f, sSampleSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sSampleSwitches, sSampleLabels>,
            grape::helpers::choiceLabelToIndex<sSampleSwitches, sSampleLabels>,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idRimshotSample, {
            "rimshot-sample",
            "Rimshot Sample",
            "",
            juce::NormalisableRange<float> (0.0f, sSampleSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sSampleSwitches, sSampleLabels>,
            grape::helpers::choiceLabelToIndex<sSampleSwitches, sSampleLabels>,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idClapSample, {
            "clap-sample",
            "Clap Sample",
            "",
            juce::NormalisableRange<float> (0.0f, sSampleSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sSampleSwitches, sSampleLabels>,
            grape::helpers::choiceLabelToIndex<sSampleSwitches, sSampleLabels>,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idCrashSample, {
            "crash-sample",
            "Crash Sample",
            "",
            juce::NormalisableRange<float> (0.0f, sSampleSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sSampleSwitches, sSampleLabels>,
            grape::helpers::choiceLabelToIndex<sSampleSwitches, sSampleLabels>,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idRideSample, {
            "ride-sample",
            "Ride Sample",
            "",
            juce::NormalisableRange<float> (0.0f, sSampleSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sSampleSwitches, sSampleLabels>,
            grape::helpers::choiceLabelToIndex<sSampleSwitches, sSampleLabels>,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },

    { ParameterId::idHatReverse, {
            "hat-reverse",
            "Hat Reverse",
            "",
            juce::NormalisableRange<float> (0.0, sReverseSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sReverseSwitches, sReverseLabels>,
            grape::helpers::choiceLabelToIndex<sReverseSwitches, sReverseLabels>,
            false,
            true,
            true,
            true,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idRimshotReverse, {
            "rimshot-reverse",
            "Rimshot Reverse",
            "",
            juce::NormalisableRange<float> (0.0, sReverseSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sReverseSwitches, sReverseLabels>,
            grape::helpers::choiceLabelToIndex<sReverseSwitches, sReverseLabels>,
            false,
            true,
            true,
            true,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idClapReverse, {
            "clap-reverse",
            "Clap Reverse",
            "",
            juce::NormalisableRange<float> (0.0, sReverseSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sReverseSwitches, sReverseLabels>,
            grape::helpers::choiceLabelToIndex<sReverseSwitches, sReverseLabels>,
            false,
            true,
            true,
            true,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idCrashReverse, {
            "crash-reverse",
            "Crash Reverse",
            "",
            juce::NormalisableRange<float> (0.0, sReverseSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sReverseSwitches, sReverseLabels>,
            grape::helpers::choiceLabelToIndex<sReverseSwitches, sReverseLabels>,
            false,
            true,
            true,
            true,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idRideReverse, {
            "ride-reverse",
            "Ride Reverse",
            "",
            juce::NormalisableRange<float> (0.0, sReverseSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sReverseSwitches, sReverseLabels>,
            grape::helpers::choiceLabelToIndex<sReverseSwitches, sReverseLabels>,
            false,
            true,
            true,
            true,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idLFO1Shape, {
            "lfo1-shape",
            "LFO1 Shape",
            "",
            juce::NormalisableRange<float> (0.0, sLFOShapesSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sLFOShapesSwitches, sLFOShapesLabels>,
            grape::helpers::choiceLabelToIndex<sLFOShapesSwitches, sLFOShapesLabels>,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idLFO1Destination, {
            "lfo1-destination",
            "LFO1 Destination",
            "",
            juce::NormalisableRange<float> (0.0, sLFO1DestinationSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sLFO1DestinationSwitches, sLFO1DestinationLabels>,
            grape::helpers::choiceLabelToIndex<sLFO1DestinationSwitches, sLFO1DestinationLabels>,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idLFO1Amplitude, {
            "lfo1-amplitude",
            "LFO1 Amplitude",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idLFO1Frequency, {
            "lfo1-frequency",
            "LFO1 Frequency",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idLFO2Shape, {
            "lfo2-shape",
            "LFO2 Shape",
            "",
            juce::NormalisableRange<float> (0.0, sLFOShapesSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sLFOShapesSwitches, sLFOShapesLabels>,
            grape::helpers::choiceLabelToIndex<sLFOShapesSwitches, sLFOShapesLabels>,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idLFO2Destination, {
            "lfo2-destination",
            "LFO2 Destination",
            "",
            juce::NormalisableRange<float> (0.0, sLFO2DestinationSwitches - 1.0f, 1.0f),
            0.0f,
            grape::helpers::choiceIndexToLabel<sLFO2DestinationSwitches, sLFO2DestinationLabels>,
            grape::helpers::choiceLabelToIndex<sLFO2DestinationSwitches, sLFO2DestinationLabels>,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idLFO2Amplitude, {
            "lfo2-amplitude",
            "LFO2 Amplitude",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    },
    { ParameterId::idLFO2Frequency, {
            "lfo2-frequency",
            "LFO2 Frequency",
            "",
            juce::NormalisableRange<float> (0.0f, 127.0f, 1.0f, 1.0f),
            0.0f,
            grape::helpers::floatValueToText<0>,
            grape::helpers::floatTextToValue,
            false,
            true,
            true,
            false,
            juce::AudioProcessorParameter::Category::genericParameter
        }
    }
};

const std::vector<grape::parameters::Parameter> sOrderedParameters =
{{
    sParameters.at (ParameterId::idKickTune),
    sParameters.at (ParameterId::idKickPitch),
    sParameters.at (ParameterId::idKickDecay),
    sParameters.at (ParameterId::idKickHarmonics),
    sParameters.at (ParameterId::idKickPulse),
    sParameters.at (ParameterId::idKickNoise),
    sParameters.at (ParameterId::idKickAttack),
    sParameters.at (ParameterId::idKickEq),
    sParameters.at (ParameterId::idKickLevel),

    sParameters.at (ParameterId::idSnareTune),
    sParameters.at (ParameterId::idSnareSnappy),
    sParameters.at (ParameterId::idSnareDecay),
    sParameters.at (ParameterId::idSnareDetune),
    sParameters.at (ParameterId::idSnareNoise),
    sParameters.at (ParameterId::idSnareLevel),

    sParameters.at (ParameterId::idTomLowTune),
    sParameters.at (ParameterId::idTomLowDecay),
    sParameters.at (ParameterId::idTomLowLevel),
    sParameters.at (ParameterId::idTomHighTune),
    sParameters.at (ParameterId::idTomHighDecay),
    sParameters.at (ParameterId::idTomHighLevel),

    sParameters.at (ParameterId::idHatSource),
    sParameters.at (ParameterId::idHatTune),
    sParameters.at (ParameterId::idHatClosedAttack),
    sParameters.at (ParameterId::idHatClosedPeaktime),
    sParameters.at (ParameterId::idHatClosedDecay),
    sParameters.at (ParameterId::idHatOpenedAttack),
    sParameters.at (ParameterId::idHatOpenedPeaktime),
    sParameters.at (ParameterId::idHatOpenedDecay),
    sParameters.at (ParameterId::idHatHPCutoff),
    sParameters.at (ParameterId::idHatLPCutoff),
    sParameters.at (ParameterId::idHatResonance),
    sParameters.at (ParameterId::idHatLevel),

    sParameters.at (ParameterId::idClapTune),
    sParameters.at (ParameterId::idClapAttack),
    sParameters.at (ParameterId::idClapPeaktime),
    sParameters.at (ParameterId::idClapDecay),
    sParameters.at (ParameterId::idClapLevel),

    sParameters.at (ParameterId::idRimshotTune),
    sParameters.at (ParameterId::idRimshotAttack),
    sParameters.at (ParameterId::idRimshotPeaktime),
    sParameters.at (ParameterId::idRimshotDecay),
    sParameters.at (ParameterId::idRimshotLevel),

    sParameters.at (ParameterId::idCrashTune),
    sParameters.at (ParameterId::idCrashAttack),
    sParameters.at (ParameterId::idCrashPeaktime),
    sParameters.at (ParameterId::idCrashDecay),
    sParameters.at (ParameterId::idCrashLevel),

    sParameters.at (ParameterId::idRideTune),
    sParameters.at (ParameterId::idRideAttack),
    sParameters.at (ParameterId::idRidePeaktime),
    sParameters.at (ParameterId::idRideDecay),
    sParameters.at (ParameterId::idRideLevel),

    sParameters.at (ParameterId::idHatSample),
    sParameters.at (ParameterId::idRimshotSample),
    sParameters.at (ParameterId::idClapSample),
    sParameters.at (ParameterId::idCrashSample),
    sParameters.at (ParameterId::idRideSample),

    sParameters.at (ParameterId::idHatReverse),
    sParameters.at (ParameterId::idRimshotReverse),
    sParameters.at (ParameterId::idClapReverse),
    sParameters.at (ParameterId::idCrashReverse),
    sParameters.at (ParameterId::idRideReverse),

    sParameters.at (ParameterId::idLFO1Shape),
    sParameters.at (ParameterId::idLFO1Destination),
    sParameters.at (ParameterId::idLFO1Amplitude),
    sParameters.at (ParameterId::idLFO1Frequency),

    sParameters.at (ParameterId::idLFO2Shape),
    sParameters.at (ParameterId::idLFO2Destination),
    sParameters.at (ParameterId::idLFO2Amplitude),
    sParameters.at (ParameterId::idLFO2Frequency)
}};

//==============================================================================

} // namespace common
} // namespace mbctrl
