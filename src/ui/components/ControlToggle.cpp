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

#include <ui/components/ControlToggle.h>

//==============================================================================

namespace mbctrl {
namespace ui {

//==============================================================================

ControlToggle::ControlToggle (grape::parameters::ParameterManager& parameterManager,
                              common::ParameterId parameterId)
    : mParameterManager (parameterManager)
    , mParameterId (parameterId)
{
    const auto param = common::sParameters.at (mParameterId);
    addAndMakeVisible (mToggle);
    mButtonAttachment.reset (
        new ButtonAttachment (mParameterManager, param.id, mToggle)
    );
}

ControlToggle::~ControlToggle()
{

}

//==============================================================================

void ControlToggle::resized()
{
    static const auto sTextBoxHeight = 20;
    const auto bounds = getLocalBounds();
    mToggle.setBounds (
        bounds.getX(),
        bounds.getY(),
        bounds.getWidth(),
        bounds.getHeight() - sTextBoxHeight
    );
}

//==============================================================================

} // namespace ui
} // namespace mbctrl
