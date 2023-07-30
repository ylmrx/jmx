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

#include <common/Parameters.h>
#include <JuceHeader.h>
#include <grape/parameters/ParameterManager.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

class ControlList : public juce::Component
{
public:
    ControlList (grape::parameters::ParameterManager&,
                 common::ParameterId);
    ~ControlList();

public: // juce::Component
    void resized() override;

private:
    typedef juce::AudioProcessorValueTreeState::ComboBoxAttachment ComboBoxAttachment;

    grape::parameters::ParameterManager&    mParameterManager;
    common::ParameterId                     mParameterId;
    juce::ComboBox  mComboBox;
    std::unique_ptr<ComboBoxAttachment> mComboBoxAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (ControlList)
};

//==============================================================================

} // namespace ui
} // namespace mbctrl
