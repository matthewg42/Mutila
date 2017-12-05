This example shows two ways a mode may flag itself as finished.

ModeA checks to see if the button is pushed in it's modeUpdate member. It then sets Mode::\_state to Finished. Note that there is a delay associated with this because ModeA only updates once every 500ms.

ModeB implements it's own isFinished() member, and returns true if the button has been tapped. This is more immediate because isFinished is called every time ModeManager::update is called.
