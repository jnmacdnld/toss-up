#define RECORD_BUTTON vexRT[Btn8R]

task Recorder()
{
	// Define variables to store the state of the record button
  bool current_state = vexRT[Btn8R];
  bool last_state = false;

  // Define variables for the recording itself
  long initial_encoder = 0;
  bool recording = false;

  while (true)
  {
    // Store the current state
    current_state = vexRT[Btn8R];  

    // Determine whether the record button was just released
    bool record_released = current_state == false && last_state == true;

    // Handle the record button being released
    if (record_released)
    {
    	// If already recording, stop recording and display the mesasurment
    	if (recording)
    	{
    		// Stop recording
    		recording = false;

    		// Calculate the distance moved
    		int distance = nMotorEncoder[backLeftDrive] - initial_encoder;

    		// Print the distance
    		writeDebugStreamLine("Moved %i ticks.", distance);
			}
			// If not yet recording, start recording
			else
			{
				// Start recording
				recording = true;

				// Store the initial position of the encoder for later
    		initial_encoder = nMotorEncoder[backLeftDrive];

    		// Print a message that recording has started
    		writeDebugStreamLine("Started mesasurment.")
			}
    }


    // Update last_state for the next iteration
    last_state = current_state;

    // Don't hog CPU
    wait1Msec(25);
  }
}