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

#include <JuceHeader.h>
#include <grape/parameters/Parameter.h>
#include <vector>
#include <map>

//==============================================================================

namespace mbctrl {
namespace common {

//==============================================================================

enum class ParameterId
{
    idKickTune,
    idKickPitch,
    idKickDecay,
    idKickHarmonics,
    idKickPulse,
    idKickNoise,
    idKickAttack,
    idKickEq,
    idKickLevel,

    idSnareTune,
    idSnareSnappy,
    idSnareDecay,
    idSnareDetune,
    idSnareNoise,
    idSnareLevel,

    idTomLowTune,
    idTomLowDecay,
    idTomLowLevel,
    idTomHighTune,
    idTomHighDecay,
    idTomHighLevel,

    idHatSource,
    idHatTune,
    idHatClosedAttack,
    idHatClosedPeaktime,
    idHatClosedDecay,
    idHatOpenedAttack,
    idHatOpenedPeaktime,
    idHatOpenedDecay,
    idHatHPCutoff,
    idHatLPCutoff,
    idHatResonance,
    idHatLevel,

    idClapTune,
    idClapAttack,
    idClapPeaktime,
    idClapDecay,
    idClapLevel,

    idRimshotTune,
    idRimshotAttack,
    idRimshotPeaktime,
    idRimshotDecay,
    idRimshotLevel,

    idCrashTune,
    idCrashAttack,
    idCrashPeaktime,
    idCrashDecay,
    idCrashLevel,

    idRideTune,
    idRideAttack,
    idRidePeaktime,
    idRideDecay,
    idRideLevel,

    idHatSample,
    idRimshotSample,
    idClapSample,
    idCrashSample,
    idRideSample,

    idHatReverse,
    idRimshotReverse,
    idClapReverse,
    idCrashReverse,
    idRideReverse,

    idLFO1Shape,
    idLFO1Destination,
    idLFO1Amplitude,
    idLFO1Frequency,
    
    idLFO2Shape,
    idLFO2Destination,
    idLFO2Amplitude,
    idLFO2Frequency,

    sNumParameterIds
};

//==============================================================================

extern const std::map<ParameterId, grape::parameters::Parameter>    sParameters;
extern const std::vector<grape::parameters::Parameter>              sOrderedParameters;

//==============================================================================

typedef std::map<ParameterId, float> ParameterMapper;

//==============================================================================

} // namespace common
} // namespace mbctrl
